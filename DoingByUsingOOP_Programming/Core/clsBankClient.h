#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUitil.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkdForDelete = false;

	string _PerparTransferLogRecordLine(float TransferAmount, clsBankClient DestinationClient, string Sperator = "#//#")
	{
		string TransferLogRecord = "";

		TransferLogRecord += clsDate::GetSystemDateTimeString() + Sperator;
		TransferLogRecord += _AccountNumber + Sperator;
		TransferLogRecord += DestinationClient._AccountNumber + Sperator;
		TransferLogRecord += to_string(TransferAmount) + Sperator;
		TransferLogRecord += to_string(_AccountBalance) + Sperator;
		TransferLogRecord += to_string(DestinationClient._AccountBalance) + Sperator;
		TransferLogRecord += CurrentUser.UserName;
		//stRegisterRecordLine
		return TransferLogRecord;
	}

	void _RegisterTransferBalancelog(float Amount, clsBankClient DestinationClient)
	{
		string stDataLine = _PerparTransferLogRecordLine(Amount, DestinationClient);

		fstream MyFile;
		MyFile.open("TransferBalanceLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	struct stTransferBalaceLogRecord;
	static stTransferBalaceLogRecord _ConvertTransferBalanceLogLineToRecord(string stDataLine, string Sperator = "#//#")
	{
		stTransferBalaceLogRecord TransferBalaceLogRecord;
		vector <string> vTransferBalaceLogRecordLine = clsString::Split(stDataLine, Sperator);

		TransferBalaceLogRecord.DateTime = vTransferBalaceLogRecordLine[0];
		TransferBalaceLogRecord.SourceAccountNumber = vTransferBalaceLogRecordLine[1];
		TransferBalaceLogRecord.DestinationAccountNumber = vTransferBalaceLogRecordLine[2];
		TransferBalaceLogRecord.TransferAmount = stof(vTransferBalaceLogRecordLine[3]);
		TransferBalaceLogRecord.SourceBalanceAfterTransfered = stof(vTransferBalaceLogRecordLine[4]);
		TransferBalaceLogRecord.DestinationBalanceAfterTransfered = stof(vTransferBalaceLogRecordLine[5]);
		TransferBalaceLogRecord.UserName = vTransferBalaceLogRecordLine[6];

		return TransferBalaceLogRecord;
	}

	static clsBankClient _ConvertLineToClientObject(string DateLine, string Sperator = "#//#")
	{

		vector<string> vClientData;
		vClientData = clsString::Split(DateLine, Sperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
			vClientData[4], clsUitil::DecryptText(vClientData[5]), stod(vClientData[6]));

	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Sperator = "#//#")
	{
		string stClientRecord = "";

		stClientRecord += Client.FirstName + Sperator;
		stClientRecord += Client.LastName + Sperator;
		stClientRecord += Client.Email + Sperator;
		stClientRecord += Client.Phone + Sperator;
		stClientRecord += Client.AccountNumber() + Sperator;
		stClientRecord += clsUitil::EncryptText(Client.PinCode) + Sperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;
	}

	static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);//OverWrite

		if (MyFile.is_open())
		{
			string DataLine;

			for (clsBankClient& Client : vClients)
			{
				if (Client._MarkdForDelete == false)
				{
					//we only write records that are not marked for delete.
					DataLine = _ConvertClientObjectToLine(Client);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& Client : _vClients)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client = *this;
				break;
			}

		}

		_SaveClientsDataToFile(_vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	struct stTransferBalaceLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float TransferAmount;
		float SourceBalanceAfterTransfered;
		float DestinationBalanceAfterTransfered;
		string UserName;
	};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber,
		string PinCode, double AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	//Property Read noly 
	string AccountNumber()
	{
		return _AccountNumber;
	}

	//Property Set
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	//Property Get
	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	double GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	//no UI Related code inside object
	/*void Print()
	{
		cout << "\nClient Card:";
		cout << "\n_______________________";
		cout << "\nFirstName  : " << FirstName;
		cout << "\nLastName   : " << LastName;
		cout << "\nFullName   : " << FullName();
		cout << "\nEmail      : " << Email;
		cout << "\nPhone      : " << Phone;
		cout << "\nAcc. Number: " << _AccountNumber;
		cout << "\nPinCode    : " << _PinCode;
		cout << "\nBalance    : " << _AccountBalance;
		cout << "\n_______________________\n";
	}*/

	static clsBankClient Find(string AccountNumber)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{

		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
			break;
		}

		case enMode::UpdateMode:
		{

			_Update();

			return enSaveResults::svSucceeded;

			break;
		}

		case enMode::AddNewMode:
		{
			//This will add new record to ffile or database
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();

				//we will need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}

		}
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		return (!Client1.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& Client : _vClients)
		{
			if (Client.AccountNumber() == _AccountNumber)
			{
				Client._MarkdForDelete = true;
				break;
			}

		}

		_SaveClientsDataToFile(_vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
		
	}

	//My Solution
	/*static bool TransferBalance(clsBankClient& FromClient, clsBankClient& ToClient, double Amount)
	{
		if (Amount > FromClient.AccountBalance)
		{
			return false;
		}
		else
		{
			FromClient.AccountBalance -= Amount;
			FromClient.Save();

			ToClient.AccountBalance += Amount;
			ToClient.Save();
			return true;
		}
	}*/
	bool TransferBalance(float Amount, clsBankClient& DestinationClient)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		return true;
	}

	static vector <stTransferBalaceLogRecord> GetTrnsferBalancesLogList()
	{
		vector <stTransferBalaceLogRecord> vTransferBalaceLogRecord;

		fstream MyFile;
		MyFile.open("TransferBalanceLog.txt", ios::in);//Read Mode

		if (MyFile.is_open())
		{

			string Line;
			stTransferBalaceLogRecord TransferBalaceRecord;

			while (getline(MyFile, Line))
			{
				TransferBalaceRecord = _ConvertTransferBalanceLogLineToRecord(Line);

				vTransferBalaceLogRecord.push_back(TransferBalaceRecord);
			}

			MyFile.close();
		}

		return vTransferBalaceLogRecord;
	}


}; 






