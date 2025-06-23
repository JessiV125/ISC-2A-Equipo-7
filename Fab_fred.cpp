/*
INTEGRANTES DE EQUIPO

Alinne Alejandra Diaz Lopez
Valeria Martin de Santos 
Jessica Vanessa Martinez de la Rosa
Danna Sofia Morales Esparza 
*/

#include <iostream>
#include <math.h>
#include <windows.h> // Para manejar graficos 
#include <conio.h> // Para leer teclas 
#include <time.h> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
using namespace std;

const int MAX = 100;

// Obtener manejador de consola
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

// ESTRUCTURAS
struct Usuario{
    char nombre[50];
    char contrasena[50];
    int puntajeMejor;
};

struct Celda{
    int numero;
    bool encendida;    
};

// VARIABLES GLOBALES
Celda **tablero=NULL;
int tamTablero;
int secuenciaMaxima=0; 
int puntaje=0;
bool juegoActivo=true; 

COORD posicionJugador={0,0}; 
COORD *secuencia=NULL; 
int longitudSecuencia=1; 
int pasoActual=0; 
char nombreJugadorActual[25] = ""; // CORREGIDO: Inicializar con cadena vacía

// COLORES
enum Colores{AZUL=1, VERDE, CIAN, ROJO, MAGENTA, AMARILLO, BLANCO};

// PROTOTIPOS
void mostrarTitulo();
void mostrarMensajeDespedida();
void limpiarPantalla();
void mostrarMenu();
void mostrarAyuda();
void menuCuentaYJugar();

// REGISTRO 
int iniciarSesion(Usuario usuarios[], int tope);
int realizarRegistro(Usuario usuarios[], int& tope, int maxUsuarios);
bool buscarUsuarios(Usuario[], int, const char*, const char* = nullptr);
bool cumpleRequisitosUsuario(const char*);
bool cumpleRequisitosContrasena(const char*);
int cargarUsuariosDesdeArchivo(Usuario[], int);
bool contraRepetida(const char*);

// FUNCIONES PARA JUGAR
void elegirNivel();
void jugarNiveles(int);
void crearTablero();
void inicializarTablero();
void generarSecuencia();
void mostrarSecuencia();
void dibujarTablero();
void moverJugador(int);
bool verificarSeleccion();
void eliminarTablero();
void guardarPartida();
void guardarPuntaje();
void mostrarHistorialUsuario();
void mostrarMejoresPuntajes();

int main(){
    srand(time(NULL));
    mostrarTitulo();
    
    menuCuentaYJugar();
    return 0;
}

void mostrarTitulo(){
    SetConsoleTextAttribute(hConsole, CIAN);
    cout << "\n";
    cout << "  ================================================================\n";
    cout << "                                                                  \n";
    cout << "    ######   #####   ######       ######  #####   #######  ######\n";
    cout << "    ##      ##   ##  ##   ##      ##      ##  ##  ##       ##   ##\n";
    cout << "    #####   #######  ######       #####   #####   #####    ##   ##\n";
    cout << "    ##      ##   ##  ##   ##      ##      ##  ##  ##       ##   ##\n";
    cout << "    ##      ##   ##  ######       ##      ##  ##  #######  ######\n";
    cout << "                                                                  \n";
    
    SetConsoleTextAttribute(hConsole, VERDE);
    cout << "                    << JUEGO DE MEMORIA >>                       \n";
    
    SetConsoleTextAttribute(hConsole, CIAN);
    cout << "                                                                  \n";
    cout << "  ================================================================\n";
    cout << "\n";
    
    SetConsoleTextAttribute(hConsole, AMARILLO);
    cout << "                    BIENVENIDO AL DESAFIO!\n";
    cout << "\n";
    
    SetConsoleTextAttribute(hConsole, BLANCO);
    cout << "  Prepara tu mente para el mayor reto de memoria y concentracion.\n";
    cout << "  Podras seguir la secuencia hasta el final?\n";
    cout << "\n";
    
    SetConsoleTextAttribute(hConsole, BLANCO);
    cout << "\n";
    cout << "  >> CONSEJOS:\n";
    cout << "     * Concentrate al maximo\n";
    cout << "     * Toma tu tiempo para recordar\n";
    cout << "     * La practica hace al maestro\n";
    cout << "     * Manten la calma bajo presion!\n";
    cout << "\n";
    
    SetConsoleTextAttribute(hConsole, AMARILLO);
    cout << "  ================================================================\n";
    cout << "           Que comience el entrenamiento mental!\n";
    cout << "  ================================================================\n";
    cout << "\n";
    
    SetConsoleTextAttribute(hConsole, BLANCO);
    cout << "  Presiona cualquier tecla para comenzar el desafio...";
    cin.get(); 
    system("cls"); 
}

