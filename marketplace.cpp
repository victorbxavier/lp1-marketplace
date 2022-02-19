#include "marketplace.hpp"
#include "utils.h"

// TODO Separa a implementação em .h e .cpp do Marketplace
Marketplace::Marketplace() {

}


bool Marketplace::me_cadastrar(string nome, string email, string senha) {
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
string Marketplace::login(string email, string senha) {
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
int Marketplace::criar_loja(string token, string nome) {
    // TODO Implementar

    Loja nova_loja;
    Usuario novo;
    int verifica = verifica_token(token);
    
    //Se não tiver nenhuma loja no map, não precisa verirficar se já existe uma loja com o mesmo nome passado
    if(lojas.size() < 1 && verifica == 1){
      nova_loja.id = lojas.size() +1;
      nova_loja.nome = nome;
      for(auto it = usuarios.begin(); it != usuarios.end(); ++it){
        nova_loja.proprietario = it ->second;
        break;
      }
      lojas.insert(make_pair(nova_loja.id, nova_loja));
      return nova_loja.id;
    }

    for(auto itr = lojas.begin(); itr != lojas.end(); ++itr){
      if(itr -> second.nome != nome && verifica == 1){
        nova_loja.id = lojas.size() +1;
        nova_loja.nome = nome;
        for(auto it = usuarios.begin(); it != usuarios.end(); ++it){
          nova_loja.proprietario = it ->second;
          break;
      }
      lojas.insert(make_pair(nova_loja.id, nova_loja));
      return nova_loja.id;
    }
  }

    return -1;
}

/**
 * Adicionando produtos em uma loja(pelo id) de um usuário(pelo token).
 * Não é permitido adicionar um produto em um loja caso seu proprietário não seja o usuário do token passado
 * A quantidade de um produto inserido é 0 (zero)
 * 
 * @return Um id do produto adicionado para ser usado em outras operações
 */
int Marketplace::adicionar_produto(string token, int loja_id, string nome, float preco) {
    // TODO Implementar

    int verificar = verifica_token(token);
    map<int,Loja>::iterator it;
    it=lojas.find(loja_id);

    if(verificar == 1){

      if(it!=lojas.end()){
        
        Produto novo_produto;
        novo_produto.id = id_produtos;
        novo_produto.quantidade = 0;
        novo_produto.nome = nome;
        novo_produto.preco = preco;
        id_produtos++;
        
        lojas[loja_id].produtos.push_back(novo_produto);
        produtos.push_back(novo_produto);

        return novo_produto.id;
        
      }
    }

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
int Marketplace::adicionar_estoque(string token, int loja_id, int produto_id, int quantidade) {
    // TODO Implementar

  map<string, int>::iterator it;
    it=acessos_liberados.find(token);

    map<int,Loja>::iterator it2;
    it2=lojas.find(loja_id);   

    if((it!=acessos_liberados.end()) && (it2!=lojas.end())){

      for (size_t i = 0; i < lojas[loja_id].produtos.size(); i++){

        if(lojas[loja_id].produtos[i].id==produto_id){

          lojas[loja_id].produtos[i].quantidade=quantidade;

          return quantidade;
        }
      }
    }

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
bool Marketplace::transferir_produto(string token, int loja_origem_id, int loja_destino_id, int produto_id) {
    // TODO Implementar


   map<string, int>::iterator it;
    it=acessos_liberados.find(token);

    map<int,Loja>::iterator it2;
    it2=lojas.find(loja_origem_id);

    map<int,Loja>::iterator it3;
    it3=lojas.find(loja_destino_id);

    if( (it!=acessos_liberados.end()) && (loja_origem_id!=loja_destino_id) && (it2!=lojas.end()) && (it3!=lojas.end()) ){

      for (size_t i = 0; i < lojas[loja_origem_id].produtos.size(); i++){

        if(lojas[loja_origem_id].produtos[i].id==produto_id){

          lojas[loja_destino_id].produtos.push_back(lojas[loja_origem_id].produtos[i]);
          //vector<Produto>::iterator it4;

          auto it4=find_if(lojas[loja_origem_id].produtos.begin(),lojas[loja_origem_id].produtos.end(),
          [&](Produto p){
            return p.id=produto_id;
          });
          

          lojas[loja_origem_id].produtos.erase(it4);

          // int pos=lojas[loja_destino_id].produtos.size()-1;

          // cout<<lojas[loja_destino_id].produtos[pos].nome<<endl;

          return true;
        }
      }

    }


    return false;
}

/**
 * Lista de produtos do marketplace que tem a string nome_parcial no nome
 * 
 * @param nome_parcial String que deve aparecer no nome do produto
 * @return Lista de produtos que tem a string nome_parcial no nome
 */
vector<Produto> Marketplace::buscar_produtos(string nome_parcial) {
    vector<Produto> encontrados;
    // TODO Implementar

    for(auto itr = lojas.begin(); itr != lojas.end(); ++itr){
      for(int i = 0; i<lojas[itr->first].produtos.size(); ++i){
          if(lojas[itr->first].produtos[i].nome.find(nome_parcial) != string::npos){
            encontrados.push_back(lojas[itr->first].produtos[i]);
        }
      }
    }

    if(encontrados.size() == 0){
      cout << "Produto não encontrado." << endl;
    }

    return encontrados;
}

/**
 * Lista de produtos de uma loja específica do marketplace que tem a string nome_parcial no nome
 * 
 * @param nome_parcial String que deve aparecer no nome do produto
 * @param loja_id Id da loja
 * @return Lista de produtos que tem a string nome_parcial no nome e que pertencem a loja especificada
 */
vector<Produto> Marketplace::buscar_produtos(string nome_parcial, int loja_id) {
    vector<Produto> encontrados;
    // TODO Implementar

    auto itr = lojas.find(loja_id);
    
    if(itr == lojas.end()){
      cout << "Loja não encontrada" << endl;
    }else{
      for(int i = 0; i < lojas[loja_id].produtos.size(); ++i){
        if(lojas[loja_id].produtos[i].nome.find(nome_parcial) != string::npos){
          encontrados.push_back(lojas[loja_id].produtos[i]);
        }
      }
    }

    return encontrados;
}

/**
 * Lista de lojas do marketplace que tem a string nome_parcial no nome
 * 
 * @param nome_parcial String que deve aparecer no nome da loja
 * @return Lista de lojas que tem a string nome_parcial no nome
 */
vector<Loja> Marketplace::buscar_lojas(string nome_parcial) {
    vector<Loja> encontradas;
    // TODO Implementar

    Loja erro;
    for(auto itr = lojas.begin(); itr != lojas.end(); ++itr){
      if(nome_parcial == itr->second.nome){
      encontradas.push_back(itr->second);
      }else{
        erro.nome = "Loja não encontrada";
        encontradas.push_back(erro);
      }
    }
    return encontradas;
}

/**
 * Lista de lojas do marketplace
 * 
 * @return Lista de lojas do marketplace
 */
vector<Loja> Marketplace::listar_lojas() {
    vector<Loja> encontradas;
    // TODO Implementar

    for(auto itr = lojas.begin(); itr != lojas.end(); ++itr){
      encontradas.push_back(itr->second);
    }

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
int Marketplace::comprar_produto(string token, int produto_id, int quantidade) {
  Venda venda;
  // TODO Implementar

  int verifica = verifica_token(token);

  if(verifica == 1){
    venda.id = vendas.size() + 1;
    venda.produto_id = produto_id;
    venda.quantidade = quantidade;

    for(auto itr = acessos_liberados.begin(); itr != acessos_liberados.end(); ++itr ){
      if(itr->first == token) venda.comprador_id = itr->second;
    }

    for(auto itr = lojas.begin(); itr != lojas.end(); ++itr){
      for(int i = 0; i < lojas[itr->first].produtos.size(); ++i){
        if(produtos[i].id == produto_id){
          venda.preco_unitario = produtos[i].preco;
          venda.loja_id = lojas[itr->first].id;
          produtos[i].quantidade--;
        }
      }
    }

    vendas.push_back(venda);


    
    
  }else{
    cout << "Não foi possível completar a venda" << endl;
    return -1;
  }

    return venda.id;
}


// Métodos de debug (adicionar a vontade)
void Marketplace::show_usuarios() {
    for (auto it = usuarios.begin(); it != usuarios.end(); it++) {
        cout << it->first << " >>> " << it->second.senha_hash << endl;
    }
}
void Marketplace::show_tokens() {
    for (auto it = acessos_liberados.begin(); it != acessos_liberados.end(); it++) {
        cout << it->first << " >>> " << it->second << endl;
    }
}

int Marketplace::verifica_token(string token){
  for(auto itr = acessos_liberados.begin(); itr != acessos_liberados.end(); ++itr){
    if(itr -> first == token){
      return 1;
    }
  }
  return 0;
}

