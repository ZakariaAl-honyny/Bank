#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include <vector>
#include <iomanip>


class clsShowTransferBalanceLogScreen : protected clsScreen
{
private:

	static void _PrintTransferBalanceLogRecordLine(clsBankClient::stTransferBalaceLogRecord TransferBalaceLog)
	{
		cout << setw(8) << left << "" << "| " << setw(23) << TransferBalaceLog.DateTime;
		cout << "| " << setw(10) << TransferBalaceLog.SourceAccountNumber;
		cout << "| " << setw(10) << TransferBalaceLog.DestinationAccountNumber;
		cout << "| " << setw(10) << TransferBalaceLog.TransferAmount;
		cout << "| " << setw(15) << TransferBalaceLog.SourceBalanceAfterTransfered;
		cout << "| " << setw(15) << TransferBalaceLog.DestinationBalanceAfterTransfered;
		cout << "| " << setw(15) << TransferBalaceLog.UserName;
	}

public:

	static void ShowTransferBalanceLogScreen()
	{
		vector <clsBankClient::stTransferBalaceLogRecord> vTransferBalaceLogRecord = clsBankClient::GetTrnsferBalancesLogList();
		
		string Title = "\tShow Transfer Balance Screen";
		string SubTitle = "\t   (" + to_string(vTransferBalaceLogRecord.size()) + ") Record(s)";

		clsScreen::_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "________________________________________________";
		cout << "________________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << setw(23) << "Date/Time";
		cout << "| " << setw(10) << "Sou.Acct";
		cout << "| " << setw(10) << "Des.Acct";
		cout << "| " << setw(10) << "Amount";
		cout << "| " << setw(15) << "Sou.Balance";
		cout << "| " << setw(15) << "Des.Balance";
		cout << "| " << setw(15) << "User";
		cout << setw(8) << left << "" << "\n\t_________________________________________________";
		cout << "_______________________________________________________\n" << endl;

		if (vTransferBalaceLogRecord.size() == 0)
			cout << "\n\t\t\t\t\tno Record available in the system :-(.";
		else
		{
			for (clsBankClient::stTransferBalaceLogRecord Record : vTransferBalaceLogRecord)
			{
				_PrintTransferBalanceLogRecordLine(Record);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t_________________________________________________";
		cout << "_______________________________________________________\n" << endl;
	}
};