void mostrarMenu(){
    int opc;   
    float opcion;  
    do{ 
        SetConsoleTextAttribute(hConsole, VERDE); 
        opc = 0; 
        cout << "\n   === MENU DEL JUEGO ===" << endl; 
        cout << "\nJugar.........................1";     
        cout << "\nVer mejores puntajes..........2"; 
        cout << "\nCargar partida................3"; 
        cout << "\nVer historial.................4"; 
        cout << "\nAyuda.........................5"; 
        cout << "\nCerrar sesion.................6"; 
        cout << "\nOpcion: "; 
        cin >> opcion; 
        SetConsoleTextAttribute(hConsole, BLANCO); 
         
        if(cin.fail()){ 
            cin.clear(); 
            cin.ignore(1000,'\n'); 
        } 
        else if (fmod(opcion,1)==0) opc = static_cast <int> (opcion); 
         
        switch (opc) { 
            case 1: system("cls"); 
                    elegirNivel();
                    break; 
            case 2: system("cls"); 
                    mostrarMejoresPuntajes();  
                    break;
            case 3: system("cls"); 
                    cout << "Funcion en desarrollo\n";
                    system("pause");
                    break; 
            case 4: system("cls"); 
                    mostrarHistorialUsuario(); 
                    break; 
            case 5: mostrarAyuda(); 
                    break; 
            case 6: system("cls");
                    mostrarMensajeDespedida();
                    Sleep(1000);
                    return; // CORREGIDO: usar return en lugar de break
            default: cout << "Opcion invalida"; 
                    Sleep(1500); 
                    system("cls"); 
        } 
    }while(opc != 6);   
}

void menuCuentaYJugar() {
    Usuario usuarios[MAX];
    int cantidadUsuarios = cargarUsuariosDesdeArchivo(usuarios, MAX);
    int opcionCuenta;
    
    while(true) { // CORREGIDO: Bucle hasta que se complete correctamente
        cout << "\n=====================================\n";
        cout << "        ¡Bienvenido a Jugar!\n";
        cout << "=====================================\n";
        cout << " Ya tienes una cuenta?\n";
        cout << "  1) Si, quiero iniciar sesion\n";
        cout << "  2) No, quiero crear una cuenta\n";
        cout << "  3) Salir\n"; // AGREGADO: Opción para salir
        cout << "-------------------------------------\n";
        cout << "Selecciona una opcion: ";
        cin >> opcionCuenta;

        // CORREGIDO: Validación de entrada
        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida. Intenta de nuevo.\n";
            system("pause");
            system("cls");
            continue;
        }

        if (opcionCuenta == 1) {
            if (iniciarSesion(usuarios, cantidadUsuarios)) {
                cout << "\nInicio de sesion exitoso! Comenzando el juego...\n";
                system("pause");
                system("cls");
                mostrarMenu();
                break;
            } else {
                cout << "\nError al iniciar sesion. Por favor, intenta de nuevo.\n";
                system("pause");
                system("cls");
            }
        } else if (opcionCuenta == 2) {
            if (realizarRegistro(usuarios, cantidadUsuarios, MAX)) {
                cout << "\nCuenta creada exitosamente! Comenzando el juego...\n";
                system("pause");
                system("cls");
                mostrarMenu();
                break;
            } else {
                cout << "\nError al crear la cuenta. Por favor, intenta de nuevo.\n";
                system("pause");
                system("cls");
            }
        } else if (opcionCuenta == 3) {
            cout << "\nGracias por usar Fabuloso Fred!\n";
            system("pause");
            break;
        } else {
            cout << "\nOpcion no valida. Intenta de nuevo.\n";
            system("pause");
            system("cls");
        }
    }
}

