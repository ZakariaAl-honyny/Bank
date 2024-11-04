#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUitil.h"
//#include "Global.h" // this include has 100 Errors

using namespace std;

class clsUser : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;

	string _PerparLogInRecord(string Sperator = "#//#")
	{
		string stRegisterRecord = "";

		stRegisterRecord += clsDate::GetSystemDateTimeString() + Sperator;
		stRegisterRecord += _UserName + Sperator;
		stRegisterRecord += clsUitil::EncryptText(_Password) + Sperator;
		stRegisterRecord += to_string(_Permissions);

		return stRegisterRecord;
	}

	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string DateLine, string Sperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector<string> vDataRecord;
		vDataRecord = clsString::Split(DateLine, Sperator);

		LoginRegisterRecord.DateAndTime = vDataRecord[0];
		LoginRegisterRecord.UserName = vDataRecord[1];
		LoginRegisterRecord.Password = clsUitil::DecryptText(vDataRecord[2]);
		LoginRegisterRecord.Permissions = stoi(vDataRecord[3]);

		return LoginRegisterRecord;
	}

	static clsUser _ConvertLineToUserObject(string DateLine, string Sperator = "#//#")
	{

		vector<string> vUserData;
		vUserData = clsString::Split(DateLine, Sperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3],
			vUserData[4], clsUitil::DecryptText(vUserData[5]), stod(vUserData[6]));
	}

	static string _ConvertUserObjectToLine(clsUser User, string Sperator = "#//#")
	{
		string stUserRecord = "";

		stUserRecord += User.FirstName + Sperator;
		stUserRecord += User.LastName + Sperator;
		stUserRecord += User.Email + Sperator;
		stUserRecord += User.Phone + Sperator;
		stUserRecord += User.UserName + Sperator;
		stUserRecord += clsUitil::EncryptText(User.Password) + Sperator;
		stUserRecord += to_string(User.Permissions);

		return stUserRecord;
	}

	static vector <clsUser> _LoadUsersDataFromFile()
	{
		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}

			MyFile.close();
		}

		return vUsers;
	}

	static void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{

		fstream MyFile;
		MyFile.open("Users.txt", ios::out);//OverWrite

		if (MyFile.is_open())
		{
			string DataLine;

			for (clsUser& User : vUsers)
			{
				if (User._MarkedForDelete == false)
				{
					//we only write records that are not marked for delete.
					DataLine = _ConvertUserObjectToLine(User);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : _vUsers)
		{
			if (User.UserName == _UserName)
			{
				User = *this;
				break;
			}

		}

		_SaveUsersDataToFile(_vUsers);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	enum enPermissions {
		pAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTransactions = 32,
		pManageUsers = 64, pLoginRegister = 128
	};

	struct stLoginRegisterRecord
	{
		string DateAndTime;
		string UserName;
		string Password;
		int Permissions;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName,
		string Password, int Permissions) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	//Property Set 
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	string GetUserName()
	{
		return _UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	//Property Set
	void SetPassword(string Password)
	{
		_Password = Password;
	}

	//Property Get
	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName)
	{
		vector <clsUser> vUsers = GetUsersList();
		
		for (clsUser& User : vUsers)
		{
			if (User.UserName == UserName)
			{
				return User;
			}
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{
		vector <clsUser> vUsers = GetUsersList();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == UserName && User.Password == Password)
			{
				return User;
			}
		}

		return _GetEmptyUserObject();
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
			//This will add new record to file or database
			if (clsUser::IsUserExist(_UserName))
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

	static bool IsUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);

		return (!User.IsEmpty());
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool Delete()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : _vUsers)
		{
			if (User.UserName == _UserName)
			{
				User._MarkedForDelete = true;
				break;
			}

		}

		_SaveUsersDataToFile(_vUsers);

		//refresh object data in run time after delete the object from file or database
		*this = _GetEmptyUserObject();

		return true;
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermssion(enPermissions Permssions)
	{
		if (Permssions == enPermissions::pAll)
			return true;

		if ((Permssions & this->Permissions) == Permssions)
			return true;
		else
			return false;

	}

	void RegisterLogIn()
	{
		string stDataLine = _PerparLogInRecord();

		fstream MyFile1;
		MyFile1.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile1.is_open())
		{

			MyFile1 << stDataLine << endl;

			MyFile1.close();
		}
	}

	static vector<stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector<stLoginRegisterRecord>  vLiginRegjsterRecords;

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);//Read Mode

		if (MyFile.is_open())
		{
			string Line;

			stLoginRegisterRecord LoginRegisterRecord;

			while (getline(MyFile, Line))
			{
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

				vLiginRegjsterRecords.push_back(LoginRegisterRecord);
			}

			MyFile.close();
		}

		return vLiginRegjsterRecords;
	}

};