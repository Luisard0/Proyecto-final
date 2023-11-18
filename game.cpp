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
    Devuelve una palabra aleatoria de la lista de palabras
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
    Devuelve un booleano, Verdadero si todas las letras de palabra_secreta están en letras_adivinadas,
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

int main()
{
    string palabrasecreta = "python";
    vector<char> letrasAdivinadas={'p','y','t','h','o','n'};
    bool adivinada = palabraAdivinada(palabrasecreta,letrasAdivinadas);

    cout<<"Palabra adivinada? "<<(adivinada ? "Si":"No")<<endl;
    return 0;
}