#include "../include/Lib.h"

string tvarkytiTeksta(const string& zodis){
    string sutvarkytas;
    for(char raide : zodis){
        if (isalpha(raide)) {
            sutvarkytas += tolower(raide);
        }
    }
    return sutvarkytas;
}