#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>
using namespace std;


string choose_palabra(const vector<string>& listaPalabras){
    /*
    listaPalabras (vector de strings): lista de palabras (strings)
    Devuelve una palabra aleatoria de la lista de palabras
    */
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % listaPalabras.size();
    return listaPalabras[randomIndex];
}

int main()
{
    vector<string> palabras ={"gato","perro","tarde","bufalo","conejo"};
    string word = choose_palabra(palabras);
    cout<<"Palabra aleatoria: "<<word;
    return 0;
}