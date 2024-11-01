#include <stdio.h>

int qtd_clientes = 0;
int qtdLivros = 0;
int id_dos_clientes = 0;

// Estrutura para armazenar informações de um cliente.
struct cliente {
    char nome[50]; 
    int id;         
};

// Estrutura para armazenar informações de um livro.
struct dados_livro {
    int id;              
    char titulo[50];     
    char autor[50];      
    int num_pag;         
    int ano_pub;         
    int qtd;             // Quantidade de exemplares disponíveis
    int emprestimos[10]; // IDs dos clientes que emprestaram o livro (máx. 10)
    int tamanhoEm;       // Número de empréstimos realizados
};

// Função para verificar se um ID de livro já existe no estoque.
int verifica_id_livro(struct dados_livro estoque[], int id_temp) {
    for (int i = 0; i < qtdLivros; i++) {
        if (estoque[i].id == id_temp) {
            return 1;  
        }
    }
    return 0;  
}

// Função para verificar se um ID de cliente já existe no sistema.
int verifica_id_cliente(struct cliente clientes[], int id_temp) {
    for (int i = 0; i < qtd_clientes; i++) {
        if (clientes[i].id == id_temp) {
            return 1;  
        }
    }
    return 0;  
}

// Função para verificar se a quantidade de livros inserida é válida (1 a 10).
int verifica_qtd_livro(int qtd_temp) {
    if (qtd_temp > 10 || qtd_temp < 1) return 1;  
    else return 0;  
}

// Função para limpar o buffer de entrada.
void ignore_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
}

// Função para cadastrar um novo cliente.
void cadastro_clientes(struct cliente *clientes) {
    printf("------------------\n");
    clientes->id = id_dos_clientes;  // Atribui ID único ao cliente
    printf("Digite o nome do cliente:\n");
    ignore_input();
    fgets(clientes->nome, 50, stdin);  
    printf("Obrigado pelo cadastro!!! O ID do cliente e %d\n", id_dos_clientes);
    id_dos_clientes++;  // Incrementa o ID para o próximo cliente
    qtd_clientes++;     // Incrementa o contador de clientes
    printf("------------------\n");
}

// Função para cadastrar um novo livro no estoque.
void cadastro_livro(struct dados_livro estoque[]) {
    printf("------------------\n");
    int id_temp, qtd_temp;
    printf("Digite o Id do livro: ");
    scanf("%d", &id_temp);
    while (verifica_id_livro(estoque, id_temp)) {  // Verifica se o ID já existe
        printf("O Id %d ja existe, Digite outro:\n", id_temp);
        scanf("%d", &id_temp);
    }
    estoque[qtdLivros].id = id_temp;
    getchar();  // Limpa o buffer de entrada
    printf("Digite o titulo do livro: ");
    fgets(estoque[qtdLivros].titulo, 50, stdin);  
    printf("Digite o nome do autor(a): ");
    fgets(estoque[qtdLivros].autor, 50, stdin);  
    printf("Digite o numero de paginas: ");
    scanf("%d", &estoque[qtdLivros].num_pag);
    printf("Digite o ano de publicacao: ");
    scanf("%d", &estoque[qtdLivros].ano_pub);
    printf("Digite a quantidade deste livro: ");
    scanf("%d", &qtd_temp);
    while (verifica_qtd_livro(qtd_temp)) {  // Verifica se a quantidade é válida
        printf("------------------\n");
        printf("Quantidade invalida, digite outra:\n");
        scanf("%d", &qtd_temp);
    }
    printf("Livro cadastrado com sucesso!!!\n");
    estoque[qtdLivros].qtd = qtd_temp;  // Atribui a quantidade ao estoque do livro
    estoque[qtdLivros].tamanhoEm = 0;  // Inicializa o número de empréstimos
    qtdLivros++;  // Incrementa o contador de livros
}

// Função para exibir as informações de um livro específico.
void print_livro(struct dados_livro estoque) {
    printf("ID: %d\n", estoque.id);
    printf("Titulo: %s", estoque.titulo);
    printf("Autor: %s", estoque.autor);
    printf("Numero de paginas: %d\n", estoque.num_pag);
    printf("Ano de publicacao: %d\n", estoque.ano_pub);
    printf("Quantidade: %d\n", estoque.qtd);
    printf("------------------\n");
}