void mostrarAyuda(){
    system("cls");
    SetConsoleTextAttribute(hConsole, AMARILLO);
    cout << "\n\t\t=== AYUDA - COMO JUGAR FABULOSO FRED ===" << endl;
    SetConsoleTextAttribute(hConsole, BLANCO);
    cout << "\nOBJETIVO:" << endl;
    cout << "Memoriza y replica la secuencia de colores que se muestra en el tablero." << endl;
    cout << "La secuencia crece: cada ronda agrega una nueva casilla al final." << endl;
    
    cout << "\nCONTROLES:" << endl;
    cout << "- Usa las flechas del teclado para moverte por el tablero" << endl;
    cout << "- Presiona ENTER para seleccionar una casilla" << endl;
    cout << "- La 'X' marca tu posicion actual" << endl;
    
    cout << "\nNIVELES:" << endl;
    cout << "- Nivel 1: Tablero 3x3, hasta 10 secuencias" << endl;
    cout << "- Nivel 2: Tablero 5x5, hasta 15 secuencias" << endl;
    cout << "- Nivel 3: Tablero 7x7, hasta 20 secuencias" << endl;
    
    cout << "\nPUNTUACION:" << endl;
    cout << "- Ganas puntos por cada secuencia completada correctamente" << endl;
    cout << "- Cada secuencia vale: longitud x 10 puntos" << endl;
    
    cout << "\nFUNCIONES ESPECIALES:" << endl;
    cout << "- Guarda tu partida para continuar despues" << endl;
    cout << "- Ve tu ranking de mejores puntajes" << endl;
    cout << "- Las partidas guardadas estan protegidas con contrasena" << endl;
    
    limpiarPantalla();
}

void limpiarPantalla(){
    system("pause"); 
    system("cls"); 
}

int iniciarSesion(Usuario usuarios[], int tope) {
    char nombre[50];
    char contrasena[50];
    char opcion;

    while (true) {
        cout << "\nNombre de usuario: ";
        cin >> nombre;
        cout << "Contrasena: ";
        cin >> contrasena;

        if (buscarUsuarios(usuarios, tope, nombre, contrasena)) {   
            cout << "Inicio de sesion exitoso.\n";
            strcpy(nombreJugadorActual, nombre);
            return 1;
        }
        else {
            cout << "Nombre o contrasena incorrectos.\n";
            cout << "1. Intentar de nuevo\n";
            cout << "2. Registrar nuevo usuario\n";
            cout << "3. Salir al menu principal\n";
            cout << "Opcion: ";
            cin >> opcion;

            if (opcion == '1') {
                continue;
            } else if (opcion == '2') {
                return realizarRegistro(usuarios, tope, MAX);
            } else {
                return 0;
            }
        }
    }
}

bool cumpleRequisitosUsuario(const char* nombre) {  
    return strlen(nombre) >= 3;     
}

bool cumpleRequisitosContrasena(const char* contra) {
    if (strlen(contra) < 6) return false;       

    bool mayus = false, minus = false, numero = false;
    for (int i = 0; contra[i]; i++) {
        if (isupper(contra[i])) mayus = true;   
        if (islower(contra[i])) minus = true;   
        if (isdigit(contra[i])) numero = true;  
    }
    return mayus && minus && numero;    
}

bool buscarUsuarios(Usuario usuarios[], int tope, const char nombre[], const char* contrasena) {
    for (int i = 0; i < tope; i++) {    
        if (strcmp(usuarios[i].nombre, nombre) == 0) {  
            if (contrasena == nullptr || strcmp(usuarios[i].contrasena, contrasena) == 0) { 
                return true;
            }
        }
    }
    return false;
}

int cargarUsuariosDesdeArchivo(Usuario usuarios[], int maxUsuarios) {
    FILE* archivo = fopen("usuarios.txt", "r");
    if (!archivo) return 0;

    int i = 0;
    while (fscanf(archivo, "%49s %49s %d", usuarios[i].nombre, usuarios[i].contrasena, &usuarios[i].puntajeMejor) == 3 && i < maxUsuarios) {    // CORREGIDO: Límite de caracteres y verificación de retorno
        i++;
    }
    fclose(archivo);
    return i;
}

int realizarRegistro(Usuario usuarios[], int& tope, int maxUsuarios) { // CORREGIDO: Usar parámetro maxUsuarios
    char nombre[50], contrasena[50];

    while (true) {
        cout << "\nNombre de usuario (minimo 3 letras): ";
        cin >> nombre;
        cout << "Contrasena  (minimo 6 caracteres, 1 mayuscula, 1 minuscula, 1 numero): ";
        cin >> contrasena;  

        if (!cumpleRequisitosUsuario(nombre) || !cumpleRequisitosContrasena(contrasena)) {  
            cout << "El usuario o contrasena no cumplen los requisitos. Intenta de nuevo.\n";
            continue;
        }

        if (contraRepetida(contrasena)) {
            cout << "La contrasena ya ha sido usada por otro usuario. Ingresa otra diferente.\n";
            continue;
        }

        if (buscarUsuarios(usuarios, tope, nombre)) {   
            cout << "El usuario ya existe.\n";
            cout << "1. Ingresar otro usuario\n";
            cout << "2. Iniciar sesion\n";
            cout << "3. Salir\n";
            int opcion;
            cin >> opcion;
            if (opcion == 1) continue;
            else if (opcion == 2) {
                return iniciarSesion(usuarios, tope);  
            }
            else {
                return 0;
            }
        }
        else {
            // CORREGIDO: Verificar límite de usuarios
            if(tope >= maxUsuarios) {
                cout << "No se pueden registrar mas usuarios.\n";
                return 0;
            }
            
            strcpy(usuarios[tope].nombre, nombre);  
            strcpy(usuarios[tope].contrasena, contrasena);  
            usuarios[tope].puntajeMejor = 0;
            
            FILE* archivo = fopen("usuarios.txt", "a");
            if (archivo) {
                fprintf(archivo, "%s %s %d\n", nombre, contrasena, 0);
                fclose(archivo);
            }
            tope++;
            strcpy(nombreJugadorActual, nombre);

            cout << "Registro exitoso.\n";
            return 1; // CORREGIDO: Retornar directamente después del registro exitoso
        }
    }
}

