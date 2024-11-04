#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen
{
private:
	enum enCurrenciesMainMenueOptions {
		eListCurrencies = 1, eFindCurrency = 2,  eUpdateCurrencyRate = 3,
		eCurrencyCalculator = 4, eMainScreen = 5
	};

	static short _ReadCurrenciesMainMenueOptions()
	{
		short Choice = 0;
		cout << setw(37) << left << "" << "Chooce what do you want to do ? from [1 to 5] ? ";
		Choice = clsInputValidate::ReadNumberBetween<short>(1, 5, "\t\t\t\t     Invaild Choice, Enter Number between [1 to 5] ? ");

		return Choice;
	}

	static void _GoBackToCurrenciesMenue()
	{
		cout << setw(8) << left << "" << "\n\n\tPress any key to go back to Currencies Menue...";
		system("pause>0");
		ShowCurrenciesMenue();
	}

	static void _ShowCurrenciesListScreen()
	{
		//cout << "\nCurrencies List Screen Will be here soon...";
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		//cout << "\nFind Currency Screen Will be here soon...";
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateCurrencyRateScreen()
	{
		//cout << "\nUpdate Currency Rate Screen Will be here soon...";
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		//cout << "\nCurrency Calculator Screen Will be here soon...";
		clsCurrencyCalculatorScreen	::ShowCurrencyCalculatorScreen();
	}

	static void _PerformCurrenciesMainMenueOptions(enCurrenciesMainMenueOptions CurrenciesExchangeMainMenueOption)
	{
		switch (CurrenciesExchangeMainMenueOption)
		{
		case enCurrenciesMainMenueOptions::eListCurrencies:
		{
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackToCurrenciesMenue();
			break;
		}

		case enCurrenciesMainMenueOptions::eFindCurrency:
		{
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrenciesMenue();
			break;
		}

		case enCurrenciesMainMenueOptions::eUpdateCurrencyRate:
		{
			system("cls");
			_ShowUpdateCurrencyRateScreen();
			_GoBackToCurrenciesMenue();
			break;
		}

		case enCurrenciesMainMenueOptions::eCurrencyCalculator:
		{
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrenciesMenue();
			break;
		}

		case enCurrenciesMainMenueOptions::eMainScreen:
		{
			//do nothing here the main screen handle it :-).;
			//You don't need any code here becouse the main screen handle it for you!.
		}

		}
	}
public:

	static void ShowCurrenciesMenue()
	{
		system("cls");
		clsScreen::_DrawScreenHeader("\tCurrency Exchange Main Screen");

		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Currency Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Screen.\n";
		cout << setw(37) << left << "" << "=============================================\n";
		_PerformCurrenciesMainMenueOptions((enCurrenciesMainMenueOptions)_ReadCurrenciesMainMenueOptions());
	}
};