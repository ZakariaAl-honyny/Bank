#pragma once
#include <iostream>
#include <string>
using namespace std;

class InterfaseCommunication
{
public:

	virtual void SendEmail(string Title, string Body) = 0;
	virtual void SendFax(string Title, string Body) = 0;
	virtual void SendSMS(string Title, string Body) = 0;
};

