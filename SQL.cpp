#include <iostream>
#include <sqlite3.h>

using namespace std;

int main() {
    sqlite3 *db;
    char *errMsg = 0;

    // Abrir base de datos
    int rc = sqlite3_open("estudiantes.db", &db);

    if (rc) {
        cout << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << endl;
        return 0;
    } else {
        cout << "Base de datos abierta correctamente\n";
    }

    // Crear tabla
    const char* sql = "CREATE TABLE IF NOT EXISTS ESTUDIANTE("
                      "ID INT PRIMARY KEY NOT NULL,"
                      "NOMBRE TEXT NOT NULL,"
                      "EDAD INT NOT NULL);";

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        cout << "Error al crear tabla: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    // Datos del usuario
    int id, edad;
    string nombre;

    cout << "Ingrese ID: ";
    cin >> id;
    cin.ignore();

    cout << "Ingrese nombre: ";
    getline(cin, nombre);

    cout << "Ingrese edad: ";
    cin >> edad;

    // Insertar datos
    string insertSQL = "INSERT INTO ESTUDIANTE (ID, NOMBRE, EDAD) VALUES (" 
                       + to_string(id) + ", '" + nombre + "', " + to_string(edad) + ");";

    rc = sqlite3_exec(db, insertSQL.c_str(), 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        cout << "Error al insertar: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Datos insertados correctamente\n";
    }

    sqlite3_close(db);
    return 0;
}