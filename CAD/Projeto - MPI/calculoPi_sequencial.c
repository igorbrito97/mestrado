#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
    double x, y, pi, distancia, tempoExecucao,totalPontos;
    int i;
    long pontosCirculo;
    clock_t tempoInicio, tempoFim;
    srand(time(NULL));    
    for (int N = 3; N <= 10; N++) //3-10
    {
        tempoInicio = clock();
        totalPontos = pow(10, N);
        pontosCirculo = 0;
        for (i = 0; i < totalPontos; i++)
        {
            //número aletório entre -1 e 1
            x = (double)rand() / RAND_MAX * 2.0 - 1.0;
            y = (double)rand() / RAND_MAX * 2.0 - 1.0;

            distancia = (x * x) + (y * y);
            if (distancia <= 1)
                pontosCirculo++;
        }
        pi = (double)((4.0 * pontosCirculo) / totalPontos);
        tempoFim = clock();
        tempoExecucao = ((double) tempoFim - tempoInicio) / CLOCKS_PER_SEC;
        printf("N = %i - PIIIIIIIII: %f\n", N, pi);
        printf("\nPontos dentro do círculo = %ld - Total de pontos: %ld\n", pontosCirculo, (long) totalPontos);
        printf("Tempo de execução em segundos: %f\n\n", tempoExecucao);
    }
    return 0;
}