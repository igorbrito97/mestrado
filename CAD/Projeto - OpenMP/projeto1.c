#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

int main()
{
    double x, y, pi, distancia, tempoExecucao,totalPontos;
    int i;
    long int pontosCirculo;
    double tempoInicio, tempoFim;
    srand(time(NULL));
    for (int N = 3; N <= 10; N++) //3-10
    {
        totalPontos = pow(10, N);
        pontosCirculo = 0;
        tempoInicio = omp_get_wtime();
        for (i = 0; i < totalPontos; i++)
        {
            //número aletório entre -1 e 1
            x = (double)rand() / RAND_MAX * 2.0 - 1.0;
            y = (double)rand() / RAND_MAX * 2.0 - 1.0;

            distancia = pow(x, 2) + pow(y, 2);
            if (distancia <= 1)
                pontosCirculo++;
        }
        pi = (double)(4 * pontosCirculo) / totalPontos;
        printf("N = %i - PIIIIIIIII: %f\n", N, pi);
        tempoFim = omp_get_wtime();
        printf("\nPontos dentro do círculo = %i - Total de pontos: %.1f\n", pontosCirculo, totalPontos);
        printf("Tempo de execução em segundos: %f\n\n", tempoFim - tempoInicio);
    }
    return 0;
}