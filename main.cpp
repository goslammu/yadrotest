#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <cctype>

#include "table.h"

using namespace std;

const string errNoFlagsPassed = "pass the CSV-file name through flags";
const int fileNameFlagPosition = 2;

int main(int argc, char* argv[]) {
    if (argc < fileNameFlagPosition) {
        msg(errNoFlagsPassed);
        return -1;
    }
    
    Table table;

    if (table.ReadFromFile(argv[fileNameFlagPosition - 1]) != 0) {
        return -1;
    }

    if (table.Calc() != 0) {
        return -1;
    }

    table.Show();

    return 0;
}

