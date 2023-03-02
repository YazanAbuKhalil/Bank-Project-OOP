#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRate.h"
#include "clsCurrencyCalculaterScreen.h"

using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen {

private:
	enum enCurrencyMainMenueOption {
		eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenue = 5
	};

	static void _ShowCurrenciesListScreen() {
		//cout << "\n\tList Currencies screen will be here\n";
		clsCurrenciesListScreen::ShowCurrenciesListScreen();

	}

	static void _ShowFindCurrencyScreen() {
		//cout << "\n\tFind Currency Screen will be here\n";
		clsFindCurrencyScreen::ShowFindCurrencyScreen();

	}

	static void _ShowUpdateCurrencyScreen() {
		//cout << "\n\tUpdate rate screen will be here\n";
		clsUpdateCurrencyRate::ShowUpdateCurrencyRateScreen();

	}

	static void _ShowCurrencyCalaculaterScreen() {
		//cout << "\n\tCurrency calculater screen will be here\n";
		clsCurrencyCalculaterScreen::ShowCurrencyCalculaterScreen();
	}

	static void _GoBackToCurrencyMainMenueScreen() {

		cout << "\n\nPress any key to go back to Currency exchange main screen...";
		system("pause>0");
		ShowCurrencyExchangeMainScreen();
	}

	static short _ReadCurrencyExchangeMainMenueOpthion() {

		short Choice = 0;
		cout << setw(37) << left << "" <<  "Choose what do you want to do? [1 to 5]? ";
		Choice = clsInputValidate::ReadShortNumberBetween(1, 5);

		return Choice;
	}

	static void _PerformCurrencyExchangeMainMenueOption(enCurrencyMainMenueOption CurrencyMainMenueOption) {

		switch (CurrencyMainMenueOption) {

		case enCurrencyMainMenueOption::eListCurrencies:
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackToCurrencyMainMenueScreen();
			break;

		case enCurrencyMainMenueOption::eFindCurrency:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyMainMenueScreen();
			break;

		case enCurrencyMainMenueOption::eUpdateRate:
			system("cls");
			_ShowUpdateCurrencyScreen();
			_GoBackToCurrencyMainMenueScreen();
			break;

		case enCurrencyMainMenueOption::eCurrencyCalculator:
			system("cls");
			_ShowCurrencyCalaculaterScreen();
			_GoBackToCurrencyMainMenueScreen();
			break;

		case enCurrencyMainMenueOption::eMainMenue:
			break;
		}
	}
public:
	static void ShowCurrencyExchangeMainScreen() {

		system("cls");
		DrawHeader("\t\tCurrency Exchange Main Screen");

		cout << endl << endl; 
		cout << setw(37) << left << "" << "===========================================================\n";
		cout << setw(37) << left << "" << "\t\t\tCurrency Exchange Menue\n";
		cout << setw(37) << left << "" << "===========================================================\n";

		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency\n.";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculater.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		
		cout << setw(37) << left << "" << "===========================================================\n";

		_PerformCurrencyExchangeMainMenueOption((enCurrencyMainMenueOption)_ReadCurrencyExchangeMainMenueOpthion());

	}
};

