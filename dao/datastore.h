#ifndef DATASTORE_H
#define DATASTORE_H

#include <vector>
#include <string>
#include "../model/book.h"
#include "../model/bookcopy.h"
#include "../model/patron.h"
#include "../model/admin.h"
#include "../model/loan.h"
#include "../model/borrow.h"
#include "../model/reservation.h"
#include "../model/fine.h"

class DataStore
{
public:
    static DataStore* instance();

    // Book
    void addBook(Book* book);
    void removeBook(const std::string& isbn);
    Book* findBookByISBN(const std::string& isbn) const;
    const std::vector<Book*>& getBooks() const;

    // BookCopy
    void addBookCopy(BookCopy* copy);
    void removeBookCopy(const std::string& libCode);
    BookCopy* findBookCopy(const std::string& libCode) const;
    const std::vector<BookCopy*>& getBookCopies() const;

    // Patron
    void addPatron(Patron* patron);
    void removePatron(const std::string& id);
    Patron* findPatron(const std::string& id) const;
    const std::vector<Patron*>& getPatrons() const;

    // Admin
    void addAdmin(Admin* admin);
    Admin* findAdmin(const std::string& id) const;
    const std::vector<Admin*>& getAdmins() const;

    // Loan
    void addLoan(Loan* loan);
    Loan* findLoan(const std::string& id) const;
    const std::vector<Loan*>& getLoans() const;

    // Borrow
    void addBorrow(Borrow* borrow);
    Borrow* findBorrow(const std::string& id) const;
    const std::vector<Borrow*>& getBorrows() const;

    // Reservation
    void addReservation(Reservation* reservation);
    void removeReservation(const std::string& id);
    Reservation* findReservation(const std::string& id) const;
    const std::vector<Reservation*>& getReservations() const;

    // Fine
    void addFine(Fine* fine);
    Fine* findFine(const std::string& id) const;
    const std::vector<Fine*>& getFines() const;

private:
    DataStore();
    ~DataStore();
    DataStore(const DataStore&) = delete;
    DataStore& operator=(const DataStore&) = delete;

    static DataStore* m_instance;

    std::vector<Book*> m_books;
    std::vector<BookCopy*> m_bookCopies;
    std::vector<Patron*> m_patrons;
    std::vector<Admin*> m_admins;
    std::vector<Loan*> m_loans;
    std::vector<Borrow*> m_borrows;
    std::vector<Reservation*> m_reservations;
    std::vector<Fine*> m_fines;
};

#endif // DATASTORE_H

