#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
using namespace std;

//Escoge una palbra de un vector de palabras
string choose_palabra(const vector<string>& listaPalabras){
    /*
    listaPalabras (vector de strings): lista de palabras (strings)
    Devuelve: palabra aleatoria de la lista de palabras
    */
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % listaPalabras.size();
    return listaPalabras[randomIndex];
}

//Reviza si la palabra ha sido adivinada
bool palabraAdivinada(const string& palabra_secreta, const vector<char>& letras_adivinadas){
    /*
    palabra secreta: string, la palabra que el usuario está adivinando; 
     se asume que todas las letras son minusculas
    letras_adivinadas: vector (de caracteres), letras que ya han sido adivinadas;
     se asume que todas las letras son minusculas
    Devuelve: booleano, Verdadero si todas las letras de palabra_secreta están en letras_adivinadas,
    de otra manera Falso.
    */
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
    /*
    palabra_secreta: string, palabra que el usuario está adivinando
    letras_adivinadas: vector (de caracteres), letras que ya han sido adivinadas
    Devuelve: string, comprendido de letras y guiones bajos (_) y espacios, que representan 
     que letras de palabra_secreta se han adivinado hasta ahora

    */
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
    /*
    letras_adivinadas: vector (de caracteres), cuales letras han sido adivinadas
    Devuelve: string (de letras), comprendido de letras que representan cuales letras aun no han sido adivinadas
    */
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

void hangman(const string& palabra_secreta){
    /*
    palabra_secreta: string, la palabra secreta a adivinar
    
    Empieza un juego interactivo del ahoracado

    *Al inicio del juego, se le deja saber al usuario cuantas
     letras tiene la palabra_secreta y con cuantos intentos empieza

    *El usuario debería empezar con 6 intentos 

    *Antes de cada round, se le muestra al usuario cuantos intentos le quedan y 
     las letras que el usuario aun no ha adivinado
    
    *Pedirle al usuario una conjetura por ronda, solo letras

    *El usuario debe recibir feedback inmediatamente despues de cada intento sobre si su intento 
      aparece en la palabra de la computadora
    
    *Despues de cada intento, se le debe mostrar al usuario la palabra parcialmente adivinada
    */

    int intentos = 6;
    int advertencias = 3;
    vector<char> letras_unicas;
    vector<char> lista_letras;
    char vocales[]={'a','e','i','o','u'};
    cout<<"Bienvenido al juego del ahorcado!!"<<endl;
    size_t tamano = palabra_secreta.length();
    cout<<"Estoy pensando en una palbra que tiene "<<tamano<<" letras\n";
    cout<<"Te quedan "<<advertencias<<" advertencias\n";
    cout<<"-------------------------------------------------------------------";

    //letras unicas en la palabra para el score
    for (char letra : palabra_secreta){
        if (find(letras_unicas.begin(),letras_unicas.end(),letra) == letras_unicas.end()){
            letras_unicas.push_back(letra);
        }
    }
    //game
    while (true){
        //Validación del imput
        while (true){
            try{
                if (intentos > 0){
                    //Pide la letra
                    cout<<"Te quedan "<<intentos<<" intentos"<<endl;
                    cout<<"Letras disponibles:  "<<get_letrasDisponibles(lista_letras)<<endl;

                    char guess;
                    cout<<"Por favor, adivina una letra: ";
                    cin>>guess;

                    if (isalpha(guess)){
                        guess = tolower(guess);

                        if (advertencias > 0){
                            if (find(lista_letras.begin(), lista_letras.end(), guess) != lista_letras.end()){
                                advertencias--;
                                cout<<"Opps, Ya has usado esa letra. Te quedan "<<advertencias<<" advertencias restantes\n";
                                cout<<get_palabraAdivinada(palabra_secreta, lista_letras)<<endl;
                                cout<<"-------------------------------------------------------------------"<<endl;
                                continue;
                            }else{
                                lista_letras.push_back(guess);
                                break;
                            }
                        }else{ //las advertencias son 0
                            if (find(lista_letras.begin(), lista_letras.end(), guess) != lista_letras.end()){
                                cout<<"Opps, ya has usado esa letra. Te has quedado sin advertencias, perderas un intento.\n";
                                intentos--;
                                cout<<get_palabraAdivinada(palabra_secreta, lista_letras)<<endl;
                                cout<<"-------------------------------------------------------------------"<<endl;
                                continue;
                            }else{
                                lista_letras.push_back(guess);
                                break;
                            }
                        }
                    }else{
                        if (advertencias > 0){
                            advertencias--;
                            cout<<"Opps!! "<<guess<<" no es valido. Te quedan "<<advertencias<<" advertencias \n";
                            cout<<get_palabraAdivinada(palabra_secreta, lista_letras)<<endl;
                            cout<<"-------------------------------------------------------------------"<<endl;
                            continue;
                        }else{
                            cout<<"Opps!! "<<guess<<" no es valido . Has perdido tus advertencias, entonces se te restará un intento. \n";
                            cout<<get_palabraAdivinada(palabra_secreta, lista_letras)<<endl;
                            cout<<"-------------------------------------------------------------------"<<endl;
                            intentos--;
                            continue;
                        }
                    }
                }else{
                    break;//se le acabaron los intentos en puros errores de dedo XD
                }
            }catch(...){
                cerr<<"Error: validar entrada"<<endl;
            }
        }
    }
    


}
int main()
{
    vector<char> letras_adivinadas = {};
    string letrasDisponibles = get_letrasDisponibles(letras_adivinadas);
    cout<<"Letras disponibles: "<<letrasDisponibles<<endl;
    return 0;
}