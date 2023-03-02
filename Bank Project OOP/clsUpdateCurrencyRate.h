#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsUpdateCurrencyRate : protected clsScreen {

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
public:
	static void ShowUpdateCurrencyRateScreen() {

		DrawHeader("\t\tUpdate Currency Screen");

		string CurrencyCode = "";
		cout << "\nPlease enter Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			cout << "\nCurrency code does not exist, please enter another code ? ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		cout << "\n\nAre you sure you want to update the rate of this Currency? y/n?";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			cout << "\n\nUpdate Currency Rate:\n";
			cout << "-----------------------------\n\n";

			cout << "Enter New Rate: ";
			float NewRate = clsInputValidate::ReadFloatNumber();
			Currency.UpdateRate(NewRate);

			cout << "\n\nCurrency Rate updated successfully :-)\n";
			_PrintCurrency(Currency);

		}
	}
};

