
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTS 100
#define MAX_PIZZAS 100
#define MAX_ORDERS 1000
#define MAX_USERS 20
#define LINE_LEN 256

typedef struct {
    int id;
    char nome[60];
    char telefone[30];
} Cliente;

typedef struct {
    int id;
    char sabor[60];
    float preco;
    int vendidas;
} Pizza;

typedef struct {
    int id;
    int client_id;
    int pizza_id;
    int quantidade;
    char pagamento[30];
    double total;
    long timestamp; // time_t as long
} Order;

typedef struct {
    char username[40];
    char password[40];
    char role[20]; // "gerente" or "atendente"
} User;

Cliente clients[MAX_CLIENTS];
int clients_count = 0;
Pizza pizzas[MAX_PIZZAS];
int pizzas_count = 0;
Order orders[MAX_ORDERS];
int orders_count = 0;
User users[MAX_USERS];
int users_count = 0;

const char *FILE_USERS = "usuarios.txt";
const char *FILE_CLIENTS = "clientes.txt";
const char *FILE_PIZZAS = "pizzas.txt";
const char *FILE_ORDERS = "pedidos.txt";
const char *FILE_LOGS = "logs.txt";

void log_action(const char *msg) {
    FILE *f = fopen(FILE_LOGS, "a");
    if (!f) return;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char timestr[64];
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", &tm);
    fprintf(f, "[%s] %s\n", timestr, msg);
    fclose(f);
}

void pause_console() {
    printf("\nPressione ENTER para continuar...");
    fflush(stdout);
    getchar();
}

void trim_nl(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r')) { s[n-1] = '\0'; n--; }
}

int next_client_id() {
    int max = 0;
    for (int i = 0; i < clients_count; i++) if (clients[i].id > max) max = clients[i].id;
    return max + 1;
}
int next_pizza_id() {
    int max = 0;
    for (int i = 0; i < pizzas_count; i++) if (pizzas[i].id > max) max = pizzas[i].id;
    return max + 1;
}
int next_order_id() {
    int max = 0;
    for (int i = 0; i < orders_count; i++) if (orders[i].id > max) max = orders[i].id;
    return max + 1;
}

void load_users() {
    FILE *f = fopen(FILE_USERS, "r");
    users_count = 0;
    if (!f) return;
    while (!feof(f) && users_count < MAX_USERS) {
        char line[LINE_LEN];
        if (!fgets(line, sizeof(line), f)) break;
        trim_nl(line);
        if (strlen(line) == 0) continue;
        char u[40], p[40], r[20];
        if (sscanf(line, "%39[^;];%39[^;];%19[^\n]", u, p, r) == 3) {
            strcpy(users[users_count].username, u);
            strcpy(users[users_count].password, p);
            strcpy(users[users_count].role, r);
            users_count++;
        }
    }
    fclose(f);
    if (users_count == 0) {
        strcpy(users[0].username, "gerente");
        strcpy(users[0].password, "1234");
        strcpy(users[0].role, "gerente");
        users_count = 1;
        FILE *fw = fopen(FILE_USERS, "w");
        if (fw) {
            fprintf(fw, "%s;%s;%s\n", users[0].username, users[0].password, users[0].role);
            fclose(fw);
        }
    }
}

void save_users() {
    FILE *f = fopen(FILE_USERS, "w");
    if (!f) return;
    for (int i = 0; i < users_count; i++)
        fprintf(f, "%s;%s;%s\n", users[i].username, users[i].password, users[i].role);
    fclose(f);
}

void load_clients() {
    FILE *f = fopen(FILE_CLIENTS, "r");
    clients_count = 0;
    if (!f) return;
    while (!feof(f) && clients_count < MAX_CLIENTS) {
        if (fscanf(f, "%d;%59[^;];%29[^\n]\n", &clients[clients_count].id, clients[clients_count].nome, clients[clients_count].telefone) == 3)
            clients_count++;
        else break;
    }
    fclose(f);
}

void save_clients() {
    FILE *f = fopen(FILE_CLIENTS, "w");
    if (!f) return;
    for (int i = 0; i < clients_count; i++)
        fprintf(f, "%d;%s;%s\n", clients[i].id, clients[i].nome, clients[i].telefone);
    fclose(f);
}

