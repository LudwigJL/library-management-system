#ifndef USER_OPERATORS_H
#define USER_OPERATORS_H

#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;

void toLowercase(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void removeSpaces(string& str) {
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}

//Checked
void addMember(sqlite3* db) {
    int data = 0;
    string name;
    string address;
    string phone;
    string email;

    cout << "Registration" << endl;

    cout << "Name: ";
    getline(cin, name);

    cout << "Adress: ";
    getline(cin, address);

    cout << "Swedish Phone Number (+46): ";
    getline(cin, phone);

    cout << "Personal E-mail: ";
    getline(cin, email);

    removeSpaces(phone);
    toLowercase(email);
    removeSpaces(email);

    data = sqlite3_open("FOR-SQLITE/mydb.db", &db);
    if (data != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_stmt *stmt;
    const char* insertQuery = "INSERT INTO Members (name, address, phone, email) VALUES (?, ?, ?, ?)";
    int qstate = sqlite3_prepare_v2(db, insertQuery, -1, &stmt, 0);

    if (qstate != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, address.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, phone.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, email.c_str(), -1, SQLITE_STATIC);

    qstate = sqlite3_step(stmt);
    if (qstate != SQLITE_DONE) {
        cerr << "Error inserting data: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "New Member Successfully Created" << endl;
    }

    sqlite3_finalize(stmt); 
    sqlite3_close(db);
}

void borrowBook(sqlite3* db) {
    int qstate = 0;
    qstate = sqlite3_open("FOR-SQLITE/mydb.db", &db);

    if (qstate != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    string book_id;
    string member_id;
    string newStatus = "unavailable";

    cout << "Book_id: ";
    cin >> book_id;

    cout << "Member_id: ";
    cin >> member_id;

    string updateBookStatusQuery = "UPDATE Books SET status = '" + newStatus + "', borrower_id = '" + member_id + "' WHERE book_id = " + book_id + ";";
    string updateMemberBorrowed = "UPDATE Members SET borrowed_id = '" + book_id + "' WHERE member_id = '" + member_id + "';";

    const char* q = updateBookStatusQuery.c_str();
    const char* r = updateMemberBorrowed.c_str();

    qstate = sqlite3_exec(db, q, 0, 0, 0);

    if (qstate != SQLITE_OK) {
        cerr << "Error updating book status and borrower ID: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Borrow registration successfully completed!" << endl;
    }

    qstate = sqlite3_exec(db, r, 0, 0, 0);

    if (qstate != SQLITE_OK) {
        cerr << "Error updating borrowed_id for Member: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "" << endl;
    }

    sqlite3_close(db);
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
        cout << "Book sucessfully returned!" << endl;
    }

    sqlite3_close(db);
    }


#endif


