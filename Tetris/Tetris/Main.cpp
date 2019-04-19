// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>

std::wstring tetromino[7];
int boardWidth = 12;
int boardHeight = 18;
int screenWidth = 80;
int screenHeight = 30;
unsigned char *pBoard = nullptr;

void createAssets() {
    //Create Tetronimos 4x4
    tetromino[0].append(L"..X...X...X...X."); 
    tetromino[1].append(L"..X..XX...X.....");
    tetromino[2].append(L".....XX..XX.....");
    tetromino[3].append(L"..X..XX..X......");
    tetromino[4].append(L".X...XX...X.....");
    tetromino[5].append(L".X...X...XX.....");
    tetromino[6].append(L"..X...X..XX.....");
}

void createBoard(int boardWidth, int boardHeight) {
    pBoard = new unsigned char[boardWidth*boardHeight];

    for (int x = 0; x < boardWidth; x++) // Board Boundary
        for (int y = 0; y < boardHeight; y++)
            pBoard[y*boardWidth + x] = (x == 0 || x == boardWidth - 1 || y == boardHeight - 1) ? 9 : 0;

}

int rotate(int px, int py, int r) {
    switch (r % 4) {
        case 0: // 0 Degrees
            return (4 * py) + px;
        case 1: // 90 Degrees
            return 12 + py - (4 * px);
        case 2: // 180 Degrees
            return 15 - (4 * py) - px;
        case 3: // 270 Degrees
            return 3 - py + (4 * px);
    }

    return 0;
}

int main() {
    // Create Screen Buffer
    wchar_t *screen = new wchar_t[screenWidth*screenHeight];
    for (int i = 0; i < screenWidth*screenHeight; i++) screen[i] = L' ';
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); 
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    createAssets();
    createBoard(boardWidth, boardHeight); 

    bool gameOver = false;

    while (!gameOver) {
        // Draw Field
        for (int x = 0; x < boardWidth; x++)
            for (int y = 0; y < boardHeight; y++)
                screen[(y + 2)*screenWidth + (x + 2)] = L" ABCDEFG=#"[pBoard[y*boardWidth + x]];

        // Display Frame
        WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
