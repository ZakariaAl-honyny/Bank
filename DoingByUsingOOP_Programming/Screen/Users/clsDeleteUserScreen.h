#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"


class clsDeleteUserScreen : protected clsScreen
{
private:
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

public:

    static void ShowDeleteUserScreen()
    {

        _DrawScreenHeader("\t   Delete User Screen");

        string UserName = "";

        cout << "\nPlease Enter User Name: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser Name is not found, chooce anther one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser DeleteUser = clsUser::Find(UserName);
        _PrintUser(DeleteUser);

        cout << "\nAre you sure you want to delete this User y/n ?: ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (DeleteUser.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(DeleteUser);
            }
            else
            {
                cout << "\nError User was not Deleted :-(\n";
            }
        }
    }

};