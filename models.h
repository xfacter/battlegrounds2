#ifndef __MODELS_H__
#define __MODELS_H__

#include <pspgu.h>
#include "xgraphics.h"

#define CELL_LENGTH (500.0f)
#define WALL_HEIGHT (150.0f)

#define RETICLE_RADIUS (50.0f)

#define RADAR_REAL_RADIUS (5000.0f)
#define RADAR_SCREEN_RADIUS (25.0f)
#define RADAR_CENTER_X (480 - 10 - RADAR_SCREEN_RADIUS)
#define RADAR_CENTER_Y (10 + RADAR_SCREEN_RADIUS)

unsigned int TeamColor[2][4] =
{
    {
        GU_COLOR(0.0f, 0.0f, 0.3f, 1.0f), //blue
        GU_COLOR(0.3f, 0.0f, 0.0f, 1.0f), //red
        GU_COLOR(0.5f, 0.5f, 0.0f, 1.0f), //yellow
        GU_COLOR(0.0f, 0.4f, 0.0f, 1.0f) //green
    },
    {
        GU_COLOR(0.0f, 0.0f, 1.0f, 1.0f), //blue
        GU_COLOR(1.0f, 0.0f, 0.0f, 1.0f), //red
        GU_COLOR(1.0f, 1.0f, 0.0f, 1.0f), //yellow
        GU_COLOR(0.0f, 1.0f, 0.0f, 1.0f) //green
    }
};

char TeamColorName[4][8] =
{
    "Blue",
    "Red",
    "Yellow",
    "Green"
};

//#define groundCol GU_COLOR(1.0f, 1.0f, 1.0f, 1.0f)

TNVertexF __attribute__((aligned(16))) ground[6] = 
{
    { 0, 1, /*groundCol,*/ 0.0f, 0.0f, 1.0f, 0.0f,  CELL_LENGTH, 0.0f },
    { 1, 1, /*groundCol,*/ 0.0f, 0.0f, 1.0f,  CELL_LENGTH,  CELL_LENGTH, 0.0f },
    { 0, 0, /*groundCol,*/ 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f },
    
    { 0, 0, /*groundCol,*/ 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f },
    { 1, 1, /*groundCol,*/ 0.0f, 0.0f, 1.0f,  CELL_LENGTH,  CELL_LENGTH, 0.0f },
    { 1, 0, /*groundCol,*/ 0.0f, 0.0f, 1.0f,  CELL_LENGTH, 0.0f, 0.0f }
};

#define reticlecol1 GU_COLOR( 1.0f, 0.83f, 0.0f, 0.6f)
#define reticlecol2 GU_COLOR( 0.0f, 0.0f, 0.0f, 0.6f)

CNVertexF __attribute__((aligned(16))) reticle1[8] =
{
    { reticlecol1, 0.0f, 0.0f, 1.0f,                   0.0f,                   0.0f, 5.0f }, //center
    { reticlecol1, 0.0f, 0.0f, 1.0f,        -RETICLE_RADIUS,                   0.0f, 5.0f }, //pi
    { reticlecol1, 0.0f, 0.0f, 1.0f,-RETICLE_RADIUS*0.9659f, RETICLE_RADIUS*0.2588f, 5.0f }, //pi/12
    { reticlecol1, 0.0f, 0.0f, 1.0f,-RETICLE_RADIUS*0.8660f, RETICLE_RADIUS*0.5000f, 5.0f }, //pi/6
    { reticlecol1, 0.0f, 0.0f, 1.0f,-RETICLE_RADIUS*0.7071f, RETICLE_RADIUS*0.7071f, 5.0f }, //pi/4
    { reticlecol1, 0.0f, 0.0f, 1.0f,-RETICLE_RADIUS*0.5000f, RETICLE_RADIUS*0.8660f, 5.0f }, //pi/3
    { reticlecol1, 0.0f, 0.0f, 1.0f,-RETICLE_RADIUS*0.2588f, RETICLE_RADIUS*0.9659f, 5.0f }, //5pi/12
    { reticlecol1, 0.0f, 0.0f, 1.0f,                   0.0f,         RETICLE_RADIUS, 5.0f }  //pi/2
};

CNVertexF __attribute__((aligned(16))) reticle2[8] =
{
    { reticlecol2, 0.0f, 0.0f, 1.0f,                   0.0f,                   0.0f, 5.0f }, //center
    { reticlecol2, 0.0f, 0.0f, 1.0f,                   0.0f,         RETICLE_RADIUS, 5.0f }, //pi/2
    { reticlecol2, 0.0f, 0.0f, 1.0f, RETICLE_RADIUS*0.2588f, RETICLE_RADIUS*0.9659f, 5.0f }, //5pi/12
    { reticlecol2, 0.0f, 0.0f, 1.0f, RETICLE_RADIUS*0.5000f, RETICLE_RADIUS*0.8660f, 5.0f }, //pi/3
    { reticlecol2, 0.0f, 0.0f, 1.0f, RETICLE_RADIUS*0.7071f, RETICLE_RADIUS*0.7071f, 5.0f }, //pi/4
    { reticlecol2, 0.0f, 0.0f, 1.0f, RETICLE_RADIUS*0.8660f, RETICLE_RADIUS*0.5000f, 5.0f }, //pi/6
    { reticlecol2, 0.0f, 0.0f, 1.0f, RETICLE_RADIUS*0.9659f, RETICLE_RADIUS*0.2588f, 5.0f }, //pi/12
    { reticlecol2, 0.0f, 0.0f, 1.0f,         RETICLE_RADIUS,                   0.0f, 5.0f }  //pi
};

#define radarcol1 GU_COLOR(0.5f, 0.5f, 0.5f, 0.3f)
#define radarcol2 GU_COLOR(0.0f, 0.85f, 0.2f, 0.3f)

CVertexF __attribute__((aligned(16))) radar1[26] =
{
    { radarcol1,                                   RADAR_CENTER_X,                                   RADAR_CENTER_Y, 0.0f }, //center
    { radarcol1,         RADAR_CENTER_X + (RADAR_SCREEN_RADIUS+1),                                   RADAR_CENTER_Y, 0.0f }, //0
    { radarcol1, RADAR_CENTER_X + (RADAR_SCREEN_RADIUS+1)*0.9659f, RADAR_CENTER_Y + (RADAR_SCREEN_RADIUS+1)*0.2588f, 0.0f }, //23pi/12
    { radarcol1, RADAR_CENTER_X + (RADAR_SCREEN_RADIUS+1)*0.8660f, RADAR_CENTER_Y + (RADAR_SCREEN_RADIUS+1)*0.5000f, 0.0f }, //11pi/6
    { radarcol1, RADAR_CENTER_X + (RADAR_SCREEN_RADIUS+1)*0.7071f, RADAR_CENTER_Y + (RADAR_SCREEN_RADIUS+1)*0.7071f, 0.0f }, //7pi/4
    { radarcol1, RADAR_CENTER_X + (RADAR_SCREEN_RADIUS+1)*0.5000f, RADAR_CENTER_Y + (RADAR_SCREEN_RADIUS+1)*0.8660f, 0.0f }, //5pi/3
    { radarcol1, RADAR_CENTER_X + (RADAR_SCREEN_RADIUS+1)*0.2588f, RADAR_CENTER_Y + (RADAR_SCREEN_RADIUS+1)*0.9659f, 0.0f }, //19pi/12
    { radarcol1,                                   RADAR_CENTER_X,         RADAR_CENTER_Y + (RADAR_SCREEN_RADIUS+1), 0.0f }, //3pi/2
    { radarcol1, RADAR_CENTER_X - (RADAR_SCREEN_RADIUS+1)*0.2588f, RADAR_CENTER_Y + (RADAR_SCREEN_RADIUS+1)*0.9659f, 0.0f }, //17pi/12
    { radarcol1, RADAR_CENTER_X - (RADAR_SCREEN_RADIUS+1)*0.5000f, RADAR_CENTER_Y + (RADAR_SCREEN_RADIUS+1)*0.8660f, 0.0f }, //4pi/3
    { radarcol1, RADAR_CENTER_X - (RADAR_SCREEN_RADIUS+1)*0.7071f, RADAR_CENTER_Y + (RADAR_SCREEN_RADIUS+1)*0.7071f, 0.0f }, //5pi/4
    { radarcol1, RADAR_CENTER_X - (RADAR_SCREEN_RADIUS+1)*0.8660f, RADAR_CENTER_Y + (RADAR_SCREEN_RADIUS+1)*0.5000f, 0.0f }, //7pi/6
    { radarcol1, RADAR_CENTER_X - (RADAR_SCREEN_RADIUS+1)*0.9659f, RADAR_CENTER_Y + (RADAR_SCREEN_RADIUS+1)*0.2588f, 0.0f }, //13pi/12
    { radarcol1,         RADAR_CENTER_X - (RADAR_SCREEN_RADIUS+1),                                   RADAR_CENTER_Y, 0.0f }, //pi
    { radarcol1, RADAR_CENTER_X - (RADAR_SCREEN_RADIUS+1)*0.9659f, RADAR_CENTER_Y - (RADAR_SCREEN_RADIUS+1)*0.2588f, 0.0f }, //11pi/12
    { radarcol1, RADAR_CENTER_X - (RADAR_SCREEN_RADIUS+1)*0.8660f, RADAR_CENTER_Y - (RADAR_SCREEN_RADIUS+1)*0.5000f, 0.0f }, //5pi/6
    { radarcol1, RADAR_CENTER_X - (RADAR_SCREEN_RADIUS+1)*0.7071f, RADAR_CENTER_Y - (RADAR_SCREEN_RADIUS+1)*0.7071f, 0.0f }, //3pi/4
    { radarcol1, RADAR_CENTER_X - (RADAR_SCREEN_RADIUS+1)*0.5000f, RADAR_CENTER_Y - (RADAR_SCREEN_RADIUS+1)*0.8660f, 0.0f }, //2pi/3
    { radarcol1, RADAR_CENTER_X - (RADAR_SCREEN_RADIUS+1)*0.2588f, RADAR_CENTER_Y - (RADAR_SCREEN_RADIUS+1)*0.9659f, 0.0f }, //7pi/12
    { radarcol1,                                   RADAR_CENTER_X,         RADAR_CENTER_Y - (RADAR_SCREEN_RADIUS+1), 0.0f }, //pi/2
    { radarcol1, RADAR_CENTER_X + (RADAR_SCREEN_RADIUS+1)*0.2588f, RADAR_CENTER_Y - (RADAR_SCREEN_RADIUS+1)*0.9659f, 0.0f }, //5pi/12
    { radarcol1, RADAR_CENTER_X + (RADAR_SCREEN_RADIUS+1)*0.5000f, RADAR_CENTER_Y - (RADAR_SCREEN_RADIUS+1)*0.8660f, 0.0f }, //pi/3
    { radarcol1, RADAR_CENTER_X + (RADAR_SCREEN_RADIUS+1)*0.7071f, RADAR_CENTER_Y - (RADAR_SCREEN_RADIUS+1)*0.7071f, 0.0f }, //pi/4
    { radarcol1, RADAR_CENTER_X + (RADAR_SCREEN_RADIUS+1)*0.8660f, RADAR_CENTER_Y - (RADAR_SCREEN_RADIUS+1)*0.5000f, 0.0f }, //pi/6
    { radarcol1, RADAR_CENTER_X + (RADAR_SCREEN_RADIUS+1)*0.9659f, RADAR_CENTER_Y - (RADAR_SCREEN_RADIUS+1)*0.2588f, 0.0f }, //pi/12
    { radarcol1,         RADAR_CENTER_X + (RADAR_SCREEN_RADIUS+1),                                   RADAR_CENTER_Y, 0.0f }  //2pi
};

CVertexF __attribute__((aligned(16))) radar2[26] =
{
    { radarcol2,                               RADAR_CENTER_X,                               RADAR_CENTER_Y, 0.0f }, //center
    { radarcol2,         RADAR_CENTER_X + RADAR_SCREEN_RADIUS,                               RADAR_CENTER_Y, 0.0f }, //0
    { radarcol2, RADAR_CENTER_X + RADAR_SCREEN_RADIUS*0.9659f, RADAR_CENTER_Y + RADAR_SCREEN_RADIUS*0.2588f, 0.0f }, //23pi/12
    { radarcol2, RADAR_CENTER_X + RADAR_SCREEN_RADIUS*0.8660f, RADAR_CENTER_Y + RADAR_SCREEN_RADIUS*0.5000f, 0.0f }, //11pi/6
    { radarcol2, RADAR_CENTER_X + RADAR_SCREEN_RADIUS*0.7071f, RADAR_CENTER_Y + RADAR_SCREEN_RADIUS*0.7071f, 0.0f }, //7pi/4
    { radarcol2, RADAR_CENTER_X + RADAR_SCREEN_RADIUS*0.5000f, RADAR_CENTER_Y + RADAR_SCREEN_RADIUS*0.8660f, 0.0f }, //5pi/3
    { radarcol2, RADAR_CENTER_X + RADAR_SCREEN_RADIUS*0.2588f, RADAR_CENTER_Y + RADAR_SCREEN_RADIUS*0.9659f, 0.0f }, //19pi/12
    { radarcol2,                               RADAR_CENTER_X,         RADAR_CENTER_Y + RADAR_SCREEN_RADIUS, 0.0f }, //3pi/2
    { radarcol2, RADAR_CENTER_X - RADAR_SCREEN_RADIUS*0.2588f, RADAR_CENTER_Y + RADAR_SCREEN_RADIUS*0.9659f, 0.0f }, //17pi/12
    { radarcol2, RADAR_CENTER_X - RADAR_SCREEN_RADIUS*0.5000f, RADAR_CENTER_Y + RADAR_SCREEN_RADIUS*0.8660f, 0.0f }, //4pi/3
    { radarcol2, RADAR_CENTER_X - RADAR_SCREEN_RADIUS*0.7071f, RADAR_CENTER_Y + RADAR_SCREEN_RADIUS*0.7071f, 0.0f }, //5pi/4
    { radarcol2, RADAR_CENTER_X - RADAR_SCREEN_RADIUS*0.8660f, RADAR_CENTER_Y + RADAR_SCREEN_RADIUS*0.5000f, 0.0f }, //7pi/6
    { radarcol2, RADAR_CENTER_X - RADAR_SCREEN_RADIUS*0.9659f, RADAR_CENTER_Y + RADAR_SCREEN_RADIUS*0.2588f, 0.0f }, //13pi/12
    { radarcol2,         RADAR_CENTER_X - RADAR_SCREEN_RADIUS,                               RADAR_CENTER_Y, 0.0f }, //pi
    { radarcol2, RADAR_CENTER_X - RADAR_SCREEN_RADIUS*0.9659f, RADAR_CENTER_Y - RADAR_SCREEN_RADIUS*0.2588f, 0.0f }, //11pi/12
    { radarcol2, RADAR_CENTER_X - RADAR_SCREEN_RADIUS*0.8660f, RADAR_CENTER_Y - RADAR_SCREEN_RADIUS*0.5000f, 0.0f }, //5pi/6
    { radarcol2, RADAR_CENTER_X - RADAR_SCREEN_RADIUS*0.7071f, RADAR_CENTER_Y - RADAR_SCREEN_RADIUS*0.7071f, 0.0f }, //3pi/4
    { radarcol2, RADAR_CENTER_X - RADAR_SCREEN_RADIUS*0.5000f, RADAR_CENTER_Y - RADAR_SCREEN_RADIUS*0.8660f, 0.0f }, //2pi/3
    { radarcol2, RADAR_CENTER_X - RADAR_SCREEN_RADIUS*0.2588f, RADAR_CENTER_Y - RADAR_SCREEN_RADIUS*0.9659f, 0.0f }, //7pi/12
    { radarcol2,                               RADAR_CENTER_X,         RADAR_CENTER_Y - RADAR_SCREEN_RADIUS, 0.0f }, //pi/2
    { radarcol2, RADAR_CENTER_X + RADAR_SCREEN_RADIUS*0.2588f, RADAR_CENTER_Y - RADAR_SCREEN_RADIUS*0.9659f, 0.0f }, //5pi/12
    { radarcol2, RADAR_CENTER_X + RADAR_SCREEN_RADIUS*0.5000f, RADAR_CENTER_Y - RADAR_SCREEN_RADIUS*0.8660f, 0.0f }, //pi/3
    { radarcol2, RADAR_CENTER_X + RADAR_SCREEN_RADIUS*0.7071f, RADAR_CENTER_Y - RADAR_SCREEN_RADIUS*0.7071f, 0.0f }, //pi/4
    { radarcol2, RADAR_CENTER_X + RADAR_SCREEN_RADIUS*0.8660f, RADAR_CENTER_Y - RADAR_SCREEN_RADIUS*0.5000f, 0.0f }, //pi/6
    { radarcol2, RADAR_CENTER_X + RADAR_SCREEN_RADIUS*0.9659f, RADAR_CENTER_Y - RADAR_SCREEN_RADIUS*0.2588f, 0.0f }, //pi/12
    { radarcol2,         RADAR_CENTER_X + RADAR_SCREEN_RADIUS,                               RADAR_CENTER_Y, 0.0f }  //2pi
};

#define radarlinescol GU_COLOR(0.0f, 0.0f, 0.0f, 0.3f)

CVertexF __attribute__((aligned(16))) radarlines[4] =
{
    { radarlinescol, RADAR_CENTER_X - RADAR_SCREEN_RADIUS, RADAR_CENTER_Y, 0 },
    { radarlinescol, RADAR_CENTER_X + RADAR_SCREEN_RADIUS, RADAR_CENTER_Y, 0 },
    
    { radarlinescol, RADAR_CENTER_X, RADAR_CENTER_Y - RADAR_SCREEN_RADIUS, 0 },
    { radarlinescol, RADAR_CENTER_X, RADAR_CENTER_Y + RADAR_SCREEN_RADIUS, 0 }
};

#define cellCol GU_COLOR(0.3f, 0.3f, 0.3f, 1.0f)

ScePspFVector3 cellPos = {CELL_LENGTH/2, CELL_LENGTH/2, 0.0f};

TNVertexF __attribute__((aligned(16))) cell[10*3] =
{
    //roof
    { 0, 1, 0.0f, 0.0f, 1.0f, -CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f, WALL_HEIGHT },
    { 1, 1, 0.0f, 0.0f, 1.0f,  CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f, WALL_HEIGHT },
    { 0, 0, 0.0f, 0.0f, 1.0f, -CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f, WALL_HEIGHT },
    
    { 0, 0, 0.0f, 0.0f, 1.0f, -CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f, WALL_HEIGHT },
    { 1, 1, 0.0f, 0.0f, 1.0f,  CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f, WALL_HEIGHT },
    { 1, 0, 0.0f, 0.0f, 1.0f,  CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f, WALL_HEIGHT },
    
    //top
    { 1, 0, 0.0f, 1.0f, 0.0f, -CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f,        0.0f },
    { 0, 0, 0.0f, 1.0f, 0.0f,  CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f,        0.0f },
    { 0, 1, 0.0f, 1.0f, 0.0f,  CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f, WALL_HEIGHT },
    
    { 1, 0, 0.0f, 1.0f, 0.0f, -CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f,        0.0f },
    { 0, 1, 0.0f, 1.0f, 0.0f,  CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f, WALL_HEIGHT },
    { 1, 1, 0.0f, 1.0f, 0.0f, -CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f, WALL_HEIGHT },
    
    //bottom
    { 1, 1, 0.0f,-1.0f, 0.0f,  CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f,  WALL_HEIGHT },
    { 1, 0, 0.0f,-1.0f, 0.0f,  CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f,         0.0f },
    { 0, 0, 0.0f,-1.0f, 0.0f, -CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f,         0.0f },
    
    { 0, 1, 0.0f,-1.0f, 0.0f, -CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f,  WALL_HEIGHT },
    { 1, 1, 0.0f,-1.0f, 0.0f,  CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f,  WALL_HEIGHT },
    { 0, 0, 0.0f,-1.0f, 0.0f, -CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f,         0.0f },
    
    //left
    { 0, 0,-1.0f, 0.0f, 0.0f, -CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f,        0.0f },
    { 0, 1,-1.0f, 0.0f, 0.0f, -CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f, WALL_HEIGHT },
    { 1, 0,-1.0f, 0.0f, 0.0f, -CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f, WALL_HEIGHT },
    
    { 1, 0,-1.0f, 0.0f, 0.0f, -CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f,        0.0f },
    { 0, 0,-1.0f, 0.0f, 0.0f, -CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f,        0.0f },
    { 1, 1,-1.0f, 0.0f, 0.0f, -CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f, WALL_HEIGHT },
    
    //right
    { 0, 1, 1.0f, 0.0f, 0.0f,  CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f, WALL_HEIGHT },
    { 1, 1, 1.0f, 0.0f, 0.0f,  CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f, WALL_HEIGHT },
    { 1, 0, 1.0f, 0.0f, 0.0f,  CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f,        0.0f },
    
    { 0, 1, 1.0f, 0.0f, 0.0f,  CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f, WALL_HEIGHT },
    { 1, 0, 1.0f, 0.0f, 0.0f,  CELL_LENGTH/2.0f,  CELL_LENGTH/2.0f,        0.0f },
    { 0, 0, 1.0f, 0.0f, 0.0f,  CELL_LENGTH/2.0f, -CELL_LENGTH/2.0f,        0.0f }
};

/*------------------------------
 roundcell detailed information:
    Number of VertexFs: 49
    Number of Edges: 216
    Number of Faces: 72
------------------------------*/

/* roundcell Material */
//#define roundcellcol GU_COLOR(150,150,150,255)
#define roundcellcol GU_COLOR(0.3f, 0.3f, 0.3f, 1.0f)

//ScePspFVector3 roundcellPos = {CELL_LENGTH/2, CELL_LENGTH/2, 0.0f};

