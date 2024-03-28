#include <iostream>
#include <string>
#include <sqlite3.h>
#include "visuals.h"
using namespace std;


void searchTitle() {
    sqlite3 *db;
    int qstate = 0;
    qstate = sqlite3_open("FOR-SQLITE/mydb.db", &db);

    if (qstate != SQLITE_OK) {
    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
    return;
    }

    string reqTitle;

    cout << "Book's Title: ";
    cin.ignore();
    getline(cin, reqTitle);

    const char* query = "SELECT book_id, title, author, publication, genre, status FROM Books";

    sqlite3_stmt *stmt;
    qstate = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (qstate == SQLITE_OK) {
        cout << "Matching books:" << endl;
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
    sqlite3_close(db);
}


void searchCollection(){
    bool exitSearch = false;
    char searchChoice;
    string title, author, genre, allPass, endstring;

    while (!exitSearch){
        cout << "Choose how you want to search: " << endl;
        cout << "1. By Title" << endl;
        cout << "2. By Author" << endl;
        cout << "3. By Genre" << endl;
        cout << "4. Browse All Books" << endl;
        cout << "r. Return to Main menu" << endl;

        cin >> searchChoice;

        switch (searchChoice){
            case '1':
            cout << "Book's Title: ";
            cin.ignore();
            getline(cin, title);

            endstring = "WHERE title = ?";
            showAllBooks(title, endstring);
            break;

            case '2': 
                cout << "Author: ";
                cin.ignore();
                getline(cin, author);

                endstring = "WHERE author = ?";
                showAllBooks(author, endstring);
                break;

            case '3':
                cout << "Examples of genres - Fiction, Science Fiction, Romance, Satire, Fantasy, Thriller..." << endl;
                cout << "Genre: ";
                cin.ignore();
                getline(cin, genre);

                endstring = "genre = ?";
                showAllBooks(genre, endstring);
                break;

            case '4':
                allPass = "";
                endstring = "";
                showAllBooks(allPass, endstring);
                break;

            case 'r':
                exitSearch = true;
        }

    }


}

