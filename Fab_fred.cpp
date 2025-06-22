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
const int MAX = 100;

// Obtener manejador de consola
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

// ESTRUCTURAS
struct Usuario{
    char nombre[10];
    char contrasena[20];
	int puntajeMejor;
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
void MostrarMenu(Usuario[], int&, int);
//registro
void iniciarSesion(Usuario usuarios[], int tope);
void realizarRegistro(Usuario[], int&, int);
bool buscarUsuarios(Usuario[], int, const char*, const char* = nullptr);
bool cumpleRequisitosUsuario(const char*);
bool cumpleRequisitosContrasena(const char*);
int cargarUsuariosDesdeArchivo(Usuario[], int);


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

int main(){
  srand(time(NULL));
  cout << "Proyecto FRED";
  MostrarMenu();
  Usuario usuarios[MAX]; //Arreglo de usuarios inicializado
  int tope = cargarUsuariosDesdeArchivo(usuarios, MAX);

  iniciarSesion(usuarios, tope);    //  Pasar el arreglo de usuarios
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
  system("pause"); // Pausar ejecución antes de limpiar la pantalla 
  system("cls"); // Limpiar la pantalla
}

void iniciarSesion(Usuario usuarios[], int tope) {
    char nombre[50];
    char contrasena[50];

    while (true) {
        cout << "\nNombre de usuario: ";
        cin >> nombre;
        cout << "Contrasena: ";
        cin >> contrasena;

		if (buscarUsuarios(usuarios, tope, nombre, contrasena)) {   // Busca el usuario y contrasena
            cout << "Inicio de sesion exitoso.\n";
            MostrarMenu();
            break;
        }
        else {
            cout << "Nombre o contrasena incorrectos.\n";
            char opcion;
            cout << "Deseas intentar de nuevo? (s/n): ";
            cin >> opcion;  
            if (opcion == 'n' || opcion == 'N') {
				MostrarMenu(usuarios, tope, 100); // Regresa al inicio
                break;
            }
        }
    }
}
// Validacion de nombre
bool cumpleRequisitosUsuario(const char* nombre) {  
	return strlen(nombre) >= 3;     // Verifica que el nombre tenga al menos 3 caracteres
}

// Validacion de contrasena
bool cumpleRequisitosContrasena(const char* contra) {
	if (strlen(contra) < 6) return false;       // Verifica longitud minima de 6 caracteres

    bool mayus = false, minus = false, numero = false;
    for (int i = 0; contra[i]; i++) {
		if (isupper(contra[i])) mayus = true;   // Verifica mayusculas
		if (islower(contra[i])) minus = true;   // Verifica minusculas
		if (isdigit(contra[i])) numero = true;  // Verifica numeros
    }
	return mayus && minus && numero;    // Verifica que tenga al menos una mayuscula, una minuscula y un numero
}


// Buscar por nombre o nombre y contrasena
bool buscarUsuarios(Usuario usuarios[], int tope, const char nombre[], const char* contrasena) {
	for (int i = 0; i < tope; i++) {    // Recorre el arreglo de usuarios
		if (strcmp(usuarios[i].nombre, nombre) == 0) {  // Compara el nombre
			if (contrasena == nullptr || strcmp(usuarios[i].contrasena, contrasena) == 0) { // Compara la contrasena si se proporciona
                return true;
            }
        }
    }
    return false;
}

// Cargar usuarios desde archivo
int cargarUsuariosDesdeArchivo(Usuario usuarios[], int maxUsuarios) {
    FILE* archivo = fopen("usuarios.txt", "r");
    if (!archivo) return 0;

    int i = 0;
	while (fscanf(archivo, "%s %s", usuarios[i].nombre, usuarios[i].contrasena) != EOF && i < maxUsuarios) {    // Lee el archivo
        i++;
    }
    fclose(archivo);
    return i;
}



// Funcion 3: Registro con validaciones y decisiones
void realizarRegistro(Usuario usuarios[], int& tope, int maxUsuarios) {
    char nombre[50], contrasena[50];

    while (true) {
        cout << "\nNombre de usuario (minimo 3 letras): ";
        cin >> nombre;
        cout << "Contrasena (minimo 6 caracteres, 1 mayuscula, 1 minuscula, 1 numero): ";
        cin >> contrasena;

		if (!cumpleRequisitosUsuario(nombre) || !cumpleRequisitosContrasena(contrasena)) {  // Verifica requisitos
            cout << "El usuario o contrasena no cumplen los requisitos. Intenta de nuevo.\n";
            continue;
        }

		if (buscarUsuarios(usuarios, tope, nombre)) {   // Verifica si el usuario ya existe
            cout << "El usuario ya existe.\n";
            cout << "1. Ingresar otro usuario\n";
            cout << "2. Iniciar sesion\n";
            cout << "3. Salir\n";
            int opcion;
            cin >> opcion;
            if (opcion == 1) continue;
            else if (opcion == 2) {
				iniciarSesion(usuarios, tope);  // Inicia sesion
                break;
            }
            else {
                MostrarMenu(usuarios, tope, maxUsuarios);
                break;
            }
        }
        else {
            // Guardar en arreglo y archivo
			strcpy(usuarios[tope].nombre, nombre);  // Copia el nombre al arreglo
			strcpy(usuarios[tope].contrasena, contrasena);  // Copia la contrasena al arreglo
            FILE* archivo = fopen("usuarios.txt", "a");
            if (archivo) {
                fprintf(archivo, "%s %s\n", nombre, contrasena);
                fclose(archivo);
            }
            tope++;

            cout << "Registro exitoso.\n";
            cout << "1. Ingresar otro usuario\n";
            cout << "2. Iniciar sesion\n";
            cout << "3. Salir\n";
            int opcion;
            cin >> opcion;
			if (opcion == 1) continue;  // Permite ingresar otro usuario
			else if (opcion == 2) {     // Inicia sesion
                iniciarSesion(usuarios, tope);
                break;
            }
            else {
                MostrarMenu(usuarios, tope, maxUsuarios);
                break;
            }
        }
    }
}


// FUNCIONES PARA JUGAR

/*
  -Explica reglas del juego
  -Tiene un menú y da a elegir entre 3 niveles
*/
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
    	