CNVertexF __attribute__((aligned(16))) roundcell[72*3] = {   /* roundcell 3D Model Code Start */
  /* (Face 1 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.0,0.0,0.0},  //CNVertexF 1
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.0,0.0,1.0},  //CNVertexF 25
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,0.258819,1.0},  //CNVertexF 26
  /* (Face 2 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.0,0.0,0.0},  //CNVertexF 1
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,0.258819,1.0},  //CNVertexF 26
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,0.258819,0.0},  //CNVertexF 2
  /* (Face 3 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,0.258819,0.0},  //CNVertexF 2
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,0.258819,1.0},  //CNVertexF 26
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,0.5,1.0},  //CNVertexF 27
  /* (Face 4 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,0.258819,0.0},  //CNVertexF 2
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,0.5,1.0},  //CNVertexF 27
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,0.5,0.0},  //CNVertexF 3
  /* (Face 5 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,0.5,0.0},  //CNVertexF 3
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,0.5,1.0},  //CNVertexF 27
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707107,0.707107,1.0},  //CNVertexF 28
  /* (Face 6 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,0.5,0.0},  //CNVertexF 3
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707107,0.707107,1.0},  //CNVertexF 28
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707107,0.707107,0.0},  //CNVertexF 4
  /* (Face 7 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707107,0.707107,0.0},  //CNVertexF 4
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707107,0.707107,1.0},  //CNVertexF 28
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,0.866025,1.0},  //CNVertexF 29
  /* (Face 8 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707107,0.707107,0.0},  //CNVertexF 4
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,0.866025,1.0},  //CNVertexF 29
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,0.866025,0.0},  //CNVertexF 5
  /* (Face 9 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,0.866025,0.0},  //CNVertexF 5
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,0.866025,1.0},  //CNVertexF 29
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,0.965926,1.0},  //CNVertexF 30
  /* (Face 10 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,0.866025,0.0},  //CNVertexF 5
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,0.965926,1.0},  //CNVertexF 30
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,0.965926,0.0},  //CNVertexF 6
  /* (Face 11 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,0.965926,0.0},  //CNVertexF 6
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,0.965926,1.0},  //CNVertexF 30
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.19209e-007,1.0,1.0},  //CNVertexF 31
  /* (Face 12 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,0.965926,0.0},  //CNVertexF 6
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.19209e-007,1.0,1.0},  //CNVertexF 31
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.19209e-007,1.0,0.0},  //CNVertexF 7
  /* (Face 13 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.19209e-007,1.0,0.0},  //CNVertexF 7
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.19209e-007,1.0,1.0},  //CNVertexF 31
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,0.965926,1.0},  //CNVertexF 32
  /* (Face 14 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.19209e-007,1.0,0.0},  //CNVertexF 7
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,0.965926,1.0},  //CNVertexF 32
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,0.965926,0.0},  //CNVertexF 8
  /* (Face 15 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,0.965926,0.0},  //CNVertexF 8
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,0.965926,1.0},  //CNVertexF 32
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,0.866025,1.0},  //CNVertexF 33
  /* (Face 16 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,0.965926,0.0},  //CNVertexF 8
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,0.866025,1.0},  //CNVertexF 33
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,0.866025,0.0},  //CNVertexF 9
  /* (Face 17 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,0.866025,0.0},  //CNVertexF 9
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,0.866025,1.0},  //CNVertexF 33
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,0.707107,1.0},  //CNVertexF 34
  /* (Face 18 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,0.866025,0.0},  //CNVertexF 9
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,0.707107,1.0},  //CNVertexF 34
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,0.707107,0.0},  //CNVertexF 10
  /* (Face 19 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,0.707107,0.0},  //CNVertexF 10
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,0.707107,1.0},  //CNVertexF 34
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866025,0.5,1.0},  //CNVertexF 35
  /* (Face 20 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,0.707107,0.0},  //CNVertexF 10
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866025,0.5,1.0},  //CNVertexF 35
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866025,0.5,0.0},  //CNVertexF 11
  /* (Face 21 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866025,0.5,0.0},  //CNVertexF 11
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866025,0.5,1.0},  //CNVertexF 35
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,0.258819,1.0},  //CNVertexF 36
  /* (Face 22 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866025,0.5,0.0},  //CNVertexF 11
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,0.258819,1.0},  //CNVertexF 36
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,0.258819,0.0},  //CNVertexF 12
  /* (Face 23 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,0.258819,0.0},  //CNVertexF 12
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,0.258819,1.0},  //CNVertexF 36
  {roundcellcol, 0.0f, 0.0f, 0.0f, -1.0,3.57628e-007,1.0},  //CNVertexF 37
  /* (Face 24 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,0.258819,0.0},  //CNVertexF 12
  {roundcellcol, 0.0f, 0.0f, 0.0f, -1.0,3.57628e-007,1.0},  //CNVertexF 37
  {roundcellcol, 0.0f, 0.0f, 0.0f, -1.0,3.57628e-007,0.0},  //CNVertexF 13
  /* (Face 25 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -1.0,3.57628e-007,0.0},  //CNVertexF 13
  {roundcellcol, 0.0f, 0.0f, 0.0f, -1.0,3.57628e-007,1.0},  //CNVertexF 37
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,-0.258819,1.0},  //CNVertexF 38
  /* (Face 26 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -1.0,3.57628e-007,0.0},  //CNVertexF 13
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,-0.258819,1.0},  //CNVertexF 38
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,-0.258819,0.0},  //CNVertexF 14
  /* (Face 27 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,-0.258819,0.0},  //CNVertexF 14
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,-0.258819,1.0},  //CNVertexF 38
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866026,-0.5,1.0},  //CNVertexF 39
  /* (Face 28 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,-0.258819,0.0},  //CNVertexF 14
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866026,-0.5,1.0},  //CNVertexF 39
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866026,-0.5,0.0},  //CNVertexF 15
  /* (Face 29 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866026,-0.5,0.0},  //CNVertexF 15
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866026,-0.5,1.0},  //CNVertexF 39
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,-0.707106,1.0},  //CNVertexF 40
  /* (Face 30 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866026,-0.5,0.0},  //CNVertexF 15
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,-0.707106,1.0},  //CNVertexF 40
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,-0.707106,0.0},  //CNVertexF 16
  /* (Face 31 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,-0.707106,0.0},  //CNVertexF 16
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,-0.707106,1.0},  //CNVertexF 40
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,-0.866025,1.0},  //CNVertexF 41
  /* (Face 32 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,-0.707106,0.0},  //CNVertexF 16
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,-0.866025,1.0},  //CNVertexF 41
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,-0.866025,0.0},  //CNVertexF 17
  /* (Face 33 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,-0.866025,0.0},  //CNVertexF 17
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,-0.866025,1.0},  //CNVertexF 41
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,-0.965926,1.0},  //CNVertexF 42
  /* (Face 34 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,-0.866025,0.0},  //CNVertexF 17
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,-0.965926,1.0},  //CNVertexF 42
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,-0.965926,0.0},  //CNVertexF 18
  /* (Face 35 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,-0.965926,0.0},  //CNVertexF 18
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,-0.965926,1.0},  //CNVertexF 42
  {roundcellcol, 0.0f, 0.0f, 0.0f, -4.76837e-007,-1.0,1.0},  //CNVertexF 43
  /* (Face 36 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,-0.965926,0.0},  //CNVertexF 18
  {roundcellcol, 0.0f, 0.0f, 0.0f, -4.76837e-007,-1.0,1.0},  //CNVertexF 43
  {roundcellcol, 0.0f, 0.0f, 0.0f, -4.76837e-007,-1.0,0.0},  //CNVertexF 19
  /* (Face 37 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -4.76837e-007,-1.0,0.0},  //CNVertexF 19
  {roundcellcol, 0.0f, 0.0f, 0.0f, -4.76837e-007,-1.0,1.0},  //CNVertexF 43
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,-0.965926,1.0},  //CNVertexF 44
  /* (Face 38 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, -4.76837e-007,-1.0,0.0},  //CNVertexF 19
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,-0.965926,1.0},  //CNVertexF 44
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,-0.965926,0.0},  //CNVertexF 20
  /* (Face 39 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,-0.965926,0.0},  //CNVertexF 20
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,-0.965926,1.0},  //CNVertexF 44
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,-0.866026,1.0},  //CNVertexF 45
  /* (Face 40 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,-0.965926,0.0},  //CNVertexF 20
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,-0.866026,1.0},  //CNVertexF 45
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,-0.866026,0.0},  //CNVertexF 21
  /* (Face 41 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,-0.866026,0.0},  //CNVertexF 21
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,-0.866026,1.0},  //CNVertexF 45
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707106,-0.707107,1.0},  //CNVertexF 46
  /* (Face 42 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,-0.866026,0.0},  //CNVertexF 21
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707106,-0.707107,1.0},  //CNVertexF 46
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707106,-0.707107,0.0},  //CNVertexF 22
  /* (Face 43 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707106,-0.707107,0.0},  //CNVertexF 22
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707106,-0.707107,1.0},  //CNVertexF 46
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,-0.500001,1.0},  //CNVertexF 47
  /* (Face 44 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707106,-0.707107,0.0},  //CNVertexF 22
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,-0.500001,1.0},  //CNVertexF 47
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,-0.500001,0.0},  //CNVertexF 23
  /* (Face 45 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,-0.500001,0.0},  //CNVertexF 23
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,-0.500001,1.0},  //CNVertexF 47
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,-0.25882,1.0},  //CNVertexF 48
  /* (Face 46 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,-0.500001,0.0},  //CNVertexF 23
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,-0.25882,1.0},  //CNVertexF 48
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,-0.25882,0.0},  //CNVertexF 24
  /* (Face 47 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,-0.25882,0.0},  //CNVertexF 24
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,-0.25882,1.0},  //CNVertexF 48
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.0,0.0,1.0},  //CNVertexF 25
  /* (Face 48 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,-0.25882,0.0},  //CNVertexF 24
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.0,0.0,1.0},  //CNVertexF 25
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.0,0.0,0.0},  //CNVertexF 1
  /* (Face 49 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,0.258819,1.0},  //CNVertexF 26
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.0,0.0,1.0},  //CNVertexF 25
  /* (Face 50 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,0.5,1.0},  //CNVertexF 27
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,0.258819,1.0},  //CNVertexF 26
  /* (Face 51 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707107,0.707107,1.0},  //CNVertexF 28
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,0.5,1.0},  //CNVertexF 27
  /* (Face 52 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,0.866025,1.0},  //CNVertexF 29
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707107,0.707107,1.0},  //CNVertexF 28
  /* (Face 53 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,0.965926,1.0},  //CNVertexF 30
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,0.866025,1.0},  //CNVertexF 29
  /* (Face 54 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.19209e-007,1.0,1.0},  //CNVertexF 31
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,0.965926,1.0},  //CNVertexF 30
  /* (Face 55 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,0.965926,1.0},  //CNVertexF 32
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.19209e-007,1.0,1.0},  //CNVertexF 31
  /* (Face 56 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,0.866025,1.0},  //CNVertexF 33
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,0.965926,1.0},  //CNVertexF 32
  /* (Face 57 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,0.707107,1.0},  //CNVertexF 34
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,0.866025,1.0},  //CNVertexF 33
  /* (Face 58 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866025,0.5,1.0},  //CNVertexF 35
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,0.707107,1.0},  //CNVertexF 34
  /* (Face 59 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,0.258819,1.0},  //CNVertexF 36
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866025,0.5,1.0},  //CNVertexF 35
  /* (Face 60 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, -1.0,3.57628e-007,1.0},  //CNVertexF 37
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,0.258819,1.0},  //CNVertexF 36
  /* (Face 61 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,-0.258819,1.0},  //CNVertexF 38
  {roundcellcol, 0.0f, 0.0f, 0.0f, -1.0,3.57628e-007,1.0},  //CNVertexF 37
  /* (Face 62 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866026,-0.5,1.0},  //CNVertexF 39
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.965926,-0.258819,1.0},  //CNVertexF 38
  /* (Face 63 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,-0.707106,1.0},  //CNVertexF 40
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.866026,-0.5,1.0},  //CNVertexF 39
  /* (Face 64 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,-0.866025,1.0},  //CNVertexF 41
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.707107,-0.707106,1.0},  //CNVertexF 40
  /* (Face 65 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,-0.965926,1.0},  //CNVertexF 42
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.5,-0.866025,1.0},  //CNVertexF 41
  /* (Face 66 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, -4.76837e-007,-1.0,1.0},  //CNVertexF 43
  {roundcellcol, 0.0f, 0.0f, 0.0f, -0.258819,-0.965926,1.0},  //CNVertexF 42
  /* (Face 67 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,-0.965926,1.0},  //CNVertexF 44
  {roundcellcol, 0.0f, 0.0f, 0.0f, -4.76837e-007,-1.0,1.0},  //CNVertexF 43
  /* (Face 68 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,-0.866026,1.0},  //CNVertexF 45
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.258819,-0.965926,1.0},  //CNVertexF 44
  /* (Face 69 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707106,-0.707107,1.0},  //CNVertexF 46
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.5,-0.866026,1.0},  //CNVertexF 45
  /* (Face 70 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,-0.500001,1.0},  //CNVertexF 47
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.707106,-0.707107,1.0},  //CNVertexF 46
  /* (Face 71 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,-0.25882,1.0},  //CNVertexF 48
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.866025,-0.500001,1.0},  //CNVertexF 47
  /* (Face 72 of 72) */
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.0,0.0,1.0},  //CNVertexF 49
  {roundcellcol, 0.0f, 0.0f, 0.0f, 1.0,0.0,1.0},  //CNVertexF 25
  {roundcellcol, 0.0f, 0.0f, 0.0f, 0.965926,-0.25882,1.0}  //CNVertexF 48
};   /* roundcell 3D Model Code End */

/*------------------------------
 mine detailed information:
    Number of VertexFs: 50
    Number of Edges: 288
    Number of Faces: 96
------------------------------*/

/* mine Material */
//#define minecol GU_COLOR(95,95,95,255)
#define minecol GU_COLOR(0.37f, 0.37f, 0.37f, 1.0f)

//ScePspFVector3 minePos = {0.0,0.0,0.0};

CNVertexF __attribute__((aligned(16))) mine[96*3] = {   /* mine 3D Model Code Start */
  /* (Face 1 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,0.0,0.0},  //CNVertexF 2
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,5.0,0.0},  //CNVertexF 3
  /* (Face 2 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,5.0,0.0},  //CNVertexF 3
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,8.66025,0.0},  //CNVertexF 4
  /* (Face 3 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,8.66025,0.0},  //CNVertexF 4
  {minecol, 0.0f, 0.0f, 0.0f, -4.39584e-007,10.0,0.0},  //CNVertexF 5
  /* (Face 4 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {minecol, 0.0f, 0.0f, 0.0f, -4.39584e-007,10.0,0.0},  //CNVertexF 5
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,8.66025,0.0},  //CNVertexF 6
  /* (Face 5 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,8.66025,0.0},  //CNVertexF 6
  {minecol, 0.0f, 0.0f, 0.0f, -8.66025,5.0,0.0},  //CNVertexF 7
  /* (Face 6 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {minecol, 0.0f, 0.0f, 0.0f, -8.66025,5.0,0.0},  //CNVertexF 7
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,1.50502e-006,0.0},  //CNVertexF 8
  /* (Face 7 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,1.50502e-006,0.0},  //CNVertexF 8
  {minecol, 0.0f, 0.0f, 0.0f, -8.66026,-5.0,0.0},  //CNVertexF 9
  /* (Face 8 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {minecol, 0.0f, 0.0f, 0.0f, -8.66026,-5.0,0.0},  //CNVertexF 9
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,-8.66025,0.0},  //CNVertexF 10
  /* (Face 9 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,-8.66025,0.0},  //CNVertexF 10
  {minecol, 0.0f, 0.0f, 0.0f, -4.64916e-006,-10.0,0.0},  //CNVertexF 11
  /* (Face 10 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {minecol, 0.0f, 0.0f, 0.0f, -4.64916e-006,-10.0,0.0},  //CNVertexF 11
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,-8.66026,0.0},  //CNVertexF 12
  /* (Face 11 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,-8.66026,0.0},  //CNVertexF 12
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,-5.00001,0.0},  //CNVertexF 13
  /* (Face 12 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,-5.00001,0.0},  //CNVertexF 13
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,0.0,0.0},  //CNVertexF 2
  /* (Face 13 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,0.0,0.0},  //CNVertexF 2
  {minecol, 0.0f, 0.0f, 0.0f, 20.0,0.0,0.0},  //CNVertexF 14
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,10.0,0.0},  //CNVertexF 15
  /* (Face 14 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,0.0,0.0},  //CNVertexF 2
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,10.0,0.0},  //CNVertexF 15
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,5.0,0.0},  //CNVertexF 3
  /* (Face 15 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,5.0,0.0},  //CNVertexF 3
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,10.0,0.0},  //CNVertexF 15
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,17.3205,0.0},  //CNVertexF 16
  /* (Face 16 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,5.0,0.0},  //CNVertexF 3
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,17.3205,0.0},  //CNVertexF 16
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,8.66025,0.0},  //CNVertexF 4
  /* (Face 17 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,8.66025,0.0},  //CNVertexF 4
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,17.3205,0.0},  //CNVertexF 16
  {minecol, 0.0f, 0.0f, 0.0f, -8.71718e-007,20.0,0.0},  //CNVertexF 17
  /* (Face 18 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,8.66025,0.0},  //CNVertexF 4
  {minecol, 0.0f, 0.0f, 0.0f, -8.71718e-007,20.0,0.0},  //CNVertexF 17
  {minecol, 0.0f, 0.0f, 0.0f, -4.39584e-007,10.0,0.0},  //CNVertexF 5
  /* (Face 19 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -4.39584e-007,10.0,0.0},  //CNVertexF 5
  {minecol, 0.0f, 0.0f, 0.0f, -8.71718e-007,20.0,0.0},  //CNVertexF 17
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,17.3205,0.0},  //CNVertexF 18
  /* (Face 20 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -4.39584e-007,10.0,0.0},  //CNVertexF 5
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,17.3205,0.0},  //CNVertexF 18
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,8.66025,0.0},  //CNVertexF 6
  /* (Face 21 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,8.66025,0.0},  //CNVertexF 6
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,17.3205,0.0},  //CNVertexF 18
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,10.0,0.0},  //CNVertexF 19
  /* (Face 22 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,8.66025,0.0},  //CNVertexF 6
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,10.0,0.0},  //CNVertexF 19
  {minecol, 0.0f, 0.0f, 0.0f, -8.66025,5.0,0.0},  //CNVertexF 7
  /* (Face 23 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -8.66025,5.0,0.0},  //CNVertexF 7
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,10.0,0.0},  //CNVertexF 19
  {minecol, 0.0f, 0.0f, 0.0f, -20.0,3.02494e-006,0.0},  //CNVertexF 20
  /* (Face 24 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -8.66025,5.0,0.0},  //CNVertexF 7
  {minecol, 0.0f, 0.0f, 0.0f, -20.0,3.02494e-006,0.0},  //CNVertexF 20
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,1.50502e-006,0.0},  //CNVertexF 8
  /* (Face 25 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,1.50502e-006,0.0},  //CNVertexF 8
  {minecol, 0.0f, 0.0f, 0.0f, -20.0,3.02494e-006,0.0},  //CNVertexF 20
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,-10.0,0.0},  //CNVertexF 21
  /* (Face 26 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,1.50502e-006,0.0},  //CNVertexF 8
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,-10.0,0.0},  //CNVertexF 21
  {minecol, 0.0f, 0.0f, 0.0f, -8.66026,-5.0,0.0},  //CNVertexF 9
  /* (Face 27 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -8.66026,-5.0,0.0},  //CNVertexF 9
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,-10.0,0.0},  //CNVertexF 21
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,-17.3205,0.0},  //CNVertexF 22
  /* (Face 28 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -8.66026,-5.0,0.0},  //CNVertexF 9
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,-17.3205,0.0},  //CNVertexF 22
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,-8.66025,0.0},  //CNVertexF 10
  /* (Face 29 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,-8.66025,0.0},  //CNVertexF 10
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,-17.3205,0.0},  //CNVertexF 22
  {minecol, 0.0f, 0.0f, 0.0f, -9.29832e-006,-20.0,0.0},  //CNVertexF 23
  /* (Face 30 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,-8.66025,0.0},  //CNVertexF 10
  {minecol, 0.0f, 0.0f, 0.0f, -9.29832e-006,-20.0,0.0},  //CNVertexF 23
  {minecol, 0.0f, 0.0f, 0.0f, -4.64916e-006,-10.0,0.0},  //CNVertexF 11
  /* (Face 31 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -4.64916e-006,-10.0,0.0},  //CNVertexF 11
  {minecol, 0.0f, 0.0f, 0.0f, -9.29832e-006,-20.0,0.0},  //CNVertexF 23
  {minecol, 0.0f, 0.0f, 0.0f, 9.99999,-17.3205,0.0},  //CNVertexF 24
  /* (Face 32 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -4.64916e-006,-10.0,0.0},  //CNVertexF 11
  {minecol, 0.0f, 0.0f, 0.0f, 9.99999,-17.3205,0.0},  //CNVertexF 24
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,-8.66026,0.0},  //CNVertexF 12
  /* (Face 33 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,-8.66026,0.0},  //CNVertexF 12
  {minecol, 0.0f, 0.0f, 0.0f, 9.99999,-17.3205,0.0},  //CNVertexF 24
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,-10.0,0.0},  //CNVertexF 25
  /* (Face 34 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,-8.66026,0.0},  //CNVertexF 12
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,-10.0,0.0},  //CNVertexF 25
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,-5.00001,0.0},  //CNVertexF 13
  /* (Face 35 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,-5.00001,0.0},  //CNVertexF 13
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,-10.0,0.0},  //CNVertexF 25
  {minecol, 0.0f, 0.0f, 0.0f, 20.0,0.0,0.0},  //CNVertexF 14
  /* (Face 36 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,-5.00001,0.0},  //CNVertexF 13
  {minecol, 0.0f, 0.0f, 0.0f, 20.0,0.0,0.0},  //CNVertexF 14
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,0.0,0.0},  //CNVertexF 2
  /* (Face 37 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 20.0,0.0,0.0},  //CNVertexF 14
  {minecol, 0.0f, 0.0f, 0.0f, 20.0,0.0,5.0},  //CNVertexF 26
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,10.0,5.0},  //CNVertexF 27
  /* (Face 38 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 20.0,0.0,0.0},  //CNVertexF 14
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,10.0,5.0},  //CNVertexF 27
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,10.0,0.0},  //CNVertexF 15
  /* (Face 39 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,10.0,0.0},  //CNVertexF 15
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,10.0,5.0},  //CNVertexF 27
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,17.3205,5.0},  //CNVertexF 28
  /* (Face 40 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,10.0,0.0},  //CNVertexF 15
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,17.3205,5.0},  //CNVertexF 28
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,17.3205,0.0},  //CNVertexF 16
  /* (Face 41 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,17.3205,0.0},  //CNVertexF 16
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,17.3205,5.0},  //CNVertexF 28
  {minecol, 0.0f, 0.0f, 0.0f, -8.71718e-007,20.0,5.0},  //CNVertexF 29
  /* (Face 42 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,17.3205,0.0},  //CNVertexF 16
  {minecol, 0.0f, 0.0f, 0.0f, -8.71718e-007,20.0,5.0},  //CNVertexF 29
  {minecol, 0.0f, 0.0f, 0.0f, -8.71718e-007,20.0,0.0},  //CNVertexF 17
  /* (Face 43 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -8.71718e-007,20.0,0.0},  //CNVertexF 17
  {minecol, 0.0f, 0.0f, 0.0f, -8.71718e-007,20.0,5.0},  //CNVertexF 29
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,17.3205,5.0},  //CNVertexF 30
  /* (Face 44 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -8.71718e-007,20.0,0.0},  //CNVertexF 17
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,17.3205,5.0},  //CNVertexF 30
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,17.3205,0.0},  //CNVertexF 18
  /* (Face 45 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,17.3205,0.0},  //CNVertexF 18
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,17.3205,5.0},  //CNVertexF 30
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,10.0,5.0},  //CNVertexF 31
  /* (Face 46 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,17.3205,0.0},  //CNVertexF 18
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,10.0,5.0},  //CNVertexF 31
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,10.0,0.0},  //CNVertexF 19
  /* (Face 47 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,10.0,0.0},  //CNVertexF 19
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,10.0,5.0},  //CNVertexF 31
  {minecol, 0.0f, 0.0f, 0.0f, -20.0,3.02494e-006,5.0},  //CNVertexF 32
  /* (Face 48 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,10.0,0.0},  //CNVertexF 19
  {minecol, 0.0f, 0.0f, 0.0f, -20.0,3.02494e-006,5.0},  //CNVertexF 32
  {minecol, 0.0f, 0.0f, 0.0f, -20.0,3.02494e-006,0.0},  //CNVertexF 20
  /* (Face 49 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -20.0,3.02494e-006,0.0},  //CNVertexF 20
  {minecol, 0.0f, 0.0f, 0.0f, -20.0,3.02494e-006,5.0},  //CNVertexF 32
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,-10.0,5.0},  //CNVertexF 33
  /* (Face 50 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -20.0,3.02494e-006,0.0},  //CNVertexF 20
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,-10.0,5.0},  //CNVertexF 33
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,-10.0,0.0},  //CNVertexF 21
  /* (Face 51 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,-10.0,0.0},  //CNVertexF 21
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,-10.0,5.0},  //CNVertexF 33
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,-17.3205,5.0},  //CNVertexF 34
  /* (Face 52 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,-10.0,0.0},  //CNVertexF 21
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,-17.3205,5.0},  //CNVertexF 34
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,-17.3205,0.0},  //CNVertexF 22
  /* (Face 53 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,-17.3205,0.0},  //CNVertexF 22
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,-17.3205,5.0},  //CNVertexF 34
  {minecol, 0.0f, 0.0f, 0.0f, -9.29832e-006,-20.0,5.0},  //CNVertexF 35
  /* (Face 54 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,-17.3205,0.0},  //CNVertexF 22
  {minecol, 0.0f, 0.0f, 0.0f, -9.29832e-006,-20.0,5.0},  //CNVertexF 35
  {minecol, 0.0f, 0.0f, 0.0f, -9.29832e-006,-20.0,0.0},  //CNVertexF 23
  /* (Face 55 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -9.29832e-006,-20.0,0.0},  //CNVertexF 23
  {minecol, 0.0f, 0.0f, 0.0f, -9.29832e-006,-20.0,5.0},  //CNVertexF 35
  {minecol, 0.0f, 0.0f, 0.0f, 9.99999,-17.3205,5.0},  //CNVertexF 36
  /* (Face 56 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -9.29832e-006,-20.0,0.0},  //CNVertexF 23
  {minecol, 0.0f, 0.0f, 0.0f, 9.99999,-17.3205,5.0},  //CNVertexF 36
  {minecol, 0.0f, 0.0f, 0.0f, 9.99999,-17.3205,0.0},  //CNVertexF 24
  /* (Face 57 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 9.99999,-17.3205,0.0},  //CNVertexF 24
  {minecol, 0.0f, 0.0f, 0.0f, 9.99999,-17.3205,5.0},  //CNVertexF 36
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,-10.0,5.0},  //CNVertexF 37
  /* (Face 58 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 9.99999,-17.3205,0.0},  //CNVertexF 24
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,-10.0,5.0},  //CNVertexF 37
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,-10.0,0.0},  //CNVertexF 25
  /* (Face 59 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,-10.0,0.0},  //CNVertexF 25
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,-10.0,5.0},  //CNVertexF 37
  {minecol, 0.0f, 0.0f, 0.0f, 20.0,0.0,5.0},  //CNVertexF 26
  /* (Face 60 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,-10.0,0.0},  //CNVertexF 25
  {minecol, 0.0f, 0.0f, 0.0f, 20.0,0.0,5.0},  //CNVertexF 26
  {minecol, 0.0f, 0.0f, 0.0f, 20.0,0.0,0.0},  //CNVertexF 14
  /* (Face 61 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 20.0,0.0,5.0},  //CNVertexF 26
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,0.0,10.0},  //CNVertexF 38
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,5.0,10.0},  //CNVertexF 39
  /* (Face 62 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 20.0,0.0,5.0},  //CNVertexF 26
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,5.0,10.0},  //CNVertexF 39
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,10.0,5.0},  //CNVertexF 27
  /* (Face 63 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,10.0,5.0},  //CNVertexF 27
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,5.0,10.0},  //CNVertexF 39
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,8.66025,10.0},  //CNVertexF 40
  /* (Face 64 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,10.0,5.0},  //CNVertexF 27
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,8.66025,10.0},  //CNVertexF 40
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,17.3205,5.0},  //CNVertexF 28
  /* (Face 65 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,17.3205,5.0},  //CNVertexF 28
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,8.66025,10.0},  //CNVertexF 40
  {minecol, 0.0f, 0.0f, 0.0f, -4.39584e-007,10.0,10.0},  //CNVertexF 41
  /* (Face 66 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,17.3205,5.0},  //CNVertexF 28
  {minecol, 0.0f, 0.0f, 0.0f, -4.39584e-007,10.0,10.0},  //CNVertexF 41
  {minecol, 0.0f, 0.0f, 0.0f, -8.71718e-007,20.0,5.0},  //CNVertexF 29
  /* (Face 67 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -8.71718e-007,20.0,5.0},  //CNVertexF 29
  {minecol, 0.0f, 0.0f, 0.0f, -4.39584e-007,10.0,10.0},  //CNVertexF 41
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,8.66025,10.0},  //CNVertexF 42
  /* (Face 68 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -8.71718e-007,20.0,5.0},  //CNVertexF 29
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,8.66025,10.0},  //CNVertexF 42
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,17.3205,5.0},  //CNVertexF 30
  /* (Face 69 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,17.3205,5.0},  //CNVertexF 30
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,8.66025,10.0},  //CNVertexF 42
  {minecol, 0.0f, 0.0f, 0.0f, -8.66025,5.0,10.0},  //CNVertexF 43
  /* (Face 70 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,17.3205,5.0},  //CNVertexF 30
  {minecol, 0.0f, 0.0f, 0.0f, -8.66025,5.0,10.0},  //CNVertexF 43
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,10.0,5.0},  //CNVertexF 31
  /* (Face 71 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,10.0,5.0},  //CNVertexF 31
  {minecol, 0.0f, 0.0f, 0.0f, -8.66025,5.0,10.0},  //CNVertexF 43
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,1.50502e-006,10.0},  //CNVertexF 44
  /* (Face 72 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,10.0,5.0},  //CNVertexF 31
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,1.50502e-006,10.0},  //CNVertexF 44
  {minecol, 0.0f, 0.0f, 0.0f, -20.0,3.02494e-006,5.0},  //CNVertexF 32
  /* (Face 73 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -20.0,3.02494e-006,5.0},  //CNVertexF 32
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,1.50502e-006,10.0},  //CNVertexF 44
  {minecol, 0.0f, 0.0f, 0.0f, -8.66026,-5.0,10.0},  //CNVertexF 45
  /* (Face 74 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -20.0,3.02494e-006,5.0},  //CNVertexF 32
  {minecol, 0.0f, 0.0f, 0.0f, -8.66026,-5.0,10.0},  //CNVertexF 45
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,-10.0,5.0},  //CNVertexF 33
  /* (Face 75 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,-10.0,5.0},  //CNVertexF 33
  {minecol, 0.0f, 0.0f, 0.0f, -8.66026,-5.0,10.0},  //CNVertexF 45
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,-8.66025,10.0},  //CNVertexF 46
  /* (Face 76 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -17.3205,-10.0,5.0},  //CNVertexF 33
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,-8.66025,10.0},  //CNVertexF 46
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,-17.3205,5.0},  //CNVertexF 34
  /* (Face 77 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,-17.3205,5.0},  //CNVertexF 34
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,-8.66025,10.0},  //CNVertexF 46
  {minecol, 0.0f, 0.0f, 0.0f, -4.64916e-006,-10.0,10.0},  //CNVertexF 47
  /* (Face 78 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,-17.3205,5.0},  //CNVertexF 34
  {minecol, 0.0f, 0.0f, 0.0f, -4.64916e-006,-10.0,10.0},  //CNVertexF 47
  {minecol, 0.0f, 0.0f, 0.0f, -9.29832e-006,-20.0,5.0},  //CNVertexF 35
  /* (Face 79 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -9.29832e-006,-20.0,5.0},  //CNVertexF 35
  {minecol, 0.0f, 0.0f, 0.0f, -4.64916e-006,-10.0,10.0},  //CNVertexF 47
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,-8.66026,10.0},  //CNVertexF 48
  /* (Face 80 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, -9.29832e-006,-20.0,5.0},  //CNVertexF 35
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,-8.66026,10.0},  //CNVertexF 48
  {minecol, 0.0f, 0.0f, 0.0f, 9.99999,-17.3205,5.0},  //CNVertexF 36
  /* (Face 81 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 9.99999,-17.3205,5.0},  //CNVertexF 36
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,-8.66026,10.0},  //CNVertexF 48
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,-5.00001,10.0},  //CNVertexF 49
  /* (Face 82 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 9.99999,-17.3205,5.0},  //CNVertexF 36
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,-5.00001,10.0},  //CNVertexF 49
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,-10.0,5.0},  //CNVertexF 37
  /* (Face 83 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,-10.0,5.0},  //CNVertexF 37
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,-5.00001,10.0},  //CNVertexF 49
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,0.0,10.0},  //CNVertexF 38
  /* (Face 84 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 17.3205,-10.0,5.0},  //CNVertexF 37
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,0.0,10.0},  //CNVertexF 38
  {minecol, 0.0f, 0.0f, 0.0f, 20.0,0.0,5.0},  //CNVertexF 26
  /* (Face 85 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,10.0},  //CNVertexF 50
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,5.0,10.0},  //CNVertexF 39
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,0.0,10.0},  //CNVertexF 38
  /* (Face 86 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,10.0},  //CNVertexF 50
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,8.66025,10.0},  //CNVertexF 40
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,5.0,10.0},  //CNVertexF 39
  /* (Face 87 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,10.0},  //CNVertexF 50
  {minecol, 0.0f, 0.0f, 0.0f, -4.39584e-007,10.0,10.0},  //CNVertexF 41
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,8.66025,10.0},  //CNVertexF 40
  /* (Face 88 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,10.0},  //CNVertexF 50
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,8.66025,10.0},  //CNVertexF 42
  {minecol, 0.0f, 0.0f, 0.0f, -4.39584e-007,10.0,10.0},  //CNVertexF 41
  /* (Face 89 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,10.0},  //CNVertexF 50
  {minecol, 0.0f, 0.0f, 0.0f, -8.66025,5.0,10.0},  //CNVertexF 43
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,8.66025,10.0},  //CNVertexF 42
  /* (Face 90 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,10.0},  //CNVertexF 50
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,1.50502e-006,10.0},  //CNVertexF 44
  {minecol, 0.0f, 0.0f, 0.0f, -8.66025,5.0,10.0},  //CNVertexF 43
  /* (Face 91 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,10.0},  //CNVertexF 50
  {minecol, 0.0f, 0.0f, 0.0f, -8.66026,-5.0,10.0},  //CNVertexF 45
  {minecol, 0.0f, 0.0f, 0.0f, -10.0,1.50502e-006,10.0},  //CNVertexF 44
  /* (Face 92 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,10.0},  //CNVertexF 50
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,-8.66025,10.0},  //CNVertexF 46
  {minecol, 0.0f, 0.0f, 0.0f, -8.66026,-5.0,10.0},  //CNVertexF 45
  /* (Face 93 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,10.0},  //CNVertexF 50
  {minecol, 0.0f, 0.0f, 0.0f, -4.64916e-006,-10.0,10.0},  //CNVertexF 47
  {minecol, 0.0f, 0.0f, 0.0f, -5.0,-8.66025,10.0},  //CNVertexF 46
  /* (Face 94 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,10.0},  //CNVertexF 50
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,-8.66026,10.0},  //CNVertexF 48
  {minecol, 0.0f, 0.0f, 0.0f, -4.64916e-006,-10.0,10.0},  //CNVertexF 47
  /* (Face 95 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,10.0},  //CNVertexF 50
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,-5.00001,10.0},  //CNVertexF 49
  {minecol, 0.0f, 0.0f, 0.0f, 5.0,-8.66026,10.0},  //CNVertexF 48
  /* (Face 96 of 96) */
  {minecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,10.0},  //CNVertexF 50
  {minecol, 0.0f, 0.0f, 0.0f, 10.0,0.0,10.0},  //CNVertexF 38
  {minecol, 0.0f, 0.0f, 0.0f, 8.66025,-5.00001,10.0}  //CNVertexF 49
};   /* mine 3D Model Code End */

