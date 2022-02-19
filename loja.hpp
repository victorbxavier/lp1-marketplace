#ifndef LOJA_HPP
#define LOJA_HPP
#include "usuario.hpp"
#include "produto.hpp"
#include <vector>
#include <string>
using namespace std;

class Loja {
    public:
    int id; // número incremental
    string nome;
    Usuario proprietario;
    vector<Produto> produtos;
};

#endif