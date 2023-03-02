#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>

using namespace std;

class clsCurrenciesListScreen : protected clsScreen{

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


    static void ShowCurrenciesListScreen()
    {


        vector <clsCurrency> vCurrencys = clsCurrency::GetCurrenciesList();
        string Title = "\t  Currencies List Screen";
        string SubTitle = "\t    (" + to_string(vCurrencys.size()) + ") Currency.";

        DrawHeader(Title, SubTitle);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        if (vCurrencys.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";
        else

            for (clsCurrency Currency : vCurrencys)
            {

                _PrintCurrency(Currency);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

    }
};


