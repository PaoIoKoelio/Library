#ifndef BOOK_H
#define BOOK_H

class Book {
	char* author;
	char* title;
	char* text;
	char* description;
	int rating;
	char* ISBN;

public:
	Book();

	void copyFrom(const Book& other);


	void free();


	Book(const Book& other);

	Book(char* author, char* title, char* text, char* description, int rating, char* ISBN);

	static int compareByAuthor(const Book& book1, const Book& book2);

	static int compareByTitle(const Book& book1, const Book& book2);

	static int compareByRating(const Book& book1, const Book& book2);

	const char* getAuthor() const;

	const char* getTitle() const;

	const int getRating() const;

	const char* getISBN() const;

	const char* getDescription() const;

	const char* getText() const;

	void setRating(int rating);

	void setISBN(char* ISBN);

	void setAuthor(char* author);

	void setTitle(char* title);

	void setText(char* text);

	void setDescription(char* description);

	Book& operator=(Book& other);

	~Book();

};

#endif