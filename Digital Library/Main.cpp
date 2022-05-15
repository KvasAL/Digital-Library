#include <iostream>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
#include <iomanip>
#pragma warning(disable:4996)

using namespace std;

struct Book_Data
{
	int Edition;
	char* Name;
	char* Author;
	char* Genre;
	int Price;
	int Rating;
	int ID_of_book;
	int Popularity;
	int	Issuing_time;
};

struct Reader_Data
{
	char* Full_name;
	int	Date_of_birth;
	int Passport_ID;
	int Books_read;
	long long Books_on_hand;
};

void Exit_menu(bool& check)
{
	int exit;
	bool exit_check = 1;

	do
	{
		cout << "\nAre you sure you want to leave?\n#1 Yes #2 No\n"; cin >> exit;

		switch (exit)
		{
		case 1: check = 0; exit_check = 0; break;
		case 2: exit_check = 0; break;
		default:cout << "Wrong choise!"; break;
		}
	} while (exit_check);
}

void Add_book(Book_Data*& Books_info, long& bsize)
{
	Book_Data* temp = new Book_Data[bsize+1];

	for (int i = 0; i < bsize; i++)
	{
		temp[i] = Books_info[i];
	}

	delete[] Books_info;
	Books_info = temp;

	char buff[100];

	cout << "\n Enter Edition of book(19**,20**) - "; cin >> Books_info[bsize].Edition;

	cout << "\nEnter Name of book - "; 	cin.ignore(); cin.get(buff, 100);
	Books_info[bsize].Name = new char[strlen(buff)+1];
	strcpy(Books_info[bsize].Name, buff);
	cout << "\nEnter Author of book - "; cin.ignore(); cin.get(buff, 100);
	Books_info[bsize].Author = new char[strlen(buff)+1];
	strcpy(Books_info[bsize].Author, buff);
	cout << "\nEnter Genre of book - "; cin.ignore(); cin.get(buff, 100);
	Books_info[bsize].Genre = new char[strlen(buff)+1];
	strcpy(Books_info[bsize].Genre, buff);

	cout << "\nEnter Price of book - "; cin >> Books_info[bsize].Price;
	cout << "\nEnter Rating of the book - "; cin >> Books_info[bsize].Rating;
	cout << "\nEnter ID of book - "; cin >> Books_info[bsize].ID_of_book;
	Books_info[bsize].Popularity = 0;
	Books_info[bsize].Issuing_time = 0;

	bsize++;
}

void Delete_book(Book_Data*& Books_info, long& bsize)
{
	int delet_identifier;
	int position;
	cout << "\nEnter ID of book - "; cin >> delet_identifier;

	for(int i = 0; i < bsize; i++)
	{
		if (delet_identifier == Books_info[i].ID_of_book)
		{
			position = i;
			break;
		}
	}

	Book_Data* temp = new Book_Data[bsize - 1];

	for (int i = 0; i < bsize; i++)
	{
		if (i < position)
		{
			temp[i] = Books_info[i];
		}
		else if (i == position)
		{
			continue;
		}
		else
		{
			temp[i - 1] = Books_info[i];
		}
	}
	delete[] Books_info;
	Books_info = temp;
	bsize--;
}

void Show_books(Book_Data* Books_info, long bsize)
{
	for (int i = 0; i < bsize; i++)
	{
		cout << "\n" << Books_info[i].Edition << "\t" << Books_info[i].Name << "\t" << Books_info[i].Author << "\t" << Books_info[i].Genre << "\t" << Books_info[i].Price;
		cout << "\t" << Books_info[i].Rating << "\t" << Books_info[i].ID_of_book << "\t" << Books_info[i].Popularity << "\n";
	}
}

void Show_only_popular(Book_Data* Books_int, long bsize)
{
	int show_popular_choise;

	cout << "\nShow only popular books?\n#1 Yes\n#0 Back to book menu\n"; cin >> show_popular_choise;
	
	switch (show_popular_choise)
	{
	//Ввести после подключения базы читателей!!!!!!!!!case 1: break;
	case 0: break;
	default:cout << "Wrong choice!"; break;
	}
}

