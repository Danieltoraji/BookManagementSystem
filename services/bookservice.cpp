#include "bookservice.h"
#include <algorithm>

BookService& BookService::getInstance()
{
	static BookService instance;
	return instance;
}

BookService::BookService() {}
bool BookService::readBooksFromFile()
{
    books = BookDao::getInstance().loadBooksFromFile("data/books.txt");
    return !books.empty();
}

bool BookService::writeBooksToFile() const
{
    return BookDao::getInstance().saveBooksToFile("data/books.txt", books);
}

std::vector<Book> BookService::getAllBooks()
{
    return books;
}

bool BookService::addBook(const Book& book)
{
	auto it = std::find_if(books.begin(), books.end(),
    [&](const Book& b) { return b.getISBN() == book.getISBN(); });

    if (it == books.end()) {
        books.push_back(book);
        return true;
    }
    return false;
}

bool BookService::removeBook(const std::string& isbn)
{
	auto it = std::find_if(books.begin(), books.end(),
    [&](const Book& b) { return b.getISBN() == isbn; });

    if (it == books.end()) {
        return false;
    }
    books.erase(it);
    return true;
}

bool BookService::updateBook(const std::string& isbn, const Book& book)
{
	auto it = std::find_if(books.begin(), books.end(), [&](const Book& item) {
		return item.getISBN() == isbn;
	});

	Book updatedBook = book;
	updatedBook.setISBN(isbn);

	if (it != books.end()) {
		*it = updatedBook;
		return true;
	}
	return false;
}



/*
std::vector<const Book*> BookService::searchBooksByISBN(const std::string& isbn) const
{
	std::vector<const Book*> result;
	for (const auto& book : books) {
		if (book.getISBN() == isbn) {
			result.push_back(&book);
		}
	}
	return result;
}
*/
