
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;


enum enMainMenueOptions {
	eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
	eUpdateClients = 4, eFindClient = 5, eTransactios = 6, eMangeUsers = 7, eLogout = 8
};
enum enTransactionsMenueOptions {
	eDeposit = 1, eWithDraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4
};
enum enMangeUsersOptions {
	eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
	eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
};
enum enMainMenuePermissions {
	pAll = -1, pListClients = 1, pAddNewClient = 2,
	pDeleteClient = 4, pUpdateClients = 8, pFindClient = 16,
	pTransactios = 32, pMangeUsers = 64
};

struct stClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool MarkForDelete = false;
};
struct stUser
{
	string Name = "";
	string Password = "";
	short Permissions = 0;
	bool MarkForDelete = false;
};

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

stUser CurrentUser;

void GoBackToMainMenue();
void ShowMainMenue();
void ShowTransactionsMenue();
void ShowMangeUsersMenue();
bool CheckAccessPermission(enMainMenuePermissions);
void Login();

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

stClient ConvertClintLineToRecord(string Line, string Sperator = "#//#")
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
stUser ConvertUserLineToRecord(string Line, string Sperator = "#//#")
{
	stUser User;
	vector<string> vUserData;

	vUserData = SplitString(Line, Sperator);

	User.Name = vUserData[0];
	User.Password = vUserData[1];
	User.Permissions = stoi(vUserData[2]);

	return User;
}
string ConvertClientRecordToLine(stClient Client, string Sperator = "#//#")
{
	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Sperator;
	stClientRecord += Client.PinCode + Sperator;
	stClientRecord += Client.Name + Sperator;
	stClientRecord += Client.Phone + Sperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}
string ConvertUserRecordToLine(stUser User, string Sperator = "#//#")
{
	string stUserLine = "";

	stUserLine += User.Name + Sperator;
	stUserLine += User.Password + Sperator;
	stUserLine += to_string(User.Permissions);

	return stUserLine;
}

bool IsClientExistsByAccountNumber(string AccountNumber, string ClientsFileName)
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

			Client = ConvertClintLineToRecord(Line);

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
bool IsUserExistsByUserName(string UserName, string UsersFileName)
{

	fstream MyFile;
	MyFile.open(UsersFileName, ios::in);

	if (MyFile.is_open())
	{

		string Line;
		stUser User;

		while (getline(MyFile, Line))
		{
			if (Line == "")
				break;
			User = ConvertUserLineToRecord(Line);

			if (User.Name == UserName)
			{
				MyFile.close();
				return true;
			}

		}

		MyFile.close();
	}

	return false;
}

stClient ReadNewClient()
{
	stClient Client;
	// Using of std::ws will extract allthe whitespace character
	cout << "\nEnter Account Number? ";
	getline(cin >> ws, Client.AccountNumber); // ignor for any width spases in bafer

	while (IsClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
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

short ReadPermissionsToSet()
{
	short Permissions = 0;
	char Answer = 'n';

	cout << "\n\nDo you want to give Full access? Y/N? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		return enMainMenuePermissions::pAll;
	}

	cout << "\nDo you want to give access to :\n";
	cout << "\nShow Client List? y/n? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermissions::pListClients;
	}

	cout << "\nAdd New Client? y/n? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermissions::pAddNewClient;
	}

	cout << "\nDelete Client? y/n? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermissions::pDeleteClient;
	}

	cout << "\nUpdate Client? y/n? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermissions::pUpdateClients;
	}

	cout << "\nFind Client? y/n? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermissions::pFindClient;
	}

	cout << "\nTransactions? y/n? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermissions::pTransactios;
	}

	cout << "\nMange Users? y/n? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermissions::pMangeUsers;
	}

	return Permissions;
}

