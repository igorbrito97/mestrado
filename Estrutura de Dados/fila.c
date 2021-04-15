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
    printf("*** LISTA DUPLAMENTE ENCADEADA *** \n");
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
    printf ("[A] Colocar: [enQueue] \n");
	printf ("[B] Retirar: [deQueue] \n");
	printf ("[C] Consultar último: \n");
	printf ("[C] (Verificar expressão regular): \n");
	printf ("[ESC] Voltar: \n");
	printf ("Digite a opção desejada: \n");
	
	return (toupper(getchar()));
}

QueueItem* newQueueItem(int value) {
    QueueItem *info = (QueueItem*) malloc(sizeof(QueueItem)); 
    info->value=value;
    info->next = NULL;
    info->prev = NULL;
    return info;
}

Queue* enQueue(Queue *list)
{
    int value;

    printf("INSERINDO NO INÍCIO!\n");
    printf("Digite um valor para inserir no ínicio da Fila:  ");
    fflush(stdin);
    scanf("%i", &value);
    if(list->start == NULL) {
        QueueItem *item = newQueueItem(value);
        list->start = list->end = item;
    }
    else {
        QueueItem *item = newQueueItem(value);
        list->start->prev = item;
        item->next = list->start;
        list->start = item;
    }
    return list;
}

Queue* deQueue(Queue *list)
{
    int value;

    printf("INSERINDO NO INÍCIO!\n");
    printf("Digite um valor para inserir no ínicio da Fila:  ");
    fflush(stdin);
    scanf("%i", &value);
    if(list->start == NULL) {
        QueueItem *item = newQueueItem(value);
        list->start = list->end = item;
    }
    else {
        QueueItem *item = newQueueItem(value);
        list->start->prev = item;
        item->next = list->start;
        list->start = item;
    }
    return list;
}



int main() {
    char op;
    Queue *queue = (Queue*) malloc(sizeof(Queue));
    queue->start = queue->end = NULL;
    
    do{
        printHeader();
        op = mainMenu();
        switch (op)
        {
            case 'A': 
                printHeader();
                queue = insertStart(queue);
                break;
            case 'B': 
                printHeader();
                queue = insertStart(queue);
                break;
            case 'C': 
                printHeader();
                queue = insertStart(queue);
                break;
        }

    } while(op!=27);
}