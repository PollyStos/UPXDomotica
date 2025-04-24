#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"

using json = nlohmann::json;

std::string token = "AAEjim7QPVZfR0gYg255IIlrt5tcDthvLRk";
std::string chat_id = "7346630970";

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output) {
    output->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    std::string url = "https://api.telegram.org/bot" + token + "/getUpdates";

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(curl, CURLOPT_CAINFO, "cacert.pem");

        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            json jsonData = json::parse(readBuffer);
            if (jsonData.contains("result")) {
                for (const auto& update : jsonData["result"]) {
                    std::string msgText = update["message"]["text"];
                    std::string senderId = std::to_string(update["message"]["chat"]["id"].get<long long>());

                    std::cout << "Mensagem recebida: " << msgText << std::endl;

                    if (msgText == "config") {
                        std::string menu = "🛠️ *Modo de Configuração*\nEscolha uma opção:\n1️⃣ Nome\n2️⃣ Música favorita\n3️⃣ Cor preferida";
                        std::string urlSend = "https://api.telegram.org/bot" + token + "/sendMessage";
                        std::string postData = "chat_id=" + senderId + "&text=" + curl_easy_escape(curl, menu.c_str(), menu.length());

                        curl_easy_setopt(curl, CURLOPT_URL, urlSend.c_str());
                        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
                        curl_easy_perform(curl);
                    }
                }
            }
        } else {
            std::cerr << "Erro ao buscar mensagens: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
