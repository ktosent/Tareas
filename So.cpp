#include <iostream>
#include <sqlite3.h>

using namespace std;

int main() {
    cout << "Programa iniciado\n";

    sqlite3 *db;

    if (sqlite3_open("test.db", &db)) {
        cout << "Error BD\n";
        return 0;
    }

    cout << "BD abierta\n";

    int id;
    cout << "Ingrese ID: " << endl;
    cin >> id;

    cout << "ID ingresado: " << id << endl;

    sqlite3_close(db);

    system("pause");
}