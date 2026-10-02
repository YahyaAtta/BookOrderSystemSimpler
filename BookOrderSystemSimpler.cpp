#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;

struct sBook {

	int BookId;
	string BookName;
	string BookAuthor;
	double BookPrice;
	int OrderNumber = 0;
	int Quantity = 0;
	double BookBarketPrice = 0; 
	int BookBarketQuantity = 0; 
	float BookDiscountPercentage = 0;
	bool isOrdered=false;
	bool isMarkForDelete = false;

};

const string BooksFileName = "Books.txt";

enum enMainMenu {
  eListBooks = 1 , eAddBooks=2  ,eUpdateBook=3 , eDeleteBook=4 , eFindBook=5 ,
eOrderBook = 6 ,eDeleteBooks=7,eExit=8
};
enum enSubOrderMenu {
	eShowOrder=1 , eAddNewOrder = 2 , eMainMenu=3
};
enum enColor {
	White = 1 , Red = 2
};

int RandomNumber(int From, int To) {
	int Random = rand() % (To - From) + From;
	return Random; 
}

int GenerateBookID() {
	return RandomNumber(1000, 10000); 
}

void ChangeColorText(enColor Color) {
		switch (Color) {
		case enColor::White:
			system("color 07"); break;
		case enColor::Red:
			system("color 04");break;
		}
}

void ResetScreen() {
	system("cls"); 
  }
void GoBackToMainMenu() {
#ifdef _WIN32
	cout << "Press Any Key To Go Back Main Menu.....";
	system("pause>0"); 
#else
    system("read -p 'Press Any Key To Go Back Main Menu.....' var")
#endif
}
vector<string> SplitString(string S1, string Sperators = "#//#")
{
	short pos = 0;
	string sWord = "";
	vector<string> vStrings;
	while ((pos = S1.find(Sperators)) != string::npos)
	{
		sWord = S1.substr(0,pos);
		if (sWord != "") {
			vStrings.push_back(sWord); 
		}
		S1.erase(0, pos + Sperators.length());
	}
	if (S1 != "")
	{
		vStrings.push_back(S1);
	}
	return vStrings;
 }
string ConvertRecordToLine(sBook Book, string Sperator = "#//#")
{
	string stBookRecord = ""; 
	stBookRecord += to_string(Book.BookId) + Sperator; 
	stBookRecord += to_string(Book.OrderNumber) + Sperator; 
	stBookRecord += Book.BookName + Sperator;
	stBookRecord += Book.BookAuthor + Sperator;
	stBookRecord += to_string(Book.Quantity) + Sperator;
	stBookRecord += to_string(Book.BookPrice) + Sperator;
	stBookRecord += to_string(Book.BookBarketQuantity) + Sperator;
	stBookRecord += to_string(Book.BookBarketPrice) + Sperator; 
	stBookRecord += to_string(Book.isOrdered);
	return stBookRecord;
}
sBook ConvertLineToRecord(string Line)
{
	vector<string> vStrings = SplitString(Line); 
	sBook Book;
	Book.BookId = stoi(vStrings[0]);
	Book.OrderNumber = stoi(vStrings[1]);
	Book.BookName = vStrings[2]; 
	Book.BookAuthor = vStrings[3]; 
	Book.Quantity = stoi(vStrings[4]);
	Book.BookPrice = stod(vStrings[5]);
	Book.BookBarketQuantity = stoi(vStrings[6]);
	Book.BookBarketPrice = stod(vStrings[7]); 
	Book.isOrdered = stoi(vStrings[8]);
	
	return Book; 
}

