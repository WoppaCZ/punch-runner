#include "raylib.h"
int main() {
  

  const int screenWidth = 240;
  const int screenHeight = 120;
  bool isgameover = 0;

  //PLAYER
  const int startY = 92;
  const int Groundlvl = 80;
  const float grav = 6.0f; //grav. konstanta
  const float jump = 65.0f; // zrychleni vyskoku
  const Vector2 playerDefSize = {12, 12};
  Rectangle playerRec = {20, 80, playerDefSize.x, playerDefSize.y};
  Rectangle playerCollRec;
  Vector2 playerExtra = {0,0};
  Vector2 playerPos = {16, Groundlvl-playerDefSize.y};
  float playerVelY=0.0f; // Y zrychleni
  bool isjumping = false; // jestli uz nahodou neskace
  Rectangle punch = {32,68,20,12};
  bool isPunching = 0;

  int playertextnum = 0;
  Texture2D playerTex [4];
  
  //Obstacles
  float timer= 5.0f;
  short obsCounter=0;
  short obsOpt;
  typedef struct {
    Rectangle rect;
    int type;
    bool active;
    Color col;
  } Obstacle;

  Rectangle obsOver = {240,72,12,8};
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
    
    playerTex[0] = LoadTexture("./default-blob.png");
    playerTex[1] = LoadTexture("./jump-blob.png");
    playerTex[2] = LoadTexture("./slide-blob.png");
    playerTex[3] = LoadTexture("./punch-blob.png");

    if(!isgameover){
    
      DrawRectangle(0,80,240,80, GRAY); //podlaha
      playertextnum = 0;
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
          Obstacles[obsCounter].type = 1;
          break;
        }
        case 1:{
          Obstacles[obsCounter].rect = obsUnder;
          Obstacles[obsCounter].col = RED;
          Obstacles[obsCounter].type = 2;
          break;
        }
        case 2:{
          Obstacles[obsCounter].rect = obsThrough;
          Obstacles[obsCounter].col = BLUE;
          Obstacles[obsCounter].type = 3;
          break;
        }
      }
      }
    
      // MOVES
      playerExtra.x=0;
      playerExtra.y=0;
      isPunching =0;
      //slide/stomp
      if (IsKeyDown(KEY_S)){
      playerExtra.y = -6;
      playerExtra.x = 4;
      playerPos.y = Groundlvl-playerDefSize.y;
      playerVelY=0.0f;
      isjumping = false;
      playertextnum = 2;
      }
      //jump
      if (IsKeyDown(KEY_A)){
      if(!isjumping){
      playerVelY = -jump;
      isjumping = true;
      }
      playerExtra.x = -4; 
      playerExtra.y = 4;
      playertextnum = 1;
      }
      //destroy
      if (IsKeyDown(KEY_D)){
      playerExtra.x=4;
      isPunching = 1;
      playertextnum = 3;
      }
      // ---MOVES



      // UPDATE MOVING OBJ + DRAW
      playerVelY += grav * GetFrameTime() * 15; // Apply gravity
        playerPos.y += playerVelY * GetFrameTime(); // Apply velocity
        // COLLISION
        // --- Collision (Ground) ---
        if (playerPos.y >= Groundlvl-12-playerExtra.y) {
            playerPos.y = Groundlvl-12-playerExtra.y;
            playerVelY = 0.0f;
            isjumping = false;
        }
      
        playerCollRec.x = playerPos.x-playerExtra.x;
        playerCollRec.y = playerPos.y-playerExtra.y;
        playerCollRec.width = playerDefSize.x+(playerExtra.x*2);
        playerCollRec.height = playerDefSize.y+playerExtra.y;

        // MOVEMENT
        for(int i = 0; i<5;i++){
          Obstacles[i].rect.x -= GetFrameTime()*40*gamediff;
          
          if(Obstacles[i].type==3&&CheckCollisionRecs(punch, Obstacles[i].rect)&& isPunching) Obstacles[i].rect.height = 40;
          if(CheckCollisionRecs(playerCollRec, Obstacles[i].rect))isgameover=1;
          if(Obstacles[i].rect.x<=-2) { if(Obstacles[i].active==true && GetTime()>2) score +=1; Obstacles[i].active = false;}
          if(Obstacles[i].active) DrawRectangleRec(Obstacles[i].rect,Obstacles[i].col);
        }
        // Draw Player (Green Square)
        // Note: DrawRectangle uses top-left corner as (x,y)
        DrawTexture(playerTex[playertextnum], playerCollRec.x, playerCollRec.y, WHITE);
        
        DrawText(TextFormat("%d", score), (int)120, (int)5, 20, RAYWHITE);
      // ---UPDATE MOVING OBJ
    }
    else {
    DrawText("GAME OVER!", (int)20, (int)25,20,RAYWHITE);
    DrawText("Restart game to try again.", (int)20, (int)65,10,RAYWHITE);
    DrawText("Score: ", (int)5, (int)85, 20, RAYWHITE);
    DrawText(TextFormat("%d", score), (int)100, (int)86, 20, RAYWHITE);

    }
    EndDrawing();
  }
  
  UnloadTexture(playerTex[0]);
  UnloadTexture(playerTex[1]);
  UnloadTexture(playerTex[2]);
  UnloadTexture(playerTex[3]);
  CloseWindow();
  
  return 0;
}