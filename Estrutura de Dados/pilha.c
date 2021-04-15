#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

struct stack {
    int value;
    struct stack *next;
    
};
typedef struct stack Stack;

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
    printf ("[A] Empilhar: [push] \n");
	printf ("[B] Desempilhar: [pop] \n");
	printf ("[C] Consultar último: \n");
	printf ("[C] (Verificar expressão regular): \n");
	printf ("[ESC] Voltar: \n");
	printf ("Digite a opção desejada: \n");
	
	return (toupper(getchar()));
}

Stack* newListItem(int value) {
    Stack *item = (Stack*) malloc(sizeof(Stack)); 
    item->value=value;
    item->next = NULL;
    return item;
}

int isEmpty(Stack *stack)
{
    return stack == NULL;
}

Stack* push(Stack *stack)
{
    
    return stack;
}

Stack* pop(Stack *stack)
{
    
    return stack;
}



int main() {
    char op;
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    
    do{
        printHeader();
        op = mainMenu();
        switch (op)
        {
            case 'A': 
                printHeader();
                stack = insertStart(stack);
                break;
            case 'B': 
                printHeader();
                stack = insertMiddle(stack);
                break;
            case 'C': 
                printHeader();
                stack = insertEnd(stack);
                break;
        }

    } while(op!=27);
}