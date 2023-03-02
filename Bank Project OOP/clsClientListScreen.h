#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsClient.h"

using namespace std;

class clsClientListScreen : protected clsScreen {

private:
	static void _PrintClientRecordLine(clsClient Client) {
		cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(20) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.Phone;
		cout << "| " << setw(20) << left << Client.Email;
		cout << "| " << setw(10) << left << Client.PinCode;
		cout << "| " << setw(12) << left << Client.AccountBalance;
	}

public:
	static void ShowClientListScreen() {
		
		if (!CheckAccessRights(clsUser::enPermissions::pListClients)) {
			return;
		}

		vector <clsClient> vClients = clsClient::GetClientsList();

		string Title = "\t\tClient List Screen";
		string SubTitle = "\t\t(" + to_string(vClients.size()) + ") Client(S).";
		DrawHeader(Title, SubTitle);


		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";;
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vClients.size() == 0) {
			cout << "\t\t\t\tNo Clients Available in the system!";
		}
		else {
			for (clsClient Client : vClients) {
				_PrintClientRecordLine(Client);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}
};


