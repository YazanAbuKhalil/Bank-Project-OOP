#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsFindClientScreen.h"

using namespace std;

class clsFindClientScreen : protected clsScreen {

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
	static void ShowFindClientScreen() {
		
		if (!CheckAccessRights(clsUser::enPermissions::pFindClient)) {
			return;
		}

		DrawHeader("\t\tFind CLient Screen");

		string AccountNumber = "";
		cout << "\nPlease enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount Number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsClient Client = clsClient::Find(AccountNumber);

		if (!clsClient::IsEmptyObject(Client))
			cout << "\nCLient Found :-)\n";
		else {
			cout << "\nClient was not found\n";
		}

		_PrintClientData(Client);
	}

};


