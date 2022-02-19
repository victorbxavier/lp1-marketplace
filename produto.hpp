#ifndef PRODUTO_HPP
#define PRODUTO_HPP
#include <string>
using namespace std;

class Produto {
    public:
    int id; // número incremental
    string nome;
    float preco;
    int quantidade;
};
#endif