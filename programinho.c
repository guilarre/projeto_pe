#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PRODUTOS 50

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
    char *codigo_str = strtok(buf, delim); // Delimita por espaço
    char *nome = strtok(NULL, delim);
    char *preco_str = strtok(NULL, delim);
    char *quantidade_str = strtok(NULL, delim);

    int codigo, quantidade;
    float preco;

    // Convertendo pros tipos correto
    codigo = atoi(codigo_str);
    preco = (float)atof(preco_str); // atof() retorna um double
    quantidade = atoi(quantidade_str);

    // Lógica pra salvar no struct produto
    if (*contador < MAX_PRODUTOS) {
        produtos[*contador] = cria_produto(nome, codigo, preco, quantidade);
        *contador += 1;
    } else {
        printf("ERRO: Limite máximo de produtos atingido!\n");
    }
  }

  fclose(fp);
}

// Função input_criar_produto
void menu_criar_produto(Produto produtos[], int *contador, int *contador_codigo){
    char nome[50];
    int codigo = *contador_codigo;
    float preco;
    int quantidade;

    // TODO: validação da string digitada
    printf("Digite o nome do produto: \n");
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome) - 1] = '\0';

    // printf("Digite o codigo do produto: \n");
    // if (scanf("%d", &codigo) != 1) {
    //     printf("\nERRO: Digite apenas números!\n");
    //     return;
    // };

    printf("Digite o preço do produto: \n");
    if (scanf("%f", &preco) != 1) {
        printf("\nERRO: Digite apenas números!\n");
        return; // FIXME: dá erro após retornar
    };

    printf("Digite a quantidade do produto: \n");
    scanf("%d", &quantidade);

    if (*contador < MAX_PRODUTOS) {
        produtos[*contador] = cria_produto(nome, codigo, preco, quantidade);
        *contador += 1;
        *contador_codigo += 1;
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

    printf("Qual código do produto para buscar? ");
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

void ordenar_preco(Produto produtos[]) {

}

void printa_menu(int opcao) {
    char menu_inicial[] = "\n===== MENU =====\n" \
			"1 - Criar produto\n" \
			"2 - Listar produtos\n" \
			"3 - Buscar produto por código\n" \
			"4 - Ordenar produtos por preço\n\n" \
			"0 - Sair\n";

    switch (opcao) {
        case 0:
            printf("%s", menu_inicial);
            break;
    }
}

int main(){
    Produto produtos[MAX_PRODUTOS];
    int contador = 0;
    int contador_codigo = 121; // Incrementa a partir de 121 (seguindo contagem em produtos.txt)
    int opcao;

    ler_produtos(produtos, &contador);

    while (1) {
        printa_menu(0);
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer
        switch (opcao) {
            case 1:
                menu_criar_produto(produtos, &contador, &contador_codigo);
                break;
            case 2:
                imprimir_produtos(produtos, &contador);
                break;
            case 3:
                buscar_por_codigo(produtos, &contador);
                break;
            case 0:
                printf("\nAté logo!\n");
                exit(0);
            default:
                printf("Opção inválida!\n");
                break;
        }
    }
    
    return 0; 
}
