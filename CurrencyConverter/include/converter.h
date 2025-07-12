#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <map>

class CurrencyConverter {
public:
    CurrencyConverter(const std::string& apiKey);

    // Retorna o valor convertido de uma moeda para outra
    double convert(const std::string& from, const std::string& to, double amount);

    // Retorna as taxas disponíveis com base na moeda base
    std::map<std::string, double> getRates(const std::string& baseCurrency);

private:
    std::string apiKey;
};

#endif