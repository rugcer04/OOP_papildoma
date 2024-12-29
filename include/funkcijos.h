#ifndef  FUNKCIJOS_H_INCLUDED
#define FUNKCIJOS_H_INCLUDED

#include "Lib.h"
//#include "../src/funkcijos.cpp"

string tvarkytiTeksta(const string& zodis);
void skaiciuotiZodzius();
//void isvestiRezultata(const map<string, int>& zodziuSkaicius, const map<string, set<int>>& zodziuEiles, const string& failoPavadinimas);
void isvestiZodziuKiekius(const map<string, int>& zodziuSkaicius, const string& failoPavadinimas);
void isvestiZodziuEilutes(const map<string, int>& zodziuSkaicius, const map<string, set<int>>& zodziuEiles, const string& failoPavadinimas);
void rastiURL(const string& ivestiesFailoPavadinimas);
//void rastiURL(const string& ivestiesFailoPavadinimas, const string& isvestiesFailoPavadinimas);

#endif