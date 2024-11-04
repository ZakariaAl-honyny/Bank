#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferBalanceScreen.h"
#include "clsShowTransferBalanceLogScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:

	enum enTransactionsMenueOptions {
		eDeposit = 1, eWithDraw = 2, eShowTotalBalance = 3,
		eTransferBalance = 4, eShowTransferBalanceLog = 5, eShowMainMenue = 6
	};

	static void _GoBackToTransactionsMenue()
	{
		cout << "\n\nPress any key to go back to Transactions menue...";
		system("pause>0");
		ShowTransactionsMenue();
	}

	static short _ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = 0;
		Choice = clsInputValidate::ReadNumberBetween<short>(1, 5, "\t\t\t\t\tError, Enter Number Between 1 to 6 ?: ");

		return Choice;
	}

	static void _ShowDepositScreen()
	{
		//cout << "\nDeposit Screen will be here soon...\n";
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		//cout << "\nWithdraw Screen will be here soon...\n";
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalacesScreen()
	{
		//cout << "\nTotal Balances Screen will be here soon...\n";
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _ShowTransferBalanceScreen()
	{
		//cout << "\nTransfer Balance Screen will be here soon...\n";
		clsTransferBalanceScreen::ShowTransferBalanceScreen();
	}

	static void _ShowTransferBalanceLogScreen()
	{
		//cout << "\nShow Transfer Balance Log Screen will be here soon...\n";
		clsShowTransferBalanceLogScreen::ShowTransferBalanceLogScreen();
	}

	static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactiosMenueOption)
	{
		switch (TransactiosMenueOption)
		{
		case enTransactionsMenueOptions::eDeposit:
		{
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case enTransactionsMenueOptions::eWithDraw:
		{
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case enTransactionsMenueOptions::eShowTotalBalance:
		{
			system("cls");
			_ShowTotalBalacesScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case enTransactionsMenueOptions::eTransferBalance:
		{
			system("cls");
			_ShowTransferBalanceScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case enTransactionsMenueOptions::eShowTransferBalanceLog:
		{
			system("cls");
			_ShowTransferBalanceLogScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case enTransactionsMenueOptions::eShowMainMenue:
		{
			//do nothing here the main screen will handle it :-) ;
		}

		}
	}


public:

	static void ShowTransactionsMenue()
	{
		if (!clsScreen::checkAccessRights(clsUser::enPermissions::pTransactions))
		{
			return; // this will exit the function and it will not continue
		}

		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");

		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t\t   Transactions  Menue\n";
		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] With draw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer Balance.\n";
		cout << setw(37) << left << "" << "\t[5] Show Transfer Balance Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main menue.\n";
		cout << setw(37) << left << "" << "=============================================\n";
		_PerformTransactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());
	}

};












