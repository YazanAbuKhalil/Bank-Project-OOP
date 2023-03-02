#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
using namespace std;

class clsMainScreen : protected clsScreen {

private:
	enum enMainMenueOption {
		eClientList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eTransactions = 6, eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9, eLogout = 10
	};

	static short _ReadMainMenueOption() {
		short Choice = 0;
		cout << setw(37) << left << "" << "Choose what do you want to do [1 to 10] ? ";
		Choice = clsInputValidate::ReadShortNumberBetween(1, 10);
		return Choice;
	}

	static void _GoBackToMainMenue() {
		cout << "\nplease press any key to go back to main menue...";
		system("pause>0");
		ShowMainMenueScreen();
	}

	static void _ShowClientListScreen() {
		clsClientListScreen::ShowClientListScreen();
	}

	static void _ShowAddNewClientScreen() {
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen() {
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen() {
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen() {
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsScreen() {
		clsTransactionsScreen::ShowTransactionsScreen();
	}

	static void _ShowManageUsersScreen() {
		clsManageUsersScreen::ShowManageUsersScreen();
	}

	static void _ShowLoginRegisterScreen() {
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}

	static void _ShowCurrencyExchangeScreen() {
		clsCurrencyExchangeMainScreen::ShowCurrencyExchangeMainScreen();
	}

	static void _Logout() {
		CurrentUser = clsUser::Find("", "");
	}

	static void _PerformMainMenueOption(enMainMenueOption MainMenueOption) {

		switch (MainMenueOption) {

		case enMainMenueOption::eClientList:
			system("cls");
			_ShowClientListScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOption::eAddNewClient:
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOption::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOption::eUpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOption::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOption::eTransactions:
			system("cls");
			_ShowTransactionsScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOption::eManageUsers:
			system("cls");
			_ShowManageUsersScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOption::eLoginRegister:
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenue();
			break; 

		case enMainMenueOption::eCurrencyExchange:
			system("cls");
			_ShowCurrencyExchangeScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOption::eLogout:
			system("cls");
			_Logout();
			break;
		}
	}


public:
	static void ShowMainMenueScreen() {
		system("cls");
		DrawHeader("\t\tMain Screen");

		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "=============================================\n";

		cout << setw(37) << left << "" <<"\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transacrions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "=============================================\n";

		_PerformMainMenueOption((enMainMenueOption)_ReadMainMenueOption());

	}

};

