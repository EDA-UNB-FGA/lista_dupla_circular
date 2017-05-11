#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int menu = -1;

    do {
        printf("\n1- Registrar\n2- Remover\n3- Mostrar lista\n");
        printf("4- Mostrar maior e menor imc\n5- Finalizar\nOpção: ");
        scanf("%d", &menu);

        switch(menu) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                printf("\nOpção inválida.\n");
                break;
        } 
    } while(menu != 5);

    return 0;
}