bool contraRepetida(const char* contrasena){
    char nombreArchivo[50], contrasenaArchivo[50];
    int puntaje;

    FILE* archivo = fopen("usuarios.txt", "r");
    if(!archivo){
        return false;
    }
    while (fscanf(archivo, "%49s %49s %d", nombreArchivo, contrasenaArchivo, &puntaje) == 3) { // CORREGIDO: Límite de caracteres y verificación de retorno
        if (strcmp(contrasenaArchivo, contrasena) == 0) {
            fclose(archivo);
            return true;
        }
    }

    fclose(archivo);
    return false;
}

void elegirNivel(){
    system("cls");
    //Reiniciar estado para nuevo nivel
    if(secuencia != NULL) {
        delete[] secuencia;
        secuencia=NULL;	
    } 
    secuenciaMaxima=0;
    tamTablero=0;
    puntaje=0;
    longitudSecuencia=1; 
    juegoActivo=true;
    
    int opc=0;
    float opcion=0;
    do{
        opc = 0;
        cout << "\nNivel 1.................1";
        cout << "\nNivel 2.................2";
        cout << "\nNivel 3.................3";
        cout << "\nAyuda (como jugar)......4";
        cout << "\nRegresar al menu........5";
        cout << "\nElige una opcion: ";
        cin>>opcion;
        
        if(cin.fail()){ 
            cin.clear(); 
            cin.ignore(1000,'\n'); 
        } 
        else if(fmod(opcion,1) == 0) opc=static_cast<int>(opcion); 

        switch(opc){
            case 1: jugarNiveles(opc); break; 
            case 2: jugarNiveles(opc); break;
            case 3: jugarNiveles(opc); break;
            case 4: mostrarAyuda(); break;
            case 5: system("cls");
                    return; // CORREGIDO: usar return para salir de la función
            default: cout<<"Ups! esa opcion es invalida, intenta de nuevo";
                    Sleep(1500);
                    system("cls");
        }
    }while(opc != 5);
}