    	// Verificar entrada de opcion
    	if(cin.fail()){ // Si la entrada no es un numero
      		cin.clear(); // Limpiar estado de error de cin
      		cin.ignore(1000,'\n'); // Descartar entrada inválida hasta mil caracteres o hasta encontrar un salto de línea
    	} 
    	else if(fmod(opcion,1) == 0) opc=static_cast<int>(opcion); // Descartar numeros con decimales // convertir opcion a entero para que pueda ser evaluado por switch

		switch(opc){
        	case 1: jugarNiveles(opc); break; // La funcion recibe opc con el nombre de nivel
          case 2: jugarNiveles(opc); break;
          case 3: jugarNiveles(opc); break;
		  case 4: mostrarAyuda(); break;
		  case 5: system("cls");
					MostrarMenu(); break;
          default: cout<<"Ups! esa opcion es invalida, intenta de nuevo";
					Sleep(1500);
					system("cls");
    	}
	}while(opc != 5);
}

// Controla la lógica principal del juego
void jugarNiveles(int nivel) {	
	// Determinar tamaño del tablero en base al nivel
	if(nivel == 1) {
		tamTablero = 3;
		secuenciaMaxima = 9;
		secuencia = new COORD[secuenciaMaxima];
	} 
	else if(nivel == 2) {
		tamTablero = 5;
		secuenciaMaxima = 25;	
		secuencia = new COORD[secuenciaMaxima];
	} 
	else if(nivel == 3) {
		tamTablero = 7;
		secuenciaMaxima = 49;	
		secuencia = new COORD[secuenciaMaxima];
	} 

	//Reiniciar estado para nuevo juego nuevo nivel
	longitudSecuencia = 1;
	puntaje = 0; 
	juegoActivo = true;
	pasoActual = 0;
	
	// Inicializar tablero
	eliminarTablero(); 
	crearTablero();
	inicializarTablero();

	generarSecuencia();
	
	while(juegoActivo) {
		// Reiniciar estado para nuevo nivel
		posicionJugador = {0,0};
		pasoActual = 0;
		
		if(!juegoActivo) break; // Terminar el juego si el jugador no repite la secuencia correctamente
		
		mostrarSecuencia();
		dibujarTablero();
		
		bool secuenciaCompleta = false; // indica si la secuencia se repitió correctamente
		while(!secuenciaCompleta && juegoActivo){ // Mientras la secuencia no llegue al maximo y el jugador no se equivoque al repetirla
			if(_kbhit()){ // _kbhit() verifica si hay una entrada del teclado
				int tecla = _getch(); // _getch() lee la tecla y obtiene su código. Si no se usa después de _kbhit() la tecla queda en el buffer
				
				// Mover al jugador 
				if(tecla == 0xE0) { // La primer llamada a _getch() retorna 0xE0 que indica que se presionó una tecla especial (flecha)
					tecla = _getch(); // La segunda llamada a _getch() retorna el código real de la tecla	
					moverJugador(tecla);
					dibujarTablero();
				} 	
				
				// Selección de casilla 
				else if(tecla == 13) { // Si es la tecla enter 
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

				// Volver al menú de niveles 
				else if(tecla == 86 || tecla == 118) { // Si es V mayúscula o v minúscula 
					elegirNivel();
				}

				// Mostrar ayuda por si no recuerdan cómo jugar 
				else if(tecla == 65 || tecla == 97) { // Si es A mayúscula o a minúscula 
					mostrarAyuda();
					mostrarSecuencia();
					dibujarTablero();
				}
				
				// Guardar la partida 
				else if(tecla == 71 || tecla == 103) { // Si es G mayúscula o g minúscula
					guardarPartida();
				}
			}
		}
	}
}

/* Función: guardarPuntaje
   Propósito: Guarda el puntaje obtenido en la partida actual y registra en el historial
   Parámetros: Ninguno
   Valor de retorno: Ninguno */
void guardarPuntaje() {
    // 1. Guardar en archivo de mejores puntajes (original)
    FILE* archivoPuntajes = fopen("mejores_puntajes.txt", "a");
    if(archivoPuntajes != NULL) {
        fprintf(archivoPuntajes, "%s %d\n", nombreJugadorActual, puntaje);
        fclose(archivoPuntajes);
    }

    // 2. Actualizar mejor puntaje del jugador (nuevo)
    Usuario usuarios[MAX];
    int cantidadUsuarios = cargarUsuariosDesdeArchivo(usuarios, MAX);
    
    for(int i = 0; i < cantidadUsuarios; i++) {
        if(strcmp(usuarios[i].nombre, nombreJugadorActual) == 0) {
            if(puntaje > usuarios[i].puntajeMejor) {
                usuarios[i].puntajeMejor = puntaje;
                
                // Actualizar archivo de usuarios
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

    // 3. Guardar en archivo de historial (nuevo)
    FILE* archivoHistorial = fopen("historial_jugadas.txt", "a");
    if(archivoHistorial != NULL) {
        // Obtener fecha y hora actual
        time_t ahora = time(NULL);
        struct tm* tiempoLocal = localtime(&ahora);
        char fechaHora[20];
        strftime(fechaHora, sizeof(fechaHora), "%Y-%m-%d %H:%M:%S", tiempoLocal);
        
        // Determinar nivel actual
        int nivel;
        if(tamTablero == 3) nivel = 1;
        else if(tamTablero == 5) nivel = 2;
        else nivel = 3;
        
        // Guardar registro de historial
        fprintf(archivoHistorial, "%s %d %d %s\n", 
                nombreJugadorActual, 
                nivel, 
                puntaje, 
                fechaHora);
        fclose(archivoHistorial);
    }
    
    // 4. Mensaje de confirmación (original)
    cout << "\nPuntuacion guardada exitosamente!" << endl;
    Sleep(2000);
}


/* Crea el tablero con diferentes tamaños
 dependiendo del nivel que se juega */
void crearTablero() {	
	tablero = new Celda*[tamTablero]; // Renglones 
	for(int i=0; i<tamTablero; i++) { // Columnas
		tablero[i] = new Celda[tamTablero];
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

// Genera las posiciones alatorias de las cassillas a encender 
void generarSecuencia() {
	if(longitudSecuencia > secuenciaMaxima) { // Terminar juego si se repite toda la secuencia
		juegoActivo = false; 
		return;
	}		
	
	if(longitudSecuencia == 1){
		// Primera ronda: generar la primera posición
		bool repetida;
		do{
			repetida = false;
			secuencia[0].X = rand() % tamTablero;
			secuencia[0].Y = rand() % tamTablero;
		}while(false); // No hay repeticiones en la primera posición
	}
	else{
		// Agregar solo una nueva posición al final
		bool repetida;
		do{
			repetida = false;
			secuencia[longitudSecuencia-1].X = rand() % tamTablero;
			secuencia[longitudSecuencia-1].Y = rand() % tamTablero;
			
			// Verificar que la nueva posición no sea igual a alguna de las anteriores
			for(int j = 0; j < longitudSecuencia-1; j++){
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
	if(secuenciaMaxima == 25) cout << "\tNIVEL 1" << endl;
	else if(secuenciaMaxima == 49) cout << "\tNIVEL 2" << endl;
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

/* Libera el espacio en memoeria que ocupa el tablero actual
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