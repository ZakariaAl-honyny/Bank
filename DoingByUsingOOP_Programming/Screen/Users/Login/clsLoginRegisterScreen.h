#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsDate.h"
#include "clsUser.h"


using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _PerintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
	{
		cout << setw(8) << left << "" << "|" << setw(35) << LoginRegisterRecord.DateAndTime;
		cout << "" << "|" << setw(20) << LoginRegisterRecord.UserName;
		cout << "" << "|" << setw(20) << LoginRegisterRecord.Password;
		cout << "" << "|" << setw(22) << LoginRegisterRecord.Permissions;
	}

public:

	

	static void ShowLoginRegisterScreen()
	{

		if (!clsScreen::checkAccessRights(clsUser::enPermissions::pShowLoginRegister))
		{
			return;//This will exit the function and it will not continue
		}

		vector <clsUser::stLoginRegisterRecord> vLoginRgisterRecords = clsUser::GetLoginRegisterList();
		string Title = "\t   Login Register Screen";
		string SubTitle = "\t\t(" + to_string(vLoginRgisterRecords.size()) + ") Record(s)";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "|" << left << setw(35) << "Date/Time";
		cout << "|" << left << setw(20) << "User Name";
		cout << "|" << left << setw(20) << "Password";
		cout << "|" << left << setw(22) << "Permissions";
		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________\n" << endl;
		
		if (vLoginRgisterRecords.size() == 0)
			cout << "\t\t\t\tno Login Register Record Available In the System :-(";
		else
		{
			for (clsUser::stLoginRegisterRecord& LoginRegisterRecord : vLoginRgisterRecords)
			{
				_PerintLoginRegisterRecordLine(LoginRegisterRecord);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________\n" << endl;

	}
};

