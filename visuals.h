#ifndef VISUALS_H
#define VISUALS_H

#include <iostream>
#include <string>
#include <sqlite3.h> 

using namespace std;

void showAllBooks(string title, string endstring) {
    
    sqlite3 *db;
    int rc = sqlite3_open("FOR-SQLITE/mydb.db", &db);
    
    const char* query;
    if (!endstring.empty()) {
        query = sqlite3_mprintf("SELECT book_id, title, author, publication, genre, status FROM Books WHERE %s", endstring.c_str());
    } else {
        query = sqlite3_mprintf("SELECT book_id, title, author, publication, genre, status FROM Books");
    }


    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        if (!title.empty()) {
            rc = sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int book_id = sqlite3_column_int(stmt, 0);
            const unsigned char *title = sqlite3_column_text(stmt, 1);
            const unsigned char *author = sqlite3_column_text(stmt, 2);
            const unsigned char *publication = sqlite3_column_text(stmt, 3);
            const unsigned char *genre = sqlite3_column_text(stmt, 4);
            const unsigned char *status = sqlite3_column_text(stmt, 5);

            cout << "Book ID: " << book_id << endl;
            cout << "Title: " << title << endl;
            cout << "Author: " << author << endl;
            cout << "Publication: " << publication << endl;
            cout << "Genre: " << genre << endl;
            cout << "Status: " << status << endl;
            cout << "-------------------------" << endl;
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_free((void*)query);
    sqlite3_close(db);
}
#endif