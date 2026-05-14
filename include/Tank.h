#ifndef TANK_H
#define TANK_H

#include "raylib.h"

// reglas para aplicarle al tanque
enum TankType {
    BLUE_CYAN_TYPE,
    RED_YELLOW_TYPE
};

class Tank {
private:
    int gridRow;     // Fila actual en el mapa (del 0 al total de filas)
    int gridCol;     // Columna actual en el mapa
    float life;      // Vida (Inicia en 100)
    int playerOwner; // Jugador 1 o 2
    Color color;     // Color de Raylib para dibujarlo
    TankType type;   // Tipo para calcular probabilidades y daño

public:
    // Constructor
    Tank(int startRow, int startCol, int player, Color tankColor, TankType tankType);

    // Métodos principales
    void Draw(int cellSize, int offsetX, int offsetY); // Magia visual
    void MoveTo(int newRow, int newCol);
    void TakeDamage(float damageAmount);
    
    // Getters
    bool IsAlive();
    int GetRow();
    int GetCol();
    float GetLife();
};

#endif