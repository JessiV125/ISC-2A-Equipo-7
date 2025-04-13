#include <iostream>
#include<math.h>
using namespace std;

// 
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
  do{
    cout<<"\nElige una opcion:";
    cout<<"\nNivel 1......1";
    cout<<"\nNivel 2......2";
    cout<<"\nNivel 3......3";
    cout<<"\nSalir........4";
    if(cin.fail()){ // Si la entrada no es un numero
      cin.clear(); // Limpiar estado de error de cin
      cin.ignore(1000,'\n'); // Descartar entrada inválida hasta mil caracteres o hasta encontrar un salto de línea
    } 
    else if(fmod(opcion,1)!=0) cout<<" "; // Descartar numeros con decimales 
    else opc=static_cast<int>(opcion); // convertir opcion a entero para que pueda ser evaluado por switch
    switch(opc){
          case 1: jugarNivel1();
          case 2: jugarNivel2();
          case 3: jugarNivel3();
          case 4: menuOpciones();
          default: cout<<"Ups! esa opcion es invalida, intenta de nuevo";
    }
  }while(opc!=4);
}