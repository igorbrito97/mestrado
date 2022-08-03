#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    double x, y, pi, distancia, tempoExecucao;
    int N;
    long long int pontosCirculo, totalPontos;
    double tempoInicio, tempoFim;

    srand(time(NULL));
    pontosCirculo = 0;
    N = atoi(argv[1]);
    totalPontos = pow(10, N);
    tempoInicio = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp for private(x, y, distancia) reduction(+:pontosCirculo) schedule(dynamic)
        for (int i = 0; i < totalPontos; i++)
        {
            //número aletório entre -1 e 1
            x = (double)rand() / RAND_MAX * 2.0 - 1.0;
            y = (double)rand() / RAND_MAX * 2.0 - 1.0;

            distancia = pow(x, 2) + pow(y, 2);
            if (distancia <= 1)
                pontosCirculo++;
        }
    }

    pi = (double)(4 * pontosCirculo) / totalPontos;
    printf("N = %i - PIIIIIIIII: %f\n", N, pi);
    tempoFim = omp_get_wtime();
    printf("\nPontos dentro do círculo = %i - Total de pontos: %i\n", pontosCirculo, totalPontos);
    tempoExecucao = (tempoFim - tempoInicio); // em segundos
    printf("Tempo de execução em segundos: %f\n\n", tempoExecucao);
    
    return 0;
}