#include <stdio.h>
#include <string.h>
#include <locale.h> // Pra forçar UTF-8

#define MAX_PRODUTOS 100

struct produto
{
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
};

typedef struct produto Produto;


Produto cria_produto(){
    Produto produto; 

    printf("Digite o nome do produto: \n");
    fgets(produto.nome, sizeof(produto.nome), stdin);
    produto.nome[strlen(produto.nome) - 1] = '\0';         // Remove o '\n' usando strlen()

    printf("Digite o codigo do produto: \n");
    scanf("%d", &produto.codigo);

  
    printf("Digite o preço do produto: \n");
    scanf("%f", &produto.preco);

    printf("Digite a quantidade do produto: \n");
    scanf("%d", &produto.quantidade);

    return produto;
}

int main(){
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Opção pra imprimir em UTF-8

    Produto produtos[MAX_PRODUTOS];
    int contador = 0;
    int opcao;

    //int id_produto;
    //Produto p1 = cria_produto();
    //printf("nome: %s", p1.nome);
    

}
