#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    double x, y, pi, pi2, distancia, totalPontos;
    int i,N;
    long pontosCirculo,reducedPontos;
    int myId, np;
    double tempoInicio, tempoFim;
    
    srand(time(NULL));
    N = atoi(argv[1]);
    totalPontos = pow(10, N);   
    pontosCirculo = 0;

    tempoInicio = MPI_Wtime();
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myId);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    for (i = 0; i < totalPontos; i++)
    {
        //número aletório entre -1 e 1
        x = (double)rand() / RAND_MAX * 2.0 - 1.0;
        y = (double)rand() / RAND_MAX * 2.0 - 1.0;

        distancia = (x * x)+ (y * y);
        if (distancia <= 1)
            pontosCirculo++;
    }
    MPI_Reduce(&pontosCirculo,&reducedPontos,1,MPI_LONG,MPI_SUM,0,MPI_COMM_WORLD);
    if(myId == 0) {
        pi = (double)((4.0 * pontosCirculo) / totalPontos);
        tempoFim = MPI_Wtime();
        printf("N = %i - PIIIIIIIII: %f\n", N, pi);
        printf("\nPontos dentro do círculo = %ld - Total de pontos: %ld\n", pontosCirculo, (long) totalPontos);
        printf("Tempo de execução em segundos: %f\n\n", tempoFim - tempoInicio);
        printf("Quantidade de processos: %i",np);
    }
    MPI_Finalize();
    return 0;
}
