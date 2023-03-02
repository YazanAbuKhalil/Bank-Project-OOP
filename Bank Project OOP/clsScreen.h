#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;


class clsScreen {

protected:
	static void DrawHeader(string Title, string SubTitle = "") {

		cout << setw(37) << left << "" << "-------------------------------------------------\n";
		cout << setw(37) << left << "" << Title << endl;
	
		if (SubTitle != "") {
			cout << setw(37) << left << "" << SubTitle << endl;
		}

		cout << setw(37) << left << "" << "-------------------------------------------------\n";

		if (!CurrentUser.IsEmpty()) {
			cout << setw(37) << left << "" << "Welcome, " << CurrentUser.FirstName << endl;
			cout << setw(37) << left << "" << "Date: " << clsDate::GetSystemDate().DateToString() << endl;
		}
	
		
	}

	static bool CheckAccessRights(clsUser::enPermissions Permission) {

		if (!CurrentUser.CheckAccessPermission(Permission)) {
			cout << "\t\t\t\t\t------------------------------------------------------";
			cout << "\n\t\t\t\t\t   Access Denied! Contact your Admin";
			cout << "\n\t\t\t\t\t------------------------------------------------------\n\n";
			return false;
		}
		else {
			return true;
		}
	}
};

