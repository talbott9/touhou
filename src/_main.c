#include <gb/gb.h>
#include <stdio.h>
#include <time.h>
#include "_global.h"
#include "bg.h"
#include "assets.h"
#include "playerMovement.h"
#include "playerProjectiles.h"
#include "enemy.h"
#include "displayHP.h"
#include "collisions.h"
#include "updateSprites.h"

int quit = 0;
int resetTicks = 0;

void resetGame(void)
{
  resetTicks = 0;

  // reset health
  playerHP = 100;
  enemyHP = 500;

  // reset player position
  playerX = 80;
  playerY = 128;

  // sets bg
  set_bkg_data(0, 20, assetsTileLabel);
  set_bkg_tiles(0, 0, bgTilemapWidth, bgTilemapHeight, bgTilemap);
  SHOW_BKG;

  // set sprites 8x8 mode
  SPRITES_8x8;

  // player sprites
  set_sprite_data(1, 21, assetsTileLabel);

  set_sprite_tile(1, 1);
  set_sprite_tile(2, 2);
  set_sprite_tile(3, 3);
  set_sprite_tile(4, 4);

  // set projectile sprites
  for (i = 5; i < MAX_PROJECTILES; i++)
  { // id 5 to MAX_PROJECTILES
    set_sprite_tile(i, 6);
  }
  // spawns boss/enemy
  setEnemy();
  SHOW_SPRITES;
  DISPLAY_ON;
}

void main(void)
{
  resetGame();
  while (!quit)
  {
    if (playerHP != 0 && enemyHP != 0)
    {
      scroll_bkg(0, -1);

      // player
      displayPlayerHP();
      shootPlayerProjectiles();
      movePlayerProjectiles();
      playerMovement();

      // enemy
      displayEnemyHP();
      enemyShoot();
      moveEnemyProjectiles();
      updateEnemyProjectiles();

      // check for collision and update sprites
      checkCol();
      updateSprites();
      delay(10); // vsync();
    }
    else
    {
      if (playerHP == 0)
      {
        printf("YOU DIED");
      }
      if (enemyHP == 0)
      {
        printf("THE ENEMY DIED");
      }
      resetTicks++;
      if (resetTicks > 120)
      {
        delay(10);
        resetGame();
      }
    }
  }
}
