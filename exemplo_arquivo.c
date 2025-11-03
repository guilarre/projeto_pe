#include <stdio.h>
int main() {
  // struct produto {
  //   char nome[50];
  //   int codigo;
  //   float preco; // float ou double no nosso projeto?
  //   //...
  // };
  //
  // typedef struct produto Produto;
  //
  // Produto p1 = {"chicletin", 123, 4.5};
  // Produto p2 = {"chocolate", 123, 4.5};
  //
  // printf("%s, %d, %f", p1.nome, p1.codigo, p1.preco);
  // printf("%s, %d, %f", p2.nome, p2.codigo, p2.preco);

  FILE *fp;
  fp = fopen("produtos.txt", "r");

  return 0;
}
