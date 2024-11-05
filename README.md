# Library Management System

## Project Description
The Library Management System is a C++ application that facilitates the management of library resources. It allows librarians to add and remove books, while members can borrow and return books easily. This project demonstrates object-oriented programming concepts through the use of classes and inheritance.

## Features
- **Book Management:** 
  - Librarians can add or remove books from the library.
  - Each book has a title, author, and unique Book ID.
- **Member Management:**
  - Members can borrow and return books.
  - Each member has a unique Member ID and can track the books they have borrowed.
- **Borrowing System:**
  - Books can be checked for availability before borrowing.
  - Members can return books they have borrowed.
- **User-Friendly Menu:**
  - A console menu allows users to navigate through the functionalities easily.

## Classes
- **Person:** A base class for both members and librarians, containing common attributes like name, age, and year.
- **Book:** Represents a book in the library with attributes for title, author, and borrow status.
- **Member:** Inherits from `Person` and includes methods for borrowing and returning books.
- **Librarian:** Inherits from `Person` and provides methods for managing books in the library.
