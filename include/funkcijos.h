#ifndef  FUNKCIJOS_H_INCLUDED
#define FUNKCIJOS_H_INCLUDED

#include "Lib.h"
//#include "../src/funkcijos.cpp"

string tvarkytiTeksta(const string& zodis);
void skaiciuotiZodzius();
void isvestiRezultata(const map<string, int>& zodziuSkaicius, const map<string, set<int>>& zodziuEiles, const string& failoPavadinimas);

#endif