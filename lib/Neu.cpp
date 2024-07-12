// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "json.hpp"
#include <string>
#include "Neu.h"

using json = nlohmann::json;

void print(const std::string& str) {
    std::cout << str << std::endl;
}

int Neu::predict(const string& imagePath) {
    json jsonFile;
    // Записываем путь к изображению в JSON для передачи d в Python
    string jsonName = "./data.json";
    jsonFile["imageToPredict"] = folder + "/" + imagePath;
    std::ofstream file(jsonName);
    if (file.is_open()) {
        file << jsonFile.dump(4); // 4 - отступ для форматирования JSON файла
        file.close();
        // std::cout << "JSON записан" << std::endl;
    } else {
        // std::cerr << "Не удалось открыть файл для записи" << std::endl;
    }

    // Выполняем Python-скрипт
    int result = system("python3 ./lib/script.py");
    if (result != 0) {
        std::cerr << "Error executing Python script" << std::endl;
        return 1;
    }

    // Открываем и читаем JSON файл
    std::ifstream infile(jsonName);

    print(imagePath);
    infile >> jsonFile;
    

    string origPath = jsonFile.at("orig").get<string>();
    string finalPath = jsonFile.at("final").get<string>();
    print(origPath);
    print(finalPath);
    return 0;
}
