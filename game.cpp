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


}

bool BosquesPerdidos(string personaje, int dificultad, int pociones, int pocionesMax, int escudos, int ataqueMortal){
    cout<<"B O S Q U E S  P E R D I D O S \n\n";
    
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