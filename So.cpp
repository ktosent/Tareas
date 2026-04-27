#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <dxgi.h> 
#include <direct.h>

#pragma comment(lib, "dxgi.lib")

using namespace std;

struct AppIcon {
    sf::RectangleShape box;
    sf::Text label;
    string id;

    AppIcon(string name, float x, sf::Font& font) {
        id = name;
        box.setSize(sf::Vector2f(70, 70));
        box.setPosition(x, 620);
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineThickness(2);
        box.setOutlineColor(sf::Color::White);

        label.setFont(font);
        label.setString(name);
        label.setCharacterSize(12);
        label.setPosition(x, 700);
    }
};

string obtenerAnalisisHardware() {
    SYSTEM_INFO sysInfo; 
    GetSystemInfo(&sysInfo);
    MEMORYSTATUSEX memInfo; 
    memInfo.dwLength = sizeof(MEMORYSTATUSEX); 
    GlobalMemoryStatusEx(&memInfo);
    
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
    string finalGpu(gpuName.begin(), gpuName.end());

    return "--- ANALISIS DE RECIPIENTE ---\n" +
           string("Nucleos de Energia: ") + to_string(sysInfo.dwNumberOfProcessors) + "\n" +
           "Memoria RAM: " + to_string(memInfo.ullTotalPhys / (1024 * 1024 * 1024)) + " GB\n" +
           "Dominio Grafico: " + finalGpu + "\n" +
           "[SISTEMA LISTO PARA EL COMBATE]";
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1100, 750), "S.O. Lolito.exe");
    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\consola.ttf")) font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    bool enBoot = true;
    sf::Clock bootClock;
    string bufferCLI = "";
    string inputUsuario = "";
    string logAccion = "";

    sf::Text txtLogo("=== JUJUTSU OS ===\n\n      ¦¦\n      ¦¦¦¦\n    ¦¦¦¦¦¦\n  ¦¦¦¦¦¦¦¦¦¦\n¦¦¦¦¦++++¦¦¦¦\n  ¦¦¦++++¦¦\n    ++++", font, 18);
    txtLogo.setPosition(450, 80); 
    txtLogo.setFillColor(sf::Color::Red);

    sf::RectangleShape desktop(sf::Vector2f(900, 580));
    desktop.setPosition(100, 40);
    desktop.setFillColor(sf::Color(25, 25, 30));
    desktop.setOutlineThickness(4);
    desktop.setOutlineColor(sf::Color(120, 120, 120));

    sf::RectangleShape cliBox(sf::Vector2f(650, 400));
    cliBox.setPosition(225, 120);
    cliBox.setFillColor(sf::Color::Black);
    cliBox.setOutlineThickness(2);
    cliBox.setOutlineColor(sf::Color(0, 255, 150));

    sf::Text txtCLI("", font, 14);
    txtCLI.setPosition(240, 135);
    txtCLI.setFillColor(sf::Color(0, 255, 150));

    vector<AppIcon> iconos;
    string nombres[] = {"S.O. CLI", "Editor", "Word", "Excel", "PPT"};
    for (int i = 0; i < 5; i++) iconos.push_back(AppIcon(nombres[i], 280 + (i * 110), font));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (!enBoot) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 13) { 
                        if (inputUsuario == "Gojo" || inputUsuario == "Gege") {
                            system("mkdir ExpansionDominio");
                            logAccion = "Dominio creado: ExpansionDominio";
                        } 
                        else if (inputUsuario == "Sukuna") {
                            logAccion = "Corte ejecutado. Todo rastro borrado.";
                        }
                        else if (inputUsuario == "Tengen") {
                            logAccion = "Registros: Gojo/Gege, Sukuna, Mahito, Kenjaku.";
                        }
                        else if (inputUsuario == "clear") {
                            bufferCLI = "";
                            logAccion = "Consola limpia.";
                        }
                        else {
                            logAccion = "Energia no reconocida.";
                        }
                        
                        bufferCLI += "\nC:\\> " + inputUsuario + "\n  " + logAccion;
                        inputUsuario = "";
                    } 
                    else if (event.text.unicode == 8) { 
                        if (!inputUsuario.empty()) inputUsuario.pop_back();
                    } 
                    else if (event.text.unicode < 128) {
                        inputUsuario += static_cast<char>(event.text.unicode);
                    }
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (auto& icono : iconos) {
                        if (icono.box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            if (icono.id == "Word") system("start winword");
                            if (icono.id == "Excel") system("start excel");
                            if (icono.id == "Editor") system("notepad");
                            if (icono.id == "PPT") system("start powerpnt");
                        }
                    }
                }
            }
        }

        window.clear(sf::Color(40, 40, 45));

        if (enBoot) {
            float t = bootClock.getElapsedTime().asSeconds();
            string carga = "=== JUJUTSU OS ===\n";
            if (t < 1.0) carga += "Sincronizando energia maldita...";
            else if (t < 2.0) carga += "Desplegando barrera...";
            else if (t < 3.0) carga += "Accediendo al sistema Jujutsu...";
            else if (t < 5.0) carga += obtenerAnalisisHardware();
            else { 
                enBoot = false; 
                bufferCLI = "Bienvenido, hechicero.\n" + obtenerAnalisisHardware(); 
            }
            
            txtCLI.setString(carga);
            window.draw(txtLogo);
            window.draw(cliBox);
            window.draw(txtCLI);
        } else {
            window.draw(desktop);
            window.draw(cliBox);
            
            txtCLI.setString(bufferCLI + "\nC:\\> " + inputUsuario + "_");
            window.draw(txtCLI);

            for (auto& icono : iconos) {
                window.draw(icono.box);
                window.draw(icono.label);
            }
        }

        window.display();
    }
    return 0;
}