#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h";
#include "clsUser.h";
#include <iomanip>
#include "clsUitil.h"

using namespace std;

class clsListUserScreen : protected clsScreen
{
private:

    static void _PrintUserRecordLine(clsUser User)
    {
        cout << setw(8) << left << "" << "|" << left << setw(15) << User.UserName;
        cout << "|" << left << setw(25) << User.FullName();
        cout << "|" << left << setw(12) << User.Phone;
        cout << "|" << left << setw(20) << User.Email;
        cout << "|" << left << setw(10) << User.Password;
        cout << "|" << left << setw(12) << User.Permissions;

    }

public:

    static void ShowUsersList()
    {
        vector<clsUser> Users = clsUser::GetUsersList();

        string Title = "\t   User List Screen";
        string SubTitle = "\t    (" + to_string(Users.size()) + ") User(s).";

        clsScreen::_DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________";
        cout << "______________________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "|" << left << setw(15) << "Account Number";
        cout << "|" << left << setw(25) << "Full Name";
        cout << "|" << left << setw(12) << "Phone";
        cout << "|" << left << setw(20) << "Email";
        cout << "|" << left << setw(10) << "Password";
        cout << "|" << left << setw(12) << "Permissions";

        cout << setw(8) << left << "" << "\n\t_______________________________________";
        cout << "______________________________________________________________\n" << endl;

        if (Users.size() == 0)
            cout << "\t\t\t\tno Users Available In the System :-(";
        else
        {

            for (clsUser& User : Users)
            {
                _PrintUserRecordLine(User);
                cout << endl;
            }

        }

        cout << setw(8) << left << "" << "\n\t_______________________________________";
        cout <<"______________________________________________________________\n" << endl;

    }
};

