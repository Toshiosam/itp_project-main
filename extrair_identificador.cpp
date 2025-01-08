#include "code_compartilhado.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <nome_arquivo>" << endl;
        return 1;
    }

    string nome_arquivo = argv[1];
    ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    if (!CodigoBarras::verificar_arquivo_pbm(arquivo)) {
        cerr << " Arquivo não é um arquivo PBM válido!" << endl;
        return 1;
    }

    ImagemPBM imagem = CodigoBarras::ler_imagem_pbm(arquivo);
    string identificador = CodigoBarras::extrair_identificador(imagem);
    
    if (identificador.empty()) {
        cerr << "Não foi possível extrair o identificador da imagem." << endl;
        return 1;
    }

    cout << "Identificador extraído: " << identificador << endl;
    return 0;
}