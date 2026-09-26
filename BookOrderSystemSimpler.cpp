#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<iomanip>
using namespace std;
struct Book {
	string BookName;
	string BookAuthor;
	float BookPrice;
	float BookPricePrecentage;
	float BookPriceAfterDiscount = 0;
	short BookNumber;
	short OrderNumber;
};
void NumberInputValidation(short& Number) {
	cin >> Number;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("color 04");
		cout << "\nINVALID NUMBER , PLEASE ENTER VALID NUMBER:\n";
		cin >> Number;
	}
	system("color 07");
}
int RandomNumber(int From, int To) {
	int R = rand() % (To - From) + From;
	return R; 
}
vector<Book> FetchBooks() {

	vector<Book> vBooks = {
	{"Treasure Island" , "Robert Louis" , (float)RandomNumber(10000,99999) ,.9,0,1, 0} ,
	{"Computer Archit" , "John L." , (float)RandomNumber(10000,99999)  ,.9,0,2, 0} ,
	{"Dart Language" , "Jonathan S." , (float)RandomNumber(10000,99999)  ,.5,0,3, 0} ,
	{"Flutter" , "Alberto M." , (float)RandomNumber(10000,99999)  ,.5,0,4, 0} ,

	};
	return vBooks;
}
void ErrorMessage() {
	system("color 04");
	cout << "\n================================================\n";
	cout << "\n                    ERROR                       \n";
	cout << "\n================================================\n\n";
	cout << "\n                THIS BOOK IS NOT EXISTS          \n";
	cout << "\n================================================\n\n";
	cout << "\nRETURN TO MAIN MENU PRESS ENTER KEY:\n";
	system("pause>0");
	system("color 07");
}
void PrintBill(const vector<Book>& vBooks , short& BookNumber) {
   system("cls");
   if (BookNumber > 4) {
	   ErrorMessage(); 
	   return;
   }
   cout << "\n================================================\n";
   cout << "\n                CUSTOMER INVOICE                  \n";
   cout << "\n================================================\n\n";
   cout << "#" << vBooks[BookNumber - 1].OrderNumber << " ORDER NUMBER" << "\n\n";
   cout << "BOOK NAME:" << vBooks[BookNumber-1].BookName << "\n\n";
   cout << "BOOK AUTHOR:" << vBooks[BookNumber - 1].BookAuthor << "\n\n";
   cout << "BOOK PRICE BEFORE DISCOUNT:" << vBooks[BookNumber - 1].BookPrice << "\n\n";
   cout << "DISCOUNTED:" << 100 - (vBooks[BookNumber - 1].BookPricePrecentage) * 100 << "%" << "\n\n";
   cout << "BOOK PRICE AFTER DISCOUNT:" << vBooks[BookNumber - 1].BookPriceAfterDiscount << "\n\n";
   cout << "\nTHANKS YOU FOR ORDERING :-)\n";
   cout << "\n================================================\n";
   cout << "\nRETURN TO MAIN MENU PRESS ENTER KEY:\n";
   system("pause>0");
}
void CalculateBillWithDiscount(vector<Book>& vBooks , short& BookNumber) {
	float Price = 0;
	float Discount = 0;
	if (BookNumber > 4) {
		return;
	}

	vBooks[BookNumber - 1].OrderNumber = RandomNumber(1000, 9999);
	Price = vBooks[BookNumber - 1].BookPrice;
	Discount = vBooks[BookNumber - 1].BookPricePrecentage; 
	switch (BookNumber) {
	case 1 : 
		Price = Price * Discount;break;
	case 2: 
		Price = Price * Discount;break;
		
	case 3:
		Price = Price * Discount;break;
	case 4:
		Price = Price * Discount;break;
	}
	vBooks[BookNumber - 1].BookPriceAfterDiscount = Price;
}
void PrintBookMenu(vector<Book>& vBooks) {
	cout << "\n================================================\n";
	cout << "\n                    BOOKS MENU                   \n";
	cout << "\n================================================\n\n";
	cout << "|-------|----------------|-------------|--------|\n";
	cout << "|NUMBER |   NAME         |   AUTHOR    | PRICE  |\n";
	cout << "|-------|----------------|-------------|--------|\n";
	for (const Book& BookObj : vBooks) 
	cout << "|" <<left <<   setw(7)  << BookObj.BookNumber << "|" << setw(16) << BookObj.BookName << "|" << setw(13) << BookObj.BookAuthor << "|" << setw(8) << BookObj.BookPrice << "|" << endl;
	cout << "|-------|----------------|-------------|--------|\n";
}

void NewOrder(short& NumberUsing){
	NumberUsing++;
	system("cls");
	short ChooseBook = 0; 
	vector<Book> vBooksFetched = FetchBooks();
	PrintBookMenu(vBooksFetched); 
	cout << "\nPLEASE CHOOSE YOUR BOOK BY NUMBER:";
	NumberInputValidation(ChooseBook); 
	CalculateBillWithDiscount(vBooksFetched,ChooseBook);
	PrintBill(vBooksFetched, ChooseBook); 
}
short MainMenu() {
	short Number = 0 ;
	cout << "\n==============================================\n";
	cout << "\n    WELCOME TO BOOK ORDER SYSTEM SIMPLER        \n";
	cout << "\n==============================================\n\n";
	cout << "                  1-NEW ORDER\n\n"; 
	cout << "                  2-EXIT\n"; 
	cout << "\n==============================================\n";
	cout << "\nCHOOSE YOUR OPTION:";
	NumberInputValidation(Number);
	return Number;
}
void Init() {
	short NumberUsing=0;
	short Exit = 1;
	do {
		system("cls"); 
		Exit = MainMenu(); 
		switch (Exit) {
		case 1:NewOrder(NumberUsing);break;
		}
	} while (Exit != 2); 
	if (NumberUsing > 0) {
		cout << "\n THANKS YOU! :-) \n\nPRESS ENTER TO EXIT\n";
		system("color 02");
		system("pause>0");
   }
}

int main() {
	srand((unsigned)time(NULL));
	Init(); 
	return 0;
}