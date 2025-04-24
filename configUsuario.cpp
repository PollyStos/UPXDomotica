#include <iostream>
#include <string>
#include <fstream>

// Função que interpreta o comando do usuário
void interpretarComando(const std::string& mensagem) {
    if (mensagem.rfind("nome:", 0) == 0) {
        std::string nome = mensagem.substr(5); // Pega o que vem depois de "nome:"
        std::ofstream config("usuario_config.txt", std::ios::app);
        config << "Nome=" << nome << std::endl;
        config.close();
        std::cout << "Nome configurado: " << nome << std::endl;
    } else if (mensagem.rfind("musica:", 0) == 0) {
        std::string musica = mensagem.substr(7); // Pega o que vem depois de "musica:"
        std::ofstream config("usuario_config.txt", std::ios::app);
        config << "Musica=" << musica << std::endl;
        config.close();
        std::cout << "Música favorita configurada: " << musica << std::endl;
    } else {
        std::cout << "Comando não reconhecido." << std::endl;
    }
}

int main() {
    std::string mensagemUsuario;

    std::cout << "Digite a mensagem recebida (ex: nome: João): ";
    std::getline(std::cin, mensagemUsuario);

    interpretarComando(mensagemUsuario);

    return 0;
}
