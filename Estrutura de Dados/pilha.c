#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

struct item {
    int value;
    struct item *next;
    
};
typedef struct item StackItem;

struct stack {
    StackItem *start;
};
typedef struct stack Stack;

void printHeader()
{
    system("@cls||clear");
    printf("*** PILHA DINÂMICA *** \n");
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
    printf ("[A] Empilhar: [push] \n");
	printf ("[B] Desempilhar: [pop] \n");
	printf ("[C] Consultar último: \n");
	printf ("[D] Esvaziar: \n");
	printf ("[E] Verificar se está vazia: \n");
	printf ("[ESC] Sair... \n");
	printf ("Digite a opção desejada: \n");
	
	return (toupper(getchar()));
}

Stack* initializeStack() {
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    stack->start = NULL;
    return stack;
}

StackItem* newStackItem(int value) {
    StackItem *item = (StackItem*) malloc(sizeof(StackItem)); 
    item->value=value;
    item->next = NULL;
    return item;
}

int isEmpty(Stack *stack) {
    return stack->start == NULL;
}

void push(Stack *stack, int value) {
    StackItem *item = newStackItem(value);
    item->next = stack->start;
    stack->start = item;
}

int pop(Stack *stack, char message[40]) {
    StackItem *pointer;
    int value;
    if(isEmpty(stack) == 1) {
        printf("Impossível remover, pilha vazia!\n");
        strcpy(message,"Erro ao remover");
        enterToContinue();
        return 0;
    } else {
        pointer = stack->start;
        value = pointer->value;
        stack->start = pointer->next;
        free(pointer);
        strcpy(message,"Removido da pilha com sucesso!");
        return value;
    }
}

Stack* freeAll(Stack *stack) {
    StackItem *pointer = stack->start;
    while(pointer->next != NULL) {
        StackItem *item = pointer;
        pointer = pointer->next;
        free(item);
    }
    free(pointer);
    stack->start = NULL;
    return stack;
}

int main() {
    int value,response;
    char op, message[40] = "", aux[40] = "";
    Stack *stack = initializeStack();
    
    do{
        printHeader();
        printf("\n%s\n",message);
        op = mainMenu();
        switch (op)
        {
            case 'A': 
                printHeader();    
                printf("EMPILHANDO!\n");
                printf("Digite um valor para inserir na pilha: ");
                fflush(stdin);
                scanf("%i", &value);
                push(stack,value);
                strcpy(message,"Inserido na pilha com sucesso!");
                break;
            case 'B': 
                printHeader();
                response = pop(stack,message);
                break;
            case 'C': 
                printHeader();
                if(isEmpty(stack) == 1) {
                    printf("Impossível verificar, pilha vazia!\n");
                } else {
                    value = pop(stack,aux);
                    printf("O último valor da pilha é: %i",value);
                    push(stack,value);
                }
                enterToContinue();
                strcpy(message,"");
                break;
            case 'D': 
                printHeader();
                stack = freeAll(stack);
                strcpy(message,"Pilha esvaziada com sucesso!");
                break;
            case 'E': 
                printHeader();
                if(isEmpty(stack) == 1)
                    strcpy(message," ");
                else 
                    strcpy(message," não ");

                printf("A pilha%sestá vazia!!\n", message);
                enterToContinue();
                strcpy(message,"");
                break;
        }

    } while(op!=27);
}