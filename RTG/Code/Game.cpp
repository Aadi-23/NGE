#include "Game.h"

void Game::MouseX(UINT button, UINT state, int x, int y)
{

}

void Game::Maze(int depth)
{
    if (depth == mRec) {
        F();
        return;
    }

    if (depth < 1)
    {
        double d = mLsys_16_9 ? 16. / 9. : 1.;
        glTranslated(0., 0., d * mLength);

        Draw_Node();
        mDrawCounter++;

        return;
    }
    

    Maze(depth + 1);
    Maze(depth + 1);
    Maze(depth + 1);
   
   
}


void Game::DrawMaze()
{
    //-----------------------
    Prim_Clear();
    //-----------------------
    glPushMatrix();
    //-----------------------
    mDrawCounter = mTexAutoShiftON ? SDL_GetTicks() >> 10 : 0;
    //-----------------------
    mRec = 3;
    Maze_alpha = 90.;
    glRotated(90., 0., 1., 0.);
    //-----------------------
    mRandSeed = 0;
    //-----------------------
    Draw_Node();

    //MazeBox Boundries

    // ----RL-RL   Bottom
    Maze(1); 
    Maze(2); 
    RevYaw(); 
 

    //----RR-RR    Right
    Maze(1);
    Maze(1);
    Maze(1);
    RevYaw();
    

    //------------- UP
    Maze(1);
    Maze(2);
    Maze(2);
    Maze(2);
    Maze(2);
    RevYaw();


    //-------------- Left
    Maze(1);
    Maze(1);
    Maze(1);
    Maze(3);
    Maze(3);
    RevYaw();

    //-----------   Bottom
    Maze(2);
    Maze(2);
    Maze(2);
    RevYaw();
    Maze(3);
    Maze(0);
    RevYaw();

    Maze(2);
    Maze(2);
    Yaw(180);
    Maze(0);
    Maze(0);
    RevYaw();
    Maze(2);










    glPopMatrix();
}


void Game::TextureLoader()
{

}