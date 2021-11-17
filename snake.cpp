#include "snake.h"

//Constructor
snake::snake(int boardWidth, int boardHeight) {
    int initX = boardWidth / 2 - 3;
    int initY = boardHeight / 2;

    auto *head = new snakeNode(make_pair(initX + 2, initY));
    auto *middle = new snakeNode(make_pair(initX + 1, initY));
    auto *last = new snakeNode(make_pair(initX + 0, initY));

    head->_next = middle;
    middle->_prev = head;
    middle->_next = last;
    last->_prev = middle;

    _head = head;
    _last = last;

    _boardHeight = boardHeight;
    _boardWidht = boardWidth;

    _lenght = 3;
    _direction = R;
}

//Destructor
snake::~snake() {
    snakeNode *currentPointer = _head;
    while (currentPointer != nullptr) {
        snakeNode *nextPointer = currentPointer->_next;
        delete currentPointer;
        currentPointer = nextPointer;
    }
}

void snake::move(pair<int, int> fruit) {
    //new head
    pair<int, int> newHeadPosition;
    switch (_direction) {
        case U:
            newHeadPosition = make_pair(_head->_position.first, _head->_position.second - 1);
            break;
        case D:
            newHeadPosition = make_pair(_head->_position.first, _head->_position.second + 1);
            break;
        case L:
            newHeadPosition = make_pair(_head->_position.first - 1, _head->_position.second);
            break;
        case R:
            newHeadPosition = make_pair(_head->_position.first + 1, _head->_position.second);
            break;
    }
    auto *newHead = new snakeNode(newHeadPosition);
    newHead->_next = _head;
    _head->_prev = newHead;
    _head = newHead;

    //if the snake's head is over a fruit, it grows without popping the last node
    if (fruit == _head->_position) {
        _lenght++;
    } else {
        snakeNode *lastPointer = _last;
        _last = _last->_prev;
        _last->_next = nullptr;
        delete lastPointer;
    }
}

void snake::turn(directions direction) {
    if ((direction == U && _direction != D) ||
        (direction == D && _direction != U) ||
        (direction == L && _direction != R) ||
        (direction == R && _direction != L)) {
        _direction = direction;
    }
}

snakeNode *snake::getHead() {
    return _head;
}

bool snake::shouldGameOver() {
    bool stepOver = false;
    bool outOfBounds = false;

    snakeNode *currentPosition = _head->_next;
    while (currentPosition != nullptr && !stepOver) {
        if (currentPosition->_position == _head->_position) {
            stepOver = true;
        }
        currentPosition = currentPosition->_next;
    }
    if (_head->_position.first >= _boardWidht ||
        _head->_position.first < 0 ||
        _head->_position.second >= _boardHeight ||
        _head->_position.second < 0) {
        outOfBounds = true;
    }
    return (stepOver || outOfBounds);
}


