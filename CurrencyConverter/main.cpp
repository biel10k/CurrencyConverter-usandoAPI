#include "include/converter.h"
#include <iostream>
#include <map>
#include <limits>
#include <fstream>
#include <string>


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"


std::string lerApiKey(const std::string& caminho) {
    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << caminho << std::endl;
        return "";
    }

    std::string chave;
    std::getline(arquivo, chave);
    arquivo.close();

    return chave;
}


void limparEntrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void exibirCaixa(const std::string& titulo) {
    std::string borda(titulo.size() + 4, '=');
    std::cout << CYAN << "╔" << borda << "╗\n";
    std::cout << "║  " << titulo << "  ║\n";
    std::cout << "╚" << borda << "╝" << RESET << "\n\n";
}


std::string escolherMoeda() {
    std::map<int, std::string> opcoes = {
        {1, "USD"},
        {2, "BRL"},
        {3, "EUR"},
        {4, "JPY"},
        {5, "GBP"}
    };

    exibirCaixa("Escolha a moeda");

    for (const auto& [num, moeda] : opcoes) {
        std::cout << GREEN << num << RESET << " - " << moeda << "\n";
    }
    std::cout << std::endl;

    int escolha = 0;
    while (true) {
        std::cout << YELLOW << "Digite o numero da moeda: " << RESET;
        if (std::cin >> escolha && opcoes.find(escolha) != opcoes.end()) {
            limparEntrada();
            return opcoes[escolha];
        }
        else {
            std::cout << RED << "Opcao invalida, tente novamente." << RESET << "\n";
            limparEntrada();
        }
    }
}

int main() {
    std::string apiKey = lerApiKey("config.txt");
    if (apiKey.empty()) {
        std::cerr << "Chave API não encontrada. Verifique o arquivo config.txt" << std::endl;
        return 1;
    }
    CurrencyConverter converter(apiKey);

    while (true) {
        exibirCaixa("Conversor de Moeda");

        std::cout << "Moeda que você TEM:\n";
        std::string from = escolherMoeda();

        std::cout << "Moeda para qual quer converter:\n";
        std::string to = escolherMoeda();

        double amount = 0;
        std::cout << BLUE << "Digite a quantidade em " << from << ": " << RESET;
        while (!(std::cin >> amount) || amount <= 0) {
            std::cout << RED << "Quantidade inválida, digite um numero positivo." << RESET << "\n";
            limparEntrada();
            std::cout << BLUE << "Digite a quantidade em " << from << ": " << RESET;
        }

        double result = converter.convert(from, to, amount);

        std::cout << GREEN << amount << " " << from << " equivalem a " << result << " " << to << RESET << std::endl;

        // Pergunta se quer fazer outra conversão
        char opcao;
        std::cout << YELLOW << "Quer fazer outra conversao? (s/n): " << RESET;
        std::cin >> opcao;
        limparEntrada();

        if (opcao != 's' && opcao != 'S') {
            std::cout << GREEN << "Obrigado por usar o Conversor de Moeda! Até mais." << RESET << std::endl;
            break;
        }
    }

    return 0;
}