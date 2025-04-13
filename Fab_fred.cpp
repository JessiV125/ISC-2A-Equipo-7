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
using namespace std;

// Obtener manejador de consola
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

//CONSTANTES

//COLORES
enum{AZUL=1, VERDE, CYAN, ROJO, MAGENTA, AMARILLO};

// PROTOTIPOS
void MostrarMenu();
void iniciarSesión();
void realizarRegistro();
void elegirNivel();
void jugarNivel1();
void jugarNivel2();
void jugarNivel3();

int main(){
  cout << "Proyecto FRED";
  MostrarMenu();

  return 0;
}

// IMPLEMENTACION 

void MostrarMenu(){
  int opc;

  cout << "Menu";
  cout << "1 - Opcion";
  cout << "2 - Opcion";
  cout << "Ingresa una opcion: ";
  cin >> opc;
  
}


void iniciarSesión(){

}

void realizarRegistro(){

}

void elegirNivel(){
  int opc=0;
  float opcion=0;
  cout<<"\nEste es un juego para trabajar tu memeoria:\nSe mostrara en pantalla una secuencia de colores en una tabla\nla cual deberas memorizar y replicar posteriormente.\n\n";
  do{
    cout<<"\nNivel 1......1";
    cout<<"\nNivel 2......2";
    cout<<"\nNivel 3......3";
    cout<<"\nSalir........4";
    cout<<"\nElige una opcion: ";
    cin>>opcion;
    if(cin.fail()){ // Si la entrada no es un numero
      cin.clear(); // Limpiar estado de error de cin
      cin.ignore(1000,'\n'); // Descartar entrada inválida hasta mil caracteres o hasta encontrar un salto de línea
    } 
    else if(fmod(opcion,1)!=0) cout<<" "; // Descartar numeros con decimales 
    else opc=static_cast<int>(opcion); // convertir opcion a entero para que pueda ser evaluado por switch
    switch(opc){
          case 1: jugarNivel1(); break;
          case 2: jugarNivel2(); break;
          case 3: jugarNivel3(); break;
          case 4: menuOpciones(); break;
          default: cout<<"Ups! esa opcion es invalida, intenta de nuevo";
    }
  }while(opc!=4);
}

void jugarNivel1(){
  cout<<"Esta funcion no ha sido implementada";
}

void jugarNivel1(){
  cout<<"Esta funcion no ha sido implementada"; 
}

void jugarNivel1(){
  cout<<"Esta funcion no ha sido implementada";   
}