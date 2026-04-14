#include <iostream>
#include <windows.h>
#include <string>
#include <direct.h>
#include <cstring>
// Librerías para detección de Hardware y GPU
#include <dxgi.h> 

#pragma comment(lib, "dxgi.lib")

using namespace std;

// ------------------------------
// UTILIDADES DE CONSOLA
// ------------------------------
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearLine(int y) {
    gotoxy(0, y);
    for (int i = 0; i < 120; i++) cout << " ";
}

// ------------------------------
// DETECCIÓN DE HARDWARE (JUJUTSU SCAN)
// ------------------------------
void detectarHardware() {
    // 1. Info de Sistema y RAM
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    // 2. Espacio en Disco (C:)
    ULARGE_INTEGER freeBytes, totalBytes, totalFreeBytes;
    GetDiskFreeSpaceExA("C:\\", &freeBytes, &totalBytes, &totalFreeBytes);
    double gbTotal = static_cast<double>(totalBytes.QuadPart) / (1024 * 1024 * 1024);
    double gbFree = static_cast<double>(totalFreeBytes.QuadPart) / (1024 * 1024 * 1024);

    // 3. Identificar GPU
    wstring gpuName = L"No detectada";
    IDXGIFactory* pFactory;
    if (SUCCEEDED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory))) {
        IDXGIAdapter* pAdapter;
        if (pFactory->EnumAdapters(0, &pAdapter) != DXGI_ERROR_NOT_FOUND) {
            DXGI_ADAPTER_DESC desc;
            pAdapter->GetDesc(&desc);
            gpuName = desc.Description;
            pAdapter->Release();
        }
        pFactory->Release();
    }

    // Renderizado de Info
    int startY = 22;
    setColor(11); // Cyan
    gotoxy(70, startY);     cout << "--- ANALISIS DE RECIPIENTE ---";
    
    setColor(15); // Blanco
    gotoxy(70, startY + 1); cout << "Nucleos de Energia: " << sysInfo.dwNumberOfProcessors;
    gotoxy(70, startY + 2); cout << "Memoria RAM: " << (memInfo.ullTotalPhys / (1024 * 1024 * 1024)) << " GB";
    gotoxy(70, startY + 3); cout << "Disco (C:): " << (int)gbFree << "GB libres / " << (int)gbTotal << "GB";
    
    setColor(14); // Dorado
    gotoxy(70, startY + 5); 
    wcout << L"Dominio Grafico: " << gpuName;
    
    setColor(12);
    gotoxy(70, startY + 7); cout << "[SISTEMA LISTO PARA EL COMBATE]";
    Sleep(2500);
}

// ------------------------------
// PANTALLA DE INICIO
// ------------------------------
void pantallaInicio() {
    system("mode con: cols=120 lines=45");

    setColor(12);
    gotoxy(48, 2);
    cout << "=== JUJUTSU OS ===";

    setColor(9);
    int startX = 20;
    int startY = 4;

    string logo[] = {
        "                                 ¦¦                                 ",
        "                                 ¦¦                                 ",
        "                                 ¦¦¦¦                               ",
        "                                 ¦¦¦¦                               ",
        "                               ¦¦¦¦¦¦                               ",
        "                               ¦¦¦¦¦¦                               ",
        "                         ¦¦  ¦¦¦¦¦¦¦¦    ¦¦                         ",
        "                         ¦¦¦¦¦¦¦¦¦¦¦¦  ¦¦¦¦                         ",
        "                       ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦  ¦¦                       ",
        "                       ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦  ¦¦                       ",
        "                       ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦  ¦¦                   ",
        "                       ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦                   ",
        "                       ¦¦¦¦¦¦++¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦                   ",
        "                       ¦¦¦¦¦¦++++¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦                   ",
        "                   ¦¦  ¦¦¦¦¦¦+++++¦¦¦¦¦¦¦¦¦¦¦¦¦                   ",
        "                    ¦¦¦¦¦¦¦¦+++++++¦¦¦¦¦¦¦¦¦¦¦                   ",
        "                    ¦¦¦¦¦¦¦¦¦¦++++++¦¦¦¦¦¦¦¦¦                   ",
        "                      ¦¦¦¦¦¦¦¦++++++++¦¦¦¦¦¦                   ",
        "                          ¦¦¦¦¦¦++++++¦¦                           ",
        "                              ++++++++                             "
    };

    for (int i = 0; i < 20; i++) {
        gotoxy(startX, startY + i);
        cout << logo[i];
    }

    Sleep(1000);
    setColor(12);
    gotoxy(70, 12); cout << "Bienvenido, hechicero.";

    int initY = 15;
    gotoxy(70, initY);     cout << "Sincronizando energia maldita...";   Sleep(500);
    gotoxy(70, initY + 1); cout << "Desplegando barrera...";           Sleep(500);
    gotoxy(70, initY + 2); cout << "Accediendo al sistema Jujutsu...";  Sleep(500);
    gotoxy(70, 19);        cout << "Inicializacion completa.";
    
    detectarHardware();
}