/*------------------------------
 Stripe detailed information:
    Number of VertexFs: 9
    Number of Edges: 21
    Number of Faces: 7
------------------------------*/

/* Stripe Material */
//#define Stripecol GU_COLOR(150,150,150,255)

//ScePspFVector3 StripePos = {0.53397,0.00334549,-8.06675};

NVertexF __attribute__((aligned(16))) Stripe[7*3] = {   /* Stripe 3D Model Code Start */
  /* (Face 1 of 7) */
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -10.9187,-2.41066,68.6391},  //CNVertexF 2
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -11.0101,1.95123,68.6391},  //CNVertexF 3
  /* (Face 2 of 7) */
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -11.0101,1.95123,68.6391},  //CNVertexF 3
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -19.3212,-4.26579,60.9052},  //CNVertexF 4
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -19.4829,3.4528,60.9052},  //CNVertexF 5
  /* (Face 3 of 7) */
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -11.0101,1.95123,68.6391},  //CNVertexF 3
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -10.9187,-2.41066,68.6391},  //CNVertexF 2
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -19.3212,-4.26579,60.9052},  //CNVertexF 4
  /* (Face 4 of 7) */
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -19.4829,3.4528,60.9052},  //CNVertexF 5
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -24.1287,-5.3272,49.3306},  //CNVertexF 6
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -24.3306,4.31193,49.3306},  //CNVertexF 7
  /* (Face 5 of 7) */
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -19.4829,3.4528,60.9052},  //CNVertexF 5
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -19.3212,-4.26579,60.9052},  //CNVertexF 4
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -24.1287,-5.3272,49.3306},  //CNVertexF 6
  /* (Face 6 of 7) */
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -24.3306,4.31193,49.3306},  //CNVertexF 7
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -25.6165,-5.65569,35.6775},  //CNVertexF 8
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -25.8309,4.57781,35.6775},  //CNVertexF 9
  /* (Face 7 of 7) */
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -24.3306,4.31193,49.3306},  //CNVertexF 7
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -24.1287,-5.3272,49.3306},  //CNVertexF 6
  {/*Stripecol,*/ 0.0f, 0.0f, 0.0f, -25.6165,-5.65569,35.6775}  //CNVertexF 8
};   /* Stripe 3D Model Code End */

/*------------------------------
 cannon detailed information:
    Number of VertexFs: 62
    Number of Edges: 360
    Number of Faces: 120
------------------------------*/

/* cannon Material */
//#define cannoncol GU_COLOR(45,45,45,255)
//#define cannoncol GU_COLOR(30.0f/255.0f,30.0f/255.0f,30.0f/255.0f,0.0f)
#define cannoncol GU_COLOR(0.12f, 0.12f, 0.12f, 1.0f)

ScePspFVector3 cannonPos = {19.4242,0.271889,47.1655};

CNVertexF __attribute__((aligned(16))) cannon[120*3] = {   /* cannon 3D Model Code Start */
  /* (Face 1 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.017662,3.47415,0.0},  //CNVertexF 2
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0142899,2.81065,2.04208},  //CNVertexF 3
  /* (Face 2 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0142899,2.81065,2.04208},  //CNVertexF 3
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.00545883,1.07357,3.30416},  //CNVertexF 4
  /* (Face 3 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.00545883,1.07357,3.30416},  //CNVertexF 4
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.00545883,-1.07357,3.30416},  //CNVertexF 5
  /* (Face 4 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.00545883,-1.07357,3.30416},  //CNVertexF 5
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.0142899,-2.81065,2.04208},  //CNVertexF 6
  /* (Face 5 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.0142899,-2.81065,2.04208},  //CNVertexF 6
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.017662,-3.47415,0.0},  //CNVertexF 7
  /* (Face 6 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.017662,-3.47415,0.0},  //CNVertexF 7
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.0142899,-2.81065,-2.04208},  //CNVertexF 8
  /* (Face 7 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.0142899,-2.81065,-2.04208},  //CNVertexF 8
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.00545883,-1.07357,-3.30416},  //CNVertexF 9
  /* (Face 8 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.00545883,-1.07357,-3.30416},  //CNVertexF 9
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.00545883,1.07357,-3.30416},  //CNVertexF 10
  /* (Face 9 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.00545883,1.07357,-3.30416},  //CNVertexF 10
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0142899,2.81065,-2.04208},  //CNVertexF 11
  /* (Face 10 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 1
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0142899,2.81065,-2.04208},  //CNVertexF 11
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.017662,3.47415,0.0},  //CNVertexF 2
  /* (Face 11 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.017662,3.47415,0.0},  //CNVertexF 2
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35703,3.46226,0.0},  //CNVertexF 12
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35366,2.79875,2.04208},  //CNVertexF 13
  /* (Face 12 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.017662,3.47415,0.0},  //CNVertexF 2
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35366,2.79875,2.04208},  //CNVertexF 13
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0142899,2.81065,2.04208},  //CNVertexF 3
  /* (Face 13 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0142899,2.81065,2.04208},  //CNVertexF 3
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35366,2.79875,2.04208},  //CNVertexF 13
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.34483,1.06168,3.30416},  //CNVertexF 14
  /* (Face 14 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0142899,2.81065,2.04208},  //CNVertexF 3
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.34483,1.06168,3.30416},  //CNVertexF 14
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.00545883,1.07357,3.30416},  //CNVertexF 4
  /* (Face 15 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.00545883,1.07357,3.30416},  //CNVertexF 4
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.34483,1.06168,3.30416},  //CNVertexF 14
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.33391,-1.08547,3.30416},  //CNVertexF 15
  /* (Face 16 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.00545883,1.07357,3.30416},  //CNVertexF 4
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.33391,-1.08547,3.30416},  //CNVertexF 15
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.00545883,-1.07357,3.30416},  //CNVertexF 5
  /* (Face 17 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.00545883,-1.07357,3.30416},  //CNVertexF 5
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.33391,-1.08547,3.30416},  //CNVertexF 15
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32508,-2.82254,2.04208},  //CNVertexF 16
  /* (Face 18 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.00545883,-1.07357,3.30416},  //CNVertexF 5
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32508,-2.82254,2.04208},  //CNVertexF 16
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.0142899,-2.81065,2.04208},  //CNVertexF 6
  /* (Face 19 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.0142899,-2.81065,2.04208},  //CNVertexF 6
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32508,-2.82254,2.04208},  //CNVertexF 16
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32171,-3.48604,0.0},  //CNVertexF 17
  /* (Face 20 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.0142899,-2.81065,2.04208},  //CNVertexF 6
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32171,-3.48604,0.0},  //CNVertexF 17
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.017662,-3.47415,0.0},  //CNVertexF 7
  /* (Face 21 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.017662,-3.47415,0.0},  //CNVertexF 7
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32171,-3.48604,0.0},  //CNVertexF 17
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32508,-2.82254,-2.04208},  //CNVertexF 18
  /* (Face 22 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.017662,-3.47415,0.0},  //CNVertexF 7
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32508,-2.82254,-2.04208},  //CNVertexF 18
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.0142899,-2.81065,-2.04208},  //CNVertexF 8
  /* (Face 23 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.0142899,-2.81065,-2.04208},  //CNVertexF 8
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32508,-2.82254,-2.04208},  //CNVertexF 18
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.33391,-1.08547,-3.30416},  //CNVertexF 19
  /* (Face 24 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.0142899,-2.81065,-2.04208},  //CNVertexF 8
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.33391,-1.08547,-3.30416},  //CNVertexF 19
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.00545883,-1.07357,-3.30416},  //CNVertexF 9
  /* (Face 25 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.00545883,-1.07357,-3.30416},  //CNVertexF 9
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.33391,-1.08547,-3.30416},  //CNVertexF 19
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.34483,1.06168,-3.30416},  //CNVertexF 20
  /* (Face 26 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, -0.00545883,-1.07357,-3.30416},  //CNVertexF 9
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.34483,1.06168,-3.30416},  //CNVertexF 20
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.00545883,1.07357,-3.30416},  //CNVertexF 10
  /* (Face 27 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.00545883,1.07357,-3.30416},  //CNVertexF 10
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.34483,1.06168,-3.30416},  //CNVertexF 20
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35366,2.79875,-2.04208},  //CNVertexF 21
  /* (Face 28 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.00545883,1.07357,-3.30416},  //CNVertexF 10
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35366,2.79875,-2.04208},  //CNVertexF 21
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0142899,2.81065,-2.04208},  //CNVertexF 11
  /* (Face 29 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0142899,2.81065,-2.04208},  //CNVertexF 11
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35366,2.79875,-2.04208},  //CNVertexF 21
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35703,3.46226,0.0},  //CNVertexF 12
  /* (Face 30 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.0142899,2.81065,-2.04208},  //CNVertexF 11
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35703,3.46226,0.0},  //CNVertexF 12
  {cannoncol, 0.0f, 0.0f, 0.0f, 0.017662,3.47415,0.0},  //CNVertexF 2
  /* (Face 31 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35703,3.46226,0.0},  //CNVertexF 12
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69641,3.45036,0.0},  //CNVertexF 22
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69303,2.78686,2.04208},  //CNVertexF 23
  /* (Face 32 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35703,3.46226,0.0},  //CNVertexF 12
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69303,2.78686,2.04208},  //CNVertexF 23
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35366,2.79875,2.04208},  //CNVertexF 13
  /* (Face 33 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35366,2.79875,2.04208},  //CNVertexF 13
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69303,2.78686,2.04208},  //CNVertexF 23
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.6842,1.04978,3.30416},  //CNVertexF 24
  /* (Face 34 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35366,2.79875,2.04208},  //CNVertexF 13
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.6842,1.04978,3.30416},  //CNVertexF 24
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.34483,1.06168,3.30416},  //CNVertexF 14
  /* (Face 35 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.34483,1.06168,3.30416},  //CNVertexF 14
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.6842,1.04978,3.30416},  //CNVertexF 24
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.67329,-1.09736,3.30416},  //CNVertexF 25
  /* (Face 36 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.34483,1.06168,3.30416},  //CNVertexF 14
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.67329,-1.09736,3.30416},  //CNVertexF 25
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.33391,-1.08547,3.30416},  //CNVertexF 15
  /* (Face 37 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.33391,-1.08547,3.30416},  //CNVertexF 15
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.67329,-1.09736,3.30416},  //CNVertexF 25
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66446,-2.83443,2.04208},  //CNVertexF 26
  /* (Face 38 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.33391,-1.08547,3.30416},  //CNVertexF 15
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66446,-2.83443,2.04208},  //CNVertexF 26
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32508,-2.82254,2.04208},  //CNVertexF 16
  /* (Face 39 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32508,-2.82254,2.04208},  //CNVertexF 16
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66446,-2.83443,2.04208},  //CNVertexF 26
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66108,-3.49794,0.0},  //CNVertexF 27
  /* (Face 40 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32508,-2.82254,2.04208},  //CNVertexF 16
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66108,-3.49794,0.0},  //CNVertexF 27
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32171,-3.48604,0.0},  //CNVertexF 17
  /* (Face 41 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32171,-3.48604,0.0},  //CNVertexF 17
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66108,-3.49794,0.0},  //CNVertexF 27
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66446,-2.83443,-2.04208},  //CNVertexF 28
  /* (Face 42 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32171,-3.48604,0.0},  //CNVertexF 17
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66446,-2.83443,-2.04208},  //CNVertexF 28
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32508,-2.82254,-2.04208},  //CNVertexF 18
  /* (Face 43 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32508,-2.82254,-2.04208},  //CNVertexF 18
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66446,-2.83443,-2.04208},  //CNVertexF 28
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.67329,-1.09736,-3.30416},  //CNVertexF 29
  /* (Face 44 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.32508,-2.82254,-2.04208},  //CNVertexF 18
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.67329,-1.09736,-3.30416},  //CNVertexF 29
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.33391,-1.08547,-3.30416},  //CNVertexF 19
  /* (Face 45 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.33391,-1.08547,-3.30416},  //CNVertexF 19
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.67329,-1.09736,-3.30416},  //CNVertexF 29
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.6842,1.04979,-3.30416},  //CNVertexF 30
  /* (Face 46 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.33391,-1.08547,-3.30416},  //CNVertexF 19
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.6842,1.04979,-3.30416},  //CNVertexF 30
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.34483,1.06168,-3.30416},  //CNVertexF 20
  /* (Face 47 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.34483,1.06168,-3.30416},  //CNVertexF 20
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.6842,1.04979,-3.30416},  //CNVertexF 30
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69303,2.78686,-2.04208},  //CNVertexF 31
  /* (Face 48 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.34483,1.06168,-3.30416},  //CNVertexF 20
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69303,2.78686,-2.04208},  //CNVertexF 31
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35366,2.79875,-2.04208},  //CNVertexF 21
  /* (Face 49 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35366,2.79875,-2.04208},  //CNVertexF 21
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69303,2.78686,-2.04208},  //CNVertexF 31
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69641,3.45036,0.0},  //CNVertexF 22
  /* (Face 50 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35366,2.79875,-2.04208},  //CNVertexF 21
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69641,3.45036,0.0},  //CNVertexF 22
  {cannoncol, 0.0f, 0.0f, 0.0f, 2.35703,3.46226,0.0},  //CNVertexF 12
  /* (Face 51 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69641,3.45036,0.0},  //CNVertexF 22
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03578,3.43847,0.0},  //CNVertexF 32
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03241,2.77497,2.04208},  //CNVertexF 33
  /* (Face 52 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69641,3.45036,0.0},  //CNVertexF 22
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03241,2.77497,2.04208},  //CNVertexF 33
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69303,2.78686,2.04208},  //CNVertexF 23
  /* (Face 53 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69303,2.78686,2.04208},  //CNVertexF 23
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03241,2.77497,2.04208},  //CNVertexF 33
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.02357,1.03789,3.30416},  //CNVertexF 34
  /* (Face 54 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69303,2.78686,2.04208},  //CNVertexF 23
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.02357,1.03789,3.30416},  //CNVertexF 34
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.6842,1.04978,3.30416},  //CNVertexF 24
  /* (Face 55 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.6842,1.04978,3.30416},  //CNVertexF 24
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.02357,1.03789,3.30416},  //CNVertexF 34
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.01266,-1.10925,3.30416},  //CNVertexF 35
  /* (Face 56 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.6842,1.04978,3.30416},  //CNVertexF 24
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.01266,-1.10925,3.30416},  //CNVertexF 35
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.67329,-1.09736,3.30416},  //CNVertexF 25
  /* (Face 57 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.67329,-1.09736,3.30416},  //CNVertexF 25
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.01266,-1.10925,3.30416},  //CNVertexF 35
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00383,-2.84633,2.04208},  //CNVertexF 36
  /* (Face 58 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.67329,-1.09736,3.30416},  //CNVertexF 25
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00383,-2.84633,2.04208},  //CNVertexF 36
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66446,-2.83443,2.04208},  //CNVertexF 26
  /* (Face 59 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66446,-2.83443,2.04208},  //CNVertexF 26
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00383,-2.84633,2.04208},  //CNVertexF 36
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00045,-3.50983,0.0},  //CNVertexF 37
  /* (Face 60 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66446,-2.83443,2.04208},  //CNVertexF 26
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00045,-3.50983,0.0},  //CNVertexF 37
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66108,-3.49794,0.0},  //CNVertexF 27
  /* (Face 61 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66108,-3.49794,0.0},  //CNVertexF 27
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00045,-3.50983,0.0},  //CNVertexF 37
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00383,-2.84633,-2.04208},  //CNVertexF 38
  /* (Face 62 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66108,-3.49794,0.0},  //CNVertexF 27
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00383,-2.84633,-2.04208},  //CNVertexF 38
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66446,-2.83443,-2.04208},  //CNVertexF 28
  /* (Face 63 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66446,-2.83443,-2.04208},  //CNVertexF 28
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00383,-2.84633,-2.04208},  //CNVertexF 38
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.01266,-1.10925,-3.30416},  //CNVertexF 39
  /* (Face 64 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.66446,-2.83443,-2.04208},  //CNVertexF 28
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.01266,-1.10925,-3.30416},  //CNVertexF 39
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.67329,-1.09736,-3.30416},  //CNVertexF 29
  /* (Face 65 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.67329,-1.09736,-3.30416},  //CNVertexF 29
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.01266,-1.10925,-3.30416},  //CNVertexF 39
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.02357,1.03789,-3.30416},  //CNVertexF 40
  /* (Face 66 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.67329,-1.09736,-3.30416},  //CNVertexF 29
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.02357,1.03789,-3.30416},  //CNVertexF 40
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.6842,1.04979,-3.30416},  //CNVertexF 30
  /* (Face 67 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.6842,1.04979,-3.30416},  //CNVertexF 30
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.02357,1.03789,-3.30416},  //CNVertexF 40
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03241,2.77497,-2.04208},  //CNVertexF 41
  /* (Face 68 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.6842,1.04979,-3.30416},  //CNVertexF 30
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03241,2.77497,-2.04208},  //CNVertexF 41
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69303,2.78686,-2.04208},  //CNVertexF 31
  /* (Face 69 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69303,2.78686,-2.04208},  //CNVertexF 31
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03241,2.77497,-2.04208},  //CNVertexF 41
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03578,3.43847,0.0},  //CNVertexF 32
  /* (Face 70 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69303,2.78686,-2.04208},  //CNVertexF 31
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03578,3.43847,0.0},  //CNVertexF 32
  {cannoncol, 0.0f, 0.0f, 0.0f, 4.69641,3.45036,0.0},  //CNVertexF 22
  /* (Face 71 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03578,3.43847,0.0},  //CNVertexF 32
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37515,3.42658,0.0},  //CNVertexF 42
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37178,2.76307,2.04208},  //CNVertexF 43
  /* (Face 72 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03578,3.43847,0.0},  //CNVertexF 32
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37178,2.76307,2.04208},  //CNVertexF 43
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03241,2.77497,2.04208},  //CNVertexF 33
  /* (Face 73 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03241,2.77497,2.04208},  //CNVertexF 33
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37178,2.76307,2.04208},  //CNVertexF 43
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.36295,1.026,3.30416},  //CNVertexF 44
  /* (Face 74 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03241,2.77497,2.04208},  //CNVertexF 33
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.36295,1.026,3.30416},  //CNVertexF 44
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.02357,1.03789,3.30416},  //CNVertexF 34
  /* (Face 75 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.02357,1.03789,3.30416},  //CNVertexF 34
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.36295,1.026,3.30416},  //CNVertexF 44
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.35203,-1.12115,3.30416},  //CNVertexF 45
  /* (Face 76 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.02357,1.03789,3.30416},  //CNVertexF 34
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.35203,-1.12115,3.30416},  //CNVertexF 45
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.01266,-1.10925,3.30416},  //CNVertexF 35
  /* (Face 77 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.01266,-1.10925,3.30416},  //CNVertexF 35
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.35203,-1.12115,3.30416},  //CNVertexF 45
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.3432,-2.85822,2.04208},  //CNVertexF 46
  /* (Face 78 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.01266,-1.10925,3.30416},  //CNVertexF 35
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.3432,-2.85822,2.04208},  //CNVertexF 46
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00383,-2.84633,2.04208},  //CNVertexF 36
  /* (Face 79 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00383,-2.84633,2.04208},  //CNVertexF 36
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.3432,-2.85822,2.04208},  //CNVertexF 46
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.33982,-3.52173,0.0},  //CNVertexF 47
  /* (Face 80 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00383,-2.84633,2.04208},  //CNVertexF 36
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.33982,-3.52173,0.0},  //CNVertexF 47
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00045,-3.50983,0.0},  //CNVertexF 37
  /* (Face 81 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00045,-3.50983,0.0},  //CNVertexF 37
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.33982,-3.52173,0.0},  //CNVertexF 47
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.3432,-2.85822,-2.04208},  //CNVertexF 48
  /* (Face 82 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00045,-3.50983,0.0},  //CNVertexF 37
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.3432,-2.85822,-2.04208},  //CNVertexF 48
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00383,-2.84633,-2.04208},  //CNVertexF 38
  /* (Face 83 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00383,-2.84633,-2.04208},  //CNVertexF 38
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.3432,-2.85822,-2.04208},  //CNVertexF 48
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.35203,-1.12115,-3.30416},  //CNVertexF 49
  /* (Face 84 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.00383,-2.84633,-2.04208},  //CNVertexF 38
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.35203,-1.12115,-3.30416},  //CNVertexF 49
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.01266,-1.10925,-3.30416},  //CNVertexF 39
  /* (Face 85 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.01266,-1.10925,-3.30416},  //CNVertexF 39
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.35203,-1.12115,-3.30416},  //CNVertexF 49
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.36295,1.026,-3.30416},  //CNVertexF 50
  /* (Face 86 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.01266,-1.10925,-3.30416},  //CNVertexF 39
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.36295,1.026,-3.30416},  //CNVertexF 50
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.02357,1.03789,-3.30416},  //CNVertexF 40
  /* (Face 87 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.02357,1.03789,-3.30416},  //CNVertexF 40
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.36295,1.026,-3.30416},  //CNVertexF 50
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37178,2.76307,-2.04208},  //CNVertexF 51
  /* (Face 88 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.02357,1.03789,-3.30416},  //CNVertexF 40
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37178,2.76307,-2.04208},  //CNVertexF 51
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03241,2.77497,-2.04208},  //CNVertexF 41
  /* (Face 89 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03241,2.77497,-2.04208},  //CNVertexF 41
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37178,2.76307,-2.04208},  //CNVertexF 51
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37515,3.42658,0.0},  //CNVertexF 42
  /* (Face 90 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03241,2.77497,-2.04208},  //CNVertexF 41
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37515,3.42658,0.0},  //CNVertexF 42
  {cannoncol, 0.0f, 0.0f, 0.0f, 7.03578,3.43847,0.0},  //CNVertexF 32
  /* (Face 91 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37515,3.42658,0.0},  //CNVertexF 42
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7145,3.41468,0.0},  //CNVertexF 52
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7111,2.75118,2.04208},  //CNVertexF 53
  /* (Face 92 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37515,3.42658,0.0},  //CNVertexF 42
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7111,2.75118,2.04208},  //CNVertexF 53
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37178,2.76307,2.04208},  //CNVertexF 43
  /* (Face 93 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37178,2.76307,2.04208},  //CNVertexF 43
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7111,2.75118,2.04208},  //CNVertexF 53
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7023,1.0141,3.30416},  //CNVertexF 54
  /* (Face 94 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37178,2.76307,2.04208},  //CNVertexF 43
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7023,1.0141,3.30416},  //CNVertexF 54
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.36295,1.026,3.30416},  //CNVertexF 44
  /* (Face 95 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.36295,1.026,3.30416},  //CNVertexF 44
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7023,1.0141,3.30416},  //CNVertexF 54
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6914,-1.13304,3.30416},  //CNVertexF 55
  /* (Face 96 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.36295,1.026,3.30416},  //CNVertexF 44
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6914,-1.13304,3.30416},  //CNVertexF 55
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.35203,-1.12115,3.30416},  //CNVertexF 45
  /* (Face 97 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.35203,-1.12115,3.30416},  //CNVertexF 45
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6914,-1.13304,3.30416},  //CNVertexF 55
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6826,-2.87012,2.04208},  //CNVertexF 56
  /* (Face 98 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.35203,-1.12115,3.30416},  //CNVertexF 45
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6826,-2.87012,2.04208},  //CNVertexF 56
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.3432,-2.85822,2.04208},  //CNVertexF 46
  /* (Face 99 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.3432,-2.85822,2.04208},  //CNVertexF 46
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6826,-2.87012,2.04208},  //CNVertexF 56
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6792,-3.53362,0.0},  //CNVertexF 57
  /* (Face 100 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.3432,-2.85822,2.04208},  //CNVertexF 46
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6792,-3.53362,0.0},  //CNVertexF 57
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.33982,-3.52173,0.0},  //CNVertexF 47
  /* (Face 101 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.33982,-3.52173,0.0},  //CNVertexF 47
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6792,-3.53362,0.0},  //CNVertexF 57
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6826,-2.87012,-2.04208},  //CNVertexF 58
  /* (Face 102 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.33982,-3.52173,0.0},  //CNVertexF 47
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6826,-2.87012,-2.04208},  //CNVertexF 58
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.3432,-2.85822,-2.04208},  //CNVertexF 48
  /* (Face 103 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.3432,-2.85822,-2.04208},  //CNVertexF 48
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6826,-2.87012,-2.04208},  //CNVertexF 58
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6914,-1.13304,-3.30416},  //CNVertexF 59
  /* (Face 104 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.3432,-2.85822,-2.04208},  //CNVertexF 48
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6914,-1.13304,-3.30416},  //CNVertexF 59
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.35203,-1.12115,-3.30416},  //CNVertexF 49
  /* (Face 105 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.35203,-1.12115,-3.30416},  //CNVertexF 49
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6914,-1.13304,-3.30416},  //CNVertexF 59
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7023,1.0141,-3.30416},  //CNVertexF 60
  /* (Face 106 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.35203,-1.12115,-3.30416},  //CNVertexF 49
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7023,1.0141,-3.30416},  //CNVertexF 60
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.36295,1.026,-3.30416},  //CNVertexF 50
  /* (Face 107 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.36295,1.026,-3.30416},  //CNVertexF 50
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7023,1.0141,-3.30416},  //CNVertexF 60
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7111,2.75118,-2.04208},  //CNVertexF 61
  /* (Face 108 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.36295,1.026,-3.30416},  //CNVertexF 50
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7111,2.75118,-2.04208},  //CNVertexF 61
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37178,2.76307,-2.04208},  //CNVertexF 51
  /* (Face 109 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37178,2.76307,-2.04208},  //CNVertexF 51
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7111,2.75118,-2.04208},  //CNVertexF 61
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7145,3.41468,0.0},  //CNVertexF 52
  /* (Face 110 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37178,2.76307,-2.04208},  //CNVertexF 51
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7145,3.41468,0.0},  //CNVertexF 52
  {cannoncol, 0.0f, 0.0f, 0.0f, 9.37515,3.42658,0.0},  //CNVertexF 42
  /* (Face 111 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6969,-0.0594679,0.0},  //CNVertexF 62
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7111,2.75118,2.04208},  //CNVertexF 53
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7145,3.41468,0.0},  //CNVertexF 52
  /* (Face 112 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6969,-0.0594679,0.0},  //CNVertexF 62
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7023,1.0141,3.30416},  //CNVertexF 54
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7111,2.75118,2.04208},  //CNVertexF 53
  /* (Face 113 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6969,-0.0594679,0.0},  //CNVertexF 62
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6914,-1.13304,3.30416},  //CNVertexF 55
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7023,1.0141,3.30416},  //CNVertexF 54
  /* (Face 114 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6969,-0.0594679,0.0},  //CNVertexF 62
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6826,-2.87012,2.04208},  //CNVertexF 56
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6914,-1.13304,3.30416},  //CNVertexF 55
  /* (Face 115 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6969,-0.0594679,0.0},  //CNVertexF 62
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6792,-3.53362,0.0},  //CNVertexF 57
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6826,-2.87012,2.04208},  //CNVertexF 56
  /* (Face 116 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6969,-0.0594679,0.0},  //CNVertexF 62
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6826,-2.87012,-2.04208},  //CNVertexF 58
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6792,-3.53362,0.0},  //CNVertexF 57
  /* (Face 117 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6969,-0.0594679,0.0},  //CNVertexF 62
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6914,-1.13304,-3.30416},  //CNVertexF 59
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6826,-2.87012,-2.04208},  //CNVertexF 58
  /* (Face 118 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6969,-0.0594679,0.0},  //CNVertexF 62
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7023,1.0141,-3.30416},  //CNVertexF 60
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6914,-1.13304,-3.30416},  //CNVertexF 59
  /* (Face 119 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6969,-0.0594679,0.0},  //CNVertexF 62
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7111,2.75118,-2.04208},  //CNVertexF 61
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7023,1.0141,-3.30416},  //CNVertexF 60
  /* (Face 120 of 120) */
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.6969,-0.0594679,0.0},  //CNVertexF 62
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7145,3.41468,0.0},  //CNVertexF 52
  {cannoncol, 0.0f, 0.0f, 0.0f, 11.7111,2.75118,-2.04208}  //CNVertexF 61
};   /* cannon 3D Model Code End */