vector<sBook> LoadBooksDataFromFile(string FileName) {
	fstream MyFile;
	MyFile.open(FileName, ios::in); 
	vector<sBook> vBooks;
	if (MyFile.is_open())
	{
		string Line; 
		sBook Book; 
		while (getline(MyFile, Line)) {
			Book = ConvertLineToRecord(Line); 
			vBooks.push_back(Book); 
		}
		MyFile.close(); 
	}
	return vBooks;
}
void PrintBookRecordLine(const sBook& Book)
{
	double BookPrice = (Book.Quantity > 0) ? Book.BookPrice * Book.Quantity : Book.BookPrice;
	string CheckStock = (Book.Quantity == 0) ? "No" : "Yes";
	cout << "| " << left << setw(8) << Book.BookId;
	cout << "| " << left << setw(20) << Book.BookName;
	cout << "| " << left << setw(15) << Book.BookAuthor;
	cout << "| " << left << setw(12) << Book.Quantity;
	cout << "| " << left << setw(12) << Book.BookPrice;
	cout << "| " << left << setw(12) << BookPrice;
	cout << "        | " << left << setw(12) << CheckStock;
	cout << endl;
 }
void ShowAllBooksScreen()
{
	vector<sBook> vBooks = LoadBooksDataFromFile(BooksFileName); 
	cout << "___________________________________________________";
	cout << "_____________________________________________________________________";
	cout << "\n\n\t\t\t\t\tAvaliable Books (" << vBooks.size() << ").\n";
	cout << "___________________________________________________";
	cout << "_____________________________________________________________________\n\n";
	cout << "| " << left << setw(8) << "Book ID"; 
	cout << "| " << left << setw(20) << "Book Name"; 
	cout << "| " << left << setw(15) << "Book Author";
	cout << "| " << left << setw(12) << "Quantity";
	cout << "| " << left << setw(12) << "Book Price";
	cout << "| " << left << setw(12) << "Price With Quantitys"; 
	cout << "| " << left << setw(12) << "Is Exists in Stock";
	cout << endl;
	cout << "___________________________________________________";
	cout << "_____________________________________________________________________\n\n";
	if (vBooks.size() == 0)
		cout << "\t\t\t\t\t No Book Avaliable in The System.\n";
	else

		for (const sBook& Book : vBooks)
			PrintBookRecordLine(Book); 
	cout << "___________________________________________________";
	cout << "_____________________________________________________________________\n\n";
}
void Title(string TitleName)
{
	cout << "\n----------------------------------------------\n";
	cout << "\n\t" << TitleName <<"\n";
	cout << "\n-----------------------------------------------\n\n";
}
bool BookExistsByBookId(string FileName , int BookId) {
	fstream MyFile; 
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line; 
		sBook Book;
		while (getline(MyFile, Line))
		{
			Book = ConvertLineToRecord(Line); 
			if (Book.BookId == BookId)
			{
				MyFile.close(); 
				return true;
			}
		}
		MyFile.close(); 
	}
	return false; 
}
void AddDataLineToFile(string FileName, string DataLine) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open()) {
		MyFile << DataLine << endl;
		MyFile.close();
	}
}
sBook ReadNewBook() {
	sBook Book;
	Book.BookId = GenerateBookID(); 
	while(BookExistsByBookId(BooksFileName, Book.BookId))
	{
		cout << "\nThis Book ID " << Book.BookId << " is Already Exists\n\n";
		system("pause>0"); 
		Book.BookId = GenerateBookID();
	}
	cout << "Enter Book Name? ";
	getline(cin >> ws, Book.BookName);
	cout << "Enter Book Author? ";
	getline(cin, Book.BookAuthor);
	cout << "Enter Quanitiy? ";
	cin >> Book.Quantity; 
	cout << "Enter Book Price? ";
	cin >> Book.BookPrice;
	return Book;
}
void AddBook() {
	sBook Book = ReadNewBook();
	AddDataLineToFile(BooksFileName, ConvertRecordToLine(Book));
}
void AddBooks() {
	char Answer = 'n'; 
	do {
		ResetScreen();
		Title("Add Books Screen"); 
		cout << "Adding New Book:\n\n"; 
		AddBook(); 
		cout << "\nBook Added Successfully....\n"; 
		cout << "Do You want to add more books y/n?";
		cin >> Answer;
	} while (toupper(Answer) == 'Y'); 
}
int ReadBookId() {
	int BookId;

	cout << "Enter Book ID? ";
	cin >> BookId;

	return BookId;
}
bool FindBookByBookId(int BookId , sBook& Book , vector<sBook>&vBooks) {

	for (sBook& B : vBooks)
	{
		if (B.BookId == BookId) {
			Book = B; 
			return true;
		}
	}
	return false; 
}

