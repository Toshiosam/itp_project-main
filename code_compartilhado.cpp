#include "code_compartilhado.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
//teste
using namespace std;

// Valida o identificador EAN-8
bool CodigoBarras::validar_identificador(const string& id) {
    if (id.length() != 8) return false;
    for (char c : id) {
        if (!isdigit(c)) return false;
    }
    return (calcular_digito_verificador(id.substr(0, 7)) == (id[7] - '0'));
}

// Calcula o dígito verificador
int CodigoBarras::calcular_digito_verificador(const string& id) {
    int soma = 0;
    for (int i = 0; i < 7; ++i) {
        soma += (i % 2 == 0 ? 3 : 1) * (id[i] - '0');
    }
    return (10 - (soma % 10)) % 10;
}

// Codifica os dígitos em barras
string CodigoBarras::codificar_barras(const string& id) {
    const string L_code[10] = {
        "0001101", "0011001", "0010011", "0111101", "0100011",
        "0110001", "0101111", "0111011", "0110111", "0001011"
    };
    const string R_code[10] = {
        "1110010", "1100110", "1101100", "1000010", "1011100",
        "1001110", "1010000", "1000100", "1001000", "1110100"
    };

    string codificacao = "101"; // Marcador de início
    for (int i = 0; i < 4; ++i) {
        codificacao += L_code[id[i] - '0'];
    }
    codificacao += "01010"; // Marcador central
    for (int i = 4; i < 8; ++i) {
        codificacao += R_code[id[i] - '0'];
    }
    codificacao += "101"; // Marcador de fim
    return codificacao;
}

// Gera a imagem PBM
void CodigoBarras::gerar_imagem_pbm(const string& codificacao, const string& nome_arquivo, int largura_area, int altura, int espaco_lateral) {
    ofstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao criar o arquivo!" << endl;
        return;
    }

    int largura_total = espaco_lateral * 2 + codificacao.length() * largura_area;
    int altura_total = altura + espaco_lateral * 2;

    // Cabeçalho do arquivo PBM
    arquivo << "P1\n" << largura_total << " " << altura_total << "\n";

    // Criação da matriz de imagem
    for (int i = 0; i < altura_total; ++i) {
        for (int j = 0; j < largura_total; ++j) {
            if (i < espaco_lateral || i >= altura_total - espaco_lateral) {
                arquivo << "1 "; // Espaço em branco
            } else {
                int posicao = (j - espaco_lateral) / largura_area;
                if (posicao < codificacao.length() && codificacao[posicao] == '1') {
                    arquivo << "0 "; // Barra preta
                } else {
                    arquivo << "1 "; // Espaço em branco
                }
            }
        }
        arquivo << "\n";
    }
    arquivo.close();
}

// Verifica se o arquivo PBM é válido
bool CodigoBarras::verificar_arquivo_pbm(std::ifstream& arquivo) {
    std::string tipo;
    arquivo >> tipo;
    return tipo == "P1";
}

// Lê a imagem PBM
ImagemPBM CodigoBarras::ler_imagem_pbm(std::ifstream& arquivo) {
    ImagemPBM imagem;
    arquivo >> imagem.largura >> imagem.altura;
    imagem.pixels.resize(imagem.altura, std::vector<int>(imagem.largura));
    for (int i = 0; i < imagem.altura; ++i) {
        for (int j = 0; j < imagem.largura; ++j) {
            arquivo >> imagem.pixels[i][j];
        }
    }
    return imagem;
}

// Extrai o identificador da imagem
std::string CodigoBarras::extrair_identificador(const ImagemPBM& imagem) {
    // Implementação da lógica para extrair o identificador a partir da imagem
    // Esta parte do código deve analisar a matriz de pixels e decodificar o código de barras
    return ""; // Retornar o identificador extraído
}
