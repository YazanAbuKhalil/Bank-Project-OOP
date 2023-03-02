#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen {

private:
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

	static void _ReadUserData(clsUser &User) {

		cout << "\nUpdate User Info:\n";
		cout << "-------------------\n";

		cout << "\nEnter FirstName: ";
		string FirstName = User.FirstName;
		User.FirstName = clsInputValidate::ReadString();
		if (User.FirstName == "0") {
			User.FirstName = FirstName;
		}

		cout << "\nEnter LastName: ";
		string LastName = User.LastName;
		User.LastName = clsInputValidate::ReadString();
		if (User.LastName == "0") {
			User.LastName = LastName;
		}

		cout << "\nEnter Email: ";
		string Email = User.Email;
		User.Email = clsInputValidate::ReadString();
		if (User.Email == "0") {
			User.Email = Email;
		}

		cout << "\nEnter Phone: ";
		string Phone = User.Phone;
		User.Phone = clsInputValidate::ReadString();
		if (User.Phone == "0") {
			User.Phone = Phone;
		}

		cout << "\nEnter Password: ";
		string Password = User.Password;
		User.Password = clsInputValidate::ReadString();
		if (User.Password == "0") {
			User.Password = Password;
		}


		cout << "\nEnter Permissions: "; 
		User.Permissions = _ReadUserPermissions();



	
	}

	static int _ReadUserPermissions() {

		int Permissions = 0;

		cout << "\nDo you want to give full access? y/n? ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			return -1;
		}

		cout << "\nDo you want to give access to:\n";

		cout << "\nShow Client List? y/n? ";
		Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += 1;
		}

		cout << "\nAdd New Client? y/n? ";
		Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += 2;
		}

		cout << "\nDelete Client? y/n? ";
		Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += 4;
		}

		cout << "\nUpdate Client? y/n? ";
		Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += 8;
		}

		cout << "\nFind Client? y/n? ";
		Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += 16;
		}

		cout << "\nTransaction? y/n? ";
		Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += 32;
		}

		cout << "\nManage Users? y/n? ";
		Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += 64;
		}

		cout << "\nShow Login Register? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pLoginRegister;
		}

		return Permissions;
	}

public:
	static void ShowUpdateUserScreen() {
		DrawHeader("\t\tUpdate User Screen");

		string UserName = "";
		cout << "\n\nPlease enter user UserName: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName)) {
			cout << "\nthis user is not found, pleasese enter another UserName: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUserCard(User);

		cout << "\n\nAre you sure you want to update this user y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {
			_ReadUserData(User);

			clsUser::enSaveResults SaveResults;

			SaveResults = User.Save();

			switch (SaveResults) {

			case clsUser::enSaveResults::eSvSuccessed:
				cout << "\n\nUser updated successfully :-)\n";
				_PrintUserCard(User);
				break;

			case clsUser::enSaveResults::eSvFailedEmptyObject:
				cout << "\nUpdated Faild, the object is empty\n";
				break;
			}
		}


	}
};