void PrintBookCard(const sBook& Book) {
	cout << "\nThe Following are the Book details Below:\n"; 
	cout << "---------------------------------------------\n"; 
	cout << "Book ID: " << Book.BookId << "\n"; 
	cout << "Book Name: " << Book.BookName << "\n"; 
	cout << "Book Author: " << Book.BookAuthor << "\n"; 
	cout << "Book Price: " << Book.BookPrice << "\n"; 
	cout << "Book Quantity: " << Book.Quantity << "\n";
 	cout << "---------------------------------------------\n";
	cout << endl; 
}
void FindBookScreen() {
	Title("Find Book Screen");
	vector<sBook> vBooks = LoadBooksDataFromFile(BooksFileName); 
	sBook Book; 
	int BookId; 
	BookId = ReadBookId(); 
	if (FindBookByBookId(BookId, Book, vBooks))
		PrintBookCard(Book); 
	else
		cout << "The Book ID " << BookId << " is Not Found!\n\n";
	cout << "\n"; 
}

void AddBookScreen() {
	AddBooks(); 
}
sBook UpdateBookData(int BookId) {
	sBook Book;
	Book.BookId = BookId;
	cout << "Enter Book Name? ";
	getline(cin >> ws, Book.BookName);
	cout << "Enter Book Author? ";
	getline(cin, Book.BookAuthor);
	cout << "Enter Book Price? ";
	cin >> Book.BookPrice;
	cout << "Enter Book Quantity? ";
	cin >> Book.Quantity;
	return Book;
}
bool SaveBooksDataIntoFile(string FileName, vector<sBook>& vBooks)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		string Line;

		for (sBook& B : vBooks) {

			if (B.isMarkForDelete == false)
			{
				Line = ConvertRecordToLine(B);
				MyFile << Line << endl;
			}
		}
	}
	return true;
}

bool UpdateBookByBookId(vector<sBook>& vBooks, int BookId)
{
	sBook Book;
	if (FindBookByBookId(BookId, Book, vBooks))
	{
		PrintBookCard(Book);
		char Answer = 'n';
		cout << "\n\nAre You Sure to Update This Book Y/N? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			for (sBook& B : vBooks) {

				if (B.BookId == BookId)
				{
					B = UpdateBookData(BookId);
				}

			}
			SaveBooksDataIntoFile(BooksFileName, vBooks);
			cout << "\nBook Updated Successfully...\n";
			return true;
		}
	}
	else {
		cout << "The Book ID " << BookId << " is Not Found!\n\n";
		return false;
	}
}
void UpdateBook()
{
	vector<sBook> vBooks = LoadBooksDataFromFile(BooksFileName);
	int BookId = ReadBookId();
	UpdateBookByBookId(vBooks, BookId);
}
void UpdateBookScreen()
{
	Title("Update Book Screen"); 
	UpdateBook(); 
}

