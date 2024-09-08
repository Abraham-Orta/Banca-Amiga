/*La oficina principal de Bancamiga en la ciudad de Puerto Ordaz, desea automatizar
todas sus operaciones bancarias. Por tal razón desea contratar sus servicios, con la finalidad
de que Ud., genere la solución en Lenguaje C utilizando Funciones, que permitan manejar
de una manera fácil y eficiente todas las operaciones considerando los siguientes
requerimientos: Para cada uno de los clientes se deberá conocer la siguiente información:
Número de la Cuenta, Tipo de Cuenta, Nombre, Dirección, Teléfono, Saldo en la Cuenta,
Cedula de Identidad, etc. Los saldos en la cuenta deben generarse en forma aleatoria. El
banco maneja básicamente tres (3) tipos de cuentas generados en forma aleatoria: cuentas
de ahorro, corrientes y de activos líquidos; cada una descuenta al cliente una tasa por el
monto de transacción realizada: Ahorro: 1%; Corriente: 2%; Activos líquidos: 3%. Deberá
existir un registro de todas las transacciones realizadas por el Banco: Código de la
Transacción, Fecha de la misma, Número de Cuenta Involucrada, Monto en Bolívares, hora
de la transacción.

Con el modelo diseñado, programe lo siguiente: Valor: 5 puntos c/u

a. Mostrar todos los clientes con Cuenta Corriente, ordenados alfabéticamente
por nombre en orden decreciente.

b. Mostrar el total de transacciones que involucraron a la cuenta de corriente
010101754 desde el día 15-01-2024 al 31-07-2024.

c. Mostrar el total de cuentas existentes en el banco, por tipo.

d. Calcular el saldo total en Bs., de todas las transacciones realizadas en el banco.

e. Calcular el monto total de las tasas desconta das por tipo de cuenta */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_TRANSACCIONES 1000

typedef enum {
    AHORRO,
    CORRIENTE,
    ACTIVOS_LIQUIDOS
} TipoCuenta;

typedef struct {
    int numeroCuenta;
    TipoCuenta tipoCuenta;
    char nombre[50];
    char direccion[100];
    char telefono[20];
    double saldo;
    char cedulaIdentidad[20];
} Cliente;

typedef struct {
    int codigoTransaccion;
    char fecha[20];
    int numeroCuenta;
    double monto;
    char hora[20];
} Transaccion;

Cliente clientes[MAX_CLIENTES];
Transaccion transacciones[MAX_TRANSACCIONES];
int numClientes = 0;
int numTransacciones = 0;


const char *nombres[] = {"Juan", "María", "Pedro", "Ana", "Luis", "Sofía", "Carlos", "Eva", "Mateo", "Isabel"};
const char *apellidos[] = {"García", "Rodríguez", "Martínez", "Hernández", "González", "López", "Díaz", "Sánchez", "Pérez", "Gómez"};


double generarAleatorio() {
    return (double)rand() / RAND_MAX;
}

// Función para generar un tipo de cuenta aleatorio
TipoCuenta generarTipoCuenta() {
    int aleatorio = (int)(generarAleatorio() * 3);
    switch (aleatorio) {
        case 0:
            return AHORRO;
        case 1:
            return CORRIENTE;
        case 2:
            return ACTIVOS_LIQUIDOS;
        default:
            return AHORRO;
    }
}

// Función para generar un saldo aleatorio
double generarSaldo() {
    return generarAleatorio() * 10000;
}

// Función para agregar un cliente
void agregarCliente() {
    Cliente cliente;
    cliente.numeroCuenta = numClientes + 1;
    cliente.tipoCuenta = generarTipoCuenta();

    // Generar nombre y apellido aleatorios
    int indiceNombre = (int)(generarAleatorio() * (sizeof(nombres) / sizeof(nombres[0])));
    int indiceApellido = (int)(generarAleatorio() * (sizeof(apellidos) / sizeof(apellidos[0])));
    sprintf(cliente.nombre, "%s %s", nombres[indiceNombre], apellidos[indiceApellido]);

    sprintf(cliente.direccion, "Dirección %d", numClientes + 1);
    sprintf(cliente.telefono, "Teléfono %d", numClientes + 1);
    cliente.saldo = generarSaldo();
    sprintf(cliente.cedulaIdentidad, "Cédula %d", numClientes + 1);
    clientes[numClientes] = cliente;
    numClientes++;
}

// Función para agregar una transacción
void agregarTransaccion() {
    Transaccion transaccion;
    transaccion.codigoTransaccion = numTransacciones + 1;
    sprintf(transaccion.fecha, "Fecha %d", numTransacciones + 1);
    transaccion.numeroCuenta = (int)(generarAleatorio() * numClientes) + 1;
    transaccion.monto = generarSaldo();
    sprintf(transaccion.hora, "Hora %d", numTransacciones + 1);
    transacciones[numTransacciones] = transaccion;
    numTransacciones++;
}

// Función de comparación para qsort
int compararNombres(const void *a, const void *b) {
    Cliente *clienteA = (Cliente *)a;
    Cliente *clienteB = (Cliente *)b;
    return strcmp(clienteA->nombre, clienteB->nombre);
}


// Función para mostrar todos los clientes con cuenta corriente
void mostrarClientesCorriente() {
    printf("Clientes con cuenta corriente:\n");

    Cliente clientesCorriente[numClientes];
    int numClientesCorriente = 0;

    for (int i = 0; i < numClientes; i++) {
        if (clientes[i].tipoCuenta == CORRIENTE) {
            clientesCorriente[numClientesCorriente++] = clientes[i];
        }
    }

    qsort(clientesCorriente, numClientesCorriente, sizeof(Cliente), compararNombres);

     for (int i = 0; i < numClientesCorriente; i++) {
        printf("%s telefeno: %s          Cedudula: %s        direccion: &s\n", clientesCorriente[i].nombre,clientesCorriente[i].telefono,clientesCorriente[i].cedulaIdentidad ,clientesCorriente[i].direccion);
    }
}


// Función para mostrar el total de transacciones que involucraron a la cuenta de corriente 010101754
void mostrarTransaccionesCorriente() {
    int totalTransacciones = 0;
    for (int i = 0; i < numTransacciones; i++) {
        if (transacciones[i].numeroCuenta == 10101754) {
            totalTransacciones++;
        }
    }
    printf("Total de transacciones que involucraron a la cuenta de corriente 010101754: %d\n\n", totalTransacciones);
}

// Función para mostrar el total de cuentas existentes en el banco por tipo
void mostrarCuentasPorTipo() {
    int totalAhorro = 0;
    int totalCorriente = 0;
    int totalActivosLiquidos = 0;
    for (int i = 0; i < numClientes; i++) {
        switch (clientes[i].tipoCuenta) {
            case AHORRO:
                totalAhorro++;
                break;
            case CORRIENTE:
                totalCorriente++;
                break;
            case ACTIVOS_LIQUIDOS:
                totalActivosLiquidos++;
                break;
        }
    }
    printf("Total de cuentas de ahorro: %d\n", totalAhorro);
    printf("Total de cuentas corrientes: %d\n", totalCorriente);
    printf("Total de cuentas de activos líquidos: %d\n", totalActivosLiquidos);
}

// Función para calcular el saldo total en Bs. de todas las transacciones realizadas en el banco
void calcularSaldoTotal() {
    double saldoTotal = 0;
    for (int i = 0; i < numTransacciones; i++) {
        saldoTotal += transacciones[i].monto;
    }
    printf("Saldo total en Bs. de todas las transacciones realizadas en el banco: %.2f\n", saldoTotal);
}

// Función para calcular el monto total de las tasas descontadas por tipo de cuenta
void calcularTasasDescontadas() {
    double tasaAhorro = 0;
    double tasaCorriente = 0;
    double tasaActivosLiquidos = 0;
    for (int i = 0; i < numTransacciones; i++) {
        switch (clientes[transacciones[i].numeroCuenta - 1].tipoCuenta) {
            case AHORRO:
                tasaAhorro += transacciones[i].monto * 0.01;
                break;
            case CORRIENTE:
                tasaCorriente += transacciones[i].monto * 0.02;
                break;
            case ACTIVOS_LIQUIDOS:
                tasaActivosLiquidos += transacciones[i].monto * 0.03;
                break;
        }
    }
    printf("Monto total de las tasas descontadas por tipo de cuenta:\n");
    printf("Ahorro: %.2f\n", tasaAhorro);
    printf("Corriente: %.2f\n", tasaCorriente);
    printf("Activos líquidos: %.2f\n", tasaActivosLiquidos);
}

void mostrarMenu() {
    printf("\nMenú de opciones:\n");
    printf("1. Mostrar todos los clientes con cuenta corriente\n");
    printf("2. Mostrar el total de transacciones que involucraron a la cuenta de corriente 010101754\n");
    printf("3. Mostrar el total de cuentas existentes en el banco por tipo\n");
    printf("4. Calcular el saldo total en Bs. de todas las transacciones realizadas en el banco\n");
    printf("5. Calcular el monto total de las tasas descontadas por tipo de cuenta\n");
    printf("6. Salir\n");
}

int main() {
    srand(time(NULL)); 

    // Agregar clientes y transacciones aleatorias
    for (int i = 0; i < 30; i++) {
        agregarCliente();
        agregarTransaccion();
    }

    int opcion;
    do {
        mostrarMenu();
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);
        printf("\n");

        switch (opcion) {
            case 1:
                mostrarClientesCorriente();
                break;
            case 2:
                mostrarTransaccionesCorriente();
                break;
            case 3:
                mostrarCuentasPorTipo();
                break;
            case 4:
                calcularSaldoTotal();
                break;
            case 5:
                calcularTasasDescontadas();
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Por favor, ingrese una opción válida.\n");
                break;
        }
    } while (opcion != 6);

    return 0;
}
