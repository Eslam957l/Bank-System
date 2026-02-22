#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

const string File = "Clients.txt";

void ShowMainMenue();
void ShowTransaction();
void PerfromTransaction();

struct strInfo
{
	string Name;
	string AccountNumber;
	string PinCode;
	string Phone;
	double Salary;
	bool MarkForDelete = false;

};

vector <string> SplitString(string S1, string Delim)
{
	vector <string> vString;
	short pos = 0;
	string Sword;

	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		Sword = S1.substr(0, pos);
		if (Sword != "")
		{
			vString.push_back(Sword);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;

}

strInfo ConvertToRecord(string Line, string Seperator = "#//#")
{
	strInfo Client;
	vector <string> vClientData;
	vClientData = SplitString(Line, Seperator);

	Client.Name = vClientData[0];
	Client.AccountNumber = vClientData[1];
	Client.PinCode = vClientData[2];
	Client.Phone = vClientData[3];
	Client.Salary = stoi(vClientData[4]);

	return Client;
}

string ConvertToLine(strInfo Client, string Seperator = "#//#")
{
	string stClientRecord = "";

	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.Salary);

	return stClientRecord;

}

bool ClientExist(string AccountNumber, string FileName)
{
	vector <strInfo> vClients;
	fstream MyFile;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		strInfo Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertToRecord(Line);
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

strInfo ReadNewClient()
{
	strInfo Client;
	cout << "Enter AccountNumber \n?";


	getline(cin >> ws, Client.AccountNumber);

	while (ClientExist(Client.AccountNumber, File))
	{
		cout << "\n Client With [ " << Client.AccountNumber << "] Already Exists, Enter Another AccountNumber ? ";

		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter PinCode ?";
	getline(cin, Client.PinCode);

	cout << "Enter Name ?";
	getline(cin, Client.Name);

	cout << "Enter Phone ?";
	getline(cin, Client.Phone);

	cout << "Enter Salary ?";
	cin >> Client.Salary;

	return Client;
}

vector <strInfo> LoadClient(string FileName)
{
	vector <strInfo> vClients;
	fstream MyFile;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		strInfo Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertToRecord(Line);
			vClients.push_back(Client);

		}
		MyFile.close();
	}
	return vClients;
}

void PrintClient(strInfo Client)
{
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.Salary;

}

void ShowAllClient()
{
	vector <strInfo> vClients = LoadClient(File);

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_____________________________________________________________ ";
	cout << "________________________________________________\n" << endl;


	cout << "| " << setw(40) << left << "Name";
	cout << "| " << setw(15) << left << "AccountNumber";
	cout << "| " << setw(10) << left << "PinCode";
	cout << "| " << setw(12) << left << "Phone";
	cout << "| " << setw(12) << left << "Salary";

	cout << "\n_____________________________________________________________ ";
	cout << "________________________________________________\n" << endl;

	if (vClients.size() == 0)
	{
		cout << "\t\t\t\t No Clients Available in The System!";
	}
	else
	{
		for (strInfo Client : vClients)
		{
			PrintClient(Client);
			cout << endl;
		}
	}

	cout << "\n_____________________________________________________________ ";
	cout << "________________________________________________\n" << endl;


}

void PrintClientCard(strInfo Client)
{
	cout << "The Following Are The Client Details:\n";
	cout << "**************************************\n";
	cout << "Client Name: " << Client.Name << endl;
	cout << "Client AccountNumber: " << Client.AccountNumber << endl;
	cout << "Client PinCode: " << Client.PinCode << endl;
	cout << "Client Phone: " << Client.Phone << endl;
	cout << "Client Salary: " << Client.Salary << endl;
	cout << "**************************************";

}

