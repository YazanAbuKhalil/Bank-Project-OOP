#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsUpdateUserScreen.h"


using namespace std;

class clsManageUsersScreen : protected clsScreen {

private:
	enum enManageUsersOption {
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
	};

	static short _ReadManageUsersOption() {
		short Choice = 0;
		cout << setw(37) << left << "" << "Choose what do you want to do [1 to 6] ? ";
		Choice = clsInputValidate::ReadShortNumberBetween(1, 6);
		return Choice;
	}

	static void _GoBackToManageUsersScreen() {
		cout << "\nPlease press any key to go back to Manage Users Screen...";
		system("pause>0");
		ShowManageUsersScreen();
	}

	static void _ShowListUsersScreen() {
		clsListUsersScreen::ShowListUsersScreen();
	}

	static void _ShowAddNewUserScreen() {
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}
	

	static void _ShowDeleteUserScreen() {
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen() {
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen() {
		clsFindUserScreen::ShowFindUserScreen();
	}


	static void _PerformManageUsersOption(enManageUsersOption ManageUsersOption) {

		switch (ManageUsersOption) {

		case enManageUsersOption::eListUsers:
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUsersScreen();
			break;

		case enManageUsersOption::eAddNewUser:
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUsersScreen();
			break;

		case enManageUsersOption::eDeleteUser:
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersScreen();
			break;

		case enManageUsersOption::eUpdateUser:
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersScreen();
			break;

		case enManageUsersOption::eFindUser:
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersScreen();
			break;

		case enManageUsersOption::eMainMenue:
			cout << "";
			break;
		}
	}

public:
	static void ShowManageUsersScreen() {
		if (!CheckAccessRights(clsUser::enPermissions::pManageUsers)) {
			return;
		}


		system("cls");
		DrawHeader("\t\tManage Users Screen");

		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t\tManage Users Menue Menue\n";
		cout << setw(37) << left << "" << 
			"=============================================\n";

		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";

		cout << setw(37) << left << "" <<
			"=============================================\n";

		_PerformManageUsersOption((enManageUsersOption)_ReadManageUsersOption());
	}
};

