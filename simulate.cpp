#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
using namespace std;
class Simulation {
public:
    void run() {
          // Esegui lo script bash per avviare la simulazione ModelSim
        int result = system("bash runSimulation.sh");
        generateInputCombinations();

        // Verifica il risultato dell'esecuzione dello script
        if (result == 0) {
            cout << "Simulazione avviata con successo." << endl;
        } else {
            cerr << "Errore durante l'avvio della simulazione." << endl;
        }
    
    }

private:
    void generateInputCombinations() {
        // Apri il file input_vectors.txt per la scrittura
        std::ofstream outputFile("input_vectors.txt");

        // Genera e scrivi tutte le combinazioni di ingressi nel file
        for (int i = 0; i < 16; ++i) {
            for (int j = 0; j < 16; ++j) {
                outputFile << intToBin(i) << " " << intToBin(j) << std::endl;
            }
        }
        // Chiudi il file
        outputFile.close();
    }

    std::string intToBin(int n) {
        std::bitset<4> binaryNum(n);
        return binaryNum.to_string();
    }
};

int main() {
    // Creazione di un oggetto Simulation e avvio della simulazione
    Simulation simulation;
    simulation.run();

    return 0;
}

