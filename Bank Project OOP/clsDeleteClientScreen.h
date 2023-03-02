#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsClient.h"


using namespace std;

class clsDeleteClientScreen : protected clsScreen {

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
	static void ShowDeleteClientScreen() {
		
		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient)) {
			return;
		}

		DrawHeader("\t\tDelete Client Screen");

		string AccountNumber = "";
		cout << "\nPlease enter account number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount Number is not found, please enter another Account Number: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsClient Client = clsClient::Find(AccountNumber);
		_PrintClientData(Client);

		cout << "\n\nAre you sure you want to delete this client y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {
			
			if (Client.Delete()) {
				cout << "\nCLient Deleted successfully :-)\n";
				_PrintClientData(Client);
			}
			else {
				cout << "\nError, Client was not deleted\n";
			}
			
		}

	}
};


