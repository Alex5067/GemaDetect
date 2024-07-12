#include "./lib/Neu.h"
#include <iostream>

int main() {
    Neu model("./images");
    model.predict("test1.jpg");
    return 0;
}
