#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewUserScreen : protected clsScreen
{
private:

    static int _ReadPermissionsToSet()
    {
        int Permissions = 0;
        char Answer = 'n';

        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            return clsUser::enPermissions::pAll;
        }
        
        cout << "\nDo you want to give access to:\n"; 
           
        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nShow Add New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nShow Delete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nShow Update Client? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nShow Find Client? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nShow Transactios? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::enPermissions::pTransactions;
        }

        cout << "\nShow Manage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        return  Permissions;
    }

    static void _ReadUserInfo(clsUser& User)
    {

        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permissions: ";
        User.Permissions = (int)_ReadPermissionsToSet();
    }

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n_______________________";
        cout << "\nFirstName  : " << User.FirstName;
        cout << "\nLastName   : " << User.LastName;
        cout << "\nFullName   : " << User.FullName();
        cout << "\nEmail      : " << User.Email;
        cout << "\nPhone      : " << User.Phone;
        cout << "\nUsername   : " << User.UserName;
        cout << "\nPassword   : " << User.Password;
        cout << "\nPermissions: " << User.Permissions;
        cout << "\n_______________________\n";
    }

public:

    static void ShowAddNewUserScreen()
    {

        _DrawScreenHeader("\t   Add New User Screen");

        string UserName = "";

        cout << "\nPlease Enter User Name: ";
        UserName = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(UserName))
        {
            cout << "\nUser Name is already used, Enter anther one: ";
            UserName = clsInputValidate::ReadString();
        }

        cout << "\nAdd New User:";
        cout << "\n_____________________\n";

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;

        SaveResult = NewUser.Save();

        switch (SaveResult)
        {

        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty :-(.\n";
            break;
        }

        case clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Added successfully :-).\n";
            _PrintUser(NewUser);
            break;
        }

        case clsUser::enSaveResults::svFaildAccountNumberExists:
        {
            cout << "\nError User was not saved because User Name is used!\n";
            break;
        }

        }

    }

};

