// Praktikum PRA-PRG2
// Programm von Lars Ebbeke
// 2023-11-21
// Bankkonto (PRA-PRG2 A3)


#include <iostream>
#include <random>

//Einstellungen
const double initSaldo = 100.0;       //Anfangsguthaben auf dem Konto
const double initSollZins = 2.5;      //Startwert für den Sollzins
const double initHabenZins = 1.25;    //Startwert für den Habenzins
const double range = 500.0;           //Bereich um 0 mit dem Transaktionen generiert werden
const double offset = 0.0;            //Offset des Bereiches der Zufallszahlen
const int jahre = 100;                //Anzahl der Jahre, die simuliert werden soll


class Bankkonto {
private:
    double guthaben;
    double sollZins;    //Zinssatz für überzogenes Konto (%)
    double habenZins;   //Zinssatz für normales Konto (%)

public:
    // Konstruktor
    Bankkonto(double anfangsGuthaben, double sollZinsAnfang, double habenZinsAnfang)
    :guthaben(anfangsGuthaben){
        sollZins = sollZinsAnfang;
        habenZins = habenZinsAnfang;
    }

    void verzinsen() {
        //Positives Guthaben habenZins, negatives Guthaben sollZins. Da in % alles noch mal /100
        if (guthaben >= 0) {
            guthaben *= (1 + habenZins/100);
        } else {
            guthaben *= (1 + sollZins/100);
        }
        //guthaben auf zwei nachkommastellen aufrunden
        guthaben = std::ceil(guthaben*100)/100;
    }

    void einzahlen(double betrag) {
        //Negative Beträge können nicht eingezahlt werden
        if (betrag < 0) {
            std::cout << "Fuer Auszahlungen bitte die Funktion \"Auszahlen\" verwenden!";
        } else {
            guthaben += betrag;
            //std::cout << betrag << "€ eingezahlt. Neues Guthaben: " << guthaben << "\n\n";
        }
    }

    void auszahlen(double betrag) {
        //Negative beträge können nicht ausgezahlt werden
        if (betrag < 0) {
            std::cout << "Negative Betraege koennen nicht ausgezahlt werden. Fuer Einzahlungen bitte \"Einzahlen\" waehlen!";
        } else {
            guthaben -= betrag;
            //std::cout << betrag << "€ ausgezahlz. Neues Guthaben: " << guthaben << "\n\n";
        }
    }

    void neuZins(double sollZinsNeu, double habenZinsNeu) {
        sollZins = sollZinsNeu;
        habenZins = habenZinsNeu;
    }

    double getSaldo() const {
        return guthaben;
    }

};


int main() {
    double kontobewegung;

    //Mersenne-Twister-Engine Zufallsgenerator initialisieren
    //Vielen dank an Herrn GPT für den Zufallsgenerator
    std::mt19937 generator(std::random_device{}());
    //Definition eines Zahlenbereiches
    std::uniform_real_distribution<double> random(-range + offset, range + offset);

    //Neues Bankkonto-Objekt erzeugen
    Bankkonto testKonto(initSaldo, initSollZins, initHabenZins);

    for (int i = 1; i <= jahre; i++) {
        std::cout << "\nJahr " << i << " Kontostand: " << testKonto.getSaldo() << " EUR\n";

        //zufälligen betrag generieren
        kontobewegung = random(generator);
        //betrag auf zwei nachkommastellen runden
        kontobewegung = std::round(kontobewegung*100)/100;

        testKonto.verzinsen();

        std::cout << "Kontostand nach Zinsen: " << testKonto.getSaldo() << " EUR\n";

        if (kontobewegung > 0) {
            testKonto.einzahlen(kontobewegung);
            std::cout << kontobewegung << " EUR eingezahlt\n";
        }
        if (kontobewegung < 0) {
            testKonto.auszahlen(-kontobewegung);
            std::cout << -kontobewegung << " EUR ausgezahlt\n";
        }
    }
    return 0;
}
