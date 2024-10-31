#include <stdio.h>

int qtd_clientes = 0;
int qtdLivros = 0;
int id_dos_clientes = 0;

struct cliente{
    char nome[50];
    int id;
};

struct dados_livro{
  int id;
  char titulo[50];
  char autor[50];
  int num_pag;
  int ano_pub;
  int qtd;
  int emprestimos[10];
  int tamanhoEm;
};

int verifica_id_livro(struct dados_livro estoque[],int id_temp){
    for(int i = 0;i<qtdLivros;i++){
        if(estoque[i].id == id_temp){
            return 1;
        }
    }
    return 0;
}
int verifica_id_cliente(struct cliente clientes[],int id_temp){
    for(int i = 0;i<qtd_clientes;i++){
        if(clientes[i].id == id_temp){
            return 1;
        }
    }
    return 0;
}
int verifica_qtd_livro(int qtd_temp){
    if(qtd_temp > 10 || qtd_temp < 1)return 1;
    else return 0;
}

void ignore_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
}

void cadastro_clientes(struct cliente *clientes){
    printf("------------------\n");
    clientes->id = id_dos_clientes;
    printf("Digite o nome do cliente:\n");
    ignore_input();
    fgets(clientes->nome,50,stdin);
    printf("Obrigado pelo cadastro!!! O ID do cliente e %d\n",id_dos_clientes);
    id_dos_clientes++;
    qtd_clientes++;
    printf("------------------\n");
}

void cadastro_livro(struct dados_livro estoque[]){
    printf("------------------\n");
    int id_temp,qtd_temp;
    printf("Digite o Id do livro: ");
    scanf("%d",&id_temp);
    while(verifica_id_livro(estoque,id_temp)){
        printf("O Id %d ja existe,Digite outro:\n",id_temp);
        scanf("%d",&id_temp);
    }
    estoque[qtdLivros].id = id_temp;
    getchar();
    printf("Digite o titulo do livro: ");
    fgets(estoque[qtdLivros].titulo,50,stdin);
    printf("Digite o nome do autor(a): ");
    fgets(estoque[qtdLivros].autor,50,stdin);
    printf("Digite o numero de paginas: ");
    scanf("%d",&estoque[qtdLivros].num_pag);
    printf("Digite o ano de publicacao: ");
    scanf("%d",&estoque[qtdLivros].ano_pub);
    printf("Digite a quantidade deste livro: ");
    scanf("%d",&qtd_temp);
    while(verifica_qtd_livro(qtd_temp)){
        printf("------------------\n");
        printf("Quantidade invalida,digite outra:\n");
        scanf("%d",&qtd_temp);
    }
    printf("Livro cadastrado com sucesso!!!\n");
    estoque[qtdLivros].qtd = qtd_temp;
    estoque[qtdLivros].tamanhoEm = 0;
    qtdLivros++;
}

void print_livro(struct dados_livro estoque){
    printf("ID: %d\n", estoque.id);
    printf("Titulo: %s", estoque.titulo);
    printf("Autor: %s", estoque.autor);
    printf("Numero de paginas: %d\n", estoque.num_pag);
    printf("Ano de publicacao: %d\n", estoque.ano_pub);
    printf("Quantidade: %d\n", estoque.qtd);
    printf("------------------\n");
}

void consulta_livro(struct dados_livro estoque[]){
    int optConsulta;
    printf("------------------\n");
    printf("Escolha uma opcao de consulta:\n");
    optConsulta = 0;
    while(optConsulta != 3){
        printf("1 - Listar todos os livros\n2 - Buscar por ID\n3 - Sair\n");
        scanf("%d", &optConsulta);
        switch (optConsulta){
            case 1:{
                if(qtdLivros == 0){
                    printf("------------------\n");
                    printf("Nenhum livro cadastrado.\n");
                    printf("------------------\n");
                }else{
                    for(int i = 0; i < qtdLivros; i++){
                        printf("------------------\n");
                        print_livro(estoque[i]);
                    }
                }
                break;
            }
            case 2:{
                int id_busca, encontrado = 0;
                printf("------------------\n");
                printf("Digite o ID do livro: ");
                scanf("%d", &id_busca);
                for(int i = 0; i < qtdLivros; i++){
                    if(estoque[i].id == id_busca){
                        printf("Livro encontrado! \n");
                        printf("------------------\n");
                        print_livro(estoque[i]);
                        encontrado = 1;
                        break;
                    }
                }
                if(!encontrado){
                    printf("Livro com ID %d nao encontrado. \n", id_busca);
                    printf("------------------\n");
                }
                break;
            }
            case 3:{
                break;
            }
            default:
                printf("Opcao invalida. \n");
        }
    }
}

