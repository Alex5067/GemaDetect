#ifndef GEM_DETECT_H
#define GEM_DETECT_H

#include <iostream>
#include <string>

using namespace std;

class Neu {
    private:
        string folder;
        // int status = 0; // возможные внутренние переменные
        
        // struct Net // структура, указывающая на сеть, например, вид и имя файла xml или что там может быть
        // {
        //     int kind;
        //     string name;
        //     Net(const int& akind = 0, const string& aname = ""): kind(akind), name(aname) {};
        // };

    public:
        Neu(const string& srcFolder): folder(srcFolder) {};
        int predict(const string& imagePath); // Предиктит гемонгеому 
        // void setNeu(int); // установка параметров, не устанавливаемых при инициализации 
        // int trainNeu(int info, string img); // обучение, info - например 0 - нет, 1- да, img - имя файла, либо каталог с файлами, либо...
        // int examNeu(int info, string img); // проверка, info - не придумал зачем ))), img - имя файла, либо...
        // ~Neu();
};



#endif