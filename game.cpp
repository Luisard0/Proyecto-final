#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
//--------- Hangman game -------------------
//Escoge una palbra de un vector de palabras
string choose_palabra(const vector<string>& listaPalabras){
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % listaPalabras.size();
    return listaPalabras[randomIndex];
}

//Reviza si la palabra ha sido adivinada
bool palabraAdivinada(const string& palabra_secreta, const vector<char>& letras_adivinadas){
    vector<char> lista;
        for (char letter : palabra_secreta) {
        if (find(letras_adivinadas.begin(), letras_adivinadas.end(), letter) != letras_adivinadas.end()) {
            lista.push_back(letter);
            }
        }
    return palabra_secreta.length()==lista.size();
}

//Devuelve una cadena comprendida por guiones bajos y letras de la palabra que se intenta adivinar
string get_palabraAdivinada(const string& palabra_secreta, const vector<char>& letras_adivinadas){
   string cadena="";
   for (char letra: palabra_secreta){
    if (find(letras_adivinadas.begin(), letras_adivinadas.end(), letra) != letras_adivinadas.end()){
        cadena+=letra;
    }else{
        cadena+="_ ";
    }
   }
    return cadena;
}

//Devuleve una cadena con las letras disponibles
string get_letrasDisponibles(const vector<char>& letras_adivinadas){
   string abecedario = "abcdefghijklmnopqrstuvwxyz"; //sin ñ
   for (char letra:letras_adivinadas){
    if (isalpha(letra)){ //si letra está en abecedario actualizamos 
        size_t pos = abecedario.find(letra);
        if (pos != string::npos){
            abecedario.erase(pos,1);
        }
    }
   }
   return abecedario;
}

//hangman (ahorcado)
bool hangman(const string& palabra_secreta){
    int intentos = 6;
    int advertencias = 3;
    vector<char> letras_unicas;
    vector<char> lista_letras;
    string vocales = "aeiou";
    string guess;
    cout<<"\nBienvenido al juego del ahoracado!!! \n";
    cout<<"Estoy pensando en una palabra secreta que tiene "<<palabra_secreta.length()<<" letras\n";
    cout<<"Te quedan "<<advertencias<<" advertencias.\n";
    cout<<"Si la letra que pones no está en la palabra secreta y es una vocal pierdes dos intentos pero si es una consonante solo pierdes un solo intento\n";
    cout<<"-----------------------------\n";
    //Calcula las letras unicas de la palabra secreta
    for(char letra : palabra_secreta){
        if(find(letras_unicas.begin(), letras_unicas.end(), letra) == letras_unicas.end()){
            letras_unicas.push_back(letra);
        }
    }

    //Game
    while (true){
        //Validación del imput
        while (true){
            try{
                if (intentos>0){
                    //Pide la letra
                    cout<<"Te quedan "<<intentos<<" intentos\n";
                    cout<<"Letras disponibles: "<<get_letrasDisponibles(lista_letras)<<endl;
                    cout<<"Por favor, adivine una letra:  ";
                    cin>>guess;

                    //Pregunta si solo es un caracter
                    if (guess.length() == 1){
                        if (advertencias > 0){
                            //pregunta si la conjetura es una letra (ya sea mayuscula o minuscula)
                            if (isalpha(guess[0])){
                                //Pregunta si ya está en la lista de letras ya usadas
                                if (find(lista_letras.begin(), lista_letras.end(), guess[0]) != lista_letras.end()){
                                    advertencias--;
                                    cout<<"Opps, Ya has usado esa letra. Te quedan "<<advertencias<<" advertencias restantes: \n";
                                    cout<<get_palabraAdivinada(palabra_secreta, lista_letras)<<endl;
                                    cout<<"-------------------------------------------------------------------"<<endl;
                                    continue;
                                }else{
                                    guess[0] = tolower(guess[0]);
                                    lista_letras.push_back(guess[0]);
                                    break;
                                }
                            }else{
                                advertencias--;
                                cout<<"Opps !, "<<guess<<" no es valido. Te quedan "<<advertencias<<" advertencias:  "<<get_palabraAdivinada(palabra_secreta, lista_letras)<<endl;
                                cout<<"-----------------------------\n";
                                continue;
                            }
                            
                        }else{ //Las advertencias son 0
                            if (isalpha(guess[0])){
                                if (find(lista_letras.begin(), lista_letras.end(), guess[0]) != lista_letras.end()){
                                    cout<<"Opps!, ya has usado esa letra. Te has quedado sin advertencias, perderas un intento\n";
                                    intentos--;
                                    cout<<get_palabraAdivinada(palabra_secreta, lista_letras)<<endl;
                                    cout<<"-----------------------------\n";
                                    continue;
                                }else{
                                    guess[0] = tolower(guess[0]);
                                    lista_letras.push_back(guess[0]);
                                    break;
                                }
                                
                            }else{
                                cout<<"Opps! "<<guess<<" no es valido. Has perdido tus advertencias entonces se te restará un intento\n";
                                cout<<get_palabraAdivinada(palabra_secreta, lista_letras)<<endl;
                                cout<<"-----------------------------\n";
                                intentos--;
                                continue;
                            }
                        }
                    }else{
                        cout<<"Solo se ascepta un caracter a la vez\n";
                        continue;
                    }
                }else{
                    //Pierde por acabarse los intentos
                    break;
                }
            }
            catch(...){
                cout<<"Error: validación de input\n";
            }
            
        }//termina la validación de input
        
        //Logica del juego

        //Pierde porque se le acabaron los intentos
        if (intentos == 0){
            cout<<"Lo siento, se te han acabado los intentos. La palabra era: "<<palabra_secreta<<endl;
            return false;
            break;
        }else if (palabra_secreta.find(guess[0]) != string::npos){
            if (palabraAdivinada(palabra_secreta, lista_letras)){//pregunta si están todas las letras de la palabra secreta en la lista de letras ya adivinadas
                cout<<"Muy bien: "<<get_palabraAdivinada(palabra_secreta, lista_letras)<<endl;
                cout<<"-----------------------------\n";
                cout<<"Felicidades, ganaste !!!\n";
                //Score = intentos restantes * numero de letras unicas en la palabra secreta
                int score = intentos * letras_unicas.size();
                cout<<"Tu puntuacion final es: "<<score<<endl;
                return true;
                break;
            }else{
                cout<<"Muy bien: "<<get_palabraAdivinada(palabra_secreta, lista_letras)<<endl;}
        }else{ //Perdida de intentos por no adivinar la letra correcta
            if (vocales.find(guess[0]) != string::npos){//si la conjetura es una vocal que no está en la palabra secreta pierde dos intentos
                cout<<"Opps!!, "<<guess[0]<<" no esta en la palabra secreta  "<<get_palabraAdivinada(palabra_secreta, lista_letras)<<endl;
                intentos-=2;
            }else{ //si la conjetura es una consonante que no está en la palabra secreta pierde un solo intentos
                cout<<"Opps!, "<<guess[0]<<" no esta en la palabra secreta  "<<get_palabraAdivinada(palabra_secreta, lista_letras)<<endl;
                intentos-=1;
            }   
        }cout<<"-----------------------------\n";
    }
}
//----------hangman game ---------------------

//------Piedra, papel o tijeras game----------

// Decide que va a jugar (1:Piedra, 2: Papel, 3: Tijeras)
int manoUsuario(){
    int eleccion;

    while (true){
        cout<<"Elige una opcion (1: Piedra, 2: Papel, 3: Tijeras):  \n";
        cin>>eleccion;

        if (eleccion == 1 || eleccion==2 || eleccion==3){
            break;
        }else{
            cout<<"Opcion no valida :/\n";
        }
        
    }
    return eleccion;
}

//La computadora escoge que va a jugar (1:Piedra, 2: Papel, 3:Tijera)
int manoComputadora(){
    //Genera número aleatorio entre 1 y 4
    return rand() % 4 + 1;
}

//Determina quien es el ganador basado en las reglas del juego, verdadero si el usario gana, falso de otro modo
bool determinarGanador(int usuario, int computadora){
    cout<<"La computadora eligio: ";
    switch (computadora)
    {
    case 1:
        cout<<"Piedra\n";
        break;
    case 2:
        cout<<"Papel\n";
        break;
    case 3:
        cout<<"Tijera\n";
        break;
    case 4:
        cout<<"Bomba Nuclear :3\n";
        break;
    default:
        cout<<"Opcion aun no validada\n";
        break;
    }


    cout<<"Tu elegiste: ";
    switch (usuario)
    {
    case 1:
        cout<<"Piedra\n";
        break;
    case 2:
        cout<<"Papel\n";
        break;
    case 3:
        cout<<"Tijera\n";
        break;
    default:
        cout<<"Opcion aun no validada\n";
        break;
    }

    //Determina ganador
    if(usuario == computadora){
        cout<<"Es un empate\n";
        return false;
    }else if ((usuario == 1 && computadora == 3) ||
               (usuario == 2 && computadora == 1) ||
               (usuario == 3 && computadora == 2)) {
        cout << "¡Ganaste!" << endl;
        return true;
    } else {
        cout << "¡La computadora gana!" << endl;
        return false;
    }
}

//Juego Piedra, Papel o Tiejeras, verdadero si logró ganar el juego, falso de otra manera
bool piedraPapelTijeras(int dificultad){
    // Configurar la semilla para generar números aleatorios
    srand(static_cast<unsigned int>(time(0)));

    cout<<"---------------------------------\n";
    cout << "\nBienvenido al juego de Piedra, Papel o Tijeras." << endl;
    cout << "Victorias necesarias para ganar: 3"<<endl;
    cout<<"Los empates seran considerados como derrotas :c"<<endl;
    cout<<"---------------------------------";
    int victorias = 0;
    int round = 1; 
    int necesarias;


    //Dependiendo de la dificultad se necesitarás más o menos victorias
    if (dificultad==1){
        necesarias=1;
    }else{
        necesarias=3;
    }
    
    while (victorias<necesarias){
        cout<<"\nRound: "<< round<<endl;
        round++;
        if(victorias==necesarias-1){
            cout<<"Solo una victoria mas...:\n" ;
        }else if (victorias>=0){
            cout<<"Victorias actuales: "<<victorias<<endl;
        }else{
            cout<<"Perdiendo :c\n";
        }
        
        int usuario = manoUsuario();
        int computadora = manoComputadora();
        //int computadora = 2; //prueba
        if(determinarGanador(usuario,computadora)){
            victorias++;
        }else{
            victorias--;
        }

        if(victorias<-1){
            cout<<"Has sido derrotado :c\n";
            break;
        }
        cout<<"---------------------------------\n";
    }
    cout<<"Gracias por jugar\n";
    if(victorias==3){
        return true;
    }else{return false;
    }
    
}

//------piedra, papel o tijeras game----------

//---------Batalla por turnos game-------------

// Ataque del enemigo y player
//Turno solo puede ser 1 o 2; 1 para player y 2 para el enemigo
int atacar(int turno) {
    if (turno % 2 == 0){
        return rand() % 30 +1; //Ataque enemigo
    }else{
        return rand() % 45 +1; //Ataque jugador
    }
}

//Defensa del enemigo y del player
int defensa(int turno){
    if (turno%2 == 0){
        return rand() % 45 +1; //defensa del enemigo
    }else{
        return rand() % 35 +1; //defensa del player
    }
}

// Batalla por turnos, si gana true de otra forma false
bool batallaPorTurnos(string nomPersonaje,string nomEnemigo, int dificultad, int sanasana,int sanasanaMAX,int repuestos, int ataqueMortal) {
    //Inicializa Items
    int vidaRana = sanasana;
    int vidaSapo = sanasanaMAX;
    int escudos = repuestos;
    int golpeDefinitivo = ataqueMortal;

    // Configurar la semilla para generar números aleatorios
    srand(static_cast<unsigned int>(time(0)));
    
    // Puntos de vida iniciales
    int vidaUsuario = 100;
    int vidaComputadora; //Dependen de la dificultad
    //Ataque y defensa
    int ataquePlayer = 0, ataqueEnemy = 0;
    int defensaPlayer = defensa(3), defensaEnemy;
    // Dependiendo de la dificultad se le asignará más o menos vida al enemigo
    if (dificultad == 1){
        //modo facil
        vidaComputadora = 75;
        defensaEnemy = 75;
    }else{
        //modo dificil
        vidaComputadora = 100;
        defensaEnemy = 200;
    }
    //turno
    int turno = 1;
    int op;//Opcion del jugador y el enemigo
    //Pelea a muerte
    cout<<"\n\n***************************************************\n";
    cout<<"\tLa batalla contra "<<nomEnemigo<<" ha empezado\n";
    cout<<"***************************************************\n";

    while (vidaUsuario > 0 && vidaComputadora > 0) {
        //Muestra información basica
        cout<<"**Turno: "<<turno<<endl;
        cout<<"Vida de "<<nomPersonaje<<" = "<<vidaUsuario<<"\t\tDefensa de "<<nomPersonaje<<" = "<<defensaPlayer<<endl;
        cout<<"Vida de "<<nomEnemigo<<" = "<<vidaComputadora << "\t\tDefensa de "<<nomEnemigo<<" = "<<defensaEnemy<<endl;
        
        //Round impar: turno del player, round par:  turno del enemigo
        if (turno%2 != 0){
            cout<<"\n\n\t\t>>>>> Tu turno <<<<<< \n";
            cout<<"------------------------------------------------------------------------------------\n";
            cout<<"\t\tQue deseas hacer??\n\n1) Atacar\t\t\t2) Reforzar escudo\n\n3) Usar item\t\t\t4) Rendirse\n";
            cout<<"------------------------------------------------------------------------------------\n{>>>} ";
            cin>>op;
            switch (op){
            case 1:
                //Ataque normal
                cout<<"Atacas a "<<nomEnemigo<<endl;
                ataquePlayer=atacar(turno);
                //ataquePlayer=2; //prueba
                if (ataquePlayer<5){//ataque critico
                    cout<<"Ataque critico!!!\n";
                    ataquePlayer=50;
                }
                
                if (defensaEnemy>0){ //le pega al escudo
                    defensaEnemy-=ataquePlayer;
                    cout<<"Has inflijido "<<ataquePlayer<<" puntos de ataque al escudo del enemigo\n";
                    if (defensaEnemy<=0){
                        cout<<"Se ha roto el escudo del enemigo"<<endl;
                        defensaEnemy=0;
                    }else{
                        cout<<"Aun le quedan "<<defensaEnemy<<" puntos de defensa al enemigo\n";
                    }
                }else{ //le pega directamente al enemigo
                    vidaComputadora-=ataquePlayer;
                    cout<<"Has inflijido "<<ataquePlayer<<" puntos de ataque directamente al enemigo\n";
                }
                break;
            case 2:
                //Reforzar escudo
                if (defensaPlayer>=100){
                    cout<<"Intentas reforzar más tu escudo pero terminas lastimandote\n";
                    vidaUsuario-=10;//recoil
                }else{
                    defensaPlayer += defensa(turno);
                    cout<<"Decides reforzar tu escudo\n";
                    cout<<"Tu defensa ha subido a "<<defensaPlayer<<endl;
                }
                break;
            case 3:
                //Menú de items

                cout<<nomPersonaje<<" reivisa sus bolsillos y....";
                if ((escudos+vidaRana+vidaSapo) == 0){
                    cout<<"NO ha encontrado nada :/ \n\t[intenta comprar items en la tienda del menú principal]\n";
                    continue;
                }else{
                    cout<<"Encontro los siguientes Items: \n\n";
                    cout<<"------------------------------------------------------------------------------------\n";
                    cout<<"Escudos: "<<escudos<<"\t\t\t[Aumenta 50 puntos de defensa]\n";
                    cout<<"Pocion de vida: "<<vidaRana<<"\t\t[Aumenta 25 puntos de vida]\n";
                    cout<<"Pocion de vida grande: "<<vidaSapo<<"\t[Aumenta 50 puntos de vida]\n";
                    cout<<"Golpe definitivo: "<<golpeDefinitivo<<"\t\t[Ataque especial que inflije 100 puntos de ataque]\n";
                }
                cout<<"------------------------------------------------------------------------------------\n";
                cout<<"\t\tQue deseas hacer??\n\n1) Usar pocion de vida\t2) Usar poscion de vida grande\t3) Mejorar el escudo\n\n4) Ataque especial\t5) Regresar\n";
                cout<<"------------------------------------------------------------------------------------\n{>>>} ";
                cin>>op;

                if(op == 1){
                    if (vidaRana>0){
                        if (vidaUsuario>=100){
                            cout<<"Ya tienes la vida maxima posible...\n";
                        }else{
                            vidaUsuario+=25;
                            vidaRana--;
                            cout<<"Has usado una pocion de vida\n";
                            cout<<"La vida de "<<nomPersonaje<<" ha subido a: "<<vidaUsuario<<endl;
                        }
                    }else{
                        cout<<"NO tienes pociones de vida disponibles, compra mas en la tienda principal\n";
                    }                    
                }else if (op==2){
                    if (vidaSapo>0){
                        if(vidaUsuario>=100){
                            cout<<"Ya tienes la vida maxima posible...\n";
                        }else{
                            vidaUsuario+=50;
                            vidaSapo--;
                            cout<<"Has usado una pocion de vida grande\n";
                            cout<<"La vida de "<<nomPersonaje<<" ha subido a: "<<vidaUsuario<<endl;
                        }
                    }else{
                        cout<<"NO tienes pociones de vida grande disponibles, adquierelas en la tienda principal\n";
                    }
                }else if (op==3){
                    if (escudos>0){
                        if (defensaPlayer>=150){
                            cout<<"Ya tienes la defensa maxima posible\n";
                        }else{
                            defensaPlayer+=50;
                            escudos--;
                            cout<<"Has usado un escudo...\n";
                            cout<<"La defensa de "<<nomPersonaje<<" ha subido a: "<<defensaPlayer<<endl;
                        }
                    }else{
                        cout<<"NO tienes escudos disponibles, adquierelos en la tienda principal\n";
                    }
                
                }else if (op==4){

                    if (golpeDefinitivo>0){
                        cout<<nomPersonaje<<" empieza a recitar un atiguo hechizo...\n";
                        if ((rand()%2 +1) % 2 == 0){
                            cout<<"El hechizo ha funcionado !!\n";
                            vidaComputadora-=100;
                            golpeDefinitivo--;
                            cout<<nomPersonaje<<" acertó el golpe definitivo directamente sobre "<<nomEnemigo<<endl;
                        }else{
                            cout<<nomEnemigo<<" te guiña el ojo  UwU\n";
                            cout<<nomPersonaje<<" se sonrroja...\n";
                            cout<<nomPersonaje<<" se ha distraido, en la confucion se termina hiriendo a si mismo [-50 de vida]\n";
                            vidaUsuario-=50;
                            if (vidaUsuario<=0){
                                cout<<nomPersonaje<<" ha sido derrotado por una distraccion ... carnal(?)\n";
                            }else{
                                cout<<nomPersonaje<<" a pesar del atrevimiento, sigue en pie...\n";
                            }
                        }
                    }else{
                        cout<<"NO tienes mas ataque definitivos disponibles :/...\n";
                    }
                }else if (op==5){
                    //Regresar
                    cout<<"Te arrepientes de usar un item...\n";
                    cout<<"------------------------------------------------------------------------------------\n\n";
                    continue;
                }else{
                    cout<<"Opcion no valida... :/\n";
                    continue;
                }
                break;
            case 4:
                cout<<"Intentas escapar pero....\n";
                if ((rand()%2 +1) == 2 ){
                    cout<<"Lo has logrado!!, te rendiste :/ \n";
                    vidaUsuario=0;
                }else{
                    cout<<"No has podido, la batalla continua\n";
                }
                break;        
            default:
                cout<<"Opcion no valida, intenta de nuevo\n";
                continue;
            }
        }else{//turno del enemigo
            op= rand() % 5 + 1;
            cout<<"\n\n\t>>>>> Turno de "<<nomEnemigo<<" <<<<<< \n\n";
            switch (op)
            {
            case 1:
                //Ataque normal
                cout<<nomEnemigo<<" ha decidido dar un ataque normal\n";
                ataqueEnemy=atacar(turno);
                if (ataqueEnemy<5){
                    cout<<"Ataque critico";
                    ataqueEnemy+=20;
                }
                

                if (defensaPlayer>0){
                    defensaPlayer-=ataqueEnemy;
                    cout<<"Te han inflijido "<<ataqueEnemy<<" puntos de ataque al escudo\n";
                    if (defensaPlayer<=0){
                        cout<<"Se ha roto tu escudo"<<endl;
                        defensaPlayer=0;
                    }else{
                        cout<<"Aun le quedan "<<defensaPlayer<<" puntos de defensa al escudo\n";
                    }
                }else{
                    vidaUsuario-=ataqueEnemy;
                    cout<<"Has recibido "<<ataqueEnemy<<" puntos de ataque directamente\n";
                }
                break;
            case 2:
                //Ataque fuerte
                cout<<nomEnemigo<<" hace un ataque fuerte!!\n";
                ataqueEnemy=atacar(turno)+15;//Sube 25 puntos a su ataque
                if (ataqueEnemy<=20){
                    ataqueEnemy+=15;
                }
                
                if (defensaPlayer>0){
                    defensaPlayer-=ataqueEnemy;
                    cout<<"Te han inflijido "<<ataqueEnemy<<" puntos de ataque al escudo\n";
                    if (defensaPlayer<=0){
                        cout<<"Se ha roto tu escudo"<<endl;
                        defensaPlayer=0;
                    }else{
                        cout<<"Aun le quedan "<<defensaPlayer<<" puntos de defensa al escudo\n";
                    }
                }else{
                    vidaUsuario-=ataqueEnemy;
                    cout<<"Has recibido "<<ataqueEnemy<<" puntos de ataque directamente\n";
                }
                //Despues de hacer el golpe hay un chance de hacer otra acción
                if ((rand()%2 + 1) % 2 ==0){
                    cout<<nomEnemigo<<" esta determinado...\n";
                    continue;
                }
                break;
            case 3:
                //Pasa
                cout<<nomEnemigo<<" mira al cielo y piensa...\n";
                cout<<nomEnemigo<<" ha decidido no atacar en este turno\n";
                break;
            case 4:
                //Reforzar escudo
                if (defensaEnemy>100){
                    cout<<nomEnemigo<<" Intenta reforzar aun mas su escudo pero se termina lastimando\n";
                    defensaEnemy=100;
                }else{
                    defensaEnemy += defensa(turno);
                    cout<<nomEnemigo<<" decide reforzar su escudo\n";
                    cout<<"Su defensa ha subido a "<<defensaEnemy<<endl;
                }
                break;
            case 5:
                //Piedra, papel o tijeras de la muerte
                cout<<nomEnemigo<<" te mira fijamente y empieza a recitar un hechizo...";
                if ((rand()%2 +1) % 2 == 0){
                    cout<<"Oh no, ha invocado el hechizo 'Piedra, papel o tijeras de la muerte'\n";
                    cout<<"Es un todo o nada, un hechizo simple pero increbrantable\n";
                    if(piedraPapelTijeras(dificultad)){
                        cout<<"Felicidades, has ganado el Piedra papel o tijeras de la muerte\n";
                        vidaComputadora=0;
                    }else{
                        cout<<"Oh no, has perdido en el Piedra, papel o tijeras de la muerte\n";
                        vidaUsuario=0;
                    }
                }else{
                    cout<<"Pero se le lengua la traba (no se acuerda del hechizo, ese dia falto a clases XD)\n";
                    cout<<nomEnemigo<<" sufre el recoil de la frustracion (-20 de vida)\n";
                    vidaComputadora-=20;
                }
                break;
            default:
                cout<<nomEnemigo<<" *Se sonroja* \n";
                break;
            }
        }
        cout<<"____________________________________________________________________________________\n";
        turno++;
    }

    //quien ganó?
    if (vidaComputadora <= 0){
        cout<<nomPersonaje<<" ha ganado!!\n";
        return true;
    }else{
        cout<<nomEnemigo<<" ha gando!!\n";
        return false;
    }
}

