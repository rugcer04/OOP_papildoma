#include "../include/Lib.h"
#include "../include/funkcijos.h"

#include <regex>
using std::regex;
using std::sregex_iterator;

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

    isvestiRezultata(zodziuSkaicius, zodziuEiles, "rez.txt");
}

void isvestiRezultata(const map<string, int>& zodziuSkaicius, const map<string, set<int>>& zodziuEiles, const string& failoPavadinimas){
    ofstream failas(failoPavadinimas);
    if (!failas) {
        cerr << "Nepavyko sukurti failo: " << failoPavadinimas << endl;
        return;
    }

    // antraste
    failas << left << setw(15) << "Zodis" << setw(10) << "Kiekis" << setw(10) << "Eilutes" << "\n";
    failas << string(50, '-') << "\n";

    for (const auto& [zodis, skaicius] : zodziuSkaicius){
        if (skaicius > 1){
            failas << left << setw(15) << zodis << setw(10) << skaicius;
            //failas << zodis << " (" << skaicius << " kartai): ";
            for (int eilute : zodziuEiles.at(zodis)){
                failas << eilute << " ";
            }
            failas << "\n";
        }
    }

    failas.close();
    cout << "Rezultatai sėkmingai išsaugoti faile: " << failoPavadinimas << endl;
}

void rastiURL(const string& ivestiesFailoPavadinimas, const string& isvestiesFailoPavadinimas){
    ifstream ivestis(ivestiesFailoPavadinimas);
    ofstream isvestis(isvestiesFailoPavadinimas);

    string eilute;
    regex urlRegex(R"((https?://[^\s,]+|www\.[^\s,]+|\b[a-z0-9.-]+\.[a-z]{2,}\b))");

    while (getline(ivestis, eilute)){
        sregex_iterator begin(eilute.begin(), eilute.end(), urlRegex), end;
        for (auto it = begin; it != end; ++it){
            isvestis << it->str() << "\n";
        }
    }  
}