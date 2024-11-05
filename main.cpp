/* Library Management System */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base class: Person
class Person {
protected:
    string name;
    int age;
    int year;

public:
    Person(string n, int a, int y) : name(n), age(a), year(y) {}

    virtual void displayInfo() const {
        cout << "Name: " << name << ", Age: " << age << ", Year: " << year << endl;
    }
};

// Class: Book
class Book {
private:
    string title;
    string author;
    int bookID;
    bool isBorrowed;

public:
    Book(string t, string a, int bid) : title(t), author(a), bookID(bid), isBorrowed(false) {}

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author << ", Book ID: " << bookID 
             << ", Is Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

    int getBookID() const {
        return bookID;
    }

    bool getBorrowStatus() const {
        return isBorrowed;
    }

    void setBorrowStatus(bool status) {
        isBorrowed = status;
    }
};

// Derived Class: Member
class Member : public Person {
private:
    int memberID;
    vector<int> borrowedBooks;

public:
    Member(string n, int a, int y, int mid) : Person(n, a, y), memberID(mid) {}

    void displayInfo() const override {
        Person::displayInfo();
        cout << "Member ID: " << memberID << ", Borrowed Books: ";
        if (borrowedBooks.empty()) {
            cout << "None";
        } else {
            for (int id : borrowedBooks) {
                cout << id << " ";
            }
        }
        cout << endl;
    }

    void borrowBook(Book& book) {
        if (!book.getBorrowStatus()) {
            borrowedBooks.push_back(book.getBookID());
            book.setBorrowStatus(true);
            cout << "Book borrowed successfully!" << endl;
        } else {
            cout << "This book is already borrowed." << endl;
        }
    }

    void returnBook(Book& book) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), book.getBookID());
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
            book.setBorrowStatus(false);
            cout << "Book returned successfully!" << endl;
        } else {
            cout << "This book was not borrowed by you." << endl;
        }
    }
};

// Derived Class: Librarian
class Librarian : public Person {
private:
    int librarianID;

public:
    Librarian(string n, int a, int y, int lid) : Person(n, a, y), librarianID(lid) {}

    void displayInfo() const override {
        Person::displayInfo();
        cout << "Librarian ID: " << librarianID << endl;
    }

    void addBook(vector<Book>& books, string title, string author, int bookID) {
        books.push_back(Book(title, author, bookID));
        cout << "Book added successfully!" << endl;
    }

    void removeBook(vector<Book>& books, int bookID) {
        auto it = remove_if(books.begin(), books.end(), [bookID](const Book& book) {
            return book.getBookID() == bookID;
        });
        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "Book removed successfully!" << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }
};

// Menu Functions
void addBook(vector<Book>& books, Librarian& librarian) {
    string title, author;
    int bookID;

    cout << "Enter the title of the book: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter the author of the book: ";
    getline(cin, author);
    cout << "Enter the Book ID: ";
    cin >> bookID;

    librarian.addBook(books, title, author, bookID);
}

void borrowBook(vector<Book>& books, Member& member) {
    int bookID;
    cout << "Enter the Book ID to borrow: ";
    cin >> bookID;

    for (auto& book : books) {
        if (book.getBookID() == bookID) {
            member.borrowBook(book);
            return;
        }
    }
    cout << "Book not found." << endl;
}

void returnBook(vector<Book>& books, Member& member) {
    int bookID;
    cout << "Enter the Book ID to return: ";
    cin >> bookID;

    for (auto& book : books) {
        if (book.getBookID() == bookID) {
            member.returnBook(book);
            return;
        }
    }
    cout << "Book not found." << endl;
}

void displayBooks(const vector<Book>& books) {
    for (const auto& book : books) {
        book.displayInfo();
    }
}

// Main Function
int main() {
    vector<Book> books;
    Member member("Alice", 25, 2022, 1001);
    Librarian librarian("Bob", 45, 2022, 2001);

    int choice;
    while (true) {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Borrow Book" << endl;
        cout << "3. Return Book" << endl;
        cout << "4. Display Books" << endl;
        cout << "5. Display Member Info" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(books, librarian);
                break;
            case 2:
                borrowBook(books, member);
                break;
            case 3:
                returnBook(books, member);
                break;
            case 4:
                displayBooks(books);
                break;
            case 5:
                member.displayInfo();
                break;
            case 6:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}