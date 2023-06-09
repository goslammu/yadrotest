using namespace std;

void msg(string msgStr) {
    cout << msgStr << endl;
}

bool containsOnlyDigits(string input) {
    int i = 0;
    if (input[0] == '-') {
        i = 1;
    }

    for (; i < input.length(); i++) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

bool containsOnlyLetters(string input) {
    for (int i = 0; i < input.length(); i++) {
        if (!isalpha(input[i])) {
            return false;
        }
    }
    return true;
}