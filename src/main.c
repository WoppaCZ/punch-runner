#include "raylib.h"

int main() {
  
  const int screenWidth = 240;
  const int screenHeight = 120;

  const int startY = 92;
  const int Groundlvl = 80;
  const float grav = 6.0f; //grav. konstanta
  const float jump = 60.0f; // zrychleni vyskoku
  
  int playerExtraHeight = 0;
  int playerExtraWidth = 0;
  
  const Vector2 playerDefSize = {12, 12};
  Rectangle playerRec = {20, 80, playerDefSize.x, playerDefSize.y};
  Vector2 playerExtra = {0,0};
  float playerVelY=0.0f; // Y zrychleni
  bool isjumping = false; // jestli uz nahodou neskace

  InitWindow(screenWidth, screenHeight, "Punch Runner");
  
  
  
  SetTargetFPS(120);
  
  while (!WindowShouldClose()) {
  
    BeginDrawing();
  
    ClearBackground(BLACK);
  
    DrawRectangle(0,80,240,80, GRAY); //podlaha
    

    playerExtraWidth=0;
    playerExtraHeight=0;
    
     if (IsKeyDown(KEY_S)){
    playerExtraHeight = 8;
    playerExtraWidth = 4;
    playerPos.y = Groundlvl-playerHeight;
    playerVelY = 0.0f;
    isjumping = false;
    }

    if (IsKeyDown(KEY_A)){
    if(!isjumping){
      playerVelY = -jump;
    isjumping = true;
    }
    playerExtra.x = 4; playerExtra.y = -4;
    }
    else
    {
      pl
    }

    
    
    
    
    
    
     playerVelY += grav * GetFrameTime() * 15; // Apply gravity
        playerPos.y += playerVelY * GetFrameTime(); // Apply velocity

        // --- Collision (Ground) ---
        if (playerPos.y >= Groundlvl-12+playerExtraHeight) {
            playerPos.y = Groundlvl-12+playerExtraHeight;
            playerVelY = 0.0f;
            isjumping = false;
        }
;
        // --- Drawing ---
        // Draw Player (Green Square)
        // Note: DrawRectangle uses top-left corner as (x,y)
        DrawRectangle(playerPos.x-playerExtraWidth, playerPos.y-playerExtraHeight, 12+(playerExtraWidth*2), 12+playerExtraHeight*2, GREEN);

    EndDrawing();
  }
  
  
  CloseWindow();
  
  return 0;
}