#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginScreen.h"
#include "Global.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:

	enum enMainMenueOptions {
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
		eUpdateClients = 4, eFindClient = 5, eTransactions = 6,
		eMangeUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9, eLogout = 10
	};

	static short _ReadMainMenueOption()
	{

		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
		short Choice = 0;
		Choice = clsInputValidate::ReadNumberBetween<short>(1, 10, "\t\t\t\t\tError, Enter Number between 1 to 10? ");

		return Choice;
	}

	static void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to main menue...";
		system("pause>0");
		ShowMainMenue();
	}


	static void _ShowAllClientsScreen()
	{
		//cout << "\nClient List Screen Will be here soon...\n";
		clsClientListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientScreen()
	{
		//cout << "\nAdd New Client Screen Will be here soon...\n";
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		//cout << "\nDelete Client Screen Will be here soon...\n";
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		//cout << "\nUpdate Client Screen Will be here soon...\n";
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		//cout << "\nFind  Client Screen Will be here soon...\n";
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenue()
	{
		//cout << "\nTravsactions Menue Will be here soon...\n";
		clsTransactionsScreen::ShowTransactionsMenue();
	}

	static void _ShowMangeUsersMenue()
	{
		//cout << "\nManage Users Menue Will be here soon...\n";
		clsManageUsersScreen::ShowMangeUsersMenue();
	}

	static void _ShowLoginRegisterScreen()
	{
		//cout << "\nLogin Register Screen Will be here soon...\n";
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}

	static void _ShowCurrencyExchangeScreen()
	{
		//cout << "\n Currency Exchange Screen Will be here soon...\n";
		clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();
	}

	/*static void _ShowEndScreen()
	{
		cout << "\nEnd Screen Will be here soon...\n";
	}*/

	static void _LogoutScreen()
	{
		CurrentUser = clsUser::Find("", "");
		//clsLoginScreen::ShowLoginScreen();

		//then it will go back to main function.
	}

	static void _PerformMainmenueOption(enMainMenueOptions MainMenueOption)
	{

		switch (MainMenueOption)
		{
		case enMainMenueOptions::eListClients:
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eAddNewClient:
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eUpdateClients:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eTransactions:
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eMangeUsers:
			system("cls");
			_ShowMangeUsersMenue();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eLoginRegister:
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eCurrencyExchange:
			system("cls");
			_ShowCurrencyExchangeScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eLogout:
			system("cls");
			_LogoutScreen();
			break;

		}

	}

public:

	static void ShowMainMenue()
	{
		system("cls");
		_DrawScreenHeader("\t\tMain Screen");

		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain  Menue\n";
		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions Menue.\n";
		cout << setw(37) << left << "" << "\t[7] Mange Users Menue.\n";
		cout << setw(37) << left << "" << "\t[8] Show Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "=============================================\n";
		_PerformMainmenueOption((enMainMenueOptions)_ReadMainMenueOption());
	}
};