void emprestimo_livro(struct dados_livro estoque[],struct cliente clientes[]){
    int id_livro;
    int opt = 0;
   
    printf("------------------\n");
    printf("1-Cadastrar Cliente\n2-Cliente ja cadastrado\n");
    scanf("%d",&opt);
    switch (opt){
        case 1:
            cadastro_clientes(&clientes[qtd_clientes]);
            break;
        case 2:
            break;
        default:
            printf("opcao invalida\n");
            return;
    }
    int id_temp_livro,id_cliente_temp;
    printf("Digite o ID do cliente:");
    scanf("%d",&id_cliente_temp);
    while(verifica_id_cliente(clientes,id_cliente_temp)!= 1){
        printf("O cliente com o Id %d nao existe,Digite outro:\n",id_cliente_temp);
        scanf("%d",&id_cliente_temp);
    }
    
    printf("Digite o Id do livro: ");
    scanf("%d",&id_temp_livro);
    while(verifica_id_livro(estoque,id_temp_livro) != 1){
        printf("O livro com o Id %d nao existe,Digite outro:\n",id_temp_livro);
        scanf("%d",&id_temp_livro);
    }
    for (int i = 0; i < qtdLivros; i++) {
        if (estoque[i].id == id_temp_livro) {
            for (int j = 0; j < estoque[i].tamanhoEm; j++) {
                if (estoque[i].emprestimos[j] == id_cliente_temp) {
                    printf("Voce ja possui um emprestimo ativo deste livro. nao e possivel fazer outro.\n");
                    return;
                }
            }
        }
    }
    for(int i = 0;i<qtdLivros;i++){
        if(estoque[i].id == id_temp_livro){
            for(int j = 0;j<qtd_clientes;j++){
                if(clientes[j].id == id_cliente_temp){
                    if(estoque[i].qtd == 0 ){
                        printf("Nao ha mais exemplares deste livro\n");
                        return;
                    }
                    estoque[i].emprestimos[estoque[i].tamanhoEm] = clientes[j].id;
                    estoque[i].qtd--;
                    estoque[i].tamanhoEm++;
                    printf("Empréstimo realizado com sucesso!\nRestam %d exemplares deste livro\n",estoque[i].qtd);
                    return;
                }
            }
        }
    }
}

void devolucao(struct dados_livro estoque[],struct cliente clientes[]){
    int id_temp_livro,id_cliente_temp;
    printf("------------------\n");
    printf("Digite o id do livro a ser devolvido:");
    scanf("%d",&id_temp_livro);
    while(verifica_id_livro(estoque,id_temp_livro) != 1){
        printf("O livro com o Id %d nao existe,Digite outro:\n",id_temp_livro);
        scanf("%d",&id_temp_livro);
    }
    
    printf("Digite o id do cliente:");
    scanf("%d",&id_cliente_temp);
    while(verifica_id_cliente(clientes,id_cliente_temp) != 1){
        printf("O cliente com o Id %d nao existe,Digite outro:\n",id_cliente_temp);
        scanf("%d",&id_cliente_temp);
    }
    
    for(int i = 0;i<qtdLivros;i++){
        if(estoque[i].id == id_temp_livro ){
            for (int j = 0; j < estoque[i].tamanhoEm; j++) {
                if (estoque[i].emprestimos[j] == id_cliente_temp) {
                    estoque[i].qtd++;
                    
                    for (int k = j; k < estoque[i].tamanhoEm - 1; k++) {
                        estoque[i].emprestimos[k] = estoque[i].emprestimos[k + 1];
                    }
                    
                    estoque[i].tamanhoEm--;
                    
                    printf("Livro devolvido com sucesso!!\n");
                    break;
                }
            }
        }
    }
}

void remover_livro(struct dados_livro estoque[]){
    int id_temp_livro;
    printf("------------------\n");
    printf("Digite o id do livro a ser removido do estoque:");
    scanf("%d",&id_temp_livro);
    while(verifica_id_livro(estoque,id_temp_livro) != 1){
        printf("O livro com o Id %d nao existe,Digite outro:\n",id_temp_livro);
        scanf("%d",&id_temp_livro);
    }
    
    for (int i = 0; i < qtdLivros; i++) {
        if (estoque[i].id == id_temp_livro) {
            
            for (int j = i; j < qtdLivros - 1; j++) {
                estoque[j] = estoque[j + 1];
            }
            qtdLivros--; 
            printf("Livro com id %d removido do estoque com sucesso!\n", id_temp_livro);
            return; 
        }
    }
    
    printf("Livro não encontrado no estoque.\n");
}
void teste(struct dados_livro estoque[]){
    for(int i = 0;i<qtdLivros;i++){
        printf("%d",estoque[i].id);
        
    }
}

int main(){
    struct dados_livro estoque[100];
    struct cliente clientes[1000];
    int opt = 0;
    while(opt != 6){
        printf("-------Menu-------\n");
        printf("1- Cadastrar livro\n2- Consultar livro\n3- Emprestimo de livro\n4- Devolucao\n5- Remover Livro\n");
        scanf("%d",&opt);
        switch (opt){
            case 1:
                cadastro_livro(estoque);
                break;
            case 2:
                consulta_livro(estoque);
                break;
            case 3:
                emprestimo_livro(estoque,clientes);
                break;
            case 4:
                devolucao(estoque,clientes);
                break;
            case 5:
                remover_livro(estoque);
                break;
            case 7:
                teste(estoque);
        }
    }
}
