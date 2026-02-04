#include <stdio.h>  // Biblioteca estándar para entrada y salida (printf, scanf)
#include <string.h> // Biblioteca para manipulación de cadenas (strcpy)
#include <stdlib.h> // Biblioteca para gestión de memoria y utilidades del sistema (system)

// --- ESTRUCTURAS ---

// Estructura 'Jugador': Define un tipo de dato compuesto para agrupar
// toda la información relacionada con el usuario.
struct Jugador {
    char nombreDelJUgador[60]; // Array de caracteres para el nombre
    int edadDelJugador;        // Entero para la edad
    char rolDelJugador[60];    // Almacenará el título del rol (Mago, Espadachin, etc.)
};

// Estructura 'Pregunta': Se usa 'typedef' para poder referirnos a ella simplemente como 'Pregunta'
// sin escribir 'struct Pregunta' cada vez. Sirve para crear el banco de datos del quiz.
typedef struct {
    char textoPregunta[300];     // El enunciado de la pregunta y las opciones
    int respuestaCorrecta;       // El número entero que representa la opción válida (1, 2 o 3)
    char retroalimentacion[200]; // Texto explicativo que aparece tras responder
} Pregunta;

// --- PROTOTIPOS DE FUNCIONES ---
// Declaramos las firmas de las funciones antes del main para que el compilador sepa que existen
// y qué tipos de datos reciben/devuelven, permitiendo organizarlas en cualquier orden.
void registroPrincipalDelJugador(struct Jugador *j);
// (Se eliminó el prototipo de mostrarEstadoDelNucleo)
int procesarRespuesta(int respuestaUsuario, int respuestaCorrecta, int *llaves, int *vidas);
void limpiarBuffer();
void mostrarInterfazDeJuego(int vidas, int llaves, int numeroPregunta);
void mostrarGameOver(); 
void mostrarWin();   // Nombre cambiado para reflejar que solo dice WIN

// --- FUNCIÓN DE REGISTRO ---
// Recibe un puntero a la estructura Jugador (*j). Esto es crucial:
// permite modificar directamente la variable 'usuario' creada en el main, no una copia.
void registroPrincipalDelJugador(struct Jugador *j){
    int opcionRol;

    printf("==----- REGISTRO DEL AVENTURERO -----==\n");

    printf("Introduce tu nombre: ");
    // " %[^\n]" es un especificador de formato avanzado:
    // El espacio inicial ignora espacios en blanco previos.
    // [^\n] lee caracteres hasta encontrar un salto de línea (permite nombres con espacios).
    scanf(" %[^\n]", j->nombreDelJUgador); 
    limpiarBuffer(); // Consumimos el '\n' que quedó en el buffer tras el scanf anterior

    // Bucle do-while para validar que la edad sea lógica (mayor que 0)
    do {
        printf("Introduce tu edad: ");
        scanf("%d", &j->edadDelJugador);
        limpiarBuffer(); // Limpieza preventiva del buffer
        
        if (j->edadDelJugador <= 0) {
            printf(">> Error: EDAD NO VALIDA -- Ingrese nuevamente su edad.\n");
        }
    } while (j->edadDelJugador <= 0);

    // Menú simple para elegir un rol temático
    printf("\nSelecciona tu rol en el circuito:\n");
    printf("1. Mago de circuitos\n");
    printf("2. Espadachin de la resistencia\n");
    printf("3. Arquero del voltaje\n");
    printf("Opcion: ");
    scanf("%d", &opcionRol);
    limpiarBuffer();

    // Estructura switch para asignar una cadena de texto al campo 'rolDelJugador'
    // dependiendo de la selección numérica.
    switch(opcionRol) {
        case 1:
            printf("El rol que has elegido es: Mago de circuitos\n");
            // strcpy copia el string literal en el array de la estructura
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
            // Opción por defecto para valores no válidos (0, 4, 5...)
            strcpy(j->rolDelJugador, "Novato del Cableado");
            break;
    }
}