bool BookMarkForDelete(vector<sBook>& vBooks , int BookId)
{
	for (sBook& B : vBooks)
	{
		if (B.BookId == BookId)
		{
			B.isMarkForDelete = true; 
			return true;
		}
	}
	return false;
}
bool DeleteBookByBookId(vector<sBook>& vBooks, int BookId)
{
	sBook Book;
	if (FindBookByBookId(BookId, Book, vBooks))
	{
		PrintBookCard(Book);
		char Answer = 'n';
		cout << "\n\nAre You Sure to Delete This Book Y/N? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			BookMarkForDelete(vBooks, BookId);
			SaveBooksDataIntoFile(BooksFileName, vBooks);
			cout << "\nBook Deleted Successfully...\n";
			return true;
		}
	}
	else {
		cout << "The Book ID " << BookId << " is Not Found!\n\n";
		return false;
	}
}
void DeleteBook() {
	vector<sBook> vBooks = LoadBooksDataFromFile(BooksFileName);
	int BookId = ReadBookId();
	DeleteBookByBookId(vBooks, BookId);
}

void DeleteBookScreen()
{
	Title("Delete Book Screen"); 
	DeleteBook(); 
}

void ExitScreen() {
	Title("Program Ends -:)");
}
void PrintBill(sBook& Book) {
	string Price = Book.BookDiscountPercentage == 1.0 ? "BOOK PRICE:" : "BOOK PRICE AFTER DISCOUNT:"; 
	ResetScreen(); 
	cout << "\n================================================\n";
	cout << "\n                CUSTOMER INVOICE                  \n";
	cout << "\n================================================\n\n";
	cout << "#" << Book.OrderNumber << " ORDER NUMBER" << "\n\n";
	cout << "BOOK NAME:" << Book.BookName << "\n\n";
	cout << "BOOK AUTHOR:" << Book.BookAuthor << "\n\n";
	cout << "DISCOUNTED:" <<  100 - (Book.BookDiscountPercentage) * 100 << "%" << "\n\n";
	cout << Price << Book.BookPrice * Book.BookDiscountPercentage << "\n\n";
	cout << "\nTHANKS YOU FOR ORDERING :-)\n";
	cout << "\n================================================\n";
}
int ReadQuantity() {
	int Q = 0 ; 
	cout << "Please Enter Quantity? ";
	cin >> Q;
	return Q;
}
int GetOrderNumber() {
	return RandomNumber(10000, 20000);
}
double GetDiscount(short Q) {
	return (Q >1) ? 0.9 : 1.0;
}
bool ChangeUpdateBookQuantity(vector<sBook>& vBooks,int BookId , int Quantity,double Discount)
{
		for (sBook& B : vBooks) {
			if (B.BookId == BookId)
			{
				B.isOrdered = true;
				B.Quantity -= Quantity;
				B.BookBarketQuantity += Quantity;
				B.isOrdered = true;
				B.OrderNumber = GetOrderNumber();
				B.BookDiscountPercentage = Discount;
				B.BookBarketPrice = B.BookPrice * B.BookDiscountPercentage;
				SaveBooksDataIntoFile(BooksFileName, vBooks);
				PrintBill(B);
				return true;
			}
		}
	return false; 
}
void UpdateBookQuantity(vector<sBook>& vBooks,int BookId , int Quantity , double Discount) {
	ChangeUpdateBookQuantity(vBooks, BookId, Quantity, Discount);
}
void GoBackToOrderMenu()
{
#ifdef _WIN32
	cout << "Press Any Key To Go Back Main Menu.....";
	system("pause>0");
#else
	system("read -p 'Press Any Key To Go Back Main Menu.....' var")
#endif
}
bool IsQuantityEmpty(int QuantityBook) {
	return (QuantityBook == 0);
}
bool BookNotExistsByBookQuantityInStock(int InputQuantity , int BookQuantity) {
	return InputQuantity > BookQuantity; 
}
bool OrderBook(vector<sBook>vBooks,int BookId)
{
	sBook Book; 
	if (FindBookByBookId(BookId, Book, vBooks)) {
		PrintBookCard(Book); 
		int Quantity = ReadQuantity(); 
		if (IsQuantityEmpty(Book.Quantity)) {
			cout << "\nThere is No Book in Stock....\n";
			return  false;
	     }
		while(BookNotExistsByBookQuantityInStock(Quantity , Book.Quantity)) {
			cout << "Your Input is Greater than Exists\n"; 
		      Quantity =ReadQuantity();
		}
		double Discount; 
		Discount = GetDiscount(Quantity);
		char Answer = 'n'; 
		cout << "Are You Sure to Perform This Operation Y/N? "; 
		cin >> Answer; 
			if (toupper(Answer) == 'Y') {
				UpdateBookQuantity(vBooks, BookId, Quantity, Discount); 
				return true;
		    }
	}
	else {
		cout << "\nThis Book " << BookId << " is Not Found!\n"; 
		return false; 
	}
}
void AddNewOrderScreen()
{
	Title("Order Book Screen");
	vector<sBook> vBooks = LoadBooksDataFromFile(BooksFileName);
	int BookId = ReadBookId();
	OrderBook(vBooks, BookId); 
}
void PrintBookOrderRecordLine(const sBook& Book) {
	cout << "| " << left << setw(8) << Book.BookId;
	cout << "| " << left << setw(12) << Book.OrderNumber; 
	cout << "| " << left << setw(20) << Book.BookName;
	cout << "| " << left << setw(15) << Book.BookAuthor;
	cout << "| " << left << setw(12) << Book.BookBarketQuantity;
	cout << "| " << left << setw(12) << Book.BookBarketPrice;
	cout << "| " << left << setw(12) << Book.BookBarketPrice * Book.BookBarketQuantity;

	cout << endl;
}
void ShowOrderScreen()
{
	double TotalPrice = 0;
	vector<sBook> vBooks = LoadBooksDataFromFile(BooksFileName);
	cout << "___________________________________________________";
	cout << "_____________________________________________________________________";
	short RemainingBook = 0;
	for (sBook& B : vBooks) {
		if (B.isOrdered == true)
			RemainingBook++;
	}
	cout << "\n\n\t\t\t\t\tAvaliable Order Books (" <<RemainingBook<< ").\n";
	cout << "___________________________________________________";
	cout << "_____________________________________________________________________\n\n";
	cout << "| " << left << setw(8) << "Book ID";
	cout << "| " << left << setw(12) << "Order Number";
	cout << "| " << left << setw(20) << "Book Name";
	cout << "| " << left << setw(15) << "Book Author";
	cout << "| " << left << setw(12) << "Quantity";
	cout << "| " << left << setw(12) << "Book Price";
	cout << "| " << left << setw(12) << "Book Price With Quantity";
	cout << endl;
	cout << "___________________________________________________";
	cout << "_____________________________________________________________________\n\n";
	if (RemainingBook == 0)
		cout << "\t\t\t\t\t No Book Avaliable in The System.\n";
	else
	
		for (const sBook& Book : vBooks)
			if (Book.isOrdered == true)
			{
				PrintBookOrderRecordLine(Book);
				 TotalPrice+= Book.BookBarketPrice * Book.BookBarketQuantity;
			} 
	cout << "___________________________________________________";
	cout << "_____________________________________________________________________\n\n";
	cout << "\n\n\n\t\t\t\tTotal Price = " << TotalPrice << endl;

}
void PerformOrderMenuOption(enSubOrderMenu eMenu) {
	switch (eMenu) {
	case enSubOrderMenu::eShowOrder:
		ResetScreen();
		ShowOrderScreen(); 
		GoBackToOrderMenu(); 
		break;
	case enSubOrderMenu::eAddNewOrder:
		ResetScreen(); 
		AddNewOrderScreen();
		GoBackToOrderMenu(); 
		break;
	case enSubOrderMenu::eMainMenu:
		break;
	}
}
short ReadMainMenuOption(short From, short To) {
	short Number;
	cout << "Please Choose Number From " << From << " To " << To << "? ";
	cin >> Number;
	while (cin.fail() || (Number < From || Number > To))
	{
		ChangeColorText(enColor::Red);
		if (!cin.fail()) {
			cout << "INVALID NUMBER PLEASE ENTER NUMBER FROM " << From << " TO " << To << " ?";
			cin >> Number;
		}
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "THIS IS NOT A NUMBER PLEASE ENTER A NUMBER?";
			cin >> Number;
		}

	}
	ChangeColorText(enColor::White);
	return Number;
}
void ShowOrderScreenMenu()
{
	enSubOrderMenu enSubMenu = enSubOrderMenu::eShowOrder; 
	do {
		ResetScreen();
		cout << "\n==============================================\n";
		cout << "\n\tOrder Menu\n";
		cout << "\n==============================================\n\n";
		cout << "\t1-Show Orders\n";
		cout << "\t2-Add New Order\n";
		cout << "\t3- Main Menu\n";
		cout << "\n==============================================\n\n";
		enSubMenu = (enSubOrderMenu)ReadMainMenuOption(1, 3);
		PerformOrderMenuOption(enSubMenu);
	} while (enSubMenu!=enSubOrderMenu::eMainMenu); 
}
void DeleteBooks(string FileName) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		MyFile.close(); 
	}
}
void DeleteBooksScreen() {
	Title("Delete Books Screen"); 
	char Answer = 'n';
	cout << "\n\nAre You Sure to Delete All Books? Y/N? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		DeleteBooks(BooksFileName); 
		cout << "\nAll Books Deleted Successfully.....\n";
	}
	cout << "\n\n"; 
}
void PerformMainMenuOption(enMainMenu eMenu) {
	switch(eMenu) {
	case enMainMenu::eListBooks:
		ResetScreen(); 
		ShowAllBooksScreen(); 
		GoBackToMainMenu(); 
		break;
	case enMainMenu::eAddBooks:
		ResetScreen();
		AddBookScreen(); 
		GoBackToMainMenu();
		break;
	case enMainMenu::eUpdateBook:
		ResetScreen(); 
		UpdateBookScreen(); 
		GoBackToMainMenu(); 
		break;
		case enMainMenu::eDeleteBook:
			ResetScreen(); 
			DeleteBookScreen(); 
			GoBackToMainMenu(); 
			break;
		case enMainMenu::eFindBook:
			ResetScreen(); 
			FindBookScreen(); 
			GoBackToMainMenu(); 
			break;
		case enMainMenu::eOrderBook:
			ResetScreen(); 
			ShowOrderScreenMenu();
			break;
		case enMainMenu::eDeleteBooks:
			ResetScreen(); 
			DeleteBooksScreen(); 
			GoBackToMainMenu();
			break;
		case enMainMenu::eExit:
			ResetScreen(); 
			ExitScreen(); 
			break;
	}
}

