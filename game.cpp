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
bool hangman( int dificultad){
    string palabra_secreta;
    if(dificultad == 1){
        vector<string> palabrasFaciles = {"gato","perro","casa","sol","arbol","mesa","silla","libro","lapiz","flor","agua","azul","rojo","cielo","jugar"};
        palabra_secreta =choose_palabra(palabrasFaciles);
    }else{
        vector<string> palabrasDificiles = {"quixotesco","inefable","munificencia","efervescente","cataclismo","obnubilar","furtividad","quimerico","inexorable","pletorico","acrimonioso","intransigente","voragine","uberrimo","elocuencia"};
        palabra_secreta =choose_palabra(palabrasDificiles);
    }


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
int manoComputadora(int dificultad){
    //Genera número aleatorio entre 1 y 4
    if (dificultad==1){
        return rand() % 3 +1;
    }else{
        return rand() % 4 +1;
    }
}

//Determina quien es el ganador basado en las reglas del juego, verdadero si el usario gana, falso de otro modo
bool determinarGanador(int usuario, int computadora, string personaje, string enemigo){
    cout<<enemigo<<" eligio: ";
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


    cout<<personaje<<" eligio: ";
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
        cout<<"Has ganado una victoria\n";
        return true;
    }else if ((usuario == 1 && computadora == 3) ||
               (usuario == 2 && computadora == 1) ||
               (usuario == 3 && computadora == 2)) {
        cout << personaje<<" gano!!" << endl;
        return true;
    } else {
        cout << enemigo <<"ha ganado!!" << endl;
        return false;
    }
}

