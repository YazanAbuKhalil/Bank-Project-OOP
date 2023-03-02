#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsString.h"

using namespace std;

class clsCurrency {

private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Seperator = "#//#") {

		vector <string> _vCurunciyData = clsString::Split(Line, Seperator);

		return clsCurrency(enMode::UpdateMode, _vCurunciyData[0], _vCurunciyData[1], _vCurunciyData[2], stod(_vCurunciyData[3]));

	}

	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile() {
		vector <clsCurrency>_vCurrencies;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {
			string Line = "";
			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				_vCurrencies.push_back(Currency);
			}
			MyFile.close();

		}
		return _vCurrencies;
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#") {

		string Line = "";

		Line += Currency.Country() + Seperator;
		Line += Currency.CurrencyCode() + Seperator;
		Line += Currency.CurrencyName() + Seperator;
		Line += to_string(Currency.Rate()) + Seperator;

		return Line;
	}

	static void _SaveCurrenciesDataToFile(vector <clsCurrency> vCurrencies) {

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		if (MyFile.is_open()) {

			for (clsCurrency C : vCurrencies) {
				MyFile << _ConvertCurrencyObjectToLine(C) << endl;
			}
			MyFile.close();
		}
	}

	void _Update() {

		vector <clsCurrency> _vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& C : _vCurrencies) {
			if (C.CurrencyCode() == _CurrencyCode) {
				C = *this;
				break;
			}
		}

		_SaveCurrenciesDataToFile(_vCurrencies);

	}
public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	//Read only
	string Country() {
		return _Country;
	}

	//Read only
	string CurrencyCode() {
		return _CurrencyCode;
	}

	//Read only
	string CurrencyName() {
		return _CurrencyName;
	}

	void UpdateRate(float NewRate) {
		_Rate = NewRate;
		_Update();
	}

	float Rate() {
		return _Rate;
	}

	bool IsEmpty() {
		return _Mode == enMode::EmptyMode;
	}

	static clsCurrency FindByCode(string CurrencyCode) {

		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {

			string Line = "";

			while (getline(MyFile, Line)) {

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode) {
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
			return _GetEmptyCurrencyObject();
		}

	}

	static clsCurrency FindByCountry(string Country) {

		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country()) == Country) {
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
			return _GetEmptyCurrencyObject();
		}
	}

	static bool IsCurrencyExist(string CurrencyCode) {

		clsCurrency Currency = FindByCode(CurrencyCode);
		return !Currency.IsEmpty();
	}

	static vector <clsCurrency> GetCurrenciesList() {
		return _LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float Amount) {
		return Amount / Rate();
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2) {

		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD") {
			return AmountInUSD;
		}
		

		return AmountInUSD * Currency2.Rate();
	}

};