void jugarNiveles(int nivel) {	
    // CORREGIDO: Validar nivel válido
    if(nivel < 1 || nivel > 3) {
        cout << "Nivel invalido\n";
        return;
    }
    
    if(nivel == 1) {
        tamTablero = 3;
        secuenciaMaxima = 9;
    } 
    else if(nivel == 2) {
        tamTablero = 5;
        secuenciaMaxima = 25;	
    } 
    else if(nivel == 3) {
        tamTablero = 7;
        secuenciaMaxima = 49;	
    } 

    // CORREGIDO: Verificar asignación de memoria
    secuencia = new(std::nothrow) COORD[secuenciaMaxima];
    if(!secuencia) {
        cout << "Error: No se pudo asignar memoria para la secuencia\n";
        return;
    }

    longitudSecuencia = 1;
    puntaje = 0; 
    juegoActivo = true;
    pasoActual = 0;
    
    eliminarTablero(); 
    crearTablero();
    if(!tablero) { // CORREGIDO: Verificar si se pudo crear el tablero
        cout << "Error: No se pudo crear el tablero\n";
        if(secuencia) {
            delete[] secuencia;
            secuencia = NULL;
        }
        return;
    }
    inicializarTablero();

    generarSecuencia();
    
    while(juegoActivo && longitudSecuencia <= secuenciaMaxima) { // CORREGIDO: Verificar límite
        posicionJugador = {0,0};
        pasoActual = 0;
        
        if(!juegoActivo) break; 
        
        mostrarSecuencia();
        dibujarTablero();
        
        bool secuenciaCompleta = false; 
        while(!secuenciaCompleta && juegoActivo){ 
            if(_kbhit()){ 
                int tecla = _getch(); 
                
                if(tecla == 0xE0) { 
                    tecla = _getch(); 	
                    moverJugador(tecla);
                    dibujarTablero();
                } 	
                
                else if(tecla == 13) { 
                        secuenciaCompleta = verificarSeleccion();
                        dibujarTablero();
                        
                        if(secuenciaCompleta) {
                            cout << "Correcto! Puntaje: "<<puntaje<<endl;
                            cout << "Secuencia completada correctamente.\n";
                            if(longitudSecuencia<secuenciaMaxima) {
                                cout << "Preparate para la siguiente secuencia";	
                            }
                            Sleep(3000);
                        }
                }

                else if(tecla == 86 || tecla == 118) { 
                    eliminarTablero(); // CORREGIDO: Limpiar memoria antes de salir
                    if(secuencia) {
                        delete[] secuencia;
                        secuencia = NULL;
                    }
                    elegirNivel();
                    return;
                }

                else if(tecla == 65 || tecla == 97) { 
                    mostrarAyuda();
                    mostrarSecuencia();
                    dibujarTablero();
                }
                
                else if(tecla == 71 || tecla == 103) { 
                    guardarPartida();
                }
            }
        }
    }
  
    guardarPuntaje(); 
    system("cls");
    int opc = 0;
    float opcion = 0;
    
    if(longitudSecuencia <= secuenciaMaxima){ 
        do{
            cout << "\nSecuencia incorrecta. Fin del juego";
            cout << "\nPuntaje alcanzado: " << puntaje;
            cout << "\nSecuencia alcanzada: " << longitudSecuencia-1;
            cout << "\nRepetir nivel.........1";
            cout << "\nRegresar..............2";
            cout << "\nTu eleccion: ";
            cin >> opcion;
            if(cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                system("cls");
                cout << "Entrada invalida";
                Sleep(2000);
                system("cls");
            }
            else if(fmod(opcion,1)==0) opc = static_cast<int>(opcion);
            switch(opc){
                case 1: eliminarTablero(); // CORREGIDO: Limpiar antes de repetir
                        if(secuencia) { delete[] secuencia; secuencia = NULL; }
                        jugarNiveles(nivel); return; 
                case 2: eliminarTablero();
                        if(secuencia) { delete[] secuencia; secuencia = NULL; }
                        elegirNivel(); return;
            }
        }while(opc != 1 && opc != 2);
    }
    
    else if(nivel == 1 || nivel == 2){ 
        do{
            cout << "\nNivel completado!";
            cout << "\nPuntaje alcanzado: " << puntaje;
            cout << "\nPasar al siguiente nivel.........1";
            cout << "\nRegresar.........................2";
            cout << "\nTu eleccion: ";
            cin >> opcion;
            if(cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                system("cls");
                cout << "Entrada invalida";
                Sleep(2000);
                system("cls");
            }
            else if(fmod(opcion,1)==0) opc = static_cast<int>(opcion);
            else{
                system("cls");
                cout << "Entrada invalida";
                Sleep(2000);
                system("cls");	
            }
            switch(opc){
                case 1: eliminarTablero();
                        if(secuencia) { delete[] secuencia; secuencia = NULL; }
                        jugarNiveles(nivel+1); return;  
                case 2: eliminarTablero();
                        if(secuencia) { delete[] secuencia; secuencia = NULL; }
                        elegirNivel(); return;
            }
        }while(opc != 1 && opc != 2);
    }
    
    else{ 
        do{
            cout << "\nFelicidades! Completaste todos los niveles!";
            cout << "\nPuntaje final: " << puntaje;
            cout << "\nRegresar.............1";
            cout << "\nTu eleccion: ";
            cin >> opcion;
            if(cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                system("cls");
                cout << "Entrada invalida";
                Sleep(2000);
                system("cls");
            }
            else if(opcion == 1){
                eliminarTablero();
                if(secuencia) { delete[] secuencia; secuencia = NULL; }
                elegirNivel();
                return;
            } 
            else{
                system("cls");
                cout << "Entrada invalida";
                Sleep(2000);
                system("cls");	
            }
        }while(opcion != 1);
    }
}

