#include <iostream>
#include "EasyBMP.h"
#include <fstream>

using namespace std;

int main()
{
    BMP Input;
    ofstream output;
    Input.ReadFromFile("SS2EGAME.bmp");
    output.open("image.txt", ios::out);
    unsigned int columns = 0;

    for(unsigned int j = 0; j < Input.TellHeight(); j++) {
        for(unsigned int i = 0; i < Input.TellWidth(); i+=2) {
            unsigned short temp = ((Input(i + 1, j)->Blue << 4) | Input(i, j)->Blue) & 0xFF;
            output << "0x" << hex << temp << ", ";
            columns++;
            if(columns == 17) {
                columns = 0;
                output << "\n\r";
            }
        }
        //cout << "\n\r";
    }
    output.close();

    cout << "Hello world!" << endl;
    return 0;
}
