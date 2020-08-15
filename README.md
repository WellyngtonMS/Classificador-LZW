# Classificador LZW
Implementar um reconhecedor de padrões baseado em LZW. Utilize um banco de dados previamente rotulado, na etapa de treinamento gere um modelo LZW (dicionário) para cada categoria do banco de dados selecionado.

Organize o banco de dados em amostras de treino e classificação utilizando a técnica de validação cruzada. Isto é, para cada categoria do banco de dados, selecione todas as
amostras - 1 para treinamento e 1 amostra para classificação, a seleção dessas amostras deve ser aleatória. Para classificação utilize o algoritmo dos K-Vizinhos mais próximos (K-NN, k-nearest neighbors) com k = 1, utilizando como métrica de distância o tamanho do arquivo comprimido. Outra possibilidade de métrica de distância é a quantidade de índices utilizado pelo LZW, antes da serialização para bytes.

O treinamento consiste em gerar o dicionário de cada categoria do banco de dados. A classificação/testes consiste em comprimir 1 amostra (que não foi utilizada na geração do
modelo) em todos os modelos/dicionários. Durante a compressão da amostra de teste o dicionário deve permanecer estático. A amostra de teste deve ser atribuída ao modelo que proporcionou a melhor compressão.

Bancos de dados a ser utilizado:
Iris Database Palacký University. Utilizar as 40 das 64 pessoas disponíveis no banco. Cada pessoa possui 6 fotos de sua íris.

#### Instruções para compilar e rodar a implementação:

1. descompacte o arquivo .rar em uma pasta exclusiva para os arquivos, em que contenha somente eles.
2. compilar e executar o programa pelo terminal de comando:

   2.1 primeiro navegue até a pasta em que foi descompactado os arquivos, como dito na instrução 1.
 
   2.2 depois insira os seguintes comandos:
 
    ````
    gcc -o classificador main.c funcoes.c (para compilar)
    .\classificador (para executar o programa)
   ````
   2.3 agora é necessário informar o caminho onde o banco de dados está, para isso eu recomendo que coloque a pasta na área de trabalho, para evitar erros na leitura do diretório. 
   ````
   Ex.: C:\Users\Desktop\Database\
   ````
   É de extrema importância colocar uma barra \ no fical do diretório.
   
   2.4 agora é só informar o valor de k em bits e aguardar o processamento com os resultados no fim.
 
3. compilar e executar o programa por alguma IDE:

   3.1 crie um projeto e insira os arquivos da pasta mencionada na instrução 1.
   
   3.2 compile e execute o programa.
   
   3.3 agora é só seguir as instruções à partir da instrução 2.3