stUser ReadNewUser()
{
	stUser User;
	// Using of std::ws will extract allthe whitespace character
	cout << "\nEnter User Name? ";
	getline(cin >> ws, User.Name);

	while (IsUserExistsByUserName(User.Name, UsersFileName))
	{
		cout << "\nUser with  [" << User.Name << "] already exists, Enter  another user name?.";
		getline(cin >> ws, User.Name);
	}

	cout << "\nEnter Password? ";
	getline(cin, User.Password);

	User.Permissions = ReadPermissionsToSet();

	return User;
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

			Client = ConvertClintLineToRecord(Line);

			vClients.push_back(Client);
		}

		MyFile.close();
	}

	return vClients;
}
vector<stUser> LoadUsersDataFromFile(string FileName)
{
	vector<stUser> vUsers;

	fstream MyFile;
	MyFile.open(FileName, ios::in); //read Mode

	if (MyFile.is_open())
	{
		string Line;
		stUser User;

		while (getline(MyFile, Line))
		{
			if (Line == "")
				break;

			User = ConvertUserLineToRecord(Line);

			vUsers.push_back(User);

		}

		MyFile.close();
	}

	return vUsers;
}

void PrintClintRecordLine(stClient Client)
{

	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}
void PrintClintRecordBalanceLine(stClient Client)
{

	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}
