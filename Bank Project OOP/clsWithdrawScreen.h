#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen {

private:
	static void _PrintClientData(clsClient Client) {

		cout << "\nClient Card:\n";
		cout << "---------------------\n";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n---------------------\n";

	}

	static float _ReadWithdrawAmount(clsClient Client) {
		float Amount = 0;
		cout << "\nPlease enter deposit amount? ";
		Amount = clsInputValidate::ReadFloatNumber();

		return Amount;
	}

public:
	static void ShowWithdrawScreen() {
		DrawHeader("\t\tWithdraw Screen");


		string AccountNumber = "";
		cout << "\nPlease enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsClient::IsClientExist(AccountNumber)) {
			cout << "\nClient with Account Number [" << AccountNumber << "] does not exist.\n";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsClient Client = clsClient::Find(AccountNumber);
		_PrintClientData(Client);

		float Amount = 0;
		cout << "\nPlease enter withdraw amount? ";
		Amount = clsInputValidate::ReadFloatNumber();

		cout << "\n\nAre you sure you want to perform this transaction? y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {
			if (Client.Withdraw(Amount)) {
				cout << "\nAmount withdraw successfully.\n";
				cout << "\nNew Balance is: " << Client.AccountBalance;
			}
			else {
				cout << "\nCannot withdraw, Insuffecient Balance!\n";
				cout << "\nAmount to withdraw is: " << Amount;
				cout << "\nYour Balance is: " << Client.AccountBalance;
			}
		}
	}
};

