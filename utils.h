#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "picosha2.h"

using namespace std;

static const char alphanum[] =
"0123456789"
"!@*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;
    
inline char genRandom()
{
    return alphanum[rand() % stringLength];
}

inline string genRandomString(int length)
{
    string str;

    static int sranded = 0;
    
    if (sranded == 0) {
        srand(time(0));
        sranded = 1;
    }

    for (int i = 0; i < length; i++) {
        str += genRandom();
    }
    return str;
}

inline string geraHash(string str) {
    return picosha2::hash256_hex_string(str);
}

inline bool testa(bool condicao, string mensagem) {
    if (condicao) {
        cout << "PASSOU: " << mensagem << endl;
        return true;
    } else {
        cout << "!ERRO: " << mensagem << endl;
        return false;
    }
}

#endif