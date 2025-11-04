#include <stdio.h>
#include <string.h>
#include <locale.h> // Pra forçar UTF-8

#define MAX_PRODUTOS 100

struct produto
{
    char nome[50];
    int codigo;
    float preco;
    int quantidade;
};

typedef struct produto Produto;

// Função criar_produto
Produto cria_produto(char nome[50], int codigo, float preco, int quantidade) {
    Produto produto;

    strcpy(produto.nome, nome); 
    produto.codigo = codigo;
    produto.preco = preco;
    produto.quantidade = quantidade;
    return produto;
}

// Função input_criar_produto
void menu_criar_produto(Produto produtos[], int *contador){
    char nome[50];
    int codigo;
    float preco;
    int quantidade;

    printf("Digite o nome do produto: \n");
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome) - 1] = '\0';         

    printf("Digite o codigo do produto: \n");
    scanf("%d", &codigo);

    printf("Digite o preço do produto: \n");
    scanf("%f", &preco);

    printf("Digite a quantidade do produto: \n");
    scanf("%d", &quantidade);

    if (*contador < MAX_PRODUTOS) {
        produtos[*contador] = cria_produto(nome, codigo, preco, quantidade);
        *contador += 1;
        printf("\nProduto criado com sucesso!\n");
    } else {
        printf("ERRO: Limite máximo de produtos atingido!\n");
    }
}


void imprimir_produtos(Produto produtos[], int *contador){
    printf("\n=== Lista de Produtos ===\n");
    
    if (*contador == 0) {
        printf("ERRO: Nenhum produto cadastrado ainda.\n");
        return;
    }
    
    for (int i = 0; i < *contador; i++) {
        printf("%d - %s | R$%.2f | Qtd: %d\n",
               produtos[i].codigo,
               produtos[i].nome,
               produtos[i].preco,
               produtos[i].quantidade);
    }
}

void buscar_por_codigo(Produto produtos[], int *contador){
    int codigo_produto;
    int encontrado = 0; 

    printf("Qual codigo do produto? ");
    scanf("%d", &codigo_produto);
    getchar();

    for (int i = 0; i < *contador; i++) {
        if(codigo_produto == produtos[i].codigo){
            printf("\n=== Produto Encontrado ===\n");
            printf("%d - %s | R$%.2f | Qtd: %d\n",
               produtos[i].codigo,
               produtos[i].nome,
               produtos[i].preco,
               produtos[i].quantidade);
            encontrado = 1;
            break; 
        }
    }
    
    if (!encontrado) { // Avisa se não encontrou
        printf("ERRO: Produto com código %d não encontrado!\n", codigo_produto);
    }
}



int main(){
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Opção pra imprimir em UTF-8

    Produto produtos[MAX_PRODUTOS];
    int contador = 0;
    int opcao;
    int *ponteiro_contador = &contador;

    //int id_produto;
    //Produto p1 = cria_produto();
    //printf("nome: %s", p1.nome);
    
    while (1) {
        printf("\n===== MENU =====\n");
        printf("1 - Criar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Buscar produto por código\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        if (opcao == 1) {
            menu_criar_produto(produtos, ponteiro_contador);
        } 

        else if (opcao == 2) {
            imprimir_produtos(produtos, ponteiro_contador);
        } 
        else if (opcao == 3) {
            buscar_por_codigo(produtos, ponteiro_contador);
        } 
        else {
            printf("Opção inválida!\n");
        }
    }
    
    return 0; 
}