//---------Batalla por turnos game-------------
// Menú principal
int menuPrincipal(){
    int op;
    cout<<"________________________________________________________\n";
    cout<<"\n\tEN BUSQUEDA DE LA PIEDRA FILOSOFAL\n\n";
    cout<<"\t\t>>Menu principal<<\n";
    while (true){
        cout<<"________________________________________________________\n";
        cout<<"Oprime:\n";
        cout<<"[1] Para jugar\n";
        cout<<"[2] Para ir a la tienda\n";
        cout<<"[3] Para ajustar la dificultad\n";
        cout<<"[4] Para salir del juego\n{>>>} ";
        cin>>op;
        if (op == 1){
            return 1;
        }else if (op == 2){
            return 2;
        }else if (op == 3){
            return 3;
        }else if (op == 4){
            return 4;
        }else{
            cout<<"Opcion no valida\n";
        }
    }
}

//pedir Nombre del jugador
string nomPlayer(){
    string nombre;
    try{
        do{
        cout<<"Por favor, ingresa tu nombre (maximo 10 caracteres): \n";
        getline(cin, nombre);
        if (nombre.length() > 10){
            cout<<"El nombre ingresado tiene más de 10 caracteres. Intentalo de nuevo :D\n";
        }
        }while (nombre.length() > 10);
        return nombre;
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        cout<<"Error: validacion del nombrel\n";
        return "";
    }
}

void introduccion(string personaje){
    cout<<"-----------------------------------------------------------------------------------------------\n";
    cout<<"\t\tI N T R O D U C C I O N \n";
    cout<<"-----------------------------------------------------------------------------------------------\n";
    cout<<"En las lejanas tierras donde lo que nunca muere y todo es ciclico\n";
    cout<<"se extrañaba el olor de auguio insipido de almas mortales capaces de\n";
    cout<<"aventurarse al olvido, al inicio y al mas alla de lo legendariamente y medievalmente\n";
    cout<<"posible, es aqui que la historia de "<<personaje<<" comienza, pues se aventura en\n";
    cout<<"busqueda de la PIEDRA FILOSOFAL, aquella piedra que es capaz de revivir a los muertos\n";
    cout<<"y trasformar cualquier elemento en oro, --muy escaso en estos tiempos--\n.";
    cout<<"Poco o nada se sabe sobre esta misteriosa piedra pues los Opus Magnum son castigados con\n";
    cout<<"sanguinarias torturas que dan lugar a una semilla cultural prohibida por el haber del hombre.\n";
    cout<<"El sangunario ESTADO ha empezado a notar cierta controvercia entre los erratas del pueblo\n";
    cout<<"aquellos quienes dicen ser los poosedores de la verdad, que en realidad no son mas que un grupo\n";
    cout<<"de blasfemos, practicantes del ocultismo y misas negras han empezado a ser perseguidos. \n";
    cout<<"PRINGLES, lider del culto al necronomicon ha invitado al poosedor\n";
    cout<<"de lo desconocido a trasmutar su alma pues en su afan de alcanzar la vida eterna descrita\n";
    cout<<"en el libro prohibido a buscado de todas las formas posibles vivir eternamente. \n";
    cout<<"Las malas lenguas suelen contar que su infancia fue dificil pues....\n";
    cout<<"vio morir a cada uno de sus seres queridos, pudriendo cada vez mas su alma, sin embargo...\n";
    cout<<"ha muerto recientemente, y ha dejado en una carta decretando que cualquiera que persiga esa piedra\n";
    cout<<"sera maldecido por la eternidad, con el castigo de morir ciclicamente...\n";
    cout<<"Pero a "<<personaje<<" realmente no le importa nada de esto, pues esta mañana\n";
    cout<<"encontro un cartel de recompensa. Que aquel que sea poseedor de la piedra puede ser acredor\n";
    cout<<"de 1,000,000,000,000,000,000,000,000,000,000,000,000,\n";
    cout<<"de monedas reales, entregadas por el mismisimo ministro del SAT.\n";
    cout<<" -- tal vez sea mucho para declarar --. Por todo esto, "<<personaje<<" se pone en marcha.\n";
    cout<<" Despues de morir PRINGLES, los seguidores del necronomicon\n";
    cout<<"Manifestaron ir tras tres lugares: Bosques perdidos, Reinos Zora y a las Ruinas del Abismo\n\n\n";
    cout<<"-----------------------------------------------------------------------------------------------\n";
}

