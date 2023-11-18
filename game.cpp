#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
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
void hangman(const string& palabra_secreta){
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
            break;
        }else if (palabra_secreta.find(guess[0]) != string::npos){
            if (palabraAdivinada(palabra_secreta, lista_letras)){//pregunta si están todas las letras de la palabra secreta en la lista de letras ya adivinadas
                cout<<"Muy bien: "<<get_palabraAdivinada(palabra_secreta, lista_letras)<<endl;
                cout<<"-----------------------------\n";
                cout<<"Felicidades, ganaste !!!\n";
                //Score = intentos restantes * numero de letras unicas en la palabra secreta
                int score = intentos * letras_unicas.size();
                cout<<"Tu puntuacion final es: "<<score<<endl;
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
bool piedraPapelTijeras(){
    // Configurar la semilla para generar números aleatorios
    srand(static_cast<unsigned int>(time(0)));
    cout<<"---------------------------------\n";
    cout << "\nBienvenido al juego de Piedra, Papel o Tijeras." << endl;
    cout << "Victorias necesarias para ganar: 3"<<endl;
    cout<<"Los empates seran considerados como derrotas :c"<<endl;
    cout<<"---------------------------------";
    int victorias = 0;
    int round = 1; 
    while (victorias<3){
        cout<<"\nRound: "<< round<<endl;
        round++;
        if(victorias==2){
            cout<<"Solo una victoria mas...:\n" ;
        }else if (victorias>=0){
            cout<<"Victorias actuales: "<<victorias<<endl;
        }else{
            cout<<"Perdiendo :c\n";
        }
        
        int usuario = manoUsuario();
        //int computadora = manoComputadora();
        int computadora = 2;
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



int main()
{
    if (piedraPapelTijeras()){
        cout<<"Reto superado\n";
    }else{
        cout<<"Reto no superado :c";
    }
    return 0;
}