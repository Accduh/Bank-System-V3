
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
enum enTransactionsMenueOption {
	Deposit = 1,
	Withdraw = 2,
	TotalBalances = 3,
	MainMenue = 4
};
enum enMangeUsersMenueOption {
	ListUsers =1,
	AddNewUser=2,
	DeleteUser=3,
	UpdateUser=4,
	FindUser=5,
	eMainMenue=6
};
enum enMainMenueOptions
{
	eListClients = 1,
	eAddNewClient = 2,
	eDeleteClient = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	Transactions = 6,
	MangeUsers=7,
	Logout = 8
};
enum enMainMenuePermissions {
	eAll = -1,
	pListClients = 1,
	pAddNewClient = 2,
	pDeleteClient = 4,
	pUpdateClient = 8,
	pFindClient = 16,
	pTransactions = 32,
	pMangeUsers = 64
};
void ShowMainMenue();
void ShowTransactionsMenue();
void ShowMangeUsersMenue(); 
bool CheckAccessPermission(enMainMenuePermissions Permission);
void Login();
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};
struct stUser
{
	string UserName;
	string Password;
	int Permissions;
	bool MarkForDelete = false;
};
stUser CurrentUser;

void printClientRecord(sClient Client) {
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.Phone;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}
void printUsersRecord(stUser User) {
	cout << "| " << left << setw(15) << User.UserName;
	cout << "| " << left << setw(10) << User.Password;
	cout << "| " << left << setw(40) << User.Permissions;
}
void PrintAllClientsData(vector <sClient> vClients) {
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n___________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n___________________________________________________________________________________________________\n\n";
	for (sClient Client : vClients) {
		printClientRecord(Client);
		cout << endl;
	}
	cout << "\n___________________________________________________________________________________________________\n";
}
void PrintAllUsersData(vector <stUser> vUser) {
	cout << "\n\t\t\t\t\tUser List (" << vUser.size() << ") User(s).";
	cout << "\n___________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permissions";
	cout << "\n___________________________________________________________________________________________________\n\n";
	for (stUser User : vUser) {
		printUsersRecord(User);
		cout << endl;
	}
	cout << "\n___________________________________________________________________________________________________\n";
}

vector<string> SplitString(string S1, string delim) {
	vector<string> vString;
	short pos = 0;
	string sWord;
	while ((pos = S1.find(delim)) != string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}
sClient convertLineToRecord(string line, string Seperator = "#//#") {
	vector<string>ClientData = SplitString(line, Seperator);
	sClient Client;
	Client.AccountNumber = ClientData[0];
	Client.PinCode = ClientData[1];
	Client.Name = ClientData[2];
	Client.Phone = ClientData[3];
	Client.AccountBalance = stod(ClientData[4]);
	return Client;
}
stUser ConvertUserLinetoRecord(string line, string Seperator = "#//#") {
	vector<string>UserData = SplitString(line, Seperator);
	stUser User;
	User.UserName = UserData[0];
	User.Password = UserData[1];
	User.Permissions = stoi(UserData[2]);
	return User;
}
vector<sClient>LoadCleintsDataFromFile(string FileName) {
	vector <sClient> vClients;
	fstream ClientFile;
	ClientFile.open(FileName, ios::in);
	string line;
	sClient Client;
	if (ClientFile.is_open()) {
		while (getline(ClientFile, line)) {
			Client = convertLineToRecord(line);
			vClients.push_back(Client);

		}
		ClientFile.close();
	}
	return vClients;
}
vector <stUser> LoadUsersDataFromFile(string FileName){
	vector <stUser> vUsers;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		stUser User;
		while (getline(MyFile, Line))
		{
			User = ConvertUserLinetoRecord(Line);
			vUsers.push_back(User);
		}
		MyFile.close();
	}
	return vUsers;
}
void printDataClient(sClient Client) {
	cout << "\nThe following are the client details:\n";
	cout << "\n------------------------------------";
	cout << "\nAccount Number  = " << Client.AccountNumber;
	cout << "\nPin Code        = " << Client.PinCode;
	cout << "\nName            = " << Client.Name;
	cout << "\nPhone           = " << Client.Phone;
	cout << fixed << "\nAccount Balance = " << Client.AccountBalance;
	cout << "\n------------------------------------\n";
}
void printDataUser(stUser User) {
	cout << "\nThe following are the client details:\n";
	cout << "\n------------------------------------";
	cout << "\nUser Name    = " << User.UserName;
	cout << "\nPassword     = " << User.Password;
	cout << "\nPermissions  = " << User.Permissions;
	cout << "\n------------------------------------\n";
}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
string ConvertUserRecordToLine(stUser User, string Seperator = "#//#") {
	string stUserRecord = "";
	stUserRecord += User.UserName + Seperator;
	stUserRecord += User.Password+ Seperator;
	stUserRecord += to_string(User.Permissions);

	return stUserRecord;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient>& vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient& C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}
