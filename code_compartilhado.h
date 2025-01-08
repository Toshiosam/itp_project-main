#ifndef CODE_COMPARTILHADO_H
#define CODE_COMPARTILHADO_H

#include <string>
#include <vector>
#include <fstream>

struct ImagemPBM {
    int largura;
    int altura;
    std::vector<std::vector<int>> pixels;
};

class CodigoBarras {
public:
    static bool validar_identificador(const std::string& id);
    static int calcular_digito_verificador(const std::string& id);
    static std::string codificar_barras(const std::string& id);
    static void gerar_imagem_pbm(const std::string& codificacao, const std::string& nome_arquivo, int largura_area, int altura, int espaco_lateral);
    static bool verificar_arquivo_pbm(std::ifstream& arquivo);
    static ImagemPBM ler_imagem_pbm(std::ifstream& arquivo);
    static bool verificar_codigo_barras(const ImagemPBM& imagem);
    static std::string extrair_identificador(const ImagemPBM& imagem);
};

#endif // CODE_COMPARTILHADO_H