void load_pizzas() {
    FILE *f = fopen(FILE_PIZZAS, "r");
    pizzas_count = 0;
    if (!f) return;
    while (!feof(f) && pizzas_count < MAX_PIZZAS) {
        if (fscanf(f, "%d;%59[^;];%f;%d\n", &pizzas[pizzas_count].id, pizzas[pizzas_count].sabor, &pizzas[pizzas_count].preco, &pizzas[pizzas_count].vendidas) == 4)
            pizzas_count++;
        else break;
    }
    fclose(f);
}

void save_pizzas() {
    FILE *f = fopen(FILE_PIZZAS, "w");
    if (!f) return;
    for (int i = 0; i < pizzas_count; i++)
        fprintf(f, "%d;%s;%.2f;%d\n", pizzas[i].id, pizzas[i].sabor, pizzas[i].preco, pizzas[i].vendidas);
    fclose(f);
}

void load_orders() {
    FILE *f = fopen(FILE_ORDERS, "r");
    orders_count = 0;
    if (!f) return;
    while (!feof(f) && orders_count < MAX_ORDERS) {
        if (fscanf(f, "%d;%d;%d;%d;%29[^;];%lf;%ld\n",
                   &orders[orders_count].id,
                   &orders[orders_count].client_id,
                   &orders[orders_count].pizza_id,
                   &orders[orders_count].quantidade,
                   orders[orders_count].pagamento,
                   &orders[orders_count].total,
                   &orders[orders_count].timestamp) == 7)
            orders_count++;
        else break;
    }
    fclose(f);
}

void save_orders() {
    FILE *f = fopen(FILE_ORDERS, "w");
    if (!f) return;
    for (int i = 0; i < orders_count; i++)
        fprintf(f, "%d;%d;%d;%d;%s;%.2f;%ld\n", orders[i].id, orders[i].client_id, orders[i].pizza_id,
                orders[i].quantidade, orders[i].pagamento, orders[i].total, orders[i].timestamp);
    fclose(f);
}

void add_client() {
    if (clients_count >= MAX_CLIENTS) { printf("Limite de clientes alcançado.\n"); return; }
    Cliente c;
    c.id = next_client_id();
    getchar();
    printf("Nome: ");
    fgets(c.nome, sizeof(c.nome), stdin); trim_nl(c.nome);
    printf("Telefone: ");
    fgets(c.telefone, sizeof(c.telefone), stdin); trim_nl(c.telefone);
    clients[clients_count++] = c;
    save_clients();
    log_action("Cliente cadastrado");
    printf("Cliente cadastrado com ID %d.\n", c.id);
}

void list_clients() {
    printf("\n--- CLIENTES ---\n");
    for (int i = 0; i < clients_count; i++)
        printf("ID:%d | %s | %s\n", clients[i].id, clients[i].nome, clients[i].telefone);
}

int find_client_index_by_id(int id) {
    for (int i = 0; i < clients_count; i++) if (clients[i].id == id) return i;
    return -1;
}

void update_client() {
    int id;
    list_clients();
    printf("ID do cliente a alterar: ");
    scanf("%d", &id);
    int idx = find_client_index_by_id(id);
    if (idx == -1) { printf("Cliente não encontrado.\n"); return; }
    getchar();
    char tmp[60];
    printf("Novo nome (ENTER para manter: %s): ", clients[idx].nome);
    fgets(tmp, sizeof(tmp), stdin); trim_nl(tmp);
    if (strlen(tmp)) strcpy(clients[idx].nome, tmp);
    printf("Novo telefone (ENTER para manter: %s): ", clients[idx].telefone);
    fgets(tmp, sizeof(tmp), stdin); trim_nl(tmp);
    if (strlen(tmp)) strcpy(clients[idx].telefone, tmp);
    save_clients();
    log_action("Cliente alterado");
    printf("Cliente atualizado.\n");
}

