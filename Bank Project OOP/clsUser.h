#pragma once
#include <iostream>
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson {

private:
	struct stLoginRegisterRecord;
	enum enUserMode {
		eEmptyMode = 0, eUpdateMode = 1, eAddMode = 2
	};
	enUserMode _UserMode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDeleted = false;

	static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#") {

		vector <string> vUserData = clsString::Split(Line, Seperator);

		return clsUser(enUserMode::eUpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5], 2), stoi(vUserData[6]));
	}

	static vector <clsUser> _LoadUsersDataFromFile() {

		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {
			string Line = "";
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}
			MyFile.close();
		}

		return vUsers;
	}

	static clsUser _GetEmptyUserObject() {

		return clsUser(enUserMode::eEmptyMode, "", "", "", "", "", "", 0);
	}

	string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#") {

		string Line = "";

		Line += User.FirstName + Seperator;
		Line += User.LastName + Seperator;
		Line += User.Email + Seperator;
		Line += User.Phone + Seperator;
		Line += User.UserName() + Seperator;
		Line += clsUtil::EncryptText(User.Password, 2) + Seperator;
		Line += to_string(User.Permissions);

		return Line;
	}

	void _SaveUsersDataToFile(vector <clsUser> vUsers) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open()) {
			for (clsUser User : vUsers) {
				if (!User.MarkedForDeleted)
					MyFile << _ConvertUserObjectToLine(User) << endl;
			}
		}
		MyFile.close();
	}

	void _Update() {

		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : vUsers) {
			if (U.UserName() == _UserName) {
				U = *this;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
	}

	void _AddNewUser(string Line) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open()) {
			MyFile << Line << endl;
		}
	}

	void _AddUser() {
		_AddNewUser(_ConvertUserObjectToLine(*this));
	}

	string _PrepareLoginRecord(string Seperator = "#//#") {

		string LoginRecord = "";

		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += _UserName + Seperator;
		LoginRecord += clsUtil::EncryptText(_Password) + Seperator;
		LoginRecord += to_string(Permissions);
		return LoginRecord;

	}


	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;


		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;

	}

	static vector <stLoginRegisterRecord> _LoadLoginRegisterFromFile() {
		vector <stLoginRegisterRecord> vLoginRegisterRecord;

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);

		if (MyFile.is_open()) {
			string DataLine = "";
			stLoginRegisterRecord LoginRegisterRecord;

			while (getline(MyFile, DataLine)) {
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(DataLine);
				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}
		}

		return vLoginRegisterRecord;
	}
public:
	clsUser(enUserMode UserMode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions) : clsPerson(FirstName, LastName, Email, Phone) {
		_UserMode = UserMode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64, pLoginRegister = 128
	};

	struct stLoginRegisterRecord {
		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};

	// Read only UserName
	string UserName() {
		return _UserName;
	}

	void SetPassword(string Password) {
		_Password = Password;
	}
	string GetPassword() {
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions) {
		_Permissions = Permissions;
	}
	int GetPermissions() {
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	//
	enUserMode UserMode() {
		return _UserMode;
	}
	//

	void SetMarkedForDeleted(bool MarkedForDeleted) {
		_MarkedForDeleted = MarkedForDeleted;
	}
	bool GetMarkedForDeleted() {
		return _MarkedForDeleted;
	}
	__declspec(property(get = GetMarkedForDeleted, put = SetMarkedForDeleted)) bool MarkedForDeleted;

	static vector <clsUser> GetUserList() {
		return _LoadUsersDataFromFile();
	}

	enum enSaveResults {eSvSuccessed = 1, eSvFailedExistObject = 2, eSvFailedEmptyObject = 3};
	enSaveResults SaveResults;

	bool IsEmpty() {
		return _UserMode == enUserMode::eEmptyMode;
	}

	enSaveResults Save() {

		switch (_UserMode) {

		case enUserMode::eEmptyMode:
			return enSaveResults::eSvFailedEmptyObject;

		case enUserMode::eAddMode:
			if (IsUserExist(_UserName)) {
				return enSaveResults::eSvFailedExistObject;
			}
			_AddUser();
			_UserMode = enUserMode::eUpdateMode;
			return enSaveResults::eSvSuccessed;

		case enUserMode::eUpdateMode:
			_Update();
			return enSaveResults::eSvSuccessed;
		}
	}

	static clsUser Find(string UserName) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {
			string Line = "";
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName() == UserName) {
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {
			string Line = "";
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName() == UserName && User.Password == Password) {
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}


	static bool IsUserExist(string UserName) {
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	static clsUser GetNewUserObject(string UserName) {
		return clsUser(enUserMode::eAddMode, "", "", "", "", UserName, "", 0);
	}

	bool Delete() {

		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		for (clsUser& User : vUsers) {
			if (User.UserName() == _UserName) {
				User.MarkedForDeleted = true;
				_SaveUsersDataToFile(vUsers);
				*this = _GetEmptyUserObject();
				return true;
			}
		}
		return false;


	}

	bool CheckAccessPermission(enPermissions Permission) {
		if (this->Permissions == enPermissions::eAll) {
			return true;
		}

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}

	void RegisterLogin() {

		string stLoginRecord = _PrepareLoginRecord();
	
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open()) {
			MyFile << stLoginRecord << endl;
			MyFile.close();
		}
	}

	static vector <stLoginRegisterRecord> GetLoginRegisterList() {
		return _LoadLoginRegisterFromFile();
	}
};

