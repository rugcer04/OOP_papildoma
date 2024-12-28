#include "../include/Lib.h"
#include "../include/funkcijos.h"

#include <map>
#include <set>
#include <fstream>
#include <sstream>
//#include <cctype>

using std::map;
using std::set;
using std::ifstream;
using std::istringstream;
using std::cerr;
using std::runtime_error;

string tvarkytiTeksta(const string& zodis){
    string sutvarkytas;
    for(char raide : zodis){
        if (!ispunct(raide)) {
            sutvarkytas += tolower(raide);
        }
    }
    return sutvarkytas;
}

// map<string, int> zodziuSkaicius - skaiciuoja kiek kartu zodis pasikartoja tekste
// map<string, set<int>> zodziuEiles - saugo koks zodis kurioje eiluteje yra
void skaiciuotiZodzius(){
    map<string, int> zodziuSkaicius;
    map<string, set<int>> zodziuEiles;
    string failoPavadinimas;
    ifstream failas;
    string eilute;
    int eilutesNumeris = 0;

    while (true) {
        try {
            cout << "Įveskite failo pavadinimą: ";
            cin >> failoPavadinimas;
            failas.open(failoPavadinimas);

            if (!failas) {
                throw runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);
            }

            break;

        } catch (const runtime_error& e) {
            cerr << e.what() << " Bandykite dar kartą." << endl;
        }
    }

    while(getline(failas, eilute)){
        ++eilutesNumeris;
        istringstream stream(eilute); // padalina eilute i zodzius
        string zodis;
        while(stream >> zodis){
            string sutvarkytas = tvarkytiTeksta(zodis);
            if (!sutvarkytas.empty()){
                zodziuSkaicius[sutvarkytas]++;
                zodziuEiles[sutvarkytas].insert(eilutesNumeris);
            }
        }
    }
}