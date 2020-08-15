#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include "biblioteca.h"

int main(){
    setlocale(LC_ALL, "Portuguese");

    TImagem dicionarios[40];
    TImagem imagens[9];
    TImagem teste[40];
    int k = 0, i;
    char caminho[200];

    printf("> Digite o diretório do Banco de dados (Ex.: C:\\Users\\Desktop\\Database\\)\n> ");
    scanf("%s", caminho);
    fflush(stdin);

    printf("> Digite o valor de K em bits entre 9 e 16\n> ");
    scanf("%d", &k);
    fflush(stdin);

    srand(time(NULL));
    i = 1 + (rand()%10);
    carregaBanco(dicionarios, imagens, teste, caminho, k, i);
    testeImagens(dicionarios, teste, k , i);

    return 0;
}
