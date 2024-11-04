#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:

	static clsCurrency _GetCurrency(string Message = "\nPlease Enter CurrencyCode? ")
	{
		string CurrencyCode = "";
		cout << Message;
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency Code is not Found, chooce another one? ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);

		return Currency;
	}

	static float _ReadAmount()
	{
		float Amount = 0;
		cout << "\nEnter Amount To Exhange? ";
		Amount = clsInputValidate::ReadNumber<float>();

		return Amount;
	}

	static void _PrintCurrencyCard(clsCurrency Currency, string Title)
	{
		cout << "\n" << Title;
		cout << "\n__________________\n";
		cout << "\nCountry     : " << Currency.Country();
		cout << "\nCode        : " << Currency.CurrencyCode();
		cout << "\nName        : " << Currency.CurrencyName();
		cout << "\nRate (1$) = : " << Currency.Rate();
		cout << "\n__________________\n";
	}

	static void _PrintCalcultionResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
	{
		_PrintCurrencyCard(CurrencyFrom, "Convert From:");

		float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);
		cout << "\n" << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << AmountInUSD << " USD\n";

		if (CurrencyTo.CurrencyCode() == "USD")
		{
			return;
		}

		cout << "\nConverting from USD to:\n";

		_PrintCurrencyCard(CurrencyTo, "Convert To:");

		float AmountInCurrencyTo = CurrencyFrom.ConvertToAnotherCurrency(Amount, CurrencyTo);
		cout << "\n" << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << AmountInCurrencyTo << " " << CurrencyTo.CurrencyCode();
		
	}

public:

	static void ShowCurrencyCalculatorScreen()
	{
		char Continue = 'y';

		while(Continue == 'Y' || Continue == 'y')
		{
			system("cls");
			clsScreen::_DrawScreenHeader("\tCurrency Culcalator Screen");

			clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code To Exchange From? ");
			clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code To Exchange To? ");

			float AmountToExchange = _ReadAmount();

			_PrintCalcultionResults(AmountToExchange, CurrencyFrom, CurrencyTo);

			cout << "\n\nDo you want to perform another culcaltion? y/n? ";
			cin >> Continue;
		}
	}

};