/*------------------------------
 dome detailed information:
    Number of VertexFs: 65
    Number of Edges: 336
    Number of Faces: 112
------------------------------*/

/* dome Material */
//#define domecol GU_COLOR(150,150,150,255)
//#define domecol GU_COLOR(150.0f/255.0f, 150.0f/255.0f, 150.0f/255.0f, 0.0f)
//#define domecol GU_COLOR(0.59f, 0.59f, 0.59f, 1.0f)
#define domecol GU_COLOR(0.5f, 0.5f, 0.5f, 1.0f)

ScePspFVector3 domePos = {0.53397,0.00334549,-8.06675};

CNVertexF __attribute__((aligned(16))) dome[112*3] = {   /* dome 3D Model Code Start */
  /* (Face 1 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, -9.16502,-6.40555,68.6391},  //CNVertexF 3
  {domecol, 0.0f, 0.0f, 0.0f, -10.9187,-2.41065,68.6391},  //CNVertexF 2
  /* (Face 2 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, -6.01608,-9.42525,68.6391},  //CNVertexF 4
  {domecol, 0.0f, 0.0f, 0.0f, -9.16502,-6.40555,68.6391},  //CNVertexF 3
  /* (Face 3 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, -1.95124,-11.0101,68.6391},  //CNVertexF 5
  {domecol, 0.0f, 0.0f, 0.0f, -6.01608,-9.42525,68.6391},  //CNVertexF 4
  /* (Face 4 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, 2.41065,-10.9187,68.6391},  //CNVertexF 6
  {domecol, 0.0f, 0.0f, 0.0f, -1.95124,-11.0101,68.6391},  //CNVertexF 5
  /* (Face 5 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, 6.40554,-9.16502,68.6391},  //CNVertexF 7
  {domecol, 0.0f, 0.0f, 0.0f, 2.41065,-10.9187,68.6391},  //CNVertexF 6
  /* (Face 6 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, 9.42525,-6.01608,68.6391},  //CNVertexF 8
  {domecol, 0.0f, 0.0f, 0.0f, 6.40554,-9.16502,68.6391},  //CNVertexF 7
  /* (Face 7 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, 11.0101,-1.95124,68.6391},  //CNVertexF 9
  {domecol, 0.0f, 0.0f, 0.0f, 9.42525,-6.01608,68.6391},  //CNVertexF 8
  /* (Face 8 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, 10.9187,2.41065,68.6391},  //CNVertexF 10
  {domecol, 0.0f, 0.0f, 0.0f, 11.0101,-1.95124,68.6391},  //CNVertexF 9
  /* (Face 9 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, 9.16502,6.40555,68.6391},  //CNVertexF 11
  {domecol, 0.0f, 0.0f, 0.0f, 10.9187,2.41065,68.6391},  //CNVertexF 10
  /* (Face 10 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, 6.01607,9.42525,68.6391},  //CNVertexF 12
  {domecol, 0.0f, 0.0f, 0.0f, 9.16502,6.40555,68.6391},  //CNVertexF 11
  /* (Face 11 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, 1.95124,11.0101,68.6391},  //CNVertexF 13
  {domecol, 0.0f, 0.0f, 0.0f, 6.01607,9.42525,68.6391},  //CNVertexF 12
  /* (Face 12 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, -2.41066,10.9187,68.6391},  //CNVertexF 14
  {domecol, 0.0f, 0.0f, 0.0f, 1.95124,11.0101,68.6391},  //CNVertexF 13
  /* (Face 13 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, -6.40555,9.16501,68.6391},  //CNVertexF 15
  {domecol, 0.0f, 0.0f, 0.0f, -2.41066,10.9187,68.6391},  //CNVertexF 14
  /* (Face 14 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, -9.42526,6.01607,68.6391},  //CNVertexF 16
  {domecol, 0.0f, 0.0f, 0.0f, -6.40555,9.16501,68.6391},  //CNVertexF 15
  /* (Face 15 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, -11.0101,1.95123,68.6391},  //CNVertexF 17
  {domecol, 0.0f, 0.0f, 0.0f, -9.42526,6.01607,68.6391},  //CNVertexF 16
  /* (Face 16 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,71.3549},  //CNVertexF 1
  {domecol, 0.0f, 0.0f, 0.0f, -10.9187,-2.41065,68.6391},  //CNVertexF 2
  {domecol, 0.0f, 0.0f, 0.0f, -11.0101,1.95123,68.6391},  //CNVertexF 17
  /* (Face 17 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -10.9187,-2.41065,68.6391},  //CNVertexF 2
  {domecol, 0.0f, 0.0f, 0.0f, -16.218,-11.335,60.9052},  //CNVertexF 19
  {domecol, 0.0f, 0.0f, 0.0f, -19.3212,-4.26578,60.9052},  //CNVertexF 18
  /* (Face 18 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -10.9187,-2.41065,68.6391},  //CNVertexF 2
  {domecol, 0.0f, 0.0f, 0.0f, -9.16502,-6.40555,68.6391},  //CNVertexF 3
  {domecol, 0.0f, 0.0f, 0.0f, -16.218,-11.335,60.9052},  //CNVertexF 19
  /* (Face 19 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -9.16502,-6.40555,68.6391},  //CNVertexF 3
  {domecol, 0.0f, 0.0f, 0.0f, -10.6458,-16.6785,60.9052},  //CNVertexF 20
  {domecol, 0.0f, 0.0f, 0.0f, -16.218,-11.335,60.9052},  //CNVertexF 19
  /* (Face 20 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -9.16502,-6.40555,68.6391},  //CNVertexF 3
  {domecol, 0.0f, 0.0f, 0.0f, -6.01608,-9.42525,68.6391},  //CNVertexF 4
  {domecol, 0.0f, 0.0f, 0.0f, -10.6458,-16.6785,60.9052},  //CNVertexF 20
  /* (Face 21 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -6.01608,-9.42525,68.6391},  //CNVertexF 4
  {domecol, 0.0f, 0.0f, 0.0f, -3.45283,-19.4829,60.9052},  //CNVertexF 21
  {domecol, 0.0f, 0.0f, 0.0f, -10.6458,-16.6785,60.9052},  //CNVertexF 20
  /* (Face 22 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -6.01608,-9.42525,68.6391},  //CNVertexF 4
  {domecol, 0.0f, 0.0f, 0.0f, -1.95124,-11.0101,68.6391},  //CNVertexF 5
  {domecol, 0.0f, 0.0f, 0.0f, -3.45283,-19.4829,60.9052},  //CNVertexF 21
  /* (Face 23 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -1.95124,-11.0101,68.6391},  //CNVertexF 5
  {domecol, 0.0f, 0.0f, 0.0f, 4.26578,-19.3212,60.9052},  //CNVertexF 22
  {domecol, 0.0f, 0.0f, 0.0f, -3.45283,-19.4829,60.9052},  //CNVertexF 21
  /* (Face 24 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -1.95124,-11.0101,68.6391},  //CNVertexF 5
  {domecol, 0.0f, 0.0f, 0.0f, 2.41065,-10.9187,68.6391},  //CNVertexF 6
  {domecol, 0.0f, 0.0f, 0.0f, 4.26578,-19.3212,60.9052},  //CNVertexF 22
  /* (Face 25 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 2.41065,-10.9187,68.6391},  //CNVertexF 6
  {domecol, 0.0f, 0.0f, 0.0f, 11.335,-16.218,60.9052},  //CNVertexF 23
  {domecol, 0.0f, 0.0f, 0.0f, 4.26578,-19.3212,60.9052},  //CNVertexF 22
  /* (Face 26 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 2.41065,-10.9187,68.6391},  //CNVertexF 6
  {domecol, 0.0f, 0.0f, 0.0f, 6.40554,-9.16502,68.6391},  //CNVertexF 7
  {domecol, 0.0f, 0.0f, 0.0f, 11.335,-16.218,60.9052},  //CNVertexF 23
  /* (Face 27 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 6.40554,-9.16502,68.6391},  //CNVertexF 7
  {domecol, 0.0f, 0.0f, 0.0f, 16.6785,-10.6458,60.9052},  //CNVertexF 24
  {domecol, 0.0f, 0.0f, 0.0f, 11.335,-16.218,60.9052},  //CNVertexF 23
  /* (Face 28 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 6.40554,-9.16502,68.6391},  //CNVertexF 7
  {domecol, 0.0f, 0.0f, 0.0f, 9.42525,-6.01608,68.6391},  //CNVertexF 8
  {domecol, 0.0f, 0.0f, 0.0f, 16.6785,-10.6458,60.9052},  //CNVertexF 24
  /* (Face 29 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 9.42525,-6.01608,68.6391},  //CNVertexF 8
  {domecol, 0.0f, 0.0f, 0.0f, 19.4829,-3.45283,60.9052},  //CNVertexF 25
  {domecol, 0.0f, 0.0f, 0.0f, 16.6785,-10.6458,60.9052},  //CNVertexF 24
  /* (Face 30 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 9.42525,-6.01608,68.6391},  //CNVertexF 8
  {domecol, 0.0f, 0.0f, 0.0f, 11.0101,-1.95124,68.6391},  //CNVertexF 9
  {domecol, 0.0f, 0.0f, 0.0f, 19.4829,-3.45283,60.9052},  //CNVertexF 25
  /* (Face 31 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 11.0101,-1.95124,68.6391},  //CNVertexF 9
  {domecol, 0.0f, 0.0f, 0.0f, 19.3212,4.26578,60.9052},  //CNVertexF 26
  {domecol, 0.0f, 0.0f, 0.0f, 19.4829,-3.45283,60.9052},  //CNVertexF 25
  /* (Face 32 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 11.0101,-1.95124,68.6391},  //CNVertexF 9
  {domecol, 0.0f, 0.0f, 0.0f, 10.9187,2.41065,68.6391},  //CNVertexF 10
  {domecol, 0.0f, 0.0f, 0.0f, 19.3212,4.26578,60.9052},  //CNVertexF 26
  /* (Face 33 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 10.9187,2.41065,68.6391},  //CNVertexF 10
  {domecol, 0.0f, 0.0f, 0.0f, 16.218,11.335,60.9052},  //CNVertexF 27
  {domecol, 0.0f, 0.0f, 0.0f, 19.3212,4.26578,60.9052},  //CNVertexF 26
  /* (Face 34 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 10.9187,2.41065,68.6391},  //CNVertexF 10
  {domecol, 0.0f, 0.0f, 0.0f, 9.16502,6.40555,68.6391},  //CNVertexF 11
  {domecol, 0.0f, 0.0f, 0.0f, 16.218,11.335,60.9052},  //CNVertexF 27
  /* (Face 35 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 9.16502,6.40555,68.6391},  //CNVertexF 11
  {domecol, 0.0f, 0.0f, 0.0f, 10.6458,16.6785,60.9052},  //CNVertexF 28
  {domecol, 0.0f, 0.0f, 0.0f, 16.218,11.335,60.9052},  //CNVertexF 27
  /* (Face 36 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 9.16502,6.40555,68.6391},  //CNVertexF 11
  {domecol, 0.0f, 0.0f, 0.0f, 6.01607,9.42525,68.6391},  //CNVertexF 12
  {domecol, 0.0f, 0.0f, 0.0f, 10.6458,16.6785,60.9052},  //CNVertexF 28
  /* (Face 37 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 6.01607,9.42525,68.6391},  //CNVertexF 12
  {domecol, 0.0f, 0.0f, 0.0f, 3.45282,19.4829,60.9052},  //CNVertexF 29
  {domecol, 0.0f, 0.0f, 0.0f, 10.6458,16.6785,60.9052},  //CNVertexF 28
  /* (Face 38 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 6.01607,9.42525,68.6391},  //CNVertexF 12
  {domecol, 0.0f, 0.0f, 0.0f, 1.95124,11.0101,68.6391},  //CNVertexF 13
  {domecol, 0.0f, 0.0f, 0.0f, 3.45282,19.4829,60.9052},  //CNVertexF 29
  /* (Face 39 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 1.95124,11.0101,68.6391},  //CNVertexF 13
  {domecol, 0.0f, 0.0f, 0.0f, -4.26579,19.3212,60.9052},  //CNVertexF 30
  {domecol, 0.0f, 0.0f, 0.0f, 3.45282,19.4829,60.9052},  //CNVertexF 29
  /* (Face 40 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 1.95124,11.0101,68.6391},  //CNVertexF 13
  {domecol, 0.0f, 0.0f, 0.0f, -2.41066,10.9187,68.6391},  //CNVertexF 14
  {domecol, 0.0f, 0.0f, 0.0f, -4.26579,19.3212,60.9052},  //CNVertexF 30
  /* (Face 41 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -2.41066,10.9187,68.6391},  //CNVertexF 14
  {domecol, 0.0f, 0.0f, 0.0f, -11.335,16.218,60.9052},  //CNVertexF 31
  {domecol, 0.0f, 0.0f, 0.0f, -4.26579,19.3212,60.9052},  //CNVertexF 30
  /* (Face 42 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -2.41066,10.9187,68.6391},  //CNVertexF 14
  {domecol, 0.0f, 0.0f, 0.0f, -6.40555,9.16501,68.6391},  //CNVertexF 15
  {domecol, 0.0f, 0.0f, 0.0f, -11.335,16.218,60.9052},  //CNVertexF 31
  /* (Face 43 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -6.40555,9.16501,68.6391},  //CNVertexF 15
  {domecol, 0.0f, 0.0f, 0.0f, -16.6785,10.6458,60.9052},  //CNVertexF 32
  {domecol, 0.0f, 0.0f, 0.0f, -11.335,16.218,60.9052},  //CNVertexF 31
  /* (Face 44 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -6.40555,9.16501,68.6391},  //CNVertexF 15
  {domecol, 0.0f, 0.0f, 0.0f, -9.42526,6.01607,68.6391},  //CNVertexF 16
  {domecol, 0.0f, 0.0f, 0.0f, -16.6785,10.6458,60.9052},  //CNVertexF 32
  /* (Face 45 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -9.42526,6.01607,68.6391},  //CNVertexF 16
  {domecol, 0.0f, 0.0f, 0.0f, -19.4829,3.45281,60.9052},  //CNVertexF 33
  {domecol, 0.0f, 0.0f, 0.0f, -16.6785,10.6458,60.9052},  //CNVertexF 32
  /* (Face 46 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -9.42526,6.01607,68.6391},  //CNVertexF 16
  {domecol, 0.0f, 0.0f, 0.0f, -11.0101,1.95123,68.6391},  //CNVertexF 17
  {domecol, 0.0f, 0.0f, 0.0f, -19.4829,3.45281,60.9052},  //CNVertexF 33
  /* (Face 47 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -11.0101,1.95123,68.6391},  //CNVertexF 17
  {domecol, 0.0f, 0.0f, 0.0f, -19.3212,-4.26578,60.9052},  //CNVertexF 18
  {domecol, 0.0f, 0.0f, 0.0f, -19.4829,3.45281,60.9052},  //CNVertexF 33
  /* (Face 48 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -11.0101,1.95123,68.6391},  //CNVertexF 17
  {domecol, 0.0f, 0.0f, 0.0f, -10.9187,-2.41065,68.6391},  //CNVertexF 2
  {domecol, 0.0f, 0.0f, 0.0f, -19.3212,-4.26578,60.9052},  //CNVertexF 18
  /* (Face 49 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -19.3212,-4.26578,60.9052},  //CNVertexF 18
  {domecol, 0.0f, 0.0f, 0.0f, -20.2534,-14.1553,49.3306},  //CNVertexF 35
  {domecol, 0.0f, 0.0f, 0.0f, -24.1287,-5.32719,49.3306},  //CNVertexF 34
  /* (Face 50 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -19.3212,-4.26578,60.9052},  //CNVertexF 18
  {domecol, 0.0f, 0.0f, 0.0f, -16.218,-11.335,60.9052},  //CNVertexF 19
  {domecol, 0.0f, 0.0f, 0.0f, -20.2534,-14.1553,49.3306},  //CNVertexF 35
  /* (Face 51 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -16.218,-11.335,60.9052},  //CNVertexF 19
  {domecol, 0.0f, 0.0f, 0.0f, -13.2947,-20.8285,49.3306},  //CNVertexF 36
  {domecol, 0.0f, 0.0f, 0.0f, -20.2534,-14.1553,49.3306},  //CNVertexF 35
  /* (Face 52 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -16.218,-11.335,60.9052},  //CNVertexF 19
  {domecol, 0.0f, 0.0f, 0.0f, -10.6458,-16.6785,60.9052},  //CNVertexF 20
  {domecol, 0.0f, 0.0f, 0.0f, -13.2947,-20.8285,49.3306},  //CNVertexF 36
  /* (Face 53 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -10.6458,-16.6785,60.9052},  //CNVertexF 20
  {domecol, 0.0f, 0.0f, 0.0f, -4.31197,-24.3306,49.3306},  //CNVertexF 37
  {domecol, 0.0f, 0.0f, 0.0f, -13.2947,-20.8285,49.3306},  //CNVertexF 36
  /* (Face 54 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -10.6458,-16.6785,60.9052},  //CNVertexF 20
  {domecol, 0.0f, 0.0f, 0.0f, -3.45283,-19.4829,60.9052},  //CNVertexF 21
  {domecol, 0.0f, 0.0f, 0.0f, -4.31197,-24.3306,49.3306},  //CNVertexF 37
  /* (Face 55 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -3.45283,-19.4829,60.9052},  //CNVertexF 21
  {domecol, 0.0f, 0.0f, 0.0f, 5.32719,-24.1287,49.3306},  //CNVertexF 38
  {domecol, 0.0f, 0.0f, 0.0f, -4.31197,-24.3306,49.3306},  //CNVertexF 37
  /* (Face 56 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -3.45283,-19.4829,60.9052},  //CNVertexF 21
  {domecol, 0.0f, 0.0f, 0.0f, 4.26578,-19.3212,60.9052},  //CNVertexF 22
  {domecol, 0.0f, 0.0f, 0.0f, 5.32719,-24.1287,49.3306},  //CNVertexF 38
  /* (Face 57 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 4.26578,-19.3212,60.9052},  //CNVertexF 22
  {domecol, 0.0f, 0.0f, 0.0f, 14.1553,-20.2534,49.3306},  //CNVertexF 39
  {domecol, 0.0f, 0.0f, 0.0f, 5.32719,-24.1287,49.3306},  //CNVertexF 38
  /* (Face 58 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 4.26578,-19.3212,60.9052},  //CNVertexF 22
  {domecol, 0.0f, 0.0f, 0.0f, 11.335,-16.218,60.9052},  //CNVertexF 23
  {domecol, 0.0f, 0.0f, 0.0f, 14.1553,-20.2534,49.3306},  //CNVertexF 39
  /* (Face 59 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 11.335,-16.218,60.9052},  //CNVertexF 23
  {domecol, 0.0f, 0.0f, 0.0f, 20.8285,-13.2947,49.3306},  //CNVertexF 40
  {domecol, 0.0f, 0.0f, 0.0f, 14.1553,-20.2534,49.3306},  //CNVertexF 39
  /* (Face 60 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 11.335,-16.218,60.9052},  //CNVertexF 23
  {domecol, 0.0f, 0.0f, 0.0f, 16.6785,-10.6458,60.9052},  //CNVertexF 24
  {domecol, 0.0f, 0.0f, 0.0f, 20.8285,-13.2947,49.3306},  //CNVertexF 40
  /* (Face 61 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 16.6785,-10.6458,60.9052},  //CNVertexF 24
  {domecol, 0.0f, 0.0f, 0.0f, 24.3306,-4.31197,49.3306},  //CNVertexF 41
  {domecol, 0.0f, 0.0f, 0.0f, 20.8285,-13.2947,49.3306},  //CNVertexF 40
  /* (Face 62 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 16.6785,-10.6458,60.9052},  //CNVertexF 24
  {domecol, 0.0f, 0.0f, 0.0f, 19.4829,-3.45283,60.9052},  //CNVertexF 25
  {domecol, 0.0f, 0.0f, 0.0f, 24.3306,-4.31197,49.3306},  //CNVertexF 41
  /* (Face 63 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 19.4829,-3.45283,60.9052},  //CNVertexF 25
  {domecol, 0.0f, 0.0f, 0.0f, 24.1287,5.32719,49.3306},  //CNVertexF 42
  {domecol, 0.0f, 0.0f, 0.0f, 24.3306,-4.31197,49.3306},  //CNVertexF 41
  /* (Face 64 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 19.4829,-3.45283,60.9052},  //CNVertexF 25
  {domecol, 0.0f, 0.0f, 0.0f, 19.3212,4.26578,60.9052},  //CNVertexF 26
  {domecol, 0.0f, 0.0f, 0.0f, 24.1287,5.32719,49.3306},  //CNVertexF 42
  /* (Face 65 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 19.3212,4.26578,60.9052},  //CNVertexF 26
  {domecol, 0.0f, 0.0f, 0.0f, 20.2534,14.1553,49.3306},  //CNVertexF 43
  {domecol, 0.0f, 0.0f, 0.0f, 24.1287,5.32719,49.3306},  //CNVertexF 42
  /* (Face 66 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 19.3212,4.26578,60.9052},  //CNVertexF 26
  {domecol, 0.0f, 0.0f, 0.0f, 16.218,11.335,60.9052},  //CNVertexF 27
  {domecol, 0.0f, 0.0f, 0.0f, 20.2534,14.1553,49.3306},  //CNVertexF 43
  /* (Face 67 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 16.218,11.335,60.9052},  //CNVertexF 27
  {domecol, 0.0f, 0.0f, 0.0f, 13.2947,20.8285,49.3306},  //CNVertexF 44
  {domecol, 0.0f, 0.0f, 0.0f, 20.2534,14.1553,49.3306},  //CNVertexF 43
  /* (Face 68 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 16.218,11.335,60.9052},  //CNVertexF 27
  {domecol, 0.0f, 0.0f, 0.0f, 10.6458,16.6785,60.9052},  //CNVertexF 28
  {domecol, 0.0f, 0.0f, 0.0f, 13.2947,20.8285,49.3306},  //CNVertexF 44
  /* (Face 69 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 10.6458,16.6785,60.9052},  //CNVertexF 28
  {domecol, 0.0f, 0.0f, 0.0f, 4.31195,24.3306,49.3306},  //CNVertexF 45
  {domecol, 0.0f, 0.0f, 0.0f, 13.2947,20.8285,49.3306},  //CNVertexF 44
  /* (Face 70 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 10.6458,16.6785,60.9052},  //CNVertexF 28
  {domecol, 0.0f, 0.0f, 0.0f, 3.45282,19.4829,60.9052},  //CNVertexF 29
  {domecol, 0.0f, 0.0f, 0.0f, 4.31195,24.3306,49.3306},  //CNVertexF 45
  /* (Face 71 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 3.45282,19.4829,60.9052},  //CNVertexF 29
  {domecol, 0.0f, 0.0f, 0.0f, -5.32721,24.1287,49.3306},  //CNVertexF 46
  {domecol, 0.0f, 0.0f, 0.0f, 4.31195,24.3306,49.3306},  //CNVertexF 45
  /* (Face 72 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 3.45282,19.4829,60.9052},  //CNVertexF 29
  {domecol, 0.0f, 0.0f, 0.0f, -4.26579,19.3212,60.9052},  //CNVertexF 30
  {domecol, 0.0f, 0.0f, 0.0f, -5.32721,24.1287,49.3306},  //CNVertexF 46
  /* (Face 73 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -4.26579,19.3212,60.9052},  //CNVertexF 30
  {domecol, 0.0f, 0.0f, 0.0f, -14.1554,20.2534,49.3306},  //CNVertexF 47
  {domecol, 0.0f, 0.0f, 0.0f, -5.32721,24.1287,49.3306},  //CNVertexF 46
  /* (Face 74 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -4.26579,19.3212,60.9052},  //CNVertexF 30
  {domecol, 0.0f, 0.0f, 0.0f, -11.335,16.218,60.9052},  //CNVertexF 31
  {domecol, 0.0f, 0.0f, 0.0f, -14.1554,20.2534,49.3306},  //CNVertexF 47
  /* (Face 75 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -11.335,16.218,60.9052},  //CNVertexF 31
  {domecol, 0.0f, 0.0f, 0.0f, -20.8285,13.2946,49.3306},  //CNVertexF 48
  {domecol, 0.0f, 0.0f, 0.0f, -14.1554,20.2534,49.3306},  //CNVertexF 47
  /* (Face 76 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -11.335,16.218,60.9052},  //CNVertexF 31
  {domecol, 0.0f, 0.0f, 0.0f, -16.6785,10.6458,60.9052},  //CNVertexF 32
  {domecol, 0.0f, 0.0f, 0.0f, -20.8285,13.2946,49.3306},  //CNVertexF 48
  /* (Face 77 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -16.6785,10.6458,60.9052},  //CNVertexF 32
  {domecol, 0.0f, 0.0f, 0.0f, -24.3306,4.31194,49.3306},  //CNVertexF 49
  {domecol, 0.0f, 0.0f, 0.0f, -20.8285,13.2946,49.3306},  //CNVertexF 48
  /* (Face 78 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -16.6785,10.6458,60.9052},  //CNVertexF 32
  {domecol, 0.0f, 0.0f, 0.0f, -19.4829,3.45281,60.9052},  //CNVertexF 33
  {domecol, 0.0f, 0.0f, 0.0f, -24.3306,4.31194,49.3306},  //CNVertexF 49
  /* (Face 79 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -19.4829,3.45281,60.9052},  //CNVertexF 33
  {domecol, 0.0f, 0.0f, 0.0f, -24.1287,-5.32719,49.3306},  //CNVertexF 34
  {domecol, 0.0f, 0.0f, 0.0f, -24.3306,4.31194,49.3306},  //CNVertexF 49
  /* (Face 80 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -19.4829,3.45281,60.9052},  //CNVertexF 33
  {domecol, 0.0f, 0.0f, 0.0f, -19.3212,-4.26578,60.9052},  //CNVertexF 18
  {domecol, 0.0f, 0.0f, 0.0f, -24.1287,-5.32719,49.3306},  //CNVertexF 34
  /* (Face 81 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -24.1287,-5.32719,49.3306},  //CNVertexF 34
  {domecol, 0.0f, 0.0f, 0.0f, -21.5022,-15.0282,35.6775},  //CNVertexF 51
  {domecol, 0.0f, 0.0f, 0.0f, -25.6165,-5.65568,35.6775},  //CNVertexF 50
  /* (Face 82 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -24.1287,-5.32719,49.3306},  //CNVertexF 34
  {domecol, 0.0f, 0.0f, 0.0f, -20.2534,-14.1553,49.3306},  //CNVertexF 35
  {domecol, 0.0f, 0.0f, 0.0f, -21.5022,-15.0282,35.6775},  //CNVertexF 51
  /* (Face 83 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -20.2534,-14.1553,49.3306},  //CNVertexF 35
  {domecol, 0.0f, 0.0f, 0.0f, -14.1144,-22.1128,35.6775},  //CNVertexF 52
  {domecol, 0.0f, 0.0f, 0.0f, -21.5022,-15.0282,35.6775},  //CNVertexF 51
  /* (Face 84 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -20.2534,-14.1553,49.3306},  //CNVertexF 35
  {domecol, 0.0f, 0.0f, 0.0f, -13.2947,-20.8285,49.3306},  //CNVertexF 36
  {domecol, 0.0f, 0.0f, 0.0f, -14.1144,-22.1128,35.6775},  //CNVertexF 52
  /* (Face 85 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -13.2947,-20.8285,49.3306},  //CNVertexF 36
  {domecol, 0.0f, 0.0f, 0.0f, -4.57785,-25.8309,35.6775},  //CNVertexF 53
  {domecol, 0.0f, 0.0f, 0.0f, -14.1144,-22.1128,35.6775},  //CNVertexF 52
  /* (Face 86 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -13.2947,-20.8285,49.3306},  //CNVertexF 36
  {domecol, 0.0f, 0.0f, 0.0f, -4.31197,-24.3306,49.3306},  //CNVertexF 37
  {domecol, 0.0f, 0.0f, 0.0f, -4.57785,-25.8309,35.6775},  //CNVertexF 53
  /* (Face 87 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -4.31197,-24.3306,49.3306},  //CNVertexF 37
  {domecol, 0.0f, 0.0f, 0.0f, 5.65567,-25.6165,35.6775},  //CNVertexF 54
  {domecol, 0.0f, 0.0f, 0.0f, -4.57785,-25.8309,35.6775},  //CNVertexF 53
  /* (Face 88 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -4.31197,-24.3306,49.3306},  //CNVertexF 37
  {domecol, 0.0f, 0.0f, 0.0f, 5.32719,-24.1287,49.3306},  //CNVertexF 38
  {domecol, 0.0f, 0.0f, 0.0f, 5.65567,-25.6165,35.6775},  //CNVertexF 54
  /* (Face 89 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 5.32719,-24.1287,49.3306},  //CNVertexF 38
  {domecol, 0.0f, 0.0f, 0.0f, 15.0282,-21.5022,35.6775},  //CNVertexF 55
  {domecol, 0.0f, 0.0f, 0.0f, 5.65567,-25.6165,35.6775},  //CNVertexF 54
  /* (Face 90 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 5.32719,-24.1287,49.3306},  //CNVertexF 38
  {domecol, 0.0f, 0.0f, 0.0f, 14.1553,-20.2534,49.3306},  //CNVertexF 39
  {domecol, 0.0f, 0.0f, 0.0f, 15.0282,-21.5022,35.6775},  //CNVertexF 55
  /* (Face 91 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 14.1553,-20.2534,49.3306},  //CNVertexF 39
  {domecol, 0.0f, 0.0f, 0.0f, 22.1128,-14.1144,35.6775},  //CNVertexF 56
  {domecol, 0.0f, 0.0f, 0.0f, 15.0282,-21.5022,35.6775},  //CNVertexF 55
  /* (Face 92 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 14.1553,-20.2534,49.3306},  //CNVertexF 39
  {domecol, 0.0f, 0.0f, 0.0f, 20.8285,-13.2947,49.3306},  //CNVertexF 40
  {domecol, 0.0f, 0.0f, 0.0f, 22.1128,-14.1144,35.6775},  //CNVertexF 56
  /* (Face 93 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 20.8285,-13.2947,49.3306},  //CNVertexF 40
  {domecol, 0.0f, 0.0f, 0.0f, 25.8309,-4.57785,35.6775},  //CNVertexF 57
  {domecol, 0.0f, 0.0f, 0.0f, 22.1128,-14.1144,35.6775},  //CNVertexF 56
  /* (Face 94 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 20.8285,-13.2947,49.3306},  //CNVertexF 40
  {domecol, 0.0f, 0.0f, 0.0f, 24.3306,-4.31197,49.3306},  //CNVertexF 41
  {domecol, 0.0f, 0.0f, 0.0f, 25.8309,-4.57785,35.6775},  //CNVertexF 57
  /* (Face 95 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 24.3306,-4.31197,49.3306},  //CNVertexF 41
  {domecol, 0.0f, 0.0f, 0.0f, 25.6165,5.65568,35.6775},  //CNVertexF 58
  {domecol, 0.0f, 0.0f, 0.0f, 25.8309,-4.57785,35.6775},  //CNVertexF 57
  /* (Face 96 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 24.3306,-4.31197,49.3306},  //CNVertexF 41
  {domecol, 0.0f, 0.0f, 0.0f, 24.1287,5.32719,49.3306},  //CNVertexF 42
  {domecol, 0.0f, 0.0f, 0.0f, 25.6165,5.65568,35.6775},  //CNVertexF 58
  /* (Face 97 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 24.1287,5.32719,49.3306},  //CNVertexF 42
  {domecol, 0.0f, 0.0f, 0.0f, 21.5022,15.0282,35.6775},  //CNVertexF 59
  {domecol, 0.0f, 0.0f, 0.0f, 25.6165,5.65568,35.6775},  //CNVertexF 58
  /* (Face 98 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 24.1287,5.32719,49.3306},  //CNVertexF 42
  {domecol, 0.0f, 0.0f, 0.0f, 20.2534,14.1553,49.3306},  //CNVertexF 43
  {domecol, 0.0f, 0.0f, 0.0f, 21.5022,15.0282,35.6775},  //CNVertexF 59
  /* (Face 99 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 20.2534,14.1553,49.3306},  //CNVertexF 43
  {domecol, 0.0f, 0.0f, 0.0f, 14.1144,22.1128,35.6775},  //CNVertexF 60
  {domecol, 0.0f, 0.0f, 0.0f, 21.5022,15.0282,35.6775},  //CNVertexF 59
  /* (Face 100 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 20.2534,14.1553,49.3306},  //CNVertexF 43
  {domecol, 0.0f, 0.0f, 0.0f, 13.2947,20.8285,49.3306},  //CNVertexF 44
  {domecol, 0.0f, 0.0f, 0.0f, 14.1144,22.1128,35.6775},  //CNVertexF 60
  /* (Face 101 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 13.2947,20.8285,49.3306},  //CNVertexF 44
  {domecol, 0.0f, 0.0f, 0.0f, 4.57784,25.8309,35.6775},  //CNVertexF 61
  {domecol, 0.0f, 0.0f, 0.0f, 14.1144,22.1128,35.6775},  //CNVertexF 60
  /* (Face 102 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 13.2947,20.8285,49.3306},  //CNVertexF 44
  {domecol, 0.0f, 0.0f, 0.0f, 4.31195,24.3306,49.3306},  //CNVertexF 45
  {domecol, 0.0f, 0.0f, 0.0f, 4.57784,25.8309,35.6775},  //CNVertexF 61
  /* (Face 103 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 4.31195,24.3306,49.3306},  //CNVertexF 45
  {domecol, 0.0f, 0.0f, 0.0f, -5.6557,25.6165,35.6775},  //CNVertexF 62
  {domecol, 0.0f, 0.0f, 0.0f, 4.57784,25.8309,35.6775},  //CNVertexF 61
  /* (Face 104 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, 4.31195,24.3306,49.3306},  //CNVertexF 45
  {domecol, 0.0f, 0.0f, 0.0f, -5.32721,24.1287,49.3306},  //CNVertexF 46
  {domecol, 0.0f, 0.0f, 0.0f, -5.6557,25.6165,35.6775},  //CNVertexF 62
  /* (Face 105 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -5.32721,24.1287,49.3306},  //CNVertexF 46
  {domecol, 0.0f, 0.0f, 0.0f, -15.0282,21.5022,35.6775},  //CNVertexF 63
  {domecol, 0.0f, 0.0f, 0.0f, -5.6557,25.6165,35.6775},  //CNVertexF 62
  /* (Face 106 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -5.32721,24.1287,49.3306},  //CNVertexF 46
  {domecol, 0.0f, 0.0f, 0.0f, -14.1554,20.2534,49.3306},  //CNVertexF 47
  {domecol, 0.0f, 0.0f, 0.0f, -15.0282,21.5022,35.6775},  //CNVertexF 63
  /* (Face 107 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -14.1554,20.2534,49.3306},  //CNVertexF 47
  {domecol, 0.0f, 0.0f, 0.0f, -22.1128,14.1144,35.6775},  //CNVertexF 64
  {domecol, 0.0f, 0.0f, 0.0f, -15.0282,21.5022,35.6775},  //CNVertexF 63
  /* (Face 108 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -14.1554,20.2534,49.3306},  //CNVertexF 47
  {domecol, 0.0f, 0.0f, 0.0f, -20.8285,13.2946,49.3306},  //CNVertexF 48
  {domecol, 0.0f, 0.0f, 0.0f, -22.1128,14.1144,35.6775},  //CNVertexF 64
  /* (Face 109 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -20.8285,13.2946,49.3306},  //CNVertexF 48
  {domecol, 0.0f, 0.0f, 0.0f, -25.8309,4.57782,35.6775},  //CNVertexF 65
  {domecol, 0.0f, 0.0f, 0.0f, -22.1128,14.1144,35.6775},  //CNVertexF 64
  /* (Face 110 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -20.8285,13.2946,49.3306},  //CNVertexF 48
  {domecol, 0.0f, 0.0f, 0.0f, -24.3306,4.31194,49.3306},  //CNVertexF 49
  {domecol, 0.0f, 0.0f, 0.0f, -25.8309,4.57782,35.6775},  //CNVertexF 65
  /* (Face 111 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -24.3306,4.31194,49.3306},  //CNVertexF 49
  {domecol, 0.0f, 0.0f, 0.0f, -25.6165,-5.65568,35.6775},  //CNVertexF 50
  {domecol, 0.0f, 0.0f, 0.0f, -25.8309,4.57782,35.6775},  //CNVertexF 65
  /* (Face 112 of 112) */
  {domecol, 0.0f, 0.0f, 0.0f, -24.3306,4.31194,49.3306},  //CNVertexF 49
  {domecol, 0.0f, 0.0f, 0.0f, -24.1287,-5.32719,49.3306},  //CNVertexF 34
  {domecol, 0.0f, 0.0f, 0.0f, -25.6165,-5.65568,35.6775}  //CNVertexF 50
};   /* dome 3D Model Code End */

