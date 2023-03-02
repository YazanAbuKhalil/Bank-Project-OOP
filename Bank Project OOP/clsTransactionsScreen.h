#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen{

private:

	enum enTransactionsMenueOption {
		eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4, eTransferLog = 5, eMainMenue = 6
	};

	static short _ReadTransactionsMenueOption() {
		short Choice = 0;
		cout << setw(37) << left << "" << "Choose what do you want to do [1 to 6] ? ";
		Choice = clsInputValidate::ReadShortNumberBetween(1, 6);
		return Choice;
	}

	static void _GoBackToTransactionsScreen() {
		cout << "Please press any key to go back to transactions screen...";
		system("pause>0");
		ShowTransactionsScreen();
	}

	static void _ShowDepositScreen() {
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen() {
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen() {
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}

	static void _ShowTransferScreen() {
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen() {
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _PerformTransactionsMenueOption(enTransactionsMenueOption TransactionsMenueOption) {

		switch (TransactionsMenueOption) {

		case enTransactionsMenueOption::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsScreen();
			break;

		case enTransactionsMenueOption::eWithdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsScreen();
			break;

		case enTransactionsMenueOption::eTotalBalances:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsScreen();
			break;

		case enTransactionsMenueOption::eTransfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsScreen();
			break;

		case enTransactionsMenueOption::eTransferLog:
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsScreen();
			break;

		case enTransactionsMenueOption::eMainMenue:
			cout << "";
			break;
		}
	}

public:
	static void ShowTransactionsScreen() {
		
		if (!CheckAccessRights(clsUser::enPermissions::pTransactions)) {
			return;
		}

		system("cls");
		DrawHeader("\tTransactions Screen");

		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t\t\tTransactions Menue\n";
		cout << setw(37) << left << "" << "=============================================\n";

		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";

		cout << setw(37) << left << "" << "=============================================\n";

		_PerformTransactionsMenueOption((enTransactionsMenueOption)_ReadTransactionsMenueOption());
	}
};

