#pragma once

#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{
protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << "\t\t\t\t\t_______________________________________";
		cout << "\n\n\t\t\t\t\t" << Title;
		if (SubTitle != "")
		{
			cout << "\n\t\t\t\t\t" << SubTitle;

		}
		cout << "\n\t\t\t\t\t_______________________________________\n";

		cout << "\n\t\t\t\t\tUser: " << CurrentUser.UserName;
		cout << "\n\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << "\n\n";
	}

	static bool checkAccessRights(clsUser::enPermissions Permissions)
	{
		if (!CurrentUser.CheckAccessPermssion(Permissions))
		{
			cout << "\t\t\t\t\t_______________________________________";
			cout << "\n\n\t\t\t\t\t   Access Denied, Contact your admin!";
			cout << "\n\t\t\t\t\t_______________________________________\n\n";
			return false;
		}
		else
		{
			return true;
		}
		
	}

};

