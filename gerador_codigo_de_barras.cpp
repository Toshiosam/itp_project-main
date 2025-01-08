#include "code_compartilhado.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <identificador> [espaco_lateral] [largura_area] [altura] [nome_arquivo]" << endl;
        return 1;
    }

    string identificador = argv[1];
    int espaco_lateral = (argc > 2) ? stoi(argv[2]) : 10; // Valor padrão
    int largura_area = (argc > 3) ? stoi(argv[3]) : 2; // Valor padrão
    int altura = (argc > 4) ? stoi(argv[4]) : 100; // Valor padrão
    string nome_arquivo = (argc > 5) ? argv[5] : "codigo_barras.pbm"; // Valor padrão

    if (!CodigoBarras::validar_identificador(identificador)) {
        cerr << "Identificador inválido!" << endl;
        return 1;
    }

    ifstream arquivo_existente(nome_arquivo);
    if (arquivo_existente.is_open()) {
        string resposta;
        cout << "O arquivo " << nome_arquivo << " já existe. Deseja sobrescrevê-lo? (s/n): ";
        cin >> resposta;
        if (resposta != "s") {
            cerr << "Arquivo resultante já existe." << endl;
            return 1;
        }
    }

    string codificacao = CodigoBarras::codificar_barras(identificador);
    CodigoBarras::gerar_imagem_pbm(codificacao, nome_arquivo, largura_area, altura, espaco_lateral);
    cout << "Imagem PBM gerada com sucesso: " << nome_arquivo << endl;

    return 0;
}