#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct tree
{
    int value;
    struct tree *right, *left;
};
typedef struct tree Tree;

void printHeader()
{
    system("@cls||clear");
    printf("*** ÁRVORE BINÁRIA DE BUSCA (ABB) *** \n");
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
    printf("\n** MENU **\n");
    printf("[A] Inserir:\n");
    printf("[B] Remover:\n");
    printf("[C] Buscar: \n");
    printf("[D] Travessia pré ordem: \n");
    printf("[E] Travessia in ordem: \n");
    printf("[F] Travessia pós ordem: \n");
    printf("([G] Profundidade da árvore:) \n");
    printf("[ESC] Sair: \n");
    printf("Digite a opção desejada: \n");

    return (toupper(getchar()));
}

Tree *newTreeNode(int value)
{
    Tree *node = (Tree *)malloc(sizeof(Tree));
    node->right = node->left = NULL;
    node->value = value;
    return node;
}

char isEmpty(Tree *root)
{
    return root == NULL;
}

void pre_ordem(Tree *root)
{
    if (!isEmpty(root))
    {
        printf("%d -", root->value);
        pre_ordem(root->left);
        pre_ordem(root->right);
    }
}

void in_ordem(Tree *root)
{
    if (!isEmpty(root))
    {
        in_ordem(root->left);
        printf("%d -", root->value);
        in_ordem(root->right);
    }
}

void pos_ordem(Tree *root)
{
    if (!isEmpty(root))
    {
        pos_ordem(root->left);
        pos_ordem(root->right);
        printf("%d -", root->value);
    }
}

void insertNode(Tree **root, int value)
{
    if (isEmpty(*root))
        (*root) = newTreeNode(value);
    else
    {
        if (value > (*root)->value)
            insertNode(&(*root)->right, value);
        else
            insertNode(&(*root)->left, value);
    }
}

void removeNode(Tree *root)
{
}

Tree *search(Tree *root, int searchValue)
{
    if (isEmpty(root) || root->value == searchValue)
        return root;
    else if (root->value > searchValue)
        search(root->left, searchValue);
    else
        search(root->right, searchValue);
}

int main()
{
    int value;
    char op, message[40] = "";
    Tree *item, *root = (Tree *)malloc(sizeof(Tree));
    root = NULL;

    do
    {
        printHeader();
        printf("\n%s", message);
        op = mainMenu();
        switch (op)
        {
        case 'A':
            printHeader();
            printf("INSERINDO NA ÁRVORE!\n");
            printf("Digite um valor para inserir: ");
            fflush(stdin);
            scanf("%i", &value);
            insertNode(&root, value);
            break;
        case 'B':
            printHeader();
            printf("REMOVENDO DA ÁRVORE!\n");
            printf("Digite um valor para remover: ");
            fflush(stdin);
            scanf("%i", &value);
            break;
        case 'C':
            printHeader();
            printf("BUSCANDO NA ÁRVORE!\n");
            printf("Digite um valor para buscar: ");
            fflush(stdin);
            scanf("%i", &value);
            //vamos ver -> da pra tirar esse item aqui
            item = search(root, value);
            if (item != NULL)
            {
                strcpy(message, "O valor foi encontrado, ");
                if (item->left == NULL && item->right == NULL)
                    strcat(message, "e ele é uma folha!\n");
                else
                {
                    strcat(message, "e é pai de: \n");
                }
                printf(message);
            }
            else
                printf("Valor não encontrado!");
            enterToContinue();
            break;
        case 'D':
            printHeader();
            printf("TRAVESSIA PRÉ ORDEM!\n\n");
            pre_ordem(root);
            enterToContinue();
            break;
        case 'E':
            printHeader();
            printf("TRAVESSIA IN ORDEM!\n\n");
            in_ordem(root);
            enterToContinue();
            break;
        case 'F':
            printHeader();
            printf("TRAVESSIA PÓS ORDEM!\n\n");
            pos_ordem(root);
            enterToContinue();
            break;
        }

    } while (op != 27);
}