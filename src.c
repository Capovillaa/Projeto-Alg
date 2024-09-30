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

void consulta_livro(struct dados_livro estoque[]){
    int optConsulta;
    printf("Escolha uma opcao de consulta:\n");
    printf("1 - Listar todos os livros\n");
    printf("2 - Buscar por ID\n");
    scanf("%d", &optConsulta);

    if(optConsulta == 1){
        if(qtdLivros == 0){
            printf("Nenhum livro cadastrado.\n");
        }else{
            for(int i = 0; i < qtdLivros; i++){
                printf("ID: %d\n", estoque[i].id);
                printf("Titulo: %s", estoque[i].titulo);
                printf("Autor: %s", estoque[i].autor);
                printf("Numero de paginas: %d\n", estoque[i].num_pag);
                printf("Ano de publicacao: %d\n", estoque[i].ano_pub);
                printf("Quantidade: %d\n", estoque[i].qtd);
                printf("-------------------------\n");
            }
        }
    }else if(optConsulta == 2){
        int id_busca, encontrado = 0;
        printf("Digite o ID do livro: ");
        scanf("%d", &id_busca);
        for(int i = 0; i < qtdLivros; i++){
            if(estoque[i].id == id_busca){
                printf("Livro encontrado! \n");
                printf("ID: %d \n", estoque[i].id);
                printf("Titulo: %s", estoque[i].titulo);
                printf("Autor: %s", estoque[i].autor);
                printf("Numero de paginas: %d \n", estoque[i].num_pag);
                printf("Ano de publicacao: %d \n", estoque[i].ano_pub);
                printf("Quantidade: %d \n", estoque[i].qtd);
                encontrado = 1;
                break;
            }
        }
        if(!encontrado){
            printf("Livro com ID %d nao encontrado. \n", id_busca);
        }
    }else{
        printf("Opcao invalida. \n");
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
                consulta_livro(estoque);
                break; 
        }
    }
}
