#pragma once
#include <iostream>
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"
#include "Global.h"

using namespace std;

class clsClient : public clsPerson {

private:

	struct stTransferLogRecord;
	enum enMode {
	eEmptyMode = 0, eUpdateMode = 1, eAddMode = 2};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDeleted = false;

	static clsClient _ConvertLineToClientObject(string Line, string Seperator = "#//#") {

		vector <string> vClientsDate = clsString::Split(Line, Seperator);

		return clsClient(enMode::eUpdateMode, vClientsDate[0], vClientsDate[1], vClientsDate[2], vClientsDate[3], vClientsDate[4], vClientsDate[5], stod(vClientsDate[6]));
	}


	static vector <clsClient> _LoadClientDateFromFile() {

		vector <clsClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {
			string Line = "";

			while (getline(MyFile, Line)) {
				clsClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;
	}

	static clsClient _GetEmptyClientObject() {

		return clsClient(enMode::eEmptyMode, "", "", "", "", "", "", 0);
	}

	string _ConvertCLientObjectToLine(clsClient Client, string Seperator = "#//#") {

		string DataLine = "";

		DataLine += Client.FirstName + Seperator;
		DataLine += Client.LastName + Seperator;
		DataLine += Client.Email + Seperator;
		DataLine += Client.Phone + Seperator;
		DataLine += Client.AccountNumber() + Seperator;
		DataLine += Client.PinCode + Seperator;
		DataLine += to_string(Client.AccountBalance);

		return DataLine;
	}

	void _SaveClientDataToFile(vector <clsClient> vClients) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open()) {

			for (clsClient Client : vClients) {
				if (!Client._MarkedForDeleted)
					MyFile << _ConvertCLientObjectToLine(Client) << endl;
			}
		}
		MyFile.close();
	}

	void _AddDataLineToFile(string Line) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open()) {
			MyFile << Line << endl;
		}

		MyFile.close();
	}

	void _AddNew() {

		_AddDataLineToFile(_ConvertCLientObjectToLine(*this));
	}

	void _Update() {

		vector <clsClient> vClients = _LoadClientDateFromFile();

		for (clsClient& C : vClients) {
			if (C.AccountNumber() == _AccountNumber) {
				C = *this;
				break;
			}
		}

		_SaveClientDataToFile(vClients);
	}

	string _PrepareTransferLogRecord(float Amount, clsClient ClientDestination, string UserName, string Seperator = "#//#") {

		string LineRecord = "";

		LineRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LineRecord += _AccountNumber + Seperator;
		LineRecord += ClientDestination.AccountNumber() + Seperator;
		LineRecord += to_string(Amount) + Seperator;
		LineRecord += to_string(_AccountBalance) + Seperator;
		LineRecord += to_string(ClientDestination.AccountBalance) + Seperator;
		LineRecord += UserName;

		return LineRecord;
	}
	
	void _RegisterTransferLog(float Amount, clsClient ClientDestination, string UserName) {
		string Line = _PrepareTransferLogRecord(Amount, ClientDestination, UserName);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open()) {
			MyFile << Line << endl;
			MyFile.close();
		}
	}

	static stTransferLogRecord _ConvertLineToTransferLogRecord(string Line, string Seperator = "#//#") {

		vector <string> vTransferLogData = clsString::Split(Line, Seperator);
		stTransferLogRecord TransferLogRecord;

		TransferLogRecord.DateTime = vTransferLogData[0];
		TransferLogRecord.SourceAccountNumber = vTransferLogData[1];
		TransferLogRecord.DestinationAccountNumber = vTransferLogData[2];
		TransferLogRecord.Amount = stod(vTransferLogData[3]);
		TransferLogRecord.SourceBalance = stod(vTransferLogData[4]);
		TransferLogRecord.DestinationBalance = stod(vTransferLogData[5]);
		TransferLogRecord.UserName = vTransferLogData[6];

		return TransferLogRecord;

	}

public:
	clsClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	struct stTransferLogRecord {

		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float SourceBalance;
		float DestinationBalance;
		string UserName;
	};

	bool IsEmpty() {
		return _Mode == enMode::eEmptyMode;
	}

	// Read only property
	string AccountNumber() {
		return _AccountNumber;
	}

	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}
	string GetPinCode() {
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance() {
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	//
	void SetMode(enMode Mode) {
		_Mode = Mode;
	}
	enMode GetMode() {
		return _Mode;
	}
	__declspec(property(get = GetMode, put = SetMode)) enMode Mode;
	//

	static vector <clsClient> GetClientsList() {
		return _LoadClientDateFromFile();
	}


	static bool IsEmptyObject(clsClient Client) {
		return Client.Mode == enMode::eEmptyMode;
	}
	static clsClient Find(string AccountNumber) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {
			string Line = "";
			while (getline(MyFile, Line)) {
				clsClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber) {
					return Client;
				}

			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {
		clsClient Client = Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	static clsClient GetAddNewCLient(string AccountNumber) {
		return clsClient(enMode::eAddMode, "", "", "", "", AccountNumber, "", 0);
	}

	enum enSaveResults {svSuccedded = 1, svFailedEmptyObject = 2, svFailedAccountFound = 3};

	enSaveResults Save() {

		switch (_Mode) {

		case enMode::eEmptyMode:
			return enSaveResults::svFailedEmptyObject;
		
		case enMode::eUpdateMode:
			_Update();
			return enSaveResults::svSuccedded;

		case enMode::eAddMode:
			if (IsClientExist(_AccountNumber)) {
				return enSaveResults::svFailedAccountFound;
			}
			else {
				_AddNew();
				_Mode = enMode::eUpdateMode;
				return enSaveResults::svSuccedded;
			}
		
		}
	}

	bool Delete() {

		vector <clsClient> vClients = _LoadClientDateFromFile();

		for (clsClient& C : vClients) {
			if (C.AccountNumber() == _AccountNumber) {
				C._MarkedForDeleted = true;
				break;
			}
		}

		_SaveClientDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	void Deposit(float Amount) {
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(float Amount) {
		if (Amount > _AccountBalance) {
			return false;
		}
		else {
			_AccountBalance -= Amount;
			Save();
		}
	}

	static float GetTotalBalances() {

		float TotalBlances = 0;

		vector <clsClient> vClients = _LoadClientDateFromFile();

		for (clsClient Client : vClients) {
			TotalBlances += Client.AccountBalance;
		}

		return TotalBlances;
	}

	bool Transfer(float Amount, clsClient& ClientDestination) {
		if (Amount > _AccountBalance) {
			return false;
		}
		Withdraw(Amount);
		ClientDestination.Deposit(Amount);
		_RegisterTransferLog(Amount, ClientDestination, CurrentUser.UserName());
		return true;
	}

	static vector <stTransferLogRecord> GetTransferLogList() {

		vector <stTransferLogRecord> vTransferLogRecord;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open()) {

			string Line = "";
			stTransferLogRecord TransferLogRecord;

			while (getline(MyFile, Line)) {
				TransferLogRecord = _ConvertLineToTransferLogRecord(Line);
				vTransferLogRecord.push_back(TransferLogRecord);
			}
			MyFile.close();
		}

		return vTransferLogRecord;
	}
	
};

