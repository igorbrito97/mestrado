#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define TF 50

struct List {
    int value;
    int next;
};

void printHeader()
{
    system("@cls||clear");
    printf("*** LISTA ESTÁTICA ENCADEADA *** \n");
}

void enterToContinue()
{
    printf("\nEnter para continar....\n");
    fflush(stdin);
    getchar();
    getchar();
}

char mainMenu(int start)
{
	printf ("\n** MENU **\n");
    if(start == -1)
	    printf ("[A] Inicializar lista: \n");
    else
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
	printf ("[K] Exibir informações da estrutura: \n");
	printf ("[ESC] Voltar: \n");
	printf ("Digite a opção desejada: \n");
	
	return (toupper(getchar()));
}

int insertStart(struct List list[], int start, int available, int length)
{
    int value, insertPos;
    insertPos = available == -1 ? length : available;
    printf("INSERINDO NO INÍCIO!\n");
    if(length == TF) {
        printf("Impossível inserir. Tamanho máximo da lista atingido!!");
        enterToContinue();
        return -1;
    } else {
        printf("Digite um valor para inserir no ínicio da lista:  ");
        fflush(stdin);
        scanf("%i", &list[insertPos].value);
        list[insertPos].next = start;
        start = insertPos;
        return start;
    }
}

int insertMiddle(struct List list[], int start, int available, int length)
{
    int pos,value,count = 1,prev,current,insertPos;
    insertPos = available == -1 ? length : available;
    printf("INSERINDO NO MEIO: \n");
    if(length == TF) {
        printf("Impossível  inserir. Tamanho máximo da lista atingido!");
        enterToContinue();
        return -1;
    } else if(start == -1 || length < 2) {
        printf("Impossível inserir. Lista deve ser inicializada e conter mais que um elemento!!\n");
        enterToContinue();
        return -1;
    } else {
        while(1) {
            printf("Digite a posição para inserir: [1 - %i]  ",length-1);
            fflush(stdin);
            scanf("%i",&pos);
            if(pos > 0 && pos < length) {
                printf("Digite um valor para inserir na posição %i da lista: ",pos);
                fflush(stdin);
                scanf("%i", &list[insertPos].value);
                prev = start;
                current = list[prev].next;
                while(count < pos) {
                    prev = current;
                    current = list[current].next;
                    count++;
                }
                list[insertPos].next = list[prev].next;
                list[prev].next = insertPos;
                return 1;
            }
            else {
                printf("\nNúmero inválido. Tente novamente!\n");
            }
        }
    }
}

int insertEnd(struct List list[],int start, int available, int length)
{
    int pos,insertPos;
    insertPos = available == -1 ? length : available;
    printf("INSERINDO NO FIM!\n");
    if(length == TF) {
        printf("Impossível inserir. Tamanho máximo da lista atingido!!");
        enterToContinue();
        return -1;
    } else if(start == -1) {
        printf("Impossível inserir. Lista deve ser inicializada!!");
        enterToContinue();
        return -1;
    } else {
        printf("Digite um valor para inserir:  ");
        fflush(stdin);
        scanf("%i", &list[insertPos].value);
        list[insertPos].next = -1;
        pos = start;
        while(list[pos].next != -1) {
            pos = list[pos].next;
        }
        list[pos].next = insertPos;
        
        return 1;
    }
}

int removeStart(struct List list[], int start, int available, int length)
{
    int pos;
    printf("REMOVENDO DO ÍNICIO: \n");
    if(length == 0) {
        printf("Impossível remover. Lista vazia!");
        enterToContinue();
        return -1;
    } else {
        list[start].next = -1;
        if(available != -1) {
            pos = available;
            while(list[pos].next != -1) {
                pos = list[pos].next;
            }
            list[pos].next = start;
        }
        else 
            available = start;  
        return available;
    }
}

int removeMiddle(struct List list[],int start, int available,int length)
{
    int prev,current,pos,count = 1,posAvailable;
    printf("REMOVENDO DA POSIÇÃO K: \n");
    if(length == 0) {
        printf("Impossível remover. Lista vazia!");
        enterToContinue();
        return -1;
    } else if(start == -1 || length < 2) {
        printf("Impossível inserir. Lista deve ser inicializada e conter mais que um elemento!!");
        enterToContinue();
        return -1;
    } else {
        while(1) {
            printf("Digite a posição para remover: [1 - %i]  ",length-1);
            fflush(stdin);
            scanf("%i",&pos);
            if(pos > 0 && pos < length) {
                prev = start;
                current = list[start].next;
                while(count < pos) {
                    current = list[current].next;
                    count ++;
                }
                list[prev].next = list[current].next;
                list[current].next = -1;

                if(available != -1) {
                    posAvailable = available;
                    while(list[posAvailable].next != -1) {
                        posAvailable = list[posAvailable].next;
                    }
                    list[posAvailable].next = current;
                }
                else 
                    available = current;
                return available;
            }
            else {
                printf("\nNúmero inválido. Tente novamente!\n");
            }
        }
    }
}

int removeEnd(struct List list[],int start, int available,int length)
{
    int current, prev, pos;
    printf("REMOVENDO DO FIM: \n");
    if(length == 0) {
        printf("Impossível remover. Lista vazia!!");
        enterToContinue();
        return -1;
    } else {
        prev = start;
        current = list[start].next;
        while(list[current].next != -1) {
            current = list[current].next;
        }
        list[prev].next = -1;
        list[current].next = -1;

        if(available != -1) {
            pos = available;
            while(list[pos].next != -1) {
                pos = list[pos].next;
            }
            list[pos].next = current;
        }
        else 
            available = current;
        return available;
    }
}

