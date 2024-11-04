#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{


private:

	static bool _Login()
	{

		bool _LoginFaild = false;
		string _UserName, _Password;
		short _FaildLoginCount = 0;

		do
		{
			if (_LoginFaild)
			{
				_FaildLoginCount++;

				system("cls");
				_DrawScreenHeader("\t\tLogin Screen");
				cout << "\nInvalid UserName/Password, Enter Again!";
				
				cout << "\nYou have " << 3 - _FaildLoginCount << " Trial(s) to login.\n";
			}

			if (_FaildLoginCount == 3)
			{
				cout << "\n\nYou are locked after 3 trial(s).\n\n";

				return false;
			}

			cout << "\nEnter UserName? ";
			_UserName = clsInputValidate::ReadString();
			cout << "Enter Password? ";
			_Password = clsInputValidate::ReadString();
			
			CurrentUser = clsUser::Find(_UserName, _Password);

			_LoginFaild = CurrentUser.IsEmpty();

		} while (_LoginFaild);

		
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\tLogin Screen");
		return _Login();
	}
};

