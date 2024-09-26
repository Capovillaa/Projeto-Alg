#include <stdio.h>

int qtdLivros = 0;

struct dados_livro{
  int id;
  char titulo[50];
  char autor[50];
  int num_pag;
  int ano_pub;
  int qtd;
};

void cadastro_livro(struct dados_livro estoque[]){
    qtdLivros++;
    for(int i = 0;i < qtdLivros;i++){
        printf("Digite o Id do livro: ");
        scanf("%d",&estoque[i].id);
        printf("Digite o titulo do livro: ");
        fgets(estoque[i].titulo,50,stdin);
        printf("Digite o nome do autor(a): ");
        fgets(estoque[i].autor,50,stdin);
        printf("Digite o numero de paginas: ");
        scanf("%d",&estoque[i].num_pag);
        printf("Digite o ano de publicacao: ");
        scanf("%d",&estoque[i].ano_pub);
        printf("Digite a quantidade deste livro: ");
        scanf("%d",&estoque[i].qtd);
        printf("-------------------------\n");
    }    
}

int main(){
    struct dados_livro estoque[100];
    int opt = 0;
    while(opt != 6){
        printf("Menu: ");
        scanf("%d",&opt);
        switch (opt){
            case 1:
                cadastro_livro(estoque);
                break;
            case 2:
                
        }
    }
    
    return 0;
}
