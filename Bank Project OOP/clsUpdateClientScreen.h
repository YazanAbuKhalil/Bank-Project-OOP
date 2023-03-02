#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClient.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen {

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

	static void _ReadClientData(clsClient& Client) {

		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();
	}

public:
	static void ShowUpdateClientScreen() {
		
		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClient)) {
			return;
		}

		DrawHeader("\t\tUpdate Client Screen");

		string AccountNumber = "";
		cout << "\nPlease enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount Number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsClient Client1 = clsClient::Find(AccountNumber);
		_PrintClientData(Client1);

		_ReadClientData(Client1);

		clsClient::enSaveResults SaveResults;

		SaveResults = Client1.Save();

		switch (SaveResults) {

		case clsClient::enSaveResults::svSuccedded:
			cout << "\nAccount Updated successfully :-)\n";
			_PrintClientData(Client1);
			break;

		case clsClient::enSaveResults::svFailedAccountFound:
			cout << "\nAccount was already found in the file\n";
			break;

		case clsClient::enSaveResults::svFailedEmptyObject:
			cout << "\nFailed, Account is an empty\n";
		}
	}
};


