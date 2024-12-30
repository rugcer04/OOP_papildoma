#include "../include/Lib.h"
#include "../include/funkcijos.h"

string tvarkytiTeksta(const string& zodis){
    string sutvarkytas;
    for(char raide : zodis){
        if (!ispunct(raide) && !isdigit(raide)) {
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

    isvestiZodziuKiekius(zodziuSkaicius, "kiekiai.txt");
    isvestiZodziuEilutes(zodziuSkaicius, zodziuEiles, "vietos.txt");
    rastiURL(failoPavadinimas);
}

void isvestiZodziuKiekius(const map<string, int>& zodziuSkaicius, const string& failoPavadinimas){
    ofstream failas(failoPavadinimas);
    if (!failas) {
        cerr << "Nepavyko sukurti failo: " << failoPavadinimas << endl;
        return;
    }

    // antraste
    failas << left << setw(15) << "Žodis" << setw(10) << "Kiekis" << "\n";
    failas << string(30, '-') << "\n";

    for (const auto& [zodis, skaicius] : zodziuSkaicius){
        if (skaicius > 1){
            failas << left << setw(15) << zodis << setw(10) << skaicius << "\n";
        }
    }

    failas.close();
    cout << "Žodžių kiekiai sėkmingai išsaugoti faile: " << failoPavadinimas << endl;

}

void isvestiZodziuEilutes(const map<string, int>& zodziuSkaicius, const map<string, set<int>>& zodziuEiles, const string& failoPavadinimas){
    ofstream failas(failoPavadinimas);
    if (!failas) {
        cerr << "Nepavyko sukurti failo: " << failoPavadinimas << endl;
        return;
    }

    // antraste
    failas << left << setw(15) << "Žodis" << setw(18) << "Vieta (eilutės nr)" << "\n";
    failas << string(60, '-') << "\n";

    for (const auto& [zodis, skaicius] : zodziuSkaicius){
        if (skaicius > 1){
            failas << left << setw(15) << zodis;
            for (int eilute : zodziuEiles.at(zodis)){
                failas << eilute << " ";
            }
            failas << "\n";
        }
    }

    failas.close();
    cout << "Žodžių vietos sėkmingai išsaugotos faile: " << failoPavadinimas << endl;

}

void rastiURL(const string& ivestiesFailoPavadinimas){
    ifstream ivestis(ivestiesFailoPavadinimas);

    char pasirinkimas;
    while (true){
        cout << "Ar norite rezultatus spausdinti į failą (F) ar į terminalą (T)?: ";
        cin >> pasirinkimas;
        pasirinkimas = toupper(pasirinkimas);

        if (pasirinkimas == 'F' || pasirinkimas == 'T'){
            break;
        } else {
            cout << "Neteisinga įvestis, bandykite dar kartą.\n";
        }
    }

    // ((https?://[^\s,]+|www\.[^\s,]+|\b[a-z0-9.-]+\.[a-z]{2,}\b))
    // ((https?://[^\s,]+|www\.[^\s,]+|\b[a-z0-9.-]+\.(com|net|org|edu|xyz|[a-z]{2})\b))
    string eilute;
    set<string> urls;
    regex urlRegex(R"((https?://[^\s,]+|www\.[^\s,]+|\b[a-z0-9.-]+\.(com|net|org|edu|xyz|int|gov|mil|info|biz|aero|asia|cat|coop|jobs|name|pro|tel|mobi|post|firm|gen|health|lat|tech|bank|bio|email|legal|news|ngo|rent|[a-z]{2})(/[^\s]*)?)\b)");

    ofstream isvestis;
    if (pasirinkimas == 'F'){
        string isvestiesFailoPavadinimas = "url.txt";
        isvestis.open(isvestiesFailoPavadinimas);

        if (!isvestis) {
            cerr << "Nepavyko sukurti failo: " << isvestiesFailoPavadinimas << endl;
            return;
        }
    }

    while (getline(ivestis, eilute)){
        sregex_iterator begin(eilute.begin(), eilute.end(), urlRegex), end;
        for (auto it = begin; it != end; ++it){
            string url = it -> str();

            while (!url.empty() && (url.back() == ',' || url.back() == '.' || url.back() == '?' || url.back() == '!')) {
                url.pop_back();
            }

            urls.insert(url);
        }
    }

    if (!urls.empty()) {
        for (const auto& url : urls) {
            if (pasirinkimas == 'F') {
                isvestis << url << "\n";
            } else {
                cout << url << "\n";
            }
        }
        if (pasirinkimas == 'F') {
            cout << "Rezultatai sėkmingai išsaugoti faile: url.txt" << endl;
        }
    } else {
        cout << "Url nerasta!" << endl;
    }
}