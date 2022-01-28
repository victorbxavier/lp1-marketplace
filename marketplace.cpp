/**
 * @file marketplace.cpp
 * @author Isaac Franco (isaacfranco@imd.ufrn.br)
 * @version 0.1
 * @date 2022-01-27
 * 
 * @brief Marketplace em C++
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "utils.h"

using namespace std;

class Usuario {
    public:
    int id; // número incremental
    string email;
    string nome;
    string senha_hash; // Senha em hash
};

class Produto {
    public:
    int id; // número incremental
    string nome;
    float preco;
    int quantidade;
};

class Loja {
    public:
    int id; // número incremental
    string nome;
    Usuario proprietario;
    vector<Produto> produtos;
};

class Venda {
    public:
    int id; // número incremental
    int comprador_id; // Id do Usuário que fez a compra
    int loja_id; // Id da Loja que o produto foi comprado
    int produto_id; // Id do produto comprado
    int quantidade; // Quantos produtos foram comprados
    float preco_unitario; // Qual era o preço do produto no momento da venda
};


class Marketplace {
    private:
    map<string, Usuario> usuarios; // Chave: email, Valor: Usuario
    map<string, int> acessos_liberados; // Chave: token_de_acesso, Valor: id_do_usuario
    map<int, Loja> lojas; // Chave: id da loja, Valor: Loja
    vector<Venda> vendas;

    // TODO Separa a implementação em .h e .cpp do Marketplace
    public:
        Marketplace() {

        }

        /**
         * Cadastra um usuário no marketplace, retornando true ou false se o cadastro foi realizado com sucesso.
         * O e-mail deve ser único
         * @param nome Nome do usuário
         * @param email Email do usuário
         * @param senha Senha do usuário. Deve ser armazenada em forma criptografada.
         * @return True se o cadastro foi realizado com sucesso, false caso contrário.
         */
        bool me_cadastrar(string nome, string email, string senha) {
            // TODO(opcional) Implementar
            // Buscando usuário com e-mail no cadastro
            auto it = usuarios.find(email);
            // Se não existir, cria um novo usuário
            if (it == usuarios.end()) {
                Usuario novo_usuario;
                novo_usuario.id = usuarios.size() + 1; //podemos fazer assim pois não existe remoção
                novo_usuario.email = email;
                novo_usuario.nome = nome;
                novo_usuario.senha_hash = geraHash(senha);
                usuarios.insert(make_pair(email, novo_usuario));
                return true;
            }
            return false;
        }

        /**
         * Tenta logar o usuário com esse e-mail / senha.
         * Caso bem sucessido o login, deve gerar aleatoriamente um token de acesso
         * e o par <token, usuario_id> deve ser armazenado em "acessos_liberados".
         * @param email Email do usuário
         * @param senha Senha do usuário.
         * @return  token de acesso caso o login seja bem sucedido. Caso contrário, retornar "invalid"
         */
        string login(string email, string senha) {
            // TODO(opcional) Implementar
            // Buscando usuário com e-mail no cadastro
            auto it = usuarios.find(email);
            // Se não existir, retorna "invalid"
            if (it == usuarios.end()) {
                return "invalid";
            }
            // Se existir, verifica se a senha está correta
            string senha_hash = geraHash(senha);
            if (it->second.senha_hash == senha_hash) {
                // Se estiver correta, gera um token de acesso
                string token_de_acesso = genRandomString(32);
                // Armazena o token de acesso e o id do usuário
                acessos_liberados.insert(make_pair(token_de_acesso, it->second.id));
                return token_de_acesso;
            }
            return "invalid";
        }

        /**
         * Cria uma loja no marketplace com o nome especificado para o usuário que tem
         * um acesso com esse token.
         * @param token Token de acesso
         * @param nome Nome da loja
         * @return O id da loja, ou -1 caso o token não exista em acessos_liberados ou
         * uma loja com esse nome já exista no marketplace
         */
        int criar_loja(string token, string nome) {
            // TODO Implementar
            return -1;
        }

        /**
         * Adicionando produtos em uma loja(pelo id) de um usuário(pelo token).
         * Não é permitido adicionar um produto em um loja caso seu proprietário não seja o usuário do token passado
         * A quantidade de um produto inserido é 0 (zero)
         * 
         * @return Um id do produto adicionado para ser usado em outras operações
         */
        int adicionar_produto(string token, int loja_id, string nome, float preco) {
            // TODO Implementar
            return -1;
        }

        /**
         * Adiciona uma quantidade em um produto em uma loja(pelo id) de um usuário(pelo token).
         * 
         * @param token Token de acesso
         * @param loja_id Id da loja
         * @param produto_id Id do produto
         * @param quantidade Quantidade a ser adicionada
         * @return retornar novo estoque
         */
        int adicionar_estoque(string token, int loja_id, int produto_id, int quantidade) {
            // TODO Implementar
            return -1;
        }

        /**
         * Muda um produto da loja com o id loja_origem_id para loja_destino_id
         * Garantir que:
         *  - loja_origem_id e loja_destino_id são do usuário
         *  - O produto está originalmente na loja_origem
         *  - loja_origem_id != loja_destino_id
         * 
         * @param token Token de acesso
         * @param loja_origem_id Id da loja de origem
         * @param loja_destino_id Id da loja de destino
         * @param produto_id Id do produto
         * @return True se a operação foi bem sucedida, false caso contrário
         */
        bool transferir_produto(string token, int loja_origem_id, int loja_destino_id, int produto_id) {
            // TODO Implementar
            return false;
        }

        /**
         * Lista de produtos do marketplace que tem a string nome_parcial no nome
         * 
         * @param nome_parcial String que deve aparecer no nome do produto
         * @return Lista de produtos que tem a string nome_parcial no nome
         */
        vector<Produto> buscar_produtos(string nome_parcial) {
            vector<Produto> encontrados;
            // TODO Implementar
            return encontrados;
        }

        /**
         * Lista de produtos de uma loja específica do marketplace que tem a string nome_parcial no nome
         * 
         * @param nome_parcial String que deve aparecer no nome do produto
         * @param loja_id Id da loja
         * @return Lista de produtos que tem a string nome_parcial no nome e que pertencem a loja especificada
         */
        vector<Produto> buscar_produtos(string nome_parcial, int loja_id) {
            vector<Produto> encontrados;
            // TODO Implementar
            return encontrados;
        }

        /**
         * Lista de lojas do marketplace que tem a string nome_parcial no nome
         * 
         * @param nome_parcial String que deve aparecer no nome da loja
         * @return Lista de lojas que tem a string nome_parcial no nome
         */
        vector<Loja> buscar_lojas(string nome_parcial) {
            vector<Loja> encontradas;
            // TODO Implementar
            return encontradas;
        }

        /**
         * Lista de lojas do marketplace
         * 
         * @return Lista de lojas do marketplace
         */
        vector<Loja> listar_lojas() {
            vector<Loja> encontradas;
            // TODO Implementar
            return encontradas;
        }

        /**
         * Cria uma nova Venda para o usuário com acesso com esse token,
         * para o produto especificado, para a loja desse produto e com a quantidade especificada.
         * 
         * @param token Token de acesso
         * @param produto_id Id do produto
         * @param quantidade Quantidade a ser vendida
         * @return Id da venda criada ou -1 caso não seja possível criar a venda
         */
        int comprar_produto(string token, int produto_id, int quantidade) {
            Venda venda;
            // TODO Implementar
            return venda.id;
        }


        // Métodos de debug (adicionar a vontade)
        void show_usuarios() {
            for (auto it = usuarios.begin(); it != usuarios.end(); it++) {
                cout << it->first << " >>> " << it->second.senha_hash << endl;
            }
        }
        void show_tokens() {
            for (auto it = acessos_liberados.begin(); it != acessos_liberados.end(); it++) {
                cout << it->first << " >>> " << it->second << endl;
            }
        }
};

