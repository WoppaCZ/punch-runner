#include "raylib.h"
int main() {
  

  const int screenWidth = 240;
  const int screenHeight = 120;

  //PLAYER
  const int startY = 92;
  const int Groundlvl = 80;
  const float grav = 6.0f; //grav. konstanta
  const float jump = 65.0f; // zrychleni vyskoku
  const Vector2 playerDefSize = {12, 12};
  Rectangle playerRec = {20, 80, playerDefSize.x, playerDefSize.y};
  Vector2 playerExtra = {0,0};
  Vector2 playerPos = {16, Groundlvl-playerDefSize.y};
  float playerVelY=0.0f; // Y zrychleni
  bool isjumping = false; // jestli uz nahodou neskace

  //Obstacles
  float timer= 5.0f;
  short obsCounter=0;
  short obsOpt;
  typedef struct {
    Rectangle rect;
    bool active;
    Color col;
  } Obstacle;

  Rectangle obsOver = {240,72,12,12};
  Rectangle obsUnder = {240,0,12,70};
  Rectangle obsThrough = {240,0,12,80};
  Obstacle Obstacles[5];
  //Difficulty + Score
  float gamediff=1.0f;
  int score=0;
  
  InitWindow(screenWidth, screenHeight, "Punch Runner");
  
  
  SetTargetFPS(60);
  
  while (!WindowShouldClose()) {
    
    BeginDrawing();
  
    ClearBackground(BLACK);
  
    DrawRectangle(0,80,240,80, GRAY); //podlaha

    gamediff = 1.0f + ((float)score * 0.02f);
// OBSTACLES
    timer-=GetFrameTime();
    if(timer<=0){
      timer=2.0f / (double)gamediff;
      obsCounter ++;
      if(obsCounter>=5)obsCounter=1;
      Obstacles[obsCounter].active = true;
      obsOpt= GetRandomValue(0,2);
      switch(obsOpt){
      case 0:{
        Obstacles[obsCounter].rect = obsOver;
        Obstacles[obsCounter].col = RAYWHITE;
        break;
      }
      case 1:{
        Obstacles[obsCounter].rect = obsUnder;
        Obstacles[obsCounter].col = RED;
        break;
      }
      case 2:{
        Obstacles[obsCounter].rect = obsThrough;
        Obstacles[obsCounter].col = BLUE;
        break;
      }
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



// UPDATE MOVING OBJ + DRAW
     playerVelY += grav * GetFrameTime() * 15; // Apply gravity
        playerPos.y += playerVelY * GetFrameTime(); // Apply velocity

        // --- Collision (Ground) ---
        if (playerPos.y >= Groundlvl-12-playerExtra.y) {
            playerPos.y = Groundlvl-12-playerExtra.y;
            playerVelY = 0.0f;
            isjumping = false;
        }

        for(int i = 0; i<5;i++){
          Obstacles[i].rect.x -= GetFrameTime()*40*gamediff;
          
          if(Obstacles[i].rect.x<=0) { if(Obstacles[i].active==true && GetTime()>2) score +=1; Obstacles[i].active = false;}
          if(Obstacles[i].active) DrawRectangleRec(Obstacles[i].rect,Obstacles[i].col);
        }
        // Draw Player (Green Square)
        // Note: DrawRectangle uses top-left corner as (x,y)
        DrawRectangle(playerPos.x-playerExtra.x, playerPos.y-playerExtra.y, playerDefSize.x+(playerExtra.x*2), playerDefSize.y+(playerExtra.y), GREEN);
        DrawText(TextFormat("%d", score), (int)120, (int)5, 20, RAYWHITE);
 // ---UPDATE MOVING OBJ
    EndDrawing();
  }
  
  
  CloseWindow();
  
  return 0;
}