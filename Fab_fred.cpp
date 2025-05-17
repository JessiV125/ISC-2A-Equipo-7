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

// ESTRUCTURAS
struct Usuario{
    char nombre[10];
    char contrasena[20];
};

struct Celda{
	int numero;
	bool encendida;	
};

// VARIABLES GLOBALES
Celda **tablero=NULL;
int tamTablero;
int secuenciaMaxima=0; // Cantidad de veces que se repite la secuencia a memorizar en cada nivel
int puntaje=0;
bool juegoActivo=true; // Interrupor: determina si el juego continua o no dependiendo de si el jugador repite la secuencia correctamente

/* COORD es una estructura de datos definida en la API de windows  |  typedef struct _COORD{
								que representa coordenadas en una pantalla de consola, en este 	|			SHORT X; //Coordenada horizontal (columna)
								programa se usa para manejar posiciones en el tablero 			|		SHORT Y; //Coordenada vertical (fila)
																								|	} COORD;												*/
COORD posicionJugador={0,0}; // Posicion inicial del jugador: esquina superior izquierda
COORD *secuencia=NULL; // Almacena las coordenadas de la secuencia a memorizar
int longitudSecuencia=1; // Numero de casillas que se encienden por secuencia, aumenta si el jugador rpepite la secuencia correctamente
int pasoActual=0; // Determina el elemento de la secuencia que el jugador debe repetir


// COLORES
enum Colores{AZUL=1, VERDE, CIAN, ROJO, MAGENTA, AMARILLO, BLANCO};

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
  srand(time(NULL));
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


// FUNCIONES PARA JUGAR

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

