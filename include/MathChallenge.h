#ifndef MATH_CHALLENGE_H
#define MATH_CHALLENGE_H

#include <string>

using namespace std;

class MathChallenge {
private:
    int left;
    int right;
    char op;
    int answer;

public:
    MathChallenge();
    explicit MathChallenge(int seed);
    ~MathChallenge();

    string getQuestion() const;
    int getAnswer() const;
    bool checkAnswer(int value) const;
};

#endif
