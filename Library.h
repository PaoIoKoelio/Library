#ifndef LIBRARY_H
#define LIBRARY_H
#include <iostream>
#include <fstream>
#include "Book.h"


class Library {
public:
	Book* books;
	int numberOfBooks;

	Library();

	void swapBooks(int i, int j);

	void sortBy(int (*f)(const Book&, const Book&), bool ascend);

	void printBooks();

	void getInfoByChoice(const char* (Book::* getElem)() const, char* searchElem);

	void showBookBySentences(const Book& book);

	void showBookByRows(const Book& book, int numRows);

	void addBookToFile(const Book& book, std::ofstream &booksFile);

	void addBookToArray(Book book);

	void sortBooks(char sortDir, char sortType);

	void castBooksToClass();

	void addBook();

	void deleteBook();

	void showBook();

	int getAmmountOfBooksInFile(std::ifstream& file);

	void getInfo();

	bool checkPassword(char* password);

	void start();
};

#endif