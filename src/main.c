#include "raylib.h"
int main() {
  

  const int screenWidth = 240;
  const int screenHeight = 120;

  //PLAYER
  const int startY = 92;
  const int Groundlvl = 80;
  const float grav = 6.0f; //grav. konstanta
  const float jump = 60.0f; // zrychleni vyskoku
  const Vector2 playerDefSize = {12, 12};
  Rectangle playerRec = {20, 80, playerDefSize.x, playerDefSize.y};
  Vector2 playerExtra = {0,0};
  Vector2 playerPos = {16, Groundlvl-playerDefSize.y};
  float playerVelY=0.0f; // Y zrychleni
  bool isjumping = false; // jestli uz nahodou neskace

  //Obstacles
  float timer= 2.0f;
  short obsCounter;
  short obsOpt;
  typedef struct {
    Rectangle rect;
    bool active;
  } Obstacle;

  Rectangle obsOver = {240,72,20,12};
  Rectangle obsUnder = {240,0,20,64};
  Rectangle obsThrough = {240};
  
  Obstacle Obstacles[4];
  InitWindow(screenWidth, screenHeight, "Punch Runner");
  
  
  
  SetTargetFPS(60);
  
  while (!WindowShouldClose()) {
    
    BeginDrawing();
  
    ClearBackground(BLACK);
  
    DrawRectangle(0,80,240,80, GRAY); //podlaha

// OBSTACLES
    timer-=GetFrameTime();
    if(timer<=0){
      timer=2.0f;
      obsCounter ++;
      if(obsCounter>=5)obsCounter=1;
      Obstacles[obsCounter].active = true;
      obsOpt= GetRandomValue(0,2);
      switch(obsOpt)
      case 0:{
        Obstacles[obsCounter].rect = obsOver;

        break;
      }
      case 1:{
        Obstacles[obsCounter].rect = obsUnder;
        break;
      }
      case 2:{
        Obstacles[obsCounter].rect = obsThrough;
        break;
      }
    }
    
// MOVES
    playerExtra.x=0;
    playerExtra.y=0;
//slide/stomp
     if (IsKeyDown(KEY_S)){
    playerExtra.y = -6;
    playerExtra.x = 4;
    playerPos.y = Groundlvl-playerDefSize.y;
    playerVelY=0.0f;
    isjumping = false;
    }
//jump
    if (IsKeyDown(KEY_A)){
    if(!isjumping){
      playerVelY = -jump;
    isjumping = true;
    }
    playerExtra.x = -4; 
    playerExtra.y = 4;
    }
//destroy

// ---MOVES



// UPDATE MOVING OBJ
     playerVelY += grav * GetFrameTime() * 15; // Apply gravity
        playerPos.y += playerVelY * GetFrameTime(); // Apply velocity
        Obstacles.x -= 
        // --- Collision (Ground) ---
        if (playerPos.y >= Groundlvl-12-playerExtra.y) {
            playerPos.y = Groundlvl-12-playerExtra.y;
            playerVelY = 0.0f;
            isjumping = false;
        }
        // --- Drawing ---
        // Draw Player (Green Square)
        // Note: DrawRectangle uses top-left corner as (x,y)
        DrawRectangle(playerPos.x-playerExtra.x, playerPos.y-playerExtra.y, playerDefSize.x+(playerExtra.x*2), playerDefSize.y+(playerExtra.y), GREEN);
 // ---UPDATE MOVING OBJ
    EndDrawing();
  }
  
  
  CloseWindow();
  
  return 0;
}