void PrintUserRecordLine(stUser User)
{

	cout << "| " << setw(40) << left << User.Name;
	cout << "| " << setw(10) << left << User.Password;
	cout << "| " << setw(15) << left << User.Permissions;

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
void PrintUserCard(stUser User)
{
	cout << "\nThe Folloing are the User details:\n";
	cout << "---------------------------------";
	cout << "\nName           : " << User.Name;
	cout << "\nPassword       : " << User.Password;
	cout << "\nPermissions    : " << User.Permissions;
	cout << "\n---------------------------------\n";
}
void ShowAccessDeniedMessage()
{
	system("cls");
	cout << "\n_________________________________\n";
	cout << "Access Denie, \n You don't have Permission to do this, \nPlease Conact your admin.";
	cout << "\n_________________________________\n";
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
bool FindUserByUserNameAnaPassword(string UserName, string Password, stUser& User)
{
	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

	for (stUser& U : vUsers)
	{
		if (U.Name == UserName && U.Password == Password)
		{
			User = U;
			return true;
		}
	}
	return false;

}
bool FindUserByUserName(string UserName, vector<stUser>& vUsers, stUser& User)
{
	for (stUser& U : vUsers)
	{
		if (U.Name == UserName)
		{
			User = U;
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
stUser ChangeUserRecord(string UserName)
{
	stUser User;

	User.Name = UserName;

	cout << "\nEnter Password? ";
	getline(cin >> ws, User.Password);

	User.Permissions = ReadPermissionsToSet();

	return User;
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
bool MarkUserForDeleteByUserName(string UserName, vector<stUser>& vUsers)
{
	for (stUser& U : vUsers)
	{
		if (U.Name == UserName)
		{
			U.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector<stClient> SaveClientsDataToFile(string FileName, vector<stClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out); // overWrite

	string DataLine = "";

	if (MyFile.is_open())
	{


		for (stClient& Client : vClients)
		{
			if (Client.MarkForDelete == false)
			{
				//we only write records that are not marked for delete

				DataLine = ConvertClientRecordToLine(Client);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}

	return vClients;
}
vector<stUser> SaveUsersDataToFile(string FileName, vector<stUser>& vUsers)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out); // overWrite

	string DataLine = "";

	if (MyFile.is_open())
	{

		for (stUser& User : vUsers)
		{
			if (User.MarkForDelete == false)
			{
				//we only write records that are not marked for delete

				DataLine = ConvertUserRecordToLine(User);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}

	return vUsers;
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
	AddDataLineToFile(ClientsFileName, ConvertClientRecordToLine(Client));

}
void AddNewUser()
{
	stUser User;
	User = ReadNewUser();
	AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(User));
}

void AddNewClients()
{
	char AddMore = 'Y';

	do
	{
		//system("pause>0");
		cout << "Adding New Client:\n\n";

		AddNewClient();
		cout << "\nClient Added Successfully, Do you want to add more Clients ? Y / N ? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');
}
void AddNewUsers()
{
	char AddMore = 'Y';

	do
	{
		//system("pause>0");
		cout << "Adding New User:\n";

		AddNewUser();
		cout << "\nUser Added Successfully, Do you want to add more Users ? Y / N ? ";
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
bool DeleteUserByUserName(string UserName, vector<stUser>& vUsers)
{

	if (UserName == "Admin")
	{
		cout << "\nYou cann't Delete this User!.\n";
		return false;
	}

	stUser User;
	char Answer = 'n';

	if (FindUserByUserName(UserName, vUsers, User))
	{
		PrintUserCard(User);

		cout << "\n\nAre you sure do you want to delete this User?? Y/N ? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			MarkUserForDeleteByUserName(UserName, vUsers);

			SaveUsersDataToFile(UsersFileName, vUsers);

			//Refresh Users
			vUsers = LoadUsersDataFromFile(UsersFileName);

			cout << "\n\nUser Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nUser with UserName (" << UserName << ") is NOT found!";
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
bool UpdateUserByUserName(string UserName, vector<stUser>& vUsers)
{
	stUser User;
	char Answer = 'n';

	if (FindUserByUserName(UserName, vUsers, User))
	{
		PrintUserCard(User);

		cout << "\n\nAre you sure do you want to Update this User?? Y/N ? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			for (stUser& U : vUsers)
			{
				if (U.Name == UserName)
				{
					U = ChangeUserRecord(UserName);
					break;
				}
			}

			SaveUsersDataToFile(UsersFileName, vUsers);

			cout << "\n\nUser Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nUser with UserName (" << UserName << ") is NOT found!";
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
string ReadUserName()
{
	string UserName = "";

	cout << "\nPlease Enter UserName? ";
	cin >> UserName;
	return UserName;
}

void ShowAllClientsScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pListClients))
	{
		ShowAccessDeniedMessage();
		return;
	}

	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\tClient List (" << vClients.size() << ") Client(s).";

	cout << "\n___________________________________________________________________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "PinCode";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n___________________________________________________________________________________________________\n" << endl;

	if (vClients.size() == 0)
		cout << "\t\t\tNo Clients availble in the screen!";
	else

	for (stClient& Client : vClients)
	{
		PrintClintRecordBalanceLine(Client);
		cout << endl;
	}
	cout << "\n___________________________________________________________________________________________________\n" << endl;

}
void ShowAllUsersScreen()
{
	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

	cout << "\n\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";

	cout << "\n___________________________________________________________________________________________________\n" << endl;
	cout << "| " << left << setw(40) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(15) << "Permissions";
	cout << "\n___________________________________________________________________________________________________\n" << endl;

	if (vUsers.size() == 0)
		cout << "\t\t\tNo Users availble in the screen!";
	else

	for (stUser& User : vUsers)
	{
		PrintUserRecordLine(User);
		cout << endl;
	}
	cout << "\n___________________________________________________________________________________________________\n" << endl;

}
void ShiwListUsersScreen()
{
	ShowAllUsersScreen();
}
void ShowTotalBalances()
{
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\tClient List (" << vClients.size() << ") Client(s).";

	cout << "\n___________________________________________________________________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n___________________________________________________________________________________________________\n" << endl;

	double TotalBalances = 0;
	if (vClients.size() == 0)
		cout << "\t\t\tNo Clients availble in the screen!";
	else

	for (stClient& Client : vClients)
	{
		PrintClintRecordBalanceLine(Client);
		TotalBalances += Client.AccountBalance;

		cout << endl;
	}
	cout << "\n___________________________________________________________________________________________________\n" << endl;

	cout << "\t\t\t\t\t\tTotal balances = " << TotalBalances;
}
void ShowAddNewClientScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pAddNewClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n------------------------------------------\n";
	cout << "\tAdd New Client Screen";
	cout << "\n------------------------------------------\n";

	AddNewClients();
}
void ShowAddNewUserScreen()
{

	cout << "\n------------------------------------------\n";
	cout << "\tAdd New User Screen";
	cout << "\n------------------------------------------\n";

	AddNewUsers();
}
void ShowDeleteClientScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n------------------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n------------------------------------------\n";

	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}
void ShowDeleteUserScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\tDelete User Screen";
	cout << "\n------------------------------------------\n";

	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();
	DeleteUserByUserName(UserName, vUsers);
}
void ShowUpdateClientScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClients))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n------------------------------------------\n";
	cout << "\tUpdate Client Screen";
	cout << "\n------------------------------------------\n";

	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}
void ShowUpdateUserScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\tUpdate User Screen";
	cout << "\n------------------------------------------\n";

	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();
	UpdateUserByUserName(UserName, vUsers);
}
void ShowFindClientScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pFindClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

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
void ShowFindUserScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\tFind User Screen";
	cout << "\n------------------------------------------\n";

	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	stUser User;
	string UserName = ReadUserName();

	if (FindUserByUserName(UserName, vUsers, User))
	{
		PrintUserCard(User);
	}
	else
	{
		cout << "\nUser with UserName [" << User.Name << "] is NOT found!";
	}
}

double ReadAmount()
{
	double Amount = 0;
	cout << "\nPlease enter amount? ";
	cin >> Amount;

	while (Amount <= 0)
	{
		cout << "\n\nYou Cann't enter amount is zero or negative, enter another one? ";
		cin >> Amount;

	}
	return Amount;
}
double ReadWithdrawAmount(double AccountBalance)
{
	cout << "\nPlease enter withdraw amount? ";
	double WithdrawAmount = 0;
	cin >> WithdrawAmount;

	while (WithdrawAmount <= 0)
	{
		cout << "\nYou can't Withdraw amount is zero or negative, enter another one? ";
		cin >> WithdrawAmount;

	}

	while (WithdrawAmount > AccountBalance)
	{
		cout << "\n\nAmount Exceeds the balance, you can withdraw up to : " << AccountBalance;
		cout << "\n\nPlease enter another amount? ";
		cin >> WithdrawAmount;

	}
	return WithdrawAmount;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<stClient>& vClients)
{

	char Answer = 'n';


	cout << "\n\nAre you sure you want perform this transaction?? Y/N ? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{

		for (stClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveClientsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully, your new balance is: " << C.AccountBalance << endl;

				return true;
			}
		}

		return false;
	}
	return false;
}

void ShowTotalBalacesScreen()
{

	ShowTotalBalances();

}

void ShowDepositScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\t\tDeposit Screen";
	cout << "\n------------------------------------------\n";

	stClient Client;
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with (" << AccountNumber << ") does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);


	double DepositAmount = ReadAmount();

	DepositBalanceToClientByAccountNumber(AccountNumber, DepositAmount, vClients);
}

void ShowWithdrawScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\t\tWith Draw Screen";
	cout << "\n------------------------------------------\n";

	stClient Client;
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with (" << AccountNumber << ") does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double WithdrawAmount = ReadAmount();

	// Valaidate that the amount does not exceeds the Balance
	while (WithdrawAmount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can Withdraw up to : " << Client.AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> WithdrawAmount;
	}

	DepositBalanceToClientByAccountNumber(AccountNumber, (WithdrawAmount * -1), vClients);
}

