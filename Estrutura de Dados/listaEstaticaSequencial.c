#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define TF 25

void printHeader()
{
    system("@cls||clear");
    printf("*** LISTA ESTÁTICA SEQUENCIAL *** \n");
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
	printf ("[A] Inserir no fim: \n");
	printf ("[B] Inserir na posicao k: \n");
	printf ("[C] Excluir o último: \n");
	printf ("[D] Excluir na posição k: \n");
	printf ("[E] Recuperar valor da posição k:  \n");
	printf ("[F] Recuperar quantidade de elementos:  \n");
	printf ("[G] Localizar posição de elemento por valor: \n");
	printf ("[H] Exibir todos os elementos: \n");
	printf ("[ESC] Voltar: \n");
	printf ("Digite a opção desejada: \n");
	
	return (toupper(getchar()));
}

int insertEnd(int list[],int length)
{
    int value;
    printf("INSERINDO NO FIM!\n");
    if(length == TF) {
        printf("Impossível inserir. Tamanho máximo da lista atingido!!");
        enterToContinue();
        return -1;
    } else {
        printf("Digite um valor para inserir:  ");
        scanf("%i", &value);
        list[length++] = value;
        return length;
    }
}

int insertPos(int list[],int length)
{
    int pos,value,aux;
    printf("INSERINDO NA POSIÇÃO K: \n");
    if(length == TF) {
        printf("Impossível remover. Lista vazia!");
        enterToContinue();
        return -1;
    } else {
        while(1) {
            printf("Digite a posição para inserir: [0 - %i]  ",length);
            fflush(stdin);
            scanf("%i",&pos);
            if(pos >= 0 && pos <= length) {
                printf("\nDigite um valor para inserir:  ");
                fflush(stdin);
                scanf("%i",&value);
                aux = length;
                while(aux > pos) {
                    list[aux] = list[aux-1];
                    aux--;
                }
                list[pos] = value;
                return ++length;
            }
            else {
                printf("\nNúmero inválido. Tente novamente!\n");
            }
        }
    }
}

int removeEnd(int list[],int length)
{
    printf("REMOVENDO DO FIM: \n");
    if(length == 0) {
        printf("Impossível remover. Lista vazia!!");
        enterToContinue();
        return -1;
    } else {
        return --length;
    }
}

int removePos(int list[],int length)
{
    int pos;
    printf("REMOVENDO DA POSIÇÃO K: \n");
    if(length == 0) {
        printf("Impossível remover. Lista vazia!");
        enterToContinue();
        return -1;
    } else {
        while(1) {
            printf("Digite a posição para remover: [0 - %i]  ",length-1);
            fflush(stdin);
            scanf("%i",&pos);
            if(pos >= 0 && pos < length) {
                while(pos < length -1) {
                    list[pos] = list[pos + 1];
                    pos++;
                }
                return --length;
            }
            else {
                printf("\nNúmero inválido. Tente novamente!\n");
            }
        }
    }
}

void getPosValue(int list[],int length)
{
    int pos;
    printf("RECUPERANDO DA POSIÇÃO K: \n");
    if(length == 0) {
        printf("Impossível recuperar. Lista vazia!!");
        enterToContinue();
    } else {
        printf("Digite a posição: [0 - %i]",length-1);
        fflush(stdin);
        scanf("%i",&pos);
        if(pos >= 0 && pos < length){
            printf("O elemento da posição %i é: %i\n",pos,list[pos]);
        }
        else {
            printf("Posição inválida!!\n");
        }
        enterToContinue();
    }
}

void searchByValue(int list[],int length)
{
    int value,found = 0;
    printf("BUSCANDO POSIÇÃO POR VALOR: \n");
    if(length == 0) {
        printf("Impossível buscar. Lista vazia!!");
        enterToContinue();
    } else {
        printf("Digite o valor para ser buscado: ");
        fflush(stdin);
        scanf("%i",&value);
        int pos = 0;
        while(pos < length) {
            if(list[pos] == value){
                found ++;
                printf("Valor encontrado!! Posição: %i\n",pos);
            }
            pos++;
        }
        if(found == 0) {
            printf("Não há itens na lista com esse valor!!\n");
        }
        enterToContinue();
    }
    //pode ter mais de 1 -> só colocar pra printar -> aparece em: (- %i )
}

void printList(int list[],int length)
{
    printf("LISTA DE ELEMENTOS ([POS]: VALOR) \n");
    for(int i = 0; i < length; i++) {
        printf("[%i]: %i\n",i,list[i]);
    }
    enterToContinue();
}


int main() {
    char op, message[40] = "";
    int length = 0, list[TF], response;

    do{
        printHeader();
        printf("\n%s\n",message);
        op = mainMenu();
        response = -1;
        switch (op)
        {
            case 'A': 
                printHeader();
                response = insertEnd(list,length);
                if(response > 0) {
                    length = response;
                    strcpy(message,"Inserido com sucesso!!");
                }
                break;
            case 'B': 
                printHeader();
                response = insertPos(list,length);
                if(response > 0) {
                    length = response;
                    strcpy(message,"Inserido com sucesso!!");
                }
                break;
            case 'C': 
                printHeader();
                response = removeEnd(list,length);
                if(response >= 0) {
                    length = response;
                    strcpy(message,"Removido com sucesso!!");
                }
                break;
            case 'D': 
                printHeader();
                response = removePos(list,length);
                if(response >= 0) {
                    length = response;
                    strcpy(message,"Removido com sucesso!!");
                }
                break;
            case 'E': 
                printHeader();
                getPosValue(list,length);
                strcpy(message,"");
                break;
            case 'F': 
                printHeader();
                printf("A quantidade de elementos na lista é: %i\n",length);
                enterToContinue();
                strcpy(message,"");
                break;
            case 'G': 
                printHeader();
                searchByValue(list,length);
                strcpy(message,"");
                break;
            case 'H': 
                printHeader();
                printList(list,length);
                strcpy(message,"");
                break;
            // default: 
            //     system("@cls||clear");
            //     printf("Comanda inválido. Tente novamente!");
            //     break;
        }

    } while(op!=27);
}