Cronograma de trabajo: https://eduuaa-my.sharepoint.com/:w:/g/personal/al281957_edu_uaa_mx/Eap6kzy8KjtIpgP-69OantgBVSZ_-efoKTDCaI-Qp_aqcQ?e=5MiaZc

Requsitos para el proyecto (marcar lo que se vaya completando): https://docs.google.com/document/d/1JMDPM7sRZwU58qVjIj_MWZH-BtW1Spc6Jvyumx-W_Jw/edit?usp=sharing

FUNCIONES PARA fabFred (modificar y agregar según sea necesario)

mostrarBienvenida: 

    Única función que se llama desde la función main
    
    LLama a las funciones mostrarMejoresPuntajes y mostrarInicio

    
mostrarMejoresPuntajes

    Muestra el historial de jugadores (mejores puntajes)

    
mostrarInicio:

    Pregunta si se desea comenzar el juego
    
          Si: pregunta si ya tienen cuenta
          
              Sí: llama a iniciarSesión
              
              No: llama a realizarRegistro
              
          No: Fin de programa

          
iniciarSesion:

      El usuario ingresa nombre y contraseña
      
      Verifica que el usuario exista y la contraseña sea correcta
      
          Si: llama a menuOpciones
          
          No: muestra mensaje de error y vuelve a preguntar si tiene cuenta

      Tiene opción de salir: llama a mostrarInicio.


realizarRegistro:

      El usuario ingresa nombre y contraseña (indica requisitos de nombre y contraseña)
  
      Verifica que el usuario y contraseña cumplan con los requisitos:

          Si: continua
          
          No: muestra mensaje de error y vuelve a pedir los datos
      
      Verifica si el usuario existe:
          
          Sí: indica que el usuario ya existe y ofrece tres opciones:
              
              Ingresar otro usuario

              Iniciar sesión: llama a iniciarSesión
              
              Salir: llama a mostrarInicio

          No: muestra mensaje de registro exitoso y ofrece tres opciones: 

              Ingresar otro usuario

              Iniciar sesión: llama a iniciarSesión

              Salir: llama a mostrarInicio


menuOpciones: 
      
      Muestra tres opciones: 
          
          Ver historial del usuario (jugador): llama a mostrarHistorial
          
          Comenzar juego: llama a elegirNivel

          Ver historial de jugadores: llama a mostrarMejoresPuntajes y luego llama a volverMenu.

      Tiene opción de salir: llama a mostrarInicio


mostrarHistorial:
      
      Muestra historial de las jugadas del usuario (si se acaba de registrar, le indica que aún no hay historial)
      
      Tiene opción de atrás: llama a menuOpciones


elegirNivel:
     
      Explica reglas del juego
      
      Tiene un menú y da a elegir entre 3 niveles:
      
      Tiene opción de atrás: llama a menuOpciones


jugarNiveles:    

        Hace llamada a otras funciones para crear tbelro y jugar.

crearTablero:

        Crea el tablero del juego con diferentes tamaños dependiendo del nivel que se juega.

inicializarTablero:

        iniciliza el tablero

generarSecuencia:

        Genera la(s) posicione(s) de la(s) casilla(s) a encender

mostrarSecuencia:

        Enciende las celdas y llama a dibujarTablero

dibujarTablero:

        Dibuja el tablero para mostrar la secuencia a repetir o la posicion en la que se ubica el jugador para repetir la secuencia

moverJugador:

        Mueve al jugador en el tablero dependiendo de la flecha preionada en teclado

verificarSeleccion:
        Comprueba la seleccion del jugador

void eliminarTablero:
        Libera el espacio en memoeria que ocupa el tablero actual para crear otro con otro tamaño dependiendo del nivel que el usuario desee jugar
