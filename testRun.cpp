#include "./lib/Neu.h"
#include <iostream>

int main() {
    Neu model("./images");
    model.predict("kirillTestImage.jpg");
    return 0;
}
