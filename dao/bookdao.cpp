#include "bookdao.h"

#include <algorithm>
#include <fstream>
#include <sstream>

BookDao& BookDao::getInstance()
{
	static BookDao instance;
	return instance;
}

bool BookDao::loadBooksFromFile(const std::string& filename)
{
	books.clear();

	std::ifstream file(filename);
	if (!file.is_open()) {
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) {
			continue;
		}
		books.push_back(stringToBook(line));
	}
	return true;
}

bool BookDao::saveBooksToFile(const std::string& filename) const
{
	std::ofstream file(filename, std::ios::trunc);
	if (!file.is_open()) {
		return false;
	}

	for (const auto& book : books) {
		file << bookToString(book) << '\n';
	}
	return true;
}

std::vector<Book> BookDao::getAllBooks()
{
	return books;
}

bool BookDao::addBook(const Book& book)
{
	auto it = std::find_if(books.begin(), books.end(),
    [&](const Book& b) { return b.getISBN() == book.getISBN(); });

    if (it == books.end()) {
        books.push_back(book);
        return true;
    }
    return false;
}

bool BookDao::removeBook(const std::string& isbn)
{
	auto it = std::find_if(books.begin(), books.end(),
    [&](const Book& b) { return b.getISBN() == isbn; });

    if (it == books.end()) {
        return false;
    }
    books.erase(it);
    return true;
}

bool BookDao::updateBook(const std::string& isbn, const Book& book)
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

std::vector<const Book*> BookDao::searchBooksByISBN(const std::string& isbn) const
{
	std::vector<const Book*> result;
	for (const auto& book : books) {
		if (book.getISBN() == isbn) {
			result.push_back(&book);
		}
	}
	return result;
}

std::vector<const Book*> BookDao::searchBooksByTitle(const std::string& title) const
{
	std::vector<const Book*> result;
	for (const auto& book : books) {
		if (book.getTitle() == title) {
			result.push_back(&book);
		}
	}
	return result;
}

std::vector<const Book*> BookDao::searchBooksByAuthor(const std::string& author) const
{
	std::vector<const Book*> result;
	for (const auto& book : books) {
		if (book.getAuthor() == author) {
			result.push_back(&book);
		}
	}
	return result;
}

std::string BookDao::bookToString(const Book& book) const
{
	std::ostringstream stream;
	stream << book.getISBN() << '|'
		   << book.getTitle() << '|'
		   << book.getAuthor() << '|'
		   << book.getPublisher() << '|'
		   << book.getPublishingYear() << '|'
		   << book.getCategory() << '|';

	bool firstCopy = true;
	for (const auto& copy : book.getCopies()) {
		if (!firstCopy) {
			stream << ',';
		}
		stream << copy;
		firstCopy = false;
	}

	stream << '|' << book.getRemarks();
	return stream.str();
}

Book BookDao::stringToBook(const std::string& bookStr) const
{
	std::vector<std::string> fields;
    std::stringstream bookStream(bookStr);
    std::string field;
    while (std::getline(bookStream,field,'|')){
        fields.push_back(field);
    }
    if (fields.size() < 8) {
		return Book("", "", "", "", 0, "", "" , {});
	}
    
    Book book(fields[0], fields[1], fields[2], fields[3], std::stoi(fields[4]), fields[5], fields[7], {});

    std::stringstream copiesStream(fields[6]);
    while (std::getline(copiesStream, field, ',')) {
        if (!field.empty()) {
            book.addCopy(field);
        }
    }

    return book;
}
