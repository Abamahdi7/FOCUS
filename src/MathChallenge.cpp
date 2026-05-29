#include "MathChallenge.h"

#include <algorithm>
#include <sstream>

using namespace std;

MathChallenge::MathChallenge() : left(13), right(4), op('-'), answer(9) {
}

MathChallenge::MathChallenge(int seed) {
    left = 8 + (seed % 10);
    right = 2 + ((seed / 3) % 8);
    op = seed % 2 == 0 ? '+' : '-';

    if (op == '+') {
        answer = left + right;
    } else {
        if (right > left) {
            swap(left, right);
        }
        answer = left - right;
    }
}

MathChallenge::~MathChallenge() {
}

string MathChallenge::getQuestion() const {
    stringstream stream;
    stream << left << " " << op << " " << right << " = ";
    return stream.str();
}

int MathChallenge::getAnswer() const {
    return answer;
}

bool MathChallenge::checkAnswer(int value) const {
    return value == answer;
}
