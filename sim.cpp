#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <cmath>
#include <sstream>
#include <cstdlib>
#include "sim.h"
using namespace std;

void Simulation::run() {
    for (int parallelism = 2; parallelism <= 8; parallelism *= 2) {
        cout << "Run program..." << endl;
        generateInputVectors(parallelism);
        updateConstantsFile(parallelism);
        executeSim();
        cout << "Sim executed" << endl;
	system("rm input_vectors.txt");
        renameFile("output_results.txt", "output_results_" + std::to_string(parallelism) + "bit.txt");
        cout << "Generate log.txt..." << endl;
        createLogFile(parallelism);
        cout << "log.txt generated!" << endl;
        }
    }


void Simulation::executeSim(){
    // Esegui lo script bash per avviare la simulazione ModelSim
    int result = system("bash runSimulation.sh");
    // Verifica il risultato dell'esecuzione dello script
    if (result == 0) {
        cout << "Simulazione avviata con successo." << endl;
    } else {
        cerr << "Errore durante l'avvio della simulazione." << endl;
        }
    }

void Simulation::generateInputVectors(int parallelism) {
    // Apri il file input_vectors.txt per la scrittura
    std::ofstream outputFile("input_vectors_" + std::to_string(parallelism) + "bit.txt");
    std::ofstream outputFile_temp("input_vectors.txt");
    std::ofstream patternFile("pattern_" + to_string(parallelism) + "bit.txt");

    double maxVal = pow(2, parallelism);

    // Genera e scrivi tutte le combinazioni di ingressi nel file
    int cnt = 0;
    for (int i = 0; i < maxVal; i++) {
        for (int j = 0; j < maxVal; j++) {
            outputFile << intToBin(i, parallelism) << " " << intToBin(j, parallelism) << std::endl;
	        outputFile_temp << intToBin(i, parallelism) << " " << intToBin(j, parallelism) << std::endl; // copio i risultati in un file tmp per farlo leggere dal testbench poi lo rimuovo
            patternFile << intToBin(i, parallelism) << " " << intToBin(j, parallelism) << " " << intToBin((i+j), parallelism + 1) << endl;

            /*Pattern newPattern(intToBin(i,parallelism), intToBin(j, parallelism), intToBin((i+j), parallelism + 1));
            patterns[cnt] = newPattern;
            cnt++;*/
        }
    }

    // Chiudi il file
    outputFile.close();
	outputFile_temp.close();
    patternFile.close();
    }

std::string Simulation::intToBin(int n, int parallelism) {
    std::string binary = "";
    for (int i = parallelism - 1; i >= 0; --i) {
        binary += ((n >> i) & 1) ? '1' : '0';
    }
    return binary;
}

void Simulation::renameFile(const std::string& oldFileName, const std::string& newFileName) {
    if (std::rename(oldFileName.c_str(), newFileName.c_str()) != 0) {
        std::cerr << "Errore durante la rinomina del file." << std::endl;
    } else {
        std::cout << "File rinominato con successo." << std::endl;
    }
}

void Simulation::updateConstantsFile(int parallelism) {
    // Apri il file constants.vhd in modalità lettura
    std::ifstream inputFile("constants.vhd");

    // Verifica se il file è stato aperto correttamente
    if (!inputFile.is_open()) {
        std::cerr << "Errore nell'apertura del file." << std::endl;
        return;
    }

    // Crea un nuovo file temporaneo per la scrittura
    std::ofstream tempFile("constants_temp.vhd");

    // Verifica se il file temporaneo è stato aperto correttamente
    if (!tempFile.is_open()) {
        std::cerr << "Errore nell'apertura del file temporaneo." << std::endl;
        inputFile.close();
        return;
    }

    // Leggi il contenuto del file riga per riga
    std::string line;
    while (std::getline(inputFile, line)) {
        // Cerca la riga contenente "constant N : natural :="
        size_t pos = line.find("constant N : natural :=");

        if (pos != std::string::npos) {
            // Trovata la riga da modificare
            // Modifica il valore di N in base al parallelismo
            std::stringstream ss;
            ss << "constant N : natural := " << parallelism << ";";
            line = ss.str();
            std::cout << line << std::endl;
        }

        // Scrivi la riga nel nuovo file temporaneo
        tempFile << line << std::endl;
    }

    // Chiudi i file
    inputFile.close();
    tempFile.close();
    // Rinomina il file temporaneo con il nome originale
    system("rm constants.vhd");
    system("mv constants_temp.vhd constants.vhd");
    }

void Simulation::createLogFile(int parallelism){
    std::ofstream logFile("log.txt", std::ios::app);
    cout << "log file creato" << endl;

    // Apri il primo file contenente valA, valB, expectedSum
    std::ifstream file1("pattern_" + to_string(parallelism) + "bit.txt");
    if (!file1.is_open()) {
        std::cerr << "Errore nell'apertura di file1.txt" << std::endl;
    }

    // Apri il secondo file contenente solo le somme
    std::ifstream file2("output_results_" + std::to_string(parallelism) + "bit.txt");
    if (!file2.is_open()) {
        std::cerr << "Errore nell'apertura di file2.txt" << std::endl;
    }

    std::string line1, line2;
    int error = 0;

    logFile << "LogFile per l'architettura a " << parallelism << "bit: " << endl;
    // Leggi entrambi i file riga per riga
    while (std::getline(file1, line1) && std::getline(file2, line2)) {
        // Estrai expectedSum dai due file
        std::istringstream iss1(line1);
        std::string valA, valB, expectedSum;
        char space;
        iss1 >> valA >> valB >> expectedSum;
        std::string expectedSumFile2 = line2;

        // Confronta i valori
        if (expectedSum != expectedSumFile2) {
            logFile << "Errore per il pattern " << valA << " " << valB << " " << expectedSum <<": valore attuale " << line2 << std::endl;
            error++;
        }
    }

    // Chiudi i file
    file1.close();
    file2.close();
    if (error > 0){
        logFile << "il logFile ha prodotto " << error << " errori" << endl;

    }
    else {
        logFile << "l'architettura non ha prodotto errori." << endl;
    }
    logFile.close();
}


