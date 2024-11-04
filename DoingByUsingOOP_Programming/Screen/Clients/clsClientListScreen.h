#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>

using namespace std;


class clsClientListScreen : protected clsScreen
{
private:

    static void _PrintClientRecordLine(clsBankClient Client)
    {
        cout << setw(8) << left << "" << "|" << left << setw(15) << Client.AccountNumber();
        cout << "|" << left << setw(20) << Client.FullName();
        cout << "|" << left << setw(12) << Client.Phone;
        cout << "|" << left << setw(20) << Client.Email;
        cout << "|" << left << setw(10) << Client.PinCode;
        cout << "|" << left << setw(12) << Client.AccountBalance;

    }

public:

    static void ShowClientsList()
    {

        if (!clsScreen::checkAccessRights(clsUser::enPermissions::pListClients))
        {
            return; // this will exit the function and it will not continue
        }

        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t   Client List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        clsScreen::_DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________\n" << endl;
        cout << setw(8) << left << "" << "|" << left << setw(15) << "Account Number";
        cout << "|" << left << setw(20) << "Full Name";
        cout << "|" << left << setw(12) << "Phone";
        cout << "|" << left << setw(20) << "Email";
        cout << "|" << left << setw(10) << "Pin Code";
        cout << "|" << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________\n" << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tno Clients Available In the System :-(";
        else
        {

            for (clsBankClient& Client : vClients)
            {
                _PrintClientRecordLine(Client);
                cout << endl;
            }

        }
        cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________\n" << endl;

    }

};