bool CheckAccessPermission(enMainMenuePermissions Permission)
{
	if (CurrentUser.Permissions == enMainMenuePermissions::pAll)
		return true;

	if ((Permission & CurrentUser.Permissions) == Permission)
		return true;
	else
		return false;
}

void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to main menue...";
	system("pause>0");
	ShowMainMenue();
}
void GoBackToTransactionsMenue()
{
	cout << "\n\nPress any key to go back to Transactions menue...";
	system("pause>0");
	ShowTransactionsMenue();
}
void GoBackToMangeUsersMenue()
{
	cout << "\n\nPress any key to go back to Mange Users menue...";
	system("pause>0");
	ShowMangeUsersMenue();
}

short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 8]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}
short ReadTransactionsMenueOption()
{
	cout << "Choose what do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}



void PerformTransactionsMenueOption(enTransactionsMenueOptions TransactiosMenueOption)
{
	switch (TransactiosMenueOption)
	{
	case enTransactionsMenueOptions::eDeposit:
	{
												 system("cls");
												 ShowDepositScreen();
												 GoBackToTransactionsMenue();
												 break;
	}

	case enTransactionsMenueOptions::eWithDraw:
	{
												  system("cls");
												  ShowWithdrawScreen();
												  GoBackToTransactionsMenue();
												  break;
	}

	case enTransactionsMenueOptions::eShowTotalBalance:
	{
														  system("cls");
														  ShowTotalBalacesScreen();
														  GoBackToTransactionsMenue();
														  break;
	}

	case enTransactionsMenueOptions::eShowMainMenue:
	{
													   ShowMainMenue();
													   break;
	}

	default:
	{
			   GoBackToTransactionsMenue();
			   break;
	}

	}
}

void ShowTransactionsMenue()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pTransactios))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
		return;
	}

	system("cls");
	cout << "=============================================\n";
	cout << "\tTransactions  Menue  Screen\n";
	cout << "=============================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] With draw.\n";
	cout << "\t[3] Total balance.\n";
	cout << "\t[4] Main menue.\n";
	cout << "=============================================\n";
	PerformTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

void PerformMangeUsersMenueOption(enMangeUsersOptions MangeUsersMenueOption)
{
	switch (MangeUsersMenueOption)
	{
	case enMangeUsersOptions::eListUsers:
	{
											system("cls");
											ShiwListUsersScreen();
											GoBackToMangeUsersMenue();
											break;
	}

	case enMangeUsersOptions::eAddNewUser:
	{
											 system("cls");
											 ShowAddNewUserScreen();
											 GoBackToMangeUsersMenue();
											 break;
	}

	case enMangeUsersOptions::eDeleteUser:
	{
											 system("cls");
											 ShowDeleteUserScreen();
											 GoBackToMangeUsersMenue();
											 break;
	}

	case enMangeUsersOptions::eUpdateUser:
	{
											 system("cls");
											 ShowUpdateUserScreen();
											 GoBackToMangeUsersMenue();
											 break;
	}

	case enMangeUsersOptions::eFindUser:
	{
										   system("cls");
										   ShowFindUserScreen();
										   GoBackToMangeUsersMenue();
										   break;
	}

	case enMangeUsersOptions::eMainMenue:
	{
											ShowMainMenue();
											break;
	}

	default:
	{
			   GoBackToMangeUsersMenue();
			   break;
	}

	}
}

short ReadMangeUsersMenueOption()
{
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}

void ShowMangeUsersMenue()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pMangeUsers))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
		return;
	}

	system("cls");
	cout << "=============================================\n";
	cout << "\tMange Users  Menue  Screen\n";
	cout << "=============================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "=============================================\n";
	PerformMangeUsersMenueOption((enMangeUsersOptions)ReadMangeUsersMenueOption());
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

	case enMainMenueOptions::eUpdateClients:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eTransactios:
		system("cls");
		ShowTransactionsMenue();
		break;

	case enMainMenueOptions::eMangeUsers:
		system("cls");
		ShowMangeUsersMenue();
		break;

	case enMainMenueOptions::eLogout:
		system("cls");
		Login();
		break;

	default:
	{
			   GoBackToMainMenue();
			   break;
	}

	}
}

void ShowMainMenue()
{
	system("cls");
	cout << "=============================================\n";
	cout << "\t\tMain  Menue  Screen\n";
	cout << "=============================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Mange Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "=============================================\n";
	PerformMainmenueOption((enMainMenueOptions)ReadMainMenueOption());
}

bool LoadUserInfo(string UserName, string Passwrod)
{

	if (FindUserByUserNameAnaPassword(UserName, Passwrod, CurrentUser))
		return true;
	else
		return false;

}

void Login()
{
	bool UserFailed = false;

	string UserName, Password;
	do
	{
		system("cls");
		cout << "\n=============================================\n";
		cout << "\tLog in Screen";
		cout << "\n=============================================\n";


		if (UserFailed)
		{
			cout << "Invalid UserName/Password!\n";
		}

		cout << "Enter UserName? ";
		cin >> UserName;

		cout << "Enter PassWord? ";
		cin >> Password;

		UserFailed = !LoadUserInfo(UserName, Password);

	} while (UserFailed);

	ShowMainMenue();

}

int main()
{

	Login();

	system("pause>0");
	return 0;
}
