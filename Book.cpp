#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Book.h"

Book::Book()
{
	author = nullptr;
	title = nullptr;
	text = nullptr;
	description = nullptr;
	rating = 0;
	ISBN = nullptr;
}
void Book::copyFrom(const Book& other)
{
	author = new char[strlen(other.author) + 1];
	strcpy(author, other.author);
	title = new char[strlen(other.title) + 1];
	strcpy(title, other.title);
	text = new char[strlen(other.text) + 1];
	strcpy(text, other.text);
	description = new char[strlen(other.description) + 1];
	strcpy(description, other.description);
	rating = other.rating;
	ISBN = new char[strlen(other.ISBN) + 1];
	strcpy(ISBN, other.ISBN);
}
void Book::free()
{
	delete[] author;
	delete[] title;
	delete[] text;
	delete[] description;
	delete[] ISBN;
}
Book::Book(const Book& other)
{
	copyFrom(other);
}
Book::Book(char* author, char* title, char* text, char* description, int rating, char* ISBN)
{
	this->author = nullptr;
	this->title = nullptr;
	this->text = nullptr;
	this->description = nullptr;
	this->rating = 0;
	this->ISBN = nullptr;
	setAuthor(author);
	setTitle(title);
	setText(text);
	setDescription(description);
	setRating(rating);
	setISBN(ISBN);
}
const char* Book::getAuthor() const
{
	return author;
}
const char* Book::getTitle() const
{
	return title;
}
const int Book::getRating() const
{
	return rating;
}
const char* Book::getISBN() const
{
	return ISBN;
}
const char* Book::getDescription() const
{
	return description;
}
const char* Book::getText() const
{
	return text;
}
void Book::setRating(int rating)
{
	if (rating > 0 && rating < 10)
	{
		this->rating = rating;
	}
	else { this->rating = 0; }
}
void Book::setISBN(char* ISBN)
{
	delete[] this->ISBN;
	this->ISBN = new char[strlen(ISBN) + 1];
	strcpy(this->ISBN, ISBN);
}
void Book::setAuthor(char* author)
{
	delete[] this->author;
	this->author = new char[strlen(author) + 1];
	strcpy(this->author, author);
}
void Book::setTitle(char* title)
{
	delete[] this->title;
	this->title = new char[strlen(title) + 1];
	strcpy(this->title, title);
}
void Book::setText(char* text)
{
	delete[] this->text;
	this->text = new char[strlen(text) + 1];
	strcpy(this->text, text);
}
void Book::setDescription(char* description)
{
	delete[] this->description;
	this->description = new char[strlen(description) + 1];
	strcpy(this->description, description);
}
Book& Book::operator=(Book& other)
{
	free();
	copyFrom(other);
	return *this;
}

int Book::compareByAuthor(const Book& book1, const Book& book2){
	return strcmp(book1.getAuthor(), book2.getAuthor());
}

int Book::compareByTitle(const Book& book1, const Book& book2) {
	return strcmp(book1.getTitle(), book2.getTitle());
}

int Book::compareByRating(const Book& book1, const Book& book2) {
	return book1.getRating() - book2.getRating();
}
Book::~Book()
{
	free();
}