void delete_client() {
    int id;
    list_clients();
    printf("ID do cliente a excluir: ");
    scanf("%d", &id);
    int idx = find_client_index_by_id(id);
    if (idx == -1) { printf("Cliente não encontrado.\n"); return; }
    for (int j = idx; j < clients_count - 1; j++) clients[j] = clients[j+1];
    clients_count--;
    save_clients();
    log_action("Cliente excluído");
    printf("Cliente excluído.\n");
}

void add_pizza() {
    if (pizzas_count >= MAX_PIZZAS) { printf("Limite de pizzas alcançado.\n"); return; }
    Pizza p;
    p.id = next_pizza_id();
    getchar();
    printf("Sabor: ");
    fgets(p.sabor, sizeof(p.sabor), stdin); trim_nl(p.sabor);
    printf("Preço: ");
    scanf("%f", &p.preco);
    p.vendidas = 0;
    pizzas[pizzas_count++] = p;
    save_pizzas();
    log_action("Pizza cadastrada");
    printf("Pizza cadastrada com ID %d.\n", p.id);
}

void list_pizzas() {
    printf("\n--- PIZZAS ---\n \n1-Clabresa \n2-Mussarela \n3-Portuguesa \n4-Frango com Catupiry");
    for (int i = 0; i < pizzas_count; i++)
        printf("ID:%d | %s | R$ %.2f | Vendidas: %d\n", pizzas[i].id, pizzas[i].sabor, pizzas[i].preco, pizzas[i].vendidas);
}

int find_pizza_index_by_id(int id) {
    for (int i = 0; i < pizzas_count; i++) if (pizzas[i].id == id) return i;
    return -1;
}

void update_pizza() {
    int id;
    list_pizzas();
    printf("ID da pizza a alterar: ");
    scanf("%d", &id);
    int idx = find_pizza_index_by_id(id);
    if (idx == -1) { printf("Pizza não encontrada.\n"); return; }
    getchar();
    char tmp[60];
    printf("Novo sabor (ENTER para manter: %s): ", pizzas[idx].sabor);
    fgets(tmp, sizeof(tmp), stdin); trim_nl(tmp);
    if (strlen(tmp)) strcpy(pizzas[idx].sabor, tmp);
    printf("Novo preço (ENTER para manter: %.2f): ", pizzas[idx].preco);
    fgets(tmp, sizeof(tmp), stdin); trim_nl(tmp);
    if (strlen(tmp)) pizzas[idx].preco = atof(tmp);
    save_pizzas();
    log_action("Pizza alterada");
    printf("Pizza atualizada.\n");
}

void delete_pizza() {
    int id;
    list_pizzas();
    printf("ID da pizza a excluir: ");
    scanf("%d", &id);
    int idx = find_pizza_index_by_id(id);
    if (idx == -1) { printf("Pizza não encontrada.\n"); return; }
    for (int j = idx; j < pizzas_count - 1; j++) pizzas[j] = pizzas[j+1];
    pizzas_count--;
    save_pizzas();
    log_action("Pizza excluída");
    printf("Pizza excluída.\n");
}

void place_order() {
    if (clients_count == 0 || pizzas_count == 0) { printf("Cadastre cliente e pizza antes.\n"); return; }
    Order o;
    o.id = next_order_id();
    list_clients();
    printf("ID do cliente (ou 0 para cadastrar novo): ");
    scanf("%d", &o.client_id);
    if (o.client_id == 0) { getchar(); add_client(); o.client_id = clients[clients_count-1].id; }
    list_pizzas();
    printf("ID da pizza: ");
    scanf("%d", &o.pizza_id);
    printf("Quantidade: ");
    scanf("%d", &o.quantidade);
    getchar();
    printf("Forma de pagamento (dinheiro/cartao/pix): ");
    fgets(o.pagamento, sizeof(o.pagamento), stdin); trim_nl(o.pagamento);
    int pidx = find_pizza_index_by_id(o.pizza_id);
    if (pidx == -1) { printf("Pizza inválida.\n"); return; }
    o.total = pizzas[pidx].preco * o.quantidade;
    o.timestamp = (long)time(NULL);
    orders[orders_count++] = o;
    pizzas[pidx].vendidas += o.quantidade;
    save_orders();
    save_pizzas();
    char msg[120];
    sprintf(msg, "Pedido %d: cliente %d pizza %d qtd %d total %.2f", o.id, o.client_id, o.pizza_id, o.quantidade, o.total);
    log_action(msg);
    printf("Pedido registrado. Total: R$ %.2f\n", o.total);
}