void getPosValue(struct List list[],int start, int length)
{
    int pos,current,count = 0;
    printf("RECUPERANDO DA POSIÇÃO K: \n");
    if(length == 0) {
        printf("Impossível recuperar. Lista vazia!!");
        enterToContinue();
    } else {
        printf("Digite a posição: [0 - %i]",length-1);
        fflush(stdin);
        scanf("%i",&pos);
        if(pos >= 0 && pos < length){
            current = start;
            while(count < pos) {
                current = list[current].next;
                count++;
            }
            printf("O elemento da posição %i é: %i\n",pos,list[current]);
        }
        else {
            printf("Posição inválida!!\n");
        }
        enterToContinue();
    }
}

void searchByValue(struct List list[], int start, int length)
{
    int value,found = 0,pos,count = 0;
    printf("BUSCANDO POSIÇÃO POR VALOR: \n");
    if(length == 0) {
        printf("Impossível buscar. Lista vazia!!");
        enterToContinue();
    } else {
        printf("Digite o valor para ser buscado: ");
        fflush(stdin);
        scanf("%i",&value);
        pos = start;
        while(list[pos].next != -1) {
            if(list[pos].value == value) {
                found++;
                printf("Valor encontrado!! Posição: %i\n",count);

            }
            count++;
            pos = list[pos].next;
        }
        if(list[pos].value == value) {
            found++;
            printf("Valor encontrado!! Posição: %i\n",count);

        }
        if(found == 0) {
            printf("Não há itens na lista com esse valor!!\n");
        }
        enterToContinue();
    }
}

void printList(struct List list[],int start, int length)
{
    int pos,count = 0;
    printf("LISTA DE ELEMENTOS ([POS]: VALOR) \n");
    if(start > -1) {
        pos = start;
        while(list[pos].next != -1) {
            printf("[%i]: %i\n",count++,list[pos].value);
            pos = list[pos].next;
        }
        printf("[%i]: %i\n",count++,list[pos].value);
    }
    enterToContinue();
}

void printListInStruct(struct List list[], int start, int available, int length)
{
    int i,count = 0, pos;
    printf("INFORMAÇÕES DA ESTRUTURA \n\n");
    printf("Ínicio: %i \n", start);
    printf("Disponível: %i \n", available);
    printf("\nLista: ([POS FISICA]: VALOR -> PRÓXIMO) \n");
    if(available > -1) {
        pos = available;
        count++;
        while(list[pos].next != -1) {
            count++;
            pos = list[pos].next;
        }
    }
    for(i = 0; i < length + count; i++) {
        printf("[%i]: %i -> %i\n",i,list[i].value,list[i].next);
    }
    enterToContinue();
}


int main() {
    char op, message[40] = "";
    int start = -1, available = -1,length = 0, response, aux;
    struct List list[TF];
    
    do{
        printHeader();
        printf("\n%s\n",message);
        op = mainMenu(start);
        response = -1;
        switch (op)
        {
            case 'A': 
                printHeader();
                response = insertStart(list,start,available,length);
                if(response >= 0) {
                    start = response;
                    length++;
                    if(available != -1) {
                        available = list[available].next;
                    }
                    strcpy(message,"Inserido no ínicio com sucesso!!");
                }
                break;
            case 'B': 
                printHeader();
                response = insertMiddle(list,start,available,length);
                if(response > 0) {
                    length++;
                    if(available != -1) {
                        available = list[available].next;
                    }
                    strcpy(message,"Inserido no meio com sucesso!!");
                }
                break;
            case 'C': 
                printHeader();
                response = insertEnd(list,start,available,length);
                if(response > 0) {
                    length++;
                    if(available != -1) {
                        available = list[available].next;
                    }
                    strcpy(message,"Inserido no fim com sucesso!!");
                }
                break;
            case 'D': 
                printHeader();
                aux = list[start].next;
                response = removeStart(list,start,available,length);
                if(response >= 0) {
                    available = response;
                    start = aux;
                    length--;
                    strcpy(message,"Removido do ínicio com sucesso!!");
                }
                break;
            case 'E': 
                printHeader();
                response = removeMiddle(list,start,available,length);
                if(response >= 0) {
                    available = response;
                    length--;
                    strcpy(message,"Removido do meio com sucesso!!");
                }
                break;
            case 'F': 
                printHeader();
                response = removeEnd(list,start,available,length);
                if(response >= 0) {
                    available = response;
                    length--;
                    if(length == 0)
                        start = -1;
                    strcpy(message,"Removido do fim com sucesso!!");
                }
                break;
            case 'G': 
                printHeader();
                searchByValue(list,start,length);
                strcpy(message,"");
                break;
            case 'H': 
                printHeader();
                printf("A quantidade de elementos na lista é: %i\n",length);
                enterToContinue();
                strcpy(message,"");
                break;
             case 'I': 
                printHeader();
                getPosValue(list,start,length);
                strcpy(message,"");
                break;
             case 'J': 
                printHeader();
                printList(list,start,length);
                strcpy(message,"");
                break;
            case 'K': 
                printHeader();
                printListInStruct(list,start,available,length);
                strcpy(message,"");
                break;
        }

    } while(op!=27);
}