void guardarPuntaje() {
    // CORREGIDO: Verificar que el nombre del jugador no esté vacío
    if(strlen(nombreJugadorActual) == 0) {
        cout << "Error: No hay jugador activo\n";
        return;
    }
    
    FILE* archivoPuntajes = fopen("mejores_puntajes.txt", "a");
    if(archivoPuntajes != NULL) {
        fprintf(archivoPuntajes, "%s %d\n", nombreJugadorActual, puntaje);
        fclose(archivoPuntajes);
    }

    Usuario usuarios[MAX];
    int cantidadUsuarios = cargarUsuariosDesdeArchivo(usuarios, MAX);
    
    for(int i = 0; i < cantidadUsuarios; i++) {
        if(strcmp(usuarios[i].nombre, nombreJugadorActual) == 0) {
            if(puntaje > usuarios[i].puntajeMejor) {
                usuarios[i].puntajeMejor = puntaje;
                
                FILE* archivoUsuarios = fopen("usuarios.txt", "w");
                if(archivoUsuarios != NULL) {
                    for(int j = 0; j < cantidadUsuarios; j++) {
                        fprintf(archivoUsuarios, "%s %s %d\n", 
                                usuarios[j].nombre, 
                                usuarios[j].contrasena, 
                                usuarios[j].puntajeMejor);
                    }
                    fclose(archivoUsuarios);
                }
                break;
            }
        }
    }

    FILE* archivoHistorial = fopen("historial_jugadas.txt", "a");
    if(archivoHistorial != NULL) {
        time_t ahora = time(NULL);
        struct tm* tiempoLocal = localtime(&ahora);
        char fechaHora[20];
        strftime(fechaHora, sizeof(fechaHora), "%Y-%m-%d_%H:%M:%S", tiempoLocal); // CORREGIDO: Usar _ en lugar de espacio
        
        int nivel;
        if(tamTablero == 3) nivel = 1;
        else if(tamTablero == 5) nivel = 2;
        else nivel = 3;
        
        fprintf(archivoHistorial, "%s %d %d %s\n", 
                nombreJugadorActual, 
                nivel, 
                puntaje, 
                fechaHora);
        fclose(archivoHistorial);
    }
    
    cout << "\nPuntuacion guardada exitosamente!" << endl;
    Sleep(2000);
}

void guardarPartida() {
    system("cls");
    cout << "\n=== GUARDAR PARTIDA ===" << endl;
    cout << "\nEsta función está en desarrollo." << endl;
    cout << "Por ahora, tu puntaje actual es: " << puntaje << endl;
    cout << "Nivel actual: ";
    if(tamTablero == 3) cout << "1";
    else if(tamTablero == 5) cout << "2";
    else cout << "3";
    cout << "\nSecuencia actual: " << longitudSecuencia << "/" << secuenciaMaxima << endl;
    cout << "\nPresiona cualquier tecla para continuar...";
    _getch();
}

void crearTablero() {	
    // CORREGIDO: Verificar asignación de memoria
    tablero = new(std::nothrow) Celda*[tamTablero]; 
    if(!tablero) {
        cout << "Error: No se pudo asignar memoria para el tablero\n";
        return;
    }
    
    // CORREGIDO: Inicializar punteros a NULL antes de asignar
    for(int i = 0; i < tamTablero; i++) {
        tablero[i] = NULL;
    }
    
    for(int i = 0; i < tamTablero; i++) {
        tablero[i] = new(std::nothrow) Celda[tamTablero];
        if(!tablero[i]) {
            // Si falla la asignación, liberar memoria ya asignada
            for(int j = 0; j < i; j++) {
                delete[] tablero[j];
            }
            delete[] tablero;
            tablero = NULL;
            cout << "Error: No se pudo asignar memoria para las filas del tablero\n";
            return;
        }
    }
}

// Inicializa el tablero
void inicializarTablero() {
    for(int i = 0; i < tamTablero; i++) {
        for(int j = 0; j < tamTablero; j++) {
            tablero[i][j].numero = i*tamTablero+j+1;
            tablero[i][j].encendida = false;
        }
    }	
}

// Genera las posiciones aleatorias de las casillas a encender 
void generarSecuencia() {
    if(longitudSecuencia > secuenciaMaxima) {
        juegoActivo = false; 
        return;
    }        
    if(longitudSecuencia == 1) {
        secuencia[0].X = rand() % tamTablero;
        secuencia[0].Y = rand() % tamTablero;
    }
    else {
        bool repetida;
        do{
            repetida = false;
            secuencia[longitudSecuencia-1].X = rand() % tamTablero;
            secuencia[longitudSecuencia-1].Y = rand() % tamTablero;
            for(int j = 0; j < longitudSecuencia - 1; j++){
                if(secuencia[longitudSecuencia-1].X == secuencia[j].X && 
                   secuencia[longitudSecuencia-1].Y == secuencia[j].Y) {
                    repetida = true; 
                    break;
                }
            }
        }while(repetida);
    }
}

