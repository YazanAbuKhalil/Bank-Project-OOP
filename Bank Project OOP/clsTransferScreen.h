#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClient.h"

using namespace std;

class clsTransferScreen : protected clsScreen {

private:
	static string _ReadAccountNumber(string Message) {

		string AccountNumber = "";
		cout << Message;
		cin >> AccountNumber;

		while (!clsClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount number was not found, please enter another Account Number ? ";
			cin >> AccountNumber;
		}

		return AccountNumber;
	}

	static void _PrintClientCard(clsClient Client) {
		cout << "\nClient Card:\n\n";
		cout << "-----------------------\n";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n\n-----------------------\n";
	}

	static float _CheckTransferAmount(float Amount, clsClient ClientSourse) {

		while (Amount > ClientSourse.AccountBalance) {
			cout << "\n\nAmount Exceeds the available Balance, Enter another Amount ?";
			cin >> Amount;
		}
		return Amount;
	}

public:
	static void ShowTransferScreen() {

		DrawHeader("\t\tTransfer Screen");

		
		clsClient ClientSource = clsClient::Find(_ReadAccountNumber("\n\nPlease enter Account Number to transfer from: "));
		_PrintClientCard(ClientSource);

	
		clsClient ClientDestination = clsClient::Find(_ReadAccountNumber("\n\nPlease enter Account Number to transfer to: "));
		_PrintClientCard(ClientDestination);

		float Amount = 0;
		cout << "\n\nEnter Transfer Amount? ";
		cin >> Amount;

		Amount = _CheckTransferAmount(Amount, ClientSource);


		cout << "\n\nAre you sure you want to perform this operation? y/n? ";;
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {
			
			if (ClientSource.Transfer(Amount, ClientDestination)) {
				cout << "\nTransfer done successfully\n";
			}
			else {
				cout << "\nTransfer Failed\n";
			}
		}
		
		_PrintClientCard(ClientSource);
		_PrintClientCard(ClientDestination);

	}
};


