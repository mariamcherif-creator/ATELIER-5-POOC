#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <string>
#include <stdexecpt>
using namespace std;

/* ============================================================
   1. Création d'un set<int> contenant les entiers de 1 à 100
   ============================================================ */
set<int> creerSet1a100() {
    set<int> s;
    for (int i = 1; i <= 100; i++) {
        s.insert(i);
    }
    return s;
}

/* ============================================================
   2. Fonction simple : recherche dans un set<int>
   ============================================================ */
bool rechercherDansSet(const set<int>& s, int valeur) {
    return s.find(valeur) != s.end();
}

/* ============================================================
   3. Fonction utilisant deux itérateurs de set<int>
   ============================================================ */
bool rechercherIterateurs(set<int>::const_iterator debut,
                          set<int>::const_iterator fin,
                          int valeur) {
    while (debut != fin) {
        if (*debut == valeur)
            return true;
        debut++;
    }
    return false;
}

/* ============================================================
   4. Version Template (fonction générique)
   ============================================================ */
template<typename It, typename T>
bool rechercherGenerique(It debut, It fin, const T& valeur) {
    while (debut != fin) {
        if (*debut == valeur)
            return true;
        ++debut;
    }
    return false;
}

/* ============================
   PROGRAMME DE TEST
   ============================ */
int main() {

    // Test 1 : Set d'entiers 1..100
    set<int> s = creerSet1a100();
    cout << "45 dans set ? " << rechercherDansSet(s, 45) << endl;
    cout << "150 dans set ? " << rechercherDansSet(s, 150) << endl;

    // Test 2 : Itérateurs de set
    cout << "80 (via iterateurs) ? " 
         << rechercherIterateurs(s.begin(), s.end(), 80) << endl;

    // Test 3 : Appels Template

    // a) vecteur de string
    vector<string> v = {"bonjour", "mariam", "tanger", "smart"};
    cout << "Recherche 'mariam' dans vector<string> : "
         << rechercherGenerique(v.begin(), v.end(), string("mariam")) << endl;

    // b) liste d'entiers
    list<int> l = {10, 20, 30, 40};
    cout << "Recherche 30 dans list<int> : "
         << rechercherGenerique(l.begin(), l.end(), 30) << endl;

    // c) tableau classique de float
    float tab[] = {1.1, 2.2, 3.3, 4.4};
    cout << "Recherche 3.3 dans tableau float : "
         << rechercherGenerique(tab, tab + 4, 3.3f) << endl;

    return 0;
}
