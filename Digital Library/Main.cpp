#include <iostream>
#include <fstream>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#pragma warning(disable:4996)

using namespace std;

struct Book_Data
{
	int Edition;
	char* Name;
	char* Author;
	char* Genre;
	int Price;
	float Rating;
	int ID_of_book;
	int Popularity;
	char* Issuing_time;
	int ID_reader_who_took_the_book;
};

struct Reader_Data
{
	char* Full_name;
	char* Date_of_birth;
	int Passport_ID;
	int ID_of_user;
	int Books_read;
};

int Choice_checker()
{
	char input[5];
	int choice;

	while (!(cin >> choice) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Only numbers!!\a" << endl;
	}

	return choice;
}

void Exit_menu(bool& check)
{
	int exit;
	bool exit_check = 1;

	do
	{
		system("cls");
		cout << "\nAre you sure you want to leave?\n#1 Yes #2 No\n"; cin >> exit;

		switch (exit)
		{
		case 1: check = 0; exit_check = 0; break;
		case 2: exit_check = 0; break;
		default:cout << "Wrong choise!\a"; break;
		}
	} while (exit_check);
}

void Show_books(Book_Data* Books_info, long bsize)
{
	cout << "\nEdition\t\tName\t\tAuthor\t\tGenre\t\tPrice\t\tRating\t\tID\t\tPopularity" << "\n";

	for (int i = 0; i < bsize; i++)
	{
		cout << "\n"<< Books_info[i].Edition << "\t   " << Books_info[i].Name << "\t\t";
		cout << Books_info[i].Author << "\t\t"<< Books_info[i].Genre << "\t\t"<< Books_info[i].Price;
		cout << "\t\t" << Books_info[i].Rating << "\t\t" << Books_info[i].ID_of_book << "\t\t" << Books_info[i].Popularity <<"\n";
	}
}

void Show_readers(Reader_Data* Readers_info, long rsize)
{
	cout << "\nName\t\tDate of birth\t\tPassport ID\t\tID\t\tActivity" << "\n";
	
	for (int i = 0; i < rsize; i++)
	{
		cout << "\n" << Readers_info[i].Full_name << "\t" << Readers_info[i].Date_of_birth << "\t\t" << Readers_info[i].Passport_ID;
		cout << "\t\t\t" << Readers_info[i].ID_of_user << "\t\t" << Readers_info[i].Books_read << "\n";
	}
}

void Add_book(Book_Data*& Books_info, long& bsize)
{
	system("cls");
	Show_books(Books_info, bsize);

	bool ID_check = 1;
	int id;

	Book_Data* temp = new Book_Data[bsize+1];

	for (int i = 0; i < bsize; i++)
	{
		temp[i] = Books_info[i];
	}

	delete[] Books_info;
	Books_info = temp;

	char buff[100];

	cout << "\nEnter Name of book - "; 	cin.ignore(); cin.get(buff, 100);
	Books_info[bsize].Name = new char[strlen(buff)+1];
	strcpy(Books_info[bsize].Name, buff);
	cout << "\nEnter Edition of book(20**) - "; cin >> Books_info[bsize].Edition;
	cout << "\nEnter Author of book(Only name) - "; cin.ignore(); cin.get(buff, 100);
	Books_info[bsize].Author = new char[strlen(buff)+1];
	strcpy(Books_info[bsize].Author, buff);
	cout << "\nEnter Genre of book - "; cin.ignore(); cin.get(buff, 100);
	Books_info[bsize].Genre = new char[strlen(buff)+1];
	strcpy(Books_info[bsize].Genre, buff);

	cout << "\nEnter Price of book($) - "; Books_info[bsize].Price = Choice_checker();
	cout << "\nEnter Rating of the book(0-100) - "; Books_info[bsize].Rating = Choice_checker();
	
	do
	{
		cout << "\nEnter ID of book(177524) - "; id = Choice_checker();

		for (int i = 0; i <= bsize; i++)
		{
			if (Books_info[i].ID_of_book == id)
			{
				cout << "This ID already exists!";
				ID_check = 1;
				break;
			}
			else
			{
				ID_check = 0;
			}
		}
		if (ID_check == 0)
		{
			Books_info[bsize].ID_of_book = id;
		}
	} while (ID_check);

	Books_info[bsize].Popularity = 0;
	Books_info[bsize].ID_reader_who_took_the_book = 0;
	time_t now = time(0);
	Books_info[bsize].Issuing_time = ctime(&now);

	bsize++;
}

