#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen {

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

public:
	static void ShowDeleteUserScreen() {
		
		DrawHeader("\t\tDelete User Screen");

		string UserName = "";
		cout << "\n\nPlease enter user UserName: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName)) {
			cout << "\nthis user is not found, please enter another UserName: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUserCard(User);

		cout << "\n\nAre you sure you want to delete this user? y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {
			
			if (User.Delete()) {
				cout << "\n\nUser Deleted successfully :-)\n";
				_PrintUserCard(User);
			}
			else {
				cout << "\n\nDelete user failed :-(\n";
			}
		}
	}
};