// Función crítica para la estabilidad de entradas por consola.
// Lee y descarta caracteres del flujo de entrada (stdin) hasta encontrar un Enter (\n) o el fin de archivo (EOF).
// Evita que un 'Enter' presionado previamente sea interpretado como la siguiente respuesta vacía.
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// (Se eliminó la función mostrarEstadoDelNucleo para quitar la interfaz de capas)

// Función puramente visual (Interfaz de Usuario - HUD)
// Muestra el progreso actual sin modificar datos, por eso recibe las variables por valor (copias).
void mostrarInterfazDeJuego(int vidas, int llaves, int numeroPregunta) {
    printf("\n=======================================================\n");
    
    // Condicional para mostrar un encabezado diferente si el juego ha terminado (pregunta > 10)
    if (numeroPregunta <= 10) {
        printf(" TABLERO DE CONTROL - PREGUNTA #%d\n", numeroPregunta);
    } else {
        printf(" TABLERO DE CONTROL - FINAL\n");
    }
    printf("=======================================================\n");

    // Dibuja la barra de vida iterando 5 veces.
    // Si el índice 'i' es menor que las vidas actuales, dibuja un bloque lleno, si no, vacío.
    printf(" ESTADO DEL AVENTURERO (Vidas): ");
    for (int i = 0; i < 5; i++) {
        if (i < vidas) {
            printf("[■] "); 
        } else {
            printf("[ ] "); 
        }
    }
    printf("(%d/5)\n", vidas);

    // Muestra el inventario de llaves recolectadas
    printf(" INVENTARIO (Llaves):       ");
    if (llaves == 0) {
        printf("[Vacio]");
    } else {
        // Bucle para dibujar una llave ASCII por cada punto obtenido
        for (int i = 0; i < llaves; i++) {
            printf(" ((0)=====¶) ");
        }
    }
    printf("\n=======================================================\n");
}

// --- PANTALLAS DE FINAL DE JUEGO (ASCII ART MODIFICADO) ---
// Función void que imprime el arte ASCII de derrota
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

// Función void que imprime el arte ASCII de victoria
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

// Lógica central de evaluación.
// Recibe punteros (*llaves, *vidas) porque necesita MODIFICAR las variables originales declaradas en main.
// Retorna 1 si la respuesta fue correcta (para lógica interna adicional) o 0 si falló.
int procesarRespuesta(int respuestaUsuario, int respuestaCorrecta, int *llaves, int *vidas) {
    if (respuestaUsuario == respuestaCorrecta) {
        printf("\n>> CORRECTO! Has obtenido una llave.\n");
        (*llaves)++; // Incrementa el valor en la dirección de memoria apuntada
        return 1; 
    } else {
        printf("\n>> INCORRECTO. Estas perdiendo energia.\n");
        (*vidas)--; // Decrementa el valor en la dirección de memoria apuntada
        return 0; 
    }
}

