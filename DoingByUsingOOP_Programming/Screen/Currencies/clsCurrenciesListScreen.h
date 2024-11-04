#pragma once
#include <iostream>
#include <iomanip>
#include "clsCurrency.h"
#include "clsScreen.h"


class clsCurrenciesListScreen : protected clsScreen
{
private:

    static void _PrintCurrencyRecordLine(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << left << setw(30) << Currency.Country();
        cout << "| " << left << setw(15) << Currency.CurrencyCode();
        cout << "| " << left << setw(40) << Currency.CurrencyName();
        cout << "| " << left << setw(12) << Currency.Rate();
    }

public:

    static void ShowCurrenciesListScreen()
    {
        vector<clsCurrency> vCurrencys = clsCurrency::GetCurrenciesList();

        string Title = "\t  Currencies List Screen";
        string SubTitle = "\t    (" + to_string(vCurrencys.size()) + ") Currency.";

        clsScreen::_DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "______________________________________________";
        cout << "__________________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Coutry";
        cout << "| " << left << setw(15) << "Currency Code";
        cout << "| " << left << setw(40) << "Currency Name";
        cout << "| " << left << setw(12) << "Rate/(1$) = \n";

        cout << setw(8) << left << "" << "______________________________________________";
        cout << "__________________________________________________________\n" << endl;

        if (vCurrencys.size() == 0)
            cout << "\t\t\t\tno Currencies Available In the System :-(";
        else
        {

            for (clsCurrency& Currency : vCurrencys)
            {
                _PrintCurrencyRecordLine(Currency);
                cout << endl;
            }

        }

        cout << setw(8) << left << "" << "______________________________________________";
        cout << "__________________________________________________________\n" << endl;
    }
};