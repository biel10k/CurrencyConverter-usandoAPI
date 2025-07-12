#include "../include/converter.h"
#include "../include/json.hpp"
#include <cpr/cpr.h>
#include <map>
#include <iostream>


using json = nlohmann::json;

CurrencyConverter::CurrencyConverter(const std::string& apiKey) : apiKey(apiKey) {}

std::map<std::string, double> CurrencyConverter::getRates(const std::string& baseCurrency) {
    std::map<std::string, double> rates;

    std::string url = "https://v6.exchangerate-api.com/v6/" + apiKey + "/latest/" + baseCurrency;
    cpr::Response r = cpr::Get(cpr::Url{ url });

    if (r.status_code != 200) {
        std::cerr << "Erro ao buscar taxas de câmbio: " << r.status_code << std::endl;
        return rates;
    }

    json response = json::parse(r.text);

    if (response["result"] != "success") {
        std::cerr << "Erro na resposta da API: " << response.dump(2) << std::endl;
        return rates;
    }

    for (auto& [currency, rate] : response["conversion_rates"].items()) {
        rates[currency] = rate;
    }

    return rates;
}

double CurrencyConverter::convert(const std::string& from, const std::string& to, double amount) {
    auto rates = getRates(from);
    if (rates.find(to) == rates.end()) {
        std::cerr << "Moeda de destino inválida: " << to << std::endl;
        return 0.0;
    }

    return amount * rates[to];
}