void report_cash_by_payment() {
    double dinheiro = 0, cartao = 0, pix = 0, outros = 0;
    for (int i = 0; i < orders_count; i++) {
        char *p = orders[i].pagamento;
        if (strstr(p, "dinheiro") || strstr(p, "Dinheiro")) dinheiro += orders[i].total;
        else if (strstr(p, "cart") || strstr(p, "Cart")) cartao += orders[i].total;
        else if (strstr(p, "pix") || strstr(p, "PIX") || strstr(p, "Pix")) pix += orders[i].total;
        else outros += orders[i].total;
    }
    printf("\n--- CAIXA POR FORMA DE PAGAMENTO ---\n");
    printf("Dinheiro: R$ %.2f\n", dinheiro);
    printf("Cartão:   R$ %.2f\n", cartao);
    printf("Pix:      R$ %.2f\n", pix);
    printf("Outros:   R$ %.2f\n", outros);
}


void report_most_sold_pizzas() {
    printf("\n--- PIZZAS MAIS VENDIDAS ---\n");
    for (int i = 0; i < pizzas_count; i++)
        printf("%s - %d vendidas\n", pizzas[i].sabor, pizzas[i].vendidas);
}

double revenue_between(long start_ts, long end_ts) {
    double total = 0;
    for (int i = 0; i < orders_count; i++)
        if (orders[i].timestamp >= start_ts && orders[i].timestamp <= end_ts) total += orders[i].total;
    return total;
}

void report_revenue_periods() {
    time_t now = time(NULL);
    long now_ts = (long)now;
    long day = now_ts - 24L*3600L;
    long week = now_ts - 7L*24L*3600L;
    long month = now_ts - 30L*24L*3600L;
    double rday = revenue_between(day, now_ts);
    double rweek = revenue_between(week, now_ts);
    double rmonth = revenue_between(month, now_ts);
    printf("\n--- FATURAMENTO ---\n");
    printf("Últimas 24h: R$ %.2f\n", rday);
    printf("Últimos 7 dias: R$ %.2f\n", rweek);
    printf("Últimos 30 dias: R$ %.2f\n", rmonth);
}

void report_orders_by_client() {
    int id;
    list_clients();
    printf("ID do cliente para relatório: ");
    scanf("%d", &id);
    printf("\n--- PEDIDOS DO CLIENTE ID %d ---\n", id);
    for (int i = 0; i < orders_count; i++) {
        if (orders[i].client_id == id) {
            int pidx = find_pizza_index_by_id(orders[i].pizza_id);
            const char *sabor = (pidx == -1) ? "ND" : pizzas[pidx].sabor;
            struct tm tm = *localtime((time_t*)&orders[i].timestamp);
            char timestr[32]; strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M", &tm);
            printf("Pedido %d | Pizza: %s | Qtd: %d | Total: R$ %.2f | Pag: %s | %s\n",
                   orders[i].id, sabor, orders[i].quantidade, orders[i].total, orders[i].pagamento, timestr);
        }
    }
}

void register_user() {
    if (users_count >= MAX_USERS) { printf("Limite de usuários.\n"); return; }
    User u;
    getchar();
    printf("Usuario (sem espaços): ");
    fgets(u.username, sizeof(u.username), stdin); trim_nl(u.username);
    printf("Senha: ");
    fgets(u.password, sizeof(u.password), stdin); trim_nl(u.password);
    do {
        printf("Tipo (gerente/atendente): ");
        fgets(u.role, sizeof(u.role), stdin); trim_nl(u.role);
        if (strcmp(u.role, "gerente") != 0 && strcmp(u.role, "atendente") != 0)
            printf("Tipo inválido. Digite 'gerente' ou 'atendente'.\n");
        else break;
    } while (1);
    users[users_count++] = u;
    save_users();
    log_action("Usuário cadastrado");
    printf("Usuário criado: %s (%s)\n", u.username, u.role);
}

