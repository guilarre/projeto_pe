#include <stdio.h>
#include <string.h>
#define MAX_PRODUTOS 100

// Struct pra armazenar produtos na memória
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

void ler_produtos(Produto produtos[], int *contador) {
  FILE *fp;
  fp = fopen("produtos.txt", "r");

  char buf[100];
  char *delim = " ";

  while (fgets(buf, 100, fp)) {
    char *codigo = strtok(buf, delim); // Delimita por espaço
    char *nome = strtok(NULL, delim);
    char *preco = strtok(NULL, delim);
    char *quantidade = strtok(NULL, delim);

    // Cast pros tipos corretos
    *codigo = (int)*codigo;
    *preco = (float)*preco;
    *quantidade = (int)*quantidade;

    // Lógica pra salvar no struct produto
    if (*contador < MAX_PRODUTOS) {
        produtos[*contador] = cria_produto(nome, *codigo, *preco, *quantidade);
        *contador += 1;
    } else {
        printf("ERRO: Limite máximo de produtos atingido!\n");
    }
  }

  fclose(fp);
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

    printf("Qual código do produto? ");
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

void printa_menu(int opcao) {
    char menu_inicial[] = "\n===== MENU =====\n" \
			"1 - Criar produto\n" \
			"2 - Listar produtos\n" \
			"3 - Buscar produto por código\n" \
			"4 - Ordenar produtos por preço\n\n" \
			"0 - Sair\n" \
    switch (opcao) {
        case 0:
            printf("%s", menu_inicial);
    }
}

int main(){
    Produto produtos[MAX_PRODUTOS];
    int contador = 0;
    int opcao;
    int *ponteiro_contador = &contador;

    ler_produtos(produtos, ponteiro_contador);

    while (1) {
        printa_menu(0);
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
