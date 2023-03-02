#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"

using namespace std;

class clsLoginScreen : protected clsScreen {

private:
	static bool _Login() {
		bool LoginFailed = false;
		short FailedTrials = 0;

		cout << "\nEnter UserName? ";
		string UserName = clsInputValidate::ReadString();

		cout << "\nEnter Password? ";
		string Password = clsInputValidate::ReadString();

		do {

			if (LoginFailed) {
				FailedTrials++;

				if (FailedTrials == 3) {
					cout << "\n\nYou are locked after " << FailedTrials << " failed trials\n\n";
					return false;
				}

				cout << "\n\nInvalid UserName/Password\n";
				cout << "you have " << (3 - FailedTrials) << " Trials to login\n\n";

				cout << "\nEnter UserName? ";
				UserName = clsInputValidate::ReadString();

				cout << "\nEnter Password? ";
				Password = clsInputValidate::ReadString();
			}

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);

		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenueScreen();
		return true;
	}

public:
	static bool ShowLoginScreen() {
		system("cls");
		DrawHeader("\t\tLogin Screen");
		return _Login();
	
	}
};

