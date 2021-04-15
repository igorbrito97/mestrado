#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

struct item {
    int value;
    struct item *next;
    struct item *prev;
};
typedef struct item ListItem;

struct list {
    ListItem *start, *end;
};
typedef struct list List;

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
    printf ("[A] Inserir no início: \n");
	printf ("[B] Inserir no meio: \n");
	printf ("[C] Inserir no fim: \n");
	printf ("[D] Excluir o primeiro: \n");
	printf ("[E] Excluir do meio: \n");
	printf ("[F] Excluir o último: \n");
	printf ("[G] Recuperar valor da posição k:  \n");
	printf ("[H] Recuperar quantidade de elementos:  \n");
	printf ("[I] Localizar posição de elemento por valor: \n");
	printf ("[J] Exibir todos os elementos: \n");
	printf ("[ESC] Voltar: \n");
	printf ("Digite a opção desejada: \n");
	
	return (toupper(getchar()));
}

ListItem* newListItem(int value) {
    ListItem *info = (ListItem*) malloc(sizeof(ListItem)); 
    info->value=value;
    info->next = NULL;
    info->prev = NULL;
    return info;
}

List* insertStart(List *list)
{
    int value;

    printf("INSERINDO NO INÍCIO!\n");
    printf("Digite um valor para inserir no ínicio da lista:  ");
    fflush(stdin);
    scanf("%i", &value);
    if(list->start == NULL) {
        ListItem *item = newListItem(value);
        list->start = list->end = item;
    }
    else {
        ListItem *item = newListItem(value);
        list->start->prev = item;
        item->next = list->start;
        list->start = item;
    }
    return list;
}

List* insertMiddle(List *list)
{
    int pos,value, count;
    ListItem *pointer;
    printf("INSERINDO NO MEIO: \n");
    if(list->start != NULL && list->start == list->end) {
        printf("Impossível inserir. Lista deve conter mais que um elemento!!\n");
        enterToContinue();
        return list;
    } else {
        while(1) {
            printf("Digite a posição para inserir: ");
            fflush(stdin);
            scanf("%i",&pos);
            if(pos > 0) {
                printf("Digite um valor para inserir na posição %i da lista: ",pos);
                fflush(stdin);
                scanf("%i", &value);

                count = 0;
                pointer = list->start;
                while(pointer != list->end && count < pos) {
                    count++;
                    pointer = pointer->next;
                }
                if(count == pos) {
                    ListItem *item = newListItem(value);
                    item->next = pointer;
                    item->prev = pointer->prev;
                    pointer->prev->next = item;
                    pointer->prev = item;

                    return list;
                }
                else {
                    printf("\nImpossível inserir, posição inválida. Tente novamente!\n");
                }
            }
            else {
                printf("\nNúmero inválido. Tente novamente!\n");
            }
        }
    }
}

List* insertEnd(List *list)
{
    int value;
    printf("INSERINDO NO FIM!\n");
    printf("Digite um valor para inserir:  ");
    fflush(stdin);
    scanf("%i", &value);
    if(list->start == NULL) {
        ListItem *item = newListItem(value);
        list->start = list->end = item;
    }
    else {
        ListItem *item = newListItem(value);
        list->end->next = item;
        item->prev = list->end;
        list->end = item;
    }
    
    return list;
}

List* removeStart(List *list)
{
    ListItem *pointer;
    printf("REMOVENDO DO ÍNICIO: \n");
    if(list->start == NULL) {
        printf("Impossível remover. Lista vazia!");
        enterToContinue();
    } else { 
        pointer = list->start;
        if(list->end == list->start) {
            list->start = list->end = NULL;
        } else {
            list->start->next->prev = NULL;
            list->start = list->start->next;
        }
        free(pointer);
    }

    return list;
}

List* removeMiddle(List *list)
{
    int pos,count,value;
    ListItem *pointer;
    printf("REMOVENDO DA POSIÇÃO K: \n");
    if(list->start == NULL) {
        printf("Impossível remover. Lista vazia!");
        enterToContinue();
        return list;
    } else {
        while(1) {
            printf("Digite a posição para remover: ");
            fflush(stdin);
            scanf("%i",&pos);
            if(pos > 0) {
                printf("Digite um valor para inserir na posição %i da lista: ",pos);
                fflush(stdin);
                scanf("%i", &value);

                count = 0;
                pointer = list->start;
                while(pointer != list->end && count < pos) {
                    count++;
                    pointer = pointer->next;
                }
                if(count == pos) {
                    pointer->prev->next = pointer->next;
                    pointer->next->prev = pointer->prev;
                    free(pointer);
                    return list;
                }
                else {
                    printf("\nImpossível inserir, posição inválida. Tente novamente!\n");
                }
            }
            else {
                printf("\nNúmero inválido. Tente novamente!\n");
            }
        }
    }
}

