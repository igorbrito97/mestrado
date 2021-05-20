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

Tree *getMinValue(Tree *root);

void printHeader()
{
    system("@cls||clear");
    printf("*** ÁRVORE AVL *** \n");
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

int getHeight(Tree *root)
{
    int right, left;

    if (isEmpty(root))
        return 0;

    left = getHeight(root->left);
    right = getHeight(root->right);
    if (left > right)
        return left + 1;
    else
        return right + 1;
}

Tree *rightRotate(Tree *root)
{
    Tree *node = root->left;
    Tree *temp = node->right;

    node->right = root;
    root->left = temp;
    return node;
}

Tree *leftRotate(Tree *root)
{
    Tree *node = root->right;
    Tree *temp = node->left;

    node->left = root;
    root->right = temp;
    return node;
}

Tree *insertNode(Tree *root, int value)
{
    int balance;
    if (isEmpty(root))
        return newTreeNode(value);

    if (value > root->value)
        root->right = insertNode(root->right, value);
    else if (value < root->value)
        root->left = insertNode(root->left, value);
    else
        return root;

    balance = getHeight(root->left) - getHeight(root->right);
    if (balance > 1)
    {
        if (value < root->left->value)
            return rightRotate(root);
        else
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    else if (balance < -1)
    {
        if (value > root->right->value)
            return leftRotate(root);
        else
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

Tree *removeNode(Tree *root, int value)
{
    int balance, childBalance;
    if (isEmpty(root))
        return root;

    if (root->value > value)
        root->left = removeNode(root->left, value);
    else if (root->value < value)
        root->right = removeNode(root->right, value);
    else
    {
        if ((root->right == NULL) || (root->left == NULL)) // 0 ou 1 filho
        {
            Tree *temp = root->left != NULL ? root->left : root->right;

            if (temp == NULL) //0
            {
                temp = root;
                root = NULL;
            }
            else //1
                root = temp;

            free(temp);
        }
        else // 2 filhos
        {
            Tree *temp = getMinValue(root->right);
            root->value = temp->value;
            root->right = removeNode(root->right, temp->value);
        }
    }

    if (isEmpty(root))
        return root;

    balance = getHeight(root->left) - getHeight(root->right);
    if (balance > 1)
    {
        childBalance = getHeight(root->left->left) - getHeight(root->left->right);
        if (childBalance >= 0)
            return rightRotate(root);
        else
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    else if (balance < -1)
    {
        childBalance = getHeight(root->right->left) - getHeight(root->right->right);
        if (childBalance <= 0)
            return leftRotate(root);
        else
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
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
            root = insertNode(root, value);
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