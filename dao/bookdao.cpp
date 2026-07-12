#include "bookdao.h"

#include <algorithm>
#include <fstream>
#include <sstream>

BookDao& BookDao::getInstance()
{
	static BookDao instance;
	return instance;
}

std::vector<Book> BookDao::loadBooksFromFile(const std::string& filename)
{
	std::vector<Book> books;

	std::ifstream file(filename);
	if (!file.is_open()) {
		return books;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) {
			continue;
		}
		books.push_back(stringToBook(line));
	}
	return books;
}

bool BookDao::saveBooksToFile(const std::string& filename, const std::vector<Book>& books) const
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



std::string BookDao::bookToString(const Book& book) const
{
	std::ostringstream stream;
	stream << book.getISBN() << '|'
		   << book.getTitle() << '|'
		   << book.getAuthor() << '|'
		   << book.getPublisher() << '|'
		   << book.getPublishingYear() << '|'
		   << book.getCategory() << '|';

	stream << book.getRemarks();
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
    if (fields.size() < 7) {
		return Book("", "", "", "", 0, "", "");
	}
    
    Book book(fields[0], fields[1], fields[2], fields[3], std::stoi(fields[4]), fields[5], fields[6]);

    return book;
}
