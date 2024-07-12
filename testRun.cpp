#include "./lib/Neu.h"
#include <iostream>

int main() {
    Neu model("./images");
    for (int i = 1; i <= 5; ++i) {
        model.predict("test" + to_string(i) + ".jpg");
    }
    // model.predict("test2.jpg");
    return 0;
}