int main() {
    // Configura la página de códigos de la consola a UTF-8 para mostrar tildes y caracteres especiales correctamente
    system("chcp 65001"); 
    
    // Instancia de la estructura Jugador (aquí se guardarán los datos del usuario)
    struct Jugador usuario;
    int opcionReiniciar = 0;

    // Arte ASCII decorativo de inicio
    printf("-------------------------------------------------------------------------\n");
    printf(" .---. .      .---. .---. .---. .---. .---.      .---. .---. .---. .---. \n");
    printf(" |   | |      |   | |       |   |   | |   |  -   | | | |   |     /  |      \n");
    printf(" |---  |      |---  |       |   |---' |   |      | | | |---|    /   |---  \n");
    printf(" |   | |      |   | |       |   |   \\ |   |      |   | |   |  /     |      \n");
    printf(" '---' '---'  '---' '---'   '   '    ''---'      '   ' '   ' '---' '---' \n");
    printf("-------------------------------------------------------------------------\n");
    // Llama a la función de registro pasando la DIRECCIÓN de memoria (&) de la variable usuario
    registroPrincipalDelJugador(&usuario);

    // --- INICIALIZACIÓN DEL BANCO DE PREGUNTAS ---
    // Se inicializa un array de 10 estructuras 'Pregunta' con los datos precargados.
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

    // Bucle principal del juego (Game Loop).
    // Usamos 'do-while' para garantizar que se ejecute al menos una vez y permitir el reinicio.
    do {
        // Reinicio de variables de estado para cada nueva partida
        int llaves = 0;
        int vidas = 5;
        int respuesta = 0;
        int victoria = 0; // Bandera para saber si ganó al final

        // Matriz tridimensional [2][2][2] (Cubo de 2x2x2). 
        // Aunque no se muestra visualmente en esta versión, se sigue calculando internamente
        // para representar el "núcleo de energía" reparándose.
        int nucleoEnergia[2][2][2] = {
            { {0, 0}, {0, 0} }, 
            { {0, 0}, {0, 0} }
        };

        printf("\n>>> INICIANDO SISTEMA DE PRUEBAS <<<\n");
        getchar(); // Pausa táctica esperando un Enter del usuario

        // Iteración por las 10 preguntas del banco
        for (int i = 0; i < 10; i++) {
            
            // Verificación constante de "Game Over"
            // Si las vidas llegan a 0, rompemos el bucle for inmediatamente con 'break'
            if (vidas <= 0) {
                break; 
            }

            // Mostramos el HUD actualizado
            mostrarInterfazDeJuego(vidas, llaves, i + 1);

            // Imprimimos la pregunta actual accediendo al array de estructuras
            printf("%s\n", bancoPreguntas[i].textoPregunta); 
            printf("Tu respuesta: ");
            scanf("%d", &respuesta);
            limpiarBuffer(); // Importante limpiar tras cada lectura numérica

            // Llamada a la lógica de validación. Pasamos la dirección (&) de llaves y vidas
            int exito = procesarRespuesta(respuesta, bancoPreguntas[i].respuestaCorrecta, &llaves, &vidas);

            // Muestra la retroalimentación educativa independientemente de si acertó o falló
            printf("-------------------------------------------------------\n");
            printf("%s\n", bancoPreguntas[i].retroalimentacion);
            printf("-------------------------------------------------------\n");
            printf("Presiona ENTER para continuar...");
            getchar(); 

            // Si la respuesta fue correcta (exito == 1), actualizamos el "núcleo" interno
            if (exito) {
                // Algoritmo para mapear un índice lineal 'i' (0-9) a coordenadas 3D (x,y,z)
                // Esto llena el cubo de energía de forma secuencial.
                int capa = (i / 4) % 2; 
                int fila = (i / 2) % 2;
                int col = i % 2;
                nucleoEnergia[capa][fila][col] = 1; // Marca la celda como "reparada" (1)
            }

            // SE ELIMINÓ LA LLAMADA A mostrarEstadoDelNucleo AQUÍ
        }

        // --- CONDICIONALES DE FINAL DE JUEGO ---
        // Al salir del bucle (ya sea por terminar las preguntas o por game over), evaluamos el resultado.
        if (llaves >= 7) {
            // Condición de victoria: 7 o más aciertos
            mostrarWin(); 
            printf("\n*****************\n");
            printf(" ¡FELICIDADES %s! HAS GANADO EL JUEGO.\n", usuario.nombreDelJUgador);
            printf(" Has reparado el núcleo de energía al 100%%.\n");
            printf("*****************\n");
            victoria = 1;
        } else {
            // Condición de derrota
            mostrarGameOver(); 
            printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
            printf(" GAME OVER. Te has quedado sin vidas .\n");
            
            printf(" Estado final:\n");
            mostrarInterfazDeJuego(vidas, llaves, 11); // El 11 indica al HUD que es el final

            printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        }

        // Pregunta para reiniciar el ciclo do-while
        printf("\n¿Deseas volver a intentar salvar el circuito? (1 = Si, 0 = No): ");
        scanf("%d", &opcionReiniciar);
        limpiarBuffer();

        if (opcionReiniciar == 1) {
            printf("\nReinicando sistemas...\n\n");
        }

    } while (opcionReiniciar == 1); // Si el usuario ingresa 1, el bucle se repite

    printf("\nGracias por jugar. Programa finalizado.\n");

    return 0; // Retorno estándar de éxito al sistema operativo
}
