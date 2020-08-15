typedef struct dicionario{
    char *palavra;
    int indice;
}TDicionario;

typedef struct imagem{
    int coluna;
    int linha;
    int tonalidade;
    unsigned char *vetor;
    char identificador[4];
    TDicionario *auxiliar;
    char nomeImagem[6];
}TImagem;

void lerImagem(char *nomeArquivo, TImagem *auxiliar);
void iniciarDicionario(TDicionario *exemplar);
int procura(TDicionario *auxiliar, int tamanhoDicionario, char *palavra);
int codificaGeraDicionario(TDicionario *exemplar, TImagem *buffer, int valor, int k);
int codifica(TDicionario *exemplar, TImagem buffer, int valor, int k);
void carregaBanco(TImagem *dicionarios, TImagem *imagens, TImagem *teste, char *caminho, int k, int i);
void testeImagens(TImagem *dicionarios, TImagem *teste, int k, int i);
