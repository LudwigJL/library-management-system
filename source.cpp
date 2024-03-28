#include <iostream>
#include <string>
#include <sqlite3.h>
#include "visuals.h"
#include "user_operators.h"
#include "search_operators.h"

using namespace std;

void showMainMenu() {

    cout << "Main Menu" << endl;
    cout << "1. Borrow Book" << endl;
    cout << "2. Return Book" << endl;
    cout << "3. Register New Member" << endl;

    cout << "4. Search Book, Author or Genre" << endl;
    cout << "5. Search through the library's collection." << endl;

    cout << "8. Show All Members" << endl;
    cout << "9. Show All Books" << endl;
    cout << "q. Exit" << endl;

    cout << "Enter your choice: ";
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
        case '4':
            searchCollection();
            break;

        case 'q': 
            exit = true;
            break;
        }
    }
    return 0;
}

