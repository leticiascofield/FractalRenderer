

// gcc -o fractal1.2 fractal1.2.c -lSDL2 -lm
// ./fractal1.2
#include <stdio.h>
#include <string.h>
#include "SDL2/SDL.h"
#include <math.h>

int main(int argc, char **argv) {
    char entrada[10000];
    char regra[10000];
    char regraX[10000];
    char regraY[10000];
    char saida[10000];
    char axioma;
    int numFractal;
    int angulacao = 60;
    int estagio;

    printf("Número do fractal: ");
    scanf("%d", &numFractal);
    printf("Axioma: ");
    scanf("%s", &axioma);
    printf("Angulo em graus: ");
    scanf("%d", &angulacao);
    
    if(axioma == 'F'){
        printf("Regra: ");
        scanf("%s", regra);
    } else if(axioma == 'X'){
        printf("Regra de X: ");
        scanf("%s", regraX);
        printf("Regra de Y: ");
        scanf("%s", regraY);
    }
    printf("Estágio: ");
    scanf("%d", &estagio);

    entrada[0] = axioma;
    memset(saida, 0, sizeof(saida)); //memset(str, c, n) - copia o caracter c para os n primeiros caracteres da string apontada por str
    int lenEntrada = strlen(entrada); //srtlen - retorna o tamanho da string
    int j = 0;
    
    for(int h = 0; h < estagio; h++){
        memset(saida, 0, sizeof(saida));
        for(int i = 0; i < lenEntrada; i++){
            if(axioma == 'F'){
                if(entrada[i] == 'F'){
                    strcat(saida, regra); //strcat - juntar duas strings
                } else {
                    strncat(saida, &entrada[i], 1); //strncat - igual strcat, mas digo a quantidade que quero juntar
                }
            } else if(axioma == 'X'){
                if(entrada[i] == 'X') {
                    strcat(saida, regraX); 
                } else if(entrada[i] == 'Y') {
                    strcat(saida, regraY);
                } else {
                    strncat(saida, &entrada[i], 1);
                }
            }
        }

        memset(entrada, 0, sizeof(entrada));
        strcat(entrada, saida);
        lenEntrada = strlen(entrada);
    }

    printf("Saída: %s\n", saida);


    /* IMAGEM FRACTAL - CÓDIGO COM SDL2*/

    SDL_Window *window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL falhou ao inicializar: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "Floco de neve onda senoidal 2 de von Koch", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        800, 600, 0
    );

    if (window == NULL) { 
        fprintf(stderr, "Falha ao inicializar a janela SDL: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int lenSaida = strlen(saida); 
    double inicioX;
    double finalX;
    double inicioY = 300;
    double finalY = 300;
    double tamanhoLinha; // para que a imagem continue do mesmo tamanho na tela
    double altura;
    double angulo = angulacao*M_PI/180;
    double direcao = 0;
    
    if(axioma == 'F'){
        inicioX = 100;
        finalX = inicioX;
        inicioY = 300;
        finalY = inicioY;
        if(regra[0] == 'F'){
            tamanhoLinha = (600 / pow(6, estagio));
        } else {
            tamanhoLinha = (600 / pow(3, estagio));
        }
    } else {
        inicioX = 200;
        finalX = inicioX;
        inicioY = 500;
        finalY = inicioY;
        tamanhoLinha = 400 / (pow(2, estagio) - 1);
    }

    for (int s = 0; s < lenSaida; s++) {
        if (saida[s] == 'F') {
            double deltaX = tamanhoLinha * cos(direcao);
            double deltaY = tamanhoLinha * sin(direcao);
            double finalX = inicioX + deltaX;
            double finalY = inicioY - deltaY;
            
            SDL_RenderDrawLine(renderer, inicioX, inicioY, finalX, finalY);
            
            inicioX = finalX;
            inicioY = finalY;
        } else if (saida[s] == '-') {
            direcao += angulo;
        } else if (saida[s] == '+') {
            direcao -= angulo;
        }
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(4000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}