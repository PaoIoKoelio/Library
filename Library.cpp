#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Library.h"

#define PASS "000000000"
	
Library::Library() {
	books = nullptr;
	numberOfBooks = 0;
}

void Library::swapBooks(int i, int j) {
	Book tmp = books[i + 1];
	books[i + 1] = books[i];
	books[i] = tmp;
}

void Library::sortBy( int (*f)(const Book&, const Book&), bool ascend) {
	for (int j = 0; j < numberOfBooks; j++)
	{
		for (int i = 0; i < numberOfBooks - j - 1; i++)
		{
			if ((f(books[i], books[i+1]) > 0&&ascend)|| (f(books[i], books[i + 1]) < 0 && !ascend))
			{
				swapBooks(i,i+1);
			}
		}
	}
}

void Library::printBooks() {
	for (int i = 0; i < numberOfBooks;i++)
	{
		std::cout << "Author:" << books[i].getAuthor() << std::endl;
		std::cout << "Title:" << books[i].getTitle() << std::endl;
		std::cout << "ISBN:" << books[i].getISBN() << std::endl;
		std::cout << std::endl;
	}
}

void Library::sortBooks(char sortDir, char sortType) {
	if (sortDir == 'u')
	{
		if (sortType == 'a')
		{
			sortBy(Book::compareByAuthor, 1);
		}
		if (sortType == 't')
		{
			sortBy(Book::compareByTitle, 1);
		}
		if (sortType == 'r')
		{
			sortBy(Book::compareByRating, 1);
		}
	}
	if (sortDir == 'd')
	{
		if (sortType == 'a')
		{
			sortBy(Book::compareByAuthor, 0);
		}
		if (sortType == 't')
		{
			sortBy(Book::compareByTitle, 0);
		}
		if (sortType == 'r')
		{
			sortBy(Book::compareByRating, 0);
		}
	}
	printBooks();
}
		
void Library::castBooksToClass() {
	std::ifstream file("books.txt");
	numberOfBooks = getAmmountOfBooksInFile(file);
	books = new Book[numberOfBooks];
	char buff[10000];
	for (int i = 0; i < numberOfBooks;i++)
	{
		file.getline(buff, 10000, '@');
		std::cout << buff << std::endl;
		books[i].setAuthor(buff);

		file.getline(buff, 10000, '@');
		std::cout << buff << std::endl;
		books[i].setTitle(buff);

		file.getline(buff, 10000, '@');
		std::cout << buff << std::endl;
		books[i].setText(buff);

		file.getline(buff, 10000, '@');
		std::cout << buff << std::endl;
		books[i].setDescription(buff);

		file.getline(buff, 10000, '@');
		std::cout << buff << std::endl;
		books[i].setRating(atoi(buff));

		file.getline(buff, 10000, '@');
		std::cout << buff << std::endl;
		books[i].setISBN(buff);
	}
	file.close();
}

void Library::addBookToFile(const Book& book, std::ofstream &booksFile) {
	booksFile << book.getAuthor() << "@";
	booksFile << book.getTitle() << "@";
	booksFile << book.getText() << "@";
	booksFile << book.getDescription() << "@";
	booksFile << book.getRating() << "@";
	booksFile << book.getISBN() << "@";
}

void Library::addBookToArray(Book book) {
	numberOfBooks++;
	Book* temp = new Book[numberOfBooks];
	for (int i = 0; i < numberOfBooks - 1; i++)
	{
		temp[i] = books[i];
	}
	temp[numberOfBooks - 1] = book;
	delete[] books;
	books = temp;
}

void Library::addBook() {
	std::cout << "Author:";
	char newauthor[100];
	std::cin.getline(newauthor, 100);

	std::cout << "Title:";
	char newtitle[100];
	std::cin.getline(newtitle, 100);

	std::cout << "Description:";
	char newdescription[100];
	std::cin.getline(newdescription, 100);

	std::cout << "text file name:";
	char newtextFile[100];
	std::cin.getline(newtextFile, 100);

	std::cout << "text(write @ at the end):";
	char newtext[10000];
	std::cin.getline(newtext, 10000, '@');

	std::ofstream file(newtextFile);
	file << newtext;
	file.close();

	int newrating;
	std::cout << "Rating:";
	std::cin >> newrating;

	std::cin.get();
	std::cout << "ISBN:";
	char newISBN[100];
	std::cin.getline(newISBN, 100);


	Book b(newauthor, newtitle, newtextFile, newdescription, newrating, newISBN);
	std::ofstream bookFile("books.txt");
	addBookToFile(b, bookFile);
	bookFile.close();


	addBookToArray(b);

}
void Library::deleteBook()
{
	std::cout << "type the title of the book you want to delete:";
	char delTitle[100];
	std::cin.getline(delTitle, 100);
	bool found=false;
	Book* temp = new Book[--numberOfBooks];
	for (int i = 0; i < numberOfBooks; i++)
	{
		if (strcmp(delTitle, books[i].getTitle()) == 0)
		{
			found = true;
			std::cout << "Do you want to delete the file with the book's text?(y or n):";
			char delFile;
			std::cin >> delFile;
			if (delFile == 'y')
			{
				remove(books[i].getText());
			}
		}
		if (!found)
		{
			temp[i] = books[i];
		}
		else {
			temp[i] = books[i + 1];
		}
		delete[] books;
		books = temp;
	}
	
	std::ofstream bookFile("books.txt");
	for (int i = 0; i < numberOfBooks; i++)
	{
		addBookToFile(books[i], bookFile);
	}
	bookFile.close();

}