bool FindClient(string AccountNumber, vector <strInfo> vClients, strInfo& Client)
{
	for (strInfo C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

strInfo ChangeClientRecord(string AccountNumber)
{
	strInfo Client;
	Client.AccountNumber = AccountNumber;

	cout << "Enter PinCode ?";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name ?";
	getline(cin, Client.Name);

	cout << "Enter Phone ?";
	getline(cin, Client.Phone);

	cout << "Enter Salary ?";
	cin >> Client.Salary;

	return Client;

}

bool MarkClientDelete(string AccountNumber, vector <strInfo>& vClients)
{
	for (strInfo& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector <strInfo> SaveDataToFile(string FileName, vector <strInfo> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	string DataLine;

	if (MyFile.is_open())
	{
		for (strInfo C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

void AddDataToFile(string FileName, string stDataLine)
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
	strInfo Client;
	Client = ReadNewClient();
	AddDataToFile(File, ConvertToLine(Client));

}

void AddNewClients()
{

	char AddMore = 'y';

	do
	{
		system("cls");
		cout << "Add New Client ?\n";
		AddNewClient();

		cout << "\nClient Added Succssfully, Do You Want Add More Client ? (Y/N)" << endl;
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

}

bool DeleteClient(string AccountNumber, vector <strInfo>& vClients)
{
	strInfo Client;
	char Answer = 'n';

	if (FindClient(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\n\n Are You Sure You Want Delete This Client ? (Y/N) ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			MarkClientDelete(AccountNumber, vClients);
			SaveDataToFile(File, vClients);

			vClients = LoadClient(File);

			cout << "\n\n Client Deleted Successfully.";
			return true;
		}

	}
	else
	{
		cout << "\n\n Client With AccoutNumber (" << AccountNumber << ") is Not Found !";
		return false;
	}
}

bool UpdateClient(string AccountNumber, vector <strInfo>& vClients)
{
	strInfo Client;
	char Answer = 'n';

	if (FindClient(AccountNumber, vClients, Client))
	{

		PrintClientCard(Client);
		cout << "\n\nAre You Sure Want Update This Client ? (Y/N)";

		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			for (strInfo& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveDataToFile(File, vClients);
			cout << "\n\n Client Updated Successfully.";
			return true;

		}

	}

	else
	{
		cout << "Client With AccoutNumber (" << AccountNumber << ") is Not Found !";
		return false;
	}

}

bool DepositBalance(string AccountNumber, double Amount, vector <strInfo> vClients)
{
	char Answer = 'n';

	cout << "\n\n Are You Sure Want Perfrom This Transaction ? (Y/N) ?";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y')
	{

		for (strInfo& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.Salary += Amount;
				SaveDataToFile(File, vClients);
				cout << "\n\n Done Successfully. New Balance is: " << C.Salary;

				return true;
			}

		}
		return false;
	}

}

string ReadClientAccoutNumber()
{
	string AccountNumber = "";
	cout << "Please Enter AccoutNumber ?";
	cin >> AccountNumber;

	return AccountNumber;
}

void ShowDeleteClient()
{
	cout << "\n_____________________________________\n";
	cout << "\t Deleted Client Screen";
	cout << "\n_____________________________________\n";

	vector <strInfo> vClients = LoadClient(File);
	string AccountNumber = ReadClientAccoutNumber();
	DeleteClient(AccountNumber, vClients);

}

void ShowUpdateClient()
{

	cout << "\n_____________________________________\n";
	cout << "\t Update Client Screen";
	cout << "\n_____________________________________\n";

	vector <strInfo> vClients = LoadClient(File);
	string AccountNumber = ReadClientAccoutNumber();
	UpdateClient(AccountNumber, vClients);

}

void ShowAddNewClient()
{

	cout << "\n_____________________________________\n";
	cout << "\t Add New Client Screen";
	cout << "\n_____________________________________\n";

	AddNewClients();
}

void ShowFindClientScreen()
{

	cout << "\n_____________________________________\n";
	cout << "\t Find Client Screen";
	cout << "\n_____________________________________\n";

	vector <strInfo> vClients = LoadClient(File);
	strInfo Client;

	string AccountNumber = ReadClientAccoutNumber();


	if (FindClient(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "\n Client With AccountNumber [" << AccountNumber << "] is Not Found !";

	}

}

short ReadTransaction()
{
	cout << "Choose what do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}

void ShowDeposite()
{
	cout << "\n-------------------------------------------\n";
	cout << "\t Deposit Screen ";
	cout << "\n-------------------------------------------\n";

		strInfo Client;

		vector <strInfo> vClients = LoadClient(File);
		string AccountNumber = ReadClientAccoutNumber();
		
		while (!FindClient(AccountNumber, vClients, Client))
		{
			cout << "\n Client With [ " << AccountNumber << "] Does Noe Exist. \n";
			AccountNumber = ReadClientAccoutNumber();

		}

		PrintClientCard(Client);


		double Amount = 0;
		cout << "\n Please Enter Deposit Amount ? ";
		cin >> Amount;

		DepositBalance(AccountNumber, Amount, vClients);

}

void ShowWithdraw()
{
	cout << "\n-------------------------------------------\n";
	cout << "\t Withdraw Screen ";
	cout << "\n-------------------------------------------\n";

	strInfo Client;

	vector <strInfo> vClients = LoadClient(File);
	string AccountNumber = ReadClientAccoutNumber();

	while (!FindClient(AccountNumber, vClients, Client))
	{
		cout << "\n Client With [ " << AccountNumber << "] Does Noe Exist. \n";
		AccountNumber = ReadClientAccoutNumber();

	}

	PrintClientCard(Client);


	double Amount = 0;
	cout << "\n Please Enter Withdraw Amount ? ";
	cin >> Amount;

	while (Amount > Client.Salary)
	{
		cout << "\n Amount Exceeds The Salary, You Can Withdraw Up To : \n";
		cout << "Please Enter Another Amount ?\n";
		cin >> Amount;
	}

	DepositBalance(AccountNumber, Amount * -1, vClients);

}

void ShowTotalBalance()
{
	vector <strInfo> vClients = LoadClient(File);

	cout << "\n\t\t\t\t\tSalary List (" << vClients.size() << ")Client(s).";
	cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Salary ";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	double Salary  = 0;
	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (strInfo Client : vClients)
		{
			PrintClient(Client);
			Salary += Client.Salary;
			cout << endl;
		}

	cout <<	"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t  = " << Salary;


}

void ShowEndScreen()
{

	cout << "\n_____________________________________\n";
	cout << "\t Program  Ends";
	cout << "\n_____________________________________\n";

}

enum enMainMenueScreen
{
	eListClient = 1,
	eAddNewClient = 2,
	eDeleteClient = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	eExit = 7,
	eShowTransaction = 6
};

enum enTransaction
{
	eDeposit = 1,
	eWithdraw = 2,
	eShowTotalBalance = 3,
	eShowMainMenue = 4
};

void GoBackToMenue()
{
	cout << "\n\n Please Any Key To Go Back To Main Menue.....";
	system("pause>0");
	ShowMainMenue();
}

void GoBackToTransaction()
{
	cout << "\n\n Press Any Key To Go Back To Transaction Menue....";
	system("pause>0");
	ShowTransaction();
}

short ReadMainMenue()
{
	cout << "Choose What Do You Want To Do? [1 to 6]?";
	short Choose = 0;
	cin >> Choose;
	return Choose;
}

void PerfromMainMenueOption(enMainMenueScreen MainMenue)
{
	switch (MainMenue)
	{
	case enMainMenueScreen::eListClient:
	{
		system("cls");
		ShowAllClient();
		GoBackToMenue();
		break;
	}

	case enMainMenueScreen::eAddNewClient:
		system("cls");
		ShowAddNewClient();
		GoBackToMenue();
		break;

	case enMainMenueScreen::eDeleteClient:
		system("cls");
		ShowDeleteClient();
		GoBackToMenue();
		break;

	case enMainMenueScreen::eUpdateClient:
		system("cls");
		ShowUpdateClient();
		GoBackToMenue();
		break;

	case enMainMenueScreen::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMenue();
		break;

	case enMainMenueScreen::eShowTransaction:
		system("cls");
		ShowTransaction();
		break;

	case enMainMenueScreen::eExit:
		system("cls");
		ShowEndScreen();
		break;
	}
}

void PerfromTransaction(enTransaction Transaction)
{

	switch (Transaction)
	{
	case enTransaction::eDeposit:
		{
			system("cls");
			ShowDeposite();
			GoBackToTransaction();
			break;
		}

	case enTransaction::eWithdraw:
	{
		system("cls");
		ShowWithdraw();
		GoBackToTransaction();
		break;

	}

	case enTransaction::eShowTotalBalance:
	{
		system("cls");
		ShowTotalBalance();
		GoBackToTransaction();
		break;

	}

	case enTransaction::eShowMainMenue:
	{
		ShowMainMenue();
	}
	}

}

void ShowTransaction()
{
	system("cls");
	cout << "=================================================\n";
	cout << "\t\tTransaction Menue Screen\n";
	cout << "=================================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Salary. \n";
	cout << "\t[4] Main Menue.\n";
	cout << "=================================================\n";

	PerfromTransaction((enTransaction)ReadTransaction());

}

void ShowMainMenue()
{
	system("cls");
	cout << "========================================================================\n";
	cout << "\t\t Main Menue Screen \n";
	cout << "========================================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Information.\n";
	cout << "\t[5] Find Client. \n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "========================================================================\n";


	PerfromMainMenueOption((enMainMenueScreen)ReadMainMenue());

}

int main()
{

	ShowMainMenue();

	system("pause>0");
	return 0;
}

