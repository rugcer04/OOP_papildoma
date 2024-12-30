#ifndef  FUNKCIJOS_H_INCLUDED
#define FUNKCIJOS_H_INCLUDED

#include "Lib.h"

string tvarkytiTeksta(const string& zodis);
void skaiciuotiZodzius();
void isvestiZodziuKiekius(const map<string, int>& zodziuSkaicius, const string& failoPavadinimas);
void isvestiZodziuEilutes(const map<string, int>& zodziuSkaicius, const map<string, set<int>>& zodziuEiles, const string& failoPavadinimas);
void rastiURL(const string& ivestiesFailoPavadinimas);

#endif