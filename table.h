#include "utils.h"
#include "cell.h"

using namespace std;

const string errFileNotOpen =           "cannot open file";
const string errInvalidFileFormat =     "invalid file format";
const string errUnknownColumnName =     "unknown column name";
const string errUnknownRowNum =         "unknown row number";
const string errUnknownActionType =     "unknown action type";
const string errUnsolvableCase =        "unsolvable case set";
const string errWrongTableStart =       "wrong table start";
const string errInvalidColumnName =     "invalid column name";
const string errInvalidRowNum =         "invalid row number";
const string errExprParsing =           "expression parsing error";
const string errZeroDiv =               "division by zero";

const char separator = ',';

const string add = "+";
const string sub = "-";
const string mul = "*";
const string dvd = "/";

struct Table {
    map<string, int> names;
    map<string, int> nums;
    vector<vector<string>> vals;

    vector<Cell> cells;

    int ReadFromFile(string fileName);
    int Calc();
    void Show();
};

int Table::ReadFromFile(string fileName) {
    ifstream inputFile(fileName);
    string tmp;
        
    if (!inputFile.is_open()) {
        msg(errFileNotOpen);
        return -1;
    }

    getline(inputFile, tmp);
    stringstream tmpStream(tmp);
            
    if (!getline(tmpStream, tmp, separator) || tmp != "") {
        msg(errWrongTableStart);
        return -1;
    }

    int namesCounter = 0;
    while (getline(tmpStream, tmp, separator)) {
        if (!names.insert(make_pair(tmp, namesCounter)).second || !containsOnlyLetters(tmp)) {
            msg(errInvalidColumnName);
            return -1;
        }
        namesCounter++;
    }

    int rowsCounter = 0;
    while (getline(inputFile, tmp)) {
        stringstream tmpStream(tmp);
            
        if (!getline(tmpStream, tmp, separator) || !nums.insert(make_pair(tmp, rowsCounter)).second || !containsOnlyDigits(tmp)) {
            msg(errInvalidRowNum);
            return -1;
        }

        vals.push_back({});
        namesCounter = 0;
        while (getline(tmpStream, tmp, separator)) {
            if (containsOnlyDigits(tmp)) {
                vals[rowsCounter].push_back(tmp);
            } else {
                vals[rowsCounter].push_back("-");
                cells.push_back(Cell{rowsCounter, namesCounter});
                if (cells.back().parseExpression(tmp) != 0) {
                    msg(errExprParsing);
                    return -1;
                }                       
            }
            namesCounter++;
        }

        if (namesCounter != names.size()) {
            msg(errInvalidFileFormat);
            return -1;
        }
        rowsCounter++;
    }
        
    return 0;
}

int Table::Calc() {
    int size = cells.size();

    for (int i = 0; i < cells.size(); i ++) {
        int x1, y1, x2, y2;

        if (names.count(cells[i].opName1)) {
            y1 = names[cells[i].opName1];
        } else {
            msg(errUnknownColumnName);
            return -1;
        }

        if (names.count(cells[i].opName2)) {
            y2 = names[cells[i].opName2];
        } else {
            msg(errUnknownColumnName);
            return -1;
        }
            
        if (nums.count(cells[i].opNum1)) {
            x1 = nums[cells[i].opNum1];
        } else {
            msg(errUnknownRowNum);
            return -1;
        }
            
        if (nums.count(cells[i].opNum2)) {
            x2 = nums[cells[i].opNum2];
        } else {
            msg(errUnknownRowNum);
            return -1;
        }

        if (vals[x1][y1] == "-" || vals[x2][y2] == "-") {
            continue;
        }

        if (cells[i].action == mul) {
            vals[cells[i].name][cells[i].num] = to_string(stoi(vals[x1][y1]) * stoi(vals[x2][y2]));
        } else if (cells[i].action == add) {
            vals[cells[i].name][cells[i].num] = to_string(stoi(vals[x1][y1]) + stoi(vals[x2][y2]));
        } else if (cells[i].action == sub) {
            vals[cells[i].name][cells[i].num] = to_string(stoi(vals[x1][y1]) - stoi(vals[x2][y2]));
        } else if (cells[i].action == dvd) {
            if (stoi(vals[x2][y2]) == 0) {
                msg(errZeroDiv);
                return -1;
            }
            vals[cells[i].name][cells[i].num] = to_string(stoi(vals[x1][y1]) / stoi(vals[x2][y2]));
        } else {
            msg(errUnknownActionType);
            return -1;
        }

        cells.erase(cells.begin() + i);
        break;
    }

    if (cells.size() == size) {
        msg(errUnsolvableCase);
        return -1;
    } else if (cells.size() == 0) {
        return 0;
    }

    return Calc();
}

void Table::Show() {
    map<string, int>::iterator it;
    int i;

    for (i = 0; i < names.size(); i ++) {
        for (it = names.begin(); it != names.end(); it ++) {
            if (it->second == i) {
                cout << "\t" << separator << it->first;
                break;
            }
        }
    }

    cout << endl;
    for (i = 0; i < vals.size(); i ++) {
        for (it = nums.begin(); it != nums.end(); it ++) {
            if (it->second == i) {
                cout << it->first;
                break;
            }
        }

        for (int j = 0; j < vals[i].size(); j++) {
            cout << "\t" << separator << vals[i][j];
        }
        cout << endl;
    }
}

