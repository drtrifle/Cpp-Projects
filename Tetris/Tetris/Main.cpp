// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <Windows.h>
#include "Tetromino.h"
#include "Tetromino3x3.h"

using namespace std;

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

void renderBoard(wchar_t *screen) {
    for (int x = 0; x < boardWidth; x++)
        for (int y = 0; y < boardHeight; y++)
            screen[(y + 2)*screenWidth + (x + 2)] = L" ABCDEFG=#"[pBoard[y*boardWidth + x]];
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY) {
    // All Field cells >0 are occupied
    for (int px = 0; px < 4; px++)
        for (int py = 0; py < 4; py++) {
            // Get index into piece
            int pi = rotate(px, py, nRotation);

            // Get index into field
            int fi = (nPosY + py) * boardWidth + (nPosX + px);

            // Check that test is in bounds. Note out of bounds does
            // not necessarily mean a fail, as the long vertical piece
            // can have cells that lie outside the boundary, so we'll
            // just ignore them
            if (nPosX + px >= 0 && nPosX + px < boardWidth) {
                if (nPosY + py >= 0 && nPosY + py < boardHeight) {
                    // In Bounds so do collision check
                    if (tetromino[nTetromino][pi] != L'.' && pBoard[fi] != 0)
                        return false; // fail on first hit
                }
            }
        }

    return true;
}

int main() {
    srand((unsigned)time(0));

    // Create Screen Buffer
    wchar_t *screen = new wchar_t[screenWidth*screenHeight];
    for (int i = 0; i < screenWidth*screenHeight; i++) screen[i] = L' ';
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); 
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    createAssets();
    createBoard(boardWidth, boardHeight); 

    bool gameOver = false;
    bool bKey[4];

    //Test
    Tetromino *tetro = new Tetromino3x3();

    while (!gameOver) {
        // Game Timing 
        this_thread::sleep_for(50ms);

        // Input
        for (int k = 0; k < 4; k++)								// R   L   D Z
            bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
        // Game Logic



        // Render

        // Draw Board
        renderBoard(screen);

        // Display Frame
        WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
    }

    return 0;
}
