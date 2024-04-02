# Library Management System

## Project Overview

This Library Management System is designed with a local SQLite database for efficient and scalable operations. This system provides various functionalities including:
- Adding library members
- Borrowing and returning books
- Browsing books in the library by genre, author, or title
- Comprehensive browsing of all available books

The primary aim of this project is to create a user-friendly system tailored for library employees, enabling them to efficiently manage all necessary operations within a library.

### Database Structure

The SQLite database consists of two main tables: `Books` and `Members`. Each table has a primary key (`book_id` and `member_id`, respectively) which uniquely identifies a specific item. These tables are connected to track which `member_id` has borrowed a specific `book_id`, and vice versa. This structure enables the system to keep track of who currently has a specific book and when it will be available in the future.
