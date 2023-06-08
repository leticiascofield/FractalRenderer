//Floco de neve onda senoidal 2 de von Koch
//Axioma: F (teta = 60º)
//Regra: F -> F-F+F+FF-F-F+F

//gcc -o fractali  fractali.c -lSDL2 -lm | ./fractali
#include <stdio.h>
#include <string.h>
#include "SDL2/SDL.h"
#include <math.h>

int main(int argc, char **argv) {
    char entrada[10000]; // F
    char regra[10000]; // F-F+F+FF-F-F+F
    char saida[10000];
    int numFractal;
    int angulacao;
    int estagio = 4;

        FILE *arquivo;
    arquivo = fopen("saidaFractali.txt", "w");  
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("Número do fractal: ");
    scanf("%d", &numFractal);
    printf("Axioma: ");
    scanf("%s", entrada);
    printf("Angulo em graus: ");
    scanf("%d", &angulacao);
    printf("Regra: ");
    scanf("%s", regra);
    memset(saida, 0, sizeof(saida)); //memset(str, c, n) - copia o caracter c para os n primeiros caracteres da string apontada por str
    int lenEntrada = strlen(entrada); //srtlen - retorna o tamanho da string
    int lenSaida;
    int j = 0;
    

    for(int h = 0; h < estagio; h++){
        memset(saida, 0, sizeof(saida));
        for(int i = 0; i < lenEntrada; i++) {
            if(entrada[i] == 'F') {
                strcat(saida, regra); //strcat - juntar duas strings
            } else {
                strncat(saida, &entrada[i], 1); //strncat - igual strcat, mas digo a quantidade que quero juntar
            }
        }

        memset(entrada, 0, sizeof(entrada));
        strcat(entrada, saida);
        lenEntrada = strlen(entrada);
        lenSaida = strlen(saida);
        fprintf(arquivo, "Estágio %d: ", h+1);
        for (int s = 0; s < lenSaida; s++) {
            if(saida[s] == 'F' || saida[s] == '-' || saida[s] == '+'){
                fprintf(arquivo, "%c", saida[s]); // para que imprima apenas o 'F', '-' e '+'
            }
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);


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

    lenSaida = strlen(saida); 
    double inicioX = 100;
    double finalX = 100;
    double inicioY = 300;
    double finalY = 300;
    double tamanhoLinha = (600 / pow(6, estagio)); // para que a imagem continue do mesmo tamanho na tela
    double altura;
    double angulo = M_PI/3;
    double direcao = 0;
    

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
    SDL_Delay(5000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}