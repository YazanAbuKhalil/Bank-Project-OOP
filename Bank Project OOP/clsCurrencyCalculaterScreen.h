#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
#include "clsString.h"

using namespace std;

class clsCurrencyCalculaterScreen : protected clsScreen {

private:

	static clsCurrency _GetCurrency(string Message) {
		string CurrencyCode = "";
		cout << Message;
		CurrencyCode = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			cout << "\nCurrency code does not exist, please enter another code ? ";
			CurrencyCode = clsInputValidate::ReadString();

		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;

	}

	static void _PrintCurrencyCard(clsCurrency Currency, string Title) {

		cout << "\n" << Title << "\n";
		cout << "--------------------------------\n";
		cout << "\nCountry         : " << Currency.Country();
		cout << "\nCode            : " << Currency.CurrencyCode();
		cout << "\nName            : " << Currency.CurrencyName();
		cout << "\nRate(1$) =      : " << Currency.Rate();

		cout << "\n--------------------------------\n";

	}

	static float _ReadAmount() {

		float Amount = 0.0;
		cout << "\nEnter Amount to Exchange: ";
		Amount = clsInputValidate::ReadFloatNumber();

		return Amount;
	}

	static void _PrintCalculationsResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo) {

		_PrintCurrencyCard(CurrencyFrom, "Convert From:");

		float AmountToUSD = CurrencyFrom.ConvertToUSD(Amount);

		cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << AmountToUSD << " USD\n";

		if (CurrencyTo.CurrencyCode() == "USD") {
			return;
		}

		cout << "\nConverting from USD to:\n";
		_PrintCurrencyCard(CurrencyTo, "To:");

		float AmountInCurrency2 = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);

		cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << AmountInCurrency2 << " " << CurrencyTo.CurrencyCode();
	}


public:
	static void ShowCurrencyCalculaterScreen() {

		char Continue = 'y';

		while (Continue == 'y' || Continue == 'Y') {

			system("cls");
			DrawHeader("\t\tCurrency Calculator Screen");

			clsCurrency CurrencyFrom = _GetCurrency("\nPlease enter Currency1 code: ");
			clsCurrency CurrencyTo = _GetCurrency("\nPlease enter Currency2 Code: ");
			float Amount = _ReadAmount();

			_PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

			cout << "\n\nDo you want to perform another calculation? y/n? ";
			cin >> Continue;
		}
		




	}
};
