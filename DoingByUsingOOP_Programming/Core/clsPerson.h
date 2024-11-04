#pragma once

#include <iostream>
#include <string>
#include "InterfaseCommunication.h"
using namespace std;

class clsPerson : public InterfaseCommunication
{
private:

	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;
public:

	clsPerson(string FirstName, string LastName, string Email, string Phone)
	{
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	//Property Set
	void SetFirstName(string FirstName)
	{
		_FirstName = FirstName;
	}

	//Property Get
	string GetFirstName()
	{
		return _FirstName;
	}

	__declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;

	void SetLastName(string LastName)
	{
		_LastName = LastName;
	}

	string GetLastName()
	{
		return _LastName;
	}

	__declspec(property(get = GetLastName, put = SetLastName)) string LastName;

	void SetEmail(string Email)
	{
		_Email = Email;
	}

	string GetEmail()
	{
		return _Email;
	}

	__declspec(property(get = GetEmail, put = SetEmail)) string Email;

	void SetPhone(string Phone)
	{
		_Phone = Phone;
	}

	string GetPhone()
	{
		return _Phone;
	}

	__declspec(property(get = GetPhone, put = SetPhone)) string Phone;


	string FullName()
	{
		return _FirstName + " " + _LastName;
	}

	void SendEmail(string Title, string Body)
	{
		// This Function Came from Interfase Communication
		//you must write This Function here
	}

	void SendFax(string Title, string Body)
	{
		// This Function Came from Interfase Communication
		//you must write This Function here
	}

	void SendSMS(string Title, string Body)
	{
		// This Function Came from Interfase Communication
		//you must write This Function here
	}

	//you must write global code for all classes
	//don't write related code UI(User Interfase) Inside Object 
	/*void Print()
	{
		cout << "\nInfo:";
		cout << "\n________________";
		cout << "\nFirstName: " << _FirstName;
		cout << "\nLastName : " << _LastName;
		cout << "\nFullName : " << FullName();
		cout << "\nEmail    : " << _Email;
		cout << "\nPhone    : " << _Phone;
		cout << "\n________________\n";
	}*/
};

