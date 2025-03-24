#ifndef SIM_H
#define SIM_H
#include <fstream>
#include <vector>

class Simulation {
public:
    void run() ;
private:
    void executeSim();
    void generateInputVectors(int parallelism);
    void renameFile(const std::string& oldFileName, const std::string& newFileName);
    void updateConstantsFile(int parallelism);
    void createLogFile(int parallelism);
    std::string intToBin(int n, int parallelism) ;
    };

#endif // SIM_H;
