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

std::vector<const Book*> BookService::searchBooks(const searchQuery& query) const
{
    std::vector<const Book*> result;
    std::vector<bool> flag1, flag2;
    switch(query.field1){
        case searchQuery::Field::Empty:
            for (size_t i = 0; i < books.size(); ++i) {
                flag1.push_back(true);
            }
        case searchQuery::Field::ISBN:
            switch(query.condition1){
                case searchQuery::Condition::Equals:
                    for (const auto& book : books){
                        if(book.getISBN()==query.value1) flag1.push_back(true);
                        else flag1.push_back(false);
                    }
                break;
                case searchQuery::Condition::Contains:
                    for (const auto& book : books){
                        if(book.getISBN().find(query.value1)!=std::string::npos) flag1.push_back(true);
                        else flag1.push_back(false);
                    }
                break;
                case searchQuery::Condition::StartsWith:
                    for (const auto& book : books){
                        if(book.getISBN().rfind(query.value1, 0) == 0) flag1.push_back(true);//最后一次出现是在开头
                        else flag1.push_back(false);
                    }
                break;
            }
        break;
        case searchQuery::Field::Title:
            switch(query.condition1){
                case searchQuery::Condition::Equals:
                    for (const auto& book : books){
                        if(book.getTitle()==query.value1) flag1.push_back(true);
                        else flag1.push_back(false);
                    }
                break;
                case searchQuery::Condition::Contains:
                    for (const auto& book : books){
                        if(book.getTitle().find(query.value1)!=std::string::npos) flag1.push_back(true);
                        else flag1.push_back(false);
                    }
                break;
                case searchQuery::Condition::StartsWith:
                    for (const auto& book : books){
                        if(book.getTitle().rfind(query.value1, 0) == 0) flag1.push_back(true);
                        else flag1.push_back(false);
                    }
                break;
            }break;
        case searchQuery::Field::Author:
            switch(query.condition1){
                case searchQuery::Condition::Equals:
                    for (const auto& book : books){
                        if(book.getAuthor()==query.value1) flag1.push_back(true);
                        else flag1.push_back(false);
                    }
                break;
                case searchQuery::Condition::Contains:
                    for (const auto& book : books){
                        if(book.getAuthor().find(query.value1)!=std::string::npos) flag1.push_back(true);
                        else flag1.push_back(false);
                    }
                break;
                case searchQuery::Condition::StartsWith:
                    for (const auto& book : books){
                        if(book.getAuthor().rfind(query.value1, 0) == 0) flag1.push_back(true);
                        else flag1.push_back(false);
                    }
                    break;
            }
        break;
    }
            
    switch(query.field2){
        case searchQuery::Field::Empty:
            for (size_t i = 0; i < books.size(); ++i) {
                flag2.push_back(true);
            }
        case searchQuery::Field::ISBN:
            switch(query.condition2){
                case searchQuery::Condition::Equals:
                    for (const auto& book : books){
                        if(book.getISBN()==query.value2) flag2.push_back(true);
                        else flag2.push_back(false);
                    }
                break;
                case searchQuery::Condition::Contains:
                    for (const auto& book : books){
                        if(book.getISBN().find(query.value2)!=std::string::npos) flag2.push_back(true);
                        else flag2.push_back(false);
                    }
                break;
                case searchQuery::Condition::StartsWith:
                    for (const auto& book : books){
                        if(book.getISBN().rfind(query.value2, 0) == 0) flag2.push_back(true);//最后一次出现是在开头
                        else flag2.push_back(false);
                    }
                break;
            }
        break;
        case searchQuery::Field::Title:
            switch(query.condition2){
                case searchQuery::Condition::Equals:
                    for (const auto& book : books){
                        if(book.getTitle()==query.value2) flag2.push_back(true);
                        else flag2.push_back(false);
                    }
                break;
                case searchQuery::Condition::Contains:
                    for (const auto& book : books){
                        if(book.getTitle().find(query.value2)!=std::string::npos) flag2.push_back(true);
                        else flag2.push_back(false);
                    }
                break;
                case searchQuery::Condition::StartsWith:
                    for (const auto& book : books){
                        if(book.getTitle().rfind(query.value2, 0) == 0) flag2.push_back(true);
                        else flag2.push_back(false);
                    }
                break;
            }break;
        case searchQuery::Field::Author:
            switch(query.condition2){
                case searchQuery::Condition::Equals:
                    for (const auto& book : books){
                        if(book.getAuthor()==query.value2) flag2.push_back(true);
                        else flag2.push_back(false);
                    }
                break;
                case searchQuery::Condition::Contains:
                    for (const auto& book : books){
                        if(book.getAuthor().find(query.value2)!=std::string::npos) flag2.push_back(true);
                        else flag2.push_back(false);
                    }
                break;
                case searchQuery::Condition::StartsWith:
                    for (const auto& book : books){
                        if(book.getAuthor().rfind(query.value2, 0) == 0) flag2.push_back(true);
                        else flag2.push_back(false);
                    }
                    break;
            }
        break;

}

    switch(query.logic){
        case searchQuery::Logic::And:
            for(size_t i=0;i<books.size();i++){
                if(flag1[i] && flag2[i]) result.push_back(&books[i]);
            }
        break;
        case searchQuery::Logic::Or:
            for(size_t i=0;i<books.size();i++){
                if(flag1[i] || flag2[i]) result.push_back(&books[i]);
            }
        break;
    }
    return result;
}
