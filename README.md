# Renderizador de Fractais

![Fractal 1](https://github.com/leticiascofield/FractalRenderer/assets/125830543/43686ad8-c437-4eb6-824d-0bce0fbc6d86)
![Fractal 2](https://github.com/leticiascofield/FractalRenderer/assets/125830543/2ebdf9f0-da6d-4be4-aa98-703cb86fceb5)
![Fractal 3](https://github.com/leticiascofield/FractalRenderer/assets/125830543/be188101-881b-453c-b515-fff9fdfe470f)

## Instruções para Configuração

Instruções necessárias para executar os códigos do projeto. Certifique-se de ter instalado corretamente todas as dependências e bibliotecas necessárias para garantir que o programa seja executado sem erros. Caso tenha dificuldades com o entendimento do código, leia os comentários.

## Ambiente Computacional

Certifique-se de ter os seguintes requisitos em seu ambiente computacional:
- Compilador GCC (GNU Compiler Collection)
- Biblioteca SDL2 (Simple DirectMedia Layer) instalada
- Biblioteca matemática (math.h)

## Instalação de SDL2 para Linux (Ubuntu)

Abra o terminal e execute os seguintes comandos:
```
sudo apt update
sudo apt install libsdl2-dev
```

## Passos para Execução

Siga as instruções abaixo para executar os códigos:

-  ### Compilação
    Compile os códigos-fonte usando o GCC com os seguintes comandos: <br>
    ```
    gcc -o fractali fractali.c -lSDL2 -lm
    gcc -o fractalii fractalii.c -lSDL2 -lm
    gcc -o fractaliii fractaliii.c -lSDL2 -lm
    ```

- ### Floco de Neve Onda Senoidal 2 de Von Koch

   Execute o programa gerado com o seguinte comando:
   ```
   ./fractali
   ```
   
   O programa solicitará algumas informações:
   ```
   linha 1: 4
   linha 2: F
   linha 3: 60
   linha 4: F-F+F+FF-F-F+F
   ```
   
   O programa gerará um arquivo chamado "saidaFractali.txt" contendo os 4 primeiros estágios de construção do fractal, conforme especificado pela regra.

- ### Preenchimento de Espaço de Hilbert

   Execute o programa gerado com o seguinte comando:
   ```
   ./fractalii
   ```
   
   O programa solicitará algumas informações:
   ```
   linha 1: 6
   linha 2: X
   linha 3: 90
   linha 4: -YF+XFX+FY-
   linha 5: +XF-YFY-FX+
   ```

   O programa gerará um arquivo chamado "saidaFractalii.txt" contendo os 4 primeiros estágios de construção do fractal, conforme especificado pela regra.

- ### Fractal Letícia Scofield

   Execute o programa gerado com o seguinte comando:
   ```
   ./fractaliii
   ```
   
   O programa solicitará algumas informações:
   ```
   linha 1: 8
   linha 2: XF+YF+XF+YF+
   linha 3: 90
   linha 4: XF-XF+XF+XF-XF
   linha 5: YF-YF+YF+YF-YF
   ```

   O programa gerará um arquivo chamado "saidaFractaliii.txt" contendo os 4 primeiros estágios de construção do fractal, conforme especificado pela regra.

-  ### Visualização
   Além disso, para cada execução, o programa exibirá uma janela de visualização do fractal usando a biblioteca SDL2. A janela mostrará o fractal no estágio 4. Após 5 segundos, a janela será fechada e o programa será encerrado.