bool BosquesPerdidos(string personaje, int dificultad, int pociones, int pocionesMax, int escudos, int ataqueMortal){
    int op1, op2, op3, op4, op5;
    int corazones = 3;
    cout<<"-----------------------------------------------------------------------------------------------\n";
    cout<<"\tB O S Q U E S  P E R D I D O S \n\n";
    cout<<"-----------------------------------------------------------------------------------------------\n";
    cout<<"Despues de caminar varias horas "<<personaje<<" encuentra a los miticos BOSQUES PERDIDOS\n";
    cout<<"Un lugar mas parecido a un laberinto que a un bosque, donde todos los que se atreven a cruzarlo\n";
    cout<<"terminan siendo comidos por el olvido. Cuenta la leyenda que detras de ese bosque se halla la \n";
    cout<<"cueva de un poderoso dragon llamado JUMEX, este dragon atesora con mucho recelo un tesoro \n";
    cout<<"aun desconocido, un posible lugar para allar la PIEDRA FILOSOFAL\n";
    cout<<"-----------------------------------------------------------------------------------------------\n";
    cout<<"Al llegar a la entrada de los bosques perdidos "<<personaje<<" se encuentra con un FINN, el alcon\n";
    cout<<"FINN: LLegar al final debes si la recompensa quieres...jeje\n";
    cout<<"-----------------------------------------------------------------------------------------------\n";
    while (corazones > 0){
        cout<<"-----------------------------------------------------------------------------------------------\n";
        cout<<"Recorriendo el inicio del coludido laberinto arboral, encuentras a un Oso que habla (si, un oso)\n";
        cout<<"Oso: Hey bro, no puede pasar por aqui, este es el bosque que le pertenece a los animales\n";
        cout<<"\tpero aqui entre nosotros puedo dejarte pasar por algunas monedas...jeje... oso corruptoso\n\n";
        cout<<"---------------------------------------------------------------------------------------------------------\n";
        cout<<"Que quieres hacer??\n[1] Pelear contra el oso\t[2] Hablar\t[3] Pagar\n\n";
        cin>>op1;
        switch (op1)
        {
        case 1://Primera decicion
            //Pelear contra el oso
            cout<<"Has decidido pelear contra el oso\n";
            cout<<"Oso: Te eseñaré porqué me dicen el Oso cariñoso...jeje\n";
            if (batallaPorTurnos(personaje,"Oso corruptoso", dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                cout<<"Oso: Veo que sabes lo que haces, pero ten cuidado al seguir por este camino, uno nunca sabe\n";
                cout<<"\thasta donde lo puede llevar los vicios :c\n";

            }else{
                cout<<"Oso: Juas juas, soy el Oso Corruptoso y la corrupcion ganó de nuevo...jeje\n";
                cout<<"Derrotado decides pagar...con uno de tus corazones...\n";
                corazones--;
                cout<<"Corazones actuales: "<<corazones<<endl;
                if (corazones<=0){
                    return false;
                }
                
            }
            //End OSO

            cout<<"---------------------------------------------------------------------------------------------------------\n";
            cout<<personaje<<" se adentra aún más en el bosque y a lo lejos escucha una peleea, al parecer es entre un\n";
            cout<<"ratón y una serpiente, los movimientos rapidos del ratón despistan un poco a la serpiente pero no se\n";
            cout<<"deja intimidar por nada del mundo, finalmente, logra encajar una mordida abrazadora en la espina dorsal\n";
            cout<<"del ratón, empezando el proceso de licuacion de organos para posteriormente absorverlos a travez\n";
            cout<<"de sus colmillos.\n";
            cout<<"-----------------------------------------------------------------------------------------------------------\n";
            cout<<"Te acercas sigilosamente, pero la serpiente se acerca a ti rapidamente...\n";
            cout<<"Serpiente: A donde crees que ibasssss, si desearme un buen probechosssssss??, en este bosque la gente que se\n";
            cout<<"\tpierdessss, es deborada por alguna variante mía, pero más o menos letal, al parecer te llegó un poco tarde\n";
            cout<<"el mensaje sobre la hora de comer, pero ya que estas aqui, no me dejas otra alternativasssss...\n";
            cout<<"-----------------------------------------------------------------------------------------------------------\n";
            
            while (corazones > 0){
                cout<<"Serpiente Indú te queda viendo fijamente, que quieres hacer??\n\n[1] Pelear\n[2] Hablar\n[3] Pagar\n\n";
                cin>>op2;
                switch (op2)
                {
                case 1:
                    //Pelea contra serpiente indu
                    cout<<personaje<<" se acerca con determinacion...\n";
                    cout<<"Serpiente Indú, veo lo que intentasssss, veo a travezzzzz de tu ser, tus pecadossssss, tu hisssstoria, nada increible\n";
                    cout<<"\tessssspero hallassss traido algun antiveneno si no ve preparandote para una gran agonia\n";
                    if(batallaPorTurnos(personaje, "Serpiente Indú", dificultad, pociones, pocionesMax, escudos, ataqueMortal)){
                        cout<<"Serpiente Indú: Sssii, es cierto no lo que cuentan por ahí, malaventuraos los seguidores de la avaricia y la codicia\n";
                    }else{
                        cout<<"Serpiente Indú: Que es lo que veo?? otro ser arrastrandose y suplicando por su perdon por estar en el momento y lugar\n";
                        cout<<"\tequivocado??. Creo que ya sabes como es esto, tengo que arrebatarte ese calido corazon con mis frias escamassss\n";
                        corazones--;
                        cout<<"Corazones actuales: "<<corazones<<endl;
                        if (corazones<=0){
                            return false;
                        }
                        
                    }
                    //End serpiente indú
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<personaje<<" empieza a desmotivarse por todo el asunto de si realmente vale la pena seguir en busqueda de\n";
                    cout<<"esa tal piedra, pero sin embargo decide no rendirse y procurar seguir adelante con sus motivaciones, \n";
                    cout<<"ese prestamos a los burgueses no se va a pagar solo.\n";
                    cout<<"El bosque a pesar de ser un lugar bastante obtuso sigue siendo una de las grandes obras magnas de la naturaleza\n";
                    cout<<"en los antiguos libros de hechizos y magias paganas, se dice que los origenes del bosque son indecifrables.\n";
                    cout<<"Las primeras investigaciones que se hicieron sobre el bosque fue sobre muestras de cortesas de arbol,\n";
                    cout<<"pues los aros de los troncos revelaría con certeza su edad y a partir de ahí estimarian tiempos junto con\n";
                    cout<<"otras muestras del sedimento y del micelio blanco que crece alrededor del perimetro del boosque, pero que \n";
                    cout<<"sin embargo, al intentar partir los arboles, estos parecian indestructibles, ni con la fuerza de 20 hombres\n";
                    cout<<"era capaz de fragmentarse un solo pedazo de madera, al parecer los arboles secretaban naturalemente\n";
                    cout<<"una especie de baba pegajosa que puede ser usada como catalizador alquimico, incluso hay registros de que\n";
                    cout<<"al ser ingerido puede hacer que la persona persiva \"otra vida\", pues se asegura que puedes experimentar\n";
                    cout<<"otra vida muy distinta a la propia, con entornos y consecuecias diferentes salvo una sola constante\n";
                    cout<<"el NECRONOMICON.\n";
                    cout<<personaje<<" se sube a la copa de un arbol, intentando ver el final del bosque, pero este parece no terminar,\n";
                    cout<<"para no perderse, empieza a marcar los arboles por donde ya ha pasado, sin embargo, empieza a notar algo extraño\n";
                    cout<<"Los arboles que al principio solo tenian una marca vuelven a aparecer "<<personaje<<" empieza a sospechar sobre si\n";
                    cout<<"ha estado caminando en ciculos, hasta que...encuentra un patron en los arboles: forman tren hileras\n";
                    cout<<"el clima empieza a mostrar una cara gris, y algunas gotas se empiezan a persivir, buscando donde refugiarse\n";
                    cout<<"encuentra un techo de hojas, es como si alguien estuviera viviendo ahí, durante un tiempo...\n";
                    cout<<"DESCONOCIDO: Hey, que haces durmiendo ahí, uno ya no puede ir por algunos conejos sin que le roben su refugio\n";
                    cout<<"\tsé que el bosque parece interminable pero hay lugar para ambos, vale?, te dejaré quedarte pero nada de timos\n";
                    cout<<"\tsoy el ultimo protector que queda del dragon JUMEX, ese dragon se apoderó de todos los frutos del bosque \n";
                    cout<<"\tdesde hace un tiempo, desde entonces solo nos queda matarnos entre nosotros, los habitantes del Bosque Perdido\n";
                    cout<<"\tha decir verdad, los bucles entre arboles son bastante común entre mas te acercas al dragon, de vez en cuando\n";
                    cout<<"\tcuando el clima cambia el dragon pierde un poco de magia y tranquiliza la randomizacion del bosque. En fin, duerme.\n";
                    cout<<"\n\nAl día siguiente "<<personaje<<" le dió las gracias por su hospitalidad al ser Anaranjado Manchinegro.\n";
                    cout<<"Dandole adios a KKKKKN\n";
                    cout<<personaje<<" comieza a perder la determinacion, pero se acuerda del dinero por la PIEDRA FILOSOFAL y se le pasa\n";
                    cout<<"Despues de haber caminado durante 3 dias y 3 noches,"<<personaje<<" finalmente encuentra el templo del Dragon JUMEX\n";
                    cout<<"el templo es una esctructura monolitica de forma piramida invertida, con rios por algunas salidas del templo\n";
                    cout<<"y desgastado por el tiempo. Al seguir caminando, "<<personaje<<" se encuentra con un viejo conocido, KKKKKN,\n";
                    cout<<"KKKKKN: Sabría que vendrias, pero no pensé que llegarías tan lejos, como sabras es mi deber proteger a este dragon\n";
                    cout<<"\tle debo la vida de mis seres queridos, cuando la nacion enemiga de mi pueblo atacó, JUMEX, en su grandeza,\n";
                    cout<<"dió la cara y con sus llamaradas elimino al ejercito enemigo. Ese día, toda mi generacion le juró lealtad junto\n";
                    cout<<"con algunas otras familias. Pero ahora solo quedo yo, y no dejaré que sigas avanzando...\n";
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<"\n\nQue deseas hacer??[1] Pelear\t[2] Pelear\t[3] Pelear";
                    cin>>op4;
                    while (corazones>0)
                    {
                        //Pelea, Pelea, Pelea
                        if (batallaPorTurnos(personaje,"KKKKKN",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                            cout<<"KKKKKN: Le he jurado lealtad al grand Dragon JUMEX, mi cuerpo calló, pero mi alma siempre estará en deuda\n";
                            cout<<"\tdespues de tanto, esta vida no fue lo que necesitaba, pero era lo que quería, gracias por testerrarme\n";
                            cout<<"\tde este tormento, por fin podré reunirme con mi pueblo, mi tribu...mi familia...\n";
                            cout<<"En medio de la agonía de KKKKKN, reune pocas de sus fuerzas, se arrebata su unico corazon del pecho\n";
                            cout<<"y te lo ofrese como trofeo...simplemente lo aceptas.\n";
                            corazones+=1;
                            cout<<"Corazones actuales: "<<corazones<<endl;
                        }else{
                            cout<<"KKKKKN: La sangre de otro mortal vuelve a manchar mi espada de sangre, que con aquejo y remordimiento\n";
                            cout<<"\nespero que la proxima vez pueda encontrar la paz\n";
                            corazones-=0;
                            if (corazones-=0){
                                return false;
                            }
                        }
                        //End KKKKKN
                        cout<<"-----------------------------------------------------------------------------------------------------------\n";
                        cout<<personaje<<" ha recorrido bastante el suelo que hoy tiene lugar a un templo sagrado y protegido por un linaje\n";
                        cout<<"de guardianes tratando de encontrar la paz en su deber, en un juramento, en un una idea.\n";
                        cout<<"Al adentrarse en el gran templo, las cosas parecen estar muy abandonadas, los pisos con cubiertos por gruesas\n";
                        cout<<"y pesadas capas de polvo formando un aura de abandono profundo, sin embargo tras caminar un tiempo\n";
                        cout<<"se logran ver algunas huellas que se repiten a si mismas, al parecer son las huellas de un Jaguar\n";
                        cout<<"parece ser que KKKKKN recorria constantemente los pasillos vacios y oscuros, así que "<<personaje<<"decide \n";
                        cout<<"seguir el rastro, mientras sigue las marcas en el piso, se pueden apreciar en los muros una cierta leyenda\n";
                        cout<<"al parecer los muros fueron pintados con un estilo muy ruprestre, no se logra ver muy bien, el paso del tiempo\n";
                        cout<<"ha hecho que se borre la pintura pero parcialmente se puede apreciar una especia de dragon blanco\n";
                        cout<<"de ojos azules saliendo del Sol en direccion para un grupo de personas, tambien hay una rota, falta un fragmento\n";
                        cout<<"solo se logra ver lo que parece una persona alzando algo....tal vez no sea importante...\n";
                        cout<<"A lo lejos se escucha un rugido temible, seguido de un golpe constante, un compas confuso de flauta se logra\n";
                        cout<<"distinguir, al ritmo se suma algunos tambores muy tribales, arpas y algunos instrumentos de cuerda.\n";
                        cout<<personaje<<" decide seguir la musica, sube unas escaleras en forma de caracol de una aparente torre y llega a \n ";
                        cout<<"una camara en donde resuena los tambores, ahí ve un dragon blanco dormido, una gran hoguera y los musicos\n";
                        cout<<"disfrutando la complicidad, la union y el rito. De repente, un grupo encapuchado empieza a escoger personas\n";
                        cout<<"aparentemente al azar, usan una especie de rampa imprivizada y lo dejan caer a la boca del dragon quien\n";
                        cout<<"instintivamente abrió el hocico, dejando algunas llamas en el aire. Las personas encapuchadas vuelven a escoger\n";
                        cout<<"personas, separando a una familia, se llevan a una madre y a su hija, el padre implora que las dejen en paz\n";
                        cout<<"entre gritos y sollozos, la hija se libera por un instante y luego dejan caer a la madre a la boca del dragon\n";
                        cout<<"mientras la madre cae, la hija corre a los brazos del padre, el padre enfurecido, en un movimiento rapido\n";
                        cout<<"carga a su hija y le arrebata un leño a la hoguera, su mirada lo dice todo, solo quire salir de ahí\n";
                        cout<<"Entre lagrimas, la hija pregunta por su madre, aún no comprende que acaba de pasar, simplemente no lo asimila\n";
                        cout<<"el padre al verse acorralado, decide subir por la rampa y saltar, el dragon abre la boca pero es tarde\n";
                        cout<<"el padre le ha clavado un leño en su ojo izquierdo. Con el ojo enrojesido el Gran Dragon Blanco se levanta\n";
                        cout<<"Y muestra su imponente forma, dando un rugido muy feroz, capaz de sacar volando a todo el culto, el padre\n";
                        cout<<"logra verte y en un breve momento de contacto visual, desaparece...El Dragon intenta volar, sin embargo tiene\n";
                        cout<<"una de sus alas rotas ya, desconocido es si aun su equilibro en orden está, al intentar levantarse no logra superar\n";
                        cout<<"los 10 segundos seguidos en una pocicion estable. Una corroida sustancia es expulsada de su boca. El legendario\n";
                        cout<<"dragon está muriendo. JUMEX, nota tu presencia, alcanza a verte con el rabillo de su ojo aun en paz\n";
                        cout<<personaje<<" decide acercase con determinacion...El momento se detiene, los flujos de agua cayendo se detienen\n";
                        cout<<"y el tiempo lo hace tambien, escuha una extraña voz agrietada y corrompida\n";
                        cout<<"\nJUMEX, el gran dragon de ojos azules: Estas aquí por esa baratija de piedra, cierto?? Bueno, tengo malas noticias\n";
                        cout<<"\tesa cosa nunca existió, solo fueron inventos de gente rechazada por la sociedad inventó, el sistema les falló\n";
                        cout<<"\tcomo puedes ver ahora los grupos de extraños me llaman una leyenda, pero que soy si no otro dragon\n";
                        cout<<"\tlas historias que se cuentan de mi, son solo grandes enagenaciones de mitos revueltos en la mente\n";
                        cout<<"\thumana, un parasito social que solo aferra a los más necesitados a un puño de promesas vacias\n ";
                        cout<<"\tPero, ya estoy cansado de todo esto, necesito descansar, necesito encontrar el equilibrio, pero qué clase de\n";
                        cout<<"\tequilibrio puede conseguir una lagartija gigante??. Te lo suplico, por favor acaba conmigo, solo quiero morir\n";
                        cout<<"\tdeseo salir de este mundo que me ha hecho tanto daño.Harias eso por mi??\n";
                        cout<<"-----------------------------------------------------------------------------------------------------------\n\n";
                        cout<<"Que deseas hacer??\n\n[1] Matar\t[2] Pelear\t[3] Perdonar\n\n";
                        cin>>op5;
                        if (op5==1){
                            cout<<personaje<<" toma su espada, desevaina la hoja, toma un respiro, hinhala, exhala, encuentra determinacion en\n";
                            cout<<"sus acciones y...\n";
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: espera, que estoy haciendo??Dejandome matar por una persona que\n";
                            cout<<"\tno tiene la menor idea de mis heroicos actos, de mi legado, de mi ser...no, un Dragon de mi linaje\n";
                            cout<<"\tno puede morir de esta forma tan patetica. Preparate para nuestra pelea, será de las cosas más dificiles que\n";
                            cout<<"hayas hecho nunca...muah...jjajajaja..coff.cofff...\n";
                        }else if (op5==2){
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: a veces, y solo a veces son necesarias las peleas pero esta vez será\n";
                            cout<<"\talgo muy sensillo,pero...por qué debería serlo, por qué me tengo tando desprecio a mi mismo??\n";
                            cout<<"\tOlvidalo por completo, PREPARATE A SER CARBONNIZADO JAJAJAJAJAJA\n";
                        }else{
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: no,no,no,no,no...no necesito tu perdon, no necesito el de nadie\n";
                            cout<<"\tTú jamas me entenderías simple mortal, acabaré con tu vida, así como la de la gente que me lo himploró\n";
                            cout<<"coff...coff....\n";
                        }
                        if (batallaPorTurnos(personaje, "JUMEX EL GRAN DRAGON BLANCO DE OJOS AZULES", 2, pociones, pocionesMax, escudos, ataqueMortal)){
                            cout<<"Esta ha sido mi ultima batalla, coff..coff, nunca fuiste realmente un rival para mi, yo no morireeee en las manos\n";
                            cout<<"de un simple mortaaaaaaaalll AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH...aaaaaaaaaaaaaaah...\n";
                            cout<<"Un liquido brumoso purpura empieza a sacar por todos los orificios del cuerpo, cae al aspero suelo y finalmente\n\n";
                            cout<<"JUMEX, EL GRAN DRAGON BLANCO DE OJOS AZULES muere\n";
                            cout<<"Corazones actuales: "<<corazones<<endl;
                            return true;

                        }else{
                            cout<<"Te lo dije, un gran ser como yo es imposible de matar...espero que la proxima vez sea distinto, aqui estaré\n";
                            cout<<personaje<<" tirado en el suelo y sufriendo de agonia, mira al dragon y da su ultimo suspiro....has muerto\n";
                            cout<<"El dragon se come tu cadaver y con ello, todos tus corazones\n";
                            corazones = 0;
                            cout<<"Corazones actuales"<<corazones<<endl;
                            return false;

                        }
                    }
                    //End dragon y Bosques Perdidos
                    break;
                case 2:
                    //Habla con serpiente Indú
                    cout<<"Serpiente Indú: Espera, no queriassss quitarme mi comida???, Debisste haberlo mencionado antesss, todo esto es un simple mal\n";
                    cout<<"\tentendidosss, de ser por mi, puedes pasar a dodne quieras, en este bosque las cosas son más simples de lo que parece\n";
                    cout<<"Serpiente Indú, te ha dejado pasar sin aparentemente ningun problema\n";
                    cout<<"Corazones actuales: "<<corazones<<endl;
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    
                    //End serpiente indú
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<personaje<<" empieza a desmotivarse por todo el asunto de si realmente vale la pena seguir en busqueda de\n";
                    cout<<"esa tal piedra, pero sin embargo decide no rendirse y procurar seguir adelante con sus motivaciones, \n";
                    cout<<"ese prestamos a los burgueses no se va a pagar solo.\n";
                    cout<<"El bosque a pesar de ser un lugar bastante obtuso sigue siendo una de las grandes obras magnas de la naturaleza\n";
                    cout<<"en los antiguos libros de hechizos y magias paganas, se dice que los origenes del bosque son indecifrables.\n";
                    cout<<"Las primeras investigaciones que se hicieron sobre el bosque fue sobre muestras de cortesas de arbol,\n";
                    cout<<"pues los aros de los troncos revelaría con certeza su edad y a partir de ahí estimarian tiempos junto con\n";
                    cout<<"otras muestras del sedimento y del micelio blanco que crece alrededor del perimetro del boosque, pero que \n";
                    cout<<"sin embargo, al intentar partir los arboles, estos parecian indestructibles, ni con la fuerza de 20 hombres\n";
                    cout<<"era capaz de fragmentarse un solo pedazo de madera, al parecer los arboles secretaban naturalemente\n";
                    cout<<"una especie de baba pegajosa que puede ser usada como catalizador alquimico, incluso hay registros de que\n";
                    cout<<"al ser ingerido puede hacer que la persona persiva \"otra vida\", pues se asegura que puedes experimentar\n";
                    cout<<"otra vida muy distinta a la propia, con entornos y consecuecias diferentes salvo una sola constante\n";
                    cout<<"el NECRONOMICON.\n";
                    cout<<personaje<<" se sube a la copa de un arbol, intentando ver el final del bosque, pero este parece no terminar,\n";
                    cout<<"para no perderse, empieza a marcar los arboles por donde ya ha pasado, sin embargo, empieza a notar algo extraño\n";
                    cout<<"Los arboles que al principio solo tenian una marca vuelven a aparecer "<<personaje<<" empieza a sospechar sobre si\n";
                    cout<<"ha estado caminando en ciculos, hasta que...encuentra un patron en los arboles: forman tren hileras\n";
                    cout<<"el clima empieza a mostrar una cara gris, y algunas gotas se empiezan a persivir, buscando donde refugiarse\n";
                    cout<<"encuentra un techo de hojas, es como si alguien estuviera viviendo ahí, durante un tiempo...\n";
                    cout<<"DESCONOCIDO: Hey, que haces durmiendo ahí, uno ya no puede ir por algunos conejos sin que le roben su refugio\n";
                    cout<<"\tsé que el bosque parece interminable pero hay lugar para ambos, vale?, te dejaré quedarte pero nada de timos\n";
                    cout<<"\tsoy el ultimo protector que queda del dragon JUMEX, ese dragon se apoderó de todos los frutos del bosque \n";
                    cout<<"\tdesde hace un tiempo, desde entonces solo nos queda matarnos entre nosotros, los habitantes del Bosque Perdido\n";
                    cout<<"\tha decir verdad, los bucles entre arboles son bastante común entre mas te acercas al dragon, de vez en cuando\n";
                    cout<<"\tcuando el clima cambia el dragon pierde un poco de magia y tranquiliza la randomizacion del bosque. En fin, duerme.\n";
                    cout<<"\n\nAl día siguiente "<<personaje<<" le dió las gracias por su hospitalidad al ser Anaranjado Manchinegro.\n";
                    cout<<"Dandole adios a KKKKKN\n";
                    cout<<personaje<<" comieza a perder la determinacion, pero se acuerda del dinero por la PIEDRA FILOSOFAL y se le pasa\n";
                    cout<<"Despues de haber caminado durante 3 dias y 3 noches,"<<personaje<<" finalmente encuentra el templo del Dragon JUMEX\n";
                    cout<<"el templo es una esctructura monolitica de forma piramida invertida, con rios por algunas salidas del templo\n";
                    cout<<"y desgastado por el tiempo. Al seguir caminando, "<<personaje<<" se encuentra con un viejo conocido, KKKKKN,\n";
                    cout<<"KKKKKN: Sabría que vendrias, pero no pensé que llegarías tan lejos, como sabras es mi deber proteger a este dragon\n";
                    cout<<"\tle debo la vida de mis seres queridos, cuando la nacion enemiga de mi pueblo atacó, JUMEX, en su grandeza,\n";
                    cout<<"dió la cara y con sus llamaradas elimino al ejercito enemigo. Ese día, toda mi generacion le juró lealtad junto\n";
                    cout<<"con algunas otras familias. Pero ahora solo quedo yo, y no dejaré que sigas avanzando...\n";
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<"\n\nQue deseas hacer??[1] Pelear\t[2] Pelear\t[3] Pelear\n";
                    cin>>op4;
                    while (corazones>0)
                    {
                        //Pelea, Pelea, Pelea
                        if (batallaPorTurnos(personaje,"KKKKKN",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                            cout<<"KKKKKN: Le he jurado lealtad al grand Dragon JUMEX, mi cuerpo calló, pero mi alma siempre estará en deuda\n";
                            cout<<"\tdespues de tanto, esta vida no fue lo que necesitaba, pero era lo que quería, gracias por testerrarme\n";
                            cout<<"\tde este tormento, por fin podré reunirme con mi pueblo, mi tribu...mi familia...\n";
                            cout<<"En medio de la agonía de KKKKKN, reune pocas de sus fuerzas, se arrebata su unico corazon del pecho\n";
                            cout<<"y te lo ofrese como trofeo...simplemente lo aceptas.\n";
                            corazones+=1;
                            cout<<"Corazones actuales: "<<corazones<<endl;
                        }else{
                            cout<<"KKKKKN: La sangre de otro mortal vuelve a manchar mi espada de sangre, que con aquejo y remordimiento\n";
                            cout<<"\nespero que la proxima vez pueda encontrar la paz\n";
                            corazones-=0;
                            if (corazones-=0){
                                return false;
                            }
                        }
                        //End KKKKKN
                        cout<<"-----------------------------------------------------------------------------------------------------------\n";
                        cout<<personaje<<" ha recorrido bastante el suelo que hoy tiene lugar a un templo sagrado y protegido por un linaje\n";
                        cout<<"de guardianes tratando de encontrar la paz en su deber, en un juramento, en un una idea.\n";
                        cout<<"Al adentrarse en el gran templo, las cosas parecen estar muy abandonadas, los pisos con cubiertos por gruesas\n";
                        cout<<"y pesadas capas de polvo formando un aura de abandono profundo, sin embargo tras caminar un tiempo\n";
                        cout<<"se logran ver algunas huellas que se repiten a si mismas, al parecer son las huellas de un Jaguar\n";
                        cout<<"parece ser que KKKKKN recorria constantemente los pasillos vacios y oscuros, así que "<<personaje<<"decide \n";
                        cout<<"seguir el rastro, mientras sigue las marcas en el piso, se pueden apreciar en los muros una cierta leyenda\n";
                        cout<<"al parecer los muros fueron pintados con un estilo muy ruprestre, no se logra ver muy bien, el paso del tiempo\n";
                        cout<<"ha hecho que se borre la pintura pero parcialmente se puede apreciar una especia de dragon blanco\n";
                        cout<<"de ojos azules saliendo del Sol en direccion para un grupo de personas, tambien hay una rota, falta un fragmento\n";
                        cout<<"solo se logra ver lo que parece una persona alzando algo....tal vez no sea importante...\n";
                        cout<<"A lo lejos se escucha un rugido temible, seguido de un golpe constante, un compas confuso de flauta se logra\n";
                        cout<<"distinguir, al ritmo se suma algunos tambores muy tribales, arpas y algunos instrumentos de cuerda.\n";
                        cout<<personaje<<" decide seguir la musica, sube unas escaleras en forma de caracol de una aparente torre y llega a \n ";
                        cout<<"una camara en donde resuena los tambores, ahí ve un dragon blanco dormido, una gran hoguera y los musicos\n";
                        cout<<"disfrutando la complicidad, la union y el rito. De repente, un grupo encapuchado empieza a escoger personas\n";
                        cout<<"aparentemente al azar, usan una especie de rampa imprivizada y lo dejan caer a la boca del dragon quien\n";
                        cout<<"instintivamente abrió el hocico, dejando algunas llamas en el aire. Las personas encapuchadas vuelven a escoger\n";
                        cout<<"personas, separando a una familia, se llevan a una madre y a su hija, el padre implora que las dejen en paz\n";
                        cout<<"entre gritos y sollozos, la hija se libera por un instante y luego dejan caer a la madre a la boca del dragon\n";
                        cout<<"mientras la madre cae, la hija corre a los brazos del padre, el padre enfurecido, en un movimiento rapido\n";
                        cout<<"carga a su hija y le arrebata un leño a la hoguera, su mirada lo dice todo, solo quire salir de ahí\n";
                        cout<<"Entre lagrimas, la hija pregunta por su madre, aún no comprende que acaba de pasar, simplemente no lo asimila\n";
                        cout<<"el padre al verse acorralado, decide subir por la rampa y saltar, el dragon abre la boca pero es tarde\n";
                        cout<<"el padre le ha clavado un leño en su ojo izquierdo. Con el ojo enrojesido el Gran Dragon Blanco se levanta\n";
                        cout<<"Y muestra su imponente forma, dando un rugido muy feroz, capaz de sacar volando a todo el culto, el padre\n";
                        cout<<"logra verte y en un breve momento de contacto visual, desaparece...El Dragon intenta volar, sin embargo tiene\n";
                        cout<<"una de sus alas rotas ya, desconocido es si aun su equilibro en orden está, al intentar levantarse no logra superar\n";
                        cout<<"los 10 segundos seguidos en una pocicion estable. Una corroida sustancia es expulsada de su boca. El legendario\n";
                        cout<<"dragon está muriendo. JUMEX, nota tu presencia, alcanza a verte con el rabillo de su ojo aun en paz\n";
                        cout<<personaje<<" decide acercase con determinacion...El momento se detiene, los flujos de agua cayendo se detienen\n";
                        cout<<"y el tiempo lo hace tambien, escuha una extraña voz agrietada y corrompida\n";
                        cout<<"\nJUMEX, el gran dragon de ojos azules: Estas aquí por esa baratija de piedra, cierto?? Bueno, tengo malas noticias\n";
                        cout<<"\tesa cosa nunca existió, solo fueron inventos de gente rechazada por la sociedad inventó, el sistema les falló\n";
                        cout<<"\tcomo puedes ver ahora los grupos de extraños me llaman una leyenda, pero que soy si no otro dragon\n";
                        cout<<"\tlas historias que se cuentan de mi, son solo grandes enagenaciones de mitos revueltos en la mente\n";
                        cout<<"\thumana, un parasito social que solo aferra a los más necesitados a un puño de promesas vacias\n ";
                        cout<<"\tPero, ya estoy cansado de todo esto, necesito descansar, necesito encontrar el equilibrio, pero qué clase de\n";
                        cout<<"\tequilibrio puede conseguir una lagartija gigante??. Te lo suplico, por favor acaba conmigo, solo quiero morir\n";
                        cout<<"\tdeseo salir de este mundo que me ha hecho tanto daño.Harias eso por mi??\n";
                        cout<<"-----------------------------------------------------------------------------------------------------------\n\n";
                        cout<<"Que deseas hacer??\n\n[1] Matar\t[2] Pelear\t[3] Perdonar\n\n";
                        cin>>op5;
                        if (op5==1){
                            cout<<personaje<<" toma su espada, desevaina la hoja, toma un respiro, hinhala, exhala, encuentra determinacion en\n";
                            cout<<"sus acciones y...\n";
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: espera, que estoy haciendo??Dejandome matar por una persona que\n";
                            cout<<"\tno tiene la menor idea de mis heroicos actos, de mi legado, de mi ser...no, un Dragon de mi linaje\n";
                            cout<<"\tno puede morir de esta forma tan patetica. Preparate para nuestra pelea, será de las cosas más dificiles que\n";
                            cout<<"hayas hecho nunca...muah...jjajajaja..coff.cofff...\n";
                        }else if (op5==2){
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: a veces, y solo a veces son necesarias las peleas pero esta vez será\n";
                            cout<<"\talgo muy sensillo,pero...por qué debería serlo, por qué me tengo tando desprecio a mi mismo??\n";
                            cout<<"\tOlvidalo por completo, PREPARATE A SER CARBONNIZADO JAJAJAJAJAJA\n";
                        }else{
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: no,no,no,no,no...no necesito tu perdon, no necesito el de nadie\n";
                            cout<<"\tTú jamas me entenderías simple mortal, acabaré con tu vida, así como la de la gente que me lo himploró\n";
                            cout<<"coff...coff....\n";
                        }
                        if (batallaPorTurnos(personaje, "JUMEX EL GRAN DRAGON BLANCO DE OJOS AZULES", 2, pociones, pocionesMax, escudos, ataqueMortal)){
                            cout<<"Esta ha sido mi ultima batalla, coff..coff, nunca fuiste realmente un rival para mi, yo no morireeee en las manos\n";
                            cout<<"de un simple mortaaaaaaaalll AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH...aaaaaaaaaaaaaaah...\n";
                            cout<<"Un liquido brumoso purpura empieza a sacar por todos los orificios del cuerpo, cae al aspero suelo y finalmente\n\n";
                            cout<<"JUMEX, EL GRAN DRAGON BLANCO DE OJOS AZULES muere\n";
                            cout<<"Corazones actuales: "<<corazones<<endl;
                            return true;

                        }else{
                            cout<<"Te lo dije, un gran ser como yo es imposible de matar...espero que la proxima vez sea distinto, aqui estaré\n";
                            cout<<personaje<<" tirado en el suelo y sufriendo de agonia, mira al dragon y da su ultimo suspiro....has muerto\n";
                            cout<<"El dragon se come tu cadaver y con ello, todos tus corazones\n";
                            corazones = 0;
                            cout<<"Corazones actuales"<<corazones<<endl;
                            return false;

                        }
                    }
                    //End dragon y Bosques Perdidos
                    break;
                case 3:
                    //Pagar a serpiente indú
                    cout<<"Serpiente Indú: Espera, qué se supone que haga yo con essssso, solo soy una serpiente de origen desconocido, lo siento pero\n";
                    cout<<"\nno puedo dejarte hacer eso, total, ya cazé mi presa del día ...ssssss.sssss.ssss\n";
                    cout<<"Corazones actuales: "<<corazones<<endl;
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    //End serpiente indú
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<personaje<<" empieza a desmotivarse por todo el asunto de si realmente vale la pena seguir en busqueda de\n";
                    cout<<"esa tal piedra, pero sin embargo decide no rendirse y procurar seguir adelante con sus motivaciones, \n";
                    cout<<"ese prestamos a los burgueses no se va a pagar solo.\n";
                    cout<<"El bosque a pesar de ser un lugar bastante obtuso sigue siendo una de las grandes obras magnas de la naturaleza\n";
                    cout<<"en los antiguos libros de hechizos y magias paganas, se dice que los origenes del bosque son indecifrables.\n";
                    cout<<"Las primeras investigaciones que se hicieron sobre el bosque fue sobre muestras de cortesas de arbol,\n";
                    cout<<"pues los aros de los troncos revelaría con certeza su edad y a partir de ahí estimarian tiempos junto con\n";
                    cout<<"otras muestras del sedimento y del micelio blanco que crece alrededor del perimetro del boosque, pero que \n";
                    cout<<"sin embargo, al intentar partir los arboles, estos parecian indestructibles, ni con la fuerza de 20 hombres\n";
                    cout<<"era capaz de fragmentarse un solo pedazo de madera, al parecer los arboles secretaban naturalemente\n";
                    cout<<"una especie de baba pegajosa que puede ser usada como catalizador alquimico, incluso hay registros de que\n";
                    cout<<"al ser ingerido puede hacer que la persona persiva \"otra vida\", pues se asegura que puedes experimentar\n";
                    cout<<"otra vida muy distinta a la propia, con entornos y consecuecias diferentes salvo una sola constante\n";
                    cout<<"el NECRONOMICON.\n";
                    cout<<personaje<<" se sube a la copa de un arbol, intentando ver el final del bosque, pero este parece no terminar,\n";
                    cout<<"para no perderse, empieza a marcar los arboles por donde ya ha pasado, sin embargo, empieza a notar algo extraño\n";
                    cout<<"Los arboles que al principio solo tenian una marca vuelven a aparecer "<<personaje<<" empieza a sospechar sobre si\n";
                    cout<<"ha estado caminando en ciculos, hasta que...encuentra un patron en los arboles: forman tren hileras\n";
                    cout<<"el clima empieza a mostrar una cara gris, y algunas gotas se empiezan a persivir, buscando donde refugiarse\n";
                    cout<<"encuentra un techo de hojas, es como si alguien estuviera viviendo ahí, durante un tiempo...\n";
                    cout<<"DESCONOCIDO: Hey, que haces durmiendo ahí, uno ya no puede ir por algunos conejos sin que le roben su refugio\n";
                    cout<<"\tsé que el bosque parece interminable pero hay lugar para ambos, vale?, te dejaré quedarte pero nada de timos\n";
                    cout<<"\tsoy el ultimo protector que queda del dragon JUMEX, ese dragon se apoderó de todos los frutos del bosque \n";
                    cout<<"\tdesde hace un tiempo, desde entonces solo nos queda matarnos entre nosotros, los habitantes del Bosque Perdido\n";
                    cout<<"\tha decir verdad, los bucles entre arboles son bastante común entre mas te acercas al dragon, de vez en cuando\n";
                    cout<<"\tcuando el clima cambia el dragon pierde un poco de magia y tranquiliza la randomizacion del bosque. En fin, duerme.\n";
                    cout<<"\n\nAl día siguiente "<<personaje<<" le dió las gracias por su hospitalidad al ser Anaranjado Manchinegro.\n";
                    cout<<"Dandole adios a KKKKKN\n";
                    cout<<personaje<<" comieza a perder la determinacion, pero se acuerda del dinero por la PIEDRA FILOSOFAL y se le pasa\n";
                    cout<<"Despues de haber caminado durante 3 dias y 3 noches,"<<personaje<<" finalmente encuentra el templo del Dragon JUMEX\n";
                    cout<<"el templo es una esctructura monolitica de forma piramida invertida, con rios por algunas salidas del templo\n";
                    cout<<"y desgastado por el tiempo. Al seguir caminando, "<<personaje<<" se encuentra con un viejo conocido, KKKKKN,\n";
                    cout<<"KKKKKN: Sabría que vendrias, pero no pensé que llegarías tan lejos, como sabras es mi deber proteger a este dragon\n";
                    cout<<"\tle debo la vida de mis seres queridos, cuando la nacion enemiga de mi pueblo atacó, JUMEX, en su grandeza,\n";
                    cout<<"dió la cara y con sus llamaradas elimino al ejercito enemigo. Ese día, toda mi generacion le juró lealtad junto\n";
                    cout<<"con algunas otras familias. Pero ahora solo quedo yo, y no dejaré que sigas avanzando...\n";
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<"\n\nQue deseas hacer??[1] Pelear\t[2] Pelear\t[3] Pelear\n";
                    cin>>op4;
                    while (corazones>0)
                    {
                        //Pelea, Pelea, Pelea
                        if (batallaPorTurnos(personaje,"KKKKKN",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                            cout<<"KKKKKN: Le he jurado lealtad al grand Dragon JUMEX, mi cuerpo calló, pero mi alma siempre estará en deuda\n";
                            cout<<"\tdespues de tanto, esta vida no fue lo que necesitaba, pero era lo que quería, gracias por testerrarme\n";
                            cout<<"\tde este tormento, por fin podré reunirme con mi pueblo, mi tribu...mi familia...\n";
                            cout<<"En medio de la agonía de KKKKKN, reune pocas de sus fuerzas, se arrebata su unico corazon del pecho\n";
                            cout<<"y te lo ofrese como trofeo...simplemente lo aceptas.\n";
                            corazones+=1;
                            cout<<"Corazones actuales: "<<corazones<<endl;
                        }else{
                            cout<<"KKKKKN: La sangre de otro mortal vuelve a manchar mi espada de sangre, que con aquejo y remordimiento\n";
                            cout<<"\nespero que la proxima vez pueda encontrar la paz\n";
                            corazones-=0;
                            if (corazones-=0){
                                return false;
                            }
                        }
                        //End KKKKKN
                        cout<<"-----------------------------------------------------------------------------------------------------------\n";
                        cout<<personaje<<" ha recorrido bastante el suelo que hoy tiene lugar a un templo sagrado y protegido por un linaje\n";
                        cout<<"de guardianes tratando de encontrar la paz en su deber, en un juramento, en un una idea.\n";
                        cout<<"Al adentrarse en el gran templo, las cosas parecen estar muy abandonadas, los pisos con cubiertos por gruesas\n";
                        cout<<"y pesadas capas de polvo formando un aura de abandono profundo, sin embargo tras caminar un tiempo\n";
                        cout<<"se logran ver algunas huellas que se repiten a si mismas, al parecer son las huellas de un Jaguar\n";
                        cout<<"parece ser que KKKKKN recorria constantemente los pasillos vacios y oscuros, así que "<<personaje<<"decide \n";
                        cout<<"seguir el rastro, mientras sigue las marcas en el piso, se pueden apreciar en los muros una cierta leyenda\n";
                        cout<<"al parecer los muros fueron pintados con un estilo muy ruprestre, no se logra ver muy bien, el paso del tiempo\n";
                        cout<<"ha hecho que se borre la pintura pero parcialmente se puede apreciar una especia de dragon blanco\n";
                        cout<<"de ojos azules saliendo del Sol en direccion para un grupo de personas, tambien hay una rota, falta un fragmento\n";
                        cout<<"solo se logra ver lo que parece una persona alzando algo....tal vez no sea importante...\n";
                        cout<<"A lo lejos se escucha un rugido temible, seguido de un golpe constante, un compas confuso de flauta se logra\n";
                        cout<<"distinguir, al ritmo se suma algunos tambores muy tribales, arpas y algunos instrumentos de cuerda.\n";
                        cout<<personaje<<" decide seguir la musica, sube unas escaleras en forma de caracol de una aparente torre y llega a \n ";
                        cout<<"una camara en donde resuena los tambores, ahí ve un dragon blanco dormido, una gran hoguera y los musicos\n";
                        cout<<"disfrutando la complicidad, la union y el rito. De repente, un grupo encapuchado empieza a escoger personas\n";
                        cout<<"aparentemente al azar, usan una especie de rampa imprivizada y lo dejan caer a la boca del dragon quien\n";
                        cout<<"instintivamente abrió el hocico, dejando algunas llamas en el aire. Las personas encapuchadas vuelven a escoger\n";
                        cout<<"personas, separando a una familia, se llevan a una madre y a su hija, el padre implora que las dejen en paz\n";
                        cout<<"entre gritos y sollozos, la hija se libera por un instante y luego dejan caer a la madre a la boca del dragon\n";
                        cout<<"mientras la madre cae, la hija corre a los brazos del padre, el padre enfurecido, en un movimiento rapido\n";
                        cout<<"carga a su hija y le arrebata un leño a la hoguera, su mirada lo dice todo, solo quire salir de ahí\n";
                        cout<<"Entre lagrimas, la hija pregunta por su madre, aún no comprende que acaba de pasar, simplemente no lo asimila\n";
                        cout<<"el padre al verse acorralado, decide subir por la rampa y saltar, el dragon abre la boca pero es tarde\n";
                        cout<<"el padre le ha clavado un leño en su ojo izquierdo. Con el ojo enrojesido el Gran Dragon Blanco se levanta\n";
                        cout<<"Y muestra su imponente forma, dando un rugido muy feroz, capaz de sacar volando a todo el culto, el padre\n";
                        cout<<"logra verte y en un breve momento de contacto visual, desaparece...El Dragon intenta volar, sin embargo tiene\n";
                        cout<<"una de sus alas rotas ya, desconocido es si aun su equilibro en orden está, al intentar levantarse no logra superar\n";
                        cout<<"los 10 segundos seguidos en una pocicion estable. Una corroida sustancia es expulsada de su boca. El legendario\n";
                        cout<<"dragon está muriendo. JUMEX, nota tu presencia, alcanza a verte con el rabillo de su ojo aun en paz\n";
                        cout<<personaje<<" decide acercase con determinacion...El momento se detiene, los flujos de agua cayendo se detienen\n";
                        cout<<"y el tiempo lo hace tambien, escuha una extraña voz agrietada y corrompida\n";
                        cout<<"\nJUMEX, el gran dragon de ojos azules: Estas aquí por esa baratija de piedra, cierto?? Bueno, tengo malas noticias\n";
                        cout<<"\tesa cosa nunca existió, solo fueron inventos de gente rechazada por la sociedad inventó, el sistema les falló\n";
                        cout<<"\tcomo puedes ver ahora los grupos de extraños me llaman una leyenda, pero que soy si no otro dragon\n";
                        cout<<"\tlas historias que se cuentan de mi, son solo grandes enagenaciones de mitos revueltos en la mente\n";
                        cout<<"\thumana, un parasito social que solo aferra a los más necesitados a un puño de promesas vacias\n ";
                        cout<<"\tPero, ya estoy cansado de todo esto, necesito descansar, necesito encontrar el equilibrio, pero qué clase de\n";
                        cout<<"\tequilibrio puede conseguir una lagartija gigante??. Te lo suplico, por favor acaba conmigo, solo quiero morir\n";
                        cout<<"\tdeseo salir de este mundo que me ha hecho tanto daño.Harias eso por mi??\n";
                        cout<<"-----------------------------------------------------------------------------------------------------------\n\n";
                        cout<<"Que deseas hacer??\n\n[1] Matar\t[2] Pelear\t[3] Perdonar\n\n";
                        cin>>op5;
                        if (op5==1){
                            cout<<personaje<<" toma su espada, desevaina la hoja, toma un respiro, hinhala, exhala, encuentra determinacion en\n";
                            cout<<"sus acciones y...\n";
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: espera, que estoy haciendo??Dejandome matar por una persona que\n";
                            cout<<"\tno tiene la menor idea de mis heroicos actos, de mi legado, de mi ser...no, un Dragon de mi linaje\n";
                            cout<<"\tno puede morir de esta forma tan patetica. Preparate para nuestra pelea, será de las cosas más dificiles que\n";
                            cout<<"hayas hecho nunca...muah...jjajajaja..coff.cofff...\n";
                        }else if (op5==2){
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: a veces, y solo a veces son necesarias las peleas pero esta vez será\n";
                            cout<<"\talgo muy sensillo,pero...por qué debería serlo, por qué me tengo tando desprecio a mi mismo??\n";
                            cout<<"\tOlvidalo por completo, PREPARATE A SER CARBONNIZADO JAJAJAJAJAJA\n";
                        }else{
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: no,no,no,no,no...no necesito tu perdon, no necesito el de nadie\n";
                            cout<<"\tTú jamas me entenderías simple mortal, acabaré con tu vida, así como la de la gente que me lo himploró\n";
                            cout<<"coff...coff....\n";
                        }
                        if (batallaPorTurnos(personaje, "JUMEX EL GRAN DRAGON BLANCO DE OJOS AZULES", 2, pociones, pocionesMax, escudos, ataqueMortal)){
                            cout<<"Esta ha sido mi ultima batalla, coff..coff, nunca fuiste realmente un rival para mi, yo no morireeee en las manos\n";
                            cout<<"de un simple mortaaaaaaaalll AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH...aaaaaaaaaaaaaaah...\n";
                            cout<<"Un liquido brumoso purpura empieza a sacar por todos los orificios del cuerpo, cae al aspero suelo y finalmente\n\n";
                            cout<<"JUMEX, EL GRAN DRAGON BLANCO DE OJOS AZULES muere\n";
                            cout<<"Corazones actuales: "<<corazones<<endl;
                            return true;

                        }else{
                            cout<<"Te lo dije, un gran ser como yo es imposible de matar...espero que la proxima vez sea distinto, aqui estaré\n";
                            cout<<personaje<<" tirado en el suelo y sufriendo de agonia, mira al dragon y da su ultimo suspiro....has muerto\n";
                            cout<<"El dragon se come tu cadaver y con ello, todos tus corazones\n";
                            corazones = 0;
                            cout<<"Corazones actuales"<<corazones<<endl;
                            return false;

                        }
                    }
                    //End dragon y Bosques Perdidos
                    break;

                default:
                    cout<<"Opcion no disponible\n";
                    break;
                }
                
            }
            if (corazones<=0){
                cout<<"Has perdido\n";
            }
            break;
        case 2://Primera opcion
            //Hablar con el oso
            cout<<"---------------------------------------------------------------------------------------------------------\n";
            cout<<"Oso: qué sucede, te dí tanto miedo como para atreverte a pelear conmigo??, vamos no soy un moustro\n";
            cout<<"\to eso me han dicho, mamá dice que no hable de eso...jeje...\n";
            cout<<"\testá bien, está bien, si adivinas mi color favorito te dejaré pasar, para no complicarte mucho\n";
            cout<<"\tlas cosas solo te dire que es el resultado de combinar los colores rojo y amarillo\n\n";
            cout<<"-----------------------------------------------------------------------------------------------\n";
            cout<<"Qué respondes??\n\n[1] Naranja\n[2] Anaranjado\n[3] Narajo\n\n";
            cin>>op2;
            if(op2==2){
                cout<<"Oso: Felicidades has adivinado mi color favorito, puedes pasar, supongo...jeje...:s\n";
            }else{
                cout<<"Oso: Opps, ese no es mi color favorito, a pesar de ser muy parecido... jeje...\n";
                cout<<"\tcomo sea, eso de escoger colores no se le da a todos, en fin, supongo que entonces te dejaré\n";
                cout<<"\tpasar, claro, antes te arrancaré uno de tus tres corazones, ya sabes, como sacrificio...jeje\n";
                corazones--;
                cout<<"Corazones actuales: "<<corazones<<endl;
            }
            //End OSO
            cout<<"---------------------------------------------------------------------------------------------------------\n";
            cout<<personaje<<" se adentra aún más en el bosque y a lo lejos escucha una peleea, al parecer es entre un\n";
            cout<<"ratón y una serpiente, los movimientos rapidos del ratón despistan un poco a la serpiente pero no se\n";
            cout<<"deja intimidar por nada del mundo, finalmente, logra encajar una mordida abrazadora en la espina dorsal\n";
            cout<<"del ratón, empezando el proceso de licuacion de organos para posteriormente absorverlos a travez\n";
            cout<<"de sus colmillos.";
            cout<<"-----------------------------------------------------------------------------------------------------------\n";
            cout<<"Te acercas sigilosamente, pero la serpiente se acerca a ti rapidamente...";
            cout<<"Serpiente: A donde crees que ibasssss, si desearme un buen probechosssssss??, en este bosque la gente que se\n";
            cout<<"\tpierdessss, es deborada por alguna variante mía, pero más o menos letal, al parecer te llegó un poco tarde\n";
            cout<<"el mensaje sobre la hora de comer, pero ya que estas aqui, no me dejas otra alternativasssss...\n";
            cout<<"-----------------------------------------------------------------------------------------------------------\n";
            while (corazones > 0){
                cout<<"Serpiente Indú te queda viendo fijamente, que quieres hacer??\n\n[1] Pelear\n[2] Hablar\n[3] Pagar\n\n";
                cin>>op2;
                switch (op2)
                {
                case 1:
                    //Pelea contra serpiente indu
                    cout<<personaje<<" se acerca con determinacion...\n";
                    cout<<"Serpiente Indú, veo lo que intentasssss, veo a travezzzzz de tu ser, tus pecadossssss, tu hisssstoria, nada increible\n";
                    cout<<"\tessssspero hallassss traido algun antiveneno si no ve preparandote para una gran agonia\n";
                    if(batallaPorTurnos(personaje, "Serpiente Indú", dificultad, pociones, pocionesMax, escudos, ataqueMortal)){
                        cout<<"Serpiente Indú: Sssii, es cierto no lo que cuentan por ahí, malaventuraos los seguidores de la avaricia y la codicia\n";
                    }else{
                        cout<<"Serpiente Indú: Que es lo que veo?? otro ser arrastrandose y suplicando por su perdon por estar en el momento y lugar\n";
                        cout<<"\tequivocado??. Creo que ya sabes como es esto, tengo que arrebatarte ese calido corazon con mis frias escamassss\n";
                        corazones--;
                        cout<<"Corazones actuales: "<<corazones<<endl;
                    }
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    //End serpiente indú
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<personaje<<" empieza a desmotivarse por todo el asunto de si realmente vale la pena seguir en busqueda de\n";
                    cout<<"esa tal piedra, pero sin embargo decide no rendirse y procurar seguir adelante con sus motivaciones, \n";
                    cout<<"ese prestamos a los burgueses no se va a pagar solo.\n";
                    cout<<"El bosque a pesar de ser un lugar bastante obtuso sigue siendo una de las grandes obras magnas de la naturaleza\n";
                    cout<<"en los antiguos libros de hechizos y magias paganas, se dice que los origenes del bosque son indecifrables.\n";
                    cout<<"Las primeras investigaciones que se hicieron sobre el bosque fue sobre muestras de cortesas de arbol,\n";
                    cout<<"pues los aros de los troncos revelaría con certeza su edad y a partir de ahí estimarian tiempos junto con\n";
                    cout<<"otras muestras del sedimento y del micelio blanco que crece alrededor del perimetro del boosque, pero que \n";
                    cout<<"sin embargo, al intentar partir los arboles, estos parecian indestructibles, ni con la fuerza de 20 hombres\n";
                    cout<<"era capaz de fragmentarse un solo pedazo de madera, al parecer los arboles secretaban naturalemente\n";
                    cout<<"una especie de baba pegajosa que puede ser usada como catalizador alquimico, incluso hay registros de que\n";
                    cout<<"al ser ingerido puede hacer que la persona persiva \"otra vida\", pues se asegura que puedes experimentar\n";
                    cout<<"otra vida muy distinta a la propia, con entornos y consecuecias diferentes salvo una sola constante\n";
                    cout<<"el NECRONOMICON.\n";
                    cout<<personaje<<" se sube a la copa de un arbol, intentando ver el final del bosque, pero este parece no terminar,\n";
                    cout<<"para no perderse, empieza a marcar los arboles por donde ya ha pasado, sin embargo, empieza a notar algo extraño\n";
                    cout<<"Los arboles que al principio solo tenian una marca vuelven a aparecer "<<personaje<<" empieza a sospechar sobre si\n";
                    cout<<"ha estado caminando en ciculos, hasta que...encuentra un patron en los arboles: forman tren hileras\n";
                    cout<<"el clima empieza a mostrar una cara gris, y algunas gotas se empiezan a persivir, buscando donde refugiarse\n";
                    cout<<"encuentra un techo de hojas, es como si alguien estuviera viviendo ahí, durante un tiempo...\n";
                    cout<<"DESCONOCIDO: Hey, que haces durmiendo ahí, uno ya no puede ir por algunos conejos sin que le roben su refugio\n";
                    cout<<"\tsé que el bosque parece interminable pero hay lugar para ambos, vale?, te dejaré quedarte pero nada de timos\n";
                    cout<<"\tsoy el ultimo protector que queda del dragon JUMEX, ese dragon se apoderó de todos los frutos del bosque \n";
                    cout<<"\tdesde hace un tiempo, desde entonces solo nos queda matarnos entre nosotros, los habitantes del Bosque Perdido\n";
                    cout<<"\tha decir verdad, los bucles entre arboles son bastante común entre mas te acercas al dragon, de vez en cuando\n";
                    cout<<"\tcuando el clima cambia el dragon pierde un poco de magia y tranquiliza la randomizacion del bosque. En fin, duerme.\n";
                    cout<<"\n\nAl día siguiente "<<personaje<<" le dió las gracias por su hospitalidad al ser Anaranjado Manchinegro.\n";
                    cout<<"Dandole adios a KKKKKN\n";
                    cout<<personaje<<" comieza a perder la determinacion, pero se acuerda del dinero por la PIEDRA FILOSOFAL y se le pasa\n";
                    cout<<"Despues de haber caminado durante 3 dias y 3 noches,"<<personaje<<" finalmente encuentra el templo del Dragon JUMEX\n";
                    cout<<"el templo es una esctructura monolitica de forma piramida invertida, con rios por algunas salidas del templo\n";
                    cout<<"y desgastado por el tiempo. Al seguir caminando, "<<personaje<<" se encuentra con un viejo conocido, KKKKKN,\n";
                    cout<<"KKKKKN: Sabría que vendrias, pero no pensé que llegarías tan lejos, como sabras es mi deber proteger a este dragon\n";
                    cout<<"\tle debo la vida de mis seres queridos, cuando la nacion enemiga de mi pueblo atacó, JUMEX, en su grandeza,\n";
                    cout<<"dió la cara y con sus llamaradas elimino al ejercito enemigo. Ese día, toda mi generacion le juró lealtad junto\n";
                    cout<<"con algunas otras familias. Pero ahora solo quedo yo, y no dejaré que sigas avanzando...\n";
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<"\n\nQue deseas hacer??[1] Pelear\t[2] Pelear\t[3] Pelear\n";
                    cin>>op4;
                    while (corazones>0)
                    {
                        //Pelea, Pelea, Pelea
                        if (batallaPorTurnos(personaje,"KKKKKN",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                            cout<<"KKKKKN: Le he jurado lealtad al grand Dragon JUMEX, mi cuerpo calló, pero mi alma siempre estará en deuda\n";
                            cout<<"\tdespues de tanto, esta vida no fue lo que necesitaba, pero era lo que quería, gracias por testerrarme\n";
                            cout<<"\tde este tormento, por fin podré reunirme con mi pueblo, mi tribu...mi familia...\n";
                            cout<<"En medio de la agonía de KKKKKN, reune pocas de sus fuerzas, se arrebata su unico corazon del pecho\n";
                            cout<<"y te lo ofrese como trofeo...simplemente lo aceptas.\n";
                            corazones+=1;
                            cout<<"Corazones actuales: "<<corazones<<endl;
                        }else{
                            cout<<"KKKKKN: La sangre de otro mortal vuelve a manchar mi espada de sangre, que con aquejo y remordimiento\n";
                            cout<<"\nespero que la proxima vez pueda encontrar la paz\n";
                            corazones-=0;
                            if (corazones-=0){
                                return false;
                            }
                        }
                        //End KKKKKN
                        cout<<"-----------------------------------------------------------------------------------------------------------\n";
                        cout<<personaje<<" ha recorrido bastante el suelo que hoy tiene lugar a un templo sagrado y protegido por un linaje\n";
                        cout<<"de guardianes tratando de encontrar la paz en su deber, en un juramento, en un una idea.\n";
                        cout<<"Al adentrarse en el gran templo, las cosas parecen estar muy abandonadas, los pisos con cubiertos por gruesas\n";
                        cout<<"y pesadas capas de polvo formando un aura de abandono profundo, sin embargo tras caminar un tiempo\n";
                        cout<<"se logran ver algunas huellas que se repiten a si mismas, al parecer son las huellas de un Jaguar\n";
                        cout<<"parece ser que KKKKKN recorria constantemente los pasillos vacios y oscuros, así que "<<personaje<<"decide \n";
                        cout<<"seguir el rastro, mientras sigue las marcas en el piso, se pueden apreciar en los muros una cierta leyenda\n";
                        cout<<"al parecer los muros fueron pintados con un estilo muy ruprestre, no se logra ver muy bien, el paso del tiempo\n";
                        cout<<"ha hecho que se borre la pintura pero parcialmente se puede apreciar una especia de dragon blanco\n";
                        cout<<"de ojos azules saliendo del Sol en direccion para un grupo de personas, tambien hay una rota, falta un fragmento\n";
                        cout<<"solo se logra ver lo que parece una persona alzando algo....tal vez no sea importante...\n";
                        cout<<"A lo lejos se escucha un rugido temible, seguido de un golpe constante, un compas confuso de flauta se logra\n";
                        cout<<"distinguir, al ritmo se suma algunos tambores muy tribales, arpas y algunos instrumentos de cuerda.\n";
                        cout<<personaje<<" decide seguir la musica, sube unas escaleras en forma de caracol de una aparente torre y llega a \n ";
                        cout<<"una camara en donde resuena los tambores, ahí ve un dragon blanco dormido, una gran hoguera y los musicos\n";
                        cout<<"disfrutando la complicidad, la union y el rito. De repente, un grupo encapuchado empieza a escoger personas\n";
                        cout<<"aparentemente al azar, usan una especie de rampa imprivizada y lo dejan caer a la boca del dragon quien\n";
                        cout<<"instintivamente abrió el hocico, dejando algunas llamas en el aire. Las personas encapuchadas vuelven a escoger\n";
                        cout<<"personas, separando a una familia, se llevan a una madre y a su hija, el padre implora que las dejen en paz\n";
                        cout<<"entre gritos y sollozos, la hija se libera por un instante y luego dejan caer a la madre a la boca del dragon\n";
                        cout<<"mientras la madre cae, la hija corre a los brazos del padre, el padre enfurecido, en un movimiento rapido\n";
                        cout<<"carga a su hija y le arrebata un leño a la hoguera, su mirada lo dice todo, solo quire salir de ahí\n";
                        cout<<"Entre lagrimas, la hija pregunta por su madre, aún no comprende que acaba de pasar, simplemente no lo asimila\n";
                        cout<<"el padre al verse acorralado, decide subir por la rampa y saltar, el dragon abre la boca pero es tarde\n";
                        cout<<"el padre le ha clavado un leño en su ojo izquierdo. Con el ojo enrojesido el Gran Dragon Blanco se levanta\n";
                        cout<<"Y muestra su imponente forma, dando un rugido muy feroz, capaz de sacar volando a todo el culto, el padre\n";
                        cout<<"logra verte y en un breve momento de contacto visual, desaparece...El Dragon intenta volar, sin embargo tiene\n";
                        cout<<"una de sus alas rotas ya, desconocido es si aun su equilibro en orden está, al intentar levantarse no logra superar\n";
                        cout<<"los 10 segundos seguidos en una pocicion estable. Una corroida sustancia es expulsada de su boca. El legendario\n";
                        cout<<"dragon está muriendo. JUMEX, nota tu presencia, alcanza a verte con el rabillo de su ojo aun en paz\n";
                        cout<<personaje<<" decide acercase con determinacion...El momento se detiene, los flujos de agua cayendo se detienen\n";
                        cout<<"y el tiempo lo hace tambien, escuha una extraña voz agrietada y corrompida\n";
                        cout<<"\nJUMEX, el gran dragon de ojos azules: Estas aquí por esa baratija de piedra, cierto?? Bueno, tengo malas noticias\n";
                        cout<<"\tesa cosa nunca existió, solo fueron inventos de gente rechazada por la sociedad inventó, el sistema les falló\n";
                        cout<<"\tcomo puedes ver ahora los grupos de extraños me llaman una leyenda, pero que soy si no otro dragon\n";
                        cout<<"\tlas historias que se cuentan de mi, son solo grandes enagenaciones de mitos revueltos en la mente\n";
                        cout<<"\thumana, un parasito social que solo aferra a los más necesitados a un puño de promesas vacias\n ";
                        cout<<"\tPero, ya estoy cansado de todo esto, necesito descansar, necesito encontrar el equilibrio, pero qué clase de\n";
                        cout<<"\tequilibrio puede conseguir una lagartija gigante??. Te lo suplico, por favor acaba conmigo, solo quiero morir\n";
                        cout<<"\tdeseo salir de este mundo que me ha hecho tanto daño.Harias eso por mi??\n";
                        cout<<"-----------------------------------------------------------------------------------------------------------\n\n";
                        cout<<"Que deseas hacer??\n\n[1] Matar\t[2] Pelear\t[3] Perdonar\n\n";
                        cin>>op5;
                        if (op5==1){
                            cout<<personaje<<" toma su espada, desevaina la hoja, toma un respiro, hinhala, exhala, encuentra determinacion en\n";
                            cout<<"sus acciones y...\n";
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: espera, que estoy haciendo??Dejandome matar por una persona que\n";
                            cout<<"\tno tiene la menor idea de mis heroicos actos, de mi legado, de mi ser...no, un Dragon de mi linaje\n";
                            cout<<"\tno puede morir de esta forma tan patetica. Preparate para nuestra pelea, será de las cosas más dificiles que\n";
                            cout<<"hayas hecho nunca...muah...jjajajaja..coff.cofff...\n";
                        }else if (op5==2){
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: a veces, y solo a veces son necesarias las peleas pero esta vez será\n";
                            cout<<"\talgo muy sensillo,pero...por qué debería serlo, por qué me tengo tando desprecio a mi mismo??\n";
                            cout<<"\tOlvidalo por completo, PREPARATE A SER CARBONNIZADO JAJAJAJAJAJA\n";
                        }else{
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: no,no,no,no,no...no necesito tu perdon, no necesito el de nadie\n";
                            cout<<"\tTú jamas me entenderías simple mortal, acabaré con tu vida, así como la de la gente que me lo himploró\n";
                            cout<<"coff...coff....\n";
                        }
                        if (batallaPorTurnos(personaje, "JUMEX EL GRAN DRAGON BLANCO DE OJOS AZULES", 2, pociones, pocionesMax, escudos, ataqueMortal)){
                            cout<<"Esta ha sido mi ultima batalla, coff..coff, nunca fuiste realmente un rival para mi, yo no morireeee en las manos\n";
                            cout<<"de un simple mortaaaaaaaalll AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH...aaaaaaaaaaaaaaah...\n";
                            cout<<"Un liquido brumoso purpura empieza a sacar por todos los orificios del cuerpo, cae al aspero suelo y finalmente\n\n";
                            cout<<"JUMEX, EL GRAN DRAGON BLANCO DE OJOS AZULES muere\n";
                            cout<<"Corazones actuales: "<<corazones<<endl;
                            return true;

                        }else{
                            cout<<"Te lo dije, un gran ser como yo es imposible de matar...espero que la proxima vez sea distinto, aqui estaré\n";
                            cout<<personaje<<" tirado en el suelo y sufriendo de agonia, mira al dragon y da su ultimo suspiro....has muerto\n";
                            cout<<"El dragon se come tu cadaver y con ello, todos tus corazones\n";
                            corazones = 0;
                            cout<<"Corazones actuales"<<corazones<<endl;
                            return false;

                        }
                    }
                    //End dragon y Bosques Perdidos

                    break;
                case 2:
                    //Habla con serpiente Indú
                    cout<<"Serpiente Indú: Espera, no queriassss quitarme mi comida???, Debisste haberlo mencionado antesss, todo esto es un simple mal\n";
                    cout<<"\tentendidosss, de ser por mi, puedes pasar a dodne quieras, en este bosque las cosas son más simples de lo que parece\n";
                    cout<<"Serpiente Indú, te ha dejado pasar sin aparentemente ningun problema\n";
                    cout<<"Corazones actuales: "<<corazones<<endl;
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    //End serpiente indú
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<personaje<<" empieza a desmotivarse por todo el asunto de si realmente vale la pena seguir en busqueda de\n";
                    cout<<"esa tal piedra, pero sin embargo decide no rendirse y procurar seguir adelante con sus motivaciones, \n";
                    cout<<"ese prestamos a los burgueses no se va a pagar solo.\n";
                    cout<<"El bosque a pesar de ser un lugar bastante obtuso sigue siendo una de las grandes obras magnas de la naturaleza\n";
                    cout<<"en los antiguos libros de hechizos y magias paganas, se dice que los origenes del bosque son indecifrables.\n";
                    cout<<"Las primeras investigaciones que se hicieron sobre el bosque fue sobre muestras de cortesas de arbol,\n";
                    cout<<"pues los aros de los troncos revelaría con certeza su edad y a partir de ahí estimarian tiempos junto con\n";
                    cout<<"otras muestras del sedimento y del micelio blanco que crece alrededor del perimetro del boosque, pero que \n";
                    cout<<"sin embargo, al intentar partir los arboles, estos parecian indestructibles, ni con la fuerza de 20 hombres\n";
                    cout<<"era capaz de fragmentarse un solo pedazo de madera, al parecer los arboles secretaban naturalemente\n";
                    cout<<"una especie de baba pegajosa que puede ser usada como catalizador alquimico, incluso hay registros de que\n";
                    cout<<"al ser ingerido puede hacer que la persona persiva \"otra vida\", pues se asegura que puedes experimentar\n";
                    cout<<"otra vida muy distinta a la propia, con entornos y consecuecias diferentes salvo una sola constante\n";
                    cout<<"el NECRONOMICON.\n";
                    cout<<personaje<<" se sube a la copa de un arbol, intentando ver el final del bosque, pero este parece no terminar,\n";
                    cout<<"para no perderse, empieza a marcar los arboles por donde ya ha pasado, sin embargo, empieza a notar algo extraño\n";
                    cout<<"Los arboles que al principio solo tenian una marca vuelven a aparecer "<<personaje<<" empieza a sospechar sobre si\n";
                    cout<<"ha estado caminando en ciculos, hasta que...encuentra un patron en los arboles: forman tren hileras\n";
                    cout<<"el clima empieza a mostrar una cara gris, y algunas gotas se empiezan a persivir, buscando donde refugiarse\n";
                    cout<<"encuentra un techo de hojas, es como si alguien estuviera viviendo ahí, durante un tiempo...\n";
                    cout<<"DESCONOCIDO: Hey, que haces durmiendo ahí, uno ya no puede ir por algunos conejos sin que le roben su refugio\n";
                    cout<<"\tsé que el bosque parece interminable pero hay lugar para ambos, vale?, te dejaré quedarte pero nada de timos\n";
                    cout<<"\tsoy el ultimo protector que queda del dragon JUMEX, ese dragon se apoderó de todos los frutos del bosque \n";
                    cout<<"\tdesde hace un tiempo, desde entonces solo nos queda matarnos entre nosotros, los habitantes del Bosque Perdido\n";
                    cout<<"\tha decir verdad, los bucles entre arboles son bastante común entre mas te acercas al dragon, de vez en cuando\n";
                    cout<<"\tcuando el clima cambia el dragon pierde un poco de magia y tranquiliza la randomizacion del bosque. En fin, duerme.\n";
                    cout<<"\n\nAl día siguiente "<<personaje<<" le dió las gracias por su hospitalidad al ser Anaranjado Manchinegro.\n";
                    cout<<"Dandole adios a KKKKKN\n";
                    cout<<personaje<<" comieza a perder la determinacion, pero se acuerda del dinero por la PIEDRA FILOSOFAL y se le pasa\n";
                    cout<<"Despues de haber caminado durante 3 dias y 3 noches,"<<personaje<<" finalmente encuentra el templo del Dragon JUMEX\n";
                    cout<<"el templo es una esctructura monolitica de forma piramida invertida, con rios por algunas salidas del templo\n";
                    cout<<"y desgastado por el tiempo. Al seguir caminando, "<<personaje<<" se encuentra con un viejo conocido, KKKKKN,\n";
                    cout<<"KKKKKN: Sabría que vendrias, pero no pensé que llegarías tan lejos, como sabras es mi deber proteger a este dragon\n";
                    cout<<"\tle debo la vida de mis seres queridos, cuando la nacion enemiga de mi pueblo atacó, JUMEX, en su grandeza,\n";
                    cout<<"dió la cara y con sus llamaradas elimino al ejercito enemigo. Ese día, toda mi generacion le juró lealtad junto\n";
                    cout<<"con algunas otras familias. Pero ahora solo quedo yo, y no dejaré que sigas avanzando...\n";
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<"\n\nQue deseas hacer??[1] Pelear\t[2] Pelear\t[3] Pelear\n";
                    cin>>op4;
                    while (corazones>0)
                    {
                        //Pelea, Pelea, Pelea
                        if (batallaPorTurnos(personaje,"KKKKKN",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                            cout<<"KKKKKN: Le he jurado lealtad al grand Dragon JUMEX, mi cuerpo calló, pero mi alma siempre estará en deuda\n";
                            cout<<"\tdespues de tanto, esta vida no fue lo que necesitaba, pero era lo que quería, gracias por testerrarme\n";
                            cout<<"\tde este tormento, por fin podré reunirme con mi pueblo, mi tribu...mi familia...\n";
                            cout<<"En medio de la agonía de KKKKKN, reune pocas de sus fuerzas, se arrebata su unico corazon del pecho\n";
                            cout<<"y te lo ofrese como trofeo...simplemente lo aceptas.\n";
                            corazones+=1;
                            cout<<"Corazones actuales: "<<corazones<<endl;
                        }else{
                            cout<<"KKKKKN: La sangre de otro mortal vuelve a manchar mi espada de sangre, que con aquejo y remordimiento\n";
                            cout<<"\nespero que la proxima vez pueda encontrar la paz\n";
                            corazones-=0;
                            if (corazones-=0){
                                return false;
                            }
                        }
                        //End KKKKKN
                        cout<<"-----------------------------------------------------------------------------------------------------------\n";
                        cout<<personaje<<" ha recorrido bastante el suelo que hoy tiene lugar a un templo sagrado y protegido por un linaje\n";
                        cout<<"de guardianes tratando de encontrar la paz en su deber, en un juramento, en un una idea.\n";
                        cout<<"Al adentrarse en el gran templo, las cosas parecen estar muy abandonadas, los pisos con cubiertos por gruesas\n";
                        cout<<"y pesadas capas de polvo formando un aura de abandono profundo, sin embargo tras caminar un tiempo\n";
                        cout<<"se logran ver algunas huellas que se repiten a si mismas, al parecer son las huellas de un Jaguar\n";
                        cout<<"parece ser que KKKKKN recorria constantemente los pasillos vacios y oscuros, así que "<<personaje<<"decide \n";
                        cout<<"seguir el rastro, mientras sigue las marcas en el piso, se pueden apreciar en los muros una cierta leyenda\n";
                        cout<<"al parecer los muros fueron pintados con un estilo muy ruprestre, no se logra ver muy bien, el paso del tiempo\n";
                        cout<<"ha hecho que se borre la pintura pero parcialmente se puede apreciar una especia de dragon blanco\n";
                        cout<<"de ojos azules saliendo del Sol en direccion para un grupo de personas, tambien hay una rota, falta un fragmento\n";
                        cout<<"solo se logra ver lo que parece una persona alzando algo....tal vez no sea importante...\n";
                        cout<<"A lo lejos se escucha un rugido temible, seguido de un golpe constante, un compas confuso de flauta se logra\n";
                        cout<<"distinguir, al ritmo se suma algunos tambores muy tribales, arpas y algunos instrumentos de cuerda.\n";
                        cout<<personaje<<" decide seguir la musica, sube unas escaleras en forma de caracol de una aparente torre y llega a \n ";
                        cout<<"una camara en donde resuena los tambores, ahí ve un dragon blanco dormido, una gran hoguera y los musicos\n";
                        cout<<"disfrutando la complicidad, la union y el rito. De repente, un grupo encapuchado empieza a escoger personas\n";
                        cout<<"aparentemente al azar, usan una especie de rampa imprivizada y lo dejan caer a la boca del dragon quien\n";
                        cout<<"instintivamente abrió el hocico, dejando algunas llamas en el aire. Las personas encapuchadas vuelven a escoger\n";
                        cout<<"personas, separando a una familia, se llevan a una madre y a su hija, el padre implora que las dejen en paz\n";
                        cout<<"entre gritos y sollozos, la hija se libera por un instante y luego dejan caer a la madre a la boca del dragon\n";
                        cout<<"mientras la madre cae, la hija corre a los brazos del padre, el padre enfurecido, en un movimiento rapido\n";
                        cout<<"carga a su hija y le arrebata un leño a la hoguera, su mirada lo dice todo, solo quire salir de ahí\n";
                        cout<<"Entre lagrimas, la hija pregunta por su madre, aún no comprende que acaba de pasar, simplemente no lo asimila\n";
                        cout<<"el padre al verse acorralado, decide subir por la rampa y saltar, el dragon abre la boca pero es tarde\n";
                        cout<<"el padre le ha clavado un leño en su ojo izquierdo. Con el ojo enrojesido el Gran Dragon Blanco se levanta\n";
                        cout<<"Y muestra su imponente forma, dando un rugido muy feroz, capaz de sacar volando a todo el culto, el padre\n";
                        cout<<"logra verte y en un breve momento de contacto visual, desaparece...El Dragon intenta volar, sin embargo tiene\n";
                        cout<<"una de sus alas rotas ya, desconocido es si aun su equilibro en orden está, al intentar levantarse no logra superar\n";
                        cout<<"los 10 segundos seguidos en una pocicion estable. Una corroida sustancia es expulsada de su boca. El legendario\n";
                        cout<<"dragon está muriendo. JUMEX, nota tu presencia, alcanza a verte con el rabillo de su ojo aun en paz\n";
                        cout<<personaje<<" decide acercase con determinacion...El momento se detiene, los flujos de agua cayendo se detienen\n";
                        cout<<"y el tiempo lo hace tambien, escuha una extraña voz agrietada y corrompida\n";
                        cout<<"\nJUMEX, el gran dragon de ojos azules: Estas aquí por esa baratija de piedra, cierto?? Bueno, tengo malas noticias\n";
                        cout<<"\tesa cosa nunca existió, solo fueron inventos de gente rechazada por la sociedad inventó, el sistema les falló\n";
                        cout<<"\tcomo puedes ver ahora los grupos de extraños me llaman una leyenda, pero que soy si no otro dragon\n";
                        cout<<"\tlas historias que se cuentan de mi, son solo grandes enagenaciones de mitos revueltos en la mente\n";
                        cout<<"\thumana, un parasito social que solo aferra a los más necesitados a un puño de promesas vacias\n ";
                        cout<<"\tPero, ya estoy cansado de todo esto, necesito descansar, necesito encontrar el equilibrio, pero qué clase de\n";
                        cout<<"\tequilibrio puede conseguir una lagartija gigante??. Te lo suplico, por favor acaba conmigo, solo quiero morir\n";
                        cout<<"\tdeseo salir de este mundo que me ha hecho tanto daño.Harias eso por mi??\n";
                        cout<<"-----------------------------------------------------------------------------------------------------------\n\n";
                        cout<<"Que deseas hacer??\n\n[1] Matar\t[2] Pelear\t[3] Perdonar\n\n";
                        cin>>op5;
                        if (op5==1){
                            cout<<personaje<<" toma su espada, desevaina la hoja, toma un respiro, hinhala, exhala, encuentra determinacion en\n";
                            cout<<"sus acciones y...\n";
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: espera, que estoy haciendo??Dejandome matar por una persona que\n";
                            cout<<"\tno tiene la menor idea de mis heroicos actos, de mi legado, de mi ser...no, un Dragon de mi linaje\n";
                            cout<<"\tno puede morir de esta forma tan patetica. Preparate para nuestra pelea, será de las cosas más dificiles que\n";
                            cout<<"hayas hecho nunca...muah...jjajajaja..coff.cofff...\n";
                        }else if (op5==2){
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: a veces, y solo a veces son necesarias las peleas pero esta vez será\n";
                            cout<<"\talgo muy sensillo,pero...por qué debería serlo, por qué me tengo tando desprecio a mi mismo??\n";
                            cout<<"\tOlvidalo por completo, PREPARATE A SER CARBONNIZADO JAJAJAJAJAJA\n";
                        }else{
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: no,no,no,no,no...no necesito tu perdon, no necesito el de nadie\n";
                            cout<<"\tTú jamas me entenderías simple mortal, acabaré con tu vida, así como la de la gente que me lo himploró\n";
                            cout<<"coff...coff....\n";
                        }
                        if (batallaPorTurnos(personaje, "JUMEX EL GRAN DRAGON BLANCO DE OJOS AZULES", 2, pociones, pocionesMax, escudos, ataqueMortal)){
                            cout<<"Esta ha sido mi ultima batalla, coff..coff, nunca fuiste realmente un rival para mi, yo no morireeee en las manos\n";
                            cout<<"de un simple mortaaaaaaaalll AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH...aaaaaaaaaaaaaaah...\n";
                            cout<<"Un liquido brumoso purpura empieza a sacar por todos los orificios del cuerpo, cae al aspero suelo y finalmente\n\n";
                            cout<<"JUMEX, EL GRAN DRAGON BLANCO DE OJOS AZULES muere\n";
                            cout<<"Corazones actuales: "<<corazones<<endl;
                            return true;

                        }else{
                            cout<<"Te lo dije, un gran ser como yo es imposible de matar...espero que la proxima vez sea distinto, aqui estaré\n";
                            cout<<personaje<<" tirado en el suelo y sufriendo de agonia, mira al dragon y da su ultimo suspiro....has muerto\n";
                            cout<<"El dragon se come tu cadaver y con ello, todos tus corazones\n";
                            corazones = 0;
                            cout<<"Corazones actuales"<<corazones<<endl;
                            return false;

                        }
                    }
                    //End dragon y Bosques Perdidos
                    break;
                case 3:
                    //Pagar a serpiente indú
                    cout<<"Serpiente Indú: Espera, qué se supone que haga yo con essssso, solo soy una serpiente de origen desconocido, lo siento pero\n";
                    cout<<"\nno puedo dejarte hacer eso, total, ya cazé mi presa del día ...ssssss.sssss.ssss\n";
                    cout<<"Corazones actuales: "<<corazones<<endl;
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    //End serpiente indú
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<personaje<<" empieza a desmotivarse por todo el asunto de si realmente vale la pena seguir en busqueda de\n";
                    cout<<"esa tal piedra, pero sin embargo decide no rendirse y procurar seguir adelante con sus motivaciones, \n";
                    cout<<"ese prestamos a los burgueses no se va a pagar solo.\n";
                    cout<<"El bosque a pesar de ser un lugar bastante obtuso sigue siendo una de las grandes obras magnas de la naturaleza\n";
                    cout<<"en los antiguos libros de hechizos y magias paganas, se dice que los origenes del bosque son indecifrables.\n";
                    cout<<"Las primeras investigaciones que se hicieron sobre el bosque fue sobre muestras de cortesas de arbol,\n";
                    cout<<"pues los aros de los troncos revelaría con certeza su edad y a partir de ahí estimarian tiempos junto con\n";
                    cout<<"otras muestras del sedimento y del micelio blanco que crece alrededor del perimetro del boosque, pero que \n";
                    cout<<"sin embargo, al intentar partir los arboles, estos parecian indestructibles, ni con la fuerza de 20 hombres\n";
                    cout<<"era capaz de fragmentarse un solo pedazo de madera, al parecer los arboles secretaban naturalemente\n";
                    cout<<"una especie de baba pegajosa que puede ser usada como catalizador alquimico, incluso hay registros de que\n";
                    cout<<"al ser ingerido puede hacer que la persona persiva \"otra vida\", pues se asegura que puedes experimentar\n";
                    cout<<"otra vida muy distinta a la propia, con entornos y consecuecias diferentes salvo una sola constante\n";
                    cout<<"el NECRONOMICON.\n";
                    cout<<personaje<<" se sube a la copa de un arbol, intentando ver el final del bosque, pero este parece no terminar,\n";
                    cout<<"para no perderse, empieza a marcar los arboles por donde ya ha pasado, sin embargo, empieza a notar algo extraño\n";
                    cout<<"Los arboles que al principio solo tenian una marca vuelven a aparecer "<<personaje<<" empieza a sospechar sobre si\n";
                    cout<<"ha estado caminando en ciculos, hasta que...encuentra un patron en los arboles: forman tren hileras\n";
                    cout<<"el clima empieza a mostrar una cara gris, y algunas gotas se empiezan a persivir, buscando donde refugiarse\n";
                    cout<<"encuentra un techo de hojas, es como si alguien estuviera viviendo ahí, durante un tiempo...\n";
                    cout<<"DESCONOCIDO: Hey, que haces durmiendo ahí, uno ya no puede ir por algunos conejos sin que le roben su refugio\n";
                    cout<<"\tsé que el bosque parece interminable pero hay lugar para ambos, vale?, te dejaré quedarte pero nada de timos\n";
                    cout<<"\tsoy el ultimo protector que queda del dragon JUMEX, ese dragon se apoderó de todos los frutos del bosque \n";
                    cout<<"\tdesde hace un tiempo, desde entonces solo nos queda matarnos entre nosotros, los habitantes del Bosque Perdido\n";
                    cout<<"\tha decir verdad, los bucles entre arboles son bastante común entre mas te acercas al dragon, de vez en cuando\n";
                    cout<<"\tcuando el clima cambia el dragon pierde un poco de magia y tranquiliza la randomizacion del bosque. En fin, duerme.\n";
                    cout<<"\n\nAl día siguiente "<<personaje<<" le dió las gracias por su hospitalidad al ser Anaranjado Manchinegro.\n";
                    cout<<"Dandole adios a KKKKKN\n";
                    cout<<personaje<<" comieza a perder la determinacion, pero se acuerda del dinero por la PIEDRA FILOSOFAL y se le pasa\n";
                    cout<<"Despues de haber caminado durante 3 dias y 3 noches,"<<personaje<<" finalmente encuentra el templo del Dragon JUMEX\n";
                    cout<<"el templo es una esctructura monolitica de forma piramida invertida, con rios por algunas salidas del templo\n";
                    cout<<"y desgastado por el tiempo. Al seguir caminando, "<<personaje<<" se encuentra con un viejo conocido, KKKKKN,\n";
                    cout<<"KKKKKN: Sabría que vendrias, pero no pensé que llegarías tan lejos, como sabras es mi deber proteger a este dragon\n";
                    cout<<"\tle debo la vida de mis seres queridos, cuando la nacion enemiga de mi pueblo atacó, JUMEX, en su grandeza,\n";
                    cout<<"dió la cara y con sus llamaradas elimino al ejercito enemigo. Ese día, toda mi generacion le juró lealtad junto\n";
                    cout<<"con algunas otras familias. Pero ahora solo quedo yo, y no dejaré que sigas avanzando...\n";
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<"\n\nQue deseas hacer??[1] Pelear\t[2] Pelear\t[3] Pelear\n";
                    cin>>op4;
                    while (corazones>0)
                    {
                        //Pelea, Pelea, Pelea
                        if (batallaPorTurnos(personaje,"KKKKKN",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                            cout<<"KKKKKN: Le he jurado lealtad al grand Dragon JUMEX, mi cuerpo calló, pero mi alma siempre estará en deuda\n";
                            cout<<"\tdespues de tanto, esta vida no fue lo que necesitaba, pero era lo que quería, gracias por testerrarme\n";
                            cout<<"\tde este tormento, por fin podré reunirme con mi pueblo, mi tribu...mi familia...\n";
                            cout<<"En medio de la agonía de KKKKKN, reune pocas de sus fuerzas, se arrebata su unico corazon del pecho\n";
                            cout<<"y te lo ofrese como trofeo...simplemente lo aceptas.\n";
                            corazones+=1;
                            cout<<"Corazones actuales: "<<corazones<<endl;
                        }else{
                            cout<<"KKKKKN: La sangre de otro mortal vuelve a manchar mi espada de sangre, que con aquejo y remordimiento\n";
                            cout<<"\nespero que la proxima vez pueda encontrar la paz\n";
                            corazones-=0;
                            if (corazones-=0){
                                return false;
                            }
                        }
                        //End KKKKKN
                        cout<<"-----------------------------------------------------------------------------------------------------------\n";
                        cout<<personaje<<" ha recorrido bastante el suelo que hoy tiene lugar a un templo sagrado y protegido por un linaje\n";
                        cout<<"de guardianes tratando de encontrar la paz en su deber, en un juramento, en un una idea.\n";
                        cout<<"Al adentrarse en el gran templo, las cosas parecen estar muy abandonadas, los pisos con cubiertos por gruesas\n";
                        cout<<"y pesadas capas de polvo formando un aura de abandono profundo, sin embargo tras caminar un tiempo\n";
                        cout<<"se logran ver algunas huellas que se repiten a si mismas, al parecer son las huellas de un Jaguar\n";
                        cout<<"parece ser que KKKKKN recorria constantemente los pasillos vacios y oscuros, así que "<<personaje<<"decide \n";
                        cout<<"seguir el rastro, mientras sigue las marcas en el piso, se pueden apreciar en los muros una cierta leyenda\n";
                        cout<<"al parecer los muros fueron pintados con un estilo muy ruprestre, no se logra ver muy bien, el paso del tiempo\n";
                        cout<<"ha hecho que se borre la pintura pero parcialmente se puede apreciar una especia de dragon blanco\n";
                        cout<<"de ojos azules saliendo del Sol en direccion para un grupo de personas, tambien hay una rota, falta un fragmento\n";
                        cout<<"solo se logra ver lo que parece una persona alzando algo....tal vez no sea importante...\n";
                        cout<<"A lo lejos se escucha un rugido temible, seguido de un golpe constante, un compas confuso de flauta se logra\n";
                        cout<<"distinguir, al ritmo se suma algunos tambores muy tribales, arpas y algunos instrumentos de cuerda.\n";
                        cout<<personaje<<" decide seguir la musica, sube unas escaleras en forma de caracol de una aparente torre y llega a \n ";
                        cout<<"una camara en donde resuena los tambores, ahí ve un dragon blanco dormido, una gran hoguera y los musicos\n";
                        cout<<"disfrutando la complicidad, la union y el rito. De repente, un grupo encapuchado empieza a escoger personas\n";
                        cout<<"aparentemente al azar, usan una especie de rampa imprivizada y lo dejan caer a la boca del dragon quien\n";
                        cout<<"instintivamente abrió el hocico, dejando algunas llamas en el aire. Las personas encapuchadas vuelven a escoger\n";
                        cout<<"personas, separando a una familia, se llevan a una madre y a su hija, el padre implora que las dejen en paz\n";
                        cout<<"entre gritos y sollozos, la hija se libera por un instante y luego dejan caer a la madre a la boca del dragon\n";
                        cout<<"mientras la madre cae, la hija corre a los brazos del padre, el padre enfurecido, en un movimiento rapido\n";
                        cout<<"carga a su hija y le arrebata un leño a la hoguera, su mirada lo dice todo, solo quire salir de ahí\n";
                        cout<<"Entre lagrimas, la hija pregunta por su madre, aún no comprende que acaba de pasar, simplemente no lo asimila\n";
                        cout<<"el padre al verse acorralado, decide subir por la rampa y saltar, el dragon abre la boca pero es tarde\n";
                        cout<<"el padre le ha clavado un leño en su ojo izquierdo. Con el ojo enrojesido el Gran Dragon Blanco se levanta\n";
                        cout<<"Y muestra su imponente forma, dando un rugido muy feroz, capaz de sacar volando a todo el culto, el padre\n";
                        cout<<"logra verte y en un breve momento de contacto visual, desaparece...El Dragon intenta volar, sin embargo tiene\n";
                        cout<<"una de sus alas rotas ya, desconocido es si aun su equilibro en orden está, al intentar levantarse no logra superar\n";
                        cout<<"los 10 segundos seguidos en una pocicion estable. Una corroida sustancia es expulsada de su boca. El legendario\n";
                        cout<<"dragon está muriendo. JUMEX, nota tu presencia, alcanza a verte con el rabillo de su ojo aun en paz\n";
                        cout<<personaje<<" decide acercase con determinacion...El momento se detiene, los flujos de agua cayendo se detienen\n";
                        cout<<"y el tiempo lo hace tambien, escuha una extraña voz agrietada y corrompida\n";
                        cout<<"\nJUMEX, el gran dragon de ojos azules: Estas aquí por esa baratija de piedra, cierto?? Bueno, tengo malas noticias\n";
                        cout<<"\tesa cosa nunca existió, solo fueron inventos de gente rechazada por la sociedad inventó, el sistema les falló\n";
                        cout<<"\tcomo puedes ver ahora los grupos de extraños me llaman una leyenda, pero que soy si no otro dragon\n";
                        cout<<"\tlas historias que se cuentan de mi, son solo grandes enagenaciones de mitos revueltos en la mente\n";
                        cout<<"\thumana, un parasito social que solo aferra a los más necesitados a un puño de promesas vacias\n ";
                        cout<<"\tPero, ya estoy cansado de todo esto, necesito descansar, necesito encontrar el equilibrio, pero qué clase de\n";
                        cout<<"\tequilibrio puede conseguir una lagartija gigante??. Te lo suplico, por favor acaba conmigo, solo quiero morir\n";
                        cout<<"\tdeseo salir de este mundo que me ha hecho tanto daño.Harias eso por mi??\n";
                        cout<<"-----------------------------------------------------------------------------------------------------------\n\n";
                        cout<<"Que deseas hacer??\n\n[1] Matar\t[2] Pelear\t[3] Perdonar\n\n";
                        cin>>op5;
                        if (op5==1){
                            cout<<personaje<<" toma su espada, desevaina la hoja, toma un respiro, hinhala, exhala, encuentra determinacion en\n";
                            cout<<"sus acciones y...\n";
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: espera, que estoy haciendo??Dejandome matar por una persona que\n";
                            cout<<"\tno tiene la menor idea de mis heroicos actos, de mi legado, de mi ser...no, un Dragon de mi linaje\n";
                            cout<<"\tno puede morir de esta forma tan patetica. Preparate para nuestra pelea, será de las cosas más dificiles que\n";
                            cout<<"hayas hecho nunca...muah...jjajajaja..coff.cofff...\n";
                        }else if (op5==2){
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: a veces, y solo a veces son necesarias las peleas pero esta vez será\n";
                            cout<<"\talgo muy sensillo,pero...por qué debería serlo, por qué me tengo tando desprecio a mi mismo??\n";
                            cout<<"\tOlvidalo por completo, PREPARATE A SER CARBONNIZADO JAJAJAJAJAJA\n";
                        }else{
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: no,no,no,no,no...no necesito tu perdon, no necesito el de nadie\n";
                            cout<<"\tTú jamas me entenderías simple mortal, acabaré con tu vida, así como la de la gente que me lo himploró\n";
                            cout<<"coff...coff....";
                        }
                        if (batallaPorTurnos(personaje, "JUMEX EL GRAN DRAGON BLANCO DE OJOS AZULES", 2, pociones, pocionesMax, escudos, ataqueMortal)){
                            cout<<"Esta ha sido mi ultima batalla, coff..coff, nunca fuiste realmente un rival para mi, yo no morireeee en las manos\n";
                            cout<<"de un simple mortaaaaaaaalll AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH...aaaaaaaaaaaaaaah...\n";
                            cout<<"Un liquido brumoso purpura empieza a sacar por todos los orificios del cuerpo, cae al aspero suelo y finalmente\n\n";
                            cout<<"JUMEX, EL GRAN DRAGON BLANCO DE OJOS AZULES muere\n";
                            cout<<"Corazones actuales: "<<corazones<<endl;
                            return true;

                        }else{
                            cout<<"Te lo dije, un gran ser como yo es imposible de matar...espero que la proxima vez sea distinto, aqui estaré\n";
                            cout<<personaje<<" tirado en el suelo y sufriendo de agonia, mira al dragon y da su ultimo suspiro....has muerto\n";
                            cout<<"El dragon se come tu cadaver y con ello, todos tus corazones\n";
                            corazones = 0;
                            cout<<"Corazones actuales"<<corazones<<endl;
                            return false;

                        }
                    }
                    //End dragon y Bosques Perdidos
                    break;
                
                default:
                    cout<<"Opcion no disponible\n";
                    break;
                }
                
            }

            break;
        case 3://Primera opcion
            //Pagar al oso
            cout<<"---------------------------------------------------------------------------------------------------------\n";
            cout<<"Oso: Puedo ver que hay un poco de masoquismo en ti...jeje...no solo sé solo soy un Oso que hablar...jaja\n";
            cout<<personaje<<" arranca uno de sus corazones y se lo ofrese al osos como forma de pago";
            corazones--;
            cout<<"Corazones actuales: "<<corazones<<endl;
            cout<<"---------------------------------------------------------------------------------------------------------\n";
            cout<<personaje<<" se adentra aún más en el bosque y a lo lejos escucha una peleea, al parecer es entre un\n";
            cout<<"ratón y una serpiente, los movimientos rapidos del ratón despistan un poco a la serpiente pero no se\n";
            cout<<"deja intimidar por nada del mundo, finalmente, logra encajar una mordida abrazadora en la espina dorsal\n";
            cout<<"del ratón, empezando el proceso de licuacion de organos para posteriormente absorverlos a travez\n";
            cout<<"de sus colmillos.";
            cout<<"-----------------------------------------------------------------------------------------------------------\n";
            cout<<"Te acercas sigilosamente, pero la serpiente se acerca a ti rapidamente...\n";
            cout<<"Serpiente: A donde crees que ibasssss, si desearme un buen probechosssssss??, en este bosque la gente que se\n";
            cout<<"\tpierdessss, es deborada por alguna variante mía, pero más o menos letal, al parecer te llegó un poco tarde\n";
            cout<<"el mensaje sobre la hora de comer, pero ya que estas aqui, no me dejas otra alternativasssss...\n";
            cout<<"-----------------------------------------------------------------------------------------------------------\n";
            while (corazones > 0){
                cout<<"Serpiente Indú te queda viendo fijamente, que quieres hacer??\n\n[1] Pelear\n[2] Hablar\n[3] Pagar\n\n";
                cin>>op2;
                switch (op2)
                {
                case 1:
                    //Pelea contra serpiente indu
                    cout<<personaje<<" se acerca con determinacion...\n";
                    cout<<"Serpiente Indú, veo lo que intentasssss, veo a travezzzzz de tu ser, tus pecadossssss, tu hisssstoria, nada increible\n";
                    cout<<"\tessssspero hallassss traido algun antiveneno si no ve preparandote para una gran agonia\n";
                    if(batallaPorTurnos(personaje, "Serpiente Indú", dificultad, pociones, pocionesMax, escudos, ataqueMortal)){
                        cout<<"Serpiente Indú: Sssii, es cierto no lo que cuentan por ahí, malaventuraos los seguidores de la avaricia y la codicia\n";
                    }else{
                        cout<<"Serpiente Indú: Que es lo que veo?? otro ser arrastrandose y suplicando por su perdon por estar en el momento y lugar\n";
                        cout<<"\tequivocado??. Creo que ya sabes como es esto, tengo que arrebatarte ese calido corazon con mis frias escamassss\n";
                        corazones--;
                        cout<<"Corazones actuales: "<<corazones<<endl;
                    }
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    //End serpiente indú
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<personaje<<" empieza a desmotivarse por todo el asunto de si realmente vale la pena seguir en busqueda de\n";
                    cout<<"esa tal piedra, pero sin embargo decide no rendirse y procurar seguir adelante con sus motivaciones, \n";
                    cout<<"ese prestamos a los burgueses no se va a pagar solo.\n";
                    cout<<"El bosque a pesar de ser un lugar bastante obtuso sigue siendo una de las grandes obras magnas de la naturaleza\n";
                    cout<<"en los antiguos libros de hechizos y magias paganas, se dice que los origenes del bosque son indecifrables.\n";
                    cout<<"Las primeras investigaciones que se hicieron sobre el bosque fue sobre muestras de cortesas de arbol,\n";
                    cout<<"pues los aros de los troncos revelaría con certeza su edad y a partir de ahí estimarian tiempos junto con\n";
                    cout<<"otras muestras del sedimento y del micelio blanco que crece alrededor del perimetro del boosque, pero que \n";
                    cout<<"sin embargo, al intentar partir los arboles, estos parecian indestructibles, ni con la fuerza de 20 hombres\n";
                    cout<<"era capaz de fragmentarse un solo pedazo de madera, al parecer los arboles secretaban naturalemente\n";
                    cout<<"una especie de baba pegajosa que puede ser usada como catalizador alquimico, incluso hay registros de que\n";
                    cout<<"al ser ingerido puede hacer que la persona persiva \"otra vida\", pues se asegura que puedes experimentar\n";
                    cout<<"otra vida muy distinta a la propia, con entornos y consecuecias diferentes salvo una sola constante\n";
                    cout<<"el NECRONOMICON.\n";
                    cout<<personaje<<" se sube a la copa de un arbol, intentando ver el final del bosque, pero este parece no terminar,\n";
                    cout<<"para no perderse, empieza a marcar los arboles por donde ya ha pasado, sin embargo, empieza a notar algo extraño\n";
                    cout<<"Los arboles que al principio solo tenian una marca vuelven a aparecer "<<personaje<<" empieza a sospechar sobre si\n";
                    cout<<"ha estado caminando en ciculos, hasta que...encuentra un patron en los arboles: forman tren hileras\n";
                    cout<<"el clima empieza a mostrar una cara gris, y algunas gotas se empiezan a persivir, buscando donde refugiarse\n";
                    cout<<"encuentra un techo de hojas, es como si alguien estuviera viviendo ahí, durante un tiempo...\n";
                    cout<<"DESCONOCIDO: Hey, que haces durmiendo ahí, uno ya no puede ir por algunos conejos sin que le roben su refugio\n";
                    cout<<"\tsé que el bosque parece interminable pero hay lugar para ambos, vale?, te dejaré quedarte pero nada de timos\n";
                    cout<<"\tsoy el ultimo protector que queda del dragon JUMEX, ese dragon se apoderó de todos los frutos del bosque \n";
                    cout<<"\tdesde hace un tiempo, desde entonces solo nos queda matarnos entre nosotros, los habitantes del Bosque Perdido\n";
                    cout<<"\tha decir verdad, los bucles entre arboles son bastante común entre mas te acercas al dragon, de vez en cuando\n";
                    cout<<"\tcuando el clima cambia el dragon pierde un poco de magia y tranquiliza la randomizacion del bosque. En fin, duerme.\n";
                    cout<<"\n\nAl día siguiente "<<personaje<<" le dió las gracias por su hospitalidad al ser Anaranjado Manchinegro.\n";
                    cout<<"Dandole adios a KKKKKN\n";
                    cout<<personaje<<" comieza a perder la determinacion, pero se acuerda del dinero por la PIEDRA FILOSOFAL y se le pasa\n";
                    cout<<"Despues de haber caminado durante 3 dias y 3 noches,"<<personaje<<" finalmente encuentra el templo del Dragon JUMEX\n";
                    cout<<"el templo es una esctructura monolitica de forma piramida invertida, con rios por algunas salidas del templo\n";
                    cout<<"y desgastado por el tiempo. Al seguir caminando, "<<personaje<<" se encuentra con un viejo conocido, KKKKKN,\n";
                    cout<<"KKKKKN: Sabría que vendrias, pero no pensé que llegarías tan lejos, como sabras es mi deber proteger a este dragon\n";
                    cout<<"\tle debo la vida de mis seres queridos, cuando la nacion enemiga de mi pueblo atacó, JUMEX, en su grandeza,\n";
                    cout<<"dió la cara y con sus llamaradas elimino al ejercito enemigo. Ese día, toda mi generacion le juró lealtad junto\n";
                    cout<<"con algunas otras familias. Pero ahora solo quedo yo, y no dejaré que sigas avanzando...\n";
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<"\n\nQue deseas hacer??[1] Pelear\t[2] Pelear\t[3] Pelear\n";
                    cin>>op4;
                    while (corazones>0)
                    {
                        //Pelea, Pelea, Pelea
                        if (batallaPorTurnos(personaje,"KKKKKN",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                            cout<<"KKKKKN: Le he jurado lealtad al grand Dragon JUMEX, mi cuerpo calló, pero mi alma siempre estará en deuda\n";
                            cout<<"\tdespues de tanto, esta vida no fue lo que necesitaba, pero era lo que quería, gracias por testerrarme\n";
                            cout<<"\tde este tormento, por fin podré reunirme con mi pueblo, mi tribu...mi familia...\n";
                            cout<<"En medio de la agonía de KKKKKN, reune pocas de sus fuerzas, se arrebata su unico corazon del pecho\n";
                            cout<<"y te lo ofrese como trofeo...simplemente lo aceptas.\n";
                            corazones+=1;
                            cout<<"Corazones actuales: "<<corazones<<endl;
                        }else{
                            cout<<"KKKKKN: La sangre de otro mortal vuelve a manchar mi espada de sangre, que con aquejo y remordimiento\n";
                            cout<<"\nespero que la proxima vez pueda encontrar la paz\n";
                            corazones-=0;
                            if (corazones-=0){
                                return false;
                            }
                        }
                        //End KKKKKN
                        cout<<"-----------------------------------------------------------------------------------------------------------\n";
                        cout<<personaje<<" ha recorrido bastante el suelo que hoy tiene lugar a un templo sagrado y protegido por un linaje\n";
                        cout<<"de guardianes tratando de encontrar la paz en su deber, en un juramento, en un una idea.\n";
                        cout<<"Al adentrarse en el gran templo, las cosas parecen estar muy abandonadas, los pisos con cubiertos por gruesas\n";
                        cout<<"y pesadas capas de polvo formando un aura de abandono profundo, sin embargo tras caminar un tiempo\n";
                        cout<<"se logran ver algunas huellas que se repiten a si mismas, al parecer son las huellas de un Jaguar\n";
                        cout<<"parece ser que KKKKKN recorria constantemente los pasillos vacios y oscuros, así que "<<personaje<<"decide \n";
                        cout<<"seguir el rastro, mientras sigue las marcas en el piso, se pueden apreciar en los muros una cierta leyenda\n";
                        cout<<"al parecer los muros fueron pintados con un estilo muy ruprestre, no se logra ver muy bien, el paso del tiempo\n";
                        cout<<"ha hecho que se borre la pintura pero parcialmente se puede apreciar una especia de dragon blanco\n";
                        cout<<"de ojos azules saliendo del Sol en direccion para un grupo de personas, tambien hay una rota, falta un fragmento\n";
                        cout<<"solo se logra ver lo que parece una persona alzando algo....tal vez no sea importante...\n";
                        cout<<"A lo lejos se escucha un rugido temible, seguido de un golpe constante, un compas confuso de flauta se logra\n";
                        cout<<"distinguir, al ritmo se suma algunos tambores muy tribales, arpas y algunos instrumentos de cuerda.\n";
                        cout<<personaje<<" decide seguir la musica, sube unas escaleras en forma de caracol de una aparente torre y llega a \n ";
                        cout<<"una camara en donde resuena los tambores, ahí ve un dragon blanco dormido, una gran hoguera y los musicos\n";
                        cout<<"disfrutando la complicidad, la union y el rito. De repente, un grupo encapuchado empieza a escoger personas\n";
                        cout<<"aparentemente al azar, usan una especie de rampa imprivizada y lo dejan caer a la boca del dragon quien\n";
                        cout<<"instintivamente abrió el hocico, dejando algunas llamas en el aire. Las personas encapuchadas vuelven a escoger\n";
                        cout<<"personas, separando a una familia, se llevan a una madre y a su hija, el padre implora que las dejen en paz\n";
                        cout<<"entre gritos y sollozos, la hija se libera por un instante y luego dejan caer a la madre a la boca del dragon\n";
                        cout<<"mientras la madre cae, la hija corre a los brazos del padre, el padre enfurecido, en un movimiento rapido\n";
                        cout<<"carga a su hija y le arrebata un leño a la hoguera, su mirada lo dice todo, solo quire salir de ahí\n";
                        cout<<"Entre lagrimas, la hija pregunta por su madre, aún no comprende que acaba de pasar, simplemente no lo asimila\n";
                        cout<<"el padre al verse acorralado, decide subir por la rampa y saltar, el dragon abre la boca pero es tarde\n";
                        cout<<"el padre le ha clavado un leño en su ojo izquierdo. Con el ojo enrojesido el Gran Dragon Blanco se levanta\n";
                        cout<<"Y muestra su imponente forma, dando un rugido muy feroz, capaz de sacar volando a todo el culto, el padre\n";
                        cout<<"logra verte y en un breve momento de contacto visual, desaparece...El Dragon intenta volar, sin embargo tiene\n";
                        cout<<"una de sus alas rotas ya, desconocido es si aun su equilibro en orden está, al intentar levantarse no logra superar\n";
                        cout<<"los 10 segundos seguidos en una pocicion estable. Una corroida sustancia es expulsada de su boca. El legendario\n";
                        cout<<"dragon está muriendo. JUMEX, nota tu presencia, alcanza a verte con el rabillo de su ojo aun en paz\n";
                        cout<<personaje<<" decide acercase con determinacion...El momento se detiene, los flujos de agua cayendo se detienen\n";
                        cout<<"y el tiempo lo hace tambien, escuha una extraña voz agrietada y corrompida\n";
                        cout<<"\nJUMEX, el gran dragon de ojos azules: Estas aquí por esa baratija de piedra, cierto?? Bueno, tengo malas noticias\n";
                        cout<<"\tesa cosa nunca existió, solo fueron inventos de gente rechazada por la sociedad inventó, el sistema les falló\n";
                        cout<<"\tcomo puedes ver ahora los grupos de extraños me llaman una leyenda, pero que soy si no otro dragon\n";
                        cout<<"\tlas historias que se cuentan de mi, son solo grandes enagenaciones de mitos revueltos en la mente\n";
                        cout<<"\thumana, un parasito social que solo aferra a los más necesitados a un puño de promesas vacias\n ";
                        cout<<"\tPero, ya estoy cansado de todo esto, necesito descansar, necesito encontrar el equilibrio, pero qué clase de\n";
                        cout<<"\tequilibrio puede conseguir una lagartija gigante??. Te lo suplico, por favor acaba conmigo, solo quiero morir\n";
                        cout<<"\tdeseo salir de este mundo que me ha hecho tanto daño.Harias eso por mi??\n";
                        cout<<"-----------------------------------------------------------------------------------------------------------\n\n";
                        cout<<"Que deseas hacer??\n\n[1] Matar\t[2] Pelear\t[3] Perdonar\n\n";
                        cin>>op5;
                        if (op5==1){
                            cout<<personaje<<" toma su espada, desevaina la hoja, toma un respiro, hinhala, exhala, encuentra determinacion en\n";
                            cout<<"sus acciones y...\n";
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: espera, que estoy haciendo??Dejandome matar por una persona que\n";
                            cout<<"\tno tiene la menor idea de mis heroicos actos, de mi legado, de mi ser...no, un Dragon de mi linaje\n";
                            cout<<"\tno puede morir de esta forma tan patetica. Preparate para nuestra pelea, será de las cosas más dificiles que\n";
                            cout<<"hayas hecho nunca...muah...jjajajaja..coff.cofff...\n";
                        }else if (op5==2){
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: a veces, y solo a veces son necesarias las peleas pero esta vez será\n";
                            cout<<"\talgo muy sensillo,pero...por qué debería serlo, por qué me tengo tando desprecio a mi mismo??\n";
                            cout<<"\tOlvidalo por completo, PREPARATE A SER CARBONNIZADO JAJAJAJAJAJA\n";
                        }else{
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: no,no,no,no,no...no necesito tu perdon, no necesito el de nadie\n";
                            cout<<"\tTú jamas me entenderías simple mortal, acabaré con tu vida, así como la de la gente que me lo himploró\n";
                            cout<<"coff...coff....";
                        }
                        if (batallaPorTurnos(personaje, "JUMEX EL GRAN DRAGON BLANCO DE OJOS AZULES", 2, pociones, pocionesMax, escudos, ataqueMortal)){
                            cout<<"Esta ha sido mi ultima batalla, coff..coff, nunca fuiste realmente un rival para mi, yo no morireeee en las manos\n";
                            cout<<"de un simple mortaaaaaaaalll AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH...aaaaaaaaaaaaaaah...\n";
                            cout<<"Un liquido brumoso purpura empieza a sacar por todos los orificios del cuerpo, cae al aspero suelo y finalmente\n\n";
                            cout<<"JUMEX, EL GRAN DRAGON BLANCO DE OJOS AZULES muere\n";
                            cout<<"Corazones actuales: "<<corazones<<endl;
                            return true;

                        }else{
                            cout<<"Te lo dije, un gran ser como yo es imposible de matar...espero que la proxima vez sea distinto, aqui estaré\n";
                            cout<<personaje<<" tirado en el suelo y sufriendo de agonia, mira al dragon y da su ultimo suspiro....has muerto\n";
                            cout<<"El dragon se come tu cadaver y con ello, todos tus corazones\n";
                            corazones = 0;
                            cout<<"Corazones actuales"<<corazones<<endl;
                            return false;

                        }
                    }
                    //End dragon y Bosques Perdidos

                    break;
                case 2:
                    //Habla con serpiente Indú
                    cout<<"Serpiente Indú: Espera, no queriassss quitarme mi comida???, Debisste haberlo mencionado antesss, todo esto es un simple mal\n";
                    cout<<"\tentendidosss, de ser por mi, puedes pasar a dodne quieras, en este bosque las cosas son más simples de lo que parece\n";
                    cout<<"Serpiente Indú, te ha dejado pasar sin aparentemente ningun problema\n";
                    cout<<"Corazones actuales: "<<corazones<<endl;
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    //End serpiente indú
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<personaje<<" empieza a desmotivarse por todo el asunto de si realmente vale la pena seguir en busqueda de\n";
                    cout<<"esa tal piedra, pero sin embargo decide no rendirse y procurar seguir adelante con sus motivaciones, \n";
                    cout<<"ese prestamos a los burgueses no se va a pagar solo.\n";
                    cout<<"El bosque a pesar de ser un lugar bastante obtuso sigue siendo una de las grandes obras magnas de la naturaleza\n";
                    cout<<"en los antiguos libros de hechizos y magias paganas, se dice que los origenes del bosque son indecifrables.\n";
                    cout<<"Las primeras investigaciones que se hicieron sobre el bosque fue sobre muestras de cortesas de arbol,\n";
                    cout<<"pues los aros de los troncos revelaría con certeza su edad y a partir de ahí estimarian tiempos junto con\n";
                    cout<<"otras muestras del sedimento y del micelio blanco que crece alrededor del perimetro del boosque, pero que \n";
                    cout<<"sin embargo, al intentar partir los arboles, estos parecian indestructibles, ni con la fuerza de 20 hombres\n";
                    cout<<"era capaz de fragmentarse un solo pedazo de madera, al parecer los arboles secretaban naturalemente\n";
                    cout<<"una especie de baba pegajosa que puede ser usada como catalizador alquimico, incluso hay registros de que\n";
                    cout<<"al ser ingerido puede hacer que la persona persiva \"otra vida\", pues se asegura que puedes experimentar\n";
                    cout<<"otra vida muy distinta a la propia, con entornos y consecuecias diferentes salvo una sola constante\n";
                    cout<<"el NECRONOMICON.\n";
                    cout<<personaje<<" se sube a la copa de un arbol, intentando ver el final del bosque, pero este parece no terminar,\n";
                    cout<<"para no perderse, empieza a marcar los arboles por donde ya ha pasado, sin embargo, empieza a notar algo extraño\n";
                    cout<<"Los arboles que al principio solo tenian una marca vuelven a aparecer "<<personaje<<" empieza a sospechar sobre si\n";
                    cout<<"ha estado caminando en ciculos, hasta que...encuentra un patron en los arboles: forman tren hileras\n";
                    cout<<"el clima empieza a mostrar una cara gris, y algunas gotas se empiezan a persivir, buscando donde refugiarse\n";
                    cout<<"encuentra un techo de hojas, es como si alguien estuviera viviendo ahí, durante un tiempo...\n";
                    cout<<"DESCONOCIDO: Hey, que haces durmiendo ahí, uno ya no puede ir por algunos conejos sin que le roben su refugio\n";
                    cout<<"\tsé que el bosque parece interminable pero hay lugar para ambos, vale?, te dejaré quedarte pero nada de timos\n";
                    cout<<"\tsoy el ultimo protector que queda del dragon JUMEX, ese dragon se apoderó de todos los frutos del bosque \n";
                    cout<<"\tdesde hace un tiempo, desde entonces solo nos queda matarnos entre nosotros, los habitantes del Bosque Perdido\n";
                    cout<<"\tha decir verdad, los bucles entre arboles son bastante común entre mas te acercas al dragon, de vez en cuando\n";
                    cout<<"\tcuando el clima cambia el dragon pierde un poco de magia y tranquiliza la randomizacion del bosque. En fin, duerme.\n";
                    cout<<"\n\nAl día siguiente "<<personaje<<" le dió las gracias por su hospitalidad al ser Anaranjado Manchinegro.\n";
                    cout<<"Dandole adios a KKKKKN\n";
                    cout<<personaje<<" comieza a perder la determinacion, pero se acuerda del dinero por la PIEDRA FILOSOFAL y se le pasa\n";
                    cout<<"Despues de haber caminado durante 3 dias y 3 noches,"<<personaje<<" finalmente encuentra el templo del Dragon JUMEX\n";
                    cout<<"el templo es una esctructura monolitica de forma piramida invertida, con rios por algunas salidas del templo\n";
                    cout<<"y desgastado por el tiempo. Al seguir caminando, "<<personaje<<" se encuentra con un viejo conocido, KKKKKN,\n";
                    cout<<"KKKKKN: Sabría que vendrias, pero no pensé que llegarías tan lejos, como sabras es mi deber proteger a este dragon\n";
                    cout<<"\tle debo la vida de mis seres queridos, cuando la nacion enemiga de mi pueblo atacó, JUMEX, en su grandeza,\n";
                    cout<<"dió la cara y con sus llamaradas elimino al ejercito enemigo. Ese día, toda mi generacion le juró lealtad junto\n";
                    cout<<"con algunas otras familias. Pero ahora solo quedo yo, y no dejaré que sigas avanzando...\n";
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<"\n\nQue deseas hacer??[1] Pelear\t[2] Pelear\t[3] Pelear\n";
                    cin>>op4;
                    while (corazones>0)
                    {
                        //Pelea, Pelea, Pelea
                        if (batallaPorTurnos(personaje,"KKKKKN",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                            cout<<"KKKKKN: Le he jurado lealtad al grand Dragon JUMEX, mi cuerpo calló, pero mi alma siempre estará en deuda\n";
                            cout<<"\tdespues de tanto, esta vida no fue lo que necesitaba, pero era lo que quería, gracias por testerrarme\n";
                            cout<<"\tde este tormento, por fin podré reunirme con mi pueblo, mi tribu...mi familia...\n";
                            cout<<"En medio de la agonía de KKKKKN, reune pocas de sus fuerzas, se arrebata su unico corazon del pecho\n";
                            cout<<"y te lo ofrese como trofeo...simplemente lo aceptas.\n";
                            corazones+=1;
                            cout<<"Corazones actuales: "<<corazones<<endl;
                        }else{
                            cout<<"KKKKKN: La sangre de otro mortal vuelve a manchar mi espada de sangre, que con aquejo y remordimiento\n";
                            cout<<"\nespero que la proxima vez pueda encontrar la paz\n";
                            corazones-=0;
                            if (corazones-=0){
                                return false;
                            }
                        }
                        //End KKKKKN
                        cout<<"-----------------------------------------------------------------------------------------------------------\n";
                        cout<<personaje<<" ha recorrido bastante el suelo que hoy tiene lugar a un templo sagrado y protegido por un linaje\n";
                        cout<<"de guardianes tratando de encontrar la paz en su deber, en un juramento, en un una idea.\n";
                        cout<<"Al adentrarse en el gran templo, las cosas parecen estar muy abandonadas, los pisos con cubiertos por gruesas\n";
                        cout<<"y pesadas capas de polvo formando un aura de abandono profundo, sin embargo tras caminar un tiempo\n";
                        cout<<"se logran ver algunas huellas que se repiten a si mismas, al parecer son las huellas de un Jaguar\n";
                        cout<<"parece ser que KKKKKN recorria constantemente los pasillos vacios y oscuros, así que "<<personaje<<"decide \n";
                        cout<<"seguir el rastro, mientras sigue las marcas en el piso, se pueden apreciar en los muros una cierta leyenda\n";
                        cout<<"al parecer los muros fueron pintados con un estilo muy ruprestre, no se logra ver muy bien, el paso del tiempo\n";
                        cout<<"ha hecho que se borre la pintura pero parcialmente se puede apreciar una especia de dragon blanco\n";
                        cout<<"de ojos azules saliendo del Sol en direccion para un grupo de personas, tambien hay una rota, falta un fragmento\n";
                        cout<<"solo se logra ver lo que parece una persona alzando algo....tal vez no sea importante...\n";
                        cout<<"A lo lejos se escucha un rugido temible, seguido de un golpe constante, un compas confuso de flauta se logra\n";
                        cout<<"distinguir, al ritmo se suma algunos tambores muy tribales, arpas y algunos instrumentos de cuerda.\n";
                        cout<<personaje<<" decide seguir la musica, sube unas escaleras en forma de caracol de una aparente torre y llega a \n ";
                        cout<<"una camara en donde resuena los tambores, ahí ve un dragon blanco dormido, una gran hoguera y los musicos\n";
                        cout<<"disfrutando la complicidad, la union y el rito. De repente, un grupo encapuchado empieza a escoger personas\n";
                        cout<<"aparentemente al azar, usan una especie de rampa imprivizada y lo dejan caer a la boca del dragon quien\n";
                        cout<<"instintivamente abrió el hocico, dejando algunas llamas en el aire. Las personas encapuchadas vuelven a escoger\n";
                        cout<<"personas, separando a una familia, se llevan a una madre y a su hija, el padre implora que las dejen en paz\n";
                        cout<<"entre gritos y sollozos, la hija se libera por un instante y luego dejan caer a la madre a la boca del dragon\n";
                        cout<<"mientras la madre cae, la hija corre a los brazos del padre, el padre enfurecido, en un movimiento rapido\n";
                        cout<<"carga a su hija y le arrebata un leño a la hoguera, su mirada lo dice todo, solo quire salir de ahí\n";
                        cout<<"Entre lagrimas, la hija pregunta por su madre, aún no comprende que acaba de pasar, simplemente no lo asimila\n";
                        cout<<"el padre al verse acorralado, decide subir por la rampa y saltar, el dragon abre la boca pero es tarde\n";
                        cout<<"el padre le ha clavado un leño en su ojo izquierdo. Con el ojo enrojesido el Gran Dragon Blanco se levanta\n";
                        cout<<"Y muestra su imponente forma, dando un rugido muy feroz, capaz de sacar volando a todo el culto, el padre\n";
                        cout<<"logra verte y en un breve momento de contacto visual, desaparece...El Dragon intenta volar, sin embargo tiene\n";
                        cout<<"una de sus alas rotas ya, desconocido es si aun su equilibro en orden está, al intentar levantarse no logra superar\n";
                        cout<<"los 10 segundos seguidos en una pocicion estable. Una corroida sustancia es expulsada de su boca. El legendario\n";
                        cout<<"dragon está muriendo. JUMEX, nota tu presencia, alcanza a verte con el rabillo de su ojo aun en paz\n";
                        cout<<personaje<<" decide acercase con determinacion...El momento se detiene, los flujos de agua cayendo se detienen\n";
                        cout<<"y el tiempo lo hace tambien, escuha una extraña voz agrietada y corrompida\n";
                        cout<<"\nJUMEX, el gran dragon de ojos azules: Estas aquí por esa baratija de piedra, cierto?? Bueno, tengo malas noticias\n";
                        cout<<"\tesa cosa nunca existió, solo fueron inventos de gente rechazada por la sociedad inventó, el sistema les falló\n";
                        cout<<"\tcomo puedes ver ahora los grupos de extraños me llaman una leyenda, pero que soy si no otro dragon\n";
                        cout<<"\tlas historias que se cuentan de mi, son solo grandes enagenaciones de mitos revueltos en la mente\n";
                        cout<<"\thumana, un parasito social que solo aferra a los más necesitados a un puño de promesas vacias\n ";
                        cout<<"\tPero, ya estoy cansado de todo esto, necesito descansar, necesito encontrar el equilibrio, pero qué clase de\n";
                        cout<<"\tequilibrio puede conseguir una lagartija gigante??. Te lo suplico, por favor acaba conmigo, solo quiero morir\n";
                        cout<<"\tdeseo salir de este mundo que me ha hecho tanto daño.Harias eso por mi??\n";
                        cout<<"-----------------------------------------------------------------------------------------------------------\n\n";
                        cout<<"Que deseas hacer??\n\n[1] Matar\t[2] Pelear\t[3] Perdonar\n\n";
                        cin>>op5;
                        if (op5==1){
                            cout<<personaje<<" toma su espada, desevaina la hoja, toma un respiro, hinhala, exhala, encuentra determinacion en\n";
                            cout<<"sus acciones y...\n";
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: espera, que estoy haciendo??Dejandome matar por una persona que\n";
                            cout<<"\tno tiene la menor idea de mis heroicos actos, de mi legado, de mi ser...no, un Dragon de mi linaje\n";
                            cout<<"\tno puede morir de esta forma tan patetica. Preparate para nuestra pelea, será de las cosas más dificiles que\n";
                            cout<<"hayas hecho nunca...muah...jjajajaja..coff.cofff...\n";
                        }else if (op5==2){
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: a veces, y solo a veces son necesarias las peleas pero esta vez será\n";
                            cout<<"\talgo muy sensillo,pero...por qué debería serlo, por qué me tengo tando desprecio a mi mismo??\n";
                            cout<<"\tOlvidalo por completo, PREPARATE A SER CARBONNIZADO JAJAJAJAJAJA\n";
                        }else{
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: no,no,no,no,no...no necesito tu perdon, no necesito el de nadie\n";
                            cout<<"\tTú jamas me entenderías simple mortal, acabaré con tu vida, así como la de la gente que me lo himploró\n";
                            cout<<"coff...coff....";
                        }
                        if (batallaPorTurnos(personaje, "JUMEX EL GRAN DRAGON BLANCO DE OJOS AZULES", 2, pociones, pocionesMax, escudos, ataqueMortal)){
                            cout<<"Esta ha sido mi ultima batalla, coff..coff, nunca fuiste realmente un rival para mi, yo no morireeee en las manos\n";
                            cout<<"de un simple mortaaaaaaaalll AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH...aaaaaaaaaaaaaaah...\n";
                            cout<<"Un liquido brumoso purpura empieza a sacar por todos los orificios del cuerpo, cae al aspero suelo y finalmente\n\n";
                            cout<<"JUMEX, EL GRAN DRAGON BLANCO DE OJOS AZULES muere\n";
                            cout<<"Corazones actuales: "<<corazones<<endl;
                            return true;

                        }else{
                            cout<<"Te lo dije, un gran ser como yo es imposible de matar...espero que la proxima vez sea distinto, aqui estaré\n";
                            cout<<personaje<<" tirado en el suelo y sufriendo de agonia, mira al dragon y da su ultimo suspiro....has muerto\n";
                            cout<<"El dragon se come tu cadaver y con ello, todos tus corazones\n";
                            corazones = 0;
                            cout<<"Corazones actuales"<<corazones<<endl;
                            return false;

                        }
                    }
                    //End dragon y Bosques Perdidos
                    break;
                case 3:
                    //Pagar a serpiente indú
                    cout<<"Serpiente Indú: Espera, qué se supone que haga yo con essssso, solo soy una serpiente de origen desconocido, lo siento pero\n";
                    cout<<"\nno puedo dejarte hacer eso, total, ya cazé mi presa del día ...ssssss.sssss.ssss\n";
                    cout<<"Corazones actuales: "<<corazones<<endl;
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    //End serpiente indú
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<personaje<<" empieza a desmotivarse por todo el asunto de si realmente vale la pena seguir en busqueda de\n";
                    cout<<"esa tal piedra, pero sin embargo decide no rendirse y procurar seguir adelante con sus motivaciones, \n";
                    cout<<"ese prestamos a los burgueses no se va a pagar solo.\n";
                    cout<<"El bosque a pesar de ser un lugar bastante obtuso sigue siendo una de las grandes obras magnas de la naturaleza\n";
                    cout<<"en los antiguos libros de hechizos y magias paganas, se dice que los origenes del bosque son indecifrables.\n";
                    cout<<"Las primeras investigaciones que se hicieron sobre el bosque fue sobre muestras de cortesas de arbol,\n";
                    cout<<"pues los aros de los troncos revelaría con certeza su edad y a partir de ahí estimarian tiempos junto con\n";
                    cout<<"otras muestras del sedimento y del micelio blanco que crece alrededor del perimetro del boosque, pero que \n";
                    cout<<"sin embargo, al intentar partir los arboles, estos parecian indestructibles, ni con la fuerza de 20 hombres\n";
                    cout<<"era capaz de fragmentarse un solo pedazo de madera, al parecer los arboles secretaban naturalemente\n";
                    cout<<"una especie de baba pegajosa que puede ser usada como catalizador alquimico, incluso hay registros de que\n";
                    cout<<"al ser ingerido puede hacer que la persona persiva \"otra vida\", pues se asegura que puedes experimentar\n";
                    cout<<"otra vida muy distinta a la propia, con entornos y consecuecias diferentes salvo una sola constante\n";
                    cout<<"el NECRONOMICON.\n";
                    cout<<personaje<<" se sube a la copa de un arbol, intentando ver el final del bosque, pero este parece no terminar,\n";
                    cout<<"para no perderse, empieza a marcar los arboles por donde ya ha pasado, sin embargo, empieza a notar algo extraño\n";
                    cout<<"Los arboles que al principio solo tenian una marca vuelven a aparecer "<<personaje<<" empieza a sospechar sobre si\n";
                    cout<<"ha estado caminando en ciculos, hasta que...encuentra un patron en los arboles: forman tren hileras\n";
                    cout<<"el clima empieza a mostrar una cara gris, y algunas gotas se empiezan a persivir, buscando donde refugiarse\n";
                    cout<<"encuentra un techo de hojas, es como si alguien estuviera viviendo ahí, durante un tiempo...\n";
                    cout<<"DESCONOCIDO: Hey, que haces durmiendo ahí, uno ya no puede ir por algunos conejos sin que le roben su refugio\n";
                    cout<<"\tsé que el bosque parece interminable pero hay lugar para ambos, vale?, te dejaré quedarte pero nada de timos\n";
                    cout<<"\tsoy el ultimo protector que queda del dragon JUMEX, ese dragon se apoderó de todos los frutos del bosque \n";
                    cout<<"\tdesde hace un tiempo, desde entonces solo nos queda matarnos entre nosotros, los habitantes del Bosque Perdido\n";
                    cout<<"\tha decir verdad, los bucles entre arboles son bastante común entre mas te acercas al dragon, de vez en cuando\n";
                    cout<<"\tcuando el clima cambia el dragon pierde un poco de magia y tranquiliza la randomizacion del bosque. En fin, duerme.\n";
                    cout<<"\n\nAl día siguiente "<<personaje<<" le dió las gracias por su hospitalidad al ser Anaranjado Manchinegro.\n";
                    cout<<"Dandole adios a KKKKKN\n";
                    cout<<personaje<<" comieza a perder la determinacion, pero se acuerda del dinero por la PIEDRA FILOSOFAL y se le pasa\n";
                    cout<<"Despues de haber caminado durante 3 dias y 3 noches,"<<personaje<<" finalmente encuentra el templo del Dragon JUMEX\n";
                    cout<<"el templo es una esctructura monolitica de forma piramida invertida, con rios por algunas salidas del templo\n";
                    cout<<"y desgastado por el tiempo. Al seguir caminando, "<<personaje<<" se encuentra con un viejo conocido, KKKKKN,\n";
                    cout<<"KKKKKN: Sabría que vendrias, pero no pensé que llegarías tan lejos, como sabras es mi deber proteger a este dragon\n";
                    cout<<"\tle debo la vida de mis seres queridos, cuando la nacion enemiga de mi pueblo atacó, JUMEX, en su grandeza,\n";
                    cout<<"dió la cara y con sus llamaradas elimino al ejercito enemigo. Ese día, toda mi generacion le juró lealtad junto\n";
                    cout<<"con algunas otras familias. Pero ahora solo quedo yo, y no dejaré que sigas avanzando...\n";
                    cout<<"-----------------------------------------------------------------------------------------------------------\n";
                    cout<<"\n\nQue deseas hacer??[1] Pelear\t[2] Pelear\t[3] Pelear\n";
                    cin>>op4;
                    while (corazones>0)
                    {
                        //Pelea, Pelea, Pelea
                        if (batallaPorTurnos(personaje,"KKKKKN",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                            cout<<"KKKKKN: Le he jurado lealtad al grand Dragon JUMEX, mi cuerpo calló, pero mi alma siempre estará en deuda\n";
                            cout<<"\tdespues de tanto, esta vida no fue lo que necesitaba, pero era lo que quería, gracias por testerrarme\n";
                            cout<<"\tde este tormento, por fin podré reunirme con mi pueblo, mi tribu...mi familia...\n";
                            cout<<"En medio de la agonía de KKKKKN, reune pocas de sus fuerzas, se arrebata su unico corazon del pecho\n";
                            cout<<"y te lo ofrese como trofeo...simplemente lo aceptas.\n";
                            corazones+=1;
                            cout<<"Corazones actuales: "<<corazones<<endl;
                        }else{
                            cout<<"KKKKKN: La sangre de otro mortal vuelve a manchar mi espada de sangre, que con aquejo y remordimiento\n";
                            cout<<"\nespero que la proxima vez pueda encontrar la paz\n";
                            corazones-=0;
                            if (corazones-=0){
                                return false;
                            }
                        }
                        //End KKKKKN
                        cout<<"-----------------------------------------------------------------------------------------------------------\n";
                        cout<<personaje<<" ha recorrido bastante el suelo que hoy tiene lugar a un templo sagrado y protegido por un linaje\n";
                        cout<<"de guardianes tratando de encontrar la paz en su deber, en un juramento, en un una idea.\n";
                        cout<<"Al adentrarse en el gran templo, las cosas parecen estar muy abandonadas, los pisos con cubiertos por gruesas\n";
                        cout<<"y pesadas capas de polvo formando un aura de abandono profundo, sin embargo tras caminar un tiempo\n";
                        cout<<"se logran ver algunas huellas que se repiten a si mismas, al parecer son las huellas de un Jaguar\n";
                        cout<<"parece ser que KKKKKN recorria constantemente los pasillos vacios y oscuros, así que "<<personaje<<"decide \n";
                        cout<<"seguir el rastro, mientras sigue las marcas en el piso, se pueden apreciar en los muros una cierta leyenda\n";
                        cout<<"al parecer los muros fueron pintados con un estilo muy ruprestre, no se logra ver muy bien, el paso del tiempo\n";
                        cout<<"ha hecho que se borre la pintura pero parcialmente se puede apreciar una especia de dragon blanco\n";
                        cout<<"de ojos azules saliendo del Sol en direccion para un grupo de personas, tambien hay una rota, falta un fragmento\n";
                        cout<<"solo se logra ver lo que parece una persona alzando algo....tal vez no sea importante...\n";
                        cout<<"A lo lejos se escucha un rugido temible, seguido de un golpe constante, un compas confuso de flauta se logra\n";
                        cout<<"distinguir, al ritmo se suma algunos tambores muy tribales, arpas y algunos instrumentos de cuerda.\n";
                        cout<<personaje<<" decide seguir la musica, sube unas escaleras en forma de caracol de una aparente torre y llega a \n ";
                        cout<<"una camara en donde resuena los tambores, ahí ve un dragon blanco dormido, una gran hoguera y los musicos\n";
                        cout<<"disfrutando la complicidad, la union y el rito. De repente, un grupo encapuchado empieza a escoger personas\n";
                        cout<<"aparentemente al azar, usan una especie de rampa imprivizada y lo dejan caer a la boca del dragon quien\n";
                        cout<<"instintivamente abrió el hocico, dejando algunas llamas en el aire. Las personas encapuchadas vuelven a escoger\n";
                        cout<<"personas, separando a una familia, se llevan a una madre y a su hija, el padre implora que las dejen en paz\n";
                        cout<<"entre gritos y sollozos, la hija se libera por un instante y luego dejan caer a la madre a la boca del dragon\n";
                        cout<<"mientras la madre cae, la hija corre a los brazos del padre, el padre enfurecido, en un movimiento rapido\n";
                        cout<<"carga a su hija y le arrebata un leño a la hoguera, su mirada lo dice todo, solo quire salir de ahí\n";
                        cout<<"Entre lagrimas, la hija pregunta por su madre, aún no comprende que acaba de pasar, simplemente no lo asimila\n";
                        cout<<"el padre al verse acorralado, decide subir por la rampa y saltar, el dragon abre la boca pero es tarde\n";
                        cout<<"el padre le ha clavado un leño en su ojo izquierdo. Con el ojo enrojesido el Gran Dragon Blanco se levanta\n";
                        cout<<"Y muestra su imponente forma, dando un rugido muy feroz, capaz de sacar volando a todo el culto, el padre\n";
                        cout<<"logra verte y en un breve momento de contacto visual, desaparece...El Dragon intenta volar, sin embargo tiene\n";
                        cout<<"una de sus alas rotas ya, desconocido es si aun su equilibro en orden está, al intentar levantarse no logra superar\n";
                        cout<<"los 10 segundos seguidos en una pocicion estable. Una corroida sustancia es expulsada de su boca. El legendario\n";
                        cout<<"dragon está muriendo. JUMEX, nota tu presencia, alcanza a verte con el rabillo de su ojo aun en paz\n";
                        cout<<personaje<<" decide acercase con determinacion...El momento se detiene, los flujos de agua cayendo se detienen\n";
                        cout<<"y el tiempo lo hace tambien, escuha una extraña voz agrietada y corrompida\n";
                        cout<<"\nJUMEX, el gran dragon de ojos azules: Estas aquí por esa baratija de piedra, cierto?? Bueno, tengo malas noticias\n";
                        cout<<"\tesa cosa nunca existió, solo fueron inventos de gente rechazada por la sociedad inventó, el sistema les falló\n";
                        cout<<"\tcomo puedes ver ahora los grupos de extraños me llaman una leyenda, pero que soy si no otro dragon\n";
                        cout<<"\tlas historias que se cuentan de mi, son solo grandes enagenaciones de mitos revueltos en la mente\n";
                        cout<<"\thumana, un parasito social que solo aferra a los más necesitados a un puño de promesas vacias\n ";
                        cout<<"\tPero, ya estoy cansado de todo esto, necesito descansar, necesito encontrar el equilibrio, pero qué clase de\n";
                        cout<<"\tequilibrio puede conseguir una lagartija gigante??. Te lo suplico, por favor acaba conmigo, solo quiero morir\n";
                        cout<<"\tdeseo salir de este mundo que me ha hecho tanto daño.Harias eso por mi??\n";
                        cout<<"-----------------------------------------------------------------------------------------------------------\n\n";
                        cout<<"Que deseas hacer??\n\n[1] Matar\t[2] Pelear\t[3] Perdonar\n\n";
                        cin>>op5;
                        if (op5==1){
                            cout<<personaje<<" toma su espada, desevaina la hoja, toma un respiro, hinhala, exhala, encuentra determinacion en\n";
                            cout<<"sus acciones y...\n";
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: espera, que estoy haciendo??Dejandome matar por una persona que\n";
                            cout<<"\tno tiene la menor idea de mis heroicos actos, de mi legado, de mi ser...no, un Dragon de mi linaje\n";
                            cout<<"\tno puede morir de esta forma tan patetica. Preparate para nuestra pelea, será de las cosas más dificiles que\n";
                            cout<<"hayas hecho nunca...muah...jjajajaja..coff.cofff...\n";
                        }else if (op5==2){
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: a veces, y solo a veces son necesarias las peleas pero esta vez será\n";
                            cout<<"\talgo muy sensillo,pero...por qué debería serlo, por qué me tengo tando desprecio a mi mismo??\n";
                            cout<<"\tOlvidalo por completo, PREPARATE A SER CARBONNIZADO JAJAJAJAJAJA\n";
                        }else{
                            cout<<"JUMEX, Dragon Blanco de Ojos Azules: no,no,no,no,no...no necesito tu perdon, no necesito el de nadie\n";
                            cout<<"\tTú jamas me entenderías simple mortal, acabaré con tu vida, así como la de la gente que me lo himploró\n";
                            cout<<"coff...coff....\n";
                        }
                        if (batallaPorTurnos(personaje, "JUMEX EL GRAN DRAGON BLANCO DE OJOS AZULES", 2, pociones, pocionesMax, escudos, ataqueMortal)){
                            cout<<"Esta ha sido mi ultima batalla, coff..coff, nunca fuiste realmente un rival para mi, yo no morireeee en las manos\n";
                            cout<<"de un simple mortaaaaaaaalll AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH...aaaaaaaaaaaaaaah...\n";
                            cout<<"Un liquido brumoso purpura empieza a sacar por todos los orificios del cuerpo, cae al aspero suelo y finalmente\n\n";
                            cout<<"JUMEX, EL GRAN DRAGON BLANCO DE OJOS AZULES muere\n";
                            cout<<"Corazones actuales: "<<corazones<<endl;
                            return true;

                        }else{
                            cout<<"Te lo dije, un gran ser como yo es imposible de matar...espero que la proxima vez sea distinto, aqui estaré\n";
                            cout<<personaje<<" tirado en el suelo y sufriendo de agonia, mira al dragon y da su ultimo suspiro....has muerto\n";
                            cout<<"El dragon se come tu cadaver y con ello, todos tus corazones\n";
                            corazones = 0;
                            cout<<"Corazones actuales"<<corazones<<endl;
                            return false;

                        }
                    }
                    //End dragon y Bosques Perdidos
                    break;
                
                default:
                    cout<<"Opcion no disponible\n";
                    break;
                }
                
            }
            break;
        default:
            cout<<"Opcion no disponible\n";
            break;
        }
    }
    if (corazones<=0){
        cout<<"Regresando al menú\n";
        return false;
    }
    

}

bool ReinosZora(string personaje, int dificultad, int pociones, int pocionesMax, int escudos, int ataqueMortal){
    cout<<"R E I N O S  Z O R A\n\n";
}

bool RuinasDelAbismo(string personaje, int dificultad, int pociones, int pocionesMax, int escudos, int ataqueMortal){
    cout<<"R U I N A S  D E L  A B I S M O \n\n";
}

void finalHistoria(){
    cout<<"F I N A L ";
}


int main(){   
    // vector<string> palabras={"platano","tact","else"};
    // string palabra =choose_palabra(palabras);
    //Nombre del jugador
    string jugador = nomPlayer();
    //string nEnemy = "Empanada";
    //Variables
    int corazones = 3;
    int dificultad = 1; //Dificultad facil
    int monedas=1000;
    //Items
    int pociones = 0;
    int pocionesMax = 0;
    int escudos = 0;
    int ataqueMortal = 0;
    //Opcion del jugador
    int op;
    int opT;
    int opJ;
    //otras opciones
    int cho1;
    int cho2;
    //Progreso
    int progreso = 0;
    //menú principal
    while (true){
        op = menuPrincipal();

        switch (op){
        case 1:
            //---------Pre game----------------------------------------------------
            cout<<"Antes de  empezar...\n\n";
            cout<<"____________________________________________________________\n";
            cout<<"\t\tAlgunas estadisticas de "<<jugador<<"\n";
            cout<<"____________________________________________________________\n";
            cout<<"Corazones: \t"<<corazones<<endl;
            cout<<"Dificultad: \t";
            if (dificultad == 1){
                cout<<"Facil\n";
            }else{cout<<"Dificil\n";}
            cout<<"Monedas: \t"<<monedas<<"\n\n";
            cout<<"____________________________________________________________\n";
            cout<<"\tAlgunos objetos disponibles de: "<<jugador<<"\n";
            cout<<"____________________________________________________________\n";
            cout<<"Pociones = "<<pociones<<endl;
            cout<<"Pociones grandes = "<<pocionesMax<<endl;
            cout<<"Escudos = "<<escudos<<endl;
            cout<<"Hechizo 'golpe definitivo' = "<<ataqueMortal<<endl;
            cout<<"____________________________________________________________\n";
            cout<<"\n\n";
            cout<<"Recuerda que puedes comprar mas items en la tienda\n";
            cout<<"Estas seguro de empezar tu aventura?\n\t[1] SI \t[2] NO\n";
            cin >> opJ;
            //---------Pre game----------------------------------------------------
            if (opJ == 1){
                introduccion(jugador);
                while (true)
                {
                    cout<<"A que lugar te gustaria ir??\n\n[1] Bosques perdidos\n[2] Reino Zora\n[3] Ruinas del abismo\n";
                    cin>>cho1;
                    if (cho1 == 1){
                        if(BosquesPerdidos(jugador, dificultad, pociones, pocionesMax, escudos, ataqueMortal)){
                            cout<<"Bosques perdidos superados\n";
                            if (dificultad==1){
                                cout<<"Has recibido 300 monedas\n";
                                monedas+=300;
                            }else{
                                cout<<"Has recibido 500 monedas";
                                monedas+=500;
                            }
                            progreso++;
                            break;
                        }else{
                            cout<<"Bosques perdidos no superados\n";
                            cout<<"Volver a intentar??\n[1]Si\t[2] NO\n";
                            cin>>cho2;
                            if (cho2 == 1){
                                continue;
                            }else{
                                break;
                            }
                        }
                    }else if (cho1 == 2){
                        if (ReinosZora(jugador, dificultad, pociones, pocionesMax, escudos, ataqueMortal)){
                            cout<<"Reinos Zora superados\n";
                            if (dificultad==1){
                                cout<<"Has recibido 300 monedas\n";
                                monedas+=300;
                            }else{
                                cout<<"Has recibido 500 monedas";
                                monedas+=500;
                            }
                            progreso++;
                            break;
                        }else{
                            cout<<"Reinos Zora no superados\n";
                            cout<<"Volver a intentar??\n[1] Si \t[2] No\n";
                            cin>>cho2;
                            if (cho2 == 1){
                                continue;
                            }else{
                                break;
                            }
                            
                        }
                    }else if (cho1 == 3){
                        if (RuinasDelAbismo(jugador, dificultad, pociones, pocionesMax, escudos, ataqueMortal)){
                            cout<<"Ruinas del Abismo superadas\n";
                            if (dificultad == 1){
                                cout<<"Has recibido 300 monedas\n";
                                monedas+=300;
                            }else{
                                cout<<"Has recibido 500 monedas\n";
                                monedas+=500;
                            }
                            progreso++;
                            break;
                        }else{
                            cout<<"Ruinas del Abismo no superadas\n";
                            cout<<"Volver a intentar??\n[1] Si\t[2] No\n";
                            cin>>cho2;
                            if (cho2 == 1){
                                continue;
                            }else{
                                break;
                            }
                            
                        }
                        

                        
                    }else{
                        cout<<"Opcion no valida\n";
                    }
                
                }
                if (progreso == 3){
                    finalHistoria();
                    cout<<"Felicidades por completar el juego, has recibido 1000 para cada item del juego ";
                    pociones+=1000;
                    pocionesMax+=1000;
                    escudos+=1000;
                    ataqueMortal+=1000;
                    monedas+=1000;
                }
                
                
            }else{
                cout<<"Regresa cuando estes listo :D\n";
                break;
            }
            

            break;
        case 2:
            //Tienda
                cout<<"____________________________________________________________\n";
                cout<<"\tBienvenido a la tienda oficial del juego\n\n";
                cout<<"Los objetos que compres se podran usar durante las batallas,\nuna vez terminada la pelea,volveran a estar disponibles \npara la siguiente batalla\n\n";
                cout<<"____________________________________________________________\n";
                while (true){ //tienda
                    //Display
                    cout<<"\t\t\t >> Tienda <<\n";
                    cout<<"____________________________________________________________\n";
                    cout<<"Monedas disponibles: "<<monedas<<endl;
                    cout<<"------------------------------------------------------------\n";
                    cout<<"Articulos disponibles: \n\n";
                    cout<<"[1] Pocion de vida\t\t--- 5 monedas\n";
                    cout<<"\tTienes: "<<pociones<<endl;
                    cout<<"[2] Pocion de vida grande\t--- 10 monedas\n";
                    cout<<"\tTienes: "<<pocionesMax<<endl;
                    cout<<"[3] Escudos\t\t\t--- 15 monedas\n";
                    cout<<"\tTienes: "<<escudos<<endl;
                    cout<<"[4] Hechizo golpe definitivo\t--- 30 monedas\n";
                    cout<<"\tTienes "<<ataqueMortal<<endl;
                    cout<<"[5] Regresar al menu\n\n";
                    cout<<"Que te gustaria adquirir??\n\n{>>>} ";
                    cin>>op;
                    //End Display
                    if (op == 1){
                        //Pociones, costo = 5 monedas
                        if (monedas>0){
                            cout<<"Muy bien, cuantas pociones quieres comprar??\n";
                            while (true){ //valida el input
                                cout<<"[1] Una (1)\t[2] Dos (2)\t[3] Cinco (5) \n\n[4] Diez (10)\t[5] Cancelar\n\n{>>>} ";
                                cin>>opT;
                                if (opT  == 1){
                                    opT = 1;
                                    break;
                                }else if (opT == 2){
                                    opT = 2;
                                    break;
                                }else if (opT == 3){
                                    opT = 5;
                                    break;
                                }else if (opT == 4){
                                    opT = 10;
                                    break;
                                }else if (opT == 5){
                                    opT=-1;
                                    cout<<"Se ha cancelado la compra...\n";
                                    break;
                                }   
                            }//termina de validar el imput
                            if (opT==-1){//se cancela la compra
                                cout<<"Continuar comprando??\t[1] Si   [2]NO\n";
                                cin>>opT;
                                if (opT==1){
                                    continue;//regresa al inicio de la tienda
                                }else{
                                    break;//regresa al menú principal                              
                                }
                            }
                            
                            //costo = opT * 5
                            if ((monedas-(opT*5)) < 0 ){
                                cout<<"NO tienes suficientes monedas, consigue mas venciendo a los enemigos en la historia principal\n";
                            }else{
                                monedas-= (opT*5);
                                cout<<"Has comprado "<<opT<<" pociones\n";
                                pociones+=opT;
                                cout<<"Continuar comprando??\t[1] Si   [2]NO\n";
                                cin>>opT;
                                if (opT==1){
                                    continue;
                                }else{
                                    break;
                                }
                            }
                        }else{
                            cout<<"No tienes monedas, puedes conseguir mas derrotando a enemigos de la historia\n";
                            break;//sale de la tienda
                        }
                    }else if (op == 2){
                        //Pocion de vida grande, costo = 10 monedas
                        if (monedas>0){
                            cout<<"Muy bien, cuantas pociones grandes quieres comprar??\n";
                            while (true){ //valida el input
                                cout<<"[1] Una (1)\t[2] Dos (2)\t[3] Cinco (5) \n\n[4] Diez (10)\t[5] Cancelar\n\n{>>>} ";
                                cin>>opT;
                                if (opT  == 1){
                                    opT = 1;
                                    break;
                                }else if (opT == 2){
                                    opT = 2;
                                    break;
                                }else if (opT == 3){
                                    opT = 5;
                                    break;
                                }else if (opT == 4){
                                    opT = 10;
                                    break;
                                }else if (opT == 5){
                                    opT=-1;
                                    cout<<"Se ha cancelado la compra...\n";
                                    break;
                                }   
                            }//termina de validar el imput
                            if (opT==-1){//se cancela la compra
                                cout<<"Continuar comprando??\t[1] Si   [2]NO\n";
                                cin>>opT;
                                if (opT==1){
                                    continue;//regresa al inicio de la tienda
                                }else{
                                    break;//regresa al menú principal                              
                                }
                            }
                            
                            //costo = opT * 10
                            if ((monedas-(opT*10)) < 0 ){
                                cout<<"NO tienes suficientes monedas, consigue mas venciendo a los enemigos en la historia principal\n";
                            }else{
                                monedas-= (opT*10);
                                cout<<"Has comprado "<<opT<<" pociones grandes\n";
                                pocionesMax+=opT;
                                cout<<"Continuar comprando??\t[1] Si   [2]NO\n";
                                cin>>opT;
                                if (opT==1){
                                    continue;
                                }else{
                                    break;
                                }
                            }
                        }else{
                            cout<<"No tienes monedas, puedes conseguir mas derrotando a enemigos de la historia\n";
                            break;//sale de la tienda
                        }


                    }else if (op == 3){
                        //Escudos, costo = 15
                        if (monedas>0){
                            cout<<"Muy bien, cuantos escudos quieres comprar??\n";
                            while (true){ //valida el input
                                cout<<"[1] Una (1)\t[2] Dos (2)\t[3] Cinco (5) \n\n[4] Diez (10)\t[5] Cancelar\n\n{>>>} ";
                                cin>>opT;
                                if (opT  == 1){
                                    opT = 1;
                                    break;
                                }else if (opT == 2){
                                    opT = 2;
                                    break;
                                }else if (opT == 3){
                                    opT = 5;
                                    break;
                                }else if (opT == 4){
                                    opT = 10;
                                    break;
                                }else if (opT == 5){
                                    opT=-1;
                                    cout<<"Se ha cancelado la compra...\n";
                                    break;
                                }   
                            }//termina de validar el imput
                            if (opT==-1){//se cancela la compra
                                cout<<"Continuar comprando??\t[1] Si   [2]NO\n";
                                cin>>opT;
                                if (opT==1){
                                    continue;//regresa al inicio de la tienda
                                }else{
                                    break;//regresa al menú principal                              
                                }
                            }
                            
                            //costo = opT * 15
                            if ((monedas-(opT*15)) < 0 ){
                                cout<<"NO tienes suficientes monedas, consigue mas venciendo a los enemigos en la historia principal\n";
                            }else{
                                monedas-= (opT*15);
                                cout<<"Has comprado "<<opT<<" escudos\n";
                                escudos+=opT;
                                cout<<"Continuar comprando??\t[1] Si   [2]NO\n";
                                cin>>opT;
                                if (opT==1){
                                    continue;
                                }else{
                                    break;
                                }
                            }
                        }else{
                            cout<<"No tienes monedas, puedes conseguir mas derrotando a enemigos de la historia\n";
                            break;//sale de la tienda
                        }
                       
                       
                    }else if (op == 4){    
                        //Hechizo golpe definitivo, costo = 30
                        op = -1;
                        if (monedas>0){
                            cout<<"Muy bien, cuantos hechizos 'golpe definitivo' quieres comprar??\n";
                            while (true){ //valida el input
                                cout<<"[1] Una (1)\t[2] Dos (2)\t[3] Cinco (5) \n\n[4] Diez (10)\t[5] Cancelar\n\n{>>>} ";
                                cin>>opT;
                                if (opT  == 1){
                                    opT = 1;
                                    break;
                                }else if (opT == 2){
                                    opT = 2;
                                    break;
                                }else if (opT == 3){
                                    opT = 5;
                                    break;
                                }else if (opT == 4){
                                    opT = 10;
                                    break;
                                }else if (opT == 5){
                                    opT=-1;
                                    cout<<"Se ha cancelado la compra...\n";
                                    break;
                                }   
                            }//termina de validar el imput
                            if (opT==-1){//se cancela la compra
                                cout<<"Continuar comprando??\t[1] Si   [2]NO\n";
                                cin>>opT;
                                if (opT==1){
                                    continue;//regresa al inicio de la tienda
                                }else{
                                    break;//regresa al menú principal                              
                                }
                            }
                            
                            //costo = opT * 30
                            if ((monedas-(opT*30)) < 0 ){
                                cout<<"NO tienes suficientes monedas, consigue mas venciendo a los enemigos en la historia principal\n";
                            }else{
                                monedas-= (opT*30);
                                cout<<"Has comprado "<<opT<<" hechizos 'golpe definitivo'\n";
                                ataqueMortal+=opT;
                                cout<<"Continuar comprando??\t[1] Si   [2]NO\n";
                                cin>>opT;
                                if (opT==1){
                                    continue;
                                }else{
                                    break;
                                }
                            }
                        }else{
                            cout<<"No tienes monedas, puedes conseguir mas derrotando a enemigos de la historia\n";
                            break;//sale de la tienda
                        }
                    }else if (op == 5){
                        //Se regresa al menú
                        cout<<"Regresa pronto :D\n\n";
                        break;
                    }
                    
                    else{
                        cout<<"Opcion no valida :/\n";
                        continue;
                    }
                }
            break;//breake de la tienda
        case 3:
            //Dificultad
            cout<<"____________________________________________________________\n";
            cout<<"\t\t\t>>> Dificultad <<<\n";
            cout<<"____________________________________________________________\n";
            cout<<"\t\t--- A D V E R T E N C I A ---\n\n";
            cout<<"Por defecto, la dificultad esta en facil, sin embargo,\n";
            cout<<"es posible cambiarla a dificil, los enemigos seran mas\n";
            cout<<"dificiles de vencer pero obtendras mas monedas si ganas\n\n";
            cout<<"Dificultad actual: ";
            if(dificultad==1){
                cout<<"Facil\n\n";
            }else{
                cout<<"Dificil\n\n";
            }
            cout<<"Cambiar dificultad??\n[1] Si\t[2] NO\n";
            cin>>opT;
            if (opT==1){
                cout<<"[1] Facil\t\t[2] Dificil\n";
                cin>>opT;
                if (opT==2){
                    dificultad = 2;
                    cout<<"La dificultad ha cambiado a dificil...\n";
                }else{
                    cout<<"La dificultad ha cambiado a facil\n";
                }
                
            }else{
                cout<<"La dificultad continuara en ";
                if (dificultad==1){
                    cout<<"Facil\n";
                }else{
                    cout<<"Dificil\n";
                }
                
            }
            
            break;//brake de la dificultad
        case 4:
            //Salir
            break;
        default:
            //Validacion de entrada limitada a 4 casos en menuPrincipal()
            cout<<"texto de relleno\n";
            break;
        }
        //Case 4, salir del juego, aqui op = 4 para salir
        if (op==4){
            cout<<"Estas saliendo del juego...\n";
            cout<<"Gracias por jugar";
            break;
        } 
    }
}