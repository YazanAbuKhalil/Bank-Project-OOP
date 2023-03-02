#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsListUsersScreen : protected clsScreen{

private:
	static void _PrintUserRecordLine(clsUser User) {
		cout << setw(5) << left << "";
		cout << "| " << setw(10) << User.UserName();
		cout << "| " << setw(25) << User.FullName();
		cout << "| " << setw(15) << User.Phone;
		cout << "| " << setw(25) << User.Email;
		cout << "| " << setw(10) << User.Password;
		cout << "| " << setw(10) << User.Permissions;
		cout << endl;
	}

public:
	static void ShowListUsersScreen() {
		
		vector <clsUser> vUsers = clsUser::GetUserList();

		string Title = "\t\tUser List Screen";
		string SubTitle = "\t\t(" + to_string(vUsers.size()) + ") User(s).";

		DrawHeader(Title, SubTitle);

		cout << "\n\n";
		cout << setw(5) << left << "" << "--------------------------------------------------------------------------------------------------------------------\n";
		cout << setw(5) << left << "" << "| " << setw(10) << "UserName";
		cout << "| " << setw(25) << "Full Name";
		cout << "| " << setw(15) << "Phone";
		cout << "| " << setw(25) << "Email";
		cout << "| " << setw(10) << "Password";
		cout << "| " << setw(10) << "Permissions";
		cout << "\n\n";
		cout << setw(5) << left << "" << "--------------------------------------------------------------------------------------------------------------------\n";

		if (vUsers.size() == 0) {
			cout << "\n\n" << setw(37) << left << "" << "No Users found in the file\n";
		}
		else {
			for (clsUser User : vUsers) {
				_PrintUserRecordLine(User);
			}
		}
		cout << setw(5) << left << "" << "--------------------------------------------------------------------------------------------------------------------\n\n";
	}
};