/*------------------------------
 base detailed information:
    Number of VertexFs: 86
    Number of Edges: 504
    Number of Faces: 168
------------------------------*/

/* base Material */
//#define basecol GU_COLOR(150,150,150,255)
//#define basecol GU_COLOR(110.0f/255.0f, 110.0f/255.0f, 110.0f/255.0f, 0.0f)
#define basecol GU_COLOR(0.43f, 0.43f, 0.43f, 1.0f)

ScePspFVector3 basePos = {0.0223274,0.0783844,17.3318};

CNVertexF __attribute__((aligned(16))) base[168*3] = {   /* base 3D Model Code Start */
  /* (Face 1 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,22.7446},  //CNVertexF 1
  {basecol, 0.0f, 0.0f, 0.0f, -9.2197,-7.24593,21.6184},  //CNVertexF 3
  {basecol, 0.0f, 0.0f, 0.0f, -11.4506,-2.52808,21.6184},  //CNVertexF 2
  /* (Face 2 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,22.7446},  //CNVertexF 1
  {basecol, 0.0f, 0.0f, 0.0f, -5.16277,-10.5286,21.6184},  //CNVertexF 4
  {basecol, 0.0f, 0.0f, 0.0f, -9.2197,-7.24593,21.6184},  //CNVertexF 3
  /* (Face 3 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,22.7446},  //CNVertexF 1
  {basecol, 0.0f, 0.0f, 0.0f, -0.0832901,-11.726,21.6184},  //CNVertexF 5
  {basecol, 0.0f, 0.0f, 0.0f, -5.16277,-10.5286,21.6184},  //CNVertexF 4
  /* (Face 4 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,22.7446},  //CNVertexF 1
  {basecol, 0.0f, 0.0f, 0.0f, 5.01269,-10.6009,21.6184},  //CNVertexF 6
  {basecol, 0.0f, 0.0f, 0.0f, -0.0832901,-11.726,21.6184},  //CNVertexF 5
  /* (Face 5 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,22.7446},  //CNVertexF 1
  {basecol, 0.0f, 0.0f, 0.0f, 9.11584,-7.37617,21.6184},  //CNVertexF 7
  {basecol, 0.0f, 0.0f, 0.0f, 5.01269,-10.6009,21.6184},  //CNVertexF 6
  /* (Face 6 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,22.7446},  //CNVertexF 1
  {basecol, 0.0f, 0.0f, 0.0f, 11.4135,-2.69049,21.6184},  //CNVertexF 8
  {basecol, 0.0f, 0.0f, 0.0f, 9.11584,-7.37617,21.6184},  //CNVertexF 7
  /* (Face 7 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,22.7446},  //CNVertexF 1
  {basecol, 0.0f, 0.0f, 0.0f, 11.4506,2.52808,21.6184},  //CNVertexF 9
  {basecol, 0.0f, 0.0f, 0.0f, 11.4135,-2.69049,21.6184},  //CNVertexF 8
  /* (Face 8 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,22.7446},  //CNVertexF 1
  {basecol, 0.0f, 0.0f, 0.0f, 9.2197,7.24594,21.6184},  //CNVertexF 10
  {basecol, 0.0f, 0.0f, 0.0f, 11.4506,2.52808,21.6184},  //CNVertexF 9
  /* (Face 9 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,22.7446},  //CNVertexF 1
  {basecol, 0.0f, 0.0f, 0.0f, 5.16277,10.5286,21.6184},  //CNVertexF 11
  {basecol, 0.0f, 0.0f, 0.0f, 9.2197,7.24594,21.6184},  //CNVertexF 10
  /* (Face 10 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,22.7446},  //CNVertexF 1
  {basecol, 0.0f, 0.0f, 0.0f, 0.0832832,11.726,21.6184},  //CNVertexF 12
  {basecol, 0.0f, 0.0f, 0.0f, 5.16277,10.5286,21.6184},  //CNVertexF 11
  /* (Face 11 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,22.7446},  //CNVertexF 1
  {basecol, 0.0f, 0.0f, 0.0f, -5.0127,10.6009,21.6184},  //CNVertexF 13
  {basecol, 0.0f, 0.0f, 0.0f, 0.0832832,11.726,21.6184},  //CNVertexF 12
  /* (Face 12 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,22.7446},  //CNVertexF 1
  {basecol, 0.0f, 0.0f, 0.0f, -9.11585,7.37616,21.6184},  //CNVertexF 14
  {basecol, 0.0f, 0.0f, 0.0f, -5.0127,10.6009,21.6184},  //CNVertexF 13
  /* (Face 13 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,22.7446},  //CNVertexF 1
  {basecol, 0.0f, 0.0f, 0.0f, -11.4135,2.69047,21.6184},  //CNVertexF 15
  {basecol, 0.0f, 0.0f, 0.0f, -9.11585,7.37616,21.6184},  //CNVertexF 14
  /* (Face 14 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,22.7446},  //CNVertexF 1
  {basecol, 0.0f, 0.0f, 0.0f, -11.4506,-2.52808,21.6184},  //CNVertexF 2
  {basecol, 0.0f, 0.0f, 0.0f, -11.4135,2.69047,21.6184},  //CNVertexF 15
  /* (Face 15 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -11.4506,-2.52808,21.6184},  //CNVertexF 2
  {basecol, 0.0f, 0.0f, 0.0f, -22.5275,-17.7048,18.4628},  //CNVertexF 17
  {basecol, 0.0f, 0.0f, 0.0f, -27.9784,-6.17714,18.4628},  //CNVertexF 16
  /* (Face 16 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -11.4506,-2.52808,21.6184},  //CNVertexF 2
  {basecol, 0.0f, 0.0f, 0.0f, -9.2197,-7.24593,21.6184},  //CNVertexF 3
  {basecol, 0.0f, 0.0f, 0.0f, -22.5275,-17.7048,18.4628},  //CNVertexF 17
  /* (Face 17 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -9.2197,-7.24593,21.6184},  //CNVertexF 3
  {basecol, 0.0f, 0.0f, 0.0f, -12.6147,-25.7257,18.4628},  //CNVertexF 18
  {basecol, 0.0f, 0.0f, 0.0f, -22.5275,-17.7048,18.4628},  //CNVertexF 17
  /* (Face 18 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -9.2197,-7.24593,21.6184},  //CNVertexF 3
  {basecol, 0.0f, 0.0f, 0.0f, -5.16277,-10.5286,21.6184},  //CNVertexF 4
  {basecol, 0.0f, 0.0f, 0.0f, -12.6147,-25.7257,18.4628},  //CNVertexF 18
  /* (Face 19 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -5.16277,-10.5286,21.6184},  //CNVertexF 4
  {basecol, 0.0f, 0.0f, 0.0f, -0.203511,-28.6514,18.4628},  //CNVertexF 19
  {basecol, 0.0f, 0.0f, 0.0f, -12.6147,-25.7257,18.4628},  //CNVertexF 18
  /* (Face 20 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -5.16277,-10.5286,21.6184},  //CNVertexF 4
  {basecol, 0.0f, 0.0f, 0.0f, -0.0832901,-11.726,21.6184},  //CNVertexF 5
  {basecol, 0.0f, 0.0f, 0.0f, -0.203511,-28.6514,18.4628},  //CNVertexF 19
  /* (Face 21 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -0.0832901,-11.726,21.6184},  //CNVertexF 5
  {basecol, 0.0f, 0.0f, 0.0f, 12.248,-25.9023,18.4628},  //CNVertexF 20
  {basecol, 0.0f, 0.0f, 0.0f, -0.203511,-28.6514,18.4628},  //CNVertexF 19
  /* (Face 22 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -0.0832901,-11.726,21.6184},  //CNVertexF 5
  {basecol, 0.0f, 0.0f, 0.0f, 5.01269,-10.6009,21.6184},  //CNVertexF 6
  {basecol, 0.0f, 0.0f, 0.0f, 12.248,-25.9023,18.4628},  //CNVertexF 20
  /* (Face 23 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 5.01269,-10.6009,21.6184},  //CNVertexF 6
  {basecol, 0.0f, 0.0f, 0.0f, 22.2737,-18.023,18.4628},  //CNVertexF 21
  {basecol, 0.0f, 0.0f, 0.0f, 12.248,-25.9023,18.4628},  //CNVertexF 20
  /* (Face 24 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 5.01269,-10.6009,21.6184},  //CNVertexF 6
  {basecol, 0.0f, 0.0f, 0.0f, 9.11584,-7.37617,21.6184},  //CNVertexF 7
  {basecol, 0.0f, 0.0f, 0.0f, 22.2737,-18.023,18.4628},  //CNVertexF 21
  /* (Face 25 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 9.11584,-7.37617,21.6184},  //CNVertexF 7
  {basecol, 0.0f, 0.0f, 0.0f, 27.8878,-6.57396,18.4628},  //CNVertexF 22
  {basecol, 0.0f, 0.0f, 0.0f, 22.2737,-18.023,18.4628},  //CNVertexF 21
  /* (Face 26 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 9.11584,-7.37617,21.6184},  //CNVertexF 7
  {basecol, 0.0f, 0.0f, 0.0f, 11.4135,-2.69049,21.6184},  //CNVertexF 8
  {basecol, 0.0f, 0.0f, 0.0f, 27.8878,-6.57396,18.4628},  //CNVertexF 22
  /* (Face 27 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 11.4135,-2.69049,21.6184},  //CNVertexF 8
  {basecol, 0.0f, 0.0f, 0.0f, 27.9784,6.17713,18.4628},  //CNVertexF 23
  {basecol, 0.0f, 0.0f, 0.0f, 27.8878,-6.57396,18.4628},  //CNVertexF 22
  /* (Face 28 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 11.4135,-2.69049,21.6184},  //CNVertexF 8
  {basecol, 0.0f, 0.0f, 0.0f, 11.4506,2.52808,21.6184},  //CNVertexF 9
  {basecol, 0.0f, 0.0f, 0.0f, 27.9784,6.17713,18.4628},  //CNVertexF 23
  /* (Face 29 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 11.4506,2.52808,21.6184},  //CNVertexF 9
  {basecol, 0.0f, 0.0f, 0.0f, 22.5275,17.7048,18.4628},  //CNVertexF 24
  {basecol, 0.0f, 0.0f, 0.0f, 27.9784,6.17713,18.4628},  //CNVertexF 23
  /* (Face 30 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 11.4506,2.52808,21.6184},  //CNVertexF 9
  {basecol, 0.0f, 0.0f, 0.0f, 9.2197,7.24594,21.6184},  //CNVertexF 10
  {basecol, 0.0f, 0.0f, 0.0f, 22.5275,17.7048,18.4628},  //CNVertexF 24
  /* (Face 31 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 9.2197,7.24594,21.6184},  //CNVertexF 10
  {basecol, 0.0f, 0.0f, 0.0f, 12.6147,25.7258,18.4628},  //CNVertexF 25
  {basecol, 0.0f, 0.0f, 0.0f, 22.5275,17.7048,18.4628},  //CNVertexF 24
  /* (Face 32 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 9.2197,7.24594,21.6184},  //CNVertexF 10
  {basecol, 0.0f, 0.0f, 0.0f, 5.16277,10.5286,21.6184},  //CNVertexF 11
  {basecol, 0.0f, 0.0f, 0.0f, 12.6147,25.7258,18.4628},  //CNVertexF 25
  /* (Face 33 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 5.16277,10.5286,21.6184},  //CNVertexF 11
  {basecol, 0.0f, 0.0f, 0.0f, 0.203495,28.6514,18.4628},  //CNVertexF 26
  {basecol, 0.0f, 0.0f, 0.0f, 12.6147,25.7258,18.4628},  //CNVertexF 25
  /* (Face 34 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 5.16277,10.5286,21.6184},  //CNVertexF 11
  {basecol, 0.0f, 0.0f, 0.0f, 0.0832832,11.726,21.6184},  //CNVertexF 12
  {basecol, 0.0f, 0.0f, 0.0f, 0.203495,28.6514,18.4628},  //CNVertexF 26
  /* (Face 35 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0832832,11.726,21.6184},  //CNVertexF 12
  {basecol, 0.0f, 0.0f, 0.0f, -12.2481,25.9023,18.4628},  //CNVertexF 27
  {basecol, 0.0f, 0.0f, 0.0f, 0.203495,28.6514,18.4628},  //CNVertexF 26
  /* (Face 36 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0832832,11.726,21.6184},  //CNVertexF 12
  {basecol, 0.0f, 0.0f, 0.0f, -5.0127,10.6009,21.6184},  //CNVertexF 13
  {basecol, 0.0f, 0.0f, 0.0f, -12.2481,25.9023,18.4628},  //CNVertexF 27
  /* (Face 37 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -5.0127,10.6009,21.6184},  //CNVertexF 13
  {basecol, 0.0f, 0.0f, 0.0f, -22.2737,18.023,18.4628},  //CNVertexF 28
  {basecol, 0.0f, 0.0f, 0.0f, -12.2481,25.9023,18.4628},  //CNVertexF 27
  /* (Face 38 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -5.0127,10.6009,21.6184},  //CNVertexF 13
  {basecol, 0.0f, 0.0f, 0.0f, -9.11585,7.37616,21.6184},  //CNVertexF 14
  {basecol, 0.0f, 0.0f, 0.0f, -22.2737,18.023,18.4628},  //CNVertexF 28
  /* (Face 39 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -9.11585,7.37616,21.6184},  //CNVertexF 14
  {basecol, 0.0f, 0.0f, 0.0f, -27.8878,6.57392,18.4628},  //CNVertexF 29
  {basecol, 0.0f, 0.0f, 0.0f, -22.2737,18.023,18.4628},  //CNVertexF 28
  /* (Face 40 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -9.11585,7.37616,21.6184},  //CNVertexF 14
  {basecol, 0.0f, 0.0f, 0.0f, -11.4135,2.69047,21.6184},  //CNVertexF 15
  {basecol, 0.0f, 0.0f, 0.0f, -27.8878,6.57392,18.4628},  //CNVertexF 29
  /* (Face 41 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -11.4135,2.69047,21.6184},  //CNVertexF 15
  {basecol, 0.0f, 0.0f, 0.0f, -27.9784,-6.17714,18.4628},  //CNVertexF 16
  {basecol, 0.0f, 0.0f, 0.0f, -27.8878,6.57392,18.4628},  //CNVertexF 29
  /* (Face 42 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -11.4135,2.69047,21.6184},  //CNVertexF 15
  {basecol, 0.0f, 0.0f, 0.0f, -11.4506,-2.52808,21.6184},  //CNVertexF 2
  {basecol, 0.0f, 0.0f, 0.0f, -27.9784,-6.17714,18.4628},  //CNVertexF 16
  /* (Face 43 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -27.9784,-6.17714,18.4628},  //CNVertexF 16
  {basecol, 0.0f, 0.0f, 0.0f, -34.0055,-26.7255,13.9029},  //CNVertexF 31
  {basecol, 0.0f, 0.0f, 0.0f, -42.2336,-9.32445,13.9029},  //CNVertexF 30
  /* (Face 44 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -27.9784,-6.17714,18.4628},  //CNVertexF 16
  {basecol, 0.0f, 0.0f, 0.0f, -22.5275,-17.7048,18.4628},  //CNVertexF 17
  {basecol, 0.0f, 0.0f, 0.0f, -34.0055,-26.7255,13.9029},  //CNVertexF 31
  /* (Face 45 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -22.5275,-17.7048,18.4628},  //CNVertexF 17
  {basecol, 0.0f, 0.0f, 0.0f, -19.0421,-38.8333,13.9029},  //CNVertexF 32
  {basecol, 0.0f, 0.0f, 0.0f, -34.0055,-26.7255,13.9029},  //CNVertexF 31
  /* (Face 46 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -22.5275,-17.7048,18.4628},  //CNVertexF 17
  {basecol, 0.0f, 0.0f, 0.0f, -12.6147,-25.7257,18.4628},  //CNVertexF 18
  {basecol, 0.0f, 0.0f, 0.0f, -19.0421,-38.8333,13.9029},  //CNVertexF 32
  /* (Face 47 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -12.6147,-25.7257,18.4628},  //CNVertexF 18
  {basecol, 0.0f, 0.0f, 0.0f, -0.307202,-43.2496,13.9029},  //CNVertexF 33
  {basecol, 0.0f, 0.0f, 0.0f, -19.0421,-38.8333,13.9029},  //CNVertexF 32
  /* (Face 48 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -12.6147,-25.7257,18.4628},  //CNVertexF 18
  {basecol, 0.0f, 0.0f, 0.0f, -0.203511,-28.6514,18.4628},  //CNVertexF 19
  {basecol, 0.0f, 0.0f, 0.0f, -0.307202,-43.2496,13.9029},  //CNVertexF 33
  /* (Face 49 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -0.203511,-28.6514,18.4628},  //CNVertexF 19
  {basecol, 0.0f, 0.0f, 0.0f, 18.4885,-39.0999,13.9029},  //CNVertexF 34
  {basecol, 0.0f, 0.0f, 0.0f, -0.307202,-43.2496,13.9029},  //CNVertexF 33
  /* (Face 50 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -0.203511,-28.6514,18.4628},  //CNVertexF 19
  {basecol, 0.0f, 0.0f, 0.0f, 12.248,-25.9023,18.4628},  //CNVertexF 20
  {basecol, 0.0f, 0.0f, 0.0f, 18.4885,-39.0999,13.9029},  //CNVertexF 34
  /* (Face 51 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 12.248,-25.9023,18.4628},  //CNVertexF 20
  {basecol, 0.0f, 0.0f, 0.0f, 33.6224,-27.2059,13.9029},  //CNVertexF 35
  {basecol, 0.0f, 0.0f, 0.0f, 18.4885,-39.0999,13.9029},  //CNVertexF 34
  /* (Face 52 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 12.248,-25.9023,18.4628},  //CNVertexF 20
  {basecol, 0.0f, 0.0f, 0.0f, 22.2737,-18.023,18.4628},  //CNVertexF 21
  {basecol, 0.0f, 0.0f, 0.0f, 33.6224,-27.2059,13.9029},  //CNVertexF 35
  /* (Face 53 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 22.2737,-18.023,18.4628},  //CNVertexF 21
  {basecol, 0.0f, 0.0f, 0.0f, 42.0969,-9.92346,13.9029},  //CNVertexF 36
  {basecol, 0.0f, 0.0f, 0.0f, 33.6224,-27.2059,13.9029},  //CNVertexF 35
  /* (Face 54 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 22.2737,-18.023,18.4628},  //CNVertexF 21
  {basecol, 0.0f, 0.0f, 0.0f, 27.8878,-6.57396,18.4628},  //CNVertexF 22
  {basecol, 0.0f, 0.0f, 0.0f, 42.0969,-9.92346,13.9029},  //CNVertexF 36
  /* (Face 55 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 27.8878,-6.57396,18.4628},  //CNVertexF 22
  {basecol, 0.0f, 0.0f, 0.0f, 42.2336,9.32445,13.9029},  //CNVertexF 37
  {basecol, 0.0f, 0.0f, 0.0f, 42.0969,-9.92346,13.9029},  //CNVertexF 36
  /* (Face 56 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 27.8878,-6.57396,18.4628},  //CNVertexF 22
  {basecol, 0.0f, 0.0f, 0.0f, 27.9784,6.17713,18.4628},  //CNVertexF 23
  {basecol, 0.0f, 0.0f, 0.0f, 42.2336,9.32445,13.9029},  //CNVertexF 37
  /* (Face 57 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 27.9784,6.17713,18.4628},  //CNVertexF 23
  {basecol, 0.0f, 0.0f, 0.0f, 34.0055,26.7255,13.9029},  //CNVertexF 38
  {basecol, 0.0f, 0.0f, 0.0f, 42.2336,9.32445,13.9029},  //CNVertexF 37
  /* (Face 58 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 27.9784,6.17713,18.4628},  //CNVertexF 23
  {basecol, 0.0f, 0.0f, 0.0f, 22.5275,17.7048,18.4628},  //CNVertexF 24
  {basecol, 0.0f, 0.0f, 0.0f, 34.0055,26.7255,13.9029},  //CNVertexF 38
  /* (Face 59 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 22.5275,17.7048,18.4628},  //CNVertexF 24
  {basecol, 0.0f, 0.0f, 0.0f, 19.0421,38.8333,13.9029},  //CNVertexF 39
  {basecol, 0.0f, 0.0f, 0.0f, 34.0055,26.7255,13.9029},  //CNVertexF 38
  /* (Face 60 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 22.5275,17.7048,18.4628},  //CNVertexF 24
  {basecol, 0.0f, 0.0f, 0.0f, 12.6147,25.7258,18.4628},  //CNVertexF 25
  {basecol, 0.0f, 0.0f, 0.0f, 19.0421,38.8333,13.9029},  //CNVertexF 39
  /* (Face 61 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 12.6147,25.7258,18.4628},  //CNVertexF 25
  {basecol, 0.0f, 0.0f, 0.0f, 0.307178,43.2496,13.9029},  //CNVertexF 40
  {basecol, 0.0f, 0.0f, 0.0f, 19.0421,38.8333,13.9029},  //CNVertexF 39
  /* (Face 62 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 12.6147,25.7258,18.4628},  //CNVertexF 25
  {basecol, 0.0f, 0.0f, 0.0f, 0.203495,28.6514,18.4628},  //CNVertexF 26
  {basecol, 0.0f, 0.0f, 0.0f, 0.307178,43.2496,13.9029},  //CNVertexF 40
  /* (Face 63 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.203495,28.6514,18.4628},  //CNVertexF 26
  {basecol, 0.0f, 0.0f, 0.0f, -18.4886,39.0999,13.9029},  //CNVertexF 41
  {basecol, 0.0f, 0.0f, 0.0f, 0.307178,43.2496,13.9029},  //CNVertexF 40
  /* (Face 64 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.203495,28.6514,18.4628},  //CNVertexF 26
  {basecol, 0.0f, 0.0f, 0.0f, -12.2481,25.9023,18.4628},  //CNVertexF 27
  {basecol, 0.0f, 0.0f, 0.0f, -18.4886,39.0999,13.9029},  //CNVertexF 41
  /* (Face 65 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -12.2481,25.9023,18.4628},  //CNVertexF 27
  {basecol, 0.0f, 0.0f, 0.0f, -33.6224,27.2059,13.9029},  //CNVertexF 42
  {basecol, 0.0f, 0.0f, 0.0f, -18.4886,39.0999,13.9029},  //CNVertexF 41
  /* (Face 66 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -12.2481,25.9023,18.4628},  //CNVertexF 27
  {basecol, 0.0f, 0.0f, 0.0f, -22.2737,18.023,18.4628},  //CNVertexF 28
  {basecol, 0.0f, 0.0f, 0.0f, -33.6224,27.2059,13.9029},  //CNVertexF 42
  /* (Face 67 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -22.2737,18.023,18.4628},  //CNVertexF 28
  {basecol, 0.0f, 0.0f, 0.0f, -42.0969,9.9234,13.9029},  //CNVertexF 43
  {basecol, 0.0f, 0.0f, 0.0f, -33.6224,27.2059,13.9029},  //CNVertexF 42
  /* (Face 68 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -22.2737,18.023,18.4628},  //CNVertexF 28
  {basecol, 0.0f, 0.0f, 0.0f, -27.8878,6.57392,18.4628},  //CNVertexF 29
  {basecol, 0.0f, 0.0f, 0.0f, -42.0969,9.9234,13.9029},  //CNVertexF 43
  /* (Face 69 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -27.8878,6.57392,18.4628},  //CNVertexF 29
  {basecol, 0.0f, 0.0f, 0.0f, -42.2336,-9.32445,13.9029},  //CNVertexF 30
  {basecol, 0.0f, 0.0f, 0.0f, -42.0969,9.9234,13.9029},  //CNVertexF 43
  /* (Face 70 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -27.8878,6.57392,18.4628},  //CNVertexF 29
  {basecol, 0.0f, 0.0f, 0.0f, -27.9784,-6.17714,18.4628},  //CNVertexF 16
  {basecol, 0.0f, 0.0f, 0.0f, -42.2336,-9.32445,13.9029},  //CNVertexF 30
  /* (Face 71 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -42.2336,-9.32445,13.9029},  //CNVertexF 30
  {basecol, 0.0f, 0.0f, 0.0f, -34.0055,-26.7255,8.84173},  //CNVertexF 45
  {basecol, 0.0f, 0.0f, 0.0f, -42.2336,-9.32445,8.84173},  //CNVertexF 44
  /* (Face 72 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -42.2336,-9.32445,13.9029},  //CNVertexF 30
  {basecol, 0.0f, 0.0f, 0.0f, -34.0055,-26.7255,13.9029},  //CNVertexF 31
  {basecol, 0.0f, 0.0f, 0.0f, -34.0055,-26.7255,8.84173},  //CNVertexF 45
  /* (Face 73 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -34.0055,-26.7255,13.9029},  //CNVertexF 31
  {basecol, 0.0f, 0.0f, 0.0f, -19.0421,-38.8333,8.84173},  //CNVertexF 46
  {basecol, 0.0f, 0.0f, 0.0f, -34.0055,-26.7255,8.84173},  //CNVertexF 45
  /* (Face 74 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -34.0055,-26.7255,13.9029},  //CNVertexF 31
  {basecol, 0.0f, 0.0f, 0.0f, -19.0421,-38.8333,13.9029},  //CNVertexF 32
  {basecol, 0.0f, 0.0f, 0.0f, -19.0421,-38.8333,8.84173},  //CNVertexF 46
  /* (Face 75 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -19.0421,-38.8333,13.9029},  //CNVertexF 32
  {basecol, 0.0f, 0.0f, 0.0f, -0.307202,-43.2496,8.84173},  //CNVertexF 47
  {basecol, 0.0f, 0.0f, 0.0f, -19.0421,-38.8333,8.84173},  //CNVertexF 46
  /* (Face 76 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -19.0421,-38.8333,13.9029},  //CNVertexF 32
  {basecol, 0.0f, 0.0f, 0.0f, -0.307202,-43.2496,13.9029},  //CNVertexF 33
  {basecol, 0.0f, 0.0f, 0.0f, -0.307202,-43.2496,8.84173},  //CNVertexF 47
  /* (Face 77 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -0.307202,-43.2496,13.9029},  //CNVertexF 33
  {basecol, 0.0f, 0.0f, 0.0f, 18.4885,-39.0999,8.84173},  //CNVertexF 48
  {basecol, 0.0f, 0.0f, 0.0f, -0.307202,-43.2496,8.84173},  //CNVertexF 47
  /* (Face 78 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -0.307202,-43.2496,13.9029},  //CNVertexF 33
  {basecol, 0.0f, 0.0f, 0.0f, 18.4885,-39.0999,13.9029},  //CNVertexF 34
  {basecol, 0.0f, 0.0f, 0.0f, 18.4885,-39.0999,8.84173},  //CNVertexF 48
  /* (Face 79 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 18.4885,-39.0999,13.9029},  //CNVertexF 34
  {basecol, 0.0f, 0.0f, 0.0f, 33.6224,-27.2059,8.84173},  //CNVertexF 49
  {basecol, 0.0f, 0.0f, 0.0f, 18.4885,-39.0999,8.84173},  //CNVertexF 48
  /* (Face 80 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 18.4885,-39.0999,13.9029},  //CNVertexF 34
  {basecol, 0.0f, 0.0f, 0.0f, 33.6224,-27.2059,13.9029},  //CNVertexF 35
  {basecol, 0.0f, 0.0f, 0.0f, 33.6224,-27.2059,8.84173},  //CNVertexF 49
  /* (Face 81 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 33.6224,-27.2059,13.9029},  //CNVertexF 35
  {basecol, 0.0f, 0.0f, 0.0f, 42.0969,-9.92346,8.84173},  //CNVertexF 50
  {basecol, 0.0f, 0.0f, 0.0f, 33.6224,-27.2059,8.84173},  //CNVertexF 49
  /* (Face 82 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 33.6224,-27.2059,13.9029},  //CNVertexF 35
  {basecol, 0.0f, 0.0f, 0.0f, 42.0969,-9.92346,13.9029},  //CNVertexF 36
  {basecol, 0.0f, 0.0f, 0.0f, 42.0969,-9.92346,8.84173},  //CNVertexF 50
  /* (Face 83 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 42.0969,-9.92346,13.9029},  //CNVertexF 36
  {basecol, 0.0f, 0.0f, 0.0f, 42.2336,9.32445,8.84173},  //CNVertexF 51
  {basecol, 0.0f, 0.0f, 0.0f, 42.0969,-9.92346,8.84173},  //CNVertexF 50
  /* (Face 84 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 42.0969,-9.92346,13.9029},  //CNVertexF 36
  {basecol, 0.0f, 0.0f, 0.0f, 42.2336,9.32445,13.9029},  //CNVertexF 37
  {basecol, 0.0f, 0.0f, 0.0f, 42.2336,9.32445,8.84173},  //CNVertexF 51
  /* (Face 85 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 42.2336,9.32445,13.9029},  //CNVertexF 37
  {basecol, 0.0f, 0.0f, 0.0f, 34.0055,26.7255,8.84173},  //CNVertexF 52
  {basecol, 0.0f, 0.0f, 0.0f, 42.2336,9.32445,8.84173},  //CNVertexF 51
  /* (Face 86 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 42.2336,9.32445,13.9029},  //CNVertexF 37
  {basecol, 0.0f, 0.0f, 0.0f, 34.0055,26.7255,13.9029},  //CNVertexF 38
  {basecol, 0.0f, 0.0f, 0.0f, 34.0055,26.7255,8.84173},  //CNVertexF 52
  /* (Face 87 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 34.0055,26.7255,13.9029},  //CNVertexF 38
  {basecol, 0.0f, 0.0f, 0.0f, 19.0421,38.8333,8.84173},  //CNVertexF 53
  {basecol, 0.0f, 0.0f, 0.0f, 34.0055,26.7255,8.84173},  //CNVertexF 52
  /* (Face 88 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 34.0055,26.7255,13.9029},  //CNVertexF 38
  {basecol, 0.0f, 0.0f, 0.0f, 19.0421,38.8333,13.9029},  //CNVertexF 39
  {basecol, 0.0f, 0.0f, 0.0f, 19.0421,38.8333,8.84173},  //CNVertexF 53
  /* (Face 89 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 19.0421,38.8333,13.9029},  //CNVertexF 39
  {basecol, 0.0f, 0.0f, 0.0f, 0.307178,43.2496,8.84173},  //CNVertexF 54
  {basecol, 0.0f, 0.0f, 0.0f, 19.0421,38.8333,8.84173},  //CNVertexF 53
  /* (Face 90 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 19.0421,38.8333,13.9029},  //CNVertexF 39
  {basecol, 0.0f, 0.0f, 0.0f, 0.307178,43.2496,13.9029},  //CNVertexF 40
  {basecol, 0.0f, 0.0f, 0.0f, 0.307178,43.2496,8.84173},  //CNVertexF 54
  /* (Face 91 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.307178,43.2496,13.9029},  //CNVertexF 40
  {basecol, 0.0f, 0.0f, 0.0f, -18.4886,39.0998,8.84173},  //CNVertexF 55
  {basecol, 0.0f, 0.0f, 0.0f, 0.307178,43.2496,8.84173},  //CNVertexF 54
  /* (Face 92 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.307178,43.2496,13.9029},  //CNVertexF 40
  {basecol, 0.0f, 0.0f, 0.0f, -18.4886,39.0999,13.9029},  //CNVertexF 41
  {basecol, 0.0f, 0.0f, 0.0f, -18.4886,39.0998,8.84173},  //CNVertexF 55
  /* (Face 93 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -18.4886,39.0999,13.9029},  //CNVertexF 41
  {basecol, 0.0f, 0.0f, 0.0f, -33.6224,27.2058,8.84173},  //CNVertexF 56
  {basecol, 0.0f, 0.0f, 0.0f, -18.4886,39.0998,8.84173},  //CNVertexF 55
  /* (Face 94 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -18.4886,39.0999,13.9029},  //CNVertexF 41
  {basecol, 0.0f, 0.0f, 0.0f, -33.6224,27.2059,13.9029},  //CNVertexF 42
  {basecol, 0.0f, 0.0f, 0.0f, -33.6224,27.2058,8.84173},  //CNVertexF 56
  /* (Face 95 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -33.6224,27.2059,13.9029},  //CNVertexF 42
  {basecol, 0.0f, 0.0f, 0.0f, -42.0969,9.9234,8.84173},  //CNVertexF 57
  {basecol, 0.0f, 0.0f, 0.0f, -33.6224,27.2058,8.84173},  //CNVertexF 56
  /* (Face 96 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -33.6224,27.2059,13.9029},  //CNVertexF 42
  {basecol, 0.0f, 0.0f, 0.0f, -42.0969,9.9234,13.9029},  //CNVertexF 43
  {basecol, 0.0f, 0.0f, 0.0f, -42.0969,9.9234,8.84173},  //CNVertexF 57
  /* (Face 97 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -42.0969,9.9234,13.9029},  //CNVertexF 43
  {basecol, 0.0f, 0.0f, 0.0f, -42.2336,-9.32445,8.84173},  //CNVertexF 44
  {basecol, 0.0f, 0.0f, 0.0f, -42.0969,9.9234,8.84173},  //CNVertexF 57
  /* (Face 98 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -42.0969,9.9234,13.9029},  //CNVertexF 43
  {basecol, 0.0f, 0.0f, 0.0f, -42.2336,-9.32445,13.9029},  //CNVertexF 30
  {basecol, 0.0f, 0.0f, 0.0f, -42.2336,-9.32445,8.84173},  //CNVertexF 44
  /* (Face 99 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -42.2336,-9.32445,8.84173},  //CNVertexF 44
  {basecol, 0.0f, 0.0f, 0.0f, -22.5275,-17.7048,4.28179},  //CNVertexF 59
  {basecol, 0.0f, 0.0f, 0.0f, -27.9784,-6.17713,4.28179},  //CNVertexF 58
  /* (Face 100 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -42.2336,-9.32445,8.84173},  //CNVertexF 44
  {basecol, 0.0f, 0.0f, 0.0f, -34.0055,-26.7255,8.84173},  //CNVertexF 45
  {basecol, 0.0f, 0.0f, 0.0f, -22.5275,-17.7048,4.28179},  //CNVertexF 59
  /* (Face 101 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -34.0055,-26.7255,8.84173},  //CNVertexF 45
  {basecol, 0.0f, 0.0f, 0.0f, -12.6147,-25.7257,4.28179},  //CNVertexF 60
  {basecol, 0.0f, 0.0f, 0.0f, -22.5275,-17.7048,4.28179},  //CNVertexF 59
  /* (Face 102 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -34.0055,-26.7255,8.84173},  //CNVertexF 45
  {basecol, 0.0f, 0.0f, 0.0f, -19.0421,-38.8333,8.84173},  //CNVertexF 46
  {basecol, 0.0f, 0.0f, 0.0f, -12.6147,-25.7257,4.28179},  //CNVertexF 60
  /* (Face 103 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -19.0421,-38.8333,8.84173},  //CNVertexF 46
  {basecol, 0.0f, 0.0f, 0.0f, -0.203511,-28.6514,4.28179},  //CNVertexF 61
  {basecol, 0.0f, 0.0f, 0.0f, -12.6147,-25.7257,4.28179},  //CNVertexF 60
  /* (Face 104 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -19.0421,-38.8333,8.84173},  //CNVertexF 46
  {basecol, 0.0f, 0.0f, 0.0f, -0.307202,-43.2496,8.84173},  //CNVertexF 47
  {basecol, 0.0f, 0.0f, 0.0f, -0.203511,-28.6514,4.28179},  //CNVertexF 61
  /* (Face 105 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -0.307202,-43.2496,8.84173},  //CNVertexF 47
  {basecol, 0.0f, 0.0f, 0.0f, 12.248,-25.9023,4.28179},  //CNVertexF 62
  {basecol, 0.0f, 0.0f, 0.0f, -0.203511,-28.6514,4.28179},  //CNVertexF 61
  /* (Face 106 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -0.307202,-43.2496,8.84173},  //CNVertexF 47
  {basecol, 0.0f, 0.0f, 0.0f, 18.4885,-39.0999,8.84173},  //CNVertexF 48
  {basecol, 0.0f, 0.0f, 0.0f, 12.248,-25.9023,4.28179},  //CNVertexF 62
  /* (Face 107 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 18.4885,-39.0999,8.84173},  //CNVertexF 48
  {basecol, 0.0f, 0.0f, 0.0f, 22.2737,-18.023,4.28179},  //CNVertexF 63
  {basecol, 0.0f, 0.0f, 0.0f, 12.248,-25.9023,4.28179},  //CNVertexF 62
  /* (Face 108 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 18.4885,-39.0999,8.84173},  //CNVertexF 48
  {basecol, 0.0f, 0.0f, 0.0f, 33.6224,-27.2059,8.84173},  //CNVertexF 49
  {basecol, 0.0f, 0.0f, 0.0f, 22.2737,-18.023,4.28179},  //CNVertexF 63
  /* (Face 109 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 33.6224,-27.2059,8.84173},  //CNVertexF 49
  {basecol, 0.0f, 0.0f, 0.0f, 27.8878,-6.57396,4.28179},  //CNVertexF 64
  {basecol, 0.0f, 0.0f, 0.0f, 22.2737,-18.023,4.28179},  //CNVertexF 63
  /* (Face 110 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 33.6224,-27.2059,8.84173},  //CNVertexF 49
  {basecol, 0.0f, 0.0f, 0.0f, 42.0969,-9.92346,8.84173},  //CNVertexF 50
  {basecol, 0.0f, 0.0f, 0.0f, 27.8878,-6.57396,4.28179},  //CNVertexF 64
  /* (Face 111 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 42.0969,-9.92346,8.84173},  //CNVertexF 50
  {basecol, 0.0f, 0.0f, 0.0f, 27.9784,6.17713,4.28179},  //CNVertexF 65
  {basecol, 0.0f, 0.0f, 0.0f, 27.8878,-6.57396,4.28179},  //CNVertexF 64
  /* (Face 112 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 42.0969,-9.92346,8.84173},  //CNVertexF 50
  {basecol, 0.0f, 0.0f, 0.0f, 42.2336,9.32445,8.84173},  //CNVertexF 51
  {basecol, 0.0f, 0.0f, 0.0f, 27.9784,6.17713,4.28179},  //CNVertexF 65
  /* (Face 113 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 42.2336,9.32445,8.84173},  //CNVertexF 51
  {basecol, 0.0f, 0.0f, 0.0f, 22.5275,17.7048,4.28179},  //CNVertexF 66
  {basecol, 0.0f, 0.0f, 0.0f, 27.9784,6.17713,4.28179},  //CNVertexF 65
  /* (Face 114 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 42.2336,9.32445,8.84173},  //CNVertexF 51
  {basecol, 0.0f, 0.0f, 0.0f, 34.0055,26.7255,8.84173},  //CNVertexF 52
  {basecol, 0.0f, 0.0f, 0.0f, 22.5275,17.7048,4.28179},  //CNVertexF 66
  /* (Face 115 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 34.0055,26.7255,8.84173},  //CNVertexF 52
  {basecol, 0.0f, 0.0f, 0.0f, 12.6147,25.7257,4.28179},  //CNVertexF 67
  {basecol, 0.0f, 0.0f, 0.0f, 22.5275,17.7048,4.28179},  //CNVertexF 66
  /* (Face 116 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 34.0055,26.7255,8.84173},  //CNVertexF 52
  {basecol, 0.0f, 0.0f, 0.0f, 19.0421,38.8333,8.84173},  //CNVertexF 53
  {basecol, 0.0f, 0.0f, 0.0f, 12.6147,25.7257,4.28179},  //CNVertexF 67
  /* (Face 117 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 19.0421,38.8333,8.84173},  //CNVertexF 53
  {basecol, 0.0f, 0.0f, 0.0f, 0.203495,28.6514,4.28179},  //CNVertexF 68
  {basecol, 0.0f, 0.0f, 0.0f, 12.6147,25.7257,4.28179},  //CNVertexF 67
  /* (Face 118 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 19.0421,38.8333,8.84173},  //CNVertexF 53
  {basecol, 0.0f, 0.0f, 0.0f, 0.307178,43.2496,8.84173},  //CNVertexF 54
  {basecol, 0.0f, 0.0f, 0.0f, 0.203495,28.6514,4.28179},  //CNVertexF 68
  /* (Face 119 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.307178,43.2496,8.84173},  //CNVertexF 54
  {basecol, 0.0f, 0.0f, 0.0f, -12.248,25.9023,4.28179},  //CNVertexF 69
  {basecol, 0.0f, 0.0f, 0.0f, 0.203495,28.6514,4.28179},  //CNVertexF 68
  /* (Face 120 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.307178,43.2496,8.84173},  //CNVertexF 54
  {basecol, 0.0f, 0.0f, 0.0f, -18.4886,39.0998,8.84173},  //CNVertexF 55
  {basecol, 0.0f, 0.0f, 0.0f, -12.248,25.9023,4.28179},  //CNVertexF 69
  /* (Face 121 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -18.4886,39.0998,8.84173},  //CNVertexF 55
  {basecol, 0.0f, 0.0f, 0.0f, -22.2737,18.023,4.28179},  //CNVertexF 70
  {basecol, 0.0f, 0.0f, 0.0f, -12.248,25.9023,4.28179},  //CNVertexF 69
  /* (Face 122 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -18.4886,39.0998,8.84173},  //CNVertexF 55
  {basecol, 0.0f, 0.0f, 0.0f, -33.6224,27.2058,8.84173},  //CNVertexF 56
  {basecol, 0.0f, 0.0f, 0.0f, -22.2737,18.023,4.28179},  //CNVertexF 70
  /* (Face 123 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -33.6224,27.2058,8.84173},  //CNVertexF 56
  {basecol, 0.0f, 0.0f, 0.0f, -27.8878,6.57392,4.28179},  //CNVertexF 71
  {basecol, 0.0f, 0.0f, 0.0f, -22.2737,18.023,4.28179},  //CNVertexF 70
  /* (Face 124 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -33.6224,27.2058,8.84173},  //CNVertexF 56
  {basecol, 0.0f, 0.0f, 0.0f, -42.0969,9.9234,8.84173},  //CNVertexF 57
  {basecol, 0.0f, 0.0f, 0.0f, -27.8878,6.57392,4.28179},  //CNVertexF 71
  /* (Face 125 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -42.0969,9.9234,8.84173},  //CNVertexF 57
  {basecol, 0.0f, 0.0f, 0.0f, -27.9784,-6.17713,4.28179},  //CNVertexF 58
  {basecol, 0.0f, 0.0f, 0.0f, -27.8878,6.57392,4.28179},  //CNVertexF 71
  /* (Face 126 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -42.0969,9.9234,8.84173},  //CNVertexF 57
  {basecol, 0.0f, 0.0f, 0.0f, -42.2336,-9.32445,8.84173},  //CNVertexF 44
  {basecol, 0.0f, 0.0f, 0.0f, -27.9784,-6.17713,4.28179},  //CNVertexF 58
  /* (Face 127 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -27.9784,-6.17713,4.28179},  //CNVertexF 58
  {basecol, 0.0f, 0.0f, 0.0f, -9.21969,-7.24593,1.12621},  //CNVertexF 73
  {basecol, 0.0f, 0.0f, 0.0f, -11.4506,-2.52808,1.12621},  //CNVertexF 72
  /* (Face 128 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -27.9784,-6.17713,4.28179},  //CNVertexF 58
  {basecol, 0.0f, 0.0f, 0.0f, -22.5275,-17.7048,4.28179},  //CNVertexF 59
  {basecol, 0.0f, 0.0f, 0.0f, -9.21969,-7.24593,1.12621},  //CNVertexF 73
  /* (Face 129 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -22.5275,-17.7048,4.28179},  //CNVertexF 59
  {basecol, 0.0f, 0.0f, 0.0f, -5.16277,-10.5286,1.12621},  //CNVertexF 74
  {basecol, 0.0f, 0.0f, 0.0f, -9.21969,-7.24593,1.12621},  //CNVertexF 73
  /* (Face 130 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -22.5275,-17.7048,4.28179},  //CNVertexF 59
  {basecol, 0.0f, 0.0f, 0.0f, -12.6147,-25.7257,4.28179},  //CNVertexF 60
  {basecol, 0.0f, 0.0f, 0.0f, -5.16277,-10.5286,1.12621},  //CNVertexF 74
  /* (Face 131 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -12.6147,-25.7257,4.28179},  //CNVertexF 60
  {basecol, 0.0f, 0.0f, 0.0f, -0.0832899,-11.726,1.12621},  //CNVertexF 75
  {basecol, 0.0f, 0.0f, 0.0f, -5.16277,-10.5286,1.12621},  //CNVertexF 74
  /* (Face 132 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -12.6147,-25.7257,4.28179},  //CNVertexF 60
  {basecol, 0.0f, 0.0f, 0.0f, -0.203511,-28.6514,4.28179},  //CNVertexF 61
  {basecol, 0.0f, 0.0f, 0.0f, -0.0832899,-11.726,1.12621},  //CNVertexF 75
  /* (Face 133 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -0.203511,-28.6514,4.28179},  //CNVertexF 61
  {basecol, 0.0f, 0.0f, 0.0f, 5.01268,-10.6009,1.12621},  //CNVertexF 76
  {basecol, 0.0f, 0.0f, 0.0f, -0.0832899,-11.726,1.12621},  //CNVertexF 75
  /* (Face 134 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -0.203511,-28.6514,4.28179},  //CNVertexF 61
  {basecol, 0.0f, 0.0f, 0.0f, 12.248,-25.9023,4.28179},  //CNVertexF 62
  {basecol, 0.0f, 0.0f, 0.0f, 5.01268,-10.6009,1.12621},  //CNVertexF 76
  /* (Face 135 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 12.248,-25.9023,4.28179},  //CNVertexF 62
  {basecol, 0.0f, 0.0f, 0.0f, 9.11583,-7.37617,1.12621},  //CNVertexF 77
  {basecol, 0.0f, 0.0f, 0.0f, 5.01268,-10.6009,1.12621},  //CNVertexF 76
  /* (Face 136 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 12.248,-25.9023,4.28179},  //CNVertexF 62
  {basecol, 0.0f, 0.0f, 0.0f, 22.2737,-18.023,4.28179},  //CNVertexF 63
  {basecol, 0.0f, 0.0f, 0.0f, 9.11583,-7.37617,1.12621},  //CNVertexF 77
  /* (Face 137 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 22.2737,-18.023,4.28179},  //CNVertexF 63
  {basecol, 0.0f, 0.0f, 0.0f, 11.4135,-2.69049,1.12621},  //CNVertexF 78
  {basecol, 0.0f, 0.0f, 0.0f, 9.11583,-7.37617,1.12621},  //CNVertexF 77
  /* (Face 138 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 22.2737,-18.023,4.28179},  //CNVertexF 63
  {basecol, 0.0f, 0.0f, 0.0f, 27.8878,-6.57396,4.28179},  //CNVertexF 64
  {basecol, 0.0f, 0.0f, 0.0f, 11.4135,-2.69049,1.12621},  //CNVertexF 78
  /* (Face 139 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 27.8878,-6.57396,4.28179},  //CNVertexF 64
  {basecol, 0.0f, 0.0f, 0.0f, 11.4506,2.52808,1.12621},  //CNVertexF 79
  {basecol, 0.0f, 0.0f, 0.0f, 11.4135,-2.69049,1.12621},  //CNVertexF 78
  /* (Face 140 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 27.8878,-6.57396,4.28179},  //CNVertexF 64
  {basecol, 0.0f, 0.0f, 0.0f, 27.9784,6.17713,4.28179},  //CNVertexF 65
  {basecol, 0.0f, 0.0f, 0.0f, 11.4506,2.52808,1.12621},  //CNVertexF 79
  /* (Face 141 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 27.9784,6.17713,4.28179},  //CNVertexF 65
  {basecol, 0.0f, 0.0f, 0.0f, 9.21969,7.24593,1.12621},  //CNVertexF 80
  {basecol, 0.0f, 0.0f, 0.0f, 11.4506,2.52808,1.12621},  //CNVertexF 79
  /* (Face 142 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 27.9784,6.17713,4.28179},  //CNVertexF 65
  {basecol, 0.0f, 0.0f, 0.0f, 22.5275,17.7048,4.28179},  //CNVertexF 66
  {basecol, 0.0f, 0.0f, 0.0f, 9.21969,7.24593,1.12621},  //CNVertexF 80
  /* (Face 143 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 22.5275,17.7048,4.28179},  //CNVertexF 66
  {basecol, 0.0f, 0.0f, 0.0f, 5.16276,10.5286,1.12621},  //CNVertexF 81
  {basecol, 0.0f, 0.0f, 0.0f, 9.21969,7.24593,1.12621},  //CNVertexF 80
  /* (Face 144 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 22.5275,17.7048,4.28179},  //CNVertexF 66
  {basecol, 0.0f, 0.0f, 0.0f, 12.6147,25.7257,4.28179},  //CNVertexF 67
  {basecol, 0.0f, 0.0f, 0.0f, 5.16276,10.5286,1.12621},  //CNVertexF 81
  /* (Face 145 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 12.6147,25.7257,4.28179},  //CNVertexF 67
  {basecol, 0.0f, 0.0f, 0.0f, 0.0832832,11.726,1.12621},  //CNVertexF 82
  {basecol, 0.0f, 0.0f, 0.0f, 5.16276,10.5286,1.12621},  //CNVertexF 81
  /* (Face 146 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 12.6147,25.7257,4.28179},  //CNVertexF 67
  {basecol, 0.0f, 0.0f, 0.0f, 0.203495,28.6514,4.28179},  //CNVertexF 68
  {basecol, 0.0f, 0.0f, 0.0f, 0.0832832,11.726,1.12621},  //CNVertexF 82
  /* (Face 147 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.203495,28.6514,4.28179},  //CNVertexF 68
  {basecol, 0.0f, 0.0f, 0.0f, -5.01269,10.6009,1.12621},  //CNVertexF 83
  {basecol, 0.0f, 0.0f, 0.0f, 0.0832832,11.726,1.12621},  //CNVertexF 82
  /* (Face 148 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.203495,28.6514,4.28179},  //CNVertexF 68
  {basecol, 0.0f, 0.0f, 0.0f, -12.248,25.9023,4.28179},  //CNVertexF 69
  {basecol, 0.0f, 0.0f, 0.0f, -5.01269,10.6009,1.12621},  //CNVertexF 83
  /* (Face 149 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -12.248,25.9023,4.28179},  //CNVertexF 69
  {basecol, 0.0f, 0.0f, 0.0f, -9.11584,7.37616,1.12621},  //CNVertexF 84
  {basecol, 0.0f, 0.0f, 0.0f, -5.01269,10.6009,1.12621},  //CNVertexF 83
  /* (Face 150 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -12.248,25.9023,4.28179},  //CNVertexF 69
  {basecol, 0.0f, 0.0f, 0.0f, -22.2737,18.023,4.28179},  //CNVertexF 70
  {basecol, 0.0f, 0.0f, 0.0f, -9.11584,7.37616,1.12621},  //CNVertexF 84
  /* (Face 151 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -22.2737,18.023,4.28179},  //CNVertexF 70
  {basecol, 0.0f, 0.0f, 0.0f, -11.4135,2.69047,1.12621},  //CNVertexF 85
  {basecol, 0.0f, 0.0f, 0.0f, -9.11584,7.37616,1.12621},  //CNVertexF 84
  /* (Face 152 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -22.2737,18.023,4.28179},  //CNVertexF 70
  {basecol, 0.0f, 0.0f, 0.0f, -27.8878,6.57392,4.28179},  //CNVertexF 71
  {basecol, 0.0f, 0.0f, 0.0f, -11.4135,2.69047,1.12621},  //CNVertexF 85
  /* (Face 153 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -27.8878,6.57392,4.28179},  //CNVertexF 71
  {basecol, 0.0f, 0.0f, 0.0f, -11.4506,-2.52808,1.12621},  //CNVertexF 72
  {basecol, 0.0f, 0.0f, 0.0f, -11.4135,2.69047,1.12621},  //CNVertexF 85
  /* (Face 154 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, -27.8878,6.57392,4.28179},  //CNVertexF 71
  {basecol, 0.0f, 0.0f, 0.0f, -27.9784,-6.17713,4.28179},  //CNVertexF 58
  {basecol, 0.0f, 0.0f, 0.0f, -11.4506,-2.52808,1.12621},  //CNVertexF 72
  /* (Face 155 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 86
  {basecol, 0.0f, 0.0f, 0.0f, -11.4506,-2.52808,1.12621},  //CNVertexF 72
  {basecol, 0.0f, 0.0f, 0.0f, -9.21969,-7.24593,1.12621},  //CNVertexF 73
  /* (Face 156 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 86
  {basecol, 0.0f, 0.0f, 0.0f, -9.21969,-7.24593,1.12621},  //CNVertexF 73
  {basecol, 0.0f, 0.0f, 0.0f, -5.16277,-10.5286,1.12621},  //CNVertexF 74
  /* (Face 157 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 86
  {basecol, 0.0f, 0.0f, 0.0f, -5.16277,-10.5286,1.12621},  //CNVertexF 74
  {basecol, 0.0f, 0.0f, 0.0f, -0.0832899,-11.726,1.12621},  //CNVertexF 75
  /* (Face 158 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 86
  {basecol, 0.0f, 0.0f, 0.0f, -0.0832899,-11.726,1.12621},  //CNVertexF 75
  {basecol, 0.0f, 0.0f, 0.0f, 5.01268,-10.6009,1.12621},  //CNVertexF 76
  /* (Face 159 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 86
  {basecol, 0.0f, 0.0f, 0.0f, 5.01268,-10.6009,1.12621},  //CNVertexF 76
  {basecol, 0.0f, 0.0f, 0.0f, 9.11583,-7.37617,1.12621},  //CNVertexF 77
  /* (Face 160 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 86
  {basecol, 0.0f, 0.0f, 0.0f, 9.11583,-7.37617,1.12621},  //CNVertexF 77
  {basecol, 0.0f, 0.0f, 0.0f, 11.4135,-2.69049,1.12621},  //CNVertexF 78
  /* (Face 161 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 86
  {basecol, 0.0f, 0.0f, 0.0f, 11.4135,-2.69049,1.12621},  //CNVertexF 78
  {basecol, 0.0f, 0.0f, 0.0f, 11.4506,2.52808,1.12621},  //CNVertexF 79
  /* (Face 162 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 86
  {basecol, 0.0f, 0.0f, 0.0f, 11.4506,2.52808,1.12621},  //CNVertexF 79
  {basecol, 0.0f, 0.0f, 0.0f, 9.21969,7.24593,1.12621},  //CNVertexF 80
  /* (Face 163 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 86
  {basecol, 0.0f, 0.0f, 0.0f, 9.21969,7.24593,1.12621},  //CNVertexF 80
  {basecol, 0.0f, 0.0f, 0.0f, 5.16276,10.5286,1.12621},  //CNVertexF 81
  /* (Face 164 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 86
  {basecol, 0.0f, 0.0f, 0.0f, 5.16276,10.5286,1.12621},  //CNVertexF 81
  {basecol, 0.0f, 0.0f, 0.0f, 0.0832832,11.726,1.12621},  //CNVertexF 82
  /* (Face 165 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 86
  {basecol, 0.0f, 0.0f, 0.0f, 0.0832832,11.726,1.12621},  //CNVertexF 82
  {basecol, 0.0f, 0.0f, 0.0f, -5.01269,10.6009,1.12621},  //CNVertexF 83
  /* (Face 166 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 86
  {basecol, 0.0f, 0.0f, 0.0f, -5.01269,10.6009,1.12621},  //CNVertexF 83
  {basecol, 0.0f, 0.0f, 0.0f, -9.11584,7.37616,1.12621},  //CNVertexF 84
  /* (Face 167 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 86
  {basecol, 0.0f, 0.0f, 0.0f, -9.11584,7.37616,1.12621},  //CNVertexF 84
  {basecol, 0.0f, 0.0f, 0.0f, -11.4135,2.69047,1.12621},  //CNVertexF 85
  /* (Face 168 of 168) */
  {basecol, 0.0f, 0.0f, 0.0f, 0.0,0.0,0.0},  //CNVertexF 86
  {basecol, 0.0f, 0.0f, 0.0f, -11.4135,2.69047,1.12621},  //CNVertexF 85
  {basecol, 0.0f, 0.0f, 0.0f, -11.4506,-2.52808,1.12621}  //CNVertexF 72
};   /* base 3D Model Code End */

