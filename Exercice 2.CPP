#include <iostream>
#include <stdexcept>
using namespace std;

class Test{
public:
    static int tableau[];

public:
    static int division(int indice, int diviseur){
        // Vérifier si l'indice existe
        if (indice < 0 || indice > 9)
            throw out_of_range("Indice hors limites !");

        // Vérifier la division par zéro
        if (diviseur == 0)
            throw runtime_error("Division par zero interdite !");

        return tableau[indice] / diviseur;
    }
};

int Test::tableau[] = {17, 12, 15, 38, 29, 157, 89, -22, 0, 5};

int main() {
    int x, y;

    try {
        cout << "Entrez l indice de l entier à diviser: " << endl;
        cin >> x;

        cout << "Entrez le diviseur: " << endl;
        cin >> y;

        cout << "Le résultat de la division est: " << endl;
        cout << Test::division(x, y) << endl;
    }
    catch (exception &e) {
        // Le programme s’arrête immédiatement en cas d’exception
        cerr << "ERREUR : " << e.what() << endl;
        return 1;  
    }

    return 0;
}
