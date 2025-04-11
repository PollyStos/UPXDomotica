#include <iostream>
#include <string>
#include <curl/curl.h>

int main() {

    std::string token = "7682687913:AAEjim7QPVZfR0gYg255IIlrt5tcDthvLRk";
    std::string chat_id = "7346630970";
    std::string mensagem = "A mensagem é essa. Coloque a variavel aqui!";



    CURL *curl;
    CURLcode res;


    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        std::string url = "https://api.telegram.org/bot" + token + "/sendMessage";
        std::string data = "chat_id=" + chat_id + "&text=" + curl_easy_escape(curl, mensagem.c_str(), mensagem.length());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        // ⚠️ Desativa verificação SSL (só para testes locais!)
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(curl, CURLOPT_CAINFO, "F:/projetos/faculdade/facens/UPX Domotica/cacert.pem");


        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Erro ao enviar mensagem: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Mensagem enviada com sucesso!" << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
