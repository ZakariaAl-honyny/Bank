#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:
	enum enFindBy { eCurrencyCode = 1, eCountry = 2};

	static enFindBy _ReadFindBy()
	{
		short FindBy = 2;
		cout << "\nFind by : [1]:Currency Code or [2]:Country? ";
		FindBy = clsInputValidate::ReadNumberBetween<short>(1, 2, "\nInvaild Input chooce again, Find by : [1]:Currency Code or [2]:Country? ");

		return (enFindBy)FindBy;
	}

	static string _ReadCurrencyCode()
	{
		string CurrencyCode = "";
		cout << "\nPlease Enter CurrencyCode? ";
		CurrencyCode = clsInputValidate::ReadString();

		return CurrencyCode;
	}

	static string _ReadCountry()
	{
		string Country = "";
		cout << "\nPlease Enter Country? ";
		Country = clsInputValidate::ReadString();

		return Country;
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
			cout << "\nCurrency Found Successfully :-)\n";
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\nCurrency is not Found :-(\n";
		}
	}

public:

	static void ShowFindCurrencyScreen()
	{
		clsScreen::_DrawScreenHeader("\tCurrency Find Screen");

		switch (_ReadFindBy())
		{

		case enFindBy::eCurrencyCode:
		{
			clsCurrency Currency = clsCurrency::FindByCurrencyCode(_ReadCurrencyCode());
			_ShowResults(Currency);
			break;
		}

		case enFindBy::eCountry:
		{
			clsCurrency Currency = clsCurrency::FindByCountry(_ReadCountry());
			_ShowResults(Currency);
			break;
		}

		}

	}
};

