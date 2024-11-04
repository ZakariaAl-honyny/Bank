#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewClientScreen : protected clsScreen
{
private:

    static void _ReadClientInfo(clsBankClient& Client)
    {

        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadNumber<float>();
    }

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

    static void ShowAddNewClientScreen()
    {
        if (!clsScreen::checkAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return; // this will exit the function and it will not continue
        }

        _DrawScreenHeader("\t   Add New Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is already used, Enter anther one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        cout << "\nAdd New Client:";
        cout << "\n_____________________\n";

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {

        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError Account was not saved because it's Empty :-(.\n";
            break;
        }

        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAcount Added successfully :-).\n";
            _PrintClient(NewClient);
            break;
        }

        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
        {
            cout << "\nError Acount was not saved because account number is used!\n";
            break;
        }

        }

    }

};

