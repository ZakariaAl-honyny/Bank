#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h";

class clsUpdateUserScreen : protected clsScreen
{
private:

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
        User.Permissions = clsInputValidate::ReadNumber<int>();
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
        cout << "\nUserName   : " << User.UserName;
        cout << "\nPassword   : " << User.Password;
        cout << "\nPermissions: " << User.Permissions;
        cout << "\n_______________________\n";
    }

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

        cout << "\nShow Login Register? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::enPermissions::pLoginRegister;
        }

        return  Permissions;
    }

public:

    static void ShowUpdateUserScreen()
    {

        _DrawScreenHeader("\t   Update User Screen");

        string UserName = "";

        cout << "\nPlease Enter User Name: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser Name is not found, chooce anther one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);
        _PrintUser(User1);

        cout << "\nAre you sure you want to Update this User y/n ?: ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {

            cout << "\nUpdate User Info:";
            cout << "\n______________________\n";

            _ReadUserInfo(User1);

            clsUser::enSaveResults SaveResult;

            SaveResult = User1.Save();

            switch (SaveResult)
            {

            case clsUser::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Update successfully :-).\n";
                _PrintUser(User1);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError Account was not saved decause it's Empty.";
                break;
            }

            }

        }
    }
};

