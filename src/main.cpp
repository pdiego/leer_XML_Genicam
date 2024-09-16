#include "SensiaBridge.h"
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <cstdlib>

// Funcion para analizar los argumentos en formato clave=valor
std::map<std::string, std::string> parse_arguments(int argc, char* argv[]) {
    std::map<std::string, std::string> arguments;

    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        auto pos = arg.find('=');
        if (pos != std::string::npos) {
            std::string key = arg.substr(0, pos);
            std::string value = arg.substr(pos + 1);
            arguments[key] = value;
        } else {
            std::cerr << "Error: Argumento invalido (debe ser clave=valor): " << arg << std::endl;
            std::cerr << "Pon como ejemplo (GainRegister=10): " << arg << std::endl;
        }
    }

    return arguments;
}

// Funcion para imprimir los argumentos
void print_arguments(const std::map<std::string, std::string>& arguments) {
    for (const auto& pair : arguments) {
        std::cout << pair.first << " = " << pair.second << std::endl;
    }
}


int main(int argc, char* argv[]) {

    bool verificarParams = false;
    // Analizar los argumentos
    auto arguments = parse_arguments(argc, argv);

    // Imprimir los argumentos
    print_arguments(arguments);

    proyectoSensiaBridge::SensiaBridge obj;
    verificarParams = true;
    obj.doSomething(arguments);

    if (verificarParams == false) {
        std::cout << "no se ven parametros validos dentro de la ejecucion." << std::endl;
    }

    return 0;
}


