#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen {

private:
	static void _ReadUserData(clsUser& User) {

		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();
	
		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();
	
		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();
		
		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();
	
		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permissions: ";
		User.Permissions = _ReadUserPermissions();




	}

	static int _ReadUserPermissions() {

		int Permissions = 0;
		char Answer = 'n';

		cout << "\nDo you want to give full access? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			return -1;
		}

		cout << "\nDo you want to give access to:\n";

		cout << "\nShow Client List? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pListClients;
		}

		cout << "\nAdd New Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pUpdateClient;
		}

		cout << "\nFind Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pFindClient;
		}

		cout << "\nTransaction? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pTransactions;
		}

		cout << "\nManage Users? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pManageUsers;
		}

		cout << "\nShow Login Register? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pLoginRegister;
		}

		return Permissions;
	}

	static void _PrintUserCard(clsUser User) {
		cout << "\n------------------------";
		cout << "\nFirstName    : " << User.FirstName;
		cout << "\nLastName     : " << User.LastName;
		cout << "\nFullName     : " << User.FullName();
		cout << "\nEmail        : " << User.Email;
		cout << "\nPhone        : " << User.Phone;
		cout << "\nUser Name    : " << User.UserName();
		cout << "\nPassword     : " << User.Password;
		cout << "\nPermissions  : " << User.Permissions;
		cout << "\n------------------------\n";

	}


public:
	static void ShowAddNewUserScreen() {
		DrawHeader("\t\tAdd New User Screen");


		string UserName = "";
		cout << "\n\nPlease enter user UserName: ";
		UserName = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(UserName)) {
			cout << "\nthis user is found, pleasese enter another UserName: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetNewUserObject(UserName);
		_ReadUserData(NewUser);

		clsUser::enSaveResults SaveResults = NewUser.Save();

		switch (SaveResults) {

		case clsUser::enSaveResults::eSvSuccessed:
			cout << "\nUser Added successfully :-)\n";
			_PrintUserCard(NewUser);
			break;

		case clsUser::enSaveResults::eSvFailedExistObject:
			cout << "\nSave Failed, User is already found\n";
			break;

		case clsUser::enSaveResults::eSvFailedEmptyObject:
			cout << "\nSave Failed, User object is an empty object\n";
			break;
		}

	}
};

