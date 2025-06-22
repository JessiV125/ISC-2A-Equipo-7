/*
INTEGRANTES DE EQUIPO

Alinne Alejandra Díaz López
Valeria Martín de Santos 
Jessica Vanessa Martínez de la Rosa
Danna Sofía Morales Esparza 
*/

#include <iostream>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <cstring>
using namespace std;



static int tope = 10;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

#define TAMN1 3
#define TAMN2 5
#define TAMN3 7

enum {AZUL = 1, VERDE, CYAN, ROJO, MAGENTA, AMARILLO, BLANCO};

struct Usuario {
    char nombre[10];
    char contrasena[20];
	int puntajeMejor;
};

struct Celda{
	int numero;
	bool encendida;	
};

void mostrarTitulo();

void limpiarPantalla();
void MostrarMenu(Usuario[], int&, int);
//registro
void iniciarSesion(Usuario usuarios[], int tope);
void realizarRegistro(Usuario usuarios[], int &tope);
void elegirNivel();
bool buscarUsuarios(Usuario usuarios[], int tope, const char nombre[], const char contrasena[]);
void mostrarBienvenida();
void mostrarMejoresPuntajes();
void mostrarInicio();
void mostrarHistorial();
void volverMenu();
void mostrarMensajeDespedida();
void mostrarAyuda();
void cargarPartida();
void verMejoresPuntajes();
void guardarJugador(const char nombre[], const char contrasena[]);
void cargarJugadores(Usuario usuarios[], int &cantidad);

void mostrarTitulo(){
    SetConsoleTextAttribute(hConsole, CYAN);
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
    
    SetConsoleTextAttribute(hConsole, CYAN);
    cout << "                                                                  \n";
    cout << "  ================================================================\n";
    cout << "\n";
    
    // Mensaje de bienvenida
    SetConsoleTextAttribute(hConsole, AMARILLO);
    cout << "                    ¡BIENVENIDO AL DESAFIO!\n";
    cout << "\n";
    
    SetConsoleTextAttribute(hConsole, BLANCO);
    cout << "  Prepara tu mente para el mayor reto de memoria y concentracion.\n";
    cout << "  ¿Podras seguir la secuencia hasta el final?\n";
    cout << "\n";
    
    SetConsoleTextAttribute(hConsole, BLANCO);
    cout << "\n";
    cout << "  >> CONSEJOS:\n";
    cout << "     * Concentrate al maximo\n";
    cout << "     * Toma tu tiempo para recordar\n";
    cout << "     * La practica hace al maestro\n";
    cout << "     * ¡Mantén la calma bajo presion!\n";
    cout << "\n";
    
    SetConsoleTextAttribute(hConsole, AMARILLO);
    cout << "  ================================================================\n";
    cout << "           ¡Que comience el entrenamiento mental!\n";
    cout << "  ================================================================\n";
    cout << "\n";
    
    SetConsoleTextAttribute(hConsole, BLANCO);
    cout << "  Presiona cualquier tecla para comenzar el desafio...";
    cin.get(); // Pausa para que el usuario lea la bienvenida
    system("cls"); // Limpiar pantalla después de la bienvenida
}

int main() {
    mostrarTitulo();
    mostrarBienvenida();
    return 0;
}

void limpiarPantalla() {
    system("pause");
    system("cls");
}


void MostrarMenu(){
	int opc;
  	float opcion;

	do{
		SetConsoleTextAttribute(hConsole, ROJO);
		opc = 0;
		cout << "\n   === MENU PRINCIPAL ===" << endl;
		cout << "\nJugar.........................1";	
		cout << "\nVer mejores puntajes..........2";
		cout << "\nCargar partida................3";
		cout << "\nAyuda.........................4";
		cout << "\nCreditos......................5";
		cout << "\nSalir.........................6";
		cout << "\nOpcion: ";
		cin >> opcion;
		SetConsoleTextAttribute(hConsole, BLANCO);
		
		if(cin.fail()){
			cin.clear();
			cin.ignore(1000,'\0');
		}
		else if (fmod(opcion,1)==0) opc = static_cast <int> (opcion);
		
      switch (opc) {
        case 1: { system("cls");
                  Usuario usuarios[tope];
                  cargarJugadores(usuarios, tope);
                  iniciarSesion(usuarios, tope); 
                  break;
                }
        case 2: system("cls");
                verMejoresPuntajes(); 
                break;
			  case 3: system("cls");
	      				cargarPartida();
				      	break;
			  case 4: mostrarAyuda();
					      break;
			  case 5: mostrarMensajeDespedida();
					      break;
			  case 6: mostrarMensajeDespedida();
					      break;
			  default: cout << "Opcion invalida";
					      Sleep(1500);
					      system("cls");
		}
	}while(opc != 6);  
}

