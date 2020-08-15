#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <time.h>
#include "biblioteca.h"

void lerImagem(char *nomeArquivo, TImagem *auxiliar){
    FILE *arquivo;

    if((arquivo = fopen(nomeArquivo, "rb")) == NULL){
        printf("Problemas na abertura do arquivo ou arquivo inexistente!\n");
        fclose(arquivo);
        exit(1);
    }
    fgets(auxiliar->identificador, sizeof(auxiliar->identificador), arquivo);
    if(strcmp(auxiliar->identificador, "P5\n") != 0){
        printf("ERRO! A imagem não é de formato PGM.\n");
        fclose(arquivo);
        exit(2);
    }
    if(fscanf(arquivo, "%d %d %d\n", &auxiliar->coluna, &auxiliar->linha, &auxiliar->tonalidade) != 3){
        printf("ERRO! Argumentos da imagem inválido.");
        fclose(arquivo);
        exit(3);
    }
    if(auxiliar->tonalidade > 255){
        printf("ERRO! Apenas imagens de 8 bits são suportadas.\n");
        fclose(arquivo);
        exit(4);
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    rewind(arquivo);

    auxiliar->vetor = malloc(tamanho);
    size_t elementos_lidos = fread(auxiliar->vetor, sizeof(unsigned char), tamanho, arquivo);
    if(elementos_lidos != tamanho){
        printf("%s\n", nomeArquivo);
        printf("ERRO! Problemas na alocação de memória.\n");
        fclose(arquivo);
        exit(5);
    }
    fclose(arquivo);
}

void iniciarDicionario(TDicionario *exemplar){
    int i;
    for(i = 0; i < 256; i++){
        exemplar[i].indice = i;
        exemplar[i].palavra = malloc(2);
        exemplar[i].palavra[0] = (char)i;
        exemplar[i].palavra[1] = '\0';
    }
}

int procura(TDicionario *auxiliar, int tamanhoDicionario, char *palavra){
    int i;
    for(i = 0; i < tamanhoDicionario; i++){
        if(strcmp(auxiliar[i].palavra, palavra) == 0){
            return i;
        }
    }
    return -1;
}

int codificaGeraDicionario(TDicionario *exemplar, TImagem *buffer, int valor, int k){
    int tamanhoDicionario = 256, i = 14, j, aux, l = 0;
    char *stringTemporaria = "";
    char *stringTemporaria2;

    while(l < 9){
        while(buffer[l].vetor[i] != '\0'){
            int auxiliar = strlen(stringTemporaria);
            stringTemporaria2 = malloc(auxiliar+2);

            for(j = 0; j < auxiliar; j++){
                stringTemporaria2[j] = stringTemporaria[j];
            }
            stringTemporaria2[auxiliar] = buffer[l].vetor[i];
            stringTemporaria2[auxiliar+1] = '\0';

            aux = procura(exemplar, tamanhoDicionario, stringTemporaria2);
            if(aux != -1){
                stringTemporaria = stringTemporaria2;
            }
            else{
                aux = procura(exemplar, tamanhoDicionario, stringTemporaria);
                if(tamanhoDicionario < valor){
                    exemplar[tamanhoDicionario].palavra = stringTemporaria2;
                    tamanhoDicionario++;
                    free(stringTemporaria);
                    stringTemporaria = malloc(2);
                    stringTemporaria[0] = buffer[l].vetor[i];
                    stringTemporaria[1] = '\0';
                }
                else{
                    free(stringTemporaria);
                    stringTemporaria = malloc(2);
                    stringTemporaria[0] = buffer[l].vetor[i];
                    stringTemporaria[1] = '\0';
                }
            }
            i++;
        }
        i = 14;
        l++;
    }
    if(strcmp(stringTemporaria, "") != 0){
        if(tamanhoDicionario < valor){
            exemplar[tamanhoDicionario].palavra = stringTemporaria2;
            tamanhoDicionario++;
        }
    }

    return tamanhoDicionario;
}

int codifica(TDicionario *exemplar, TImagem buffer, int valor, int k){
    int tamanhoDicionario = valor, i = 14, j, aux, x = 0;
    char *stringTemporaria = "";
    char *stringTemporaria2;

    while(buffer.vetor[i] != '\0'){
        int auxiliar = strlen(stringTemporaria);
        stringTemporaria2 = malloc(auxiliar+2);

        for(j = 0; j < auxiliar; j++){
            stringTemporaria2[j] = stringTemporaria[j];
        }
        stringTemporaria2[auxiliar] = buffer.vetor[i];
        stringTemporaria2[auxiliar+1] = '\0';

        aux = procura(exemplar, tamanhoDicionario, stringTemporaria2);
        if(aux != -1){
            stringTemporaria = stringTemporaria2;
            x++;
        }
        else{
            free(stringTemporaria);
            stringTemporaria = malloc(2);
            stringTemporaria[0] = buffer.vetor[i];
            stringTemporaria[1] = '\0';
        }
        i++;
    }

    if(strcmp(stringTemporaria, "") != 0){
        int aux1 = procura(exemplar, tamanhoDicionario, stringTemporaria);
        if(aux1 != -1){
            x++;
        }
    }
    return x;
}

void carregaBanco(TImagem *dicionarios, TImagem *imagens, TImagem *teste, char *caminho, int k, int i){
    int valor = pow(2, k);
    DIR *d, *b;
    struct dirent *dir, *dirr;
    char caminhoAux[200];
    strcpy(caminhoAux, caminho);
    d = opendir(caminho);
    int aux = 0, j = 0, l = 0, val = 0, w = 0;
    if(d != NULL){
        printf("> Lendo banco de dados e gerando dicionários...\n");
        while((dir = readdir(d)) != NULL){
            if((strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0 || (*dir->d_name) == '.')){
                dir = readdir(d);
                continue;
            }
            strcat(caminho, dir->d_name);
            b = opendir(caminho);
            dicionarios[l].auxiliar = malloc(valor *sizeof(TDicionario));
            iniciarDicionario(dicionarios[l].auxiliar);
            while((dirr = readdir(b)) != NULL){
                if((strcmp(dirr->d_name,".") == 0 || strcmp(dirr->d_name,"..") == 0 || (*dirr->d_name) == '.')){
                    dirr = readdir(b);
                    continue;
                }
                else{
                    strcat(caminho, "\\");
                    strcat(caminho, dirr->d_name);
                    aux = atoi(&dirr->d_name[0]);
                    if(aux != i){
                        lerImagem(caminho, &imagens[j]);
                        strcpy(imagens[j].nomeImagem, dir->d_name);
                        j++;
                    }
                    else{
                        lerImagem(caminho, &teste[w]);
                        strcpy(teste[w].nomeImagem, dir->d_name);
                        w++;
                    }
                }
                strcpy(caminho, caminhoAux);
                strcat(caminho, dir->d_name);
            }
            strcpy(dicionarios[l].nomeImagem, dir->d_name);
            val = codificaGeraDicionario(dicionarios[l].auxiliar, imagens, valor, k);
            dicionarios[l].tonalidade = val;
            j = 0;
            l++;
            strcpy(caminho, caminhoAux);
        }
        closedir(b);
        closedir(d);
    }
}

void testeImagens(TImagem *dicionarios, TImagem *teste, int k, int i){
    int x = 0, y = 0, z = 0, aux = 0, l = 0;
    float cont = 0;
    char nome[3];
    printf("> Codificando imagens teste com dicionários gerados...\n");
    while(l < 40){
        while(x < 40){
            aux = dicionarios[x].tonalidade;
            y = codifica(dicionarios[x].auxiliar, teste[l], aux, k);
            if(y > z){
                z = y;
                strcpy(nome, dicionarios[x].nomeImagem);
            }
            x++;
        }
        x = atoi(&nome[1]);
        y = atoi(&teste[l].nomeImagem[1]);
        l++;
        if(x == y){
            cont++;
        }
        printf("> A imagem s%d_%d.pgm, combina melhor com o dicionário do banco s%d\n", y, i, x);
        x = 0, y = 0, z = 0;
    }
    printf("\nTaxa de acerto: %.1f%%.\n", (cont*100)/40);
}
