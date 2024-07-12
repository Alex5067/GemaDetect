# GemaDetect
## Введение 
В данном проекте роль основного файла играет *main.cpp*.

Для использования данной библиотеки у себя в проекте необходимо скопировать папку *lib* в свой проект.

## Пример использования библиотеки

```c++
#include "./lib/Neu.h"
#include <iostream>

int main() {
    Neu model("./images");
    model.predict("test1.jpg");
    return 0;
}
```
В данном коде, при создании экземпляра класса Neu нужно передать путь к папке, в которой хранятся исходные изображния и куда будет сохряняться полученный результат.

Для обработки изображения необходимо вызвать у экземпляра класса *Neu* метод *predict*, в который передать имя изображения формата *jpg* из папки.

## Инструкция по запуску
Для запуска тестового проекта нужно прописать в терминале:
```
cmake -B ./build/
cmake --build ./build/
./build/main
```

## Сборка проекта
Данные тестовый проект собирается с использованием CMake.
Для сборки своего проекта необходимо в CMakeLists прописать соответствующие команды.

Пример CMakeLists.txt:
```
cmake_minimum_required(VERSION 3.14)

project("prjName")

add_subdirectory(lib)
add_executable(main main.cpp)
target_link_libraries(main PUBLIC Neu)
```






