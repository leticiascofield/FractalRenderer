//Preenchimento de espaço de Hilbert
//Axioma: X (teta = 90º)
//Regras: X -> -YF+XFX+FY-
//Y -> +XF-YFY-FX+

#include <stdio.h>
#include <string.h>
#include "SDL2/SDL.h"
#include <math.h>

int main() {
    char entrada[10000] = "X";
    char regraX[10000] = "-YF+XFX+FY-";
    char regraY[10000] = "+XF-YFY-FX+";
    char saida[10000];
    int angulacao = 90;
    int estagio;
    printf("Axioma: %s\n", entrada);
    printf("Angulação: %d\n", angulacao);
    printf("Regra de X: %s\n", regraX);
    printf("Regra de Y: %s\n", regraY);
    printf("Estágio: ");
    scanf("%d", &estagio);
    memset(saida, 0, sizeof(saida)); 
    int lenEntrada = strlen(entrada);
    int j = 0;
    
    for (int h = 0; h < estagio; h++){
        memset(saida, 0, sizeof(saida));
        for (int i = 0; i < lenEntrada; i++) {
            if (entrada[i] == 'X') {
                strcat(saida, regraX); 
            } else if (entrada[i] == 'Y') {
                strcat(saida, regraY);
            } else {
                strncat(saida, &entrada[i], 1);
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
        "Preenchimento de espaço de Hilbert", 
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

    // ATENÇÂO: os nomes das variáveis estão relacionados às coordenadas (x,y), não aos X e Y das regras
    int lenSaida = strlen(saida); 
    double inicioX = 200;
    double finalX = inicioX;
    double inicioY = 500;
    double finalY = inicioY;
    double tamanhoLinha = 400 / (pow(2, estagio) - 1); // para que a imagem continue do mesmo tamanho na tela
    double altura;
    double angulo = M_PI/2;
    double direcao = 0;
    

    for (int s = 0; s < lenSaida; s++) {
        if (saida[s] == 'F'){
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
    SDL_Delay(3000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}