// Hace llamdas a otras funciones para crear el tablero y jugar
void jugarNiveles(int nivel){	
	// Determinar tamaño del tablero en base al nivel
	if(nivel==1){
		tamTablero=3;
		secuenciaMaxima=10;
		secuencia=new COORD[secuenciaMaxima];
	} 
	else if(nivel==2){
		tamTablero=5;
		secuenciaMaxima=15;	
		secuencia=new COORD[secuenciaMaxima];
	} 
	else if(nivel==3){
		tamTablero=7;
		secuenciaMaxima=20;	
		secuencia=new COORD[secuenciaMaxima];
	} 

	//Reiniciar estado para nuevo juego nuevo nivel
	longitudSecuencia=1;
	puntaje=0; 
	juegoActivo=true;
	pasoActual=0;
	
	// Inicializar tablero
	eliminarTablero(); 
	crearTablero();
	inicializarTablero();
	
	while(juegoActivo){
		// Reiniciar estado para nuevo nivel
		posicionJugador={0,0};
		pasoActual=0;
		
		generarSecuencia();
		
		if(!juegoActivo) break; // Terminar el juego si el jugador no repite la secuencia correctamente
		
		mostrarSecuencia();
		dibujarTablero();
		
		bool secuenciaCompleta=false; // indica si la secuencia se repitió correctamente
		while(!secuenciaCompleta && juegoActivo){ // Mientras la secuencia no llegue al maximo y el jugador no se equivoque al repetirla
			if(_kbhit()){ // _kbhit() verifica si hay una entrada del teclado
				int tecla=_getch(); // _getch() lee la tecla y obtiene su código. Si no se usa después de _kbhit() la tecla queda en el buffer
				
				if(tecla==0xE0){ // La primer llamada a _getch() retorna 0xE0 que indica que se presionó una tecla especial (flechas, inicio...)
					tecla=_getch(); // La segunda llamada a _getch() retorna el código real de la tecla	
					moverJugador(tecla);
					dibujarTablero();
				} 	
				
				else if(tecla==13){ // 13 es el código ASCII para la tecla Enter
						secuenciaCompleta=verificarSeleccion();
						dibujarTablero();
						
						if(secuenciaCompleta){
							cout<<"Correcto! Puntaje: "<<puntaje<<endl;
							cout<<"Secuencia completada correctamente.\n";
							if(longitudSecuencia<secuenciaMaxima){
								cout<<"Preparate para la siguiente secuencia";	
							}
							Sleep(3000);
						}
				}
			}
		}
	}
	
	// AL FINALIZAR EL JUEGO:
	system("cls");
	int opc=0;
	float opcion=0;
	if(longitudSecuencia<secuenciaMaxima){ // Si no completa el nivel
		do{
			cout<<"\nSecuencia incorrecta. Fin del juego";
			cout<<"\nPuntaje alcanzado: "<<puntaje;
			cout<<"\nSecuencia alcanzada: "<<longitudSecuencia-1;
			cout<<"\nRepetir nivel.........1";
			cout<<"\nRegresar..............2";
			cout<<"\nTu eleccion: ";
			cin>>opcion;
			if(cin.fail()){
				cin.clear();
				cin.ignore(1000,'\n');
				system("cls");
				cout<<"Entrada invalida";
				Sleep(2000);
				system("cls");
			}
			else if(fmod(opcion,1)==0) opc=static_cast<int>(opcion);
			switch(opc){
				case 1: jugarNiveles(nivel); return; 
				case 2: eliminarTablero();
						elegirNivel(); return;
			}
		}while(opc!=1 || opc!=2);
	}
	
	else if(nivel==1 || nivel==2){ // Si completa el nivel 1 o 2 
		do{
			cout<<"\nNivel completado";
			cout<<"\nPuntaje alcanzado: "<<puntaje;
			cout<<"\nPasar al siguiente nivel.........1";
			cout<<"\nRegresar.........................2";
			cout<<"\nTu eleccion: ";
			cin>>opcion;
			if(cin.fail()){
				cin.clear();
				cin.ignore(1000,'\n');
				system("cls");
				cout<<"Entrada invalida";
				Sleep(2000);
				system("cls");
			}
			else if(fmod(opcion,1)==0) opc=static_cast<int>(opcion);
			else{
				system("cls");
				cout<<"Entrada invalida";
				Sleep(2000);
				system("cls");	
			}
			switch(opc){
				case 1: eliminarTablero();
						jugarNiveles(nivel+1); return;  // Siguiente nivel
				case 2: eliminarTablero();
						elegirNivel(); return;
			}
		}while(opc!=1 || opc!=2);
	}
	
	else{ // Si completa el nivel 3
		do{
			cout<<"\nNivel completado";
			cout<<"\nPuntaje alcanzado: "<<puntaje;
			cout<<"\nRegresar.............1";
			cout<<"\nTu eleccion: ";
			cin>>opcion;
			if(cin.fail()){
				cin.clear();
				cin.ignore(1000,'\n');
				system("cls");
				cout<<"Entrada invalida";
				Sleep(2000);
				system("cls");
			}
			else if(opcion==1){
				eliminarTablero();
				elegirNivel();
				return;
			} 
			else{
				system("cls");
				cout<<"Entrada invalida";
				Sleep(2000);
				system("cls");	
			}
		}while(opcion!=1);
	}
}


/* Crea el tablero con diferentes tamaños
 dependiendo del nivel que se juega */
void crearTablero(){	
	tablero=new Celda*[tamTablero]; // Renglones 
	for(int i=0; i<tamTablero; i++){ // Columnas
		tablero[i]=new Celda[tamTablero];
	}
}

// Inicializa el tablero
void inicializarTablero(){
	for(int i=0; i<tamTablero; i++){
		for(int j=0; j<tamTablero; j++){
			tablero[i][j].numero=i*tamTablero+j+1;
			tablero[i][j].encendida=false;
		}
	}	
}

