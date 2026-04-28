#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <dxgi.h>
#include <direct.h>

#pragma comment(lib, "dxgi.lib")

using namespace std;

void gotoxy(int x, int y) {
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void dibujarInterfaz() {
    system("cls");
    system("mode con: cols=110 lines=38");
    setColor(8);
    for (int i = 0; i < 105; i++) { 
        gotoxy(i, 0); cout << "X"; 
        gotoxy(i, 32); cout << "X"; 
    }
    for (int i = 0; i < 32; i++) { 
        gotoxy(0, i); cout << "X"; 
        gotoxy(104, i); cout << "X"; 
    }
    
    gotoxy(2, 1); setColor(15); cout << "Medidas   Ayuda";
    gotoxy(90, 1); setColor(11); cout << "[ _ ][ # ][ X ]";
    
    setColor(8);
    gotoxy(1, 2); for (int i = 0; i < 103; i++) cout << "-";

    setColor(7);
    gotoxy(5, 34);  cout << "[S.O. CLI]";
    gotoxy(20, 34); cout << "[Editor .txt]";
    gotoxy(40, 34); cout << "[Word]";
    gotoxy(55, 34); cout << "[Excel]";
    gotoxy(70, 34); cout << "[PowerPoint]";
}

string detectarGPU() {
    wstring gpu = L"Generica";
    IDXGIFactory* pFactory;
    if (SUCCEEDED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory))) {
        IDXGIAdapter* pAdapter;
        if (pFactory->EnumAdapters(0, &pAdapter) != DXGI_ERROR_NOT_FOUND) {
            DXGI_ADAPTER_DESC desc;
            pAdapter->GetDesc(&desc);
            gpu = desc.Description;
            pAdapter->Release();
        }
        pFactory->Release();
    }
    return string(gpu.begin(), gpu.end());
}

void ejecutarBoot() {
    dibujarInterfaz();
    setColor(12);
    gotoxy(45, 5);  cout << "=== JUJUTSU OS ===";
    gotoxy(50, 7);  cout << "||";
    gotoxy(49, 8);  cout << "||||";
    gotoxy(48, 9);  cout << "||||||";
    gotoxy(46, 10); cout << "||||||||||";
    
    setColor(11);
    gotoxy(38, 14); cout << "Sincronizando energia maldita..."; Sleep(600);
    gotoxy(38, 15); cout << "Desplegando barrera..."; Sleep(600);
    
    setColor(14);
    gotoxy(38, 17); cout << "--- ANALISIS DE RECIPIENTE ---";
    SYSTEM_INFO si; GetSystemInfo(&si);
    MEMORYSTATUSEX mem; mem.dwLength = sizeof(mem); GlobalMemoryStatusEx(&mem);
    gotoxy(38, 18); cout << "Nucleos: " << si.dwNumberOfProcessors;
    gotoxy(38, 19); cout << "RAM: " << mem.ullTotalPhys / (1024 * 1024 * 1024) << " GB";
    gotoxy(38, 20); cout << "GPU: " << detectarGPU().substr(0, 35);
    
    setColor(10);
    gotoxy(38, 22); cout << "[SISTEMA LISTO]"; Sleep(1200);
}

int main() {
    ejecutarBoot();
    dibujarInterfaz();
    
    setColor(10);
    gotoxy(25, 8);  cout << "______________________________________________";
    for (int i = 0; i < 12; i++) { 
        gotoxy(25, 9 + i); cout << "|                                            |"; 
    }
    gotoxy(25, 21); cout << "|____________________________________________|";
    
    string cmd;
    int fila = 0;
    while (true) {
        gotoxy(27, 9 + fila);
        setColor(10); cout << "C:\\> ";
        setColor(15); cin >> cmd;
        
        gotoxy(27, 10 + fila);
        if (cmd == "Gojo") cout << ">> Expansion de dominio: Carpeta creada.";
        else if (cmd == "Sukuna") cout << ">> Desmantelar: Archivo eliminado.";
        else if (cmd == "Tengen") cout << ">> Comandos: Gojo, Sukuna, Mahito, Kenjaku.";
        else if (cmd == "exit") break;
        else cout << ">> Energia no reconocida.";
        
        fila += 2;
        if (fila > 10) { 
            for (int i = 0; i < 12; i++) { 
                gotoxy(27, 9 + i); cout << "                                          "; 
            }
            fila = 0; 
        }
    }
    return 0;
}