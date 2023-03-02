#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClient.h"
#include "clsString.h";

using namespace std;

class clsAddNewClientScreen : protected clsScreen {

private:
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

	static void _PrintClientCard(clsClient Client) {
		cout << "\nInfo:\n";
		cout << "\n----------------------------\n";
		cout << "FirstName: " << Client.FirstName << endl;
		cout << "LastName: " << Client.LastName << endl;
		cout << "FullName: " << Client.FullName() << endl;
		cout << "Email: " << Client.Email << endl; 
		cout << "Phone: " << Client.Phone << endl; 
		cout << "\n----------------------------\n";
	}

public:
	static void ShowAddNewClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient)) {
			return;
		}
		DrawHeader("\t\tAdd New Client Screen");
		
		cout << "\nPlease enter Account Number: ";
		string AccountNumber = clsInputValidate::ReadString();
		while (clsClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount number is exist, please enter another AccountNumber: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsClient NewClient = clsClient::GetAddNewCLient(AccountNumber);
		_ReadClientData(NewClient);

		clsClient::enSaveResults SaveReasults;
		SaveReasults =  NewClient.Save();

		switch (SaveReasults) {

		case clsClient::enSaveResults::svSuccedded:
			cout << "\nAccount Added successfully :-)\n";
			_PrintClientCard(NewClient);
			break;

		case clsClient::enSaveResults::svFailedAccountFound:
			cout << "\nFailed, Account was already found in the file\n";
			break;

		case clsClient::enSaveResults::svFailedEmptyObject:
			cout << "\nFailed, Account is an empty\n";
		}



	}
};

