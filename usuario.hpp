#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <string>
using namespace std;

class Usuario {
    public:
    int id; // número incremental
    string email;
    string nome;
    string senha_hash; // Senha em hash
};
#endif