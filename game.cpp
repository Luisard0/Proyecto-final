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

int main()
{
    vector<char> letras_adivinadas = {};
    string letrasDisponibles = get_letrasDisponibles(letras_adivinadas);
    cout<<"Letras disponibles: "<<letrasDisponibles<<endl;
    return 0;
}