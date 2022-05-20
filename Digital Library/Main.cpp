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
	char* Date_of_birth;
	int Passport_ID;
	int ID_of_user;
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

void Show_books(Book_Data* Books_info, long bsize)
{
	for (int i = 0; i < bsize; i++)
	{
		cout << "\n" << Books_info[i].Edition << "\t" << Books_info[i].Name << "\t" << Books_info[i].Author << "\t" << Books_info[i].Genre << "\t" << Books_info[i].Price;
		cout << "\t" << Books_info[i].Rating << "\t" << Books_info[i].ID_of_book << "\t" << Books_info[i].Popularity << "\n";
	}
}

void Add_book(Book_Data*& Books_info, long& bsize)
{
	Show_books(Books_info, bsize);

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

//œ–Œ¬≈–»“‹ –¿¡Œ“” ‘”Õ ÷»» œŒ—À≈ ¬¬≈ƒ≈Õ»≈ œŒÀ‹«Œ¬¿“≈À≈… — + —◊≈“◊» ŒÃ œŒœ”Àﬂ–ÕŒ—“»
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
}

void Show_only_popular(Book_Data* Books_info, long bsize)
{
	int show_popular_choise;

	cout << "\nShow only popular books?\n#1 Yes\n#0 Back to book menu\n"; cin >> show_popular_choise;
	
	switch (show_popular_choise)
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

void Edit_book(Book_Data*& Books_info, long bsize,int m,int editor_choise)
{
	char buff[100];
	int number_buff;

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
		cout << "\nEnter ID of book - "; cin >> Books_info[m].ID_of_book;
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
	//Œ◊≈Õ‹ ¬¿∆ÕŒ!!!!!!! ID —¬ﬂ«¿Õ — ¡¿«Œ… ◊»“¿“≈À≈….  Œ√ƒ¿ —ƒ≈À¿ﬁ ¡¿«”, —ƒ≈—‹ Õ”∆ÕŒ ƒŒ¡¿¬»“‹ ¬Õ≈—≈Õ»≈ »«Ã≈Õ≈Õ»… ¿¬“ŒÃ¿“»◊≈— » ¬ ¡¿«≈ œŒÀ‹«Œ¬¿“≈À≈…
	//≈—À» ” Õ≈√Œ ›“¿  Õ»√¿ Õ¿ –” ¿’!!!!!!!!!!!!!!!!!!!!!!
	else if (editor_choise == 7)
	{
		cout << "\nEnter ID of book - "; cin >> Books_info[m].ID_of_book;
	}
	else if (editor_choise == 8)
	{
		cout << "\n Enter Edition of book(19**,20**) - "; cin >> Books_info[m].Edition;
	}

	cout << "\n" << Books_info[m].Edition << "\t" << Books_info[m].Name << "\t" << Books_info[m].Author << "\t" << Books_info[m].Genre << "\t" << Books_info[m].Price;
	cout << "\t" << Books_info[m].Rating << "\t" << Books_info[m].ID_of_book << "\t" << Books_info[m].Popularity << "\n";
}

void Book_editor_menu(Book_Data*& Books_info, long bsize)
{
	int m = 0;
	int editor_choise;
	bool editor_check = 1;

	do
	{
		int position_of_book;
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
		cout << "\nWhat information will be edited?\n#1 All\n#2 Name\n#3 Author\n#4 Genre\n#5 Price\n#6 Rating\n#7 ID\n#8 Edit\n#0 Back to book menu\n"; cin >> editor_choise;

		switch (editor_choise)
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
		Show_books(Books_info, bsize);

		cout << "\nWhat are the criteria for sorting?\n1# Author\n2# Name\n3# Genre\n#4 Popularity\n#0 Back to book menu\n"; cin >> book_sort_menu_choice;

		switch (book_sort_menu_choice)
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


void Book_menu(Book_Data*& Books_info, long& bsize, Reader_Data*& Readers_info, long& rsize)
{
	bool book_menu_exit = 1;
	int book_menu_choise;

	do
	{
		cout << "\nEnter choise\n#1 Show books\n#2 Book search\n#3 Sorting the list of books\n#4 Add book\n#5 Edit book\n#6 Delete book\n#7 Book Managenent\n#0 Back to main menu\n";
		cin >> book_menu_choise;

		switch (book_menu_choise)
		{
		case 1: Show_books(Books_info, bsize); Show_only_popular(Books_info, bsize); break;
		case 2: Search_book_menu(Books_info, bsize); break;
		case 3: Sort_books_menu(Books_info, bsize); break;
		case 4: cin.ignore(); Add_book(Books_info, bsize); break;
		case 5: Book_editor_menu(Books_info, bsize); break;
		case 6: Delete_book(Books_info, bsize); break;
		case 7: break;
		case 0: book_menu_exit = 0; break;
		default:"Wrong choice!"; break;
		}
	} while (book_menu_exit);
}

void Show_readers(Reader_Data* Readers_info, long rsize)
{
	for (int i = 0; i < rsize; i++)
	{
		cout << "\n" << Readers_info[i].Full_name << "\t" << Readers_info[i].Date_of_birth << "\t" << Readers_info[i].Passport_ID;
		cout << "\t" << Readers_info[i].ID_of_user << "\t" << Readers_info[i].Books_read << "\n";
	}
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
}

void Show_only_active_readers_menu(Reader_Data* Readers_info, long rsize)
{
	int show_only_active_readers_choise;

	cout << "\nShow only active readers?\n#1 Yes\n#0 Back to readers menu\n"; cin >> show_only_active_readers_choise;

	switch (show_only_active_readers_choise)
	{
	case 1: Only_popylar_readers(Readers_info, rsize); break;
	case 0: break;
	default: cout << "Wrong choice!"; break;
	}
}

void Add_reader(Reader_Data*& Readers_info, long& rsize)
{
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
	cout << "\nEnter ID of passport - "; cin >> Readers_info[rsize].Passport_ID;
	cout << "\nEnter ID of reader - "; cin >> Readers_info[rsize].ID_of_user;
	Readers_info[rsize].Books_read = 0;

	rsize++;
}

void Delete_reader(Reader_Data*& Readers_info, long& rsize)
{
	Show_readers(Readers_info, rsize);
	
	int delete_id,positiion_of_delete;
	bool delete_check = 1;

	cout << "\nEnter ID of reader - "; cin >> delete_id;

	for (int i = 0; i < rsize; i++)
	{
		if (Readers_info[i].ID_of_user == delete_id)
		{
			positiion_of_delete = i;
			delete_check = 0;
			break;
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
		cout << "Enter full name - "; cin.ignore(); cin.get(buff, 100);

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
		cout << "\nEnter ID of reader - "; cin >> intbuff;

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
		cout << "\nEnter passport ID of reader - "; cin >> intbuff;

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
}

void Reader_Search_menu(Reader_Data* Readers_info, long rsize)
{
	bool reader_serch_menu_exit = 1;
	int reader_serch_menu_choise;

	do
	{
		cout << "\nBy what criteria to search?\n#1 Full Name\n#2 Number of books read\n#3 ID\n#4 Passport ID\n#0 Back to reader menu\n";
		cin >> reader_serch_menu_choise;

		switch (reader_serch_menu_choise)
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
}

void Reader_Sort_menu(Reader_Data* Readers_info,long rsize)
{
	bool reader_sort_menu_exit = 1;
	int reader_sort_menu_choise;

	do
	{
		cout << "\nSelect sort criteria\n1# Full name\n#2 Number of books read\n#3 ID\n#4 Passport ID\n#0 Back to reader menu\n";
		cin >> reader_sort_menu_choise;

		switch (reader_sort_menu_choise)
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

void Reader_menu(Reader_Data*& Readers_info, long& rsize, Book_Data*& Books_info, long& bsize)
{
	bool reader_menu_exit = 1;
	int reader_menu_choise;

	do
	{
		cout << "\nEnter choise\n#1 Show reader\n#2 Reader search\n#3 Sorting the list of readers\n#4 Add reader\n#5 Edit reader info\n#6 Delete reader\n";
		cout << "#7 List of readers with an overdue return date\n#0 Back to main menu\n";
		cin >> reader_menu_choise;

		switch (reader_menu_choise)
		{
		case 1: Show_readers(Readers_info, rsize); Show_only_active_readers_menu(Readers_info, rsize); break;
		case 2: Reader_Search_menu(Readers_info, rsize); break;
		case 3: Reader_Sort_menu(Readers_info, rsize); break;
		case 4: Add_reader(Readers_info, rsize); break;
		case 5: break;
		case 6: Delete_reader(Readers_info, rsize); break;
		case 7: break;
		case 0: reader_menu_exit = 0; break;
		default: cout << "\nWrong choise!"; break;
		}
	} while (reader_menu_exit);
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
		case 3: break;
		case 4: break;
		case 0: Exit_menu(check); break;
		default:cout << "Wrong choise!"; break;
		}

	} while (check);
}