// Genera la(s) posicione(s) de la(s) casilla(s) a encender
void generarSecuencia(){
	if(longitudSecuencia>secuenciaMaxima){ // Terminar juego si se repite toda la secuencia
		juegoActivo=false; 
		return;
	}		
	
	
	for(int i=0; i<longitudSecuencia; i++){ // Posicion de la casilla a encender 
		bool repetida;
		do{
			repetida=false;
			secuencia[i].X=rand()%tamTablero;
			secuencia[i].Y=rand()%tamTablero;
			
			/* Verificar que la secuencia sea única para evitar 
			problemas en el seguimiento de la secuencia */
			for(int j=0; j<i; j++){
				if(secuencia[i].X == secuencia[j].X && secuencia[i].Y == secuencia[j].Y) repetida=true; break;
			}
		}while(repetida);	
	}	
}

// Enciende las celdas y llama a dibujarTablero
void mostrarSecuencia(){
	system("cls");	
	for(int i=0; i<longitudSecuencia; i++){
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
void dibujarTablero(){
	system("cls");
	// Encabezado
	if(secuenciaMaxima==10) cout<<"\tNIVEL 1"<<endl;
	else if(secuenciaMaxima==15) cout<<"\tNIVEL 2"<<endl;
	else cout<<"\tNIVEL 3"<<endl;
	cout<<"Puntaje: "<<puntaje<<"  |  Secuencia: "<<longitudSecuencia<<"/"<<secuenciaMaxima<<endl<<endl;
	
	for(int i=0; i<tamTablero; i++){
		for(int j=0; j<tamTablero; j++){
			// Mostrar secuencia
			if(tablero[i][j].encendida){
				int color=1+(rand()%6); // Generar color para las casillas
				switch(color){
					case 1: SetConsoleTextAttribute(hConsole, AZUL); break;
					case 2: SetConsoleTextAttribute(hConsole, VERDE); break;
					case 3: SetConsoleTextAttribute(hConsole, CIAN); break;
					case 4: SetConsoleTextAttribute(hConsole, ROJO); break;
					case 5: SetConsoleTextAttribute(hConsole, MAGENTA); break;
					case 6: SetConsoleTextAttribute(hConsole, AMARILLO); break;
				}
				cout<<"[";
				if(tablero[i][j].numero<10) cout<<" ";
				cout<<tablero[i][j].numero<<"]";
			}
			
			// Mostrar posición del jugador en el tablero
			else{
				SetConsoleTextAttribute(hConsole, BLANCO);
				cout<<"[";
				if(posicionJugador.X==j && posicionJugador.Y==i){ // Casilla en la que se ubica el jugador
					SetConsoleTextAttribute(hConsole, 240); // Fondo blanco, texto negro
					cout<<" X";
				}
				else cout<<"  "; // Casillas en las que no está el jugador
				cout<<"]";
			}
			SetConsoleTextAttribute(hConsole, BLANCO);
		}
		cout<<endl;
	}
	
}

// Mueve al jugador en el tablero dependiendo de la flecha preionada en teclado
void moverJugador(int tecla){
	switch(tecla){
		case 75: if(posicionJugador.X>0) posicionJugador.X--; break; 			// Izquierda
		case 77: if(posicionJugador.X<tamTablero-1) posicionJugador.X++; break; // Derecha
		case 72: if(posicionJugador.Y>0) posicionJugador.Y--; break; 			// Arriba
		case 80: if(posicionJugador.Y<tamTablero-1) posicionJugador.Y++; break; // Abajo
	}	
}

bool verificarSeleccion(){
	if(posicionJugador.X==secuencia[pasoActual].X && posicionJugador.Y==secuencia[pasoActual].Y){
		
		pasoActual++;
		
		if(pasoActual>=longitudSecuencia){
			puntaje+=longitudSecuencia*10;
			longitudSecuencia++;
			pasoActual=0;
			return true;
		}
	}	
	else juegoActivo=false;
	return false;
}

/* Libera el espacio en memoeria que ocupa el tablero actual
	para crear otro con otro tamaño dependiendo del nivel
	que el usuario desee jugar
*/
void eliminarTablero(){
	if(tablero!=NULL){ 
		// Eliminar columnas
		for(int i=0; i<tamTablero; i++){
			delete[] tablero[i]; 
		}
	
		// Eliminar filas
		delete[] tablero;
		
		tablero=NULL;		
	}
}