int login(char *out_role) {
    char user[40], pass[40];
    printf("Usuário: ");
    scanf(" %39[^\n]", user);
    printf("Senha: ");
    scanf(" %39[^\n]", pass);
    for (int i = 0; i < users_count; i++) {
        if (strcmp(users[i].username, user) == 0 && strcmp(users[i].password, pass) == 0) {
            strcpy(out_role, users[i].role);
            char msg[100]; sprintf(msg, "Login: %s (%s)", users[i].username, users[i].role);
            log_action(msg);
            return 1;
        }
    }
    printf("Credenciais inválidas.\n");
    return 0;
}

void menu_manager() {
    int op;
    do {
        printf("\n--- MENU GERENTE ---\n");
        printf("1) Cadastrar Cliente\n2) Alterar Cliente\n3) Excluir Cliente\n4) Listar Clientes\n");
        printf("5) Cadastrar Pizza\n6) Alterar Pizza\n7) Excluir Pizza\n8) Listar Pizzas\n");
        printf("9) Fazer Pedido\n10) Caixa por forma de pagamento\n11) Pizzas mais vendidas\n12) Faturamento (dia/sem/mês)\n13) Pedidos por cliente\n14) Cadastrar Usuário\n0) Logout\nOpção: ");
        scanf("%d", &op); getchar();
        switch (op) {
            case 1: add_client(); break;
            case 2: update_client(); break;
            case 3: delete_client(); break;
            case 4: list_clients(); pause_console(); break;
            case 5: add_pizza(); break;
            case 6: update_pizza(); break;
            case 7: delete_pizza(); break;
            case 8: list_pizzas(); pause_console(); break;
            case 9: place_order(); break;
            case 10: report_cash_by_payment(); pause_console(); break;
            case 11: report_most_sold_pizzas(); pause_console(); break;
            case 12: report_revenue_periods(); pause_console(); break;
            case 13: report_orders_by_client(); pause_console(); break;
            case 14: register_user(); break;
            case 0: printf("Logout gerenciado.\n"); break;
            default: printf("Opção inválida.\n"); break;
        }
    } while (op != 0);
}

void menu_attendant() {
    int op;
    do {
        printf("\n--- MENU ATENDENTE ---\n");
        printf("1) Cadastrar Cliente\n2) Alterar Cliente\n3) Listar Clientes\n4) Listar Pizzas\n5) Fazer Pedido\n0) Logout\nOpção: ");
        scanf("%d", &op); getchar();
        switch (op) {
            case 1: add_client(); break;
            case 2: update_client(); break;
            case 3: list_clients(); pause_console(); break;
            case 4: list_pizzas(); pause_console(); break;
            case 5: place_order(); break;
            case 0: printf("Logout atendente.\n"); break;
            default: printf("Opção inválida.\n"); break;
        }
    } while (op != 0);
}

int main() {
    load_users();
    load_clients();
    load_pizzas();
    load_orders();

    printf("BEM-VINDO(A) AO SISTEMA PIZZAFONY\n");
    printf("Suporte: (82) 99973-7470 | pizzafonysuporte@gmail.com\n");

    int has_manager = 0;
    for (int i=0;i<users_count;i++) if (strcmp(users[i].role, "gerente") == 0) has_manager = 1;
    if (!has_manager) {
        printf("Nenhum gerente encontrado. Crie um gerente agora:\n");
        register_user();
    }

    char role[20] = "";
    int auth = 0;
    int attempts = 0;
    while (!auth && attempts < 3) {
        printf("\n1-Cadastrar usuário  \n2-Login \n0-Sair \nOpção: ");
        int op; scanf("%d", &op); getchar();
        if (op == 1) register_user();
        else if (op == 2) {
            if (login(role)) { auth = 1; break; }
            else attempts++;
        } else if (op == 0) { printf("Saindo...\n"); return 0; }
    }
    if (!auth) { printf("Falha no login. Encerrando.\n"); return 0; }

    if (strcmp(role, "gerente") == 0) menu_manager();
    else menu_attendant();

    save_users(); save_clients(); save_pizzas(); save_orders();
    log_action("Sistema encerrado");
    printf("Obrigado por usar Pizzafony!\n");
    return 0;
}
