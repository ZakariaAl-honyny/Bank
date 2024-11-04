#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:

	static string _ReadCurrencyCode()
	{
		string CurrencyCode = "";
		cout << "\nPlease Enter CurrencyCode? ";
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency Code is not exsit, enter again? ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		return CurrencyCode;
	}

	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\nCurrency Card:";
		cout << "\n__________________\n";
		cout << "\nCountry     : " << Currency.Country();
		cout << "\nCode        : " << Currency.CurrencyCode();
		cout << "\nName        : " << Currency.CurrencyName();
		cout << "\nRate (1$) = : " << Currency.Rate();
		cout << "\n__________________\n";
	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\nCurrency is not Found :-(\n";
		}
	}

	static float _ReadNewCurrencyRate()
	{
		float NewRate = 0;

		cout << "\nEnter New Rate: ";
		NewRate = clsInputValidate::ReadNumber<float>();

		return NewRate;
	}

public:

	static void ShowUpdateCurrencyRateScreen()
	{
		clsScreen::_DrawScreenHeader("\tUpdate Currency Rate Screen");

		clsCurrency Currency = clsCurrency::FindByCurrencyCode(_ReadCurrencyCode());
		_ShowResults(Currency);

		char Answer = 'n';
		cout << "\nAre you sure you want to update rate of this currency? y/n? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			cout << "\nUpdate Currency Rate:";
		    cout << "\n________________________\n";

			Currency.UpdateRate(_ReadNewCurrencyRate());
			_ShowResults(Currency);
		}

	}
};