//Juego Piedra, Papel o Tiejeras, verdadero si logró ganar el juego, falso de otra manera
bool piedraPapelTijeras(int dificultad,string personaje, string enemigo){
    // Configurar la semilla para generar números aleatorios
    srand(static_cast<unsigned int>(time(0)));
    int victorias = 0;
    int round = 1; 
    int necesarias;

    cout<<"---------------------------------\n";
    cout << "\nBienvenido al juego de Piedra, Papel o Tijeras." << endl;
    cout << "Victorias necesarias para ganar: ";
    if (dificultad == 1){
        cout<<"1\n";
        necesarias=1;
    }else{
        cout<<"3\n";
        necesarias=3;
    }
    cout<<"Los empates seran considerados como victorias :D"<<endl;
    cout<<"---------------------------------";    
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
        int computadora = manoComputadora(dificultad);
        //int computadora = 2; //prueba
        if(determinarGanador(usuario, computadora, personaje,enemigo)){
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
    if(victorias==necesarias){
        return true;
    }else{return false;}
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
    cout<<"\n\n********************************************************************************\n";
    cout<<"\tLa batalla contra "<<nomEnemigo<<" ha empezado\n";
    cout<<"\n\n********************************************************************************\n";

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
                    if(piedraPapelTijeras(dificultad,nomPersonaje,nomEnemigo)){
                        cout<<"Felicidades, has ganado el Piedra papel o tijeras de la muerte\n";
                        return true;
                    }else{
                        cout<<"Oh no, has perdido en el Piedra, papel o tijeras de la muerte\n";
                        return false;
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
        cout<<"[4] Para ver el progreso de la historia\n";
        cout<<"[5] Para salir del juego\n ";
        cin>>op;
        if (op == 1){
            return 1;
        }else if (op == 2){
            return 2;
        }else if (op == 3){
            return 3;
        }else if (op == 4){
            return 4;
        }else if (op == 5){
            return 5;
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
//------ruleta rusa-------
// Función para simular el giro del tambor
bool girarTambor() {
    srand(static_cast<unsigned int>(time(0)));
    return rand() % 6 == 0; // 1/6 de probabilidad de disparar
}

// Función que implementa el juego de la ruleta rusa y retorna true si el jugador 1 es el último en pie
bool jugarRuletaRusa(const string& jugador1, const string& jugador2, const string& jugador3) {
    srand(static_cast<unsigned int>(time(0)));
    string jugadores[] = {jugador1, jugador2, jugador3};
    int numJugadores = 3;

    int tambor[6] = {0}; // Tambor con 6 cámaras, inicialmente todas vacías
    int posicionActual = 0; // Posición del revólver

    // Colocamos una bala en una posición aleatoria
    tambor[rand() % 6] = 1;

    while (numJugadores > 1) {
        for (int i = 0; i < numJugadores; i++) {
            cout << "Es el turno de " << jugadores[i] << "." << endl;
            cout << "Presiona Enter para girar el tambor.";
            cin.ignore();
            cin.get(); // Espera a que el jugador presione Enter

            if (girarTambor()) {
                cout << "¡BANG! " << jugadores[i] << " ha sido eliminado." << endl;
                // Elimina al jugador eliminado del juego
                for (int j = i; j < numJugadores - 1; j++) {
                    jugadores[j] = jugadores[j + 1];
                }
                numJugadores--;

                // Verifica si el jugador 1 es el último en pie después de la eliminación
                if (numJugadores == 1 && jugadores[0] == jugador1) {
                    return true;
                }

                break; // Sale del bucle for
            } else {
                cout << "Click. " << jugadores[i] << " ha sobrevivido." << endl;
            }

            // Mueve la posición del tambor al siguiente jugador
            posicionActual = (posicionActual + 1) % 6;
        }
    }

    // Si llegamos aquí, el jugador 1 no es el último en pie
    return false;
}
//------ruleta rusa-------
//------trivia----------
struct Pregunta {
    string enunciado;
    vector<string> opciones;
    int respuestaCorrecta;
};

// Función para mostrar la pregunta y opciones
void mostrarPregunta(const Pregunta& pregunta) {
    cout << pregunta.enunciado << endl;
    for (size_t i = 0; i < pregunta.opciones.size(); ++i) {
        cout << i + 1 << ". " << pregunta.opciones[i] << endl;
    }
    cout << "Ingresa el número de tu respuesta: ";
}

// Función para verificar si la respuesta es correcta
bool verificarRespuesta(const Pregunta& pregunta, int respuesta) {
    return respuesta == pregunta.respuestaCorrecta;
}

// Función para jugar a la trivia y retornar verdadero si la mayoría de las respuestas son correctas
bool jugarTrivia() {
    srand(static_cast<unsigned int>(time(0)));
    vector<Pregunta> preguntasSet1;
    preguntasSet1.push_back({"¿Cuál es la capital de Francia?", {"Londres", "París", "Madrid"}, 2});
    preguntasSet1.push_back({"¿En qué año comenzó la Segunda Guerra Mundial?", {"1939", "1945", "1914"}, 1});
    preguntasSet1.push_back({"¿Cuántos continentes hay en el mundo?", {"6", "7", "5"}, 2});
    preguntasSet1.push_back({"¿Quién escribió 'Romeo y Julieta'?", {"Charles Dickens", "William Shakespeare", "Jane Austen"}, 2});
    preguntasSet1.push_back({"¿Cuál es el río más largo del mundo?", {"Nilo", "Amazonas", "Misisipi"}, 2});

    vector<Pregunta> preguntasSet2;
    preguntasSet2.push_back({"¿Cuál es el elemento más abundante en la corteza terrestre?", {"Hierro", "Oxígeno", "Carbono"}, 2});
    preguntasSet2.push_back({"¿Cuál es la montaña más alta del mundo?", {"Kilimanjaro", "Mont Everest", "Mont Blanc"}, 2});
    preguntasSet2.push_back({"¿En qué año se fundó Google?", {"1998", "2005", "1995"}, 1});
    preguntasSet2.push_back({"¿Cuál es el animal terrestre más rápido?", {"León", "Guepardo", "Antílope"}, 2});
    preguntasSet2.push_back({"¿Quién pintó la Mona Lisa?", {"Vincent van Gogh", "Leonardo da Vinci", "Pablo Picasso"}, 2});

    vector<Pregunta> preguntasSet3;

    preguntasSet3.push_back({"¿Cuál es el océano más grande del mundo?", {"Atlántico", "Índico", "Pacífico"}, 3});
    preguntasSet3.push_back({"¿Cuál es el país más grande en términos de área?", {"Estados Unidos", "Rusia", "China"}, 2});
    preguntasSet3.push_back({"¿Cuántos huesos tiene el cuerpo humano en promedio?", {"206", "300", "150"}, 1});
    preguntasSet3.push_back({"¿Quién escribió 'Cien años de soledad'?", {"Mario Vargas Llosa", "Gabriel García Márquez", "Isabel Allende"}, 2});
    preguntasSet3.push_back({"¿Cuál es el instrumento musical más grande de la familia de las cuerdas?", {"Violín", "Contrabajo", "Viola"}, 2});

    int aleatorio = rand()%3 + 1;
    vector<Pregunta> preguntas;

    if (aleatorio == 1){
         preguntas = preguntasSet1;
    }else if (aleatorio == 2){
         preguntas = preguntasSet2;
    }else{
         preguntas = preguntasSet3;
    }

    int puntaje = 0;

    // Itera a través de las preguntas
    for (const Pregunta& pregunta : preguntas) {
        mostrarPregunta(pregunta);

        int respuesta;
        while (!(cin >> respuesta) || respuesta < 1 || respuesta > pregunta.opciones.size()) {
            cout << "Respuesta inválida. Ingresa un número válido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (verificarRespuesta(pregunta, respuesta)) {
            cout << "¡Correcto!" << endl;
            puntaje++;
        } else {
            cout << "Incorrecto. La respuesta correcta es: " << pregunta.respuestaCorrecta << endl;
        }

        cout << "------------------------" << endl;
    }

    // Retornar verdadero si la mayoría de las respuestas son correctas
    return puntaje >= preguntas.size() / 2;
}
//------trivia----------
//Introduccion
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
    cout<<"Manifestaron ir tras tres lugares: Bosques perdidos, Reinos Zora y a las Ruinas del Abismo...\n";
    cout<<"Pues se rumora que cada uno de esos tres luegares alberga un fragmento de la PIEDRA FILOSOFAL\n";
    cout<<"-----------------------------------------------------------------------------------------------\n\n\n";
}

//Bosques perdidos historia
bool BosquesPerdidos(string personaje, int dificultad, int pociones, int pocionesMax, int escudos, int ataqueMortal){
    int op1, op2,  op4, op5;
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
                    cout<<"\n\nQue deseas hacer??[1] Pelear\t[2] Pelear\t[3] Pelear\n\n";
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
                    cout<<"Serpiente Indú: Espera, no queriassss quitarme mi comida???,\nDebisste haberlo mencionado antesss, todo esto es un simple mal\n";
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
                    cout<<"Serpiente Indú: Espera, no queriassss quitarme mi comida???,\nDebisste haberlo mencionado antesss, todo esto es un simple mal\n";
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

            break;
        case 3://Primera opcion
            //Pagar al oso
            cout<<"---------------------------------------------------------------------------------------------------------\n";
            cout<<"Oso: Puedo ver que hay un poco de masoquismo en ti...jeje...no solo sé solo soy un Oso que hablar...jaja\n";
            cout<<personaje<<" arranca uno de sus corazones y se lo ofrese al osos como forma de pago\n";
            corazones--;
            cout<<"Corazones actuales: "<<corazones<<endl;
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

//Reinos Zora
bool ReinosZora(string personaje, int dificultad, int pociones, int pocionesMax, int escudos, int ataqueMortal){
    int op1,op2,op3,op4;
    int corazones = 3;
    cout<<"-------------------------------------------------------------------------------------------------------------\n";
    cout<<"\tR E I N O S  Z O R A\n\n";
    cout<<"-------------------------------------------------------------------------------------------------------------\n";
    cout<<"Los lagos son en verdad de agua o aparentan serlo??. Si bien los cuerpos de agua proceden desde un clico\n";
    cout<<"y con sus ciertos desfaces por alteraciones no naturales como la humana son por si mismos una gran fuente\n ";
    cout<<"albergadora de vida, o eso era. Poco se conoce de la raza Zora, seres que se dice provienen del cielo\n";
    cout<<"llegaron a travez de bolas de fuego que calleron al mar, pero, no se tendrían registros de estos hasta que\n";
    cout<<"un viejo pescador de la costa este, en medio de una tormenta en el centro del golfo que forma el continente\n";
    cout<<"seria arrazado por una imponente ola moustro, hundiendo a toda la tripulacion del barco pesquero y dejandolos\n";
    cout<<"a la deriva, con solo suministros para 2 dias, una brujula con el puntero rojo girando sin sentido, y 10 litros\n";
    cout<<"de agua para consumo, y es ahí en donde se hizo el primer contacto con esta especie, seres llenos de tentaculos\n";
    cout<<"piel azul diamente, con cuerpos variados devido al nivel de precion atmosferica, cada colonia de los Zora\n";
    cout<<"abarca aproximadamente 3 leguas marinas, sin embargo, como todo comun denominador en cualquier especie avanzada\n";
    cout<<"constantemente estan en guerra por más territorio. Desde que se estableció un acuerdo maritimo para los continentes\n";
    cout<<"y los Zora, se ha logrado que los barcos navios lleguen más rapido, las rutas comerciales se expanden cada vez más\n";
    cout<<"y el mundo burgues se hace cada vez más la regla, sin embargo, desde que estos alienigenas llegaron, todo su\n";
    cout<<"desarrollo tecnologico se ha enfocado en la vida marina, llena de seres apenas pensantes, compadeciendose de ellos\n";
    cout<<"lograron gracias a un sistema de plasmidos, hacer que las especies marinas avancen por lo menos 50,000 millones\n";
    cout<<"de años, dotandolos de una gran inteligencia y formando todo un imperio de vida bajo el mar. Existen dos grandes\n";
    cout<<"problemas con esta neo civilizacion, el primero es una adiccion hacia los plasmidos, pues su alto consumo provoca\n";
    cout<<"deformaciones genetias que eventualmente terminan matando al ser, el segundo problema es un desavastecimiento de comida\n";
    cout<<"despues del tratado del Atlantico este y sur, se llegó al acuerdo de no comer a otro ser pensante marino, por lo que\n";
    cout<<"desarrollaron un meto de alimentacion a base de fotosintesis, sin embargo, las mutaciones de los plasmidos han\n";
    cout<<"creado mutaciones de la sintesis dependientes de la melanina humana, es por ello que suelen cazar algunos barcos\n";
    cout<<"perdidos, o embarcaciones desoladas, le arrancan los ojos a los humanos junto con su cabello y por ultimo lo someten\n";
    cout<<"a un proceso que retira toda la piel del cuerpo, sin embargo, suelen usar los corazones y la medula espinal\n";
    cout<<"como un condimento especial muy vendido en el mercado profundo, ademas de tambien \n";
    cout<<"para conseguir aun más melanina especial. Esta meleanina es unica pues es capaz de obtener energia\n";
    cout<<"disociando las moleculas de agua a partir de la radiacion electromagnetica, un proceso similar a la clorofila\n";
    cout<<"pero mucho más efectiva.\n";
    cout<<"-------------------------------------------------------------------------------------------------------------\n";
    cout<<personaje<<" se aventura en un barco con direccion a los reinos Zora...\n";
    cout<<"Una gabiota se acerca a "<<personaje<<endl;
    cout<<"GABIOTA: NI los mejores marineros se atreverían a navegar por estas aguas tan turbulentas, si lo que deseas es uno \n";
    cout<<"de esos fragmentos rojos, deberás buscar en lo más profundo de ti y del mar. Ese barco no restirá, los viejos Zoras\n";
    cout<<"que venian a las costas les daban a estas semillas a humanos ingenuos, las semillas del hermitaño te permiten estar\n";
    cout<<"en el fondo del mar sin la necesidad de respirar, crea momentanamente un organo adaptativo a partir del apendice que\n";
    cout<<"lleva el oxigeno del mar a tus pulmones, estas semillas solo funcionan durante 24 horas, pero los días de luna llena\n";
    cout<<"el efecto se hace aun mas fuerte, provocando tumores malignos una fuerte descalcificaion en los huesos\n";
    cout<<"por lo que si estas en lo profundo del oceano la presion atmosferica terminará triturandote vivo todo el sistema oceo\n";
    cout<<"por cierto, cuando lo encuentres no lo mieres a los ojos...sabras lo que significa cuando lo veas...\n";
    cout<<"-------------------------------------------------------------------------------------------------------------\n";
    while (corazones>0)
    {
        cout<<"Que te gustaría hacer??\n[1] Comer la semilla del hermitaño\t[2] NO comer la semilla del hermitaño\t[3] Sospechar de la gabiota\n\n";
        cin>>op1;
        if (op1==1){
            //Comer la semilla del hermitaño
            while (true){
                cout<<"-------------------------------------------------------------------------------------------------------------\n";
                cout<<"A pesar de lo poco confiable que puede ser comer algo que un extraño te ofrese por motivos desconocidos.     \n";
                cout<<"asceptas el riesgo que tu decicion implica y no te deas intimidar por falsos prejuicios de la sociedad       \n";
                cout<<personaje<<" consume las semillas del hermitaño....                                                           \n";
                cout<<"GABIOTA: jeje a veces es bueno asceptar la ayuda de los demas jeje...Sigue tu viaje, simplemente recuerda    \n";
                cout<<"mantener tu melanina a salvo si es que no quieres terminar siendo comida de los Zora ac...ac                 \n";
                cout<<"(graznido de gaviota)                                                                                        \n";
                cout<<"-------------------------------------------------------------------------------------------------------------\n\n";
                cout<<"Para aprovechar al maximo tu nueva habilidad, decides saltar de barco y nadar directamente hacia las         \n";
                cout<<"profundidades del mar, empiezas a ver algunos seres Zora de aspecto reflejante y deciden cazarte...          \n";
                cout<<"La pelea es inevitable...pero...                                                                             \n";
                cout<<"Que te gustaría hacer??\n[1] Pelear\t[2] Hablar\t[3] Sacrificar un corazon\n\n";
                cin>>op2;
                switch (op2){
                case 1:
                    //Pelear
                    cout<<"Estas determinado a enfrentar la situación...\n";
                    if (batallaPorTurnos(personaje,"Zora dosil",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                        cout<<"Pueden ver tu determinacion pero no te dejaran pasar hasta que les des solo uno de tus corazones...\n";
                        cout<<"renegado, les dan uno de tus corazones\n";
                        corazones--;
                        cout<<"Corazones actuales: "<<corazones<<endl;
                    }else{
                        cout<<"Despues de intentar salvar tu vida, los Zora ven algo en ti, algo que les recuerda a ellos, lo toman uno de tus corazones\n";
                        cout<<"y te dejan seguir...\n";
                        corazones--;
                        cout<<"Corazones actuales: "<<corazones<<endl;
                    }
                    cout<<"-------------------------------------------------------------------------------------------------------------\n\n";
                    cout<<"Despues de evirar ser comido, por una simple forma extraña de una sensibilidad alianada entre seres\n";
                    cout<<"continuas bajando, pues es todo lo que queda, tu cuerpo se acontumbra al lento procesoce del cambio de \n";
                    cout<<"presion atmosferico, la luz empieza a hacerse más escasa, el oceano no solo no parece tener fin, tambie es una\n";
                    cout<<"exprecion pura de profundidad. A pesar de lo poco que se conoce de los Zora, es bien sabido que la cuspide de\n";
                    cout<<"su creación fue la metropolis llamada Raputure, un lugar lleno de los grandes misterios pues no mucha gente se\n";
                    cout<<"ha atrevido a llegar tan lejos, se dice que fue contruida por encima de los viejos restos de la ATLANTIDA y \n";
                    cout<<"para hacer aún más seguro el lugar, lo cubrieron debajo de un domo trasparente.\n";
                    cout<<"LLegas al fondo del oceano y encuentras una red de tubos de trasporte, aparentemente la manera de moverse es \n";
                    cout<<"dejando que la tecnologia lo haga, ademas, hay una cabina de abordaje que permite subir a cualquier especie marina.\n";
                    cout<<"Al llegar a la cabina de abordaje te percatas que el capitan ispecciona el pase para abordar, encuentras una especie\n";
                    cout<<"de taquilla, y procedes a coprar un boleto, sin embargo te hacen una comision por el cambio de moneda, y todavía\n";
                    cout<<"te hacen dejar una propina al sistema de cambios automaticos, estas frustrado, pero tienes tu boleto, haces fila\n";
                    cout<<"para abordar el trasporte, el capitan que supervisa los boletos te ve de pies a cabeza, es facil reconocer que\n";
                    cout<<"no eres un animal marino, sin embargo un neo delfin arto de esperar en la fila, pide que se apresuren\n";
                    cout<<"el capitan te deja pasar aparentemente. Entras al vagon, una vez lleno, empieza a moverse a muy alta velocidad,los\n ";
                    cout<<"los tubos parecen estar echos de una especie de fibrra de vidrio unida uno con otro a travez de un superconductor\n";
                    cout<<"capas de manejar los campos delectromagneticos de los vagones, y todo el tubo está cubierto por fibra de carbono\n";
                    cout<<"transparente, todo el sitema de tubos funciona por nodos, como si fueran grafos.\n ";
                    cout<<"Una vez llegando a la gran central (o gran nodo), puedes ver como se abre ante ti un grupo armado de tiburones blancos\n";
                    cout<<"el dominio de los Zora no solo se remonta a su propia existencia, si no al de muchos seres marinos\n";
                    cout<<"empiezas a correr pero todo parece ser muy confuso, empiezas a marearte, tal vez sea un efecto secundario de las\n";
                    cout<<"semillas del hermitaño, finalmente vuelves a ti y ahí junto con los tiburones blanco se presenta ante ti el gran\n";
                    cout<<"KITO CORLEONE, un gran tiburon blanco mutado por los plasmidos, pero que en realidad no es si no más que otra\n";
                    cout<<"marioneta de las grandes mentes Zora, KITO, te hace unas preguntas pero no sabes lo que dice, y al nunca haber\n";
                    cout<<"situación similar, no hay una especie de protocolo por lo que deciden llevarte ante el Rey del Todo para que decida\n";
                    cout<<"qué hacer contigo, usan una bolsa de pseaudo plastico biodegradable a vase de algas para taparte la cara y no\n";
                    cout<<"puedas ver el camino...\n";
                    cout<<"vuelves a ser despertado de una manera ruda, uno de los tiburones de KITO te azotado la cara contra una especie\n";
                    cout<<"de libro en un atril de oro. Lo poco que puedes distinguir es que la pagina de ese libro dice en varios idiomas\n";
                    cout<<"incluyendo el humano: NO LO MIRES A LOS OJOS. Una voz o más bien un sonido tan grave que retumba por todo \n";
                    cout<<"comienza a decir algo, porque parece tener un ritmo, parece hablar en una lengua tan antigua arena del mar\n";
                    cout<<"todo esta oscuro, no puedes ver de donde vienen esos sonidos, pero logras escuchar una cadena acercandose...\n";
                    cout<<"entre las oscuridades más profundas, puedes lograr ver una luz de una vela marina, siguie acercandose hasta que \n";
                    cout<<"depues de ese basto sonido de cadenas se puede entrever un ser encapuchado con una tunica roja, te ve, y lo sabe\n";
                    cout<<"sabe que este día llegaría...\n\n";
                    cout<<"MILLER: Sabes como es esto, no??. Bueno primero es decir que este lugar realmente no es Rapture, si no que el \n";
                    cout<<"\tverdadero nombre  es R'lyeh y has viajado tanto que has llegado al oceano Pacífico. Este momento es realmente sublime\n";
                    cout<<"\tlos millones de años han pasado y por fin, solo tines que decir las palabras sagradas y todo estára listo\n";
                    cout<<"\t¿Qué pasa, no las conoces a caso?¿Cómo es eso posible?, espera, no sabes lo que está ocurriendo cierto???\n";
                    cout<<"\tjajajajajajajajajajajajajajajajajajajajajajajajaja, esto es en serio fabuloso, tan kafkiano, veras, estas apunto\n";
                    cout<<"\tde traer paz al mundo...(está mintiendo), todo lo que necesitas saber está en ese libro, serías tan amable de\n";
                    cout<<"\tcambiar de pagina??...\n\n";
                    cout<<"Cambias la pagina y ves un mismo texto escrito en los diferentes lenguajes, una frase que se repite y se repite: \n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"-------------------------------------------------------------------------------------------------------------\n\n";
                    while (true){
                        cout<<"QUE QUIERES HACER??\n[1] RECITAR LA SAGRADA FRASE\t[2] NO RECITAR LA SAGRADA FRASE\t[3] Intentar escapar\n\n";
                        cin>>op3;
                        switch (op3){
                        case 1:
                            //recita la sagrada frase
                            cout<<"Recuerdas las palabres de aquella gaviota al inicio de tu aventura, y decides recitar las palabras sagradas\n";
                            cout<<"sin saber exactamente lo que significa ni lo que está pasando, prefieres no ver a nadie a los ojos\n";
                            cout<<"en cuanto comienzas, el tiempo parece detenerse, y todo el oceano comienza a herbir, los suelos se agritan\n";
                            cout<<"y sale lava de las fragmentaciones, empiezas a sentir que flotas, cada vez más y más arriba en un estado de\n";
                            cout<<"trance profundo repitiendo las frases sagradas, y de repente, vuelves a ti, estas en la playa, a mitad de una\n";
                            cout<<"tormenta de relampagos y tsunamis, en las aguas de los mares comiezan a salir seres marinos sin vida,\n";
                            cout<<"incluyendo algunos Zora, y al fondo ves a un monstruo de contornos vagamente antropoides, pero con una cabeza\n";
                            cout<<"de pulpo cuyo rostro es una masa de tentaculos, un cuerpo escamoso que sugiere cierta elasticidad, cuatro\n";
                            cout<<"extremidades dotadas de garras enormes y un par de alas largas y estrechas en la espalda...\n";
                            cout<<"el caos viviente ha despertado y viene a reclamar lo que es suyo, el planeta, el gran ser aterra a todos\n";
                            cout<<"avionetas esparcen un mensaje: Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn. Te parece similar, reaccionas\n";
                            cout<<"esas palabras han causado todo este desastre. Comienza a haber todo un cataclismo ambiental, nada parecido\n";
                            cout<<"a algo nunca antes visto. Las personas que intentan luchar por su vida contra este ser cosmico socumben a la\n";
                            cout<<"locura, comienzan a haber más habionetas con bocinas que predican ser seguidores del ser, son los seguidores\n";
                            cout<<"del sacerdote. Repentinamente, del agua sale Miller, explicando lo que ha sucedido, acabas de despertar a un ser\n";
                            cout<<"cosmico ancestral que esperaba en un sueño eterno. Tambien te revela que hay un fragmento de la piedra que tanto\n";
                            cout<<"anhelas, y está incrustrada en una de sus alas, se despide de ti, proclama que su verdadero nombre no es miller\n";
                            cout<<"Su verdadero nombre es NYARLATHOTEP...\nLuego procede a mostrarte su verdadera forma, una gran masa poliposa\n";
                            cout<<"con una larga excrecion roja, o es el lo que cree que quieres ver...\n";
                            cout<<"-------------------------------------------------------------------------------------------------------------\n\n";
                            cout<<"Decides seguirle la pista al gran moustro marino, encuentras un tronco liso a medio cortar, rompes 3/4\n";
                            cout<<"de los anillos del tronco, decides impulsarte desde una montaña y usar la corteza del tronco como\n";
                            cout<<"recorres rapidamente la playa y llegas a un pueblo habitado por personas con tres ojos, pregutas por direcciones\n";
                            cout<<"y continuas tu viaje, cerca de llegar al moustro, decides subir un molino que esta proximo a llegar \n";
                            cout<<"subes a lo más alto del molino y saltas a una de sus aspas, y te impulsas con tu propio peso para\n";
                            cout<<"aprobechar el momentum y saltas hasta la cima del molino donde esperas al gigante marino\n";
                            cout<<"el logra verte e intenta destruir el molino, aprobechas ese momento para subirte a uno de sus brazos y \n";
                            cout<<"correr a travez de el, pronto llegas a su espalda y ubicas el fragmaento de la piedra en una terminacion\n";
                            cout<<"del ala, te lanzas hacia ella y por fin la consigues, otro fragmento de la piedra filosofal\n";
                            cout<<"Pero el cara de masa tentacular logra sentirte y logra arrojarte de nuevo al mar, pronto el planeta\n";
                            cout<<"comienza a ser inestable y empieza a expulsar torres de lava, desde lo lejos logras percatarte de \n";
                            cout<<"una explosion masiva, el nucleo de la tierra explotó y el planeta con el. Estas varado en el espacio \n";
                            cout<<"sin poder respirar. Las cosas empiezan a detenerse, un punto rojo a lo lejos se comienza a acercar\n";
                            cout<<"el punto rojo se presenta a si mismo como MEFISTOFELES, y te ofrece un trato, el cual consiste en que\n";
                            cout<<"nunca haber despertado al moustro marino a cambio de tu alma\n";
                            cout<<"-------------------------------------------------------------------------------------------------------------\n\n";
                            cout<<"Qué quieres hacer??\n[1] Vender alma\t[2] No vender alma\t[3] Negociar\n";
                            cin>>op4;
                            if (op4 == 3 || op4 == 2){
                                cout<<"NO terminas de aceptar vender tu alma del todo, MEFISTOFELES, entendiendo de la clase de problema\n";
                                cout<<"en la que te acabas e meter, se pregunta si relamente hacía falta salvarte, se cuentiona a si mismo\n";
                                cout<<"encuentra la respuesta en su interior, no debe ayudarte...\nMEFISTOFELES TE HA HABANDONADO...\n";
                                cout<<"Se reanudan las cosas en el espacio tiempo , tu sangre empieza a herbir y te empiezas a sofocar por la falta\n";
                                cout<<"de oxigeno...terminas muriendo\n";
                                cout<<"sin embargo y apesar de tus malas deciciones,MEFISTOFELES te deja un regalo...intenetarlo otra vez\n";
                                continue;
                            }else if (op4 == 1){
                                cout<<"Al verte superado por la situacion, decides aceptar el trato siempre y cuando puedas conservar el fragmento\n";
                                cout<<"de la piedra filosofal...el simplemente ascepta...\n\n";
                                return true;
                            }else{
                                cout<<"Opcion no valida\n";
                            }
                            break;
                        case 2:
                            //no recita la sagrada frase
                            cout<<"Te niegas a hacer lo que te pide, no quieres formar parte de ningun rito extraño, ni nada por el estilo\n";
                            cout<<"pero las salidas se cierran y queda solamente la luz de Miller, reflejando el atril de oro decides desafiar\n";
                            cout<<"a miller, él se empieza a reir, desconcertado levantas la mirada y logras finalmente verlo, un mounstro de\n";
                            cout<<"contornos vagamente antropoides, pero con una cabeza de pulpo cuyo rostro es una masa de tentaculos,\n";
                            cout<<"un cuerpo escamoso que sugiere cierta elasticidad, cuatro extremidades dotadas de garras enormes y un\n";
                            cout<<"par de alas largas y estrechas en la espalda....\n";
                            cout<<"Haces contacto visual con el y ....\n";
                            cout<<"sales de la habitación con la mirada viendo la nada, llegas al centro de la estacion que conecta al nodo \n";
                            cout<<"central, en medio del todo, te quitas los ojos, caes de rodillas y mueres...\n";
                            cout<<"tu ecuentro con el ser ancestral te ha llevado a la locura...\n";
                            return false;
                            break;
                        case 3:
                            //intenta escapar
                            cout<<"Te ves superado por la situacion, empiezas a perder la cabeza...empiezas a escuhar voces susurrandote\n";
                            cout<<"que debes recitar la sagrada frase, entras en desesperación, tu pupilas se comienzan a dilatar, y \n";
                            cout<<"decides alzar la mirada, y logras verlo finalmente...logras quedar anonadado por un mounstro de \n";
                            cout<<"contornos vagamente antropoides, pero con una cabeza de pulpo cuyo rostro es una masa de tentaculos,\n";
                            cout<<"un cuerpo escamoso que sugiere cierta elasticidad, cuatro extremidades dotadas de garras enormes y un\n";
                            cout<<"par de alas largas y estrechas en la espalda....\n";
                            cout<<"Haces contacto visual con el y ....\n";
                            cout<<"sales de la habitación con la mirada viendo la nada, llegas al centro de la estacion que conecta al nodo \n";
                            cout<<"central, en medio del todo, te quitas los ojos, caes de rodillas y mueres...\n";
                            cout<<"tu ecuentro con el ser ancestral te ha llevado a la locura...\n";
                            return false;
                            break;
                        default:
                            cout<<"Opcion no valida\nRECITA LA SAGRADA FRASE....\n";
                            break;
                        }
                    }      
                    break;
                case 2:
                    //Hablar
                    cout<<"Intentas hablar y negociar con los Zora, sin embargo, ellos desarrollaron otro lenguaje, algun si son capaces\n";
                    cout<<"de comunicarse, pero estos no, no te queda otra opcion más que pelear...\n";
                    if (batallaPorTurnos(personaje,"Zora dosil",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                        cout<<"Pueden ver tu determinacion pero no te dejaran pasar hasta que les des solo uno de tus corazones...\n";
                        cout<<"renegado, les dan uno de tus corazones\n";
                        corazones--;
                        cout<<"Corazones actuales: "<<corazones<<endl;
                    }else{
                        cout<<"Despues de intentar salvar tu vida, los Zora ven algo en ti, algo que les recuerda a ellos, lo toman uno de tus corazones\n";
                        cout<<"y te dejan seguir...\n";
                        corazones--;
                        cout<<"Corazones actuales: "<<corazones<<endl;
                        }
                    cout<<"-------------------------------------------------------------------------------------------------------------\n\n";
                    cout<<"Despues de evirar ser comido, por una simple forma extraña de una sensibilidad alianada entre seres\n";
                    cout<<"continuas bajando, pues es todo lo que queda, tu cuerpo se acontumbra al lento procesoce del cambio de \n";
                    cout<<"presion atmosferico, la luz empieza a hacerse más escasa, el oceano no solo no parece tener fin, tambie es una\n";
                    cout<<"exprecion pura de profundidad. A pesar de lo poco que se conoce de los Zora, es bien sabido que la cuspide de\n";
                    cout<<"su creación fue la metropolis llamada Raputure, un lugar lleno de los grandes misterios pues no mucha gente se\n";
                    cout<<"ha atrevido a llegar tan lejos, se dice que fue contruida por encima de los viejos restos de la ATLANTIDA y \n";
                    cout<<"para hacer aún más seguro el lugar, lo cubrieron debajo de un domo trasparente.\n";
                    cout<<"LLegas al fondo del oceano y encuentras una red de tubos de trasporte, aparentemente la manera de moverse es \n";
                    cout<<"dejando que la tecnologia lo haga, ademas, hay una cabina de abordaje que permite subir a cualquier especie marina.\n";
                    cout<<"Al llegar a la cabina de abordaje te percatas que el capitan ispecciona el pase para abordar, encuentras una especie\n";
                    cout<<"de taquilla, y procedes a coprar un boleto, sin embargo te hacen una comision por el cambio de moneda, y todavía\n";
                    cout<<"te hacen dejar una propina al sistema de cambios automaticos, estas frustrado, pero tienes tu boleto, haces fila\n";
                    cout<<"para abordar el trasporte, el capitan que supervisa los boletos te ve de pies a cabeza, es facil reconocer que\n";
                    cout<<"no eres un animal marino, sin embargo un neo delfin arto de esperar en la fila, pide que se apresuren\n";
                    cout<<"el capitan te deja pasar aparentemente. Entras al vagon, una vez lleno, empieza a moverse a muy alta velocidad,los\n ";
                    cout<<"los tubos parecen estar echos de una especie de fibrra de vidrio unida uno con otro a travez de un superconductor\n";
                    cout<<"capas de manejar los campos delectromagneticos de los vagones, y todo el tubo está cubierto por fibra de carbono\n";
                    cout<<"transparente, todo el sitema de tubos funciona por nodos, como si fueran grafos.\n ";
                    cout<<"Una vez llegando a la gran central (o gran nodo), puedes ver como se abre ante ti un grupo armado de tiburones blancos\n";
                    cout<<"el dominio de los Zora no solo se remonta a su propia existencia, si no al de muchos seres marinos\n";
                    cout<<"empiezas a correr pero todo parece ser muy confuso, empiezas a marearte, tal vez sea un efecto secundario de las\n";
                    cout<<"semillas del hermitaño, finalmente vuelves a ti y ahí junto con los tiburones blanco se presenta ante ti el gran\n";
                    cout<<"KITO CORLEONE, un gran tiburon blanco mutado por los plasmidos, pero que en realidad no es si no más que otra\n";
                    cout<<"marioneta de las grandes mentes Zora, KITO, te hace unas preguntas pero no sabes lo que dice, y al nunca haber\n";
                    cout<<"situación similar, no hay una especie de protocolo por lo que deciden llevarte ante el Rey del Todo para que decida\n";
                    cout<<"qué hacer contigo, usan una bolsa de pseaudo plastico biodegradable a vase de algas para taparte la cara y no\n";
                    cout<<"puedas ver el camino...\n";
                    cout<<"vuelves a ser despertado de una manera ruda, uno de los tiburones de KITO te azotado la cara contra una especie\n";
                    cout<<"de libro en un atril de oro. Lo poco que puedes distinguir es que la pagina de ese libro dice en varios idiomas\n";
                    cout<<"incluyendo el humano: NO LO MIRES A LOS OJOS. Una voz o más bien un sonido tan grave que retumba por todo \n";
                    cout<<"comienza a decir algo, porque parece tener un ritmo, parece hablar en una lengua tan antigua arena del mar\n";
                    cout<<"todo esta oscuro, no puedes ver de donde vienen esos sonidos, pero logras escuchar una cadena acercandose...\n";
                    cout<<"entre las oscuridades más profundas, puedes lograr ver una luz de una vela marina, siguie acercandose hasta que \n";
                    cout<<"depues de ese basto sonido de cadenas se puede entrever un ser encapuchado con una tunica roja, te ve, y lo sabe\n";
                    cout<<"sabe que este día llegaría...\n\n";
                    cout<<"MILLER: Sabes como es esto, no??. Bueno primero es decir que este lugar realmente no es Rapture, si no que el \n";
                    cout<<"\tverdadero nombre  es R'lyeh y has viajado tanto que has llegado al oceano Pacífico. Este momento es realmente sublime\n";
                    cout<<"\tlos millones de años han pasado y por fin, solo tines que decir las palabras sagradas y todo estára listo\n";
                    cout<<"\t¿Qué pasa, no las conoces a caso?¿Cómo es eso posible?, espera, no sabes lo que está ocurriendo cierto???\n";
                    cout<<"\tjajajajajajajajajajajajajajajajajajajajajajajajaja, esto es en serio fabuloso, tan kafkiano, veras, estas apunto\n";
                    cout<<"\tde traer paz al mundo...(está mintiendo), todo lo que necesitas saber está en ese libro, serías tan amable de\n";
                    cout<<"\tcambiar de pagina??...\n\n";
                    cout<<"Cambias la pagina y ves un mismo texto escrito en los diferentes lenguajes, una frase que se repite y se repite: \n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"-------------------------------------------------------------------------------------------------------------\n\n";
                    while (true){
                        cout<<"QUE QUIERES HACER??\n[1] RECITAR LA SAGRADA FRASE\t[2] NO RECITAR LA SAGRADA FRASE\t[3] Intentar escapar\n\n";
                        cin>>op3;
                        switch (op3){
                        case 1:
                            //recita la sagrada frase
                            cout<<"Recuerdas las palabres de aquella gaviota al inicio de tu aventura, y decides recitar las palabras sagradas\n";
                            cout<<"sin saber exactamente lo que significa ni lo que está pasando, prefieres no ver a nadie a los ojos\n";
                            cout<<"en cuanto comienzas, el tiempo parece detenerse, y todo el oceano comienza a herbir, los suelos se agritan\n";
                            cout<<"y sale lava de las fragmentaciones, empiezas a sentir que flotas, cada vez más y más arriba en un estado de\n";
                            cout<<"trance profundo repitiendo las frases sagradas, y de repente, vuelves a ti, estas en la playa, a mitad de una\n";
                            cout<<"tormenta de relampagos y tsunamis, en las aguas de los mares comiezan a salir seres marinos sin vida,\n";
                            cout<<"incluyendo algunos Zora, y al fondo ves a un monstruo de contornos vagamente antropoides, pero con una cabeza\n";
                            cout<<"de pulpo cuyo rostro es una masa de tentaculos, un cuerpo escamoso que sugiere cierta elasticidad, cuatro\n";
                            cout<<"extremidades dotadas de garras enormes y un par de alas largas y estrechas en la espalda...\n";
                            cout<<"el caos viviente ha despertado y viene a reclamar lo que es suyo, el planeta, el gran ser aterra a todos\n";
                            cout<<"avionetas esparcen un mensaje: Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn. Te parece similar, reaccionas\n";
                            cout<<"esas palabras han causado todo este desastre. Comienza a haber todo un cataclismo ambiental, nada parecido\n";
                            cout<<"a algo nunca antes visto. Las personas que intentan luchar por su vida contra este ser cosmico socumben a la\n";
                            cout<<"locura, comienzan a haber más habionetas con bocinas que predican ser seguidores del ser, son los seguidores\n";
                            cout<<"del sacerdote. Repentinamente, del agua sale Miller, explicando lo que ha sucedido, acabas de despertar a un ser\n";
                            cout<<"cosmico ancestral que esperaba en un sueño eterno. Tambien te revela que hay un fragmento de la piedra que tanto\n";
                            cout<<"anhelas, y está incrustrada en una de sus alas, se despide de ti, proclama que su verdadero nombre no es miller\n";
                            cout<<"Su verdadero nombre es NYARLATHOTEP...\nLuego procede a mostrarte su verdadera forma, una gran masa poliposa\n";
                            cout<<"con una larga excrecion roja, o es el lo que cree que quieres ver...\n";
                            cout<<"-------------------------------------------------------------------------------------------------------------\n\n";
                            cout<<"Decides seguirle la pista al gran moustro marino, encuentras un tronco liso a medio cortar, rompes 3/4\n";
                            cout<<"de los anillos del tronco, decides impulsarte desde una montaña y usar la corteza del tronco como\n";
                            cout<<"recorres rapidamente la playa y llegas a un pueblo habitado por personas con tres ojos, pregutas por direcciones\n";
                            cout<<"y continuas tu viaje, cerca de llegar al moustro, decides subir un molino que esta proximo a llegar \n";
                            cout<<"subes a lo más alto del molino y saltas a una de sus aspas, y te impulsas con tu propio peso para\n";
                            cout<<"aprobechar el momentum y saltas hasta la cima del molino donde esperas al gigante marino\n";
                            cout<<"el logra verte e intenta destruir el molino, aprobechas ese momento para subirte a uno de sus brazos y \n";
                            cout<<"correr a travez de el, pronto llegas a su espalda y ubicas el fragmaento de la piedra en una terminacion\n";
                            cout<<"del ala, te lanzas hacia ella y por fin la consigues, otro fragmento de la piedra filosofal\n";
                            cout<<"Pero el cara de masa tentacular logra sentirte y logra arrojarte de nuevo al mar, pronto el planeta\n";
                            cout<<"comienza a ser inestable y empieza a expulsar torres de lava, desde lo lejos logras percatarte de \n";
                            cout<<"una explosion masiva, el nucleo de la tierra explotó y el planeta con el. Estas varado en el espacio \n";
                            cout<<"sin poder respirar. Las cosas empiezan a detenerse, un punto rojo a lo lejos se comienza a acercar\n";
                            cout<<"el punto rojo se presenta a si mismo como MEFISTOFELES, y te ofrece un trato, el cual consiste en que\n";
                            cout<<"nunca haber despertado al moustro marino a cambio de tu alma\n";
                            cout<<"-------------------------------------------------------------------------------------------------------------\n\n";
                            cout<<"Qué quieres hacer??\n[1] Vender alma\t[2] No vender alma\t[3] Negociar\n";
                            cin>>op4;
                            if (op4 == 3 || op4 == 2){
                                cout<<"NO terminas de aceptar vender tu alma del todo, MEFISTOFELES, entendiendo de la clase de problema\n";
                                cout<<"en la que te acabas e meter, se pregunta si relamente hacía falta salvarte, se cuentiona a si mismo\n";
                                cout<<"encuentra la respuesta en su interior, no debe ayudarte...\nMEFISTOFELES TE HA HABANDONADO...\n";
                                cout<<"Se reanudan las cosas en el espacio tiempo , tu sangre empieza a herbir y te empiezas a sofocar por la falta\n";
                                cout<<"de oxigeno...terminas muriendo\n";
                                cout<<"sin embargo y apesar de tus malas deciciones,MEFISTOFELES te deja un regalo...intenetarlo otra vez\n";
                                continue;
                            }else if (op4 == 1){
                                cout<<"Al verte superado por la situacion, decides aceptar el trato siempre y cuando puedas conservar el fragmento\n";
                                cout<<"de la piedra filosofal...el simplemente ascepta...\n\n";
                                return true;
                            }else{
                                cout<<"Opcion no valida\n";
                            }
                            break;
                        case 2:
                            //no recita la sagrada frase
                            cout<<"Te niegas a hacer lo que te pide, no quieres formar parte de ningun rito extraño, ni nada por el estilo\n";
                            cout<<"pero las salidas se cierran y queda solamente la luz de Miller, reflejando el atril de oro decides desafiar\n";
                            cout<<"a miller, él se empieza a reir, desconcertado levantas la mirada y logras finalmente verlo, un mounstro de\n";
                            cout<<"contornos vagamente antropoides, pero con una cabeza de pulpo cuyo rostro es una masa de tentaculos,\n";
                            cout<<"un cuerpo escamoso que sugiere cierta elasticidad, cuatro extremidades dotadas de garras enormes y un\n";
                            cout<<"par de alas largas y estrechas en la espalda....\n";
                            cout<<"Haces contacto visual con el y ....\n";
                            cout<<"sales de la habitación con la mirada viendo la nada, llegas al centro de la estacion que conecta al nodo \n";
                            cout<<"central, en medio del todo, te quitas los ojos, caes de rodillas y mueres...\n";
                            cout<<"tu ecuentro con el ser ancestral te ha llevado a la locura...\n";
                            return false;
                            break;
                        case 3:
                            //intenta escapar
                            cout<<"Te ves superado por la situacion, empiezas a perder la cabeza...empiezas a escuhar voces susurrandote\n";
                            cout<<"que debes recitar la sagrada frase, entras en desesperación, tu pupilas se comienzan a dilatar, y \n";
                            cout<<"decides alzar la mirada, y logras verlo finalmente...logras quedar anonadado por un mounstro de \n";
                            cout<<"contornos vagamente antropoides, pero con una cabeza de pulpo cuyo rostro es una masa de tentaculos,\n";
                            cout<<"un cuerpo escamoso que sugiere cierta elasticidad, cuatro extremidades dotadas de garras enormes y un\n";
                            cout<<"par de alas largas y estrechas en la espalda....\n";
                            cout<<"Haces contacto visual con el y ....\n";
                            cout<<"sales de la habitación con la mirada viendo la nada, llegas al centro de la estacion que conecta al nodo \n";
                            cout<<"central, en medio del todo, te quitas los ojos, caes de rodillas y mueres...\n";
                            cout<<"tu ecuentro con el ser ancestral te ha llevado a la locura...\n";
                            return false;
                            break;
                        default:
                            cout<<"Opcion no valida\nRECITA LA SAGRADA FRASE....\n";
                            break;
                        }
                    }
                    break;
                case 3:
                    //Sacrificar un corazon
                    cout<<"Los ZORA, no hacen negocios con la comida, te dasafian a una batalla\n";
                    if (batallaPorTurnos(personaje,"Zora dosil",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                        cout<<"Pueden ver tu determinacion pero no te dejaran pasar hasta que les des solo uno de tus corazones...\n";
                        cout<<"renegado, les dan uno de tus corazones\n";
                        corazones--;
                        cout<<"Corazones actuales: "<<corazones<<endl;
                    }else{
                        cout<<"Despues de intentar salvar tu vida, los Zora ven algo en ti, algo que les recuerda a ellos, lo toman uno de tus corazones\n";
                        cout<<"y te dejan seguir...\n";
                        corazones--;
                        cout<<"Corazones actuales: "<<corazones<<endl;
                    }
                    cout<<"-------------------------------------------------------------------------------------------------------------\n\n";
                    cout<<"Despues de evirar ser comido, por una simple forma extraña de una sensibilidad alianada entre seres\n";
                    cout<<"continuas bajando, pues es todo lo que queda, tu cuerpo se acontumbra al lento procesoce del cambio de \n";
                    cout<<"presion atmosferico, la luz empieza a hacerse más escasa, el oceano no solo no parece tener fin, tambie es una\n";
                    cout<<"exprecion pura de profundidad. A pesar de lo poco que se conoce de los Zora, es bien sabido que la cuspide de\n";
                    cout<<"su creación fue la metropolis llamada Raputure, un lugar lleno de los grandes misterios pues no mucha gente se\n";
                    cout<<"ha atrevido a llegar tan lejos, se dice que fue contruida por encima de los viejos restos de la ATLANTIDA y \n";
                    cout<<"para hacer aún más seguro el lugar, lo cubrieron debajo de un domo trasparente.\n";
                    cout<<"LLegas al fondo del oceano y encuentras una red de tubos de trasporte, aparentemente la manera de moverse es \n";
                    cout<<"dejando que la tecnologia lo haga, ademas, hay una cabina de abordaje que permite subir a cualquier especie marina.\n";
                    cout<<"Al llegar a la cabina de abordaje te percatas que el capitan ispecciona el pase para abordar, encuentras una especie\n";
                    cout<<"de taquilla, y procedes a coprar un boleto, sin embargo te hacen una comision por el cambio de moneda, y todavía\n";
                    cout<<"te hacen dejar una propina al sistema de cambios automaticos, estas frustrado, pero tienes tu boleto, haces fila\n";
                    cout<<"para abordar el trasporte, el capitan que supervisa los boletos te ve de pies a cabeza, es facil reconocer que\n";
                    cout<<"no eres un animal marino, sin embargo un neo delfin arto de esperar en la fila, pide que se apresuren\n";
                    cout<<"el capitan te deja pasar aparentemente. Entras al vagon, una vez lleno, empieza a moverse a muy alta velocidad,los\n ";
                    cout<<"los tubos parecen estar echos de una especie de fibrra de vidrio unida uno con otro a travez de un superconductor\n";
                    cout<<"capas de manejar los campos delectromagneticos de los vagones, y todo el tubo está cubierto por fibra de carbono\n";
                    cout<<"transparente, todo el sitema de tubos funciona por nodos, como si fueran grafos.\n ";
                    cout<<"Una vez llegando a la gran central (o gran nodo), puedes ver como se abre ante ti un grupo armado de tiburones blancos\n";
                    cout<<"el dominio de los Zora no solo se remonta a su propia existencia, si no al de muchos seres marinos\n";
                    cout<<"empiezas a correr pero todo parece ser muy confuso, empiezas a marearte, tal vez sea un efecto secundario de las\n";
                    cout<<"semillas del hermitaño, finalmente vuelves a ti y ahí junto con los tiburones blanco se presenta ante ti el gran\n";
                    cout<<"KITO CORLEONE, un gran tiburon blanco mutado por los plasmidos, pero que en realidad no es si no más que otra\n";
                    cout<<"marioneta de las grandes mentes Zora, KITO, te hace unas preguntas pero no sabes lo que dice, y al nunca haber\n";
                    cout<<"situación similar, no hay una especie de protocolo por lo que deciden llevarte ante el Rey del Todo para que decida\n";
                    cout<<"qué hacer contigo, usan una bolsa de pseaudo plastico biodegradable a vase de algas para taparte la cara y no\n";
                    cout<<"puedas ver el camino...\n";
                    cout<<"vuelves a ser despertado de una manera ruda, uno de los tiburones de KITO te azotado la cara contra una especie\n";
                    cout<<"de libro en un atril de oro. Lo poco que puedes distinguir es que la pagina de ese libro dice en varios idiomas\n";
                    cout<<"incluyendo el humano: NO LO MIRES A LOS OJOS. Una voz o más bien un sonido tan grave que retumba por todo \n";
                    cout<<"comienza a decir algo, porque parece tener un ritmo, parece hablar en una lengua tan antigua arena del mar\n";
                    cout<<"todo esta oscuro, no puedes ver de donde vienen esos sonidos, pero logras escuchar una cadena acercandose...\n";
                    cout<<"entre las oscuridades más profundas, puedes lograr ver una luz de una vela marina, siguie acercandose hasta que \n";
                    cout<<"depues de ese basto sonido de cadenas se puede entrever un ser encapuchado con una tunica roja, te ve, y lo sabe\n";
                    cout<<"sabe que este día llegaría...\n\n";
                    cout<<"MILLER: Sabes como es esto, no??. Bueno primero es decir que este lugar realmente no es Rapture, si no que el \n";
                    cout<<"\tverdadero nombre  es R'lyeh y has viajado tanto que has llegado al oceano Pacífico. Este momento es realmente sublime\n";
                    cout<<"\tlos millones de años han pasado y por fin, solo tines que decir las palabras sagradas y todo estára listo\n";
                    cout<<"\t¿Qué pasa, no las conoces a caso?¿Cómo es eso posible?, espera, no sabes lo que está ocurriendo cierto???\n";
                    cout<<"\tjajajajajajajajajajajajajajajajajajajajajajajajaja, esto es en serio fabuloso, tan kafkiano, veras, estas apunto\n";
                    cout<<"\tde traer paz al mundo...(está mintiendo), todo lo que necesitas saber está en ese libro, serías tan amable de\n";
                    cout<<"\tcambiar de pagina??...\n\n";
                    cout<<"Cambias la pagina y ves un mismo texto escrito en los diferentes lenguajes, una frase que se repite y se repite: \n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"PH'NGLUI MGLW'NAFH CTHULHU R'LYEH WGAH'NAGL FHTAGN...\n";
                    cout<<"-------------------------------------------------------------------------------------------------------------\n\n";
                    while (true){
                        cout<<"QUE QUIERES HACER??\n[1] RECITAR LA SAGRADA FRASE\t[2] NO RECITAR LA SAGRADA FRASE\t[3] Intentar escapar\n\n";
                        cin>>op3;
                        switch (op3){
                        case 1:
                            //recita la sagrada frase
                            cout<<"Recuerdas las palabres de aquella gaviota al inicio de tu aventura, y decides recitar las palabras sagradas\n";
                            cout<<"sin saber exactamente lo que significa ni lo que está pasando, prefieres no ver a nadie a los ojos\n";
                            cout<<"en cuanto comienzas, el tiempo parece detenerse, y todo el oceano comienza a herbir, los suelos se agritan\n";
                            cout<<"y sale lava de las fragmentaciones, empiezas a sentir que flotas, cada vez más y más arriba en un estado de\n";
                            cout<<"trance profundo repitiendo las frases sagradas, y de repente, vuelves a ti, estas en la playa, a mitad de una\n";
                            cout<<"tormenta de relampagos y tsunamis, en las aguas de los mares comiezan a salir seres marinos sin vida,\n";
                            cout<<"incluyendo algunos Zora, y al fondo ves a un monstruo de contornos vagamente antropoides, pero con una cabeza\n";
                            cout<<"de pulpo cuyo rostro es una masa de tentaculos, un cuerpo escamoso que sugiere cierta elasticidad, cuatro\n";
                            cout<<"extremidades dotadas de garras enormes y un par de alas largas y estrechas en la espalda...\n";
                            cout<<"el caos viviente ha despertado y viene a reclamar lo que es suyo, el planeta, el gran ser aterra a todos\n";
                            cout<<"avionetas esparcen un mensaje: Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn. Te parece similar, reaccionas\n";
                            cout<<"esas palabras han causado todo este desastre. Comienza a haber todo un cataclismo ambiental, nada parecido\n";
                            cout<<"a algo nunca antes visto. Las personas que intentan luchar por su vida contra este ser cosmico socumben a la\n";
                            cout<<"locura, comienzan a haber más habionetas con bocinas que predican ser seguidores del ser, son los seguidores\n";
                            cout<<"del sacerdote. Repentinamente, del agua sale Miller, explicando lo que ha sucedido, acabas de despertar a un ser\n";
                            cout<<"cosmico ancestral que esperaba en un sueño eterno. Tambien te revela que hay un fragmento de la piedra que tanto\n";
                            cout<<"anhelas, y está incrustrada en una de sus alas, se despide de ti, proclama que su verdadero nombre no es miller\n";
                            cout<<"Su verdadero nombre es NYARLATHOTEP...\nLuego procede a mostrarte su verdadera forma, una gran masa poliposa\n";
                            cout<<"con una larga excrecion roja, o es el lo que cree que quieres ver...\n";
                            cout<<"-------------------------------------------------------------------------------------------------------------\n\n";
                            cout<<"Decides seguirle la pista al gran moustro marino, encuentras un tronco liso a medio cortar, rompes 3/4\n";
                            cout<<"de los anillos del tronco, decides impulsarte desde una montaña y usar la corteza del tronco como\n";
                            cout<<"recorres rapidamente la playa y llegas a un pueblo habitado por personas con tres ojos, pregutas por direcciones\n";
                            cout<<"y continuas tu viaje, cerca de llegar al moustro, decides subir un molino que esta proximo a llegar \n";
                            cout<<"subes a lo más alto del molino y saltas a una de sus aspas, y te impulsas con tu propio peso para\n";
                            cout<<"aprobechar el momentum y saltas hasta la cima del molino donde esperas al gigante marino\n";
                            cout<<"el logra verte e intenta destruir el molino, aprobechas ese momento para subirte a uno de sus brazos y \n";
                            cout<<"correr a travez de el, pronto llegas a su espalda y ubicas el fragmaento de la piedra en una terminacion\n";
                            cout<<"del ala, te lanzas hacia ella y por fin la consigues, otro fragmento de la piedra filosofal\n";
                            cout<<"Pero el cara de masa tentacular logra sentirte y logra arrojarte de nuevo al mar, pronto el planeta\n";
                            cout<<"comienza a ser inestable y empieza a expulsar torres de lava, desde lo lejos logras percatarte de \n";
                            cout<<"una explosion masiva, el nucleo de la tierra explotó y el planeta con el. Estas varado en el espacio \n";
                            cout<<"sin poder respirar. Las cosas empiezan a detenerse, un punto rojo a lo lejos se comienza a acercar\n";
                            cout<<"el punto rojo se presenta a si mismo como MEFISTOFELES, y te ofrece un trato, el cual consiste en que\n";
                            cout<<"nunca haber despertado al moustro marino a cambio de tu alma\n";
                            cout<<"-------------------------------------------------------------------------------------------------------------\n\n";
                            cout<<"Qué quieres hacer??\n[1] Vender alma\t[2] No vender alma\t[3] Negociar\n";
                            cin>>op4;
                            if (op4 == 3 || op4 == 2){
                                cout<<"NO terminas de aceptar vender tu alma del todo, MEFISTOFELES, entendiendo de la clase de problema\n";
                                cout<<"en la que te acabas e meter, se pregunta si relamente hacía falta salvarte, se cuentiona a si mismo\n";
                                cout<<"encuentra la respuesta en su interior, no debe ayudarte...\nMEFISTOFELES TE HA HABANDONADO...\n";
                                cout<<"Se reanudan las cosas en el espacio tiempo , tu sangre empieza a herbir y te empiezas a sofocar por la falta\n";
                                cout<<"de oxigeno...terminas muriendo\n";
                                cout<<"sin embargo y apesar de tus malas deciciones,MEFISTOFELES te deja un regalo...intenetarlo otra vez\n";
                                continue;
                            }else if (op4 == 1){
                                cout<<"Al verte superado por la situacion, decides aceptar el trato siempre y cuando puedas conservar el fragmento\n";
                                cout<<"de la piedra filosofal...el simplemente ascepta...\n\n";
                                return true;
                            }else{
                                cout<<"Opcion no valida\n";
                            }
                            break;
                        case 2:
                            //no recita la sagrada frase
                            cout<<"Te niegas a hacer lo que te pide, no quieres formar parte de ningun rito extraño, ni nada por el estilo\n";
                            cout<<"pero las salidas se cierran y queda solamente la luz de Miller, reflejando el atril de oro decides desafiar\n";
                            cout<<"a miller, él se empieza a reir, desconcertado levantas la mirada y logras finalmente verlo, un mounstro de\n";
                            cout<<"contornos vagamente antropoides, pero con una cabeza de pulpo cuyo rostro es una masa de tentaculos,\n";
                            cout<<"un cuerpo escamoso que sugiere cierta elasticidad, cuatro extremidades dotadas de garras enormes y un\n";
                            cout<<"par de alas largas y estrechas en la espalda....\n";
                            cout<<"Haces contacto visual con el y ....\n";
                            cout<<"sales de la habitación con la mirada viendo la nada, llegas al centro de la estacion que conecta al nodo \n";
                            cout<<"central, en medio del todo, te quitas los ojos, caes de rodillas y mueres...\n";
                            cout<<"tu ecuentro con el ser ancestral te ha llevado a la locura...\n";
                            return false;
                            break;
                        case 3:
                            //intenta escapar
                            cout<<"Te ves superado por la situacion, empiezas a perder la cabeza...empiezas a escuhar voces susurrandote\n";
                            cout<<"que debes recitar la sagrada frase, entras en desesperación, tu pupilas se comienzan a dilatar, y \n";
                            cout<<"decides alzar la mirada, y logras verlo finalmente...logras quedar anonadado por un mounstro de \n";
                            cout<<"contornos vagamente antropoides, pero con una cabeza de pulpo cuyo rostro es una masa de tentaculos,\n";
                            cout<<"un cuerpo escamoso que sugiere cierta elasticidad, cuatro extremidades dotadas de garras enormes y un\n";
                            cout<<"par de alas largas y estrechas en la espalda....\n";
                            cout<<"Haces contacto visual con el y ....\n";
                            cout<<"sales de la habitación con la mirada viendo la nada, llegas al centro de la estacion que conecta al nodo \n";
                            cout<<"central, en medio del todo, te quitas los ojos, caes de rodillas y mueres...\n";
                            cout<<"tu ecuentro con el ser ancestral te ha llevado a la locura...\n";
                            return false;
                            break;
                        default:
                            cout<<"Opcion no valida\nRECITA LA SAGRADA FRASE....\n";
                            break;
                        }
                    }
                    break;
                default:
                    cout<<"Opcion no valida";
                    break;
                }
            }
        }else if (op1 == 2){
            //NO comer la semilla del hermitaño
            cout<<"-------------------------------------------------------------------------------------------------------------\n";
            cout<<"Has decidio no comer la semilla del hermitaño...algo te dió una mala corazonada (triple corazonada),          \n";
            cout<<"te mantienes alerta, sobre la gaviota, puedes ver uno de sus ojos brillar demaciado y te preguntas si los Zora\n";
            cout<<"han empezado a buscar la melanina en otros animales...tal vez ese ojo de la GAVIOTA, no sea real...           \n";
            cout<<"Como sea, decides ignorar a la GAVIOTA e ir avanzando con direccion hacia el sol. Pasan las horas y al parecer\n";
            cout<<"empieza a oscurecer, de repente tres moustros Zora te rodean y empiezan a acechar...                         \n";
            while (true){
                cout<<"Uno de ellos te empieza a oler... al parecer es uno de los PIGMENTARIOS, un grupo de cazadores Zora        \n";
                cout<<"Otro de ellos saca algo brilloso de su garganta, en un abrir y cerrar de ojos, te ha inyectado un plasmido \n";
                cout<<"el plasmido empieza a envenenar tu sangre y ha empezando a coagularla...aun así no te das por vencido y...\n";
                cout<<"Que te gustaría hacer??\n[1] Pelear\t[2] Intentar escapar\t[3] Sacrificar un corazon\n\n";
                cout<<"-------------------------------------------------------------------------------------------------------------\n";
                cin>>op2;
                switch (op2){
                case 1:
                    //Pelear
                    cout<<"-------------------------------------------------------------------------------------------------------------\n";
                    cout<<"Determinado, decides pelear por tu vida...\n";
                    if (batallaPorTurnos(personaje,"PIGMENTARIO 1",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                        cout<<"Has ganado la primera batalla, pero aun quedan dos PIGMENTARIOS...y la pelea  continua\n";
                        if (batallaPorTurnos(personaje,"PIGMENTARIO 2",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                            cout<<"Empiezas a sentir como tu pierna empieza a sentirse extraña, acaso esto será una trombosis venosa profunda?\n";
                            if(batallaPorTurnos(personaje,"PIGMENTARIO 3",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                                cout<<"Empiezas a sentirte un poco mariado apesar de haber derrotado a los cazadores PIGMENTARIOS\n";
                                cout<<"la falta de oxigeno empieza a hacerse severa, la desesperacion empieza a apoderarse de ti\n";
                                cout<<"...comiezas a preguntarte si realmente era necesario pelear...\n";
                                cout<<"Los corazones pueden salvarte de peleas, pero las embolias pulmonares y la trombosis venosa profunda son inevitables\n";
                                cout<<"y es aqui donde "<<personaje<<" despues de tanto sufrimiento, muere\n";
                                cout<<"Por la posicion en la que caiste, tu cuerpo quedo flotando y la luna llena en todo su esplandor...te habla...\n";
                                cout<<"-------------------------------------------------------------------------------------------------------------\n\n";
                                cout<<"Continuar luchando??\n[1] Si\t[2] No\n";
                                cin>>op3;
                                if (op3 == 1){
                                    continue;
                                }else{
                                    break;
                                }
                            }else{
                                cout<<"Las dos batallas anteriores te han deteriorado demaciado...empiezas a sentir un dolor en el pecho\n";
                                cout<<"estas presionando el lado izquierdo del pecho pero el dolor no desaparece, empiezas a escuchar el ritmo\n";
                                cout<<"cardiaco de tus corazones, y los latidos se empiezan a acelerar aun más, uno de tus corazones empieza a seguir otro ritmo\n";
                                cout<<"no lo puedes creer, tu vida pasa por tus ojos y finalmente mueres...\n";
                                cout<<"Si es de ayuda, el PIGMENTARIO restante se llevó tu cuerpo y llevo la cena a la mesa de su familia...\n";
                                return false;
                            }
                        }else{
                            cout<<"Tu cuerpo esta siendo llevado al limite, no sabes si sobreviviras...en pocos minutos todo terminará...\n";
                            cout<<"los PIGMENTARIOS no te esperan por siempre, decididos, ambos se abalanzan contra ti, te sacan los ojos\n";
                            cout<<"y te arrancan tus corazones...simplemente mueres...\n";
                            return false;
                        }
                    }else{
                        cout<<"Has perdido, no tienes más esperanzas, te resignas a seguir, la ansiedad se apodera de ti, sacas tu navaja y ...\n";
                        cout<<"te has herido de gravedad, los PIGMENTARIOS se abalanzan contra ti, te empiezan a devorar vivo...finalmente...mueres\n";
                        return false;
                    }
                    
                    break;
                case 2:
                    //Escapar
                    cout<<"Intentas escapar...reconoces que la situacion te supera, desesperado empiezas a nadar en la direccion contraria pero\n";
                    cout<<"los PIGMENTARIOS no van a dejar que su comida simplemente escape, por lo que empiezan a perseguirte salvajemente\n";
                    cout<<"uno de ellos saca una soga con un arpon amarrado, lo lanza y te lo ha clavado, empieza a jalar, y con uno de sus tentaculos\n";
                    cout<<"empieza a realizar una lobotomia, llegando al lobulo frontal y moviendo sensiblemente la punta del tentaculo provoca que\n";
                    cout<<"la parte motora deje de responder y tranquilamete te llevan con ellos para desollarte vivo...\n";
                    return false;
                    break;
                case 3:
                    //Sacrificar un corazon
                    cout<<"Cortas una parte de ti para sacrificar uno de tus corazones, sin embargo, eso no los deja satisfechos, por lo que\n";
                    cout<<"un de los PIGMENTARIOS te apresa con una especie de alga muy resistente, dejando te inmovil, pronto otro de ellos\n";
                    cout<<"abre un orifico por donde sale una larva verde y muy gelatinosa y la inserta en uno de tus corazones, ponen otro plasmido\n";
                    cout<<"adormecedor y te llevan al fondo del oceano en donde la larva al crecer, consumirá cada uno de tus corazones en busqueda\n";
                    cout<<"de melanina, una vez lo suficientemente grande, sale de tu pecho rompiendo todo en su paso y empezando a llamar a sus padres\n";
                    cout<<"has muerto...\n";
                    return false;
                    break;
                default:
                    cout<<"Opcion no valida\n";
                    break;
                }
            }
        }else if (op1 == 3){
            //Sospechar de la gabiota
            cout<<"Consideras la oferta pero, no te sientes muy seguro con sus intentciones, reconsideras tus opciones\n";
            cout<<"pero no es suficiente, decides revelarle tus pensamientos...GAVIOTA no está muy contenta con tus comentarios\n";
            cout<<"se ha marchado pero no te preocupas, comienzas a apresurarte. Antes de sarpar, te preparas con un arpon\n";
            cout<<"-------------------------------------------------------------------------------------------------------------\n";
            while (true){
                cout<<"Pronto llegas a la mitad del golfo, todo parece tranquilo hasta que todo el mar se empieza a inclinar\n";
                cout<<"Un sonido ensordesedor se apodera de toda tu audicion, y en segundos eres capturador por una gran boca\n";
                cout<<"al parecer el espermaceti de alguien no funciona con regularidad, toda el agua que entró junto contigo\n";
                cout<<"fluye a travez del esofago y choca con la pared del estomago del colosal animal, a pesar de que el ser fue modificado\n";
                cout<<"con plasmidos, para el no fue un gran cambio a su hambiente, ahora al ser un mejor depredador tambien mejoró sus organos\n";
                cout<<"logrando producir enzimas con un mayor grado de complejidad logrando así devorar grandes cantidades\n";
                cout<<"cantidades de comida en poco tiempo...\n";
                cout<<"El barco se roto por completo, tendras que nadar. Te percatas sobre una extraña masa gelatinosa indescriptible\n";
                cout<<"logras ver un pequeño ritmo en la masa negra, puedes ver como consumen al cachalote poco a poco, te has\n";
                cout<<"dado cuenta de lo que realmente esta pasando, el cachalote que te secuestró esta siendo manipulado por un parasito\n";
                cout<<"Decides nadar en direccion de la boca del animal pero la fuerza centrifuga con la que jala es demaciada para nadar \n";
                cout<<"contra ella, por lo que decides ir seguir a travez de los intentinos, despues de los plasmidos, el cachalote empezó\n";
                cout<<"a producir aun más ambar gris, despues de caminar por un rato encuentras cuerpos de calamares gigantes a medio devorar\n";
                cout<<"pero escuchas un sonido lejano que llama tu atención, lo sigues y resulta ser una extraña combinacion de masa parasitoide\n";
                cout<<"y un calamar gigante, agobiado, intentas salir corriendo pero la mente colmena del paracito pronto se percata\n";
                cout<<"de otro ser vivo, te has topado directamente contra tres calamares paracitados...\n";
                cout<<"-------------------------------------------------------------------------------------------------------------\n";
                cout<<"Que te gustaría hacer??\n[1] Pelear\t[2] Intentar escapar\t[3] Sacrificar un corazon\n\n";
                cin>>op2;
                switch (op2){
                case 1:
                    //Pelear
                    cout<<"Luces determinado, dando cada paso con seguridad y decides pelear.\n";
                    if (batallaPorTurnos(personaje,"CALAMAR PARASITADO 1",dificultad,pociones, pocionesMax,escudos,ataqueMortal)){
                        cout<<"Has logrado vencer al primer CALAMAR PARASITADO, pero no es suficiente, aqui viene otro\n";
                        if(batallaPorTurnos(personaje,"CALAMAR PARASITADO 2",dificultad, pociones,pocionesMax,escudos,ataqueMortal)){
                            cout<<"Estas derrotando a cada uno de ellos, pero aún no encuetras forma de salir del los intestinos del cachalote\n";
                            if(batallaPorTurnos(personaje,"CALAMAR PARASITADO 3",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                                cout<<"Tras derrotar a cada uno de ellos, el parasito decide unirse en una sola cosa, estas a punto de enfrentar al parasito\n";
                                cout<<"te mira fijamente y despliega su verdaro ser, una aberracion alienigena de pura maldad\n";
                                if (batallaPorTurnos(personaje,"PARASITO DEVORADOR DE MUNDOS",dificultad,pociones,pocionesMax,escudos,ataqueMortal)){
                                    cout<<"Una vez derrotado al parasito, decides seguir el camino de los intentinos...\n";
                                    cout<<"tras una grotesca expulcion, logra salir del cachalote, sin embargo, la desidad osea de tu cuerpo\n";
                                    cout<<"y tus organos no soportan el cambio atmosferico tan brusco e implosionas...\n";
                                    cout<<"Has muerto...";
                                    return false;
                                }else{
                                    cout<<"No has podido derrotar a la cosa aberrante que se returece por si misma\n";
                                    cout<<"Despues de forcejear un rato el parasito te arranca la cabeza con dos psedudo extremidades\n";
                                    cout<<"despues de acabar contigo, se expande aun más y logra controlar por completo al cachalote\n";
                                    cout<<"el cachalote empieza a nadar y nadar hasta llegar al fin del de su territorio, en donde una falsa\n";
                                    cout<<"orca se termina enganchando de el y trasmitiendole el parasito en a la falsa orca\n";
                                    cout<<"pronto se empieza a apoderar de más seres marinos provocando una epidemia, los Zora al percatarse\n";
                                    cout<<"ponen a todos los seres marinos en cuarentena...tras dos años de ella, salen pero al no haber encontrado\n";
                                    cout<<"una cura estable, el panico de los demas seres marinos empieza a hacerse notar\n";
                                    cout<<"provocando que empiecen a matar a los seres infectados, encerrandolos en supercontenedores\n";
                                    cout<<"con bombas de hiperimplocion...acabando con una gran parte de la diversidad marina y un duro golpe para el\n";
                                    cout<<"ecosistema marino\n";
                                    return false;
                                }   
                            }else{
                                cout<<"derrotado, te hayas en el suelo con un gran panico\n";
                                cout<<"el CALAMAR PAARASITADO, usa su pseudo extremidad y te atravieza la cabeza...\n";
                                cout<<"Has muerto...\n";
                                return false;
                            }
                        }else{
                            cout<<"derrotado, te hayas en el suelo con un gran panico\n";
                                cout<<"el CALAMAR PAARASITADO, usa su pseudo extremidad y te atravieza la cabeza...\n";
                                cout<<"Has muerto...\n";
                                return false;
                        }
                    }else{
                        cout<<"derrotado, te hayas en el suelo con un gran panico\n";
                                cout<<"el CALAMAR PAARASITADO, usa su pseudo extremidad y te atravieza la cabeza...\n";
                                cout<<"Has muerto...\n";
                                return false;
                    }
                    
                    break;
                case 2:
                    //Intentar escapar
                    cout<<"La desesperacion se apodera de ti, no sabes como reaccionar, pronto el paracito ha cerrado un segmento de intensino\n";
                    cout<<"se empieza a estirar a lo largo de esos 10 metros rodeando las paredes intestinales, haciendo sobresalir\n";
                    cout<<"lo que parece un tentaculo especial, logras cortar dos de los tentaculos del calamar pero no es suficiente, la masa\n";
                    cout<<"parasitaria empieza a crecer por detras de ti, sometiendote a travez de  inmovilizar tus extremidades, con el\n";
                    cout<<"tentaculo especial logra acariciar tu cara y logra introducirlo por uno de tus oidos, introduciendo un poco de\n";
                    cout<<"una oscura masa parasitaria de calamar en el laberinto del oido, ropiendo el utrículo y saculo en el proceso\n";
                    cout<<"probocando una desorientación fatal, sin embargo, las enzimas del cachalote son más fuertes que el paracito y lo empiezan\n";
                    cout<<"a descomponer pero el paracito se cubre tras una gran montaña de ambar gris soltandote en el proceso y dejandote\n";
                    cout<<"desorientado, las enzimas son más poderosas pues han sido modificadas por los plasmidos, logrando así un produccion\n";
                    cout<<"de amoniaco en todo el intenstino consecuentemente una quemadura quimica en la piel, garganta y los pulmones...\n";
                    cout<<"Has muerto...\n";
                    return false;
                    break;
                case 3:
                    //Sacrificar un corazon
                    cout<<"Decides practicar la sumicion entregandole uno de tus corazones, no se dejan asombrar, dos de ellos te atrapan con sus\n";
                    cout<<"ventosas, la precion de sus ventosas hacen que te arrranquen por partes la piel mostrando la capa subcutanea por cada ventosa,\n";
                    cout<<"cortadon las puntas de los nervios en el proceso y a travez de los nervios abiertos el parasito oscuro viaja y llega\n";
                    cout<<"al cerebro. Apoderandose de tu cuerpo, tus sentidos y funcion motora...\n";
                    cout<<"Eventualmente las encimas del cachalote terminan degradando al paracito junto contigo. Al día siguiente, el cachalote\n";
                    cout<<"llega a su trabajo en nuevo nuevo león, entra a las oficinas, se dirije a su cubiculo, toma 6 llamadas en 10 minutos\n";
                    cout<<"y sigue así durante todo su día, regresa a su casa en trasporte publico y a dos cuadras de su casa lo asaltan\n";
                    cout<<"llega a su casa donde lo espera su familia y llega a recostarse al sillon, ese día era quincena pero no le pagaron\n";
                    cout<<"es la tercera vez que le dicen eso, va su refigerador y toma una lata de extractor de Carpa Crucian (pes que produce alcohol)\n";
                    cout<<"despues de la cena de calamares bebe, decide tomar un baño de agua termal, y es ahí donde crea se le ocurre crear un\n";
                    cout<<"sindicato corrupto. Despues de tres años, ese cachalote alguna vez parasitado, ya no es el mismo, el no está en peligro\n";
                    cout<<"él es el peligro.\n\n";
                    cout<<"Has muerto\n";
                    return false;
                    break;
                default:
                    cout<<"Opcion no valida";
                    break;
                }
            }
        }else{
            cout<<"Opcion no valida\n";
        }
        
        
        
    }
    
    
}

//Ruinas del Abismo
bool RuinasDelAbismo(string personaje, int dificultad, int pociones, int pocionesMax, int escudos, int ataqueMortal){
    int fichas = 0;
    int op,op1,op2,op3,op4;
    cout<<"-----------------------------------------------------------------------------------------------\n";
    cout<<"DENTRO DE: ----R U I N A S  D E L  A B I S M O \n\n";
    cout<<"-----------------------------------------------------------------------------------------------\n";
    cout<<"A pasar de las adversidades de la situación consideras que debes terminar lo que empezaste\n";
    cout<<"estas decidido.\n"<<personaje<<" comienza a bajar unas escaleras con letreros neon en las paredes\n";
    cout<<"mostrando, bebidas, alguna especie de alienigena de caracter femenino, pero sexualizada\n";
    cout<<"mientras baja se percata de los sonidos de los brindis, las risas y la musica, algo equivalente a los\n";
    cout<<"clasicos del jazz de los 20s, al final de estas escaleras, encuentra una puerta roja, detras de ella\n";
    cout<<"encuentra un ambiente bastante moderno, lleno de estimulos para el cerebro, como para nunca irse\n";
    cout<<"sin embargo, "<<personaje<<" recuerda su mision y retoma la valentía necesaria para seguir, ademas\n";
    cout<<"en estos días no es facil conseguir conseguir esas 300 monedas, antes, con eso podrías comprarte\n";
    cout<<"una casa, una buena carreta con varios caballos e incluso poder mantener una clasica familia\n";
    cout<<"con una linda esposa y dos bellos niños. Pero parece que las cosas cambian muy rapido, ahora no\n";
    cout<<"tienes ni la certeza si podras jubilarte algun día.\n";
    cout<<"LLegas a la barra en donde pides un martini seco...\n\n";
    cout<<"RAMONA : Primera vez que vienes, cierto?? La gente no suele venir preparada para matar a Dios, en fin...\n\n";
    cout<<"RAMONA agrega los hielos al shaker y los deja reposar por algunos segundos. Agrega el vermouth seco y \n";
    cout<<"mescla con la cuchara bailarina para perfumar los hielos. Coloca el colador oruga y desecha el exeso de\n";
    cout<<"vermouth.\n\n";
    cout<<"RAMONA: todo el mundo a veces necesita realajarse un poco sabes, simplemente la gente llega del trabajo\n";
    cout<<"\ty lo unico que quiere hacer es sentir lo que quiere sentir, ver lo que quiere ver y expresar lo que\n";
    cout<<"\ttenga que decir, no lo crees?? Bueno, hace poco se empezó a hacer más famoso este lugar desde que\n";
    cout<<"\tlos seguidores de ese cara de papa empezaron a tener reuniones supuestamente secretas, que realmente\n";
    cout<<"\tlo unico secreto es cuanto dinero han de hacer estafando a todas esas pobres almas victimas de la lepra\n";
    cout<<"\tresignadas a usar medicamentos a base de carbotano, miel de orontox y limon. Muy triste la situación,no??\n\n";
    cout<<"RAMONA desecha el hielo de la copa martinera. Vierte ginebra en el shaker y mezcla nuevamente con la cuchara\n";
    cout<<"bailarina durante 15 segundos, lo tapa con el colador oruga y pasa el coctel a travez del colador fino para\n";
    cout<<"verterlo en la copa .\n\n";
    cout<<"RAMONA: como sea, los sujetos aquellos no son más que un monton de viles carroñeros esperando otra presa\n";
    cout<<"\tmuerda el ansuelo, ahora que tienen un fragmento de la dichosa piedra filosofal esa se sienten los dueños\n";
    cout<<"\tdel lugar, y los pobres ilusos no dejan de intentar ganarle ese fragmento a base de apuestas super arriesgadas\n";
    cout<<"\thay veces en las que pienso en que pasaría si todos lo framentos de esa cosa se unieran, tal vez explote\n";
    cout<<"\tla realidad misma, o no lo sé, jaja.\n\n";
    cout<<"RAMONA inserta las aceitunas en ambos extremos de un palillo y lo sumerge el el martini\n\n";
    cout<<"RAMONA: Parece ser que no dejas de verlos jugar, si planeas jugar contra ellos debes de tener cuidado luego las\n";
    cout<<"\treglas se ponen muy locas, lo peor es que la chica de la limpieza termina usando todo el agua oxigenada para\n";
    cout<<"\tlimpiar las manchas de sangre y los restos se los suelen dar a los perros. Espero no haberte asustado jaja\n";
    cout<<"\ttengo que atender a alguien más, disfruta tu bebida JAMES BOND...\n";
    cout<<"-----------------------------------------------------------------------------------------------\n";
    cout<<"Un sujeto junto a ti te comienza a mirar y te dirige la palabra...tiene un acento gringo muy marcado\n\n";
    cout<<"SAUL BADMAN:Hey que tal, estar en la barra aveces puede parecer una buena idea para socializar más, no lo crees?\n";
    cout<<"\tmi nombre es SAUL y si necesitas un lawyer, just call me, btw. Como veras, todo este lugar no si no más que\n";
    cout<<"\totra trampa para aquellos despistados, pero tú pareces diferente, sabes, creo que me agradas, btw, sabías\n";
    cout<<"\tque este lugar funciona con fichas?? Así es, el dinero real solo se usa allá afuera, por lo que si quieres\n";
    cout<<"\ttener la verdadera experiencia de este lugar deberías traer algunas, ¿qué?, tinenes ninguna,don t worry\n";
    cout<<"\tsiempre soy amigo del cartel, y ellos me pueden conseguir algunas, por ahora solo tengo 3, ten\n";
    cout<<"\tdiviertete con ellas, consigue más y pagamelas despues, como me caiste tan bien solo te pediré 2 de regreso,btw\n";
    cout<<"\ten fin, enjoy the full experience. Nos veremos luego, btw. And if u necesitas algo mejor llamame, bettter call Saul\n";
    cout<<"\tbtw.\nPD. Las fichas no se pueden cambiar por dinero solo por asesinatos, una vez que aceptaste esas fichas que te\n";
    cout<<"\tdí, tambien asceptaste los términos y condiciones jaja\n";
    fichas += 3;
    cout<<"Fichas actuales: "<<fichas<<endl;
    cout<<"-----------------------------------------------------------------------------------------------\n";
    cout<<"Necesitas encontrar al culto del NECRONOMICON, pues ellos tienen el fragmento de la PIEDRA FILOSOFAL\n";
    cout<<"tal vez estén detras de aquella puerta que reza 'Solo miebros VIP' (precio 7 fichas), -vaya burocracia-\n";
    cout<<personaje<<" se percata que la unica manera de poder llegar a esa puerta es apostando...\n";
    cout<<"-----------------------------------------------------------------------------------------------\n";
    while (true){
        while (fichas > 0){
            cout<<"Llegas al cuarto de juegos, en donde te gustaría apostar??\n[1] Trivia\t [2] Piedra, Papel o tijeras \t[3] Hangman\t[4] Intentar abrir puerta VIP\n";
            cin>>op1;
            if (op1==1){
                //Trivia
            }else if (op1 == 2){
                //Piedra papel o tijeras
                cout<<"Decides jugar piedra papel o tijeras\n";
                cout<<"el arbitro indica que solo es necesario apostar una sola ficha, si ganas obtienes tres\n";
                cout<<"si pierdes te quitan dos\n";
                if (piedraPapelTijeras(dificultad,personaje,"LUDOPATA CASUAL")){
                    cout<<"Has ganado la apuest !!!...Obtienes 3 fichas más\n";
                    fichas+=3;
                    cout<<"Fichas actuales: "<<fichas<<endl;
                    cout<<"Te gustaría ir a intentar abrir la puerta VIP??\n[1] Si\t[2]No\n";
                    cin>>op;
                    if (op == 1){
                        break;//regresa a abrir la puerta VIP
                    }else{
                        cout<<"Vale, continua disfrutando de tus apuestas\n";
                        continue;
                    }
                }else{
                    cout<<"Has perdido la apuesta, pierdes 2 fichas :/\n";
                    fichas-=2;
                    cout<<"Fichas actuales: "<<fichas<<endl;
                    cout<<"Te gustaría ir a intentar abrir la puerta VIP??\n[1] Si\t[2] NO\n";
                    cin>>op;
                    if (op == 1){
                        break;//regresa a abrir la puerta VIP
                    }else{
                        cout<<"Vale, continua desfrutando de tus apuestas\n";
                        continue;
                    }
                }
            }else if (op1 == 3){
                //Hangman
                cout<<"Decides jugar al hangman, llegas al lugar y  el coordinador\n";
                cout<<"te dice que es necesario apostar una sola ficha, si ganas, obtienes dos fichas, eso es todo\n";
                if(hangman(dificultad)){
                    cout<<"Has ganado la  apuesta!!...Obienes 2 fichas más\n";
                    fichas+=2;
                    cout<<"Fichas actuales: "<<fichas<<endl;
                    cout<<"Te gustaría ir a intentar abrir la puerta VIP??\n[1] Si\t[2] NO\n";
                    cin>>op;
                    if (op == 1){
                        break;//regresa a abrir la puerta VIP
                    }else{
                        cout<<"Vale, continua disfrutando de tus apuestas\n";
                        continue;
                    }
                }else{
                    cout<<"Has perdido la apuesta, pierdes tu ficha :/\n";
                    fichas--;
                    cout<<"Fichas actuales: "<<fichas<<endl;
                    cout<<"Te gustaría ir a intentar abrir la puerta VIP??\n[1] Si\t[2] NO\n";
                    cin>>op;
                    if (op == 1){
                        break;//regresa a abrir la puerta VIP
                    }else{
                        cout<<"Vale, continua desfrutando de tus apuestas\n";
                        continue;
                    }
                }
            }else if (op1 == 4 ){
                cout<<"regresando a la puerta...\n";
                break;//Regresa a la puerta vip
            }else{
                cout<<"Opcion no valida :c\n";
                continue;
            }

        }
        if(fichas <= 0){
            cout<<"Se te han acabado, las fichas, realmente no puedes hacer mucho sin ellas\n ";
            cout<<"decides regresar al bar, te reencuentras con RAMONA...\n\n";
            cout<<"RAMONA:Vaya, otro intento más, otra perdida más, dejame llevarte a la zona especial :D\n\n";
            cout<<personaje<<" llega a un cuarto oscuro y con un olor muy fuerte a podredumbre, RAMONA enciende la luz\n";
            cout<<"es un cuarto con una cabina abierta, RAMONA te lleva dentro de la cabina, una vez dentro, empiezas a sentir un\n";
            cout<<"zumbido que cada vez se hace más fuerte hasta que . . . simplemente ya no lo escuchas, la cabeza te ha explotado\n";
            cout<<"o eso piensas persivir, pues realmente tu cuerpo está intacto, pero completamente adormecido\n";
            cout<<"una vez que este proceso da lugar, la cabina detecta el momenteo y gira el suelo de la misma, llevandote a\n";
            cout<<"un gran almacen en donde hay más cuerpos tambien, estos cuerpos pronto se recuperan y se les son arrebatados\n";
            cout<<"el pelo, la piel, el corazon y una parte de la medula espinal. Estos tejidos son muy valiosos para\n";
            cout<<"otros seres llamados Zora.\n";
            cout<<"Las palabras de Saul sobre los terminos y condiciones cobran más sentido.\n Al parecer las bebidas del lugar reaccionan con\n";
            cout<<"las fichas, una vez terminadas estas ultimas, el alcohol engaña a las neuronas explosivas holísticas y persiven una ausencia de vida\n";
            cout<<"basicamente es un golpe tan extraño del alcohol produciendo un estimulo tan complejo que termina apagando el cuerpo por completo\n";
            cout<<"una vez procesado tu cuerpo ya no hay marcha atras...has muerto\n";
            return false;
        }
        if (op == 1 || op1 == 4){
            cout<<"La puerta VIP necesita 7 fichas para entrar...\n";
            if (fichas>7){
                cout<<"has abierto la puerta VIP\n";
            }else{
                cout<<"Aun no cuentas con suficientes fichas para pasar la puerta VIP, regresa al cuarto de juegos y sigue apostando\n";
                cout<<"no deberías quedarte sin fichas...\n";
                continue;
            }  
        }
    }
    
    
}

void finalHistoria(){
    cout<<"F I N A L ";
}


int main(){   
    // vector<string> palabras={"platano","tact","else"};
    // string palabra =choose_palabra(palabras);
    //Fragmentos de la piedra filosofal
    int fragmentoPiedra = 0;
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
    //menú principal
    while (true){
        op = menuPrincipal();

        switch (op){
        case 1:
            //---------Pre game----------------------------------------------------
            cout<<"\n\n____________________________________________________________\n";
            cout<<"Antes de  empezar...\n\n";
            cout<<"____________________________________________________________\n";
            cout<<"\t\tAlgunas estadisticas de "<<jugador<<"\n";
            cout<<"____________________________________________________________\n";
            cout<<"Corazones: \t\t\t\t"<<corazones<<endl;
            cout<<"Dificultad: \t\t\t\t";
            if (dificultad == 1){
                cout<<"Facil\n";
            }else{cout<<"Dificil\n";}
            cout<<"Monedas: \t\t\t\t"<<monedas<<"\n";
            cout<<"Fragmentos de la piedra Filosofal: \t"<<fragmentoPiedra<<endl;
            cout<<"\n____________________________________________________________\n";
            cout<<"\tAlgunos objetos disponibles de: "<<jugador<<"\n";
            cout<<"____________________________________________________________\n";
            cout<<"Pociones : \t\t\t\t"<<pociones<<endl;
            cout<<"Pociones grandes : \t\t\t"<<pocionesMax<<endl;
            cout<<"Escudos : \t\t\t\t"<<escudos<<endl;
            cout<<"Hechizo 'golpe definitivo' : \t\t"<<ataqueMortal<<endl;
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
                            cout<<"Despues de derrotar al DRAGON DE OJOS AZULES,"<<jugador<<" sigue el sonido del agua\n";
                            cout<<"callendo, y encuentra una cueva, dentro de ella, hay un cadaver con una carta y un \n";
                            cout<<"paño rojo, dentro del paño hay una piedra roja y la carta reza lo siguiente: \n";
                            cout<<"LA PRINCESA ESTA EN OTRO CASTILLO!!!\n\n\njaja, la piedra fue fracturada hacer mucho\n";
                            cout<<"por un viejo hechizero que conocia el poder de la piedra, he aqui solo un fragmento\n";
                            cout<<"encuentra los otros dos y obtendras la piedra completa...\n\n";
                            cout<<jugador<<" ha encontrado un fragmento de  LA PIEDRA FILOSOFAL!!!\n\n";
                            fragmentoPiedra+=1;
                            cout<<"Fragmentos de la piedra filosofal: "<<fragmentoPiedra<<endl;
                            if (dificultad==1){
                                cout<<"Has recibido 300 monedas\n";
                                monedas+=300;
                            }else{
                                cout<<"Has recibido 500 monedas\n";
                                monedas+=500;
                            }
                            cout<<"Bosques perdidos superados!!!"<<endl;
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
                            cout<<"Despues de haber vuelto todo a la normalidad\n";
                            cout<<"te das cuenta de que el fragmento sigue contigo, estas cada vez más cerca de lograrlo\n";
                            cout<<"cada vez más cerca de conseguir la PIEDRA FILOSOFAL\n";
                            fragmentoPiedra++;
                            cout<<"Fragmentos de la piedra filosofal: "<<fragmentoPiedra<<endl;
                            cout<<"Reinos Zora superados\n";
                            if (dificultad==1){
                                cout<<"Has recibido 300 monedas\n";
                                monedas+=300;
                            }else{
                                cout<<"Has recibido 500 monedas";
                                monedas+=500;
                            }
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
                        cout<<"-----------------------------------------------------------------------------------------------\n";
                        cout<<"\tR U I N A S  D E L  A B I S M O \n\n";
                        cout<<"-----------------------------------------------------------------------------------------------\n";
                        cout<<"Resulta ser que los segidores de PRINGLES ya habian obtenido uno de los fragmentos, tuvieron que\n";
                        cout<<"hacer hasta lo imposible para que pudieran conseguir el fragmento, realmente no se sabe mucho\n";
                        cout<<"de ello, pues fue algo de lo que no se suele habla, sin embargo es bien sabido que, muchas de sus\n";
                        cout<<"cosas como un buen culto es mantenerlo en secreto, desafortunadamente no lo hacen realmente bien.\n";
                        cout<<"uno de sus grandes problemas, ademas de formar aquelarres con brujas, son las apuestas...\n";
                        cout<<"Uno de sus lugares favoritos para hacer este tipo de cosas en un ya conocido bar, tode se practica\n";
                        cout<<"un torneo de apuestas, que permite apuestas de practicamente todo, obiamente no está regulado y\n";
                        cout<<"mucho menos es legal ante el estado, por eso es necesario hacer algunas generosas donaciones a los\n";
                        cout<<"que cuidan el lugar, aquellos Goblins que solo velan por sus propios interese, se podrá decir de todo\n";
                        cout<<"sobre ellos pero lo cierto es que realmente son avariciosos y muy vivaces."<<jugador<<" espera hasta la\n";
                        cout<<"media noche para visitar el lugar. Resulta ser que la guarida tiene por nombre RUINAS DEL ABISMO\n";
                        cout<<"bastante inverosimil para ser lo que es.Te hacercas a la entrada y...\n";
                        cout<<"-----------------------------------------------------------------------------------------------\n\n";  
                        if(monedas>300){
                            cout<<"GOBLIN: Oye bro, no puedes pasar así como así, las cosas no son así, claro que nonononon\n";
                            cout<<"\tsi sabes lo que debes hacer, solo haslo, dejemonos de tanto rodeo...vale bro??\n";
                            cout<<"\tconoces el precio?? sisisisis son 300 monedas sisisisis ni una más, ni una menos sisisis\n\n";
                            cout<<"Pasan muchas cosas por tu cabeza, consideras los pro y contras, pero la posibilidad de obtener\n";
                            cout<<"esa piedra completa es demaciado tentadora...le das lo que pide el sujeto verdoso\n\n";
                            cout<<"GOBLIN: Sisisisi, ni una moneda más, ni una moneda menos, sisisi...te dejaré pasar\n";
                            cout<<"\tsabes, para la proxima entra por la puerta trasera, o vuelveme a pagar sisisisi...\n";
                            monedas-=300;
                            cout<<"Monedas actuales: "<<monedas<<endl;
                            if (RuinasDelAbismo(jugador, dificultad, pociones, pocionesMax, escudos, ataqueMortal)){
                            cout<<"Ruinas del Abismo superadas\n";
                            if (dificultad == 1){
                                cout<<"Has recibido 300 monedas\n";
                                monedas+=300;
                            }else{
                                cout<<"Has recibido 500 monedas\n";
                                monedas+=500;
                            }
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
                            cout<<"GOBLIN: Oye bro, no puedes pasar así como así, las cosas no son así, claro que nonononon\n";
                            cout<<"\tsi sabes lo que debes hacer, solo haslo, dejemonos de tanto rodeo...vale bro??\n";
                            cout<<"\tconoces el precio?? sisisisis son 300 monedas sisisisis ni una más, ni una menos sisisis\n\n";
                            cout<<"Pasan muchas cosas por tu cabeza, consideras los pro y contras, pero la posibilidad de obtener\n";
                            cout<<"esa piedra completa es demaciado tentadora...le das lo que pide el sujeto verdoso\n\n";
                            cout<<"sacas tu cartera del america y no encuentras lo suficiente....\n\n";
                            cout<<"GOBLIN: Veo lo que pasa, no hay monedas, no hay trato nononono, intentalo depues, vale bro?\n";
                            cout<<"\ttal vez puedas conseguir más completando las otras partes de la historia, ¿Qué como sé eso?\n";
                            cout<<"de la misma forma que sé que si pasas esos dichosos modos dificiles de la historia obtienes más monedas\n";
                            cout<<"\tbueno, realmente ni siquiera yo sé lo que significa...nonono, así que daja de molestarme sisisisis\n\n";
                            cout<<"Entiendes la situación y se apodera de ti la descepción...\n\n";
                            cout<<"Monedas actuales: "<<monedas<<endl;
                            cout<<"-----------------------------------------------------------------------------------------------------------\n\n";
                            break;

                        }
                    }else{
                        cout<<"Opcion no valida\n";
                    }
                
                }
                if (fragmentoPiedra == 3){
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
                        op = 1;
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
            //Progreso
            cout<<"____________________________________________________________\n";
            cout<<"\t\tAVANCE DE LA HISTORIA\n\n";
            cout<<"____________________________________________________________\n";
            cout<<"La historia principal se compone de 3 capitulos. Cada uno\n";
            cout<<"de ellos comprende su propio hilo narrativo pero en      \n";
            cout<<"conjunto forman la historia completa. Para ver el final, \n";
            cout<<"es necesario pasar los 3 capitulos.\n";
            cout<<"____________________________________________________________\n";
            cout<<"\t\t\tPROGRESO: \n\n";
            if (fragmentoPiedra == 0){
                cout<<"Aun no has jugado lo suficiente. Prueba usar items de la\n";
                cout<<"tienda para facilitar la aventura.\n";
                cout<<"Fragmentos de la PIEDRA FILOSOFAL encontrados: \t"<<fragmentoPiedra<<endl;
            }else if (fragmentoPiedra==3){
                cout<<"Felicidades, has completado el juego por completo\n";
                cout<<"en verdad, no fue facil hacerlo pero si lo has\n";
                cout<<"disfrutado, valio la pena...\n";
                cout<<"Fragmentos de la PIEDRA FILOSOFAL encontrados: \t"<<fragmentoPiedra<<endl;
            }else{
                cout<<"Estas cada vez más cerca del final del juego, itenta pasar\n";
                cout<<"los otros "<<3-fragmentoPiedra<<" capitulos restantes para\n";
                cout<<"terminar el juego\n";
                cout<<"Fragmentos de la PIEDRA FILOSOFAL encontrados: \t"<<fragmentoPiedra<<endl;
            }
            break;
        case 5:
            //Salir
            break;
        default:
            //Validacion de entrada limitada a 4 casos en menuPrincipal()
            cout<<"texto de relleno\n";
            break;
        }
        //Case 4, salir del juego, aqui op = 4 para salir
        if (op==5){
            cout<<"Estas saliendo del juego...\n";
            cout<<"Gracias por jugar";
            break;
        } 
    }
}