// Enciende las celdas y llama a dibujarTablero
void mostrarSecuencia() {
    system("cls");	
    for(int i = 0; i < longitudSecuencia; i++) {
        tablero[secuencia[i].Y][secuencia[i].X].encendida=true;
        dibujarTablero();
        Sleep(1000);
        tablero[secuencia[i].Y][secuencia[i].X].encendida=false;
        dibujarTablero();
        Sleep(300);		
    }
}

/* Dibuja el tablero para mostrar la secuencia a repetir
    o la posicion en la que se ubica el jugador para 
    repetir la secuencia*/
void dibujarTablero() {
    system("cls");
    // Encabezado
    if(secuenciaMaxima == 9) cout << "\tNIVEL 1" << endl;
    else if(secuenciaMaxima == 25) cout << "\tNIVEL 2" << endl;
    else cout << "\tNIVEL 3" << endl;
    cout << "Puntaje: " << puntaje << "  |  Secuencia: " << longitudSecuencia << "/" << secuenciaMaxima << endl;
    cout << "Ayuda/Como jugar (a/A)\t\tVolver (v/V)" << endl;
    cout << "Guardar partida (g/G)" << endl << endl;

    for(int i = 0; i < tamTablero; i++) {
        for(int j = 0; j < tamTablero; j++) {
            // Mostrar secuencia
            if(tablero[i][j].encendida) {
                int color = 1 + (rand() % 6); // Generar color para las casillas
                switch(color) {
                    case 1: SetConsoleTextAttribute(hConsole, AZUL); break;
                    case 2: SetConsoleTextAttribute(hConsole, VERDE); break;
                    case 3: SetConsoleTextAttribute(hConsole, CIAN); break;
                    case 4: SetConsoleTextAttribute(hConsole, ROJO); break;
                    case 5: SetConsoleTextAttribute(hConsole, MAGENTA); break;
                    case 6: SetConsoleTextAttribute(hConsole, AMARILLO); break;
                }
                cout << "[";
                if(tablero[i][j].numero<10) cout << " ";
                cout << tablero[i][j].numero << "]";
            }
            
            // Mostrar posición del jugador en el tablero
            else {
                SetConsoleTextAttribute(hConsole, 240); // Fondo blanco, texto negro
                cout << "[";
                if(posicionJugador.X == j && posicionJugador.Y == i) { // Casilla en la que se ubica el jugador
                    cout << " X";
                }
                else cout << "  "; // Casillas en las que no está el jugador
                cout << "]";
            }
            SetConsoleTextAttribute(hConsole, BLANCO);
        }
        cout<<endl;
    }
}

// Mueve al jugador en el tablero dependiendo de la flecha presionada en teclado
void moverJugador(int tecla) {
    switch(tecla) {
        case 75: if(posicionJugador.X > 0) posicionJugador.X--; break; 			// Izquierda
        case 77: if(posicionJugador.X < tamTablero-1) posicionJugador.X++; break; // Derecha
        case 72: if(posicionJugador.Y > 0) posicionJugador.Y--; break; 			// Arriba
        case 80: if(posicionJugador.Y < tamTablero-1) posicionJugador.Y++; break; // Abajo
    }	
}

// Verificar si la selección del jugador es correcta
bool verificarSeleccion() {
    // Verificar que la selección actual coincida con la guardada 
    if(posicionJugador.X == secuencia[pasoActual].X && posicionJugador.Y == secuencia[pasoActual].Y) {
        
        pasoActual++;
        
        if(pasoActual >= longitudSecuencia) {
            // Calcular puntos: pasoActual*10
            puntaje += longitudSecuencia * 10;

            // Preparar para la siguiente ronda
            longitudSecuencia++;
            pasoActual = 0;
            
            // Verificar si completó el nivel
            if(longitudSecuencia > secuenciaMaxima) {
                juegoActivo = false;
                return true; // Nivel completado
            }
            
            // Generar nueva secuencia (agregar una casilla más)
            generarSecuencia();
            return true; // Secuencia completada, continuar

        }
        return false;
    }	
    else juegoActivo=false;
    return false;
}

/* Libera el espacio en memoria que ocupa el tablero actual
    para crear otro con otro tamaño dependiendo del nivel
    que el usuario desee jugar
*/
void eliminarTablero() {
    if(tablero != NULL) { 
        // Eliminar columnas
        for(int i = 0; i < tamTablero; i++){
            delete[] tablero[i]; 
        }
    
        // Eliminar filas
        delete[] tablero;
        
        tablero = NULL;		
    }
}

