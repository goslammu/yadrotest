using namespace std;


const string errInvalidExprStart = "expression starts with invalid symbol";
const char exprStartSym = '=';

struct Cell {
    int name, num;
    string opName1, opName2, opNum1, opNum2, action;

    int parseExpression(string expr) {
        if (expr[0] != exprStartSym) {
            msg(errInvalidExprStart);
            return -1;
        }
        bool secondPart;
        
        for (int j = 1; j < expr.length(); j ++) {
            if (isalpha(expr[j])) {
                if (!secondPart) {
                    opName1 += expr[j];
                    continue;
                } else {
                    opName2 += expr[j];
                    continue;
                }    
            } else if (isdigit(expr[j])) {
                if (!secondPart) {
                    opNum1 += expr[j];
                    continue;
                } else {
                    opNum2 += expr[j];
                    continue;
                }
            }

            secondPart = true;
            action.push_back(expr[j]);
        }

        return 0;
    }
};