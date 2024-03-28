#include <iostream>
#include <string>
#include <sqlite3.h>
#include "visuals.h"
using namespace std;

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

            endstring = "title = ?";
            showAllBooks(title, endstring);
            break;

            case '2': 
                cout << "Author: ";
                cin.ignore();
                getline(cin, author);

                endstring = "author = ?";
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

