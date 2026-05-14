#include "../include/raylib.h"
#include "../include/Graph.h" 
#include "../include/Tank.h" 

int main() {
    // 1. Configuración de la Ventana y el Grafo
    const int screenWidth = 1000;
    const int screenHeight = 700;
    InitWindow(screenWidth, screenHeight, "Tank Attack!");
    SetTargetFPS(60);

    // Creamos el grafo (Ej: 10 filas x 15 columnas)
    int filas = 10;
    int columnas = 15;
    Graph mapa(filas, columnas);
    
    // Generamos 20 obstáculos aleatorios asegurando que todo sea accesible

    // 2. Cálculos para dibujar la cuadrícula centrada
    // Dejamos un margen superior para el HUD (donde irán los tiempos y vidas)
    int hudHeight = 80; 
    
    // Calculamos de qué tamaño debe ser cada celda para que quepan todas en pantalla
    // Usamos el espacio disponible (Alto total - HUD)
    int cellSize = (screenHeight - hudHeight) / filas; 
    
    // Centramos el mapa horizontalmente
    int offsetX = (screenWidth - (columnas * cellSize)) / 2; 
    int offsetY = hudHeight;

    // Creamos un tanque de prueba
    Tank tanquePrueba(0, 0, 1, BLUE, BLUE_CYAN_TYPE); // Tanque Azul en (0,0)

    // 3. Game Loop
    while (!WindowShouldClose()) {
        
        // --- DIBUJADO ---
        BeginDrawing();
            ClearBackground(RAYWHITE); // Fondo general

            // A. DIBUJAR EL HUD (Fondo gris arriba)
            DrawRectangle(0, 0, screenWidth, hudHeight, LIGHTGRAY);
            DrawText("TANK ATTACK!", screenWidth/2 - 80, 20, 20, DARKGRAY);

            // B. DIBUJAR EL MAPA Y OBSTÁCULOS
            for (int r = 0; r < filas; r++) {
                for (int c = 0; c < columnas; c++) {
                    
                    // Calculamos las coordenadas X e Y en píxeles para este cuadrito
                    int pixelX = offsetX + (c * cellSize);
                    int pixelY = offsetY + (r * cellSize);

                    // Preguntamos al grafo de tu compañero si hay obstáculo
                    if (mapa.isObstacle(r, c)) {
                        // Dibujar Pared (Gris oscuro)
                        DrawRectangle(pixelX, pixelY, cellSize, cellSize, DARKGRAY);
                    } else {
                        // Dibujar Camino (Gris claro/arena)
                        DrawRectangle(pixelX, pixelY, cellSize, cellSize, DARKBROWN);
                    }

                    // Dibujar los bordes de la cuadrícula (opcional, se ve bien)
                    DrawRectangleLines(pixelX, pixelY, cellSize, cellSize, BLACK);
                }
            }

            // C. DIBUJAR EL TANQUE
            tanquePrueba.Draw(cellSize, offsetX, offsetY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}