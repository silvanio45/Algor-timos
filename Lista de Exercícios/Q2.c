#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int TamVet = 100000, QtdVet = 1000;
clock_t tInicio;
clock_t tAleatorio;

double TempoTotal_Inicio = 0;
double TempoTotal_Aleatorio = 0;

double MaximoInicio = 0;
double MinimoInicio = 100000;

double MaximoAleatorio = 0;
double MinimoAleatorio = 100000;

void geraVet(int **vet, int QtdVet, int TamVet) {
    for (int i = 0; i < QtdVet; i++) {
        for (int j = 0; j < TamVet; j++) {
            vet[i][j] = rand();
        }
    }
}

void copiaVet(int *origem, int *destino, int TamVet) {
    for (int i = 0; i < TamVet; i++) {
        destino[i] = origem[i];
    }
}

int particionaInicio(int *v, int inicio, int fim) {
    int pivo = v[inicio];
    int esquerda = inicio + 1;
    int direita = fim;

    while (esquerda <= direita) {
        while (esquerda <= fim && v[esquerda] <= pivo) {
            esquerda++;
        }
        while (direita >= inicio && v[direita] > pivo) {
            direita--;
        }
        if (esquerda < direita) {
            int aux = v[esquerda];
            v[esquerda] = v[direita];
            v[direita] = aux;
        }
    }
    int aux = v[inicio];
    v[inicio] = v[direita];
    v[direita] = aux;
    
    return direita;
}

int particionaAleatorio(int *v, int inicio, int fim) {
    int randIndex = inicio + rand() % (fim - inicio + 1);
    int pivo = v[randIndex];
    int esquerda = inicio + 1;
    int direita = fim;

    while (esquerda <= direita) {
        while (esquerda <= fim && v[esquerda] <= pivo) {
            esquerda++;
        }
        while (direita >= inicio && v[direita] > pivo) {
            direita--;
        }
        if (esquerda < direita) {
            int aux = v[esquerda];
            v[esquerda] = v[direita];
            v[direita] = aux;
        }
    }
    int aux = v[inicio];
    v[inicio] = v[direita];
    v[direita] = aux;
    
    return direita;
}

void QuickSortInicio(int* v, int inicio, int fim) {
    if (inicio < fim) {
        int posicao = particionaInicio(v, inicio, fim);
        QuickSortInicio(v, inicio, posicao - 1);
        QuickSortInicio(v, posicao + 1, fim);
    }
}

void QuickSortAleatorio(int* v, int inicio, int fim) {
    if (inicio < fim) {
        int posicao = particionaAleatorio(v, inicio, fim);
        QuickSortAleatorio(v, inicio, posicao - 1);
        QuickSortAleatorio(v, posicao + 1, fim);
    }
}

int main() {
    srand(time(NULL));

    int **vet = (int **)malloc(QtdVet * sizeof(int *));
    for (int i = 0; i < QtdVet; i++) {
        vet[i] = (int *)malloc(TamVet * sizeof(int));
    }

    geraVet(vet, QtdVet, TamVet);

    int *copia = (int *)malloc(TamVet * sizeof(int));
    int teto = 1000, cont = 0;
    
    while(cont < teto){
        
        copiaVet(vet[cont], copia, TamVet);

        tInicio = clock();
        QuickSortInicio(copia, 0, TamVet - 1);
        tInicio = clock() - tInicio;
        double tempoDecorridoInicio = ((double)tInicio / CLOCKS_PER_SEC);
        TempoTotal_Inicio += tempoDecorridoInicio;
        
        if(tempoDecorridoInicio > MaximoInicio){
            MaximoInicio = tempoDecorridoInicio;
        }
        if(tempoDecorridoInicio < MinimoInicio){
            MinimoInicio = tempoDecorridoInicio;
        }
        
        tAleatorio = clock();
        QuickSortAleatorio(vet[cont], 0, TamVet - 1);
        tAleatorio = clock() - tAleatorio;
        double tempoDecorridoAleatorio = ((double)tAleatorio / CLOCKS_PER_SEC);
        TempoTotal_Aleatorio += tempoDecorridoAleatorio;
        
        if(tempoDecorridoAleatorio > MaximoAleatorio){
            MaximoAleatorio = tempoDecorridoAleatorio;
        }
        if(tempoDecorridoAleatorio < MinimoAleatorio){
            MinimoAleatorio = tempoDecorridoAleatorio;
        }

        cont++;
    }

    printf("Para o pivo no inicio: \n");
    printf("O TempoTotal_Inicio: %lf s\n", TempoTotal_Inicio);
    printf("O TempoMaximo_Inicio: %lf s\n", MaximoInicio);
    printf("O TempoMinimo_Inicio: %lf s\n", MinimoInicio);
    printf("Média Inicio: %lf s\n", TempoTotal_Inicio/teto);
    
    printf("\n");
    
    printf("Para o pivo no Aleatorio: \n");
    printf("O TempoTotal_Aleatorio: %lf s\n", TempoTotal_Aleatorio);
    printf("O TempoMaximo_Aleatorio: %lf s\n", MaximoAleatorio);
    printf("O TempoMinimo_Aleatorio: %lf s\n", MinimoAleatorio);
    printf("Média Aleatorio: %lf s\n", TempoTotal_Aleatorio/teto);

    for (int i = 0; i < QtdVet; i++) {
        free(vet[i]);
    }
    free(vet);
    free(copia);

    return 0;
}