vector <stUser> SaveUsersDataToFile(string FileName, vector <stUser>& vUser)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (stUser& U : vUser)
		{
			if (U.MarkForDelete == false)
			{
				DataLine = ConvertUserRecordToLine(U);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vUser;
}
bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client) {
	for (sClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
bool FindUsertByUserName(string UserName, vector <stUser> vUser, stUser& User) {
	for (stUser U : vUser)
	{
		if (U.UserName == UserName)
		{
			User = U;
			return true;
		}
	}
	return false;
}
bool ClientExistsByAccountNumber(string AccountNumber, string FileName) {

	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = convertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}

		}
		MyFile.close();
	}

	return false;
}
bool UserExistsByUserName(string UserName, string FileName) {

	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		stUser User;
		while (getline(MyFile, Line))
		{
			User = ConvertUserLinetoRecord(Line);
			if (User.UserName == UserName)
			{
				MyFile.close();
				return true;
			}

		}
		MyFile.close();
	}

	return false;
}
int  ReadPermissionsToSet() {
	int Permissions = 0;
	char Answer = 'n';
	cout << "\nDo you want to give full access? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		return -1;
	}
	cout << "\nDo you want to give access to : \n ";

	cout << "\nShow Client List? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permissions += enMainMenuePermissions::pListClients;
	}
	cout << "\nAdd New Client? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permissions += enMainMenuePermissions::pAddNewClient;
	}
	cout << "\nDelete Client? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permissions += enMainMenuePermissions::pDeleteClient;
	}
	cout << "\nUpdate Client? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permissions += enMainMenuePermissions::pUpdateClient;
	}
	cout << "\nFind Client? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permissions += enMainMenuePermissions::pFindClient;
	}
	cout << "\nTransactions? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permissions += enMainMenuePermissions::pTransactions;
	}
	cout << "\nMange Users? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permissions += enMainMenuePermissions::pMangeUsers;
	}
	return Permissions;
}
sClient ReadNewClient() {
	sClient Client;
	cout << "Enter Account Number ? ";
	getline(cin >> ws, Client.AccountNumber);
	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName)) {
		cout << "\nClient With [" << Client.AccountNumber << "] Already Exists, Enter Another Account Number ? ";
		getline(cin >> ws, Client.AccountNumber);

	}
	cout << "Enter Pin Code ? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return Client;
}
stUser ReadNewUser(){
	stUser User;
	cout << "Enter User Name ? ";
	getline(cin >> ws, User.UserName);
	while (UserExistsByUserName(User.UserName, UsersFileName)) {
		cout << "\nUser With [" << User.UserName << "] Already Exists, Enter Another User Namer ? ";
		getline(cin >> ws, User.UserName);

	}
	cout << "Enter Password ? ";
	getline(cin, User.Password);
	User.Permissions = ReadPermissionsToSet();
	return User;
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
	sClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}