// Função para consultar livros no estoque.
void consulta_livro(struct dados_livro estoque[]) {
    int optConsulta;
    printf("------------------\n");
    printf("Escolha uma opcao de consulta:\n");
    optConsulta = 0;
    while (optConsulta != 3) {
        printf("1 - Listar todos os livros\n2 - Buscar por ID\n3 - Sair\n");
        scanf("%d", &optConsulta);
        switch (optConsulta) {
            case 1: { 
                if (qtdLivros == 0) {
                    printf("------------------\n");
                    printf("Nenhum livro cadastrado.\n");
                    printf("------------------\n");
                } else {
                    for (int i = 0; i < qtdLivros; i++) {
                        printf("------------------\n");
                        print_livro(estoque[i]); 
                    }
                }
                break;
            }
            case 2: {  
                int id_busca, encontrado = 0;
                printf("------------------\n");
                printf("Digite o ID do livro: ");
                scanf("%d", &id_busca);
                for (int i = 0; i < qtdLivros; i++) {
                    if (estoque[i].id == id_busca) {
                        printf("Livro encontrado! \n");
                        printf("------------------\n");
                        print_livro(estoque[i]);  
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {  
                    printf("Livro com ID %d nao encontrado. \n", id_busca);
                    printf("------------------\n");
                }
                break;
            }
            case 3: {
                break;  
            }
            default:
                printf("Opcao invalida. \n"); 
        }
    }
}
// Função para realizar o empréstimo de um livro
void emprestimo_livro(struct dados_livro estoque[], struct cliente clientes[]) {
    int id_livro;
    int opt = 0; 

    printf("------------------\n");
    printf("1-Cadastrar Cliente\n2-Cliente já cadastrado\n");
    scanf("%d", &opt); 
    switch (opt) {
        case 1:
            cadastro_clientes(&clientes[qtd_clientes]);
            break;
        case 2:
            break;
        default:
            printf("Opção inválida\n");
            return; 
    }

    int id_temp_livro, id_cliente_temp;
    printf("Digite o ID do cliente: ");
    scanf("%d", &id_cliente_temp); 

    // Verifica se o ID do cliente existe
    while (verifica_id_cliente(clientes, id_cliente_temp) != 1) {
        printf("O cliente com o Id %d não existe,Digite outro:\n", id_cliente_temp);
        scanf("%d", &id_cliente_temp); // Solicita um novo ID se o anterior for inválido
    }

    printf("Digite o Id do livro: ");
    scanf("%d", &id_temp_livro); 

    // Verifica se o ID do livro existe
    while (verifica_id_livro(estoque, id_temp_livro) != 1) {
        printf("O livro com o Id %d não existe,Digite outro:\n", id_temp_livro);
        scanf("%d", &id_temp_livro); // Solicita um novo ID se o anterior for inválido
    }

    // Verifica se o cliente já possui um empréstimo ativo desse livro
    for (int i = 0; i < qtdLivros; i++) {
        if (estoque[i].id == id_temp_livro) {
            for (int j = 0; j < estoque[i].tamanhoEm; j++) {
                if (estoque[i].emprestimos[j] == id_cliente_temp) {
                    printf("Você já possui um empréstimo ativo deste livro. Não é possível fazer outro.\n");
                    return; // Retorna se já tiver um empréstimo ativo
                }
            }
        }
    }

    // Realiza o empréstimo do livro ao cliente
    for (int i = 0; i < qtdLivros; i++) {
        if (estoque[i].id == id_temp_livro) {
            for (int j = 0; j < qtd_clientes; j++) {
                if (clientes[j].id == id_cliente_temp) {
                    if (estoque[i].qtd == 0) {
                        printf("Não há mais exemplares deste livro\n");
                        return; // Retorna se não houver mais exemplares disponíveis
                    }
                    // Adiciona o ID do cliente ao registro de empréstimos
                    estoque[i].emprestimos[estoque[i].tamanhoEm] = clientes[j].id;
                    estoque[i].qtd--; // Reduz a quantidade de livros disponíveis
                    estoque[i].tamanhoEm++; // Aumenta o tamanho dos empréstimos
                    printf("Empréstimo realizado com sucesso!\nRestam %d exemplares deste livro\n", estoque[i].qtd);
                    return; // Retorna após realizar o empréstimo
                }
            }
        }
    }
}

// Função para realizar a devolução de um livro
void devolucao(struct dados_livro estoque[], struct cliente clientes[]) {
    int id_temp_livro, id_cliente_temp;
    printf("------------------\n");
    printf("Digite o id do livro a ser devolvido: ");
    scanf("%d", &id_temp_livro); 

    // Verifica se o ID do livro existe
    while (verifica_id_livro(estoque, id_temp_livro) != 1) {
        printf("O livro com o Id %d não existe,Digite outro:\n", id_temp_livro);
        scanf("%d", &id_temp_livro); // Solicita um novo ID se o anterior for inválido
    }

    printf("Digite o id do cliente: ");
    scanf("%d", &id_cliente_temp); 

    // Verifica se o ID do cliente existe
    while (verifica_id_cliente(clientes, id_cliente_temp) != 1) {
        printf("O cliente com o Id %d não existe,Digite outro:\n", id_cliente_temp);
        scanf("%d", &id_cliente_temp); // Solicita um novo ID se o anterior for inválido
    }

    // Realiza a devolução do livro
    for (int i = 0; i < qtdLivros; i++) {
        if (estoque[i].id == id_temp_livro) {
            for (int j = 0; j < estoque[i].tamanhoEm; j++) {
                if (estoque[i].emprestimos[j] == id_cliente_temp) {
                    estoque[i].qtd++; // Aumenta a quantidade de livros disponíveis

                    // Remove o ID do cliente da lista de empréstimos
                    for (int k = j; k < estoque[i].tamanhoEm - 1; k++) {
                        estoque[i].emprestimos[k] = estoque[i].emprestimos[k + 1];
                    }

                    estoque[i].tamanhoEm--; // Reduz o tamanho dos empréstimos
                    printf("Livro devolvido com sucesso!!\n");
                    break; 
                }
            }
        }
    }
}

// Função para remover um livro do estoque
void remover_livro(struct dados_livro estoque[]) {
    int id_temp_livro;
    printf("------------------\n");
    printf("Digite o id do livro a ser removido do estoque: ");
    scanf("%d", &id_temp_livro); 

    // Verifica se o ID do livro existe
    while (verifica_id_livro(estoque, id_temp_livro) != 1) {
        printf("O livro com o Id %d não existe,Digite outro:\n", id_temp_livro);
        scanf("%d", &id_temp_livro); // Solicita um novo ID se o anterior for inválido
    }

    // Remove o livro do estoque
    for (int i = 0; i < qtdLivros; i++) {
        if (estoque[i].id == id_temp_livro) {
            // Desloca os livros restantes para preencher a lacuna
            for (int j = i; j < qtdLivros - 1; j++) {
                estoque[j] = estoque[j + 1];
            }
            qtdLivros--; // Reduz a contagem total de livros
            printf("Livro com id %d removido do estoque com sucesso!\n", id_temp_livro);
            return; 
        }
    }

    printf("Livro não encontrado no estoque.\n");
}

