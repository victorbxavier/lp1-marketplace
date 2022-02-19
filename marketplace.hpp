#ifndef MARKETPLACE_HPP
#define MARKETPLACE_HPP
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "usuario.hpp"
#include "produto.hpp"
#include "loja.hpp"
#include "venda.hpp"

using namespace std;

/**
 * @file marketplace.hpp
 * @authors Gabriel Cavalcante, Isaac Medeiros e Victor Xavier
 * @version 0.1
 * @date 2022-01-27
 * 
 * @brief Marketplace em C++
 * 
 */

class Marketplace {
    private:
    map<string, Usuario> usuarios; // Chave: email, Valor: Usuario
    map<string, int> acessos_liberados; // Chave: token_de_acesso, Valor: id_do_usuario
    map<int, Loja> lojas; // Chave: id da loja, Valor: Loja
    vector<Venda> vendas;

    public:
    
        Marketplace();
        bool me_cadastrar(string, string, string);
        string login(string, string);
        int criar_loja(string, string);
        int adicionar_produto(string, int, string, float);
        int adicionar_estoque(string, int, int, int);
        bool transferir_produto(string, int, int, int);
        vector<Produto> buscar_produtos(string);
        vector<Produto> buscar_produtos(string, int);
        vector<Loja> buscar_lojas(string);
        vector<Loja> listar_lojas();
        int comprar_produto(string, int, int);

        // Métodos de debug (adicionar a vontade)
        void show_usuarios();
        void show_tokens();
        int verifica_token(std::string token);
        int id_produtos = 1;
        vector<Produto> produtos;
};


#endif