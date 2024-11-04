#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsUitil.h";

class clsTotalBalancesScreen : protected clsScreen
{
private:

    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << setw(25) << left << "" << "|" << left << setw(15) << Client.AccountNumber();
        cout << "|" << left << setw(40) << Client.FullName();
        cout << "|" << left << setw(12) << Client.AccountBalance;
    }

public:

    static void ShowTotalBalances()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t   Total Balances Screen";
        string SubTitle = "\t\t(" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader(Title, SubTitle);

        cout << setw(25) << left << "" << "\n\t\t____________________________________________________________________________\n" << endl;
        cout << setw(25) << left << "" << "|" << left << setw(15) << "Account Number";
        cout << "|" << left << setw(40) << "Client Name";
        cout << "|" << left << setw(12) << "Balance\n";
        cout << setw(25) << left << "" << "\n\t\t____________________________________________________________________________\n" << endl;

        double TotalBalances = clsBankClient::GetTotalBalances();

        if (vClients.size() == 0)
            cout << "\t\t\t\tno Clients Available In the System :-(";
        else
        {

            for (clsBankClient& Client : vClients)
            {
                _PrintClientRecordBalanceLine(Client);
                cout << endl;
            }

        }
        cout << setw(25) << left << "" << "\n\t\t____________________________________________________________________________\n" << endl;
        cout << setw(8) << left << "" << "\t\t\t\t\t\t\tTotal Balances = " << TotalBalances << endl;
        cout << setw(8) << left << "" << "\t\t\t\t(" << clsUitil::NumberToText(TotalBalances) << ")" << endl;

    }

};

