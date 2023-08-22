#include "g2oSE3.h"

#include <string>

int main(int argc, const char **argv)
{
    std::setbuf(stdout, nullptr);

    if (argc != 4) {
        std::cout << "Usage: g2oSE3 initFilePath maxIterations resultFilePath" << std::endl;
        return 1;
    }

    std::string inFile(argv[1]);
    int maxIterations = std::stoi(argv[2]);
    std::string outFile(argv[3]);
    G2OSE3 g2Ose3;
    g2Ose3.addVertexAndEdge(inFile);
    g2Ose3.optimize(maxIterations);
    g2Ose3.writeToG2o(outFile);
    return 0;
}