List* removeEnd(List *list)
{
    ListItem *pointer;
    printf("REMOVENDO DO FIM: \n");
    if(list->start == NULL) {
        printf("Impossível remover. Lista vazia!!");
        enterToContinue();
    } else {
        pointer = list->end;
        if(list->start == list->end) {
            list->start = list->end = NULL;
        } else {
            list->end->prev->next = NULL;
            list->end = list->end->prev;
        }
        free(pointer);
    }

    return list;
}

void getPosValue(List *list)
{
    int pos,count = 0;
    ListItem *pointer;
    printf("RECUPERANDO DA POSIÇÃO K: \n");
    if(list->start== NULL) {
        printf("Impossível recuperar. Lista vazia!!");
        enterToContinue();
    } else {
        printf("Digite a posição: ");
        fflush(stdin);
        scanf("%i",&pos);
        if(pos >= 0){
            while(pointer != list->end && count < pos) {
                pointer = pointer->next;
                count++;
            }
            if(pos == count)
                printf("O elemento da posição %i é: %i\n",pos,pointer->value);
            else if(pos == count + 1)//último 
                printf("O elemento da posição %i é: %i\n",pos,list->end->value);
            else 
                printf("Posição inválida!!\n");
        }
        else {
            printf("Posição inválida!!\n");
        }
        enterToContinue();
    }
}

void getQuantity(List *list)
{
    int count = 0;
    ListItem *pointer;
    if(list->start != NULL) {
        pointer = list->start;
        while(pointer != list->end) {
            count++;
            pointer = pointer->next;
        }
        count++;
    }
    printf("A quantidade de elementos na lista é: %i\n", count);
    enterToContinue();
}

void searchByValue(List *list)
{
    int value,count = 0,found = 0;
    ListItem *pointer;
    printf("BUSCANDO POSIÇÃO POR VALOR: \n");
    if(list->start == NULL) {
        printf("Impossível buscar. Lista vazia!!");
        enterToContinue();

    } else {
        printf("Digite o valor para ser buscado: ");
        fflush(stdin);
        scanf("%i",&value);
        pointer = list->start;
        while(pointer != list->end) {
            if(pointer->value == value){
                printf("Valor encontrado na posição: %i!\n",count);
                found++;
            }
            pointer = pointer->next;
            count++;
        }
        if(pointer->value == value) {
            printf("Valor encontrado na posição: %i!\n",count+1);
            found++;
        }

        if(found == 0) {
            printf("Nenhum item com esse valor encontrado!!!!\n");
        }
        enterToContinue();
    }

}

void printList(List *list)
{
    int count = 0;
    ListItem *pointer;
    printf("LISTA DE ELEMENTOS ([POS]: VALOR) \n");

    if(list->start != NULL) {
        pointer = list->start;
        while(pointer != list->end) {
            printf("[%i]: %i\n",count,pointer->value);
            pointer = pointer->next;
            count++;
        }
        printf("[%i]: %i\n",count,list->end->value);
    }   
    enterToContinue();
}

int main() {
    char op;
    List *list = (List*) malloc(sizeof(List));
    list->start = list->end = NULL;
    
    do{
        printHeader();
        op = mainMenu();
        switch (op)
        {
            case 'A': 
                printHeader();
                list = insertStart(list);
                break;
            case 'B': 
                printHeader();
                list = insertMiddle(list);
                break;
            case 'C': 
                printHeader();
                list = insertEnd(list);
                break;
            case 'D': 
                printHeader();
                list = removeStart(list);
                break;
            case 'E': 
                printHeader();
                list = removeMiddle(list);
                break;
            case 'F': 
                printHeader();
                list = removeEnd(list);
                break;
            case 'G': 
                printHeader();
                searchByValue(list);
                break;
            case 'H': 
                printHeader();
                getQuantity(list);
                enterToContinue();
                break;
             case 'I': 
                printHeader();
                getPosValue(list);
                break;
             case 'J': 
                printHeader();
                printList(list);
                break;
        }

    } while(op!=27);
}