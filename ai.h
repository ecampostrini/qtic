#ifndef AI_H
#define AI_H

#include <utility>

class Ai
{
public:
    Ai(int _rNum, int _cNum) : rowNum(_rNum), colNum(_cNum) {};
    ~Ai();

    bool getNextMove(char **board, std::pair<int, int> &result);
private:
    int rowNum, colNum;
};

#endif // AI_H