int main() {
    Marketplace marketplace;

    bool cadastro1_ok, cadastro2_ok;

    cadastro1_ok = marketplace.me_cadastrar("João", "joao@gmail.com", "123456");
    testa(cadastro1_ok, "Cadastro de usuário 1");
    cadastro2_ok = marketplace.me_cadastrar("Maria", "maria@gmail.com", "654321");
    testa(cadastro2_ok, "Cadastro de usuário 2");

    marketplace.show_usuarios();

    if ( !cadastro1_ok || !cadastro2_ok) {
        cout << "Cadastro de João ou Maria nao realizado" << endl;
        return -1;
    }

    string invalid_token = marketplace.login("inexistente@hotmail.com", "senha qualquer");
    testa(invalid_token == "invalid", "login de usuario inexistente");
    
    string joao_token = marketplace.login("joao@gmail.com", "123456");
    testa(joao_token != "invalid", "login de usuario valido");
    cout << "Token de acesso recebido para João: " << joao_token << endl;

    if (joao_token != "invalid") {
        cout << "Usuário logado com sucesso" << endl;

        // João cria duas lojas com o seu token de acesso
        int bodega_do_joao_id = marketplace.criar_loja(joao_token, "Bodega do João");
        testa(bodega_do_joao_id != -1, "Cadastro de loja");
        int acougue_do_joao_id = marketplace.criar_loja(joao_token, "Açougue do João");
        testa(acougue_do_joao_id != -1, "Cadastro de loja");
        
        // João adiciona produtos na loja e altera o seu estoque
        int leite_id = marketplace.adicionar_produto(joao_token, bodega_do_joao_id, "Leite em pó", 8.40);
        testa(leite_id != -1, "Cadastro de produto");
        marketplace.adicionar_estoque(joao_token, bodega_do_joao_id, leite_id, 10);
       
        int novo_estoque_leite = marketplace.adicionar_estoque(joao_token, bodega_do_joao_id, leite_id, 5);
        testa(novo_estoque_leite == 15, "Adicionando estoque");
        
        int arroz_id = marketplace.adicionar_produto(joao_token, bodega_do_joao_id, "Arroz", 3.50);
        marketplace.adicionar_estoque(joao_token, bodega_do_joao_id, arroz_id, 40);
        
        int coca_id = marketplace.adicionar_produto(joao_token, bodega_do_joao_id, "Coca cola 250ml", 2.40);
        marketplace.adicionar_estoque(joao_token, bodega_do_joao_id, coca_id, 15);
        
        // João adicionou um produto na loja que não deveria... Aff João...
        int picanha_id = marketplace.adicionar_produto(joao_token, bodega_do_joao_id, "Picanha Maturada", 58.40);
        marketplace.adicionar_estoque(joao_token, bodega_do_joao_id, picanha_id, 5);
        
        int pic_suina_id = marketplace.adicionar_produto(joao_token, acougue_do_joao_id, "Picanha Suína", 78.40);
        marketplace.adicionar_estoque(joao_token, acougue_do_joao_id, pic_suina_id, 8);
        
        // Transferindo um produto de uma loja para outrao (do mesmo usuário)
        marketplace.transferir_produto(joao_token, bodega_do_joao_id, acougue_do_joao_id, pic_suina_id);

        // Logar como Maria
        string maria_token = marketplace.login("maria@gmail.com", "654321");
        marketplace.show_tokens(); // opcional. debug
        marketplace.comprar_produto(maria_token, pic_suina_id, 2);

        // Maria buscando picanha:
        vector<Produto> picanhas = marketplace.buscar_produtos("Picanha");
        
        // verificando se achou picanhas e comprando a primeira
        if (picanhas.size() > 0) {
            marketplace.comprar_produto(maria_token, picanhas[0].id, 1);
        }

        // Maria buscando uma loja qualquer com o nome Bodega
        vector<Loja> bodegas = marketplace.buscar_lojas("Bodega");
        // vendo se existe alguma bodega, se existir, comprando o primeiro produto com o nome Coca
        if (bodegas.size() > 0) {
            vector<Produto> produtos = marketplace.buscar_produtos("Coca", bodegas[0].id);
            if (produtos.size() > 0) {
                marketplace.comprar_produto(maria_token, produtos[0].id, 1);
            }
        }
        
        // mostrando todas as lojas do marketplace
        vector<Loja> lojas = marketplace.listar_lojas();
        cout << "Lista de lojas do marketplace com os seus produtos" << endl;
        for (Loja loja : lojas) {
            cout << loja.nome << endl;
            for (Produto produto : loja.produtos) {
                cout << "\t" << produto.nome << endl;
            }
        }
    } else {
        cout << "Usuário não pode se logar" << endl;
    }

}