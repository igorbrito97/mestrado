#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

struct item {
    int value;
    struct item *next;
    struct item *prev;
};
typedef struct item QueueItem;

struct queue {
    QueueItem *start, *end;
};
typedef struct queue Queue;

void printHeader()
{
    system("@cls||clear");
    printf("*** FILA DINÂMICA *** \n");
}

void enterToContinue()
{
    printf("\nEnter para continar....\n");
    fflush(stdin);
    getchar();
    getchar();
}

char mainMenu()
{
	printf ("\n** MENU **\n");
    printf ("[A] Inserir: [enQueue] \n");
	printf ("[B] Retirar: [deQueue] \n");
	printf ("[C] Esvaziar: \n");
	printf ("[D] Verificar se está vazia: \n");
	printf ("[ESC] Sair: \n");
	printf ("Digite a opção desejada: \n");
	
	return (toupper(getchar()));
}

Queue* initializeQueue() 
{
    Queue *queue = (Queue*) malloc(sizeof(Queue));
    queue->start = queue->end = NULL;
    return queue;
}

QueueItem* newQueueItem(int value) {
    QueueItem *info = (QueueItem*) malloc(sizeof(QueueItem)); 
    info->value=value;
    info->next = NULL;
    info->prev = NULL;
    return info;
}

int isEmpty(Queue *queue) {
    return queue->start == NULL;
}

void enQueue(Queue *queue,int value){
    QueueItem *item = newQueueItem(value);
    if(isEmpty(queue) == 1) 
        queue->start = item;    
    else 
        queue->end->next = item;    
    queue->end = item;
}

int deQueue(Queue *queue, char message[40])
{
    QueueItem *pointer;
    int value;

    printf("RETIRANDO DA FILA!\n");
    if(isEmpty(queue) == 1) {
        printf("Impossível retirar, fila vazia!\n");
        strcpy(message,"Erro ao retirar\n");
        enterToContinue();
        return 0;
    } else {
        pointer = queue->start;
        value = pointer->value;
        queue->start = pointer->next;
        if(queue->start == NULL)    
            queue->end = NULL;
        free(pointer);
        strcpy(message,"Retirado da fila com sucesso!\n");
        return value;
    }
}

Queue* freeAll(Queue *queue) {
    QueueItem *pointer;
    if(isEmpty(queue) != 1) {
        pointer = queue->start;
        while(pointer->next != NULL) {
            QueueItem *item = pointer;
            pointer = pointer->next;
            free(item);
        }
        free(pointer);
        queue->start = queue->end = NULL;
    }
    return queue;
}

int main() {
    int value;
    char op, message[40] = "";
    Queue *queue = initializeQueue();
    
    do{
        printHeader();
        printf("\n%s",message);
        op = mainMenu();
        switch (op)
        {
            case 'A': 
                printHeader();
                printf("INSERINDO NA FILA!\n");
                printf("Digite um valor para inserir no ínicio da Fila:  ");
                fflush(stdin);
                scanf("%i", &value);
                enQueue(queue,value);
                strcpy(message,"Inserido na fila com sucesso!\n");
                break;
            case 'B': 
                printHeader();
                value = deQueue(queue,message);
                break;
            case 'C':
                printHeader();
                queue = freeAll(queue);
                strcpy(message,"Fila esvaziada com sucesso!\n");
                break;
            case 'D':
                printHeader();
                if(isEmpty(queue) == 1)
                    strcpy(message," ");
                else 
                    strcpy(message," não ");

                printf("A fila%sestá vazia!!\n", message);
                enterToContinue();
                strcpy(message,"");
                break;
        }

    } while(op!=27);
}