void iniciarSesion(Usuario usuarios[], int tope) {
    char tieneCuenta;
    char nombre[20];
    char contrasena[20];
    int cantidad = tope;

    do {
        cout << "Tienes una cuenta? (s/n): ";
        cin >> tieneCuenta;

        if (tieneCuenta == 'n' || tieneCuenta == 'N') {
            realizarRegistro(usuarios, cantidad);
            MostrarMenu();
            break;
        } else if (tieneCuenta == 's' || tieneCuenta == 'S') {
            cout << "Nombre de usuario: ";
            cin >> nombre;
            cout << "Contrasena: ";
            cin >> contrasena;

            if (buscarUsuarios(usuarios, tope, nombre, contrasena)) {
                MostrarMenu();
                break;
            } else {
                cout << "Nombre o contrasena incorrectos.\n";
            }
        } else {
            cout << "Opcion no valida. Intenta de nuevo.\n";
        }

    } while (true);
}

bool buscarUsuarios(Usuario usuarios[], int tope, const char nombre[], const char contrasena[]) {
    for (int i = 0; i < tope; i++) {
        if (strcmp(usuarios[i].nombre, nombre) == 0 &&
            strcmp(usuarios[i].contrasena, contrasena) == 0) {
            return true;
        }
    }
    return false;
}

void realizarRegistro(Usuario usuarios[], int &tope) {
    char nombre[10];
    char contrasena[20];
    
    cout << "=== REGISTRO DE NUEVO USUARIO ===\n";
    cout << "Nombre de usuario: ";
    cin >> nombre;
    cout << "Contrasena: ";
    cin >> contrasena;
    
    // Agregar el nuevo usuario al array
    strcpy(usuarios[tope].nombre, nombre);
    strcpy(usuarios[tope].contrasena, contrasena);
    tope++;
    
    cout << "Usuario registrado exitosamente!\n";
    system("pause");
    system("cls");
}

void mostrarBienvenida() {
    cout << "=== Bienvenido a fabFred ===\n";
    mostrarMejoresPuntajes();
    mostrarInicio();
}

void mostrarMejoresPuntajes() {
    cout << "[Mostrar mejores puntajes de todos los jugadores]\n";
}

void mostrarInicio() {
    int opcionInicio;
    cout << "\n¿Deseas comenzar el juego?\n";
    cout << "1. Sí\n";
    cout << "2. No (Salir)\n";
    cin >> opcionInicio;

    if (opcionInicio == 1) {
        int opcionCuenta;
        cout << "¿Ya tienes una cuenta?\n";
        cout << "1. Sí (Iniciar sesión)\n";
        cout << "2. No (Registrarse)\n";
        cin >> opcionCuenta;

        cout << "[Aquí iría: ";
        if (opcionCuenta == 1) cout << "Iniciar Sesión";
        else cout << "Registro";
        cout << "]\n";

        cout << "[Luego iría a MostrarMenu() si todo es exitoso]\n";
        MostrarMenu();
    } else {
        cout << "¡Hasta pronto!\n";
    }
}

void mostrarHistorial() {
    cout << "[Mostrar historial del usuario actual]\n";
    cout << "1. Volver al menú principal\n";
    int op;
    cin >> op;
    MostrarMenu();
}

void elegirNivel() {
    int opc = 0, tab1[TAMN1][TAMN1], tab2[TAMN2][TAMN2], tab3[TAMN3][TAMN3];
    float opcion = 0;

    cout << "\nEste es un juego para trabajar tu memoria:\n";
    cout << "Se mostrará una secuencia de colores en una tabla\n";
    cout << "la cual deberás memorizar y replicar después.\n\n";
    cout << "Muévete por las casillas usando letras de flechas y presiona Enter para seleccionar.\n";

    do {
        cout << "\nNivel 1......1";
        cout << "\nNivel 2......2";
        cout << "\nNivel 3......3";
        cout << "\nAtras........4";
        cout << "\nElige una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        } else if (fmod(opcion, 1) != 0) {
            cout << "";
        } else {
            opc = static_cast<int>(opcion);
        }

        switch (opc) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                MostrarMenu();
                break;
            default:
                cout << "Ups! esa opcion es invalida, intenta de nuevo";
        }

    } while (opc != 4);
}

void cargarJugadores(Usuario*, int&) {
    // Por implementar
}

void verMejoresPuntajes() {
    // Por implementar
}

void cargarPartida() {
    // Por implementar
}

void mostrarAyuda() {
    // Por implementar
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

void volverMenu() {
    cout << "Presiona Enter para volver al menú...\n";
    cin.ignore();
    cin.get();
    system("cls");
}