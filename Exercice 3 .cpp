#include <iostream>
#include <algorithm> // pour std::copy
#include <stdexcept>

using namespace std;

/*
 Classe de base fournie (version complète et sûre)
*/
class vect {
protected:
    int nelem;   // nombre d'éléments
    int *adr;    // adresse zone dynamique contenant les éléments

public:
    // constructeur (alloue et initialise à 0)
    explicit vect(int n = 0) : nelem(n) {
        if (nelem > 0) {
            adr = new int[nelem];
            for (int i = 0; i < nelem; ++i) adr[i] = 0;
        } else {
            adr = nullptr;
        }
    }

    // destructeur
    virtual ~vect() {
        delete[] adr;
        adr = nullptr;
    }

    // accès à un élément (par référence) - sans checks pour être fidèle à la signature,
    // mais ici on ajoute un contrôle pour éviter comportement indéfini
    int & operator[] (int i) {
        if (i < 0 || i >= nelem) throw out_of_range("indice hors limites");
        return adr[i];
    }

    // version const pour accès en lecture
    const int & operator[] (int i) const {
        if (i < 0 || i >= nelem) throw out_of_range("indice hors limites");
        return adr[i];
    }

     
};


class vectok : public vect {
public:
    explicit vectok(int n = 0) : vect(n) {}
    vectok(const vectok &other) : vect(other.nelem) {
        if (nelem > 0) {
            std::copy(other.adr, other.adr + nelem, adr);
        }
    }

    
    vectok & operator=(const vectok &other) {
        if (this == &other) return *this; 
        if (other.nelem != nelem) {
            delete[] adr;
            nelem = other.nelem;
            if (nelem > 0) {
                adr = new int[nelem];
            } else {
                adr = nullptr;
            }
        }

        if (nelem > 0) {
            std::copy(other.adr, other.adr + nelem, adr);
        }
        return *this;
    }
    
    int size() const { return nelem; }

    // (optionnel) on peut définir un constructeur depuis vect (copie base -> derived)
    // ici pas nécessaire pour l'exercice.
};

/* ---------- petit programme de test  ---------- */
void affiche(const vectok &v, const string &nom) {
    cout << nom << " (taille=" << v.size() << "): ";
    for (int i = 0; i < v.size(); ++i) cout << v[i] << " ";
    cout << "\n";
}

// fonction prenant l'objet par valeur (test de copie)
void modifParValeur(vectok v) {
    if (v.size() > 0) v[0] = 999; // modifie la copie
    cout << "Dans modifParValeur, copie modifiée: ";
    for (int i = 0; i < v.size(); ++i) cout << v[i] << " ";
    cout << "\n";
}

int main() {
    // création d'un vectok de taille 5
    vectok a(5);
    for (int i = 0; i < a.size(); ++i) a[i] = i + 1; // 1 2 3 4 5
    affiche(a, "a");

    // test constructeur de copie
    vectok b = a; // copie profonde
    affiche(b, "b (après vectok b = a)");

    // modifier b et montrer que a n'est pas affecté (preuve de deep copy)
    b[0] = 42;
    cout << "Après b[0]=42 :\n";
    affiche(a, "a");
    affiche(b, "b");

    // test opérateur d'affectation
    vectok c(3);
    for (int i = 0; i < c.size(); ++i) c[i] = 100 + i;
    affiche(c, "c (avant c = a)");

    c = a; // opérateur d'affectation
    affiche(c, "c (après c = a)");

    // test auto-affectation (doit rester stable)
    c = c;
    affiche(c, "c (après c = c)");

    // test passage par valeur (doit appeler constructeur de copie)
    modifParValeur(a);
    cout << "Après modifParValeur(a), a doit rester inchangé:\n";
    affiche(a, "a");

    return 0;
}
