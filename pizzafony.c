#include <stdio.h>
#include <string.h>
#include "user.h"
#include "structs.h"
#include "dados.h"
#include "menu.h"

int main() {

   /* int pos = login();

    if (pos != -1) {

        if (strcmp(users[pos].role, "gerente") == 0) {
            menuGerente(pos);
        }
        else if (strcmp(users[pos].role, "atendente") == 0) {
            menuAtendente(pos);
        }
    }*/

    // powershell:   
    //    gcc pizzafony.c dados.c user.c menu.c pizza.c pedidos.c -o pizzafony
    //   ./pizzafony

    menuInicial();

    return 0;
}

