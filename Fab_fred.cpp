/*
INTEGRANTES DE EQUIPO

Alinne Alejandra Díaz López
Valeria Martín de Santos 
Jessica Vanessa Martínez de la Rosa
Danna Sofía Morales Esparza 
*/

#include <iostream>
#include<math.h>
#include<windows.h> // Para manejar graficos 
#include<conio.h> // Para leer teclas 
#include<time.h>
#include<stdlib.h>
using namespace std;
static int tope = 10;    //Contador  y declaración de la variable estatica

// Obtener manejador de consola
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

//CONSTANTES

//COLORES
enum{AZUL=1, VERDE, CYAN, ROJO, MAGENTA, AMARILLO};

//STRUCT
struct Usuario{
    char nombre[10];
    char contrasena[20];
};

// PROTOTIPOS
void limpiarPantalla();
void MostrarMenu();
void iniciarSesion(Usuario usuarios[], int tope);
void MostrarInicio();
void realizarRegistro();
bool buscarUsuarios(Usuario usuarios[], int tope, const char nombre[], const char contrasena[]);

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

int main(){
  cout << "Proyecto FRED";
  MostrarMenu();
  Usuario usuarios[10]; //Arreglo de usuarios inicializado
  iniciarSesion(usuarios, tope);    //  Pasar el arreglo de usuarios
  return 0;
}

// IMPLEMENTACION 
void limpiarPantalla(){
  system("pause"); // Pausar ejecución antes de limpiar la pantalla 
  system("cls"); // Limpiar la pantalla
}

void MostrarMenu(){
  int opc;

  cout << "Menu";
  cout << "1 - Opcion";
  cout << "2 - Opcion";
  cout << "Ingresa una opcion: ";
  cin >> opc;
  
}

void iniciarSesion(Usuario usuarios[], int tope){
  char tieneCuenta;
  char nombre[20];
  char contrasena[20];

  do{
    cout<<"Tienes una cuenta? (s/n)";
    cin>> tieneCuenta;

      if (tieneCuenta == 'n' || tieneCuenta == 'N')  {
       MostrarMenu();
       break;
      } else if (tieneCuenta == 's' || tieneCuenta == 'S')  {
            cout << "Nombre de usuario: ";
            cin >> nombre;
            cout << "Contrasena: ";
            cin>> contrasena;

              if (buscarUsuarios(usuarios, tope, nombre, contrasena)) {
                MostrarMenu();
                break;    //Termina el proceso al enttrar correctamente 
              } else  {
                cout << "Nombre o contrasena incorrectos. \n";
              }   //Vuelve al inicio del ciclo
    
        } else {
          cout << "Opcion no valida. Intenta de nuevo. \n";
        }
      
  
  } while(true);   
}

bool buscarUsuarios(Usuario usuarios[], int tope, const char nombre[], const char contrasena[]){
  for (int i = 0; i < tope; i++) {
    if (strcmp(usuarios[i].nombre, nombre) == 0 &&
    strcmp(usuarios[i].contrasena, contrasena) == 0) {
    return true;
}
}
return false;

}

void realizarRegistro(){

}

/*
  -Explica reglas del juego
  -Tiene un menú y da a elegir entre 3 niveles
*/
void elegirNivel(){
	system("cls");
	//Reiniciar estado para nuevo nivel
	if(secuencia!=NULL){
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
  	cout<<"\nEste es un juego para trabajar tu memeoria:\nSe mostrara en pantalla una secuencia de colores en una tabla\nla cual deberas memorizar y replicar posteriormente.\n\n";
  	cout<<"Muevete por las casillas usando las teclas de flechas y presiona Enter para seleccionar una.\n\n";
	do{
    	cout<<"\nNivel 1......1";
    	cout<<"\nNivel 2......2";
    	cout<<"\nNivel 3......3";
    	cout<<"\nElige una opcion: ";
    	cin>>opcion;
    	
    	// Verificar entrada de opcion
    	if(cin.fail()){ // Si la entrada no es un numero
      		cin.clear(); // Limpiar estado de error de cin
      		cin.ignore(1000,'\n'); // Descartar entrada inválida hasta mil caracteres o hasta encontrar un salto de línea
    	} 
    	else if(fmod(opcion,1)==0) opc=static_cast<int>(opcion); // Descartar numeros con decimales // convertir opcion a entero para que pueda ser evaluado por switch
    	else{ 
			system("cls");
			cout<<"Ups! esa opcion es invalida, intenta de nuevo";
			Sleep(2000);
			system("cls");	
		}

		switch(opc){
        	case 1: jugarNiveles(opc); break; // La funcion recibe opc con el nombre de nivel
          case 2: jugarNiveles(opc); break;
          case 3: jugarNiveles(opc); break;
          default: cout<<"Ups! esa opcion es invalida, intenta de nuevo";
    	}
	}while(opc!=4);
}