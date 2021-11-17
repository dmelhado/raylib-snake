#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include "tuple"

using namespace std;

enum directions{U,D,L,R};

struct snakeNode{
    snakeNode *_next;
    snakeNode *_prev;
    pair<int,int> _position;

    explicit snakeNode(pair<int,int> position){
        _position = position;
        _prev = nullptr;
        _next = nullptr;
    }
};

class snake {
public:
    snake(int boardWidth, int boardHeight);

    ~snake();

    void move(pair<int,int> fruit);

    bool shouldGameOver();

    void turn(directions direction);

    snakeNode *getHead();

private:

    snakeNode *_head;
    snakeNode *_last;
    int _lenght;

    int _boardWidht;
    int _boardHeight;

    directions _direction;


};


#endif //SNAKE_SNAKE_H
