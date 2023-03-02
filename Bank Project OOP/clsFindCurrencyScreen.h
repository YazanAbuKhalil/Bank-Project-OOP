#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen {

private:
	static void _PrintCurrency(clsCurrency Currency) {
		cout << "\nCurrency Card\n";
		cout << "--------------------------------\n";
		cout << "\nCountry         : " << Currency.Country();
		cout << "\nCode            : " << Currency.CurrencyCode();
		cout << "\nName            : " << Currency.CurrencyName();
		cout << "\nRate(1$) =      : " << Currency.Rate();

		cout << "\n--------------------------------\n";

	}

	static void _ShowResults(clsCurrency Currency) {
		if (!Currency.IsEmpty()) {
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else {
			cout << "\nCurrency was not found :-(\n";
		}
	}


public:
	static void ShowFindCurrencyScreen() {

		DrawHeader("\t\tFind Currency Screen");

		cout << "\nFind By: [1] Code or [2] Country ? ";
		short Answer = 1;

		cin >> Answer;

		if (Answer == 1) {
			string CurrencyCode;
			cout << "\nPlease enter CurrencyCode: ";
			CurrencyCode = clsInputValidate::ReadString();

			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResults(Currency);
		}
		else {
			string Country;
			cout << "\nPlease enter Country Name: ";
			Country = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResults(Currency);
		}
	
	}
};
