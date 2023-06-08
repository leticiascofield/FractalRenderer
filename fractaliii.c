//Fractal Letícia Scofield
//Axioma: XF+YF+XF+YF+ (teta = 90º)
//Regras: X -> XF-XF+XF+XF-XF
//Y -> YF-YF+YF+YF-YF

//gcc -o fractaliii  fractaliii.c -lSDL2 -lm | ./fractalii
#include <stdio.h>
#include <string.h>
#include "SDL2/SDL.h"
#include <math.h>

int main() {
    char entrada[10000]; // XF+YF+XF+YF+
    char regraX[10000]; // XF-XF+XF+XF-XF
    char regraY[10000]; // YF-YF+YF+YF-YF
    char saida[10000];
    int numFractal;
    int angulacao; // 90
    int estagio = 4;

    FILE *arquivo; // abrir o arquivo "saidaFractaliii.txt" para escrita
    arquivo = fopen("saidaFractaliii.txt", "w");  
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("Número do fractal: "); // leitura dos dados do fractal
    scanf("%d", &numFractal);
    printf("Axioma: ");
    scanf("%s", entrada);
    printf("Angulo em graus: ");
    scanf("%d", &angulacao);
    printf("Regra de X: ");
    scanf("%s", regraX);
    printf("Regra de Y: ");
    scanf("%s", regraY);
    memset(saida, 0, sizeof(saida)); //memset(str, c, n) - copia o caracter c para os n primeiros caracteres do char apontada por str
    int lenEntrada = strlen(entrada); //srtlen - retorna o tamanho do char
    int lenSaida;
    int j = 0;

    fprintf(arquivo, "Estágio 0: "); // retorna no saidaFractaliii.txt o Estágio 0 (axioma), necessário apenas para o fractaliii
    for (int e = 0; e < lenEntrada; e++) {
        fprintf(arquivo, "%c", entrada[e]);
    }
    fprintf(arquivo, "\n");

    for (int h = 0; h < estagio; h++){
        memset(saida, 0, sizeof(saida));
        for (int i = 0; i < lenEntrada; i++) { // iterar pelas posições da entrada, para substituí-la pelo estágio atual
            if (entrada[i] == 'X') {
                strcat(saida, regraX);  // strcat - juntar dois char
            } else if (entrada[i] == 'Y') {
                strcat(saida, regraY);
            } else {
                strncat(saida, &entrada[i], 1); // strncat - igual strcat, mas digo a quantidade que quero juntar
            }
        }

        memset(entrada, 0, sizeof(entrada)); // limpa a entrada
        strcat(entrada, saida); // adiciona os char de saida na entrada
        lenEntrada = strlen(entrada); // lenEntrada e lenSaida são atualizados
        lenSaida = strlen(saida);
        fprintf(arquivo, "Estágio %d: ", h+1);
        for (int s = 0; s < lenSaida; s++) { // imprimir o estágio atual do fractal no arquivo
            if(h != 3){
                fprintf(arquivo, "%c", saida[s]);
            } else{
                if(saida[s] == 'F' || saida[s] == '-' || saida[s] == '+'){
                    fprintf(arquivo, "%c", saida[s]);  // para que imprima apenas o 'F', '-' e '+' no estágio 4
                }
            }
        }
        fprintf(arquivo, "\n");
    }
   
    fclose(arquivo);

    /* IMAGEM FRACTAL - CÓDIGO COM SDL2*/

    SDL_Window *window = NULL; // criação de janela e renderizador
    SDL_Renderer* renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL falhou ao inicializar: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "Fractal Letícia Scofield", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        800, 600, 0
    );

    if (window == NULL) { 
        fprintf(stderr, "Falha ao inicializar a janela SDL: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // define a cor (branco)

    // ATENÇÂO: os nomes das variáveis estão relacionados às coordenadas (x,y), não aos X e Y das regras
    lenSaida = strlen(saida); // lenSaida é atualizado
    double inicioX = 300;
    double finalX = inicioX;
    double inicioY = 200;
    double finalY = inicioY;
    double tamanhoLinha = 200 / (pow(5, estagio - 1)) ;
    double altura;
    double angulo = M_PI/2;
    double direcao = 0;
    

    for (int s = 0; s < lenSaida; s++) {
        if (saida[s] == 'F'){
            double deltaX = tamanhoLinha * cos(direcao);
            double deltaY = tamanhoLinha * sin(direcao);
            double finalX = inicioX + deltaX;
            double finalY = inicioY - deltaY;
            
            SDL_RenderDrawLine(renderer, inicioX, inicioY, finalX, finalY); // desenha a linha com essas coordenadas de início e fim
            
            inicioX = finalX;
            inicioY = finalY;
        } else if (saida[s] == '-') { // mudança de direção em 90º no sentido anti-horário
            direcao += angulo;
        } else if (saida[s] == '+') { // mudança de direção em 90º no sentido horário
            direcao -= angulo;
        }
    }

    SDL_RenderPresent(renderer); // exibe o fractal na tela
    SDL_Delay(5000); // tempo da imagem na tela (em milissegundos)
    SDL_DestroyRenderer(renderer); // exclusão de janela e renderizador
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}