// ------------------------------
// INTERFAZ DE COMANDOS
// ------------------------------
void prompt(int y) {
    char dir[256];
    _getcwd(dir, 256);
    setColor(13);
    clearLine(y);
    gotoxy(2, y);
    cout << dir << " >> ";
    gotoxy(2 + strlen(dir) + 4, y);
}

int main() {
    pantallaInicio();

    int currentY = 32;
    string comando;

    while (true) {
        prompt(currentY);
        cin >> comando;

        setColor(13);
        clearLine(currentY + 1);
        gotoxy(2, currentY + 1);

        if (comando == "Gege" || comando == "Gojo") {
            string nombre;
            cout << "Nombre de expansion: ";
            cin >> nombre;
            system(("mkdir " + nombre).c_str());
            cout << "  Dominio creado: " << nombre;
        }
        else if (comando == "Kenjaku" || comando == "kjk") {
            string ruta;
            cout << "Ruta de transmigracion: ";
            cin >> ruta;
            if (ruta == "..") {
                if (_chdir("..") == 0) cout << "  Regresando al origen.";
                else cout << "  Error al retroceder.";
            } else {
                if (_chdir(ruta.c_str()) == 0) cout << "  Cuerpo cambiado (Directorio ok).";
                else cout << "  Error: Territorio no encontrado.";
            }
        }
        else if (comando == "Sukuna") {
            string ruta;
            cout << "Objetivo a desmantelar: ";
            cin >> ruta;
            system(("rmdir /s /q " + ruta).c_str());
            cout << "  Corte ejecutado. Todo rastro borrado.";
        }
        else if (comando == "Mahito" || comando == "mh") {
            string viejo, nuevo;
            cout << "Forma actual: "; cin >> viejo;
            cout << "Nueva forma: "; cin >> nuevo;
            system(("rename " + viejo + " " + nuevo).c_str());
            cout << "  Transfiguracion ociosa completada.";
        }
        else if (comando == "Tengen" || comando == "tng") {
            cout << "\n--- REGISTROS DE TENGEN ---\n";
            cout << "Gege/Gojo   -> Crear carpeta\n";
            cout << "Kenjaku/kjk -> Moverse entre directorios\n";
            cout << "Sukuna      -> Eliminar permanentemente\n";
            cout << "Mahito/mh   -> Renombrar archivo/carpeta\n";
            cout << "Tengen/tng  -> Mostrar estos registros\n";
            Sleep(2000);
        }
        else if (comando == "exit") {
            break;
        }
        else {
            cout << "Energia no reconocida (Comando invalido).";
        }

        Sleep(700);
        currentY += 2;
        if (currentY > 42) {
            system("cls"); // Limpia pantalla si se llena
            currentY = 2;
        }
    }

    return 0;
}