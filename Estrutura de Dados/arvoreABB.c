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
    printf("[D] Recuperar valor mínimo:\n");
    printf("[E] Recuperar valor máximo: \n");
    printf("[F] Travessia pré ordem: \n");
    printf("[G] Travessia in ordem: \n");
    printf("[H] Travessia pós ordem: \n");
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

Tree *getMinValue(Tree *root)
{
    Tree *current = root;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

Tree *getMaxValue(Tree *root)
{
    Tree *current = root;

    while (current && current->right != NULL)
        current = current->right;

    return current;
}

Tree *removeNode(Tree *root, int value)
{
    if (isEmpty(root))
        return root;

    if (root->value > value)
        root->left = removeNode(root->left, value);
    else if (root->value < value)
        root->right = removeNode(root->right, value);
    else
    {
        if (root->left == NULL)
        {
            Tree *aux = root->right;
            free(root);
            return aux;
        }
        else if (root->right == NULL)
        {
            Tree *aux = root->left;
            free(root);
            return aux;
        }

        Tree *aux = getMinValue(root->right);
        root->value = aux->value;
        root->right = removeNode(root->right, aux->value);
    }

    return root;
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
    //cria arvore vazia
    root = NULL;

    do
    {
        printHeader();
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
            root = removeNode(root, value);
            break;
        case 'C':
            printHeader();
            printf("BUSCANDO NA ÁRVORE!\n");
            printf("Digite um valor para buscar: ");
            fflush(stdin);
            scanf("%i", &value);
            item = search(root, value);
            if (item != NULL)
            {
                int count = 0;
                if (item->left != NULL)
                    count++;
                if (item->right != NULL)
                    count++;
                strcpy(message, "O valor foi encontrado, ");
                if (count == 0)
                    strcat(message, "e ele é uma folha!\n");
                else
                {
                    strcat(message, "e ele tem %i filho%s!\n");
                }
                printf(message, count, count == 1 ? "" : "s");
            }
            else
                printf("Valor não encontrado!\n");
            enterToContinue();
            break;
        case 'D':
            printHeader();
            printf("RECUPERAR VALOR MÍNIMO!\n\n");
            if (isEmpty(root))
                printf("Árvore vazia!!\n");
            else
            {
                item = getMinValue(root);
                printf("O valor mínimo da árvore é: %i\n", item->value);
            }
            enterToContinue();
            break;
        case 'E':
            printHeader();
            printf("RECUPERAR VALOR MÁXIMO!\n\n");
            if (isEmpty(root))
                printf("Árvore vazia!!\n");
            else
            {
                item = getMaxValue(root);
                printf("O valor máximo da árvore é: %i\n", item->value);
            }
            enterToContinue();
            break;
        case 'F':
            printHeader();
            printf("TRAVESSIA PRÉ ORDEM!\n\n");
            pre_ordem(root);
            enterToContinue();
            break;
        case 'G':
            printHeader();
            printf("TRAVESSIA IN ORDEM!\n\n");
            in_ordem(root);
            enterToContinue();
            break;
        case 'H':
            printHeader();
            printf("TRAVESSIA PÓS ORDEM!\n\n");
            pos_ordem(root);
            enterToContinue();
            break;
        }

    } while (op != 27);
}