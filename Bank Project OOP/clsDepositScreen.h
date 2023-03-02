#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsClient.h"

using namespace std;

class clsDepositScreen : protected clsScreen {

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

public:
	static void ShowDepositScreen() {
		DrawHeader("\t\tDeposit Screen");

		string AccountNumber = "";
		cout << "\nPlease enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount Number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsClient Client = clsClient::Find(AccountNumber);
		_PrintClientData(Client);

		float Amount = 0;
		cout << "\nPlease enter deposit amount? ";
		Amount = clsInputValidate::ReadFloatNumber();
		
		cout << "\n\nAre you sure you want to perform this transaction? y/n ? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {
			Client.Deposit(Amount);
			cout << "\n\nAmount Deposited successfully.\n";
			cout << "\nNew Balance is: " << Client.AccountBalance << endl;
		}
		else {
			cout << "\nOperation was cancelled.\n";
		}

	}
};

