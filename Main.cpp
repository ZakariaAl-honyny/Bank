
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;
const string ClientsFileName = "Clients.txt";

void ShowMainMenue();

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

vector<string> SplitString(string S1, string delimiter = " ")
{
	vector<string> vString;

	short Pos = 0;
	string sWord; // define a string variable

	// use find() function to get the position of the delimiter
	while ((Pos = short(S1.find(delimiter))) != std::string::npos)
	{
		sWord = S1.substr(0, Pos); // store the word
		if (sWord != "")
		{
			vString.push_back(sWord);
		}

		S1.erase(0, Pos + delimiter.length()); // erase() until position and move to next word.
	}

	if (S1 != "")
	{
		vString.push_back(S1);// it push last word of the string
	}

	return vString;

}

stClient ConvertLineToRecord(string Line, string Sperator = "#//#")
{
	stClient Client;
	vector<string> vClientData;

	vClientData = SplitString(Line, Sperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);// cast string to double

	return Client;
}

string ConvertRecordToLine(stClient Client, string Sperator = "#//#")
{
	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Sperator;
	stClientRecord += Client.PinCode + Sperator;
	stClientRecord += Client.Name + Sperator;
	stClientRecord += Client.Phone + Sperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string ClientsFileName)
{
	vector<stClient> vClients;
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::in);

	if (MyFile.is_open())
	{

		string Line;
		stClient Client;

		while (getline(MyFile, Line))
		{

			Client = ConvertLineToRecord(Line);

			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}

		MyFile.close();
	}

	return false;
}

stClient ReadNewClient()
{
	stClient Client;
	
	cout << "\nEnter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);// Using of std::ws will extract allthe whitespace character

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with  [" << Client.AccountNumber << "] already exists, Enter  another Account Number?.\n";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);

	cout << "Enter your Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance? ";
	cin >> Client.AccountBalance;

	return Client;
}

vector<stClient> LoadClientsDataFromFile(string FileName)
{
	vector<stClient> vClients;
	fstream MyFile;

	MyFile.open(FileName, ios::in); // Read Mode

	if (MyFile.is_open())
	{
		string Line;
		stClient Client;

		while (getline(MyFile, Line))
		{

			Client = ConvertLineToRecord(Line);

			vClients.push_back(Client);
		}

		MyFile.close();
	}

	return vClients;
}

void PrintClintRecordLine(stClient Client)
{

	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.Phone;
	cout << "| " << left << setw(12) << Client.AccountBalance;

}

void ShowAllClientsScreen()
{
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\tClient List (" << vClients.size() << ") Client(s).";

	cout << "\n___________________________________________________________________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "PinCode";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n___________________________________________________________________________________________________\n" << endl;

	for (stClient& Client : vClients)
	{
		PrintClintRecordLine(Client);
		cout << endl;
	}
	cout << "\n___________________________________________________________________________________________________\n" << endl;

}

void PrintClientCard(stClient Client)
{
	cout << "\nThe Folloing are the client details:\n";
	cout << "---------------------------------";
	cout << "\nAccount Number : " << Client.AccountNumber;
	cout << "\nPinCode        : " << Client.PinCode;
	cout << "\nName           : " << Client.Name;
	cout << "\nPhone          : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n---------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<stClient>& vClients, stClient& Client)
{

	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;

}

stClient ChangeClientRecord(string AccountNumber)
{
	stClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter your Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance? ";
	cin >> Client.AccountBalance;

	return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{

	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector<stClient> SaveClientsDataToFile(string FileName, vector<stClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out); // Write Mode

	string DataLine = "";

	if (MyFile.is_open())
	{


		for (stClient& Client : vClients)
		{
			if (Client.MarkForDelete == false)
			{
				//we only write records that are not marked for delete

				DataLine = ConvertRecordToLine(Client);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}

	return vClients;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;

		MyFile.close();
	}
}

void AddNewClient()
{

	stClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}

void AddNewClients()
{
	char AddMore = 'Y';

	do
	{

		cout << "Adding New Client:\n\n";

		AddNewClient();
		cout << "\nClient Added Successfully, Do you want to add more Clients ? Y / N ? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{
	stClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure do you want to delete this Client?? Y/N ? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);

			SaveClientsDataToFile(ClientsFileName, vClients);

			//Refresh Clients
			vClients = LoadClientsDataFromFile(ClientsFileName);

			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is NOT found!";
		return false;
	}
	return false;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{
	stClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure do you want to Update this Client?? Y/N ? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			for (stClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is NOT found!";
		return false;
	}
	return false;
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter Account Number? ";
	cin >> AccountNumber;
	return AccountNumber;
}

void ShowDeleteClientScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n------------------------------------------\n";

	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\tUpdate Client Screen";
	cout << "\n------------------------------------------\n";

	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowAddNewClientScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\tAdd New Client Screen";
	cout << "\n------------------------------------------\n";

	AddNewClients();
}

void ShowFindClientScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n------------------------------------------\n";

	stClient Client;
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is NOT found!";
	}
}

void ShowExitScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\tSystem Ends :-)\a";
	cout << "\n------------------------------------------\n";
}

enum enMainMenueOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eExit = 6 };

void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to main menue...";
	system("pause>0");
	ShowMainMenue();
}

short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}

void PerformMainmenueOption(enMainMenueOptions MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOptions::eListClients:

		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eAddNewClient:

		system("cls");
		ShowAddNewClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eDeleteClient:

		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eUpdateClient:

		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eFindClient:

		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eExit:

		system("cls");
		ShowExitScreen();
		break;
	}
}

void ShowMainMenue()
{
	system("cls");
	cout << "=============================================\n";
	cout << "\t\tMain  Menue  Screen\n";
	cout << "=============================================\n"A
		cout << "\t[1] Show Client List.\n";					 A
		cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Exit.\n";
	cout << "=============================================\n";
	PerformMainmenueOption((enMainMenueOptions)ReadMainMenueOption());
}

int main()
{

	ShowMainMenue();

	system("pause>0");
	return 0;
}