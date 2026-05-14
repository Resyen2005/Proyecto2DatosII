#include "../include/Tank.h"
#include <iostream>

// Constructor
Tank::Tank(int startRow, int startCol, int player, Color tankColor, TankType tankType) {
    gridRow = startRow;
    gridCol = startCol;
    playerOwner = player;
    color = tankColor;
    type = tankType;
    life = 100.0f; // Todos inician con 100 de vida
}

// Lógica de Raylib para dibujarlo en pantalla
void Tank::Draw(int cellSize, int offsetX, int offsetY) {
    if (!IsAlive()) return; // Si está destruido, no lo dibujamos

    // Calculamos las coordenadas reales en la pantalla (píxeles)
    // Multiplicamos su posición en la matriz por el tamaño de cada celda y sumamos el margen
    int pixelX = offsetX + (gridCol * cellSize);
    int pixelY = offsetY + (gridRow * cellSize);

    // Dibujamos el cuerpo principal del tanque (dejamos un pequeño margen para que no toque los bordes de la celda)
    int margin = cellSize * 0.15f; 
    int size = cellSize - (margin * 2);
    
    DrawRectangle(pixelX + margin, pixelY + margin, size, size, color);

    // Dibujamos la vida encima del tanque
    DrawText(TextFormat("%.0f%%", life), pixelX + margin, pixelY - 5, 10, DARKGRAY);
}

// Lógica de movimiento
void Tank::MoveTo(int newRow, int newCol) {
    gridRow = newRow;
    gridCol = newCol;
}

// Lógica de daño
void Tank::TakeDamage(float damageAmount) {
    life -= damageAmount;
    if (life < 0) life = 0;
}

// Getters
bool Tank::IsAlive() { return life > 0; }
int Tank::GetRow() { return gridRow; }
int Tank::GetCol() { return gridCol; }
float Tank::GetLife() { return life; }