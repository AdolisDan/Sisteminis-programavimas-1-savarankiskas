#include "MyLib.h"

class Studentas {
private:
    string vardas;
    string pavarde;
    vector<int> namuDarbai;
    int egzaminoRezultatas;
    double galutinisBalas;

public:
    Studentas() : egzaminoRezultatas(0), galutinisBalas(0.0) {}

    Studentas(const string& v, const string& p, const vector<int>& nd, int egz)
        : vardas(v), pavarde(p), namuDarbai(nd), egzaminoRezultatas(egz) {
        skaiciuotiGalutini(true);
    }

    Studentas(const Studentas& other)
        : vardas(other.vardas), pavarde(other.pavarde),
        namuDarbai(other.namuDarbai), egzaminoRezultatas(other.egzaminoRezultatas),
        galutinisBalas(other.galutinisBalas) {}

    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            vardas = other.vardas;
            pavarde = other.pavarde;
            namuDarbai = other.namuDarbai;
            egzaminoRezultatas = other.egzaminoRezultatas;
            galutinisBalas = other.galutinisBalas;
        }
        return *this;
    }

    ~Studentas() {}

    friend istream& operator>>(istream& cin, Studentas& studentas) {
        cout << "?veskite vard?: ";
        cin >> studentas.vardas;
        cout << "?veskite pavard?: ";
        cin >> studentas.pavarde;

        cout << "?veskite nam? darb? rezultatus (baigti ?vedus -1, generuoti atsitiktiniu pazymius -2): ";
        int nd;
        if (cin >> nd && nd == -2) {
            for (int i = 0; i < 10; i++)
            {
                srand(static_cast<unsigned int>(std::time(nullptr)));
                studentas.namuDarbai.push_back(rand() % 10 + 1);
                studentas.egzaminoRezultatas = rand() % 10 + 1;
            }
        }
        else {
            while (cin >> nd && nd != -1)
            {
                if (0< nd && nd <= 10) {
                    studentas.namuDarbai.push_back(nd);
                }
                else {
                    cout << "?vestas blogas pažymys, veskite dar kart?: ";
                }
            }
            cout << "?veskite egzamino rezultat?: ";
            cin >> studentas.egzaminoRezultatas;
        }
     
        return cin;
    }

    friend ostream& operator<<(ostream& out, const Studentas& studentas) {
        cout << left << setw(15) << studentas.pavarde << setw(15) << studentas.vardas << fixed << setprecision(2) << studentas.galutinisBalas;
        return cout;
    }

    void skaiciuotiGalutini(int vidMed) {
        if (vidMed == 1) {
            double vidurkis = 0;
            for (int nd : namuDarbai)
            {
                vidurkis += nd;
            }
            galutinisBalas = 0.4 * (vidurkis / namuDarbai.size()) + 0.6 * egzaminoRezultatas;
        }
        else if (vidMed == 2) {
            sort(namuDarbai.begin(), namuDarbai.end());
            double mediana;
            if (namuDarbai.size() % 2 == 0) {
                mediana = (namuDarbai[namuDarbai.size() / 2 - 1] + namuDarbai[namuDarbai.size() / 2]) / 2.0;
            }
            else {
                mediana = namuDarbai[namuDarbai.size() / 2];
            }
            galutinisBalas = 0.4 * mediana + 0.6 * egzaminoRezultatas;
        }
    }
};

    

int main()
{
    vector<Studentas> studentai;
    char ar = 't';
    do {
        Studentas studentas;
        cin >> studentas;
        int vidMed;
        cout << "Ar norite skai?iuoti galutin? bal? pagal vidurk? ar median?? (1 - vidurk? | 2 - median?): ";
        cin >> vidMed;
        studentas.skaiciuotiGalutini(vidMed);
        studentai.push_back(studentas);

        cout << "Ar norite prid?ti dar vien? student?? (t/n): ";
        cin >> ar;
    } while (ar == 't');

    cout << "Pavard?        Vardas         Galutinis(Vid.)" << endl;
    cout << "-------------------------------------------------" << endl;
    for (const auto& studentas : studentai) {
        cout << studentas << endl;
    }

    return 0;
}
