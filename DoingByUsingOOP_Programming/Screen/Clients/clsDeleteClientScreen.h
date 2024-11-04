#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"


class clsDeleteClientScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n_______________________";
        cout << "\nFirstName  : " << Client.FirstName;
        cout << "\nLastName   : " << Client.LastName;
        cout << "\nFullName   : " << Client.FullName();
        cout << "\nEmail      : " << Client.Email;
        cout << "\nPhone      : " << Client.Phone;
        cout << "\nAcc. Number: " << Client.AccountNumber();
        cout << "\nPinCode    : " << Client.PinCode;
        cout << "\nBalance    : " << Client.AccountBalance;
        cout << "\n_______________________\n";
    }

public:

    static void ShowDeleteClientScreen()
    {
        if (!clsScreen::checkAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return; // this will exit the function and it will not continue
        }

        _DrawScreenHeader("\t   Delete Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, chooce anther one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient DeleteClient = clsBankClient::Find(AccountNumber);
        //DeleteClient.Print();
        _PrintClient(DeleteClient);

        cout << "\nAre you sure you want to delete this client y/n ?: ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (DeleteClient.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";
                //DeleteClient.Print();
                _PrintClient(DeleteClient);
            }
            else
            {
                cout << "\nError client was not Deleted :-(\n";
            }
        }
    }

};

