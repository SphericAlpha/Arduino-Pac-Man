class pac_ghost
{
  public:
  pac_ghost();
  pac_ghost(int start_x, int start_y, int g_handle, int anim);
  void ghost_update(int pacTile_x, int pacTile_y);
  
  int x, y;

  int g_tile_x;
  int g_tile_y;

  int handle;
  int animation;
  
  int frame = 0;
  int threshold = 1;
  int default_anim = 0;
  int orig_handle;
  
  int dx, dy = 0; 
  int tempX = 0;
  int tempY = 0;

  bool doOnce = false;
  bool ghost = false;
  bool eyes = false;
  int eye_time = 0;
  int ghost_time = 0;
  long randNum;
  String ghost_direction;
};

pac_ghost::pac_ghost()
{}

pac_ghost::pac_ghost(int start_x, int start_y, int g_handle, int anim)
{
	x = start_x;
	y = start_y;
  handle = g_handle;
  orig_handle = g_handle;
  animation = anim;
  g_tile_x = (x-10)*0.125;
  g_tile_y = y*0.125;
  randomSeed(56);
}

void pac_ghost::ghost_update(int pacTile_x, int pacTile_y)
{
  GD.Begin(BITMAPS);
  // Spawn a ghost at location x+y, with a certain animation
  GD.Vertex2ii(x+3, y+8, handle, animation);

  tempX = abs((g_tile_x*8+10) - x);
  tempY = abs((g_tile_y*8) - y);

  // if blinky
  if(handle == BLINKY_HANDLE)
  {
    if(doOnce == false)
    {
      dx = -1;
      ghost_direction = "right";
      animation = 2;
      default_anim = 2;
      threshold = 3;
      doOnce = true;
    }
  }
  // if clyde
  if(handle == CLYDE_HANDLE)
  {
    if(p_collected >= 80)
    {
      if(doOnce == false)
      {
        dx = -1;
        ghost_direction = "right";
        animation = 2;
        default_anim = 2;
        threshold = 3;
        doOnce = true;
      }
    }
  }
  // if inky
  if(handle == INKY_HANDLE)
  {
    if(p_collected >= 30)
    {
      if(doOnce == false)
      {
        dx = 1;
        ghost_direction = "left";
        animation = 4;
        default_anim = 4;
        threshold = 5;
        doOnce = true;
      }
    }
  }
  // if pinky
  if(handle == PINKY_HANDLE)
  {
    if(doOnce == false)
    {
      dy = -1;
      ghost_direction = "down";
      animation = 6;
      default_anim = 6;
      threshold = 7;
      doOnce = true;
    }
  }
    
  if(mapTiles[g_tile_y][g_tile_x] == 'T' || mapTiles[g_tile_y][g_tile_x] == 'C' || mapTiles[g_tile_y][g_tile_x] == 'Q' || mapTiles[g_tile_y][g_tile_x] == 'G' && eyes == false)
  {
    while(true)
    {
      randNum = random(1, 5);
      // LEFT
      if(randNum == 1)
      {
        if(mapTiles[g_tile_y][g_tile_x-1] != 'W' && ghost_direction != "left" && tempX < 1 && tempY < 1)
        {
          dx = -1;
          dy = 0;
          ghost_direction = "right";
          // for the animation
          if(ghost == false)
          {
            animation = 2;
            default_anim = 2;
            threshold = 3;
          }
          break;
        }
        else
        {
          break;
        }
      }
      // DOWN
      else if(randNum == 2)
      {
        if(mapTiles[g_tile_y+1][g_tile_x] != 'W' && ghost_direction != "down" && tempX < 1 && tempY <1 && mapTiles[g_tile_y+1][g_tile_x] != 'D')
        {
          dy = +1;
          dx = 0;
          ghost_direction = "up";
          // for the animation
          if(ghost == false)
          {
            animation = 0;
            default_anim = 0;
            threshold = 1;
          }
          break;
        }
        else
        {
          break;
        }
      }
      // RIGHT
      else if(randNum == 3)
      {
        if(mapTiles[g_tile_y][g_tile_x+1] != 'W' && ghost_direction != "right" && tempX < 1 && tempY <1)
        {
          dx = +1;
          dy = 0;
          ghost_direction = "left";
          // for the animation
          if(ghost == false)
          {
            animation = 4;
            default_anim = 4;
            threshold = 5;
          }
          break;
        }
        else
        {
          break;
        }
      }
      // UP
      else if(randNum == 4)
      {
        if(mapTiles[g_tile_y-1][g_tile_x] != 'W' && ghost_direction != "up" && tempX < 1 && tempY <1)
        {
          dy = -1;
          dx = 0;
          ghost_direction = "down";
          // for the animation
          if(ghost == false)
          {
            animation = 6;
            default_anim = 6;
            threshold = 7;
          }
          break;
        }
        else
        {
          break;
        }
      }
    }
  }
  else if(mapTiles[g_tile_y][g_tile_x] == 'Z')
  {
    if(g_tile_x == 27)
    {
      dx = -1;
      animation = 2;
      default_anim = 2;
      threshold = 3;
    }
    else if(g_tile_x == 0)
    {
      dx = +1;
      animation = 4;
      default_anim = 4;
      threshold = 5;
    }
  }
  else if(g_tile_x == 13 && g_tile_y == 14 && tempX < 1 && tempY < 1)
  {
    dx = 0;
    dy = -1;
    animation = 6;
    default_anim = 6;
    threshold = 7;
    ghost_direction = "up";
  }
  if(mapTiles[g_tile_y+dy][g_tile_x+dx] != 'W')
  {
    x += dx;
    y += dy;
  }
  else if(tempX >= 1 || tempY >= 1)
  {
    x += dx;
    y += dy;
  }
  
  g_tile_x = (x-10)*0.125;
  g_tile_y = y*0.125;

  if(frame > 10 && ghost == false)
  {
    if(eyes != true)
    {
      frame = 0;
      animation++;
      if(animation > threshold)
      {
        animation = default_anim;
      }
    }
  }
  else if(frame > 10 && ghost == true)
  {
    if(eyes != true)
    {
      handle = GHOST_HANDLE;
      frame = 0;
      animation++;
      if(animation > 3)
      {
        animation = 0;
      }
      ghost_time++;
      if(ghost_time == 30 && ghost == true)
      {
        handle = orig_handle;
        ghost_time = 0;
        ghost = false;
      }
    }
  }
  if(eyes == true)
  {
    eye_time++;
    handle = EYES_HANDLE;
    if(g_tile_x>13)
    {
      dx = -1;
    }
    else if(g_tile_x<13)
    {
      dx = 1;
    }
    if(g_tile_y>14)
    {
      dy = -1;
    }
    else if(g_tile_y<14)
    {
      dy = 1;
    }
    if(g_tile_x == 13 && tempX < 1)
    {
      dx = 0;
    }
    if(g_tile_y == 14 && tempY < 1)
    {
      dy = 0;
    }
    if(g_tile_x == 13 && g_tile_y == 14)
    {
      x = 13*8+10;
      y = 14*8;
      eyes = false;
      ghost = true;
    }
  }
  frame++;
}