#define retcol GU_COLOR(0.12f, 0.04f, 0.51f, 0.5f)

/*------------------------------
 ret1 detailed information:
    Number of VertexFs: 8
    Number of Edges: 36
    Number of Faces: 12
------------------------------*/

ScePspFVector3 ret1Pos = {200.0,0.0,40.0};

CNVertexF __attribute__((aligned(16))) ret1[12*3] = {   /* ret1 3D Model Code Start */
  /* (Face 1 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-15.0,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,15.0,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,15.0,0.0},  //CNVertexF 3
  /* (Face 2 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,15.0,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-15.0,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-15.0,0.0},  //CNVertexF 2
  /* (Face 3 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-15.0,30.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,15.0,30.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-15.0,30.0},  //CNVertexF 6
  /* (Face 4 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,15.0,30.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-15.0,30.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,15.0,30.0},  //CNVertexF 7
  /* (Face 5 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-15.0,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-15.0,30.0},  //CNVertexF 6
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-15.0,0.0},  //CNVertexF 2
  /* (Face 6 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-15.0,30.0},  //CNVertexF 6
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-15.0,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-15.0,30.0},  //CNVertexF 5
  /* (Face 7 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-15.0,0.0},  //CNVertexF 2
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,15.0,30.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,15.0,0.0},  //CNVertexF 4
  /* (Face 8 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,15.0,30.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-15.0,0.0},  //CNVertexF 2
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-15.0,30.0},  //CNVertexF 6
  /* (Face 9 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,15.0,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,15.0,30.0},  //CNVertexF 7
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,15.0,0.0},  //CNVertexF 3
  /* (Face 10 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,15.0,30.0},  //CNVertexF 7
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,15.0,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,15.0,30.0},  //CNVertexF 8
  /* (Face 11 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,15.0,0.0},  //CNVertexF 3
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-15.0,30.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-15.0,0.0},  //CNVertexF 1
  /* (Face 12 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-15.0,30.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,15.0,0.0},  //CNVertexF 3
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,15.0,30.0}  //CNVertexF 7
};   /* ret1 3D Model Code End */

/*------------------------------
 ret2 detailed information:
    Number of VertexFs: 8
    Number of Edges: 36
    Number of Faces: 12
------------------------------*/

ScePspFVector3 ret2Pos = {400.0,0.0,40.0};

CNVertexF __attribute__((aligned(16))) ret2[12*3] = {   /* ret2 3D Model Code Start */
  /* (Face 1 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-12.5,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,12.5,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,12.5,0.0},  //CNVertexF 3
  /* (Face 2 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,12.5,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-12.5,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-12.5,0.0},  //CNVertexF 2
  /* (Face 3 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-12.5,25.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,12.5,25.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-12.5,25.0},  //CNVertexF 6
  /* (Face 4 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,12.5,25.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-12.5,25.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,12.5,25.0},  //CNVertexF 7
  /* (Face 5 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-12.5,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-12.5,25.0},  //CNVertexF 6
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-12.5,0.0},  //CNVertexF 2
  /* (Face 6 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-12.5,25.0},  //CNVertexF 6
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-12.5,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-12.5,25.0},  //CNVertexF 5
  /* (Face 7 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-12.5,0.0},  //CNVertexF 2
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,12.5,25.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,12.5,0.0},  //CNVertexF 4
  /* (Face 8 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,12.5,25.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-12.5,0.0},  //CNVertexF 2
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-12.5,25.0},  //CNVertexF 6
  /* (Face 9 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,12.5,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,12.5,25.0},  //CNVertexF 7
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,12.5,0.0},  //CNVertexF 3
  /* (Face 10 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,12.5,25.0},  //CNVertexF 7
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,12.5,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,12.5,25.0},  //CNVertexF 8
  /* (Face 11 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,12.5,0.0},  //CNVertexF 3
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-12.5,25.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-12.5,0.0},  //CNVertexF 1
  /* (Face 12 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-12.5,25.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,12.5,0.0},  //CNVertexF 3
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,12.5,25.0}  //CNVertexF 7
};   /* ret2 3D Model Code End */

/*------------------------------
 ret3 detailed information:
    Number of VertexFs: 8
    Number of Edges: 36
    Number of Faces: 12
------------------------------*/

ScePspFVector3 ret3Pos = {600.0,0.0,35.0};

CNVertexF __attribute__((aligned(16))) ret3[12*3] = {   /* ret3 3D Model Code Start */
  /* (Face 1 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-10.0,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,10.0,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,10.0,0.0},  //CNVertexF 3
  /* (Face 2 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,10.0,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-10.0,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-10.0,0.0},  //CNVertexF 2
  /* (Face 3 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-10.0,20.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,10.0,20.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-10.0,20.0},  //CNVertexF 6
  /* (Face 4 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,10.0,20.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-10.0,20.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,10.0,20.0},  //CNVertexF 7
  /* (Face 5 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-10.0,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-10.0,20.0},  //CNVertexF 6
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-10.0,0.0},  //CNVertexF 2
  /* (Face 6 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-10.0,20.0},  //CNVertexF 6
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-10.0,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-10.0,20.0},  //CNVertexF 5
  /* (Face 7 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-10.0,0.0},  //CNVertexF 2
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,10.0,20.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,10.0,0.0},  //CNVertexF 4
  /* (Face 8 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,10.0,20.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-10.0,0.0},  //CNVertexF 2
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-10.0,20.0},  //CNVertexF 6
  /* (Face 9 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,10.0,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,10.0,20.0},  //CNVertexF 7
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,10.0,0.0},  //CNVertexF 3
  /* (Face 10 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,10.0,20.0},  //CNVertexF 7
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,10.0,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,10.0,20.0},  //CNVertexF 8
  /* (Face 11 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,10.0,0.0},  //CNVertexF 3
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-10.0,20.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-10.0,0.0},  //CNVertexF 1
  /* (Face 12 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-10.0,20.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,10.0,0.0},  //CNVertexF 3
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,10.0,20.0}  //CNVertexF 7
};   /* ret3 3D Model Code End */

/*------------------------------
 ret4 detailed information:
    Number of VertexFs: 8
    Number of Edges: 36
    Number of Faces: 12
------------------------------*/

ScePspFVector3 ret4Pos = {800.0,0.0,30.0};

CNVertexF __attribute__((aligned(16))) ret4[12*3] = {   /* ret4 3D Model Code Start */
  /* (Face 1 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-7.5,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,7.5,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,7.5,0.0},  //CNVertexF 3
  /* (Face 2 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,7.5,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-7.5,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-7.5,0.0},  //CNVertexF 2
  /* (Face 3 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-7.5,15.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,7.5,15.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-7.5,15.0},  //CNVertexF 6
  /* (Face 4 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,7.5,15.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-7.5,15.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,7.5,15.0},  //CNVertexF 7
  /* (Face 5 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-7.5,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-7.5,15.0},  //CNVertexF 6
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-7.5,0.0},  //CNVertexF 2
  /* (Face 6 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-7.5,15.0},  //CNVertexF 6
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-7.5,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-7.5,15.0},  //CNVertexF 5
  /* (Face 7 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-7.5,0.0},  //CNVertexF 2
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,7.5,15.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,7.5,0.0},  //CNVertexF 4
  /* (Face 8 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,7.5,15.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-7.5,0.0},  //CNVertexF 2
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-7.5,15.0},  //CNVertexF 6
  /* (Face 9 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,7.5,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,7.5,15.0},  //CNVertexF 7
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,7.5,0.0},  //CNVertexF 3
  /* (Face 10 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,7.5,15.0},  //CNVertexF 7
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,7.5,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,7.5,15.0},  //CNVertexF 8
  /* (Face 11 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,7.5,0.0},  //CNVertexF 3
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-7.5,15.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-7.5,0.0},  //CNVertexF 1
  /* (Face 12 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-7.5,15.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,7.5,0.0},  //CNVertexF 3
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,7.5,15.0}  //CNVertexF 7
};   /* ret4 3D Model Code End */

/*------------------------------
 ret5 detailed information:
    Number of VertexFs: 8
    Number of Edges: 36
    Number of Faces: 12
------------------------------*/

ScePspFVector3 ret5Pos = {1000.0,0.0,15.0};

CNVertexF __attribute__((aligned(16))) ret5[12*3] = {   /* ret5 3D Model Code Start */
  /* (Face 1 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-5.0,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,5.0,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,5.0,0.0},  //CNVertexF 3
  /* (Face 2 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,5.0,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-5.0,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-5.0,0.0},  //CNVertexF 2
  /* (Face 3 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-5.0,10.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,5.0,10.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-5.0,10.0},  //CNVertexF 6
  /* (Face 4 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,5.0,10.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-5.0,10.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,5.0,10.0},  //CNVertexF 7
  /* (Face 5 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-5.0,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-5.0,10.0},  //CNVertexF 6
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-5.0,0.0},  //CNVertexF 2
  /* (Face 6 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-5.0,10.0},  //CNVertexF 6
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-5.0,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-5.0,10.0},  //CNVertexF 5
  /* (Face 7 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-5.0,0.0},  //CNVertexF 2
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,5.0,10.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,5.0,0.0},  //CNVertexF 4
  /* (Face 8 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,5.0,10.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-5.0,0.0},  //CNVertexF 2
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-5.0,10.0},  //CNVertexF 6
  /* (Face 9 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,5.0,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,5.0,10.0},  //CNVertexF 7
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,5.0,0.0},  //CNVertexF 3
  /* (Face 10 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,5.0,10.0},  //CNVertexF 7
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,5.0,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,5.0,10.0},  //CNVertexF 8
  /* (Face 11 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,5.0,0.0},  //CNVertexF 3
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-5.0,10.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-5.0,0.0},  //CNVertexF 1
  /* (Face 12 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-5.0,10.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,5.0,0.0},  //CNVertexF 3
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,5.0,10.0}  //CNVertexF 7
};   /* ret5 3D Model Code End */

/*------------------------------
 retsmall detailed information:
    Number of VertexFs: 8
    Number of Edges: 36
    Number of Faces: 12
------------------------------*/

ScePspFVector3 retsmall1Pos = {100.0,0.0,47.5};
ScePspFVector3 retsmall2Pos = {300.0,0.0,50.0};
ScePspFVector3 retsmall3Pos = {500.0,0.0,45.0};
ScePspFVector3 retsmall4Pos = {700.0,0.0,37.5};
ScePspFVector3 retsmall5Pos = {900.0,0.0,27.5};
ScePspFVector3 retsmall6Pos = {1100.0,0.0,10.0};

CNVertexF __attribute__((aligned(16))) retsmall[12*3] = {   /* retsmall 3D Model Code Start */
  /* (Face 1 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-2.5,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,2.5,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,2.5,0.0},  //CNVertexF 3
  /* (Face 2 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,2.5,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-2.5,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-2.5,0.0},  //CNVertexF 2
  /* (Face 3 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-2.5,5.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,2.5,5.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-2.5,5.0},  //CNVertexF 6
  /* (Face 4 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,2.5,5.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-2.5,5.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,2.5,5.0},  //CNVertexF 7
  /* (Face 5 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-2.5,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-2.5,5.0},  //CNVertexF 6
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-2.5,0.0},  //CNVertexF 2
  /* (Face 6 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-2.5,5.0},  //CNVertexF 6
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-2.5,0.0},  //CNVertexF 1
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-2.5,5.0},  //CNVertexF 5
  /* (Face 7 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-2.5,0.0},  //CNVertexF 2
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,2.5,5.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,2.5,0.0},  //CNVertexF 4
  /* (Face 8 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,2.5,5.0},  //CNVertexF 8
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-2.5,0.0},  //CNVertexF 2
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,-2.5,5.0},  //CNVertexF 6
  /* (Face 9 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,2.5,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,2.5,5.0},  //CNVertexF 7
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,2.5,0.0},  //CNVertexF 3
  /* (Face 10 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,2.5,5.0},  //CNVertexF 7
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,2.5,0.0},  //CNVertexF 4
  {retcol, 0.0f, 0.0f, 0.0f, 1.25,2.5,5.0},  //CNVertexF 8
  /* (Face 11 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,2.5,0.0},  //CNVertexF 3
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-2.5,5.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-2.5,0.0},  //CNVertexF 1
  /* (Face 12 of 12) */
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,-2.5,5.0},  //CNVertexF 5
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,2.5,0.0},  //CNVertexF 3
  {retcol, 0.0f, 0.0f, 0.0f, -1.25,2.5,5.0}  //CNVertexF 7
};   /* retsmall 3D Model Code End */




#define POLE_HEIGHT (60.0f)
#define POLE_WIDTH (5.0f)
#define poleCol GU_COLOR(0.35f, 0.25f, 0.0f, 1.0f)

ScePspFVector3 polePos = {0.0f, 0.0f, 0.0f};//50.0f};

CNVertexF __attribute__((aligned(16))) pole[10*3] =
{
    //roof
    { poleCol, 0.0f, 0.0f, 1.0f, -POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f, POLE_HEIGHT },
    { poleCol, 0.0f, 0.0f, 1.0f,  POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f, POLE_HEIGHT },
    { poleCol, 0.0f, 0.0f, 1.0f, -POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f, POLE_HEIGHT },
    
    { poleCol, 0.0f, 0.0f, 1.0f, -POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f, POLE_HEIGHT },
    { poleCol, 0.0f, 0.0f, 1.0f,  POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f, POLE_HEIGHT },
    { poleCol, 0.0f, 0.0f, 1.0f,  POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f, POLE_HEIGHT },
    
    //top
    { poleCol, 0.0f, POLE_WIDTH, POLE_HEIGHT/2, -POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f,        0.0f },
    { poleCol, 0.0f, POLE_WIDTH, POLE_HEIGHT/2,  POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f,        0.0f },
    { poleCol, 0.0f, POLE_WIDTH, POLE_HEIGHT/2,  POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f, POLE_HEIGHT },
    
    { poleCol, 0.0f, POLE_WIDTH, POLE_HEIGHT/2, -POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f,        0.0f },
    { poleCol, 0.0f, POLE_WIDTH, POLE_HEIGHT/2,  POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f, POLE_HEIGHT },
    { poleCol, 0.0f, POLE_WIDTH, POLE_HEIGHT/2, -POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f, POLE_HEIGHT },
    
    //bottom
    { poleCol, 0.0f,-POLE_WIDTH, POLE_HEIGHT/2,  POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f,  POLE_HEIGHT },
    { poleCol, 0.0f,-POLE_WIDTH, POLE_HEIGHT/2,  POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f,         0.0f },
    { poleCol, 0.0f,-POLE_WIDTH, POLE_HEIGHT/2, -POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f,         0.0f },
    
    { poleCol, 0.0f,-POLE_WIDTH, POLE_HEIGHT/2, -POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f,  POLE_HEIGHT },
    { poleCol, 0.0f,-POLE_WIDTH, POLE_HEIGHT/2,  POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f,  POLE_HEIGHT },
    { poleCol, 0.0f,-POLE_WIDTH, POLE_HEIGHT/2, -POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f,         0.0f },
    
    //left
    { poleCol,-POLE_WIDTH, 0.0f, POLE_HEIGHT/2, -POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f,        0.0f },
    { poleCol,-POLE_WIDTH, 0.0f, POLE_HEIGHT/2, -POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f, POLE_HEIGHT },
    { poleCol,-POLE_WIDTH, 0.0f, POLE_HEIGHT/2, -POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f, POLE_HEIGHT },
    
    { poleCol,-POLE_WIDTH, 0.0f, POLE_HEIGHT/2, -POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f,        0.0f },
    { poleCol,-POLE_WIDTH, 0.0f, POLE_HEIGHT/2, -POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f,        0.0f },
    { poleCol,-POLE_WIDTH, 0.0f, POLE_HEIGHT/2, -POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f, POLE_HEIGHT },
    
    //right
    { poleCol, POLE_WIDTH, 0.0f, POLE_HEIGHT/2,  POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f, POLE_HEIGHT },
    { poleCol, POLE_WIDTH, 0.0f, POLE_HEIGHT/2,  POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f, POLE_HEIGHT },
    { poleCol, POLE_WIDTH, 0.0f, POLE_HEIGHT/2,  POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f,        0.0f },
    
    { poleCol, POLE_WIDTH, 0.0f, POLE_HEIGHT/2,  POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f, POLE_HEIGHT },
    { poleCol, POLE_WIDTH, 0.0f, POLE_HEIGHT/2,  POLE_WIDTH/2.0f,  POLE_WIDTH/2.0f,        0.0f },
    { poleCol, POLE_WIDTH, 0.0f, POLE_HEIGHT/2,  POLE_WIDTH/2.0f, -POLE_WIDTH/2.0f,        0.0f }
};

#define FLAG_HEIGHT (25.0f)
#define FLAG_LENGTH (25.0f)
#define FLAG_WIDTH (5.0f)
//#define flagCol GU_COLOR(0.4f, 0.27f, 0.0f, 1.0f)

ScePspFVector3 flagPos = {/*0.0f*/ POLE_WIDTH/2, 0.0f, /*50 +*/ POLE_HEIGHT};

NVertexF __attribute__((aligned(16))) flag[12*3] =
{
    //roof
    { /*flagCol,*/ 0.0f, 0.0f, 1.0f,        0.0f,  FLAG_WIDTH/2.0f, 0.0f },
    { /*flagCol,*/ 0.0f, 0.0f, 1.0f, FLAG_LENGTH,  FLAG_WIDTH/2.0f, 0.0f },
    { /*flagCol,*/ 0.0f, 0.0f, 1.0f,        0.0f, -FLAG_WIDTH/2.0f, 0.0f },
    
    { /*flagCol,*/ 0.0f, 0.0f, 1.0f,        0.0f, -FLAG_WIDTH/2.0f, 0.0f },
    { /*flagCol,*/ 0.0f, 0.0f, 1.0f, FLAG_LENGTH,  FLAG_WIDTH/2.0f, 0.0f },
    { /*flagCol,*/ 0.0f, 0.0f, 1.0f, FLAG_LENGTH, -FLAG_WIDTH/2.0f, 0.0f },
    
    //floor
    { /*flagCol,*/ 0.0f, 0.0f,-1.0f,        0.0f, -FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    { /*flagCol,*/ 0.0f, 0.0f,-1.0f, FLAG_LENGTH,  FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    { /*flagCol,*/ 0.0f, 0.0f,-1.0f,        0.0f,  FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    
    { /*flagCol,*/ 0.0f, 0.0f,-1.0f, FLAG_LENGTH, -FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    { /*flagCol,*/ 0.0f, 0.0f,-1.0f, FLAG_LENGTH,  FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    { /*flagCol,*/ 0.0f, 0.0f,-1.0f,        0.0f, -FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    
    //top
    { /*flagCol,*/ 0.0f, FLAG_WIDTH, FLAG_HEIGHT/2,        0.0f,  FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    { /*flagCol,*/ 0.0f, FLAG_WIDTH, FLAG_HEIGHT/2, FLAG_LENGTH,  FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    { /*flagCol,*/ 0.0f, FLAG_WIDTH, FLAG_HEIGHT/2, FLAG_LENGTH,  FLAG_WIDTH/2.0f,         0.0f },
    
    { /*flagCol,*/ 0.0f, FLAG_WIDTH, FLAG_HEIGHT/2,        0.0f,  FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    { /*flagCol,*/ 0.0f, FLAG_WIDTH, FLAG_HEIGHT/2, FLAG_LENGTH,  FLAG_WIDTH/2.0f,         0.0f },
    { /*flagCol,*/ 0.0f, FLAG_WIDTH, FLAG_HEIGHT/2,        0.0f,  FLAG_WIDTH/2.0f,         0.0f },
    
    //bottom
    { /*flagCol,*/ 0.0f,-FLAG_WIDTH, FLAG_HEIGHT/2, FLAG_LENGTH, -FLAG_WIDTH/2.0f,         0.0f },
    { /*flagCol,*/ 0.0f,-FLAG_WIDTH, FLAG_HEIGHT/2, FLAG_LENGTH, -FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    { /*flagCol,*/ 0.0f,-FLAG_WIDTH, FLAG_HEIGHT/2,        0.0f, -FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    
    { /*flagCol,*/ 0.0f,-FLAG_WIDTH, FLAG_HEIGHT/2,        0.0f, -FLAG_WIDTH/2.0f,         0.0f },
    { /*flagCol,*/ 0.0f,-FLAG_WIDTH, FLAG_HEIGHT/2, FLAG_LENGTH, -FLAG_WIDTH/2.0f,         0.0f },
    { /*flagCol,*/ 0.0f,-FLAG_WIDTH, FLAG_HEIGHT/2,        0.0f, -FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    
    //left
    { /*flagCol,*/-FLAG_WIDTH, 0.0f, FLAG_HEIGHT/2, 0.0f,  FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    { /*flagCol,*/-FLAG_WIDTH, 0.0f, FLAG_HEIGHT/2, 0.0f,  FLAG_WIDTH/2.0f,         0.0f },
    { /*flagCol,*/-FLAG_WIDTH, 0.0f, FLAG_HEIGHT/2, 0.0f, -FLAG_WIDTH/2.0f,         0.0f },
    
    { /*flagCol,*/-FLAG_WIDTH, 0.0f, FLAG_HEIGHT/2, 0.0f, -FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    { /*flagCol,*/-FLAG_WIDTH, 0.0f, FLAG_HEIGHT/2, 0.0f,  FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    { /*flagCol,*/-FLAG_WIDTH, 0.0f, FLAG_HEIGHT/2, 0.0f, -FLAG_WIDTH/2.0f,         0.0f },
    
    //right
    { /*flagCol,*/ FLAG_WIDTH, 0.0f, FLAG_HEIGHT/2, FLAG_LENGTH, -FLAG_WIDTH/2.0f,         0.0f },
    { /*flagCol,*/ FLAG_WIDTH, 0.0f, FLAG_HEIGHT/2, FLAG_LENGTH,  FLAG_WIDTH/2.0f,         0.0f },
    { /*flagCol,*/ FLAG_WIDTH, 0.0f, FLAG_HEIGHT/2, FLAG_LENGTH,  FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    
    { /*flagCol,*/ FLAG_WIDTH, 0.0f, FLAG_HEIGHT/2, FLAG_LENGTH, -FLAG_WIDTH/2.0f,         0.0f },
    { /*flagCol,*/ FLAG_WIDTH, 0.0f, FLAG_HEIGHT/2, FLAG_LENGTH,  FLAG_WIDTH/2.0f, -FLAG_HEIGHT },
    { /*flagCol,*/ FLAG_WIDTH, 0.0f, FLAG_HEIGHT/2, FLAG_LENGTH, -FLAG_WIDTH/2.0f, -FLAG_HEIGHT }
};

#endif