void Search_book(Book_Data* Books_info, long bsize,int search_book_choise)
{
	int concidence = 0;
	char* search_data;
	char buff[100];
	
	if (search_book_choise == 1)
	{
		cout << "\nEnter name of Author - "; cin.ignore(); cin.getline(buff, 100);
		search_data = new char[strlen(buff) + 1];
		strcpy(search_data, buff);

		for (int i = 0; i < bsize; i++)
		{
			if (strcmp(search_data, Books_info[i].Author) == 0)
			{
				cout << "\n" << Books_info[i].Edition << "\t" << Books_info[i].Name << "\t" << Books_info[i].Author << "\t" << Books_info[i].Genre << "\t" << Books_info[i].Price;
				cout << "\t" << Books_info[i].Rating << "\t" << Books_info[i].ID_of_book << "\t" << Books_info[i].Popularity << "\n";
				concidence++;
			}
			else
			{
				continue;
			}
		}
		if (concidence == 0)
		{
			cout << "\n No matches";
		}
	}
	else if (search_book_choise == 2)
	{
		cout << "\nEnter name of book - "; cin.ignore(); cin.getline(buff, 100);
		search_data = new char[strlen(buff) + 1];
		strcpy(search_data, buff);

		for (int i = 0; i < bsize; i++)
		{
			if (strcmp(search_data, Books_info[i].Name) == 0)
			{
				cout << "\n" << Books_info[i].Edition << "\t" << Books_info[i].Name << "\t" << Books_info[i].Author << "\t" << Books_info[i].Genre << "\t" << Books_info[i].Price;
				cout << "\t" << Books_info[i].Rating << "\t" << Books_info[i].ID_of_book << "\t" << Books_info[i].Popularity << "\n";
				concidence++;
			}
			else
			{
				continue;
			}
		}
		if (concidence == 0)
		{
			cout << "\n No matches";
		}
	}
	else if (search_book_choise == 3)
	{
		cout << "\nEnter genre of book - "; cin.ignore(); cin.getline(buff, 100);
		search_data = new char[strlen(buff) + 1];
		strcpy(search_data, buff);

		for (int i = 0; i < bsize; i++)
		{
			if (strcmp(search_data, Books_info[i].Genre) == 0)
			{
				cout << "\n" << Books_info[i].Edition << "\t" << Books_info[i].Name << "\t" << Books_info[i].Author << "\t" << Books_info[i].Genre << "\t" << Books_info[i].Price;
				cout << "\t" << Books_info[i].Rating << "\t" << Books_info[i].ID_of_book << "\t" << Books_info[i].Popularity << "\n";
				concidence++;
			}
			else
			{
				continue;
			}
		}
		if (concidence == 0)
		{
			cout << "\n No matches";
		}
	}
	else if (search_book_choise == 4)
	{
		cout << "\nEnter popularity of book - "; cin.ignore(); cin.getline(buff, 100);
		int popularity = atoi(buff);

		for (int i = 0; i < bsize; i++)
		{
			if (popularity == Books_info[i].Popularity)
			{
				cout << "\n" << Books_info[i].Edition << "\t" << Books_info[i].Name << "\t" << Books_info[i].Author << "\t" << Books_info[i].Genre << "\t" << Books_info[i].Price;
				cout << "\t" << Books_info[i].Rating << "\t" << Books_info[i].ID_of_book << "\t" << Books_info[i].Popularity << "\n";
				concidence++;
			}
			else
			{
				continue;
			}
		}
		if (concidence == 0)
		{
			cout << "\n No matches";
		}
	}
}

void Search_book_menu(Book_Data* Books_info, long bsize)
{
	bool search_book_exit = 1;
	int search_book_choise;
	do
	{
		cout << "\nWhat data to search?\n#1 Author\n#2 Name\n#3 Genre\n#4 Popularity\n#0 Back to book menu\n"; cin >> search_book_choise;

		switch (search_book_choise)
		{
		case 1: Search_book(Books_info, bsize, search_book_choise); break;
		case 2: Search_book(Books_info, bsize, search_book_choise); break;
		case 3: Search_book(Books_info, bsize, search_book_choise); break;
		case 4: Search_book(Books_info, bsize, search_book_choise); break;
		case 0: search_book_exit = 0; break;
		default:cout << "Wrong choise!"; break;
		}
	} while (search_book_exit);
}

void Book_menu(Book_Data*& Books_info, long& bsize, Reader_Data*& Reader_info, long& rsize)
{
	bool book_menu_exit = 1;
	int book_menu_choise;

	do
	{
		cout << "Enter choise\n#1 Show books\n#2 Book search\n#3 Sorting the list of books\n#4 Add book\n#5 Edit book\n#6 Delete book\n#7 Book Managenent\n#0 Back to main menu";
		cin >> book_menu_choise;

		switch (book_menu_choise)
		{
		case 1: Show_books(Books_info, bsize); Show_only_popular(Books_info, bsize); break;
		case 2: Search_book_menu(Books_info, bsize); break;
		case 3: break;
		case 4: cin.ignore(); Add_book(Books_info, bsize); break;
		case 5: break;
		case 6: Delete_book(Books_info, bsize); break;
		case 7: break;
		case 0: book_menu_exit = 0; break;
		default:"Wrong choice!"; break;
		}
	} while (book_menu_exit);
}

void Reader_menu(Reader_Data*& Reader_info, long& rsize, Book_Data*& Books_info, long& bsize)
{

}

int main()
{
	long bsize = 0, rsize = 0;
	int choise;
	bool check = 1;
	Book_Data* Books_info = nullptr;
	Reader_Data* Readers_info = nullptr;

	do
	{
		cout << "\t\t\t\t@Made by Kvas\n\n\n\n\n\n\n\n\n\n";
		cout << "Enter choice\n1# Working with books\n#2 Working with readers\n#3 Import all base\n#4 Export all base\n#0 Exit\n"; cin >> choise;
		switch (choise)
		{
		case 1: Book_menu(Books_info, bsize, Readers_info, rsize); break;
		case 2: Reader_menu(Readers_info, rsize, Books_info, bsize); break;
		//case 3: Import_bdata(Books_info,bsize); Import_rdata(Readers_info,rsize); break;
		//case 4: Export_bdata(Books_info, bsize); Export_rdata(Readers_info, rsize);  break;
		case 0: Exit_menu(check); break;
		default:cout << "Wrong choise!"; break;
		}

	} while (check);
}