void AddNewUsers(){
	stUser User;
	User = ReadNewUser();
	AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(User));
}
void AddClients()
{
	char AddMore = 'Y';
	do
	{
		cout << "Adding New Client:\n\n";
		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
void AddUsers()
{
	char AddMore = 'Y';
	do
	{
		cout << "Adding New Users:\n\n";
		AddNewUsers();
		cout << "\nClient Added Successfully, do you want to add more Users ? Y / N ? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
void ShowAccessDeniedMessage()
{
	cout << "\n------------------------------------\n";
	cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";
	cout << "\n------------------------------------\n";
}
void ShowClientListScreen() {
	if (!CheckAccessPermission(enMainMenuePermissions::pListClients))
	{
		ShowAccessDeniedMessage();
		return;
	}
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	PrintAllClientsData(vClients);

}
void ShowUsersListScreen() {
	vector <stUser> vUser = LoadUsersDataFromFile(UsersFileName);
	PrintAllUsersData(vUser);
}

bool CheckAccessPermission(enMainMenuePermissions Permission)
{
	if (CurrentUser.Permissions == enMainMenuePermissions::eAll)
		return true;

	if ((Permission & CurrentUser.Permissions) == Permission)
		return true;
	else
		return false;

}

void GoBackToMianMenue() {
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}
void GoBackToMangeUsers() {
	cout << "\n\nPress any key to go back to Mange Users Menue...";
	system("pause>0");
	ShowMangeUsersMenue();
}
void GoBackToTransactionsMenue() {
	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	ShowTransactionsMenue();
}
void ShowAddNewClientScreen() {
	if (!CheckAccessPermission(enMainMenuePermissions::pAddNewClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n------------------------------------\n";
	cout << "\tAdd New Client \n";
	cout << "------------------------------------\n\n";
	AddClients();
}
void ShowAddNewUserScreen() {
	cout << "\n------------------------------------\n";
	cout << "\tAdd New User \n";
	cout << "------------------------------------\n\n";
	AddUsers();
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
bool MarkUserForDeleteByUserName(string UserName, vector<stUser>& vUser)
{
	for (stUser& U : vUser)
	{
		if (U.UserName == UserName)
		{
			U.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		printDataClient(Client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}
bool DeleteUserByUserName(string UserName, vector<stUser>& vUser)
{
	if (UserName == "Admin")
	{
		cout << "\n\nYou cannot Delete This User.";
		return false;

	}

	stUser User;
	char Answer = 'n';
	if (FindUsertByUserName(UserName, vUser, User))
	{
		printDataUser(User);
		cout << "\n\nAre you sure you want delete this User? y/n ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			MarkUserForDeleteByUserName(UserName, vUser);
			SaveUsersDataToFile(UsersFileName, vUser);
			vUser = LoadUsersDataFromFile(UsersFileName);
			cout << "\n\nUser Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nUser with User Name (" << UserName << ") is Not Found!";
		return false;
	}
}
string ReadAccountNumber() {
	string AccountNumber = "";
	cout << "please Enter Account Number ? ";
	cin >> AccountNumber;
	return AccountNumber;
}
string ReadUserName() {
	string UserName = "";
	cout << "please Enter User Name ? ";
	cin >> UserName;
	return UserName;
}
void ShowDeletClientScreen() {
	if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	cout << "\n------------------------------------\n";
	cout << "\tDelet Client Screen  \n";
	cout << "------------------------------------\n\n";
	string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);

}
void ShowDeletUsersScreen() {
	vector<stUser> vUser = LoadUsersDataFromFile(UsersFileName);
	cout << "\n------------------------------------\n";
	cout << "\tDelet Users Screen  \n";
	cout << "------------------------------------\n\n";
	string UserName = ReadUserName();
	DeleteUserByUserName(UserName, vUser);
}
sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return Client;
}
stUser ChangeUserRecord(string UserName)
{
	stUser User;
	User.UserName= UserName;
	cout << "\n\nEnter Password? ";
	getline(cin >> ws, User.Password);
	User.Permissions = ReadPermissionsToSet();
	return User;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients) {

	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		printDataClient(Client);
		cout << "\n\nAre you sure you want update this client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (sClient& C : vClients) {
				if (C.AccountNumber == AccountNumber) {
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}
bool UpdateUserByUserName(string UserName, vector<stUser>& vUser) {

	stUser User;
	char Answer = 'n';
	if (FindUsertByUserName(UserName, vUser, User))
	{
		printDataUser(User);
		cout << "\n\nAre you sure you want update this User? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			for (stUser& U : vUser)
			{
				if (U.UserName == UserName)
				{
					U = ChangeUserRecord(UserName);
					break;
				}
			}
			SaveUsersDataToFile(UsersFileName, vUser);
			cout << "\n\nUser Updated Successfully.";
			return true;
		}
	}
	else {
		cout << "\nUser with User Name (" << UserName << ") is Not Found!";
		return false;
	}
}
void ShowUpdateClienScreen() {
	if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n------------------------------------\n";
	cout << "\tUpdate Clien Screen  \n";
	cout << "------------------------------------\n\n";
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}
void ShowUpdateUsersScreen() {
	cout << "\n------------------------------------\n";
	cout << "\tUpdate User Screen  \n";
	cout << "------------------------------------\n\n";
	vector<stUser> vUser = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();
	UpdateUserByUserName(UserName, vUser);
}
void ShowFindClienScreen() {
	if (!CheckAccessPermission(enMainMenuePermissions::pFindClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	sClient Client;
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	cout << "\n------------------------------------\n";
	cout << "\tFind Clien Screen  \n";
	cout << "------------------------------------\n\n";
	string AccountNumber = ReadAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		printDataClient(Client);
	}
	else {
		cout << "Client With Account Number [" << AccountNumber << "] is Not Found!";
	}
}
void ShowFindUserScreen() {
	stUser User;
	vector<stUser> vUser = LoadUsersDataFromFile(UsersFileName);
	cout << "\n------------------------------------\n";
	cout << "\tFind User Screen  \n";
	cout << "------------------------------------\n\n";
	string UserName = ReadUserName();
	if (FindUsertByUserName(UserName, vUser, User)) {
		printDataUser(User);
	}
	else {
		cout << "User With Account Number [" << UserName << "] is Not Found!";
	}
}
void ShowEndScreen() {
	cout << "\n------------------------------------\n";
	cout << "\tProgram Ends :-)  \n";
	cout << "------------------------------------\n\n";
}
double GetTotalBalances(vector <sClient> vClients) {
	double totalBalance = 0;
	for (sClient& C : vClients) {
		totalBalance += C.AccountBalance;
	}
	return totalBalance;
}
void PrintClientsBalances(vector <sClient> vClients) {
	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
	cout << "\n___________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n___________________________________________________________________________________________________\n\n";
	for (sClient& Client : vClients) {
		cout << "| " << left << setw(15) << Client.AccountNumber;
		cout << "| " << left << setw(40) << Client.Name;
		cout << "| " << left << setw(12) << Client.AccountBalance;
		cout << endl;
	}
	cout << "\n___________________________________________________________________________________________________\n";

	cout << "\n\t\t\t\t\tTotal Balances = " << GetTotalBalances(vClients) << "\n";
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
short ReadMangeUsersMenueOption()
{
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
double ReadDepositAmount()
{
	double DepositAmount = 0;
	cout << "\nPlease enter deposit amount ? ";
	cin >> DepositAmount;
	return DepositAmount;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{
	char Answer = 'n';
	cout << "\n\nAre you sure you want perfrom this transaction? y / n ? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New balance is: "
					<< C.AccountBalance;
				return true;
			}
		}
		return false;
	}
}

void ShowDeposit() {
	cout << "\n------------------------------------\n";
	cout << "\tDeposit Screen  \n";
	cout << "------------------------------------\n\n";
	sClient Client;
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does Not exist.\n\n";
		AccountNumber = ReadAccountNumber();
	}
	printDataClient(Client);
	double Amount = 0;
	cout << "\n\nPlease enter deposit amount ? ";
	cin >> Amount;
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}
void ShowWithdraw() {
	cout << "\n------------------------------------\n";
	cout << "\tWithdraw Screen  \n";
	cout << "------------------------------------\n\n";
	sClient Client;
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does Not exist.\n\n";
		AccountNumber = ReadAccountNumber();
	}
	printDataClient(Client);
	double Amount = 0;
	cout << "\n\nPlease enter deposit amount ? ";
	cin >> Amount;
	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw upto : " << Client.AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;
	}
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}
void ShowTotalBalances() {
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	PrintClientsBalances(vClients);
}
void PerformTransactionsMenueOption(enTransactionsMenueOption TransactionsMenueOption) {
	switch (TransactionsMenueOption)
	{
	case enTransactionsMenueOption::Deposit:
		system("cls");
		ShowDeposit();
		GoBackToTransactionsMenue();
		break;
	case enTransactionsMenueOption::Withdraw:
		system("cls");
		ShowWithdraw();
		GoBackToTransactionsMenue();
		break;
	case enTransactionsMenueOption::TotalBalances:
		system("cls");
		ShowTotalBalances();
		GoBackToTransactionsMenue();
		break;
	case enTransactionsMenueOption::MainMenue:
		ShowMainMenue();

	}
}
void PerformMangeUsersMenueOption(enMangeUsersMenueOption MangeUsersMenueOption) {
	switch (MangeUsersMenueOption)
	{
	case enMangeUsersMenueOption::ListUsers:
		system("cls");
		ShowUsersListScreen();
		GoBackToMangeUsers();
		break;
	case  enMangeUsersMenueOption::AddNewUser:
		system("cls");
		ShowAddNewUserScreen();
		GoBackToMangeUsers();
		break;
	case  enMangeUsersMenueOption::DeleteUser:
		system("cls");
		ShowDeletUsersScreen();
		GoBackToMangeUsers();
		break;
	case  enMangeUsersMenueOption::UpdateUser:
		system("cls");
		ShowUpdateUsersScreen();
		GoBackToMangeUsers();
		break;
	case  enMangeUsersMenueOption::FindUser:
		system("cls");
		ShowFindUserScreen();
		GoBackToMangeUsers();
		break;
	case  enMangeUsersMenueOption::eMainMenue:
		ShowMainMenue();
	}
}
void ShowTransactionsMenue() {
	if (!CheckAccessPermission(enMainMenuePermissions::pTransactions))
	{
		ShowAccessDeniedMessage();
		return;
	}
	system("cls");
	cout << "===============================================\n";
	cout << "\t\Transactions Menue Screen \n";
	cout << "===============================================\n";
	cout << "\t[1] Deposit.\n ";
	cout << "\t[2] Withdraw.\n ";
	cout << "\t[3] Total Balances.\n ";
	cout << "\t[4] Mian Menue.\n ";
	cout << "===============================================\n";
	PerformTransactionsMenueOption(enTransactionsMenueOption(ReadTransactionsMenueOption()));
}
void ShowMangeUsersMenue() {
	if (!CheckAccessPermission(enMainMenuePermissions::pMangeUsers))
	{
		ShowAccessDeniedMessage();
		return;
	}
	system("cls");
	cout << "===============================================\n";
	cout << "\t\Mange Users Menue Screen \n";
	cout << "===============================================\n";
	cout << "\t[1] List Users.\n ";
	cout << "\t[2] Add New User.\n ";
	cout << "\t[3] Delete User.\n ";
	cout << "\t[4] Update User.\n ";
	cout << "\t[5] Find User.\n ";
	cout << "\t[6] Mian Menue. \n ";
	cout << "===============================================\n";
	PerformMangeUsersMenueOption(enMangeUsersMenueOption(ReadMangeUsersMenueOption()));
}
void PerformMainMenueOption(enMainMenueOptions MainMenueOption) {
	switch (MainMenueOption)
	{
	case enMainMenueOptions::eListClients:
		system("cls");
		ShowClientListScreen();
		GoBackToMianMenue();
		break;
	case  enMainMenueOptions::eAddNewClient:
		system("cls");
		ShowAddNewClientScreen();
		GoBackToMianMenue();
		break;
	case  enMainMenueOptions::eDeleteClient:
		system("cls");
		ShowDeletClientScreen();
		GoBackToMianMenue();
		break;
	case  enMainMenueOptions::eUpdateClient:
		system("cls");
		ShowUpdateClienScreen();
		GoBackToMianMenue();
		break;
	case  enMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClienScreen();
		GoBackToMianMenue();
		break;
	case  enMainMenueOptions::Transactions:
		system("cls");
		ShowTransactionsMenue();
		GoBackToMianMenue();
		break;
	case  enMainMenueOptions::MangeUsers:
		system("cls");
		ShowMangeUsersMenue();
		GoBackToMianMenue();
		break;
	case  enMainMenueOptions::Logout:
		system("cls");
		//ShowEndScreen();
		Login();
		break;
	}
}
void ShowMainMenue() {
	system("cls");
	cout << "===============================================\n";
	cout << "\t\tMain Menue Screen \n";
	cout << "===============================================\n";
	cout << "\t[1] Show Client List.   \n ";
	cout << "\t[2] Add New Client.     \n ";
	cout << "\t[3] Delet Client.       \n ";
	cout << "\t[4] Update Client Info. \n ";
	cout << "\t[5] Find Client. \n ";
	cout << "\t[6] Transactions.\n ";
	cout << "\t[7] Mange Users.\n ";
	cout << "\t[8] Logout.\n ";
	cout << "===============================================\n";
	PerformMainMenueOption(enMainMenueOptions(ReadMainMenueOption()));
}
bool FindUserByUsernameAndPassword(string Username, string Password, stUser& User)
{
	vector<stUser> vUser = LoadUsersDataFromFile(UsersFileName);

	for (stUser U : vUser)
	{
		if (U.UserName == Username && U.Password == Password)
		{
			User = U;
			return true;
		}
	}

	return false;
}
bool LoadUserInfo(string Username, string Password)
{

	return (FindUserByUsernameAndPassword(Username, Password, CurrentUser));
	
}

void Login()
{
	bool LoginFaild = false;

	string Username, Password;
	do
	{
		system("cls");
		cout << "\n---------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n---------------------------------\n";

		if (LoginFaild)
		{
			cout << "Invlaid Username/Password!\n";
		}

		cout << "Enter Username? ";
		cin >> Username;
		cout << "Enter Password? ";
		cin >> Password;
		LoginFaild = !LoadUserInfo(Username, Password);
	} while (LoginFaild);

	ShowMainMenue();

}
int main() {
	Login();
	system("pause>0");
	return 0;
}
