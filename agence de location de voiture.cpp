#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Voiture {
private:
    string matricule;
    string marque;
    string modele;
    bool disponible;

public:
    Voiture() : matricule("00000"), marque("xx"), modele("xx"), disponible(true) {}
    Voiture(string mat, string mar, string mod) : matricule(mat), marque(mar), modele(mod), disponible(true) {}

    string getMatricule() const { return matricule; }
    string getMarque() const { return marque; }
    string getModele() const { return modele; }
    bool estDisponible() const { return disponible; }

    void setDisponibilite(bool dispo) { disponible = dispo; }

    void afficherVoiture() const {
        cout << "Matricule: " << matricule << " | Marque: " << marque << " | Modele: " << modele;
        cout << " | Disponibilite: ";
        	if (disponible == true) {
    			cout << "Oui"; }
			else 
    			cout << "Non";
    }
};

class Client {
private:
    string nom;
    string prenom;
    string cin;

public:
    Client() : nom("X"), prenom("X"), cin("XXXXX") {}
    Client(string n, string p, string c) : nom(n), prenom(p), cin(c) {}

    string getNom() const { return nom; }
    string getPrenom() const { return prenom; }
    string getCin() const { return cin; }
};

class Location {
private:
    Voiture* voiture;
    Client client;
    string loc;

public:
    Location(Voiture* v, const Client& c, string loc) : voiture(v), client(c), loc(loc) {}

    Voiture* getVoiture() const { return voiture; }
    const Client& getClient() const { return client; }
    string getLoc() const { return loc; }

    void afficherLocation() const {
        cout << "Voiture: " << voiture->getMatricule() << " louee par "
             << client.getNom() << " " << client.getPrenom() << " a "
             << loc << "." << endl;
    }
};

class Agence {
private:
    vector<Voiture> voitures;
    vector<Location> locations;

public:
    void ajouterVoiture(const Voiture& v) {
        voitures.push_back(v);
        cout << "Voiture ajoutee: " << v.getMatricule() << endl;
    }

    void louerVoiture(const string& matricule, const Client& client, const string& loc) {
        for (int i = 0; i < voitures.size(); ++i) {
            if (voitures[i].getMatricule() == matricule) {
                if (!voitures[i].estDisponible()) {
                    cout << "La voiture " << matricule << " n est pas disponible." << endl;
                    return;
                }
                voitures[i].setDisponibilite(false);
                locations.push_back(Location(&voitures[i], client, loc));
                cout << "La voiture " << matricule << " a ete louee par " << client.getNom() << " a " << loc << "." << endl;
                return;
            }
        }
        cout << "Voiture avec matricule " << matricule << " introuvable." << endl;
    }

    void retournerVoiture(const string& matricule) {
        for (int i = 0; i < locations.size(); ++i) {
            if (locations[i].getVoiture()->getMatricule() == matricule) {
                locations[i].getVoiture()->setDisponibilite(true);
                locations.erase(locations.begin() + i);
                cout << "La voiture " << matricule << " a ete retournee." << endl;
                return;
            }
        }
        cout << "Aucune location en cours pour la voiture " << matricule << "." << endl;
    }

    void afficherVoituresDisponibles() const {
        cout << "Voitures disponibles: " << endl;
        for (int i = 0; i < voitures.size(); ++i) {
            if (voitures[i].estDisponible()) {
                voitures[i].afficherVoiture();
            }
        }
    }

    void afficherLocations() const {
        cout << "Locations en cours: " << endl;
        for (int i = 0; i < locations.size(); ++i) {
            locations[i].afficherLocation();
        }
    }
};

int main() {
    Agence agence;
    int x;

    do {
        cout << "\nMenu: " << endl;
        cout << "1. Ajouter une voiture a la flotte" << endl;
        cout << "2. Louer une voiture" << endl;
        cout << "3. Retourner une voiture" << endl;
        cout << "4. Afficher les voitures disponibles" << endl;
        cout << "5. Afficher les locations en cours" << endl;
        cout << "6. Quitter" << endl;
        cout << "Choix: ";

        cin >> x;

        switch (x) {
            case 1: {
                string matricule, marque, modele;
                cout << "Saisir matricule : ";
                cin >> matricule;
                cout << "Saisir marque : ";
                cin >> marque;
                cout << "Saisir modele : ";
                cin >> modele;
                agence.ajouterVoiture(Voiture(matricule, marque, modele));
                break;
            }
            case 2: {
                string matricule, nom, prenom, cinClient, loc;
                cout << "Saisir matricule de la voiture : ";
                cin >> matricule;
                cout << "Saisir nom du client : ";
                cin >> nom;
                cout << "Saisir prenom du client : ";
                cin >> prenom;
                cout << "Saisir CIN du client : ";
                cin >> cinClient;
                cout << "Saisir lieu de location : ";
                cin >> loc;
                agence.louerVoiture(matricule, Client(nom, prenom, cinClient), loc);
                break;
            }
            case 3: {
                string matricule;
                cout << "Saisir matricule de la voiture retournee : ";
                cin >> matricule;
                agence.retournerVoiture(matricule);
                break;
            }
            case 4:
                agence.afficherVoituresDisponibles();
                break;
            case 5:
                agence.afficherLocations();
                break;
            case 6:
                cout << "Au revoir!" << endl;
                break;
            default:
                cout << "Choix invalide." << endl;
        }
    } while (x != 6);

    return 0;
}
