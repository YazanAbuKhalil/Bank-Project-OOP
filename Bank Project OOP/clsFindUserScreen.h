#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;

class clsFindUserScreen : protected clsScreen {

private:
	static void _PrintUserCard(clsUser User) {
		cout << "\n------------------------";
		cout << "\nFirstName    : " << User.FirstName;
		cout << "\nLastName     : " << User.LastName;
		cout << "\nFullName     : " << User.LastName;
		cout << "\nEmail        : " << User.Email;
		cout << "\nPhone        : " << User.Phone;
		cout << "\nUser Name    : " << User.UserName();
		cout << "\nPassword     : " << User.Password;
		cout << "\nPermissions  : " << User.Permissions;
		cout << "\n------------------------\n";

	}

public:
	static void ShowFindUserScreen() {
		DrawHeader("\t\tFind User Screen");

		string UserName = "";
		cout << "\nPlease enter UserName: ";
		UserName = clsInputValidate::ReadString();

		clsUser User = clsUser::Find(UserName);

		if (clsUser::IsUserExist(UserName)) {
			cout << "\nUser Found :-)\n";
		}
		else {
			cout << "\nUser is not found :-(\n";
		}
		_PrintUserCard(User);

	}
};

