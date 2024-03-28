#include <iostream>
#include <string>
#include <sqlite3.h>
#include "visuals.h"
#include "user_operators.h"

using namespace std;

void showMainMenu() {
    char cont;

    cout << "Main Menu" << endl;
    cout << "1. Borrow Book" << endl;
    cout << "2. Return Book" << endl;
    cout << "3. Register New Member" << endl;
    
    
    
    
    
    cout << "8. Show All Members" << endl;
    cout << "9. Show All Books" << endl;
    cout << "q. Exit" << endl;

    cout << "Enter your choice: ";
    }

void returnBook(sqlite3* db) {
    int qstate = 0;
    qstate = sqlite3_open("FOR-SQLITE/mydb.db", &db);
    
    string book_id;
    string member_id;
    string newStatus = "available";

    cout << "Book id: ";
    cin >> book_id;

    cout << "Member id: ";
    cin >> member_id;

    string updateBookStatusQuery = "UPDATE Books SET status = '" + newStatus + "', borrower_id = NULL WHERE book_id = " + book_id + ";";
    string updateMemberBorrowed = "UPDATE Members SET borrowed_id = NULL WHERE member_id = '" + member_id + "';";

    const char* q = updateBookStatusQuery.c_str();
    const char* r = updateMemberBorrowed.c_str();

    qstate = sqlite3_exec(db, q, 0, 0, 0);

    if (qstate != SQLITE_OK) {
        cerr << "Error updating book status and borrower ID: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Book Successfully returned!" << endl;
    }

    qstate = sqlite3_exec(db, r, 0, 0, 0);

    if (qstate != SQLITE_OK) {
        cerr << "Error updating borrowed_id for Member: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "" << endl;
    }

    sqlite3_close(db);
    }

int main() {
    sqlite3 *db;
    char choice;
    bool exit = false;

    while (!exit) {
        showMainMenu();

        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {  
        case '1':
            borrowBook(db);
            break;
        case '2':
            returnBook(db);
            break;
        case '3':
            addMember(db);
            break;

        case '9':
            showAllBooks(db);
            break;
        case 'q': 
            exit = true;
            break;
        }
    }
    return 0;
}

