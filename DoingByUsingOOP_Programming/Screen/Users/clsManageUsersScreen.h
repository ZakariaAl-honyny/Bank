#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsListUserScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:

	enum enMangeUsersOptions {
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
	};

	static short _ReadMangeUsersMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = 0;
		Choice = clsInputValidate::ReadNumberBetween<short>(1, 6, "\t\t\t\t\tEnter Number Between 1 to 6 ? ");

		return Choice;
	}

	static void _GoBackToMangeUsersMenue()
	{
		cout << "\n\n\tPress any key to go back to Mange Users menue...";
		system("pause>0");
		ShowMangeUsersMenue();
	}

	static void _ShowListUsersScreen()
	{
		//cout << "\nList Users Screen will be here soon...\n";
		clsListUserScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		//cout << "\nAdd New User Screen will be here soon...\n";
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		//cout << "\nDelete User Screen will be here soon...\n";
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		//cout << "\nUpdate User Screen will be here soon...\n";
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		//cout << "\nFind User Screen will be here soon...\n";
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformMangeUsersMenueOption(enMangeUsersOptions MangeUsersMenueOption)
	{
		switch (MangeUsersMenueOption)
		{
		case enMangeUsersOptions::eListUsers:
		{
			system("cls");
			_ShowListUsersScreen();
			_GoBackToMangeUsersMenue();
			break;
		}

		case enMangeUsersOptions::eAddNewUser:
		{
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToMangeUsersMenue();
			break;
		}

		case enMangeUsersOptions::eDeleteUser:
		{
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToMangeUsersMenue();
			break;
		}

		case enMangeUsersOptions::eUpdateUser:
		{
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToMangeUsersMenue();
			break;
		}

		case enMangeUsersOptions::eFindUser:
		{
			system("cls");
			_ShowFindUserScreen();
			_GoBackToMangeUsersMenue();
			break;
		}

		case enMangeUsersOptions::eMainMenue:
		{
			//do nothing here the main screen will handle it :-); 
			//ShowMainMenue();
		}

		}
	}

	

	

public:

	static void ShowMangeUsersMenue()
	{
		if (!clsScreen::checkAccessRights(clsUser::enPermissions::pManageUsers))
		{
			return; // this will exit the function and it will not continue
		}

		system("cls");
		_DrawScreenHeader("\tManage Users Screen");

		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t       Mange Users  Menue\n";
		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "=============================================\n";
		_PerformMangeUsersMenueOption((enMangeUsersOptions)_ReadMangeUsersMenueOption());
	}

};

