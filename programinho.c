#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Criando uma constante pro máx de produtos
// #define MAX_PRODUTOS 50

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

// Contador usado para acessar elementos do vetor produtos[]
void ler_produtos(Produto **produtos, int *contador) {
    // Ponteiro pro arquivo
    FILE *fp;
    fp = fopen("produtos.txt", "r");
    // caso arquivo não exista
    if (!fp) {
        printf("ERRO: arquivo produtos.txt não foi encontrado!\n");
    };

    // Buffer de leitura
    char buf[100];
    char *delim = " "; // Delimitador = espaço

    // fgets() lê linha por linha
    while (fgets(buf, 100, fp)) {
        // Colocando cada dado lido em uma variável
        // strtok() para separar a string
        char *codigo_str = strtok(buf, delim); 
        // TEM que mudar pra NULL após primeiro split
        // por padrão quando usa strtok()
        char *nome = strtok(NULL, delim);
        char *preco_str = strtok(NULL, delim);
        char *quantidade_str = strtok(NULL, delim);

        int codigo, quantidade;
        float preco;

        // Convertendo pros tipos correto
        // atoi() = ASCII to int
        codigo = atoi(codigo_str);
        // atof() (ASCII to float) retorna um double
        // então tem que fazer cast para float no nosso caso
        preco = (float)atof(preco_str); 
        quantidade = atoi(quantidade_str);

        // Lógica pra salvar no struct produto
        // Verificamos a qtd máxima de produtos permitido
        // FIXME: Pode ser melhorado com alocação dinâmica,
        // não precisando de um máximo

        *produtos = realloc(*produtos, (*contador+1) * sizeof(Produto));
        if (*produtos != NULL) {
            (*produtos)[*contador] = cria_produto(nome, codigo, preco, quantidade);
            *contador += 1;
        } else {
            printf("ERRO: Limite máximo de produtos atingido!\n");
            return; // Retorno após erro
        }
     }

    

    // Fecha o stream do arquivo e libera espaço na memória
    fclose(fp);
}

// Vamos precisar do limpar_buffer() pra quando tiver
// fgets/scanf um junto do outro, por conta do comportamento
// do fgets de adicionar um \n no final e problemas do scanf
// em não saber lidar bem com isso
void limpar_buffer() {
    int c;
    // Consome os caracteres até o fim da linha/arquivo
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Função input_criar_produto
void menu_criar_produto(Produto **produtos, int *contador, int *contador_codigo) {
    char nome[50];
    int codigo = *contador_codigo;
    float preco;
    int quantidade;

    printf("Digite o nome do produto: \n");
    if (fgets(nome, sizeof(nome), stdin) == NULL) {
        printf("\nERRO: Nome inválido!.\n");
    }

    // Tirando o '\n' do fgets
    if (strlen(nome) > 0 && nome[strlen(nome)-1] == '\n') {
        nome[strlen(nome) - 1] = '\0';
    } else {
        // Caso n tenha '\n' é pq input excedeu o tamanho de nome
        limpar_buffer();
    }

    printf("Digite o preço do produto: \n");
    if (scanf("%f", &preco) != 1) {
        printf("\nERRO: Digite apenas números!\n");
        limpar_buffer(); // HACK: se não limpar aqui, continua no scanf
        return;
    }
    limpar_buffer(); // limpar após sucesso

    printf("Digite a quantidade do produto: \n");
    if (scanf("%d", &quantidade) != 1) {
        printf("\nERRO: Digite apenas números!\n");
        limpar_buffer(); // HACK: se não limpar aqui, continua no scanf
        return;
    }
    limpar_buffer(); // limpar após sucesso

    if (*produtos != NULL) {
        (*produtos)[*contador] = cria_produto(nome, codigo, preco, quantidade);
        *contador += 1;
        *contador_codigo += 1;
        printf("\nProduto criado com sucesso!\n");
    } else {
        printf("ERRO: Limite máximo de produtos atingido!\n");
        return;
    }
}


void imprimir_produtos(Produto **produtos, int *contador){
    printf("\n=== Lista de Produtos ===\n");
    
    if (*contador == 0) {
        printf("ERRO: Nenhum produto cadastrado ainda.\n");
        return;
    }

    for (int i = 0; i < *contador; i++) {
        printf("%d - %s | R$%.2f | Qtd: %d\n",
                (*produtos)[i].codigo,
                (*produtos)[i].nome,
                (*produtos)[i].preco,
                (*produtos)[i].quantidade);
    }
}

void buscar_por_codigo(Produto **produtos, int *contador){
    int codigo_produto;
    int encontrado = 0; 

    printf("Qual código do produto para buscar? ");
    scanf("%d", &codigo_produto);
    getchar();

    for (int i = 0; i < *contador; i++) {
        if(codigo_produto == (*produtos)[i].codigo){
            printf("\n=== Produto Encontrado ===\n");
            printf("%d - %s | R$%.2f | Qtd: %d\n",
                    (*produtos)[i].codigo,
                    (*produtos)[i].nome,
                    (*produtos)[i].preco,
                    (*produtos)[i].quantidade);
            encontrado = 1;
            break; 
        }
    }
 
    if (!encontrado) { // Avisa se não encontrou
        printf("ERRO: Produto com código %d não encontrado!\n", codigo_produto);
    }
}
void ordenar_por_preco(Produto **produtos, int *contador) {
    if (contador == 0) {
        printf("Nenhum produto cadastrado ainda.\n");
        return;
    }
 
    // Bubble Sort - ordena do menor para o maior preço
    for (int i = 0; i < *contador - 1; i++) {
        for (int j = 0; j < *contador - i - 1; j++) {
            if ((*produtos)[j].preco > (*produtos)[j + 1].preco) {
                // Troca os produtos de posição
                Produto temp = (*produtos)[j];
                (*produtos)[j] = (*produtos)[j + 1];
                (*produtos)[j + 1] = temp;
            }
        }
    }

    // Imprime os produtos ordenados
    printf("\n=== Produtos Ordenados por Preço ===\n");
    for (int i = 0; i < *contador; i++) {
        printf("%d - %s | R$%.2f | Qtd: %d\n",
               (*produtos)[i].codigo,
               (*produtos)[i].nome,
               (*produtos)[i].preco,
               (*produtos)[i].quantidade);
    }
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

int main() {
    Produto *produtos = NULL;
    int contador = 0;
    int contador_codigo = 121; // Incrementa a partir de 121 (seguindo contagem em produtos.txt)
    int opcao;

    ler_produtos(&produtos, &contador);

    while (1) {
        printa_menu(0);

        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer
        switch (opcao) {
            case 1:
                menu_criar_produto(&produtos, &contador, &contador_codigo);
                break;
            case 2:
                imprimir_produtos(&produtos, &contador);
                break;
            case 3:
                buscar_por_codigo(&produtos, &contador);
                break;
            case 4:
                ordenar_por_preco(&produtos, &contador);
                break;
            case 0:
                printf("\nAté logo!\n");
                exit(0);
            default:
                printf("Opção inválida!\n");
                break;
        }
    }
 
    free(produtos);
    return 0; 
}
