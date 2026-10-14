#include "raylib.h"

int main() {
  
  const int screenWidth = 240;
  const int screenHeight = 120;

  const int startY = 92;
  const int Groundlvl = 80;
  const float grav = 0.3f; //grav. k0nstanta
  const float jump = 5.0f; // zrychleni vyskoku
  
  int playerHeight = 12;
  int playerExtraWidth = 0;
  Vector2 playerPos = {20-playerExtraWidth, 80+playerHeight}; //pozice kostky
  float playerVelY=0.0f; // Y zrychleni
  bool isjumping = false; // jestli uz nahodou neskace

  InitWindow(screenWidth, screenHeight, "Slime Punch");
  
  
  
  SetTargetFPS(30);
  
  while (!WindowShouldClose()) {
  
    BeginDrawing();
  
    ClearBackground(BLACK);
  
    DrawRectangle(0,80,240,80, GRAY); //podlaha
    
    if (IsKeyPressed(KEY_A) && !isjumping){
    playerVelY = -jump;
    playerExtraWidth = -4;
    isjumping = true;
    }

     if (IsKeyPressed(KEY_S)){
    playerHeight = 8;
    playerExtraWidth = 4;
    playerPos.y = Groundlvl+playerHeight;
    playerVelY = 0.0f;
    isjumping = false;
    }
     playerExtraWidth=0;
    playerVelY += grav * GetFrameTime(); // Apply gravity
        playerPos.y += playerVelY * GetFrameTime(); // Apply velocity

        // --- Collision (Ground) ---
        if (playerPos.y >= Groundlvl+playerHeight) {
            playerPos.y = Groundlvl+playerHeight;
            playerVelY = 0.0f;
            isjumping = false;
        }

        // --- Drawing ---
        // Draw Player (Green Square)
        // Note: DrawRectangle uses top-left corner as (x,y)
        DrawRectangle(playerPos.x, playerPos.y, 12+playerExtraWidth, playerHeight, GREEN);


    EndDrawing();
  }
  
  
  CloseWindow();
  
  return 0;
}