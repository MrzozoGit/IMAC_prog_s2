#include <iostream>

using namespace std;

struct Noeud {
    int data;
    Noeud* suivant;
};

struct Liste {
    Noeud* premier;
};

struct DynaTableau {
    int* data;
    int capacite;
    int nbVal;
};


void initialise(Liste* liste) {
    liste->premier = nullptr;
}

bool est_vide(const Liste* liste) {
    if(liste->premier == nullptr)
        return true;
    else
        return false;
}

void ajoute(Liste* liste, int valeur) {
    Noeud* nouveau = new Noeud;
    nouveau->data = valeur;
    nouveau->suivant = nullptr;

    Noeud* dernier = liste->premier;

    if(est_vide(liste)) {
        liste->premier = nouveau;
    } else {
        while(dernier->suivant != nullptr) {
            dernier = dernier->suivant;
        }
        dernier->suivant = nouveau;
    }
}

void affiche(const Liste* liste) {
    Noeud* dernier = liste->premier;

    while(dernier != nullptr) {
        printf("%d ", dernier->data);
        dernier = dernier->suivant;
    }
    printf("\n");
}

int recupere(const Liste* liste, int n) {
    Noeud* dernier = liste->premier;

    for(int i=0; i<n; i++) {
        if(dernier != nullptr) {
            dernier = dernier->suivant;
        } else {
            return -1;
        }
    }

    return dernier->data;
}

int cherche(const Liste* liste, int valeur) {
    Noeud* dernier = liste->premier;
    int compteur = 1;

    while(dernier != nullptr) {
        if(dernier->data == valeur) {
            return compteur;
        }
        compteur++;
        dernier = dernier->suivant;
    }

    return -1;
}

// INCOMPLET !!!
void stocke(Liste* liste, int n, int valeur) {
    Noeud* dernier = liste->premier;

    for(int i = 0; i < n; i++) {
        if(dernier != nullptr) {
            dernier = dernier->suivant;
        } else {
            printf("ERREUR: index out of bound");
        }
    }

    dernier->data = valeur;
}

void ajoute(DynaTableau* tableau, int valeur) {
    if(tableau->nbVal+1 > tableau->capacite) {
        tableau->capacite++;
        int* newData = new int[tableau->capacite];

        for(int i=0; i<tableau->capacite; i++) {
            newData[i] = tableau->data[i];
        }

        newData[tableau->capacite] = valeur;
        tableau->data = newData;

        tableau->nbVal++;
    } else {
        tableau->data[tableau->nbVal] = valeur;
        tableau->nbVal++;
    }
}


void initialise(DynaTableau* tableau, int capacite) {
    tableau->nbVal = 0;
    tableau->capacite = capacite;
    tableau->data = new int[capacite];
}

bool est_vide(const DynaTableau* liste) {
    if(liste->nbVal == 0)
        return true;
    else
        return false;
}

void affiche(const DynaTableau* tableau) {
    for(int i = 0; i < tableau->nbVal; i++) {
        printf("%i ", tableau->data[i]);
    }
    printf("\n");
}

int recupere(const DynaTableau* tableau, int n) {
    if(tableau->nbVal > n) {
        return tableau->data[n];
    }
    return -1;
}

int cherche(const DynaTableau* tableau, int valeur) {
    for (int i = 0; i < tableau->nbVal; i++) {
        if (tableau->data[i] == valeur) {
            return i;
        }
    }
    return -1;
}

void stocke(DynaTableau* tableau, int n, int valeur) {
    if (tableau->nbVal > n) {
        tableau->data[n] = valeur;
    }
}

void pousse_file(Liste* liste, int valeur) {
    Noeud* nouveau = new Noeud;
    nouveau->data = valeur;

    if(est_vide(liste)) {
        nouveau->suivant = nullptr;
    } else {
        nouveau->suivant = liste->premier;
    }

    liste->premier = nouveau;
}

int retire_file(Liste* liste) {
    Noeud* dernier = liste->premier;

    if(liste->premier->suivant == NULL) {
        int valeur = liste->premier->data;
        liste->premier = NULL;
        return valeur;
    }

    while(dernier->suivant != nullptr && dernier->suivant->suivant != nullptr) {
        dernier = dernier->suivant;
    }

    int valeur = dernier->suivant->data;
    delete dernier->suivant;
    dernier->suivant = nullptr;
    return valeur;
}

void pousse_pile(Liste* liste, int valeur) {
    ajoute(liste, valeur);
}

int retire_pile(Liste* liste) {
    Noeud* dernier = liste->premier;

    if(liste->premier->suivant == NULL) {
        int valeur = liste->premier->data;
        liste->premier = NULL;
        return valeur;
    }

    while(dernier->suivant != nullptr && dernier->suivant->suivant != nullptr) {
        dernier = dernier->suivant;
    }

    int valeur = dernier->suivant->data;
    delete dernier->suivant;
    dernier->suivant = nullptr;
    return valeur;
}


int main() {
    Liste liste;
    initialise(&liste);
    DynaTableau tableau;
    initialise(&tableau, 5);

    if(!est_vide(&liste)) {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if(!est_vide(&tableau)) {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    for(int i=1; i<=7; i++) {
        ajoute(&liste, i*7);
        ajoute(&tableau, i*5);
    }

    if(est_vide(&liste)) {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if(est_vide(&tableau)) {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    std::cout << "Elements initiaux:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    std::cout << "5e valeur de la liste " << recupere(&liste, 4) << std::endl;
    std::cout << "5e valeur du tableau " << recupere(&tableau, 4) << std::endl;

    std::cout << "21 se trouve dans la liste a " << cherche(&liste, 21) << std::endl;
    std::cout << "15 se trouve dans la liste a " << cherche(&tableau, 15) << std::endl;

    stocke(&liste, 4, 7);
    stocke(&tableau, 4, 7);

    std::cout << "Elements apres stockage de 7:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    Liste pile; // DynaTableau pile;
    Liste file; // DynaTableau file;

    initialise(&pile);
    initialise(&file);

    for(int i=1; i<=7; i++) {
        pousse_file(&file, i);
        pousse_pile(&pile, i);
    }

    int compteur = 10;
    while(!est_vide(&file) && compteur > 0) {
        std::cout << retire_file(&file) << std::endl;
        compteur--;
    }

    if(compteur == 0) {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    compteur = 10;
    while(!est_vide(&pile) && compteur > 0) {
        std::cout << retire_pile(&pile) << std::endl;
        compteur--;
    }

    if(compteur == 0) {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    return 0;
}
