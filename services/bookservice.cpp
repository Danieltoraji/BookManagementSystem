#include "bookservice.h"

bookService::bookService() {}

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

std::vector<const Book*> BookService::searchBooksByTitle(const std::string& title) const
{
	std::vector<const Book*> result;
	for (const auto& book : books) {
		if (book.getTitle() == title) {
			result.push_back(&book);
		}
	}
	return result;
}

std::vector<const Book*> BookService::searchBooksByAuthor(const std::string& author) const
{
	std::vector<const Book*> result;
	for (const auto& book : books) {
		if (book.getAuthor() == author) {
			result.push_back(&book);
		}
	}
	return result;
}
std::vector<Book> BookDao::getAllBooks()
{
	return books;
}