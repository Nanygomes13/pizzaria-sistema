#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ===================== CONSTANTES =====================
#define MAX_CLIENTES 50
#define MAX_PIZZAS 50
#define MAX_PEDIDOS 100
#define MAX_CARRINHO 10

#define ARQ_CLIENTES "clientes.txt"
#define ARQ_PIZZAS "pizzas.txt"
#define ARQ_PEDIDOS "pedidos.txt"
#define ARQ_LOGS "logs.txt"

// ===================== ESTRUTURAS =====================
typedef struct {
    int id;
    char nome[50];
    char telefone[20];
    char endereco[100];
} Cliente;

typedef struct {
    int id;
    char nome[50];
    char tipo[30];
    float preco;
    int vendidas;
} Pizza;

typedef struct {
    int idCliente;
    int idPizza;
    int quantidade;
    char pagamento[20];
    float total;
} Pedido;

// ===================== VARIÁVEIS GLOBAIS =====================
Cliente clientes[MAX_CLIENTES];
Pizza pizzas[MAX_PIZZAS];
Pedido pedidos[MAX_PEDIDOS];
int totalClientes = 0, totalPizzas = 0, totalPedidos = 0;

// ===================== FUNÇÕES AUXILIARES =====================
void salvarLog(char *acao) {
    FILE *f = fopen(ARQ_LOGS, "a");
    if (f) {
        fprintf(f, "%s\n", acao);
        fclose(f);
    }
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

// ===================== CLIENTES =====================
void cadastrarCliente() {
    Cliente c;
    c.id = totalClientes + 1;

    printf("Nome do cliente: ");
    fgets(c.nome, 50, stdin); strtok(c.nome, "\n");

    printf("Telefone: ");
    fgets(c.telefone, 20, stdin); strtok(c.telefone, "\n");

    printf("Endereço: ");
    fgets(c.endereco, 100, stdin); strtok(c.endereco, "\n");

    clientes[totalClientes++] = c;

    FILE *f = fopen(ARQ_CLIENTES, "a");
    if (f) {
        fprintf(f, "%d;%s;%s;%s\n", c.id, c.nome, c.telefone, c.endereco);
        fclose(f);
    }

    salvarLog("Novo cliente cadastrado.");
    printf("\nCliente cadastrado com sucesso!\n");
}

void listarClientes() {
    printf("\n--- Lista de Clientes ---\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("%d - %s (%s)\n", clientes[i].id, clientes[i].nome, clientes[i].telefone);
    }
}

// ===================== PIZZAS =====================
void cadastrarPizza() {
    Pizza p;
    p.id = totalPizzas + 1;
    p.vendidas = 0;

    printf("Nome da pizza: ");
    fgets(p.nome, 50, stdin); strtok(p.nome, "\n");

    printf("Tipo (salgada, doce, etc): ");
    fgets(p.tipo, 30, stdin); strtok(p.tipo, "\n");

    printf("Preço: ");
    scanf("%f", &p.preco);
    getchar();

    pizzas[totalPizzas++] = p;

    FILE *f = fopen(ARQ_PIZZAS, "a");
    if (f) {
        fprintf(f, "%d;%s;%s;%.2f;%d\n", p.id, p.nome, p.tipo, p.preco, p.vendidas);
        fclose(f);
    }

    salvarLog("Nova pizza cadastrada.");
    printf("\nPizza cadastrada com sucesso!\n");
}

void listarPizzas() {
    printf("\n--- Cardápio de Pizzas ---\n");
    for (int i = 0; i < totalPizzas; i++) {
        printf("%d - %s (%s) - R$%.2f\n", pizzas[i].id, pizzas[i].nome, pizzas[i].tipo, pizzas[i].preco);
    }
}

// ===================== PEDIDOS E CARRINHO =====================
void fazerPedido() {
    int idCliente, opcaoPizza, qtd, continuar = 1;
    float totalPedido = 0;
    Pedido carrinho[MAX_CARRINHO];
    int itensCarrinho = 0;

    listarClientes();
    printf("\nDigite o ID do cliente: ");
    scanf("%d", &idCliente);
    getchar();

    while (continuar) {
        listarPizzas();
        printf("\nEscolha o ID da pizza: ");
        scanf("%d", &opcaoPizza);
        printf("Quantidade: ");
        scanf("%d", &qtd);
        getchar();

        if (opcaoPizza <= totalPizzas && idCliente <= totalClientes) {
            Pizza p = pizzas[opcaoPizza - 1];
            Pedido ped;
            ped.idCliente = idCliente;
            ped.idPizza = opcaoPizza;
            ped.quantidade = qtd;
            ped.total = qtd * p.preco;
            totalPedido += ped.total;
            carrinho[itensCarrinho++] = ped;
            pizzas[opcaoPizza - 1].vendidas += qtd;
            printf("Pizza adicionada ao carrinho!\n");
        } else {
            printf("ID inválido.\n");
        }

        printf("\nDeseja adicionar mais uma pizza? (1=Sim / 0=Não): ");
        scanf("%d", &continuar);
        getchar();
    }

    printf("\nForma de pagamento (dinheiro, pix, cartão): ");
    char pagamento[20];
    fgets(pagamento, 20, stdin); strtok(pagamento, "\n");

    FILE *f = fopen(ARQ_PEDIDOS, "a");
    if (f) {
        for (int i = 0; i < itensCarrinho; i++) {
            fprintf(f, "%d;%d;%d;%d;%.2f;%s\n",
                    carrinho[i].idCliente,
                    carrinho[i].idPizza,
                    carrinho[i].quantidade,
                    i + 1,
                    carrinho[i].total,
                    pagamento);
        }
        fclose(f);
    }

    salvarLog("Novo pedido realizado.");
    printf("\nPedido finalizado! Total: R$%.2f\n", totalPedido);
}

// ===================== RELATÓRIOS =====================
void relatorioPizzasMaisVendidas() {
    printf("\n--- Pizzas Mais Vendidas ---\n");
    for (int i = 0; i < totalPizzas; i++) {
        printf("%s - Vendidas: %d\n", pizzas[i].nome, pizzas[i].vendidas);
    }
}

// ===================== LOGIN =====================
int login() {
    char user[20], senha[20];
    printf("=== LOGIN PIZZAFONY ===\n");
    printf("Usuário: ");
    fgets(user, 20, stdin); strtok(user, "\n");
    printf("Senha: ");
    fgets(senha, 20, stdin); strtok(senha, "\n");

    if (strcmp(user, "gerente") == 0 && strcmp(senha, "123") == 0) {
        printf("Bem-vindo, gerente!\n");
        return 2;
    } else if (strcmp(user, "atendente") == 0 && strcmp(senha, "123") == 0) {
        printf("Bem-vindo, atendente!\n");
        return 1;
    } else {
        printf("Login inválido!\n");
        return 0;
    }
}

// ===================== MENU PRINCIPAL =====================
void menuPrincipal(int nivel) {
    int opcao;
    do {
        printf("\n===== MENU PIZZAFONY =====\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Cadastrar Pizza\n");
        printf("3 - Fazer Pedido\n");
        printf("4 - Relatório Pizzas Mais Vendidas\n");
        printf("5 - Contato Suporte\n");
        printf("0 - Sair\n");
        printf("==========================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarCliente(); break;
            case 2: if (nivel == 2) cadastrarPizza(); else printf("Apenas o gerente pode cadastrar pizzas.\n"); break;
            case 3: fazerPedido(); break;
            case 4: relatorioPizzasMaisVendidas(); break;
            case 5:
                printf("\nSuporte Pizzafony:\nTelefone: (82) 99973-7470\nE-mail: pizzafonysuporte@gmail.com\n");
                break;
            case 0:
                printf("Saindo do sistema...\n");
                salvarLog("Sistema encerrado.");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}

// ===================== PROGRAMA PRINCIPAL =====================
int main() {
    int nivel = login();
    if (nivel == 0) {
        printf("Encerrando o sistema.\n");
        return 0;
    }

    menuPrincipal(nivel);

    return 0;
}