void ShowMainMenuOptions()
{
	enMainMenu eMenu = enMainMenu::eListBooks; 
	do {
		ResetScreen(); 
		cout << "\n==============================================\n";
		cout << "\n\tMain Menu\n";
		cout << "\n==============================================\n\n";
		cout << "\t1-Show Books\n";
		cout << "\t2-Add Books\n";
		cout << "\t3-Update Book\n";
		cout << "\t4-Delete Book\n"; 
		cout << "\t5-Find Book\n"; 
		cout << "\t6-Order Book\n";
		cout << "\t7-Delete Books\n";
		cout << "\t8-Exit\n";
		cout << "\n==============================================\n\n";
		eMenu =(enMainMenu)ReadMainMenuOption(1, 8); 
		PerformMainMenuOption(eMenu);
	} while (eMenu!=enMainMenu::eExit); 
}

void Init() {
	cout << "\n================================================\n";
	cout << "\n\tWELCOME TO BOOK ORDER SYSTEM SIMPLER\n";
	cout << "\n================================================\n\n";
	cout << "Press Any Key To Start Program..."; 
	system("pause>0");
	cout << "\a";
	ShowMainMenuOptions();
}

int main() {
	srand((unsigned)time(NULL));
	Init();
	system("pause>0");
	return 0;
}