#include <iostream>
#include <raylib.h>

#include "snake.h"

using namespace std;

void renderSquare(pair<int, int> position, Color color) {
    DrawRectangle(10 + position.first * 25, 50 + position.second * 25, 20, 20, color);
}

pair<int, int> randomFruit(snake &player, int boardWidth, int boardHeight) {
    pair<int, int> fruit = make_pair(GetRandomValue(0, boardWidth - 1), GetRandomValue(0, boardHeight - 1));

    //re-generate another fruit until it's not colliding with snake
    snakeNode *currentPosition = player.getHead();
    while (currentPosition != nullptr) {
        if (currentPosition->_position == fruit) {
            fruit = make_pair(GetRandomValue(0, boardWidth - 1), GetRandomValue(0, boardHeight - 1));
            currentPosition = player.getHead();
        } else {
            currentPosition = currentPosition->_next;
        }
    }
    return fruit;
}

int main() {

    const int boardWidth = 16;
    const int boardHeight = 16;

    const int screenWidth = 15 + boardWidth * 25;
    const int screenHeight = 55 + boardHeight * 25;

    Color backgroundColor = BLACK;
    Color textColor = WHITE;

    InitWindow(screenWidth, screenHeight, "Raylib Snake");

    double ticksPerSecond = 6;
    double tickTime = 1 / ticksPerSecond;

    int points = 0;
    snake player(boardWidth, boardHeight);
    pair<int, int> fruit = randomFruit(player, boardWidth, boardHeight);

    bool gameOver = false;

    while (!WindowShouldClose()) {
        //deltaTime: time passed between frames
        double deltaTime = GetTime();

        //reset the game
        if (IsKeyPressed(KEY_R)) {
            points = 0;
            player.~snake();
            new(&player) snake(boardWidth, boardHeight);
            fruit = randomFruit(player, boardWidth, boardHeight);
            gameOver = false;
        }

        if (!gameOver) {
            if (IsKeyPressed(KEY_UP)) {
                player.turn(U);
            }
            if (IsKeyPressed(KEY_DOWN)) {
                player.turn(D);
            }
            if (IsKeyPressed(KEY_LEFT)) {
                player.turn(L);
            }
            if (IsKeyPressed(KEY_RIGHT)) {
                player.turn(R);
            }
            if(tickTime < 0){
                player.move(fruit);
                if (player.getHead()->_position == fruit) {
                    fruit = randomFruit(player, boardWidth, boardHeight);
                    points++;
                }
                tickTime = 1 / ticksPerSecond;
            }
        }

        //player dies
        if (player.shouldGameOver()) {
            gameOver = true;
        }

        BeginDrawing();
        ClearBackground(backgroundColor);

        //Draw board
        for (int i = 0; i < boardWidth; i++) {
            for (int j = 0; j < boardHeight; j++) {
                renderSquare(make_pair(i, j), (Color) {15, 15, 15, 255});
            }
        }
        //Draw Fruit
        renderSquare(fruit, RED);

        //Draw Snake
        snakeNode *drawerNode = player.getHead();
        while (drawerNode != nullptr) {
            Color color = GREEN;
            if (gameOver) {
                color = DARKGREEN;
            }
            renderSquare(drawerNode->_position, color);
            drawerNode = drawerNode->_next;
        }
        //Draw Text and game over screen
        if (gameOver) {
            DrawRectangle(0, 0, screenWidth, 50, backgroundColor);
            DrawRectangle(0, 0, 10, screenHeight, backgroundColor);
            DrawRectangle(screenWidth - 10, 0, 10, screenHeight, backgroundColor);
            DrawRectangle(0, screenHeight - 10, screenWidth, 10, backgroundColor);
            DrawText("GAME OVER", screenWidth - 260, 5, 40, textColor);
        }
        DrawText(to_string(points).c_str(), 10, 5, 40, textColor);
        EndDrawing();

        deltaTime -= GetTime();
        tickTime += deltaTime;

    }
    return 0;
}
