#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// --- ESTRUCTURAS ---

struct Jugador {
    char nombreDelJUgador[60];
    int edadDelJugador;
    char rolDelJugador[60];
};

typedef struct {
    char textoPregunta[300];    
    int respuestaCorrecta;      
    char retroalimentacion[200]; 
} Pregunta;

// --- PROTOTIPOS DE FUNCIONES ---
void registroPrincipalDelJugador(struct Jugador *j);
// (Se eliminó el prototipo de mostrarEstadoDelNucleo)
int procesarRespuesta(int respuestaUsuario, int respuestaCorrecta, int *llaves, int *vidas);
void limpiarBuffer();
void mostrarInterfazDeJuego(int vidas, int llaves, int numeroPregunta);
void mostrarGameOver(); 
void mostrarWin();   // Nombre cambiado para reflejar que solo dice WIN

// --- FUNCIÓN DE REGISTRO ---
void registroPrincipalDelJugador(struct Jugador *j){
    int opcionRol;

    printf("==----- REGISTRO DEL AVENTURERO -----==\n");

    printf("Introduce tu nombre: ");
    scanf(" %[^\n]", j->nombreDelJUgador); 
    limpiarBuffer();

    do {
        printf("Introduce tu edad: ");
        scanf("%d", &j->edadDelJugador);
        limpiarBuffer();
        
        if (j->edadDelJugador <= 0) {
            printf(">> Error: EDAD NO VALIDA -- Ingrese nuevamente su edad.\n");
        }
    } while (j->edadDelJugador <= 0);

    printf("\nSelecciona tu rol en el circuito:\n");
    printf("1. Mago de circuitos\n");
    printf("2. Espadachin de la resistencia\n");
    printf("3. Arquero del voltaje\n");
    printf("Opcion: ");
    scanf("%d", &opcionRol);
    limpiarBuffer();

    switch(opcionRol) {
        case 1:
            printf("El rol que has elegido es: Mago de circuitos\n");
            strcpy(j->rolDelJugador, "Mago de circuitos");
            break;
        case 2:
            printf("El rol que has elegido es: Espadachin de la resistencia\n");
            strcpy(j->rolDelJugador, "Espadachin de la resistencia");
            break;
        case 3:
            printf("El rol que has elegido es: Arquero del voltaje\n");  
            strcpy(j->rolDelJugador, "Arquero del voltaje");
            break;
        default:
            strcpy(j->rolDelJugador, "Novato del Cableado");
            break;
    }
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// (Se eliminó la función mostrarEstadoDelNucleo para quitar la interfaz de capas)

void mostrarInterfazDeJuego(int vidas, int llaves, int numeroPregunta) {
    printf("\n=======================================================\n");
    if (numeroPregunta <= 10) {
        printf(" TABLERO DE CONTROL - PREGUNTA #%d\n", numeroPregunta);
    } else {
        printf(" TABLERO DE CONTROL - FINAL\n");
    }
    printf("=======================================================\n");

    printf(" ESTADO DEL AVENTURERO (Vidas): ");
    for (int i = 0; i < 5; i++) {
        if (i < vidas) {
            printf("[■] "); 
        } else {
            printf("[ ] "); 
        }
    }
    printf("(%d/5)\n", vidas);

    printf(" INVENTARIO (Llaves):      ");
    if (llaves == 0) {
        printf("[Vacio]");
    } else {
        for (int i = 0; i < llaves; i++) {
            printf(" ((0)=====¶) ");
        }
    }
    printf("\n=======================================================\n");
}

// --- PANTALLAS DE FINAL DE JUEGO (ASCII ART MODIFICADO) ---
void mostrarGameOver() {
    printf("\n\n");
    // Mensaje GAME OVER legible hecho con puntos
    printf("  ....     .       .   .    .....       ...    .       .    .....   ....   \n");
    printf(" .        . .      .. ..    .          .   .    .     .     .       .   .  \n");
    printf(" .  ..   .....     . . .    .....      .   .    .     .     .....   ....   \n");
    printf(" .   .   .   .     .   .    .          .   .     .   .      .       . .    \n");
    printf("  ....   .   .     .   .    .....       ...       ...       .....   .  .   \n");
    printf("\n\n");
}

void mostrarWin() {
    printf("\n\n");
    // Mensaje WIN legible hecho con puntos
    printf(" .         .   .....   .    . \n");
    printf(" .    .    .     .     ..   . \n");
    printf(" .   . .   .     .     . .  . \n");
    printf("  . .   . .      .     .  . . \n");
    printf("   .     .     .....   .    . \n");
    printf("\n\n");
}

int procesarRespuesta(int respuestaUsuario, int respuestaCorrecta, int *llaves, int *vidas) {
    if (respuestaUsuario == respuestaCorrecta) {
        printf("\n>> CORRECTO! Has obtenido una llave.\n");
        (*llaves)++; 
        return 1; 
    } else {
        printf("\n>> INCORRECTO. Estas perdiendo energia.\n");
        (*vidas)--; 
        return 0; 
    }
}

int main() {
    system("chcp 65001"); 
    struct Jugador usuario;
    int opcionReiniciar = 0;

    printf("-------------------------------------------------------------------------\n");
    printf(" .---. .      .---. .---. .---. .---. .---.      .---. .---. .---. .---. \n");
    printf(" |   | |      |   | |       |   |   | |   |  -   | | | |   |     /  |      \n");
    printf(" |---  |      |---  |       |   |---' |   |      | | | |---|    /   |---  \n");
    printf(" |   | |      |   | |       |   |   \\ |   |      |   | |   |  /     |      \n");
    printf(" '---' '---'  '---' '---'   '   '    ' '---'      '   ' '   ' '---' '---' \n");
    printf("-------------------------------------------------------------------------\n");

    registroPrincipalDelJugador(&usuario);

    // --- INICIALIZACIÓN DEL BANCO DE PREGUNTAS ---
    Pregunta bancoPreguntas[10] = {
        {"1. ¿Cual es la unidad de resistencia electrica?\n   1) Ohm\n   2) Voltio\n   3) Amperio", 1, "RETROALIMENTACION: El Ohm es la unidad oficial del SI para medir resistencia."},
        {"2. ¿Que ley establece que V = I * R?\n   1) Ley de Watt\n   2) Ley de Ohm\n   3) Ley de Kirchhoff", 2, "RETROALIMENTACION: La Ley de Ohm relaciona voltaje, corriente y resistencia."},
        {"3. ¿Que componente almacena energia en un campo electrico?\n   1) Capacitor\n   2) Resistencia\n   3) Inductor", 1, "RETROALIMENTACION: Los capacitores almacenan carga en sus placas internas."},
        {"4. ¿Cual es la frecuencia estandar de la corriente alterna en Ecuador?\n   1) 50Hz\n   2) 100Hz\n   3) 60Hz", 3, "RETROALIMENTACION: En Ecuador y gran parte de America se usa 60Hz."},
        {"5. ¿Que instrumento se usa para medir la corriente?\n   1) Voltimetro\n   2) Amperimetro\n   3) Ohmetro", 2, "RETROALIMENTACION: El Amperimetro se conecta en serie para medir corriente."},
        {"6. En un circuito en serie, ¿que magnitud permanece constante?\n   1) La Corriente\n   2) El Voltaje\n   3) La Potencia", 1, "RETROALIMENTACION: En serie, la corriente solo tiene un camino, por eso es constante."},
        {"7. ¿Cual es el simbolo quimico de un material conductor como el Cobre?\n   1) Co\n   2) Au\n   3) Cu", 3, "RETROALIMENTACION: Cu proviene del latin Cuprum (Cobre)."},
        {"8. ¿Que hace un diodo?\n   1) Amplifica la señal\n   2) Permite el paso de corriente en un solo sentido\n   3) Genera luz siempre", 2, "RETROALIMENTACION: El diodo actua como una valvula check electronica."},
        {"9. ¿Cual es la formula de la Potencia Electrica?\n   1) P = V * I\n   2) P = V / R\n   3) P = I * R", 1, "RETROALIMENTACION: Potencia (Watts) es igual a Voltaje por Corriente."},
        {"10. ¿Que significa LED?\n   1) Low Energy Diode\n   2) Light Emitting Diode\n   3) Large Electronic Device", 2, "RETROALIMENTACION: Significa Diodo Emisor de Luz (Light Emitting Diode)."}
    };

    printf("\n-------------------------------------------\n");
    printf("Bienvenido, %s (%s). Prepárate.\n", usuario.nombreDelJUgador, usuario.rolDelJugador);
    printf("Objetivo: Consigue 10 LLAVES respondiendo correctamente las preguntas.\n");
    printf("Peligro: Si fallas 5 veces, PIERDES.\n");
    printf("-------------------------------------------\n");

    do {
        int llaves = 0;
        int vidas = 5;
        int respuesta = 0;
        int victoria = 0;

        // Aunque eliminamos la visualización, mantenemos la variable si el código interno la necesitara, 
        // pero eliminamos el bucle de visualización.
        int nucleoEnergia[2][2][2] = {
            { {0, 0}, {0, 0} }, 
            { {0, 0}, {0, 0} }
        };

        printf("\n>>> INICIANDO SISTEMA DE PRUEBAS <<<\n");
        getchar(); 

        for (int i = 0; i < 10; i++) {
            
            if (vidas <= 0) {
                break; 
            }

            mostrarInterfazDeJuego(vidas, llaves, i + 1);

            printf("%s\n", bancoPreguntas[i].textoPregunta); 
            printf("Tu respuesta: ");
            scanf("%d", &respuesta);
            limpiarBuffer();

            int exito = procesarRespuesta(respuesta, bancoPreguntas[i].respuestaCorrecta, &llaves, &vidas);

            printf("-------------------------------------------------------\n");
            printf("%s\n", bancoPreguntas[i].retroalimentacion);
            printf("-------------------------------------------------------\n");
            printf("Presiona ENTER para continuar...");
            getchar(); 

            if (exito) {
                int capa = (i / 4) % 2; 
                int fila = (i / 2) % 2;
                int col = i % 2;
                nucleoEnergia[capa][fila][col] = 1; 
            }

            // SE ELIMINÓ LA LLAMADA A mostrarEstadoDelNucleo AQUÍ
        }

        // --- CONDICIONALES DE FINAL DE JUEGO ---
        if (llaves >= 7) {
            mostrarWin(); // Muestra solo WIN con puntos
            printf("\n*****************\n");
            printf(" ¡FELICIDADES %s! HAS GANADO EL JUEGO.\n", usuario.nombreDelJUgador);
            printf(" Has reparado el núcleo de energía al 100%%.\n");
            printf("*****************\n");
            victoria = 1;
        } else {
            mostrarGameOver(); // Muestra GAME OVER legible
            printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
            printf(" GAME OVER. Te has quedado sin vidas .\n");
            
            printf(" Estado final:\n");
            mostrarInterfazDeJuego(vidas, llaves, 11); 

            printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        }

        printf("\n¿Deseas volver a intentar salvar el circuito? (1 = Si, 0 = No): ");
        scanf("%d", &opcionReiniciar);
        limpiarBuffer();

        if (opcionReiniciar == 1) {
            printf("\nReinicando sistemas...\n\n");
        }

    } while (opcionReiniciar == 1);

    printf("\nGracias por jugar. Programa finalizado.\n");

    return 0;
}