// Función para mostrar el historial de jugadas del usuario
void mostrarHistorialUsuario() {
    system("cls");
    SetConsoleTextAttribute(hConsole, AMARILLO);
    cout << "\n\t\t=== HISTORIAL DE JUGADAS ===" << endl;
    SetConsoleTextAttribute(hConsole, BLANCO);

    if(strlen(nombreJugadorActual) == 0) {
        cout << "\nDebes iniciar sesión para ver tu historial." << endl;
        limpiarPantalla();
        return;
    }

    FILE* archivo = fopen("historial_jugadas.txt", "r");
    if(!archivo) {
        cout << "\nAún no hay historial de jugadas registrado." << endl;
        limpiarPantalla();
        return;
    }

    char nombre[50], fecha[20];
    int nivel, puntaje;
    bool tieneHistorial = false;

    cout << "\nHistorial de jugadas para " << nombreJugadorActual << ":\n";
    cout << "--------------------------------------------------\n";
    cout << "Nivel\tPuntaje\t\tFecha y Hora\n";
    cout << "--------------------------------------------------\n";

    while(fscanf(archivo, "%s %d %d %s", nombre, &nivel, &puntaje, fecha) != EOF) {
        if(strcmp(nombre, nombreJugadorActual) == 0) {
            tieneHistorial = true;
            cout << nivel << "\t" << puntaje << "\t\t" << fecha << endl;
        }
    }
    fclose(archivo);

    if(!tieneHistorial) {
        cout << "\nAún no tienes partidas registradas en tu historial." << endl;
    }

    limpiarPantalla();
}

// Función para mostrar los mejores puntajes
void mostrarMejoresPuntajes() {
    system("cls");
    SetConsoleTextAttribute(hConsole, AMARILLO);
    cout << "\n\t\t=== MEJORES PUNTAJES ===" << endl;
    SetConsoleTextAttribute(hConsole, BLANCO);

    FILE* archivo = fopen("mejores_puntajes.txt", "r");
    if(!archivo) {
        cout << "\nAún no hay puntajes registrados." << endl;
        limpiarPantalla();
        return;
    }

    struct {
        char nombre[50];
        int puntaje;
    } puntajes[MAX];
    int cantidad = 0;

    while(fscanf(archivo, "%s %d", puntajes[cantidad].nombre, &puntajes[cantidad].puntaje) != EOF && cantidad < MAX) {
        cantidad++;
    }
    fclose(archivo);

    // Ordenar puntajes de mayor a menor
    for(int i = 0; i < cantidad-1; i++) {
        for(int j = 0; j < cantidad-i-1; j++) {
            if(puntajes[j].puntaje < puntajes[j+1].puntaje) {
                auto temp = puntajes[j];
                puntajes[j] = puntajes[j+1];
                puntajes[j+1] = temp;
            }
        }
    }

    cout << "\nTOP 10 MEJORES PUNTAJES:\n";
    cout << "-----------------------------------------\n";
    cout << "Posición\tJugador\t\tPuntaje\n";
    cout << "-----------------------------------------\n";

    int limite = (cantidad < 10) ? cantidad : 10;
    for(int i = 0; i < limite; i++) {
        cout << i+1 << "\t\t" << puntajes[i].nombre << "\t\t" << puntajes[i].puntaje << endl;
    }

    if(strlen(nombreJugadorActual) > 0) {
        bool encontrado = false;
        for(int i = 0; i < cantidad; i++) {
            if(strcmp(puntajes[i].nombre, nombreJugadorActual) == 0) {
                cout << "\nTu mejor puntaje: " << puntajes[i].puntaje;
                cout << " (Posición #" << i+1 << ")\n";
                encontrado = true;
                break;
            }
        }
        if(!encontrado && cantidad > 0) {
            cout << "\nTu mejor puntaje aún no está entre los mejores.\n";
        }
    }

    limpiarPantalla();
}

void mostrarMensajeDespedida() {
    system("cls");
    SetConsoleTextAttribute(hConsole, AMARILLO);
    cout << "\n";
    cout << "  ================================================================\n";
    cout << "                                                                  \n";
    cout << "                    ¡GRACIAS POR JUGAR!                          \n";
    cout << "                                                                  \n";
    cout << "                      FABULOSO FRED                              \n";
    cout << "                    JUEGO DE MEMORIA                             \n";
    cout << "                                                                  \n";
    cout << "              ¡Esperamos verte de nuevo pronto!                  \n";
    cout << "                                                                  \n";
    cout << "  ================================================================\n";
    cout << "\n";
    SetConsoleTextAttribute(hConsole, BLANCO);
    Sleep(3000);
}