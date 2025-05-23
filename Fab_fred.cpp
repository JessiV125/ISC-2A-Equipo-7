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
#define TAMN1 3 // Tamaño para el tablero del primer nivel
#define TAMN2 5 // Tamaño para el tablero del primer nivel
#define TAMN3 7 // Tamaño para el tablero del primer nivel

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
void elegirNivel();
bool buscarUsuarios(Usuario usuarios[], int tope, const char nombre[], const char contrasena[]);

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
  -Tiene un menú y da a elegir entre 3 niveles:
        1)Nivel 1: llama a jugarNivel1
        2)Nivel 2: llama a jugarNivel2
        3)Nivel 3: llama a jugarNivel3
  -En el menú, también tiene opción de atrás: llama a menuOpciones
*/
void elegirNivel(){
  int opc=0, tab1[TAMN1][TAMN1], tab2[TAMN2][TAMN2], tab3[TAMN3][TAMN3];
  float opcion=0;
  cout<<"\nEste es un juego para trabajar tu memeoria:\nSe mostrara en pantalla una secuencia de colores en una tabla\nla cual deberas memorizar y replicar posteriormente.\n\n";
  cout<<"Muévete por las casillas usando las letras de flechas y presiona Enter para seleccionar una.\n\n";
  do{
    cout<<"\nNivel 1......1";
    cout<<"\nNivel 2......2";
    cout<<"\nNivel 3......3";
    cout<<"\nAtras........4";
    cout<<"\nElige una opcion: ";
    cin>>opcion;
    if(cin.fail()){ // Si la entrada no es un numero
      cin.clear(); // Limpiar estado de error de cin
      cin.ignore(1000,'\n'); // Descartar entrada inválida hasta mil caracteres o hasta encontrar un salto de línea
    } 
    else if(fmod(opcion,1)!=0) cout<<" "; // Descartar numeros con decimales 
    else opc=static_cast<int>(opcion); // convertir opcion a entero para que pueda ser evaluado por switch
    switch(opc){
          case 1: break;
          case 2: break;
          case 3: break;
          case 4: MostrarMenu(); break;
          default: cout<<"Ups! esa opcion es invalida, intenta de nuevo";
    }
  }while(opc!=4);
}