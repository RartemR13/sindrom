#include <iostream>

#include "SindromPicture/SindromPicture.hpp"

int main() {
    SindromPicture kaneki("kaneki.bmp");

    kaneki.ReplaceColor({0xFF, 0xFF, 0xFF, 0x00}, {0x00, 0xFF, 0x00, 0x00});
    //kaneki.Negative();

    kaneki.Save("sosi.bmp");
}