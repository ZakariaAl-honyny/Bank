#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"


class clsTransferBalanceScreen : protected clsScreen
{
private:

	static void _PerintShortClintCard(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n____________________\n";
		cout << "\nFull Name    : " << Client.FullName();
		cout << "\nAcc. Number  : " << Client.AccountNumber();
		cout << "\nBalance      : " << Client.AccountBalance;
		cout << "\n____________________\n";
	}

	static string _ReadAccountNumber(string Message = "\nPlease Enter Account Number to transfer: ")
	{
		string AccountNumber = "";
		cout << Message;
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{

			cout << "\nAccount Number is not found, chooce Another one? ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static float _ReadAmount(clsBankClient SourceClient)
	{
		float Amount = 0;

		cout << "\nEnter Transfer Amount? ";
		Amount = clsInputValidate::ReadNumber<float>();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the available balance, Enter Another Amount? ";
			Amount = clsInputValidate::ReadNumber<float>();
		}
		return Amount;
	}

public:

	static void ShowTransferBalanceScreen()
	{
		clsScreen::_DrawScreenHeader("\tTransfer Balance Screen");
		
		string SourceAccountNumber = _ReadAccountNumber("\nPlease Enter Account Number to transfer from: ");
		clsBankClient SourceClient = clsBankClient::Find(SourceAccountNumber);
		_PerintShortClintCard(SourceClient);

		string DestinationAccountNumber = _ReadAccountNumber("\nPlease Enter Account Number to transfer to: ");
		while (SourceAccountNumber == DestinationAccountNumber)
		{
			DestinationAccountNumber = _ReadAccountNumber("\nInvaild you Can not Transfer Balance to the same Account Number, Enter Another One? ");
		}
		clsBankClient DestinationClient = clsBankClient::Find(DestinationAccountNumber);
		_PerintShortClintCard(DestinationClient);
		
		float Amount = _ReadAmount(SourceClient);


		cout << "\nAre you sure, you want to perform this operation? y/n? ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			if (SourceClient.TransferBalance(Amount, DestinationClient))
			{
				cout << "\nTransfer done successfully :-).\n";

			}
			else
			{
				cout << "\nTransfer Faild :-(\n";
			}

			_PerintShortClintCard(SourceClient);
			_PerintShortClintCard(DestinationClient);

		}
	}
};