void Library::showBook() {
	std::cout << "Enter title of book:";
	char showTitle[100];
	std::cin.getline(showTitle, 100);
	std::cout << "r-show book by rows" << std::endl << "s-show book by sentences" << std::endl << "rows or sentences:";
	char command;
	std::cin >> command;
	for (int i = 0; i < numberOfBooks; i++)
	{
		if (strcmp(showTitle, books[i].getTitle()) == 0)
		{
			if (command == 'r') {
				std::cout << "How many rows:";
				int numberOfRows;
				std::cin >> numberOfRows;
				showBookByRows(books[i], numberOfRows);
			}
			else if (command == 's') {
				showBookBySentences(books[i]);
			}
		}
	}
}

	void Library::showBookByRows(const Book& book, int numRows) {
		std::ifstream file(book.getText());
		char row[100];
		while (!file.eof())
		{
			for (int j = 0; j < numRows; j++)
			{
				file.get(row, 100);
				std::cout << row << std::endl;
			}
			std::cout << "Continue?:";
			char nextPage;
			std::cin >> nextPage;
			if (nextPage == 'y')
			{
				continue;
			}
			else if (nextPage == 'n')
			{
				break;
			}
		}
		file.close();
	}

	void Library::showBookBySentences(const Book& book){
		std::ifstream file(book.getText());
		char nextSentence;
		while (!file.eof())
		{
			char character = '0';
			while (character != '?' && character != '.' && character != '!')
			{
				file.get(character);
				std::cout << character;
				if (file.eof())
				{
					std::cout << "the end";
					break;
				}
			}
			std::cout << std::endl;
			std::cout << "Continue?:";
			std::cin >> nextSentence;
			if (nextSentence == 'y')
			{
				continue;
			}
			else if (nextSentence == 'n')
			{
				break;
			}
		}
	file.close();
	}

	int Library::getAmmountOfBooksInFile(std::ifstream& file) {

		int counter = -1;
		while (!file.eof())
		{
			char ch;
			file >> ch;
			if (ch == '@')
			{
				counter++;
			}
		}
		file.clear();
		file.seekg(0, std::ios::beg);
		std::cout << counter / 6;
		return counter / 6;
	}

	void Library::getInfoByChoice(const char* (Book::*getElem)() const, char* searchElem) {
		for (int i = 0; i < numberOfBooks; i++)
		{
			if (strcmp(searchElem, (books[i].*getElem)()) == 0)
			{
				std::cout << "Author:" << books[i].getAuthor() << std::endl;
				std::cout << "Title:" << books[i].getTitle() << std::endl;
				std::cout << "ISBN:" << books[i].getISBN() << std::endl;
				std::cout << "Description:" << books[i].getDescription() << std::endl;
			}
		}
	}

	void Library::getInfo() {

		std::cout << "a-Type author of the book" << std::endl << "t-Type title of the book" << std::endl << "i-Type ISBN of the book" << std::endl << "d-Type Part of the description of the book" << std::endl;
		std::cout << "Enter your choice:";
		char command;
		std::cin >> command;
		char searchElem[100];
		switch(command) {
			case 'a':
				std::cout << "Author:";
				std::cin.get();
				std::cin.get(searchElem, 100);
				getInfoByChoice(&Book::getAuthor, searchElem);
				break;
			case 't':
				std::cout << "Title:";
				std::cin.get();
				std::cin.get(searchElem, 100);
				getInfoByChoice(&Book::getTitle, searchElem);
				break;
			case 'i':
				std::cout << "ISBN:";
				std::cin.get();
				std::cin.get(searchElem, 100);
				getInfoByChoice(&Book::getISBN, searchElem);
				break;
			case 'd':
				std::cout << "Description:";
				std::cin.get();
				std::cin.get(searchElem, 100);
				getInfoByChoice(&Book::getDescription, searchElem);
				break;
		}
	}
	
	bool Library::checkPassword(char* password) {
		if (strcmp(password, PASS) == 0)
		{
			return 1;
		}
		return 0;
	}

	void Library::start(){
		char newpas[20];
		char command;
		std::cout << "Command guide:" << std::endl << "a-add a book" << std::endl << "r-remove a book" << std::endl << "s-sort books" << std::endl << "i-show info for book" << std::endl << "f-find Book" << std::endl << "c-close" << std::endl << "h-help" << std::endl;
		while (true)
		{
			std::cout << "Enter command:";
			std::cin >> command;
			std::cin.ignore();
			if (command == 'h')
			{
				std::cout << "Command guide:" << std::endl << "a-add a book" << std::endl << "r-remove a book" << std::endl << "s-sort books" << std::endl << "i-show info for book" << std::endl << "f-find Book" << std::endl << "c-close" << std::endl << "h-help" << std::endl;
			}
			else if (command == 'c')
			{
				break;
			}
			else if (command == 's')
			{
				std::cout << "u-upwards sort" << std::endl << "d-downwards sort" << std::endl;
				char sortDir;
				std::cin >> sortDir;
				std::cout << "a-sort by author" << std::endl << "t-sort by title" << std::endl << "r-sort by rating" << std::endl;
				char sortType;
				std::cin >> sortType;
				sortBooks(sortDir, sortType);
			}
			else if (command == 'r')
			{
				std::cout << "Enter password:";
				std::cin.getline(newpas, 20);
				if (checkPassword(newpas))
				{
					deleteBook();
				}
				else { std::cout << "No access" << std::endl; }
			}
			else if (command == 'a')
			{
				std::cout << "Enter password:";
				std::cin.getline(newpas, 20);
				if (checkPassword(newpas))
				{
					addBook();
				}
				else { std::cout << "No access" << std::endl; }
			}
			else if (command == 'i')
			{
				getInfo();
			}
			else if (command == 'f')
			{
				showBook();
			}
		}
	}