void Delete_book(Book_Data*& Books_info, long& bsize)
{
	int delet_identifier;
	int position = 0;
	Show_books(Books_info, bsize);
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

void Withdrawal_of_popular(Book_Data* Books_info, long bsize)
{
	char genre_for_popular[30];
	int m;
	bool popular_check = 1;

	cout << "\nIn what genre? - "; cin.ignore(); cin.getline(genre_for_popular, 30);

	for (int i = 0; i < bsize; i++)
	{
		if (strcmp(genre_for_popular, Books_info[i].Genre) == 0)
		{
			m = i;
			popular_check = 0;
			break;
		}
	}

	if (popular_check == 0)
	{
		for (int j = 0; j < bsize; j++)
		{
			if (m != j)
			{
				if (Books_info[m].Genre == Books_info[j].Genre)
				{
					if (Books_info[m].Popularity < Books_info[j].Popularity)
					{
						m = j;
					}
					else
					{
						continue;
					}
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
		cout << "\n" << Books_info[m].Edition << "\t" << Books_info[m].Name << "\t" << Books_info[m].Author << "\t" << Books_info[m].Genre << "\t" << Books_info[m].Price;
		cout << "\t" << Books_info[m].Rating << "\t" << Books_info[m].ID_of_book << "\t" << Books_info[m].Popularity << "\n";
	}
	else
	{
		cout << "\nNo matches by genre!";
	}

	cin.ignore(); cin.get();
}

void Show_only_popular(Book_Data* Books_info, long bsize)
{
	cout << "\nShow only popular books?\n#1 Yes\n#0 Back to book menu\n";
	
	switch (Choice_checker())
	{
	case 1:Withdrawal_of_popular(Books_info, bsize);  break;
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

	cin.ignore(); cin.get();
}

void Search_book_menu(Book_Data* Books_info, long bsize)
{
	bool search_book_exit = 1;
	int search_book_choise;

	do
	{
		system("cls");
		cout << "\nWhat data to search?\n#1 Author\n#2 Name\n#3 Genre\n#4 Popularity\n#0 Back to book menu\n";

		switch (search_book_choise = Choice_checker())
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

void Edit_book(Book_Data*& Books_info, long bsize,int m,int editor_choise)
{
	char buff[100];
	bool ID_check = 1;
	int id;

	if (editor_choise == 1)
	{
		cout << "\n Enter Edition of book(19**,20**) - "; cin >> Books_info[m].Edition;

		cout << "\nEnter Name of book - "; 	cin.ignore(); cin.get(buff, 100);
		Books_info[m].Name = new char[strlen(buff) + 1];
		strcpy(Books_info[m].Name, buff);
		cout << "\nEnter Author of book - "; cin.ignore(); cin.get(buff, 100);
		Books_info[m].Author = new char[strlen(buff) + 1];
		strcpy(Books_info[m].Author, buff);
		cout << "\nEnter Genre of book - "; cin.ignore(); cin.get(buff, 100);
		Books_info[m].Genre = new char[strlen(buff) + 1];
		strcpy(Books_info[m].Genre, buff);

		cout << "\nEnter Price of book - "; cin >> Books_info[m].Price;
		cout << "\nEnter Rating of the book - "; cin >> Books_info[m].Rating;
		
		do
		{
			cout << "\nEnter ID of book(177524) - "; id = Choice_checker();

			for (int i = 0; i < bsize; i++)
			{
				if (Books_info[i].ID_of_book == id)
				{
					cout << "This ID already exists!";
					ID_check = 1;
					break;
				}
				else
				{
					ID_check = 0;
				}
			}
			if (ID_check == 0)
			{
				Books_info[bsize].ID_of_book = id;
			}
		} while (ID_check);
	}
	else if (editor_choise == 2)
	{
		cout << "\nEnter Name of book - "; 	cin.ignore(); cin.get(buff, 100);
		delete Books_info[m].Name;
		Books_info[m].Name = new char[strlen(buff) + 1];
		strcpy(Books_info[m].Name, buff);
	}
	else if (editor_choise == 3)
	{
		cout << "\nEnter Author of book - "; cin.ignore(); cin.get(buff, 100);
		delete Books_info[m].Author;
		Books_info[m].Author = new char[strlen(buff) + 1];
		strcpy(Books_info[m].Author, buff);
	}
	else if (editor_choise == 4)
	{
		cout << "\nEnter Genre of book - "; cin.ignore(); cin.get(buff, 100);
		delete Books_info[m].Genre;
		Books_info[m].Genre = new char[strlen(buff) + 1];
		strcpy(Books_info[m].Genre, buff);
	}
	else if (editor_choise == 5)
	{
		cout << "\nEnter Price of book - "; cin >> Books_info[m].Price;
	}
	else if (editor_choise == 6)
	{
		cout << "\nEnter Rating of the book - "; cin >> Books_info[m].Rating;
	}
	else if (editor_choise == 7)
	{
		do
		{
			cout << "\nEnter ID of book(177524) - "; id = Choice_checker();

			for (int i = 0; i < bsize; i++)
			{
				if (Books_info[i].ID_of_book == id)
				{
					cout << "This ID already exists!";
					ID_check = 1;
					break;
				}
				else
				{
					ID_check = 0;
				}
			}
			if (ID_check == 0)
			{
				Books_info[bsize].ID_of_book = id;
			}
		} while (ID_check);
	}
	else if (editor_choise == 8)
	{
		cout << "\n Enter Edition of book(19**,20**) - "; cin >> Books_info[m].Edition;
	}

	cout << "\n" << Books_info[m].Edition << "\t" << Books_info[m].Name << "\t" << Books_info[m].Author << "\t" << Books_info[m].Genre << "\t" << Books_info[m].Price;
	cout << "\t" << Books_info[m].Rating << "\t" << Books_info[m].ID_of_book << "\t" << Books_info[m].Popularity << "\n";

	cin.ignore(); cin.get();
}

void Book_editor_menu(Book_Data*& Books_info, long bsize)
{
	int m = 0;
	int editor_choise;
	bool editor_check = 1;

	do
	{
		int position_of_book;
		system("cls");
		Show_books(Books_info, bsize);

		cout << "\nEnter ID of book - "; cin >> position_of_book;
	
		for (int i = 0; i < bsize; i++)
		{
			if (Books_info[i].ID_of_book == position_of_book)
			{
				cout << "\n" << Books_info[i].Edition << "\t" << Books_info[i].Name << "\t" << Books_info[i].Author << "\t" << Books_info[i].Genre << "\t" << Books_info[i].Price;
				cout << "\t" << Books_info[i].Rating << "\t" << Books_info[i].ID_of_book << "\t" << Books_info[i].Popularity << "\n";
				m = i;
				editor_check = 0;
				break;
			}
			else
			{
				continue;
			}
		}
		if (editor_check == 1)
		{
			cout << "Book not found\n";
		}
	} while (editor_check);

	editor_check = 1;

	do
	{
		system("cls");
		cout << "\nWhat information will be edited?\n#1 All\n#2 Name\n#3 Author\n#4 Genre\n#5 Price\n#6 Rating\n#7 ID\n#8 Edit\n#0 Back to book menu\n";

		switch (editor_choise = Choice_checker())
		{
		case 1: Edit_book(Books_info, bsize, m, editor_choise); break;
		case 2: Edit_book(Books_info, bsize, m, editor_choise); break;
		case 3: Edit_book(Books_info, bsize, m, editor_choise); break;
		case 4: Edit_book(Books_info, bsize, m, editor_choise); break;
		case 5: Edit_book(Books_info, bsize, m, editor_choise); break;
		case 6: Edit_book(Books_info, bsize, m, editor_choise); break;
		case 7: Edit_book(Books_info, bsize, m, editor_choise); break;
		case 8: Edit_book(Books_info, bsize, m, editor_choise); break;
		case 0:editor_check = 0; break;
		default: cout << "Wrong choise!"; break;
		}
	} while (editor_check);
}

void Sort_books(Book_Data* Books_info, long bsize, int book_sort_menu_choice)
{
	if (book_sort_menu_choice == 1)
	{
		for (int i = 0; i < bsize; i++)
		{
			for (int j = 0; j < bsize - 1; j++)
			{
				int one = Books_info[j].Author[0];
				int two = Books_info[j + 1].Author[0];

				if (one > two)
				{
					swap(Books_info[j], Books_info[j + 1]);
				}
				else
				{
					continue;
				}
			}
		}
	}
	else if (book_sort_menu_choice == 2)
	{
		for (int i = 0; i < bsize; i++)
		{
			for (int j = 0; j < bsize; j++)
			{
				int one = Books_info[j].Name[0];
				int two = Books_info[j + 1].Name[0];

				if (one > two)
				{
					swap(Books_info[j], Books_info[j + 1]);
				}
				else
				{
					continue;
				}
			}
		}
	}
	else if (book_sort_menu_choice == 3)
	{
		for (int i = 0; i < bsize; i++)
		{
			for (int j = 0; j < bsize; j++)
			{
				int one = Books_info[j].Genre[0];
				int two = Books_info[j + 1].Genre[0];

				if (one > two)
				{
					swap(Books_info[j], Books_info[j + 1]);
				}
				else
				{
					continue;
				}
			}
		}
	}
	else if (book_sort_menu_choice == 4)
	{
		for (int i = 0; i < bsize; i++)
		{
			for (int j = 0; j < bsize; j++)
			{
				if (Books_info[j].Popularity > Books_info[j].Popularity)
				{
					swap(Books_info[j], Books_info[j + 1]);
				}
				else
				{
					continue;
				}
			}
		}
	}
}

void Sort_books_menu(Book_Data* Books_info, long bsize)
{
	bool book_sort_menu_exit = 1;
	int book_sort_menu_choice;

	do
	{
		system("cls");
		Show_books(Books_info, bsize);

		cout << "\nWhat are the criteria for sorting?\n1# Author\n2# Name\n3# Genre\n#4 Popularity\n#0 Back to book menu\n";

		switch (book_sort_menu_choice = Choice_checker())
		{
		case 1: Sort_books(Books_info, bsize, book_sort_menu_choice); break;
		case 2: Sort_books(Books_info, bsize, book_sort_menu_choice); break;
		case 3: Sort_books(Books_info, bsize, book_sort_menu_choice); break;
		case 4: Sort_books(Books_info, bsize, book_sort_menu_choice); break;
		case 0: book_sort_menu_exit = 0; break;
		default: cout << "Wrong choice!"; break;
		}
	} while (book_sort_menu_exit);
	
}

void Show_borrowed_books(Book_Data* Books_info,long bsize,Reader_Data* Readers_info,long rsize)
{
	for (int i = 0; i < bsize; i++)
	{
		if (Books_info[i].ID_reader_who_took_the_book > 0)
		{
			cout << "\nDate of issue - "<<Books_info[i].Issuing_time<<"\n";
			cout << "\n" << Books_info[i].Name << "\t" << Books_info[i].Author << "\t" << Books_info[i].Genre << "\t";
			cout << Books_info[i].ID_of_book <<"\t-->\t";

			for (int j = 0; j < rsize; j++)
			{
				if (Readers_info[j].ID_of_user == Books_info[i].ID_reader_who_took_the_book)
				{
					cout << Readers_info[j].Full_name << "\t" << Readers_info[j].ID_of_user<<"\n";
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
	}

	cin.ignore(); cin.get();
}

void Issuing_book(Book_Data*& Books_info, long bsize, Reader_Data*& Readers_info, long rsize)
{
	int ID_of_book;
	int ID_of_reader;
	bool issung_check = 1;
	bool search_check = 1;

	Show_books(Books_info, bsize);
	do
	{
		cout << "\nEnter ID of book for issuing - "; cin >> ID_of_book;

		for (int i = 0; i < bsize; i++)
		{
			if (Books_info[i].ID_of_book == ID_of_book)
			{
				if (Books_info[i].ID_reader_who_took_the_book > 0)
				{
					search_check = 0;
				}
				else
				{
					issung_check = 0;
					ID_of_book = i;
					break;
				}
			}
			else
			{
				continue;
			}
		}
		if (search_check == 0)
		{
			cout << "The book is already with the reader!";
		}
		else if (issung_check == 1)
		{
			cout << "The book could not be found. Please enter a valid ID";
		}
		else
		{
			continue;
		}

	} while (issung_check);

	issung_check = 1;

	Show_readers(Readers_info, rsize);

	do
	{
		cout << "\nEnter ID of reader - "; ID_of_reader = Choice_checker();
		
		for (int i = 0; i < rsize; i++)
		{
			if (Readers_info[i].ID_of_user == ID_of_reader)
			{
				ID_of_reader = i;
				issung_check = 0;
				break;
			}
			else
			{
				continue;
			}
		}

		if (issung_check == 1)
		{
			cout << "Failed to find reader, please enter valid ID";
		}

	} while (issung_check);

	time_t now = time(0);

	Books_info[ID_of_book].ID_reader_who_took_the_book = Readers_info[ID_of_reader].ID_of_user;
	Books_info[ID_of_book].Issuing_time = ctime(&now);
	Books_info[ID_of_book].Popularity++;
	Readers_info[ID_of_reader].Books_read++;

	Show_borrowed_books(Books_info, bsize, Readers_info, rsize);
}

void Book_return(Book_Data*& Books_info, long bsize, Reader_Data*& Readers_info, long rsize)
{
	Show_borrowed_books(Books_info, bsize, Readers_info, rsize);

	bool book_return_check = 1;
	int ID_of_book;

	cout << "\nEnter ID of book to return - "; ID_of_book = Choice_checker();

	for (int i = 0; i < bsize; i++)
	{
		if (Books_info[i].ID_of_book == ID_of_book)
		{
			if (Books_info[i].ID_reader_who_took_the_book > 0)
			{
				Books_info[i].ID_reader_who_took_the_book = 0;
				book_return_check = 0;
			}
			else
			{
				continue;
			}
		}
	}
	if (book_return_check == 1)
	{
		cout << "Book not found or book not taken";
	}
	else
	{
		cout<< "Book successfully returned";
	}

	cin.ignore(); cin.get();
}

void Book_menegment_menu(Book_Data*& Books_info,long bsize,Reader_Data*& Readers_info,long rsize)
{
	bool book_menegment_menu_exit = 1;

	do
	{
		system("cls");
		cout << "\nEnter choice\n#1 Displaying a list of borrowed books\n#2 Give out a book\n#3 Return a book\n#0 Back to book menu\n";

		switch (Choice_checker())
		{
		case 1: Show_borrowed_books(Books_info, bsize, Readers_info, rsize); break;
		case 2: Issuing_book(Books_info, bsize, Readers_info, rsize); break;
		case 3: Book_return(Books_info, bsize, Readers_info, rsize); break;
		case 0: book_menegment_menu_exit = 0; break;
		default: cout << "Wrong choice!\a"; break;
		}
	} while (book_menegment_menu_exit);
}

void Book_menu(Book_Data*& Books_info, long& bsize, Reader_Data*& Readers_info, long& rsize)
{
	bool book_menu_exit = 1;

	do
	{
		system("cls");
		cout << "\n\n\n\t\t\t\t\t\tBook menu\n\n";
		cout << "\nEnter choise\n#1 Show books\n#2 Book search\n#3 Sorting the list of books\n#4 Add book\n#5 Edit book\n#6 Delete book\n#7 Book Managenent\n#0 Back to main menu\n";

		switch (Choice_checker())
		{
		case 1: Show_books(Books_info, bsize); Show_only_popular(Books_info, bsize); break;
		case 2: Search_book_menu(Books_info, bsize); break;
		case 3: Sort_books_menu(Books_info, bsize); break;
		case 4: Add_book(Books_info, bsize); break;
		case 5: Book_editor_menu(Books_info, bsize); break;
		case 6: Delete_book(Books_info, bsize); break;
		case 7: Book_menegment_menu(Books_info, bsize, Readers_info, rsize); break;
		case 0: book_menu_exit = 0; break;
		default:"Wrong choice!\a"; break;
		}
	} while (book_menu_exit);
}

void Only_popylar_readers(Reader_Data* Readers_info, long rsize)
{
	Reader_Data* temp = new Reader_Data[rsize];

	for (int i = 0; i < rsize; i++)
	{

		temp[i] = Readers_info[i];
	}

	for (int i = 0; i < rsize; i++)
	{
		for (int j = 0; j < rsize-1; j++)
		{
			if (temp[j].Books_read > temp[j + 1].Books_read)
			{
				swap(temp[j], temp[j + 1]);
			}
		}
	}

	for (int i = 0; i < rsize/2; i++)
	{
		cout << "\n" << temp[i].Full_name << "\t" << temp[i].Date_of_birth << "\t" << temp[i].Passport_ID << "\t" << temp[i].ID_of_user << "\t" << temp[i].Books_read<<"\n";
	}

	cin.ignore(); cin.get();
}

void Show_only_active_readers_menu(Reader_Data* Readers_info, long rsize)
{
	cout << "\nShow only active readers?\n#1 Yes\n#0 Back to readers menu\n";

	switch (Choice_checker())
	{
	case 1: Only_popylar_readers(Readers_info, rsize); break;
	case 0: break;
	default: cout << "Wrong choice!\a"; break;
	}
}

void Add_reader(Reader_Data*& Readers_info, long& rsize)
{
	bool ID_checker = 1;
	int id;

	Reader_Data* temp = new Reader_Data[rsize + 1];

	for (int i = 0; i < rsize; i++)
	{
		temp[i] = Readers_info[i];
	}

	delete[] Readers_info;
	Readers_info = temp;

	char buff[100];
	int m = 0;

	cout << "\nEnter Full name of reader - "; cin.ignore(); cin.get(buff, 100);
	Readers_info[rsize].Full_name = new char[strlen(buff) + 1];

	for (int i = 0; i < strlen(buff); i++)
	{
		if (i > 0 && isupper(buff[i]))
		{
			break;
		}
		Readers_info[rsize].Full_name[m] = buff[i];
		m++;
	}

	for (int i = 1; i < strlen(buff); i++)
	{
		if (isupper(buff[i]))
		{
			Readers_info[rsize].Full_name[m] = buff[i];
			m++;
			Readers_info[rsize].Full_name[m] = '.';
			m++;
		}
	}

	Readers_info[rsize].Full_name[m] = '\0';

	cout << "\nEnter date of birth(22.04.2000) - "; cin.ignore(); cin.get(buff, 100);
	Readers_info[rsize].Date_of_birth = new char[strlen(buff) + 1];
	strcpy(Readers_info[rsize].Date_of_birth, buff);
	cout << "\nEnter ID of passport - "; Readers_info[rsize].Passport_ID = Choice_checker();
	
	do
	{
		cout << "\nEnter ID of reader - "; id = Choice_checker();

		for (int i = 0; i <= rsize; i++)
		{
			if (Readers_info[i].ID_of_user == id)
			{
				cout << "This ID already exists!";
				ID_checker = 1;
				break;
			}
			else
			{
				ID_checker = 0;
			}
		}
		if (ID_checker == 0)
		{
			Readers_info[rsize].ID_of_user = id;
		}
	} while (ID_checker);

	Readers_info[rsize].Books_read = 0;

	rsize++;
}

void Delete_reader(Reader_Data*& Readers_info, long& rsize,Book_Data* Books_info,long bsize)
{
	Show_readers(Readers_info, rsize);
	
	int delete_id,positiion_of_delete;
	bool delete_check = 1;

	cout << "\nEnter ID of reader - "; cin >> delete_id;

	for (int i = 0; i < rsize; i++)
	{
		if (Readers_info[i].ID_of_user == delete_id)
		{
			for (int j = 0; j <= bsize; j++)
			{
				if (Books_info[j].ID_reader_who_took_the_book==delete_id)
				{
					cout << "Before deleting a reader, you must return the book!\a";
					cin.ignore(); cin.get();
					delete_check = 1;
					break;
				}
				else
				{
					positiion_of_delete = i;
					delete_check = 0;
				}
			}
		}
	}

	if (delete_check == 0)
	{
		Reader_Data* temp = new Reader_Data[rsize - 1];

		for (int i = 0; i < rsize; i++)
		{
			if (i < positiion_of_delete)
			{
				temp[i] = Readers_info[i];
			}
			else if (i == positiion_of_delete)
			{
				continue;
			}
			else
			{
				temp[i - 1] = Readers_info[i];
			}
		}
		delete[] Readers_info;
		Readers_info = temp;
		rsize--;
	}
	else
	{
		cout << "\nUser is not found";
	}
}

void Reader_Serch(Reader_Data* Readers_info, long rsize, int reader_serch_choise)
{
	Show_readers(Readers_info, rsize);

	int intbuff;
	char buff[100];
	bool serch_check = 1;

	if (reader_serch_choise == 1)
	{
		cout << "\nEnter full name - "; cin.ignore(); cin.get(buff, 100);

		for (int i = 0; i < rsize; i++)
		{
			if (strcmp(strtok(Readers_info[i].Full_name, " "), strtok(buff, " ")) == 0)
			{
				cout << "\n" << Readers_info[i].Full_name << "\t" << Readers_info[i].Date_of_birth << "\t" << Readers_info[i].Passport_ID;
				cout << "\t" << Readers_info[i].ID_of_user << "\t" << Readers_info[i].Books_read << "\n";
				serch_check = 0;
				break;
			}
			else
			{
				continue;
			}
		}
	}
	else if (reader_serch_choise == 2)
	{
		cout << "\nEnter number of readed books - "; cin >> intbuff;

		for (int i = 0; i < rsize; i++)
		{
			if (Readers_info[i].Books_read == intbuff)
			{
				cout << "\n" << Readers_info[i].Full_name << "\t" << Readers_info[i].Date_of_birth << "\t" << Readers_info[i].Passport_ID;
				cout << "\t" << Readers_info[i].ID_of_user << "\t" << Readers_info[i].Books_read << "\n";
				serch_check = 0;
			}
			else
			{
				continue;
			}
		}

	}
	else if (reader_serch_choise == 3)
	{
		cout << "\nEnter ID of reader - "; intbuff = Choice_checker();

		for (int i = 0; i < rsize; i++)
		{
			if (Readers_info[i].ID_of_user == intbuff)
			{
				cout << "\n" << Readers_info[i].Full_name << "\t" << Readers_info[i].Date_of_birth << "\t" << Readers_info[i].Passport_ID;
				cout << "\t" << Readers_info[i].ID_of_user << "\t" << Readers_info[i].Books_read << "\n";
				serch_check = 0;
				break;
			}
			else
			{
				continue;
			}
		}
	}
	else if (reader_serch_choise == 4)
	{
		cout << "\nEnter passport ID of reader - "; intbuff = Choice_checker();

		for (int i = 0; i < rsize; i++)
		{
			if (Readers_info[i].Passport_ID == intbuff)
			{
				cout << "\n" << Readers_info[i].Full_name << "\t" << Readers_info[i].Date_of_birth << "\t" << Readers_info[i].Passport_ID;
				cout << "\t" << Readers_info[i].ID_of_user << "\t" << Readers_info[i].Books_read << "\n";
				serch_check = 0;
				break;
			}
			else
			{
				continue;
			}
		}
	}

	if (serch_check == 1)
	{
		cout << "\nReader not found";
	}

	cin.ignore(); cin.get();
}

void Reader_Search_menu(Reader_Data* Readers_info, long rsize)
{
	bool reader_serch_menu_exit = 1;
	int reader_serch_menu_choise;

	do
	{
		system("cls");
		cout << "\nBy what criteria to search?\n#1 Full Name\n#2 Number of books read\n#3 ID\n#4 Passport ID\n#0 Back to reader menu\n";

		switch (reader_serch_menu_choise = Choice_checker())
		{
		case 1: Reader_Serch(Readers_info, rsize, reader_serch_menu_choise); break;
		case 2: Reader_Serch(Readers_info, rsize, reader_serch_menu_choise); break;
		case 3: Reader_Serch(Readers_info, rsize, reader_serch_menu_choise); break;
		case 4: Reader_Serch(Readers_info, rsize, reader_serch_menu_choise); break;
		case 0: reader_serch_menu_exit = 0; break;
		default: cout << "\nWrong choice!"; break;
		}
	} while (reader_serch_menu_exit);
}

void Reader_Sort(Reader_Data*& Readers_info, long& rsize,int reader_sort_choise)
{
	if (reader_sort_choise == 1)
	{
		for (int i = 0; i < rsize; i++)
		{
			for (int j = 0; j < rsize - 1; j++)
			{
				int one = Readers_info[j].Full_name[0];
				int two = Readers_info[j + 1].Full_name[0];

				if (one > two)
				{
					swap(Readers_info[j], Readers_info[j + 1]);
				}
				else
				{
					continue;
				}
			}
		}
	}
	else if (reader_sort_choise == 2)
	{
		for (int i = 0; i < rsize; i++)
		{
			for (int j = 0; j < rsize - 1; j++)
			{
				if (Readers_info[j].Books_read < Readers_info[j + 1].Books_read)
				{
					swap(Readers_info[j], Readers_info[j + 1]);
				}
				else
				{
					continue;
				}
			}
		}
	}
	else if (reader_sort_choise == 3)
	{
		for (int i = 0; i < rsize; i++)
		{
			for (int j = 0; j < rsize - 1; j++)
			{
				if (Readers_info[j].ID_of_user < Readers_info[j + 1].ID_of_user)
				{
					swap(Readers_info[j], Readers_info[j + 1]);
				}
				else
				{
					continue;
				}
			}
		}
	}
	else if (reader_sort_choise == 4)
	{
		for (int i = 0; i < rsize; i++)
		{
			for (int j = 0; j < rsize - 1; j++)
			{
				if (Readers_info[j].Passport_ID < Readers_info[j + 1].Passport_ID)
				{
					swap(Readers_info[j], Readers_info[j + 1]);
				}
				else
				{
					continue;
				}
			}
		}
	}

	Show_readers(Readers_info, rsize);
	cin.ignore(); cin.get();
}

void Reader_Sort_menu(Reader_Data* Readers_info,long rsize)
{
	bool reader_sort_menu_exit = 1;
	int reader_sort_menu_choise;

	do
	{
		system("cls");
		cout << "\nSelect sort criteria\n1# Full name\n#2 Number of books read\n#3 ID\n#4 Passport ID\n#0 Back to reader menu\n";

		switch (reader_sort_menu_choise = Choice_checker())
		{
		case 1: Reader_Sort(Readers_info, rsize, reader_sort_menu_choise); break;
		case 2: Reader_Sort(Readers_info, rsize, reader_sort_menu_choise); break;
		case 3: Reader_Sort(Readers_info, rsize, reader_sort_menu_choise); break;
		case 4: Reader_Sort(Readers_info, rsize, reader_sort_menu_choise); break;
		case 0: reader_sort_menu_exit = 0; break;
		default: cout << "\nWrong choice!"; break;
		}

	} while (reader_sort_menu_exit);
}

void Reader_edit(Reader_Data*& Readers_info, long rsize,Book_Data* Books_info, long bsize, int reader_edit_choice, int ID_of_reader)
{
	char buff[100];
	bool ID_checker = 1;
	int id;

	if (reader_edit_choice == 1)
	{
		int m = 0;

		cout << "\nEnter Full name of reader - "; cin.ignore(); cin.get(buff, 100);
		Readers_info[ID_of_reader].Full_name = new char[strlen(buff) + 1];

		for (int i = 0; i < strlen(buff); i++)
		{
			if (i > 0 && isupper(buff[i]))
			{
				break;
			}
			Readers_info[ID_of_reader].Full_name[m] = buff[i];
			m++;
		}

		for (int i = 1; i < strlen(buff); i++)
		{
			if (isupper(buff[i]))
			{
				Readers_info[ID_of_reader].Full_name[m] = buff[i];
				m++;
				Readers_info[ID_of_reader].Full_name[m] = '.';
				m++;
			}
		}

		Readers_info[ID_of_reader].Full_name[m] = '\0';

		cout << "\nEnter date of birth(22.04.2000) - "; cin.ignore(); cin.get(buff, 100);
		Readers_info[ID_of_reader].Date_of_birth = new char[strlen(buff) + 1];
		strcpy(Readers_info[ID_of_reader].Date_of_birth, buff);
		cout << "\nEnter ID of passport - "; Readers_info[ID_of_reader].Passport_ID = Choice_checker();
		
		do
		{
			cout << "\nEnter ID of reader - "; id = Choice_checker();

			for (int i = 0; i <= rsize; i++)
			{
				if (Readers_info[i].ID_of_user == id)
				{
					cout << "This ID already exists!";
					ID_checker = 1;
					break;
				}
				else
				{
					ID_checker = 0;
				}
			}

			if (ID_checker == 0)
			{
				for (int i = 0; i <= bsize; i++)
				{
					if (Books_info[i].ID_reader_who_took_the_book == Readers_info[ID_of_reader].ID_of_user)
					{
						Books_info[i].ID_reader_who_took_the_book = id;
						Readers_info[ID_of_reader].ID_of_user = id;
					}
				}
			}
		} while (ID_checker);
	}
	else if (reader_edit_choice == 2)
	{
		cout << "\nEnter full name - "; cin.ignore(); cin.get(buff, 100);
		strcpy(Readers_info[ID_of_reader].Full_name, buff);
	}
	else if (reader_edit_choice == 3)
	{
		cout << "\nEnter date of birth(22.04.2000) - "; cin.ignore(); cin.get(buff, 100);
		strcpy(Readers_info[ID_of_reader].Date_of_birth, buff);
	}
	else if (reader_edit_choice == 4)
	{
		cout << "\nEnter passport ID - "; Readers_info[ID_of_reader].Passport_ID = Choice_checker();
	}
	else if (reader_edit_choice == 5)
	{
		do
		{
			cout << "\nEnter ID of reader - "; id = Choice_checker();

			for (int i = 0; i <= rsize; i++)
			{
				if (Readers_info[i].ID_of_user == id)
				{
					cout << "This ID already exists!";
					ID_checker = 1;
					break;
				}
				else
				{
					ID_checker = 0;
				}
			}
			
			if (ID_checker == 0)
			{
				for (int i = 0; i <= bsize; i++)
				{
					if (Books_info[i].ID_reader_who_took_the_book == Readers_info[ID_of_reader].ID_of_user)
					{
						Books_info[i].ID_reader_who_took_the_book = id;
						Readers_info[ID_of_reader].ID_of_user = id;
					}
				}
			}
		} while (ID_checker);
	}
}

void Reader_edit_menu(Reader_Data*& Readers_info, long rsize,Book_Data* Books_info,long bsize)
{
	int ID_of_reader;
	int reader_edit_choice;
	bool reader_edit_exit = 1;

	Show_readers(Readers_info, rsize);

	do
	{
		cout << "\nEnter ID of reader - "; ID_of_reader = Choice_checker();

		for (int i = 0; i < rsize; i++)
		{
			if (Readers_info[i].ID_of_user == ID_of_reader)
			{
				cout << "\n" << Readers_info[i].Full_name << "\t" << Readers_info[i].Date_of_birth << "\t" << Readers_info[i].Passport_ID;
				cout << "\t" << Readers_info[i].ID_of_user << "\t" << Readers_info[i].Books_read << "\n";
				ID_of_reader = i;
				reader_edit_exit = 0;
				break;
			}
		}
		if (reader_edit_exit == 1)
		{
			cout << "Reader not found";
		}
	} while (reader_edit_exit);

	reader_edit_exit = 1;

	do
	{
		cout << "\nWhat will we edit?\n1# All information\n#2 Full name\n#3 Date of birth\n#4 Passport ID\n#5 ID of reader\n#0 Back to reader menu\n";

		switch (reader_edit_choice = Choice_checker())
		{
		case 1: Reader_edit(Readers_info, rsize, Books_info, bsize, reader_edit_choice, ID_of_reader); break;
		case 2: Reader_edit(Readers_info, rsize, Books_info, bsize, reader_edit_choice, ID_of_reader); break;
		case 3: Reader_edit(Readers_info, rsize, Books_info, bsize, reader_edit_choice, ID_of_reader); break;
		case 4: Reader_edit(Readers_info, rsize, Books_info, bsize, reader_edit_choice, ID_of_reader); break;
		case 5: Reader_edit(Readers_info, rsize, Books_info, bsize, reader_edit_choice, ID_of_reader); break;
		case 0: reader_edit_exit = 0; break;
		default: cout << "Wrong choice!"; break;
		}
	} while (reader_edit_exit);
}
//ÏÅÐÅÄÅËÀÒÜ ÝÒÓ ÑÒÛÄÎÁÓ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void Readers_overdue_return_date(Reader_Data* Readers_info, long rsize, Book_Data* Books_info, long bsize)
{
	char buff[100];
	int data1;
	int data2;

	for (int i = 0; i < bsize; i++)
	{
		if (Books_info[i].ID_reader_who_took_the_book > 0)
		{
			for (int j = 0; j < rsize; j++)
			{
				if (Books_info[i].ID_reader_who_took_the_book == Readers_info[j].ID_of_user)
				{
					strcpy(buff,Books_info[i].Issuing_time);
					strtok(buff, " ");
					strtok(NULL, " ");
					data1 = atoi(strtok(NULL, " "));

					time_t now = time(0);
					char* time = ctime(&now);
					strtok(time, " ");
					strtok(NULL, " ");
					data2 = atoi(strtok(NULL, " "));

					if (data1 + 1 < data2)
					{
						cout << "RETURN DATE OVERDUE\n";
						cout << Readers_info[j].Full_name << "\t" << Readers_info[j].ID_of_user << "\t<--\t" << Books_info[i].Name << "\t";
						cout << Books_info[i].Author << "\t" << Books_info[i].ID_of_book<<"\n";
					}
					else
					{
						continue;
					}
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
	}

	cin.ignore(); cin.get();
}

void Reader_menu(Reader_Data*& Readers_info, long& rsize, Book_Data*& Books_info, long& bsize)
{
	bool reader_menu_exit = 1;

	do
	{
		system("cls");
		cout << "\n\n\n\t\t\t\t\t\tReaders menu\n\n";
		cout << "\nEnter choise\n#1 Show reader\n#2 Reader search\n#3 Sorting the list of readers\n#4 Add reader\n#5 Edit reader info\n#6 Delete reader\n";
		cout << "#7 List of readers with an overdue return date\n#0 Back to main menu\n";

		switch (Choice_checker())
		{
		case 1: Show_readers(Readers_info, rsize); Show_only_active_readers_menu(Readers_info, rsize); break;
		case 2: Reader_Search_menu(Readers_info, rsize); break;
		case 3: Reader_Sort_menu(Readers_info, rsize); break;
		case 4: Add_reader(Readers_info, rsize); break;
		case 5: Reader_edit_menu(Readers_info, rsize,Books_info,bsize); break;
		case 6: Delete_reader(Readers_info, rsize,Books_info,bsize); break;
		case 7: Readers_overdue_return_date(Readers_info, rsize, Books_info, bsize); break;
		case 0: reader_menu_exit = 0; break;
		default: cout << "\nWrong choise!"; break;
		}
	} while (reader_menu_exit);
}

void Import_readers_base(Reader_Data*& Readers_info, long& rsize)
{
	char buff[300];
	char* temp;

	ifstream impreader("C:/CPP/Digital Library/Base/Reader_list.txt");
	if (!impreader)
	{
		cout << "Saved readers base not found. Loading a clean library...";
		cin.get();
	}
	else
	{
		while (impreader)
		{
			impreader.getline(buff, 300);
			rsize++;
		}
		rsize--;

		impreader.close();
		Readers_info = new Reader_Data[rsize];
		impreader.open("C:/CPP/Digital Library/Base/Reader_list.txt");

		for (int i = 0; i < rsize; i++)
		{
			impreader.getline(buff, 300);
			temp = strtok(buff, "#");
			Readers_info[i].Full_name = new char[strlen(temp) + 1];
			strcpy(Readers_info[i].Full_name, temp);
			temp = strtok(NULL, "#");
			Readers_info[i].Date_of_birth = new char[strlen(temp) + 1];
			strcpy(Readers_info[i].Date_of_birth, temp);
			Readers_info[i].Passport_ID = atoi(strtok(NULL, "#"));
			Readers_info[i].ID_of_user = atoi(strtok(NULL, "#"));
			Readers_info[i].Books_read = atoi(strtok(NULL, "#"));
		}
		impreader.close();
	}
}


void Import_book_base(Book_Data*& Books_info, long& bsize)
{
	char buff[300];
	char* temp;

	ifstream impbook("C:/CPP/Digital Library/Base/Book_list.txt");
	if (!impbook)
	{
		cout << "\nSaved book base not found. Loading a clean library...";
		cin.get();
	}
	else
	{
		while (impbook)
		{
			impbook.getline(buff, 300);
			bsize++;
		}
		bsize--;

		impbook.close();
		Books_info = new Book_Data[bsize];
		impbook.open("C:/CPP/Digital Library/Base/Book_list.txt");

		for (int i = 0; i < bsize; i++)
		{
			impbook.getline(buff, 300);
			Books_info[i].Edition = atoi(strtok(buff, "#"));
			temp = strtok(NULL, "#");
			Books_info[i].Name = new char[strlen(temp) + 1];
			strcpy(Books_info[i].Name, temp);
			temp = strtok(NULL, "#");
			Books_info[i].Author = new char[strlen(temp) + 1];
			strcpy(Books_info[i].Author, temp);
			temp = strtok(NULL, "#");
			Books_info[i].Genre = new char[strlen(temp) + 1];
			strcpy(Books_info[i].Genre, temp);
			Books_info[i].Price = atoi(strtok(NULL, "#"));
			Books_info[i].Rating = atoi(strtok(NULL, "#"));
			Books_info[i].ID_of_book = atoi(strtok(NULL, "#"));
			Books_info[i].Popularity = atoi(strtok(NULL, "#"));
			Books_info[i].ID_reader_who_took_the_book = atoi(strtok(NULL, "#"));
			temp = strtok(NULL, "#");
			Books_info[i].Issuing_time = new char[strlen(temp)+1];
			strcpy(Books_info[i].Issuing_time, temp);
		}
		impbook.close();
	}

}

void Export_book_base(Book_Data* Books_info, long bsize)
{
	ofstream exbook("C:/CPP/Digital Library/Base/Book_list.txt");

	for (int i = 0; i < bsize; i++)
	{
		exbook <<Books_info[i].Edition<<"#"<< Books_info[i].Name << "#" << Books_info[i].Author << "#" << Books_info[i].Genre << "#" << Books_info[i].Price << "#" << Books_info[i].Rating << "#";
		exbook << Books_info[i].ID_of_book << "#" << Books_info[i].Popularity << "#"<< Books_info[i].ID_reader_who_took_the_book<<"#"<< Books_info[i].Issuing_time<<"#\n";
	}
	exbook.close();
}

void Export_readers_base(Reader_Data* Readers_info, long rsize)
{
	ofstream exreader("C:/CPP/Digital Library/Base/Reader_list.txt");

	for (int i = 0; i < rsize; i++)
	{
		exreader << Readers_info[i].Full_name << "#" << Readers_info[i].Date_of_birth << "#" << Readers_info[i].Passport_ID << "#"; 
		exreader << Readers_info[i].ID_of_user << "#" << Readers_info[i].Books_read<<"#\n";
	}
	exreader.close();
}

int main()
{
	long bsize = 0, rsize = 0;
	bool check = 1;
	Book_Data* Books_info = nullptr;
	Reader_Data* Readers_info = nullptr;
	
	Import_readers_base(Readers_info, rsize);
	Import_book_base(Books_info, bsize);

	do
	{
		system("cls");
		cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t@Made by Kvas\n\n\n\n\n\n\n\n\n\n";
		cout << "\t\t\t\t\t\tDIGITAL LIBRARY\n\n";
		cout << "\nEnter choice\n1# Working with books\n2# Working with readers\n0# Exit\n";
		switch (Choice_checker())
		{
		case 1: Book_menu(Books_info, bsize, Readers_info, rsize); break;
		case 2: Reader_menu(Readers_info, rsize, Books_info, bsize); break;
		case 0: Exit_menu(check); break;
		default:cout << "Wrong choise!\a"; cin.ignore(); cin.get(); break;
		}

	} while (check);

	Export_book_base(Books_info, bsize);
	Export_readers_base(Readers_info, rsize);
}