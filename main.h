/**
 * This file belongs to the 'Battlegrounds 2' game project.
 * Copyright 2009 xfacter
 * Copyright 2016 wickles
 * This work is licensed under the GPLv3
 * subject to all terms as reproduced in the included LICENSE file.
 */

#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <pspgu.h>
#include <pspgum.h>
#include <pspdisplay.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <psppower.h>
#include <pspctrl.h>

#include "models.h"
#include "wave.h"
#include "xastar.h"
#include "xconsole.h"
#include "xdraw.h"
#include "xgraphics.h"
#include "xlib.h"
#include "xmath.h"
#include "xparticle.h"
#include "xtext.h"
#include "xtexture.h"
#include "xvertex.h"

#define ANALOG_THRESHOLD (30)

#define GROUND_LENGTH (map.Length()*CELL_LENGTH)
#define GROUND_HEIGHT (map.Height()*CELL_LENGTH)
#define PERSPECT_NEAR (100.0f)
#define PERSPECT_FAR  (1000000.0f)

#define TANK_RADIUS (42.5f)
//REAL: 42.2336 ~ 43.2496
#define TANK_DOME_RADIUS (30.0f)
//REAL: 22.15015
#define TANK_DOME_CENTER_HEIGHT (45.0f)
//REAL: 41.138

#define TANK_HIGH            (63.2882f)
#define TANK_LOW             (17.3318f)
#define TANK_LOW_SECT_HEIGHT (22.7446f)
#define TANK_HEIGHT          (TANK_HIGH - TANK_LOW)

#define ENEMY_HOOK (1400.0f)
#define ENEMY_RELEASE (1600.0f)
//enemy's sweet spot is 1200 from player
#define ENEMY_FLAG_RADIUS (1000.0f)
#define PLAYER_LOCK_ANGLE (PI/5.0f)

#define SKYBOX_OFFSET (25000.0f)
#define SKYBOX_LENGTH (x_maxf(GROUND_LENGTH, GROUND_HEIGHT) + 2*SKYBOX_OFFSET)
#define SKYBOX_HEIGHT (25000.0f)
#define SKYBOX_SUBDIV (10)

#define EXPLOSION_RADIUS (200.0f)
#define MINE_EXPL_RADIUS (400.0f)
#define MINE_DET_RADIUS (50.0f)

#define MAX_TEAMS (4)
#define MAX_ENEMIES (8)

#define NUM_FLAGS (4)

#define PLAYER_TEAM (0)
#define PLAYER_MEMBER (-1)
#define LASER_CACHE (20)
#define CANNON_CACHE (5)
#define MINE_CACHE (5)
#define EXPLOSION_CACHE (15)
#define GLOW_CACHE (100)

#define START_MINES (3)

#define CANNON_DMG (75.0f)
#define LASER_DMG (20.0f)
#define MINE_DMG (150.0f)
#define FF_DMG_PERCENT (0.20f)

#define L_TEAM (Enemy[t][i].LockedOnTeam)
#define L_MEMBER (Enemy[t][i].LockedOnMember)

#define CANNON_AGGRO_MIN (20)
#define CANNON_AGGRO_MAX (30)
#define LASER_BIAS_MIN (50)
#define LASER_BIAS_MAX (200)
#define SPEED_BIAS_MIN (100)
#define SPEED_BIAS_MAX (225)
#define RADIUS_BIAS_MIN (1000)
#define RADIUS_BIAS_MAX (1200)

#define ZOOM_MIN (750.0f)
#define ZOOM_MAX (1900.0f)

#define ZOOM_THIRD_MIN (550.0f)
#define ZOOM_THIRD_MAX (1250.0f)

#define CAM_X_MIN (PI/6)
#define CAM_X_MAX (PI/3)

#define FREE_CAM_SPEED_MIN (100.0f)
#define FREE_CAM_SPEED_MAX (5000.0f)
#define FREE_CAM_ACCEL (1500.0f)

#define CANNON_GRAVITY (15.0f)

#define SOUND_MULTIPLE (30.0f)
#define SOUND_THRESHOLD (128.0f*SOUND_MULTIPLE)

#define BALL_SPEED (1.8f)
#define LASER_SPEED (2.25f)

#define BLOCK_X_LEFT (x)
#define BLOCK_X_RIGHT (x + 1)
#define BLOCK_Y_BOTTOM (y)
#define BLOCK_Y_TOP (y + 1)
#define BLOCK_X_CENTER (x + 0.5f)
#define BLOCK_Y_CENTER (y + 0.5f)

#define BLOCK_SMALL_PROPORTION (0.5f)
#define BLOCK_SMALL_X_LEFT (x + (0.5f - BLOCK_SMALL_PROPORTION/2))
#define BLOCK_SMALL_X_RIGHT (x + (0.5f + BLOCK_SMALL_PROPORTION/2))
#define BLOCK_SMALL_Y_BOTTOM (y + (0.5f - BLOCK_SMALL_PROPORTION/2))
#define BLOCK_SMALL_Y_TOP (y + (0.5f + BLOCK_SMALL_PROPORTION/2))

#define ROUND_BLOCK_RADIUS (CELL_LENGTH/2)
#define ROUND_BLOCK_SMALL_RADIUS (BLOCK_SMALL_PROPORTION*(CELL_LENGTH/2))

#define PATH_SIZE_PROPORTION (0.7f)
#define PATH_X_LEFT (xPath[ID] + (0.5f - PATH_SIZE_PROPORTION/2))
#define PATH_X_RIGHT (xPath[ID] + (0.5f + PATH_SIZE_PROPORTION/2))
#define PATH_Y_BOTTOM (yPath[ID] + (0.5f - PATH_SIZE_PROPORTION/2))
#define PATH_Y_TOP (yPath[ID] + (0.5f + PATH_SIZE_PROPORTION/2))
#define PATH_X_CENTER (xPath[ID] + 0.5f)
#define PATH_Y_CENTER (yPath[ID] + 0.5f)
#define PATH_RADIUS (PATH_SIZE_PROPORTION*(CELL_LENGTH/2))

#define SETTINGS_BOX_LENGTH (100)
#define SETTINGS_BOX_HEIGHT (10)
#define SETTINGS_POS_LENGTH (10)

void PauseEditor();
void MapEditor();
void DrawEditor();
void PauseGame();
void Game();
void DrawGame();
void DrawHUD();

float SpawnTimer = 0.0f;

float rotPlayer  = PI_2;
float rotCurrent = 0.0f;

float posPlayerX = 0.0f;
float posPlayerY = 0.0f;
float PlayerHeight = 0.0f;

float posPlayerLastX = 0.0f;
float posPlayerLastY = 0.0f;

float Timer = 0.0f;

float camOffsetX = 0.0f;
float camOffsetY = 0.0f;

float zoom[2] = {1000, 750};
float rotCamX = PI/4;
float rotCamZ = 0.0f;

float posBallX[CANNON_CACHE];
float posBallY[CANNON_CACHE];
float posBallZ[CANNON_CACHE];
float posBallLastX[CANNON_CACHE];
float posBallLastY[CANNON_CACHE];
float posBallLastZ[CANNON_CACHE];
float BallHeading[CANNON_CACHE];
float BallCos[CANNON_CACHE];
float BallSin[CANNON_CACHE];
float BallFallSpeed[CANNON_CACHE];
bool ShootingCannon[CANNON_CACHE];
bool CountAllowCannon = 0;
float CannonAllowTimer = 0.0f;

float posLaserX[LASER_CACHE];
float posLaserY[LASER_CACHE];
float posLaserZ[LASER_CACHE];
float posLaserLastX[LASER_CACHE];
float posLaserLastY[LASER_CACHE];
float posLaserLastZ[LASER_CACHE];
float LaserHeading[LASER_CACHE];
float LaserCos[LASER_CACHE];
float LaserSin[LASER_CACHE];
float LaserMoveTimer[LASER_CACHE];
float LaserAllowTimer = 0;
bool ShootingLaser[LASER_CACHE];
bool CountAllowLaser = 0;


float posMineX[MINE_CACHE];
float posMineY[MINE_CACHE];
bool MinePrimed[MINE_CACHE];
bool MineLinked[MINE_CACHE];
int NumMines = START_MINES;

bool PlayerAlive = 1;
float PlayerHealth = 100;
float Boost = 100;
float Heat = 0;

int Score = 0;
int Deaths = 0;
int Caps = 0;
int Returns = 0;
char buffer[256];
char buffer2[256];

bool AllowShoot = 1;
bool AllowBoost = 1;

bool TeamInPlay[MAX_TEAMS];
float posFlagX[MAX_TEAMS];
float posFlagY[MAX_TEAMS];
float posFlagZ[MAX_TEAMS];
float rotFlag[MAX_TEAMS];
float FlagSpawnX[MAX_TEAMS];
float FlagSpawnY[MAX_TEAMS];
int FlagHeldTeam[MAX_TEAMS];
int FlagHeldMember[MAX_TEAMS];

int Camera = 0;
float posFreeCamX = 0;
float posFreeCamY = 0;
float posFreeCamZ = 1000;
float rotFreeCamX = 0;
float rotFreeCamZ = 0;
float FreeCamSpeed = 1000;

int Player_Lock_Team = -1;
int Player_Lock_Member = -1;

float posReticleX = 0;
float posReticleY = 0;
float rotReticle = 0.0f;

ScePspFVector3 cam = {0,0,0};

bool cfg_show_health = 0;
bool cfg_show_fps = 0;
bool cfg_target_lock = 0;
u8 cfg_analog_deadzone = 30;
float cfg_sfx_volume = 1.0f;
float cfg_bg_volume = 1.0f;

enum game_difficulties
{
    easy    = 0,
    medium  = 1,
    hard    = 2,
};

const float SQUARE_RADIUS = sqrtf( 2 * SQR(CELL_LENGTH*0.5f) );
const float SQUARE_SMALL_RADIUS = sqrtf( 2 * SQR(BLOCK_SMALL_PROPORTION*(CELL_LENGTH*0.5f)) );

float AITimer = 0;

float dt;

bool in_game = 0;

int NUM_ENEMIES;

class AI
{
public:
    bool Alive;
    float SpawnTimer;
    int LockedOnTeam;
    int LockedOnMember;
    float Health;
    float posTankX;
    float posTankY;
    float Height;
    float HoverOffset;
    float posTankLastX;
    float posTankLastY;
    float rotTank;
    bool StrafeDir;
    float posBallX[CANNON_CACHE];
    float posBallY[CANNON_CACHE];
    float posBallZ[CANNON_CACHE];
    float posBallLastX[CANNON_CACHE];
    float posBallLastY[CANNON_CACHE];
    float posBallLastZ[CANNON_CACHE];
    float BallHeading[CANNON_CACHE];
    float BallCos[CANNON_CACHE];
    float BallSin[CANNON_CACHE];
    float BallFallSpeed[CANNON_CACHE];
    float CannonAllowTimer;
    bool CannonAllowShoot;
    bool ShootingCannon[CANNON_CACHE];
    float posLaserX[LASER_CACHE];
    float posLaserY[LASER_CACHE];
    float posLaserZ[LASER_CACHE];
    float posLaserLastX[LASER_CACHE];
    float posLaserLastY[LASER_CACHE];
    float posLaserLastZ[LASER_CACHE];
    float LaserHeading[LASER_CACHE];
    float LaserCos[LASER_CACHE];
    float LaserSin[LASER_CACHE];
    float LaserMoveTimer[LASER_CACHE];
    bool ShootingLaser[LASER_CACHE];
    float posExplosionX[EXPLOSION_CACHE];
    float posExplosionY[EXPLOSION_CACHE];
    float posExplosionZ[EXPLOSION_CACHE];
    bool Explosion[EXPLOSION_CACHE];
    float ExplosionTimer[EXPLOSION_CACHE];

    int Score;
    int Deaths;
    int Caps;
    int Returns;
    float NextX;
    float NextY;

    int CannonAggro;
    int LaserBias;
    int SpeedBias;
    int RadiusBias;
    int OffenseBias;

    AI();
    void Spawn();
    void Create();
};

AI::AI()
{
    Score = 0;
    Deaths = 0;
    Caps = 0;
    Returns = 0;
}

void AI::Create()
{
    CannonAggro = x_randi(CANNON_AGGRO_MIN, CANNON_AGGRO_MAX);
    LaserBias = x_randi(LASER_BIAS_MIN, LASER_BIAS_MAX);
    SpeedBias = x_randi(SPEED_BIAS_MIN, SPEED_BIAS_MAX);
    RadiusBias = x_randi(RADIUS_BIAS_MIN, RADIUS_BIAS_MAX);
    //Enemy[t][i].OffenseBias = x_randi(0, 10);

    Score = 0;
    Deaths = 0;
    Caps = 0;
    Returns = 0;
}

AI Enemy[MAX_TEAMS][MAX_ENEMIES];

void SpawnFlag(int flag)
{
    if (flag < 0 || flag >= MAX_TEAMS) return;
    posFlagX[flag] = FlagSpawnX[flag];
    posFlagY[flag] = FlagSpawnY[flag];
    posFlagZ[flag] = 0;
    rotFlag[flag] = 0;
    FlagHeldTeam[flag] = -1;
}

bool FlagHeld(int flag)
{
    if (flag < 0 || flag >= MAX_TEAMS) return 1;
    if (FlagHeldTeam[flag] < 0) return 0;
    return 1;
}

bool FlagHome(int flag)
{
    if (flag < 0 || flag >= MAX_TEAMS || FlagHeld(flag)) return 0;
    if (posFlagX[flag] == FlagSpawnX[flag] && posFlagY[flag] == FlagSpawnY[flag]) return 1;
    return 0;
}

int HoldingFlag(int team, int member)
{
    if (team < 0) return -1;
    for (int i = 0; i < MAX_TEAMS; i++)
    {
        if (FlagHeldTeam[i] == team && FlagHeldMember[i] == member) return i;
    }
    return -1;
}

void GiveFlag(int flag, int team, int member)
{
    if (flag < 0 || flag >= MAX_TEAMS) return;
    FlagHeldTeam[flag] = team;
    FlagHeldMember[flag] = member;
}

void DropFlag(int flag)
{
    if (flag < 0 || flag >= MAX_TEAMS) return;
    posFlagZ[flag] = 0;
    FlagHeldTeam[flag] = -1;
}

void UpdateFlags()
{
    for (int i = 0; i < MAX_TEAMS; i++)
    {
        int team = FlagHeldTeam[i];
        int member = FlagHeldMember[i];
        if (team >= 0)
        {
            if (member < 0)
            {
                posFlagX[i] = posPlayerX;
                posFlagY[i] = posPlayerY;
                posFlagZ[i] = 50 + 10.0f + PlayerHeight;
                rotFlag[i] = rotPlayer - PI_2;
            }
            else
            {
                posFlagX[i] = Enemy[team][member].posTankX;
                posFlagY[i] = Enemy[team][member].posTankY;
                posFlagZ[i] = 50.0f + Enemy[team][member].Height;
                rotFlag[i] = Enemy[team][member].rotTank - PI_2;
            }
        }
    }
}

void SpawnPlayer();

void ResetGame()
{
    SpawnTimer = 0.0f;
    rotPlayer  = PI_2;
    rotCurrent = 0.0f;
    posPlayerX = 0.0f;
    posPlayerY = 0.0f;
    PlayerHeight = 0.0f;
    posPlayerLastX = 0.0f;
    posPlayerLastY = 0.0f;
    camOffsetX = 0.0f;
    camOffsetY = 0.0f;
    zoom[0] = ZOOM_MAX;
    zoom[1] = 750;
    rotCamX = PI/4;
    rotCamZ = 0.0f;
    Player_Lock_Team = -1;
    Player_Lock_Member = -1;
    posReticleX = 0;
    posReticleY = 0;
    rotReticle = 0.0f;
    Camera = 0;
    posFreeCamX = 0;
    posFreeCamY = 0;
    posFreeCamZ = 1000;
    rotFreeCamX = 0;
    rotFreeCamZ = 0;
    FreeCamSpeed = 1000;
    AITimer = 0;
    SpawnPlayer();
    Score = 0;
    Deaths = 0;
    Caps = 0;
    Returns = 0;
    for (int t = 0; t < MAX_TEAMS; t++)
    {
        if (TeamInPlay[t])
        {
            SpawnFlag(t);
            for (int i = 0; i < NUM_ENEMIES - (t == PLAYER_TEAM ? 1 : 0); i++)
            {
                Enemy[t][i].Create();
            }
        }
    }
    UpdateFlags();
    in_game = 1;
}

class BG3DMap
{
private:
    u32 map_length;
    u32 map_height;
    char* map;
public:
    BG3DMap();
    ~BG3DMap();
    bool LoadMap(char* filename);
    bool SaveMap(char* filename);
    void Free();
    int Length() { return (int)map_length; }
    int Height() { return (int)map_height; }
    char Feature(int x, int y);
    void SetFeature(int x, int y, char new_feature);
    bool Create(u32 length, u32 height);
    bool Valid();
};

BG3DMap::BG3DMap()
{
    //Reserved
    map_length = 0;
    map_height = 0;
    map = 0;
}

BG3DMap::~BG3DMap()
{
    Free();
}

bool BG3DMap::LoadMap(char* filename)
{
    FILE *file;

    file = fopen(filename, "rb");
    if (!file) return false;

    u8 header[10];

    fread(header, 1, 10, file);

    u32 length = header[2] << 0 | header[3] << 8 | header[4] << 16 | header[5] << 24;
    u32 height = header[6] << 0 | header[7] << 8 | header[8] << 16 | header[9] << 24;

    if (header[0] != 'B' || header[1] != 'G' || !Create(length, height))
    {
        fclose(file);
        return false;
    }

    for (int y = 0; y < Height(); y++)
    {
        for (int x = 0; x < Length(); x++)
        {
            SetFeature(x, y, (char)fgetc(file));
        }
    }

    fclose(file);

    if (!Valid())
    {
        Free();
        return false;
    }

    return true;
}

void BG3DMap::Free()
{
    free(map);
    map_length = 0;
    map_height = 0;
}

bool BG3DMap::Create(u32 length, u32 height)
{
    if (length <= 0 || height <= 0 || length*height > 64*64) return false;

    map_length = length;
    map_height = height;

    map = (char*)malloc(Length()*Height()*sizeof(char));

    for (int x = 0; x < Length(); x++)
    {
        for (int y = 0; y < Height(); y++)
        {
            SetFeature(x, y, '0');
        }
    }

    for (int i = 0; i < MAX_TEAMS; i++) TeamInPlay[i] = 0;
    return true;
}

bool BG3DMap::Valid()
{
    if (!TeamInPlay[PLAYER_TEAM]) return false;
    int teams = 0;
    for (int i = 0; i < MAX_TEAMS; i++)
    {
        if (TeamInPlay[i]) teams += 1;
    }
    if (teams < 2) return false;
    return true;
}

bool BG3DMap::SaveMap(char* filename)
{
    if (!Valid()) return false;

    FILE* file = fopen(filename, "wb");
    if (file == 0) return false;

    fputc('B', file);
    fputc('G', file);

    fputc(Length() >>  0 & 0xff, file);
    fputc(Length() >>  8 & 0xff, file);
    fputc(Length() >> 16 & 0xff, file);
    fputc(Length() >> 24 & 0xff, file);

    fputc(Height() >>  0 & 0xff, file);
    fputc(Height() >>  8 & 0xff, file);
    fputc(Height() >> 16 & 0xff, file);
    fputc(Height() >> 24 & 0xff, file);

    for (int y = 0; y < Height(); y++)
    {
        for (int x = 0; x < Length(); x++)
        {
            fputc((int)Feature(x, y), file);
        }
    }

    fclose(file);

    return true;
}

char BG3DMap::Feature(int x, int y)
{
    if (x < 0 || y < 0 || x >= Length() || y >= Height()) return '0';
    return map[y*Length() + x];
}

void BG3DMap::SetFeature(int x, int y, char new_feature)
{
    if (x < 0 || y < 0 || x >= Length() || y >= Height()) return;
    if (Feature(x,y) >= 'a' && Feature(x,y) <= 'd') TeamInPlay[Feature(x,y) - 'a'] = 0;
    if (new_feature >= 'a' && new_feature <= 'd')
    {
        int flag = new_feature - 'a';
        TeamInPlay[flag] = 1;
        FlagSpawnX[flag] = (x+0.5f)*CELL_LENGTH;
        FlagSpawnY[flag] = (y+0.5f)*CELL_LENGTH;
    }
    map[y*Length() + x] = new_feature;
}

BG3DMap map;

bool SetupAstar()
{
    if (!InitAstar(map.Length(), map.Height(), MAX_TEAMS*NUM_ENEMIES)) return false;
    int open = 0;
    for (int x = 0; x < map.Length(); x++)
    {
        for (int y = 0; y < map.Height(); y++)
        {
            if (map.Feature(x, y) == '1' || map.Feature(x, y) == '5') walkable[x][y] = 0;
            else
            {
                walkable[x][y] = 1;
                open += 1;
            }
        }
    }
    if (open <= 0)
    {
        EndAstar();
        return false;
    }
    return true;
}

bool MapCollision(float test_x, float test_y, float test_radius)
{
    int ax = (int)(test_x/CELL_LENGTH) - 1;
    int ay = (int)(test_y/CELL_LENGTH) - 1;

    for (int x = ax - 1; x <= ax + 1; x++)
    {
        for (int y = ay - 1; y <= ay + 1; y++)
        {
            if (map.Feature(x, y) == '1')
            {
                if (test_x + test_radius > BLOCK_X_LEFT*CELL_LENGTH && test_x - test_radius < BLOCK_X_RIGHT*CELL_LENGTH &&
                    test_y + test_radius > BLOCK_Y_BOTTOM*CELL_LENGTH && test_y - test_radius < BLOCK_Y_TOP*CELL_LENGTH)
                {
                    return true;
                }
            }
            else if (map.Feature(x, y) == '2')
            {
                if (test_x + test_radius > BLOCK_SMALL_X_LEFT*CELL_LENGTH && test_x - test_radius < BLOCK_SMALL_X_RIGHT*CELL_LENGTH &&
                    test_y + test_radius > BLOCK_SMALL_Y_BOTTOM*CELL_LENGTH && test_y - test_radius < BLOCK_SMALL_Y_TOP*CELL_LENGTH)
                {
                    return true;
                }
            }
            else if (map.Feature(x, y) == '5')
            {
                if (test_x + test_radius > BLOCK_X_LEFT*CELL_LENGTH && test_x - test_radius < BLOCK_X_RIGHT*CELL_LENGTH &&
                    test_y + test_radius > BLOCK_Y_BOTTOM*CELL_LENGTH && test_y - test_radius < BLOCK_Y_TOP*CELL_LENGTH)
                {
                    float distance = x_sqrtf( SQR( test_x - BLOCK_X_CENTER*CELL_LENGTH ) + SQR( test_y - BLOCK_Y_CENTER*CELL_LENGTH ) );
                    if (distance < ROUND_BLOCK_RADIUS + test_radius)
                    {
                        return true;
                    }
                }
            }
            else if (map.Feature(x, y) == '6')
            {
                if (test_x + test_radius > BLOCK_SMALL_X_LEFT*CELL_LENGTH && test_x - test_radius < BLOCK_SMALL_X_RIGHT*CELL_LENGTH &&
                    test_y + test_radius > BLOCK_SMALL_Y_BOTTOM*CELL_LENGTH && test_y - test_radius < BLOCK_SMALL_Y_TOP*CELL_LENGTH)
                {
                    float distance = x_sqrtf( SQR( test_x - BLOCK_X_CENTER*CELL_LENGTH ) + SQR( test_y - BLOCK_Y_CENTER*CELL_LENGTH ) );
                    if (distance < ROUND_BLOCK_SMALL_RADIUS + test_radius)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool ObjectVisible(float eye_x, float eye_y, float obj_x, float obj_y, float interval)
{
    if (interval <= 0) return false;
    float x = obj_x - eye_x;
    float y = obj_y - eye_y;
    float dist = x_sqrtf(SQR(x) + SQR(y));
    if (dist == 0) return true;
    x = interval*(x/dist);
    y = interval*(y/dist);

    if (MapCollision(obj_x, obj_y, 0)) return false;

    for (float i = 0; i < dist + interval; i += interval)
    {
        if (MapCollision(eye_x, eye_y, 0)) return false;
        eye_x += x;
        eye_y += y;
    }
    return true;
}

float CircleCollision(float x1, float y1, float radius1, float x2, float y2, float radius2)
{
    if (x1 + radius1 > x2 - radius2 && x1 - radius1 < x2 + radius2 && y1 + radius1 > y2 - radius2 && y1 - radius1 < y2 + radius2)
    {
        float distance = x_sqrtf(SQR(x2 - x1) + SQR(y2 - y1));
        if (distance < radius1 + radius2) return distance;
    }
    return -1;
}

bool TankCollision(int team, int member, float x, float y, float z)
{
    if (team < 0 || member < 0)
    {
        if (PlayerAlive)
        {
            if (x > posPlayerX - TANK_RADIUS && x < posPlayerX + TANK_RADIUS &&
                y > posPlayerY - TANK_RADIUS && y < posPlayerY + TANK_RADIUS &&
                z > TANK_LOW + PlayerHeight && z < TANK_HIGH + PlayerHeight)
            {
                //collision with base of tank
                if (z < TANK_LOW + TANK_LOW_SECT_HEIGHT + PlayerHeight)
                {
                    return true;
                }
                //collision with dome of tank
                else
                {
                    float distance = x_sqrtf(SQR(posPlayerX - x) +
                                           SQR(posPlayerY - y) +
                                           SQR(TANK_DOME_CENTER_HEIGHT + PlayerHeight - z));
                    if (distance < TANK_DOME_RADIUS)
                    {
                        return true;
                    }
                }
            }
        }
    }
    else
    {
        if (Enemy[team][member].Alive)
        {
            if (x > Enemy[team][member].posTankX - TANK_RADIUS && x < Enemy[team][member].posTankX + TANK_RADIUS &&
                y > Enemy[team][member].posTankY - TANK_RADIUS && y < Enemy[team][member].posTankY + TANK_RADIUS &&
                z > TANK_LOW + Enemy[team][member].Height && z < TANK_HIGH + Enemy[team][member].Height)
            {
                //collision with base of tank
                if (z < TANK_LOW + TANK_LOW_SECT_HEIGHT + Enemy[team][member].Height)
                {
                    return true;
                }
                //collision with dome of tank
                else
                {
                    float distance = x_sqrtf(SQR(Enemy[team][member].posTankX - x) +
                                           SQR(Enemy[team][member].posTankY - y) +
                                           SQR(TANK_DOME_CENTER_HEIGHT + Enemy[team][member].Height - z));
                    if (distance < TANK_DOME_RADIUS)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool InterpolatedTankCollision(int team, int member, float eye_x, float eye_y, float eye_z, float obj_x, float obj_y, float obj_z, float interval)
{
    if (interval <= 0) return false;
    float x = obj_x - eye_x;
    float y = obj_y - eye_y;
    float z = obj_z - eye_z;
    float dist = x_sqrtf(SQR(x) + SQR(y) + SQR(z));
    if (dist == 0) return false;
    x = interval*(x/dist);
    y = interval*(y/dist);
    z = interval*(z/dist);

    if (TankCollision(team, member, obj_x, obj_y, obj_z)) return true;

    for (float i = 0; i < dist + interval; i += interval)
    {
        if (TankCollision(team, member, eye_x, eye_y, eye_z)) return true;
        eye_x += x;
        eye_y += y;
        eye_z += z;
    }
    return false;
}

void Sound_3D(wavout_wavinfo_t* sound, float x, float y)
{
    float distance = 0;
    if (Camera == 0 || Camera == 1) distance = x_sqrtf( SQR(posPlayerX - x) + SQR(posPlayerY - y) );
    else if (Camera == 2) distance = x_sqrtf( SQR(posFreeCamX - x) + SQR(posFreeCamY - y) + SQR(posFreeCamZ) );
    if (distance <= SOUND_THRESHOLD)
    {
        float pan = 0, volume = 0;
        if (Camera == 0)
        {
            float xdist = x - posPlayerX;
            pan = xdist/SOUND_THRESHOLD + 0.5f;
            //WAV_SetPan(sound, (int)((xdist/SOUND_MULTIPLE) + 128) );
        }
        else if (Camera == 1)
        {
            float angletotarget = x_atan2f(y - posPlayerY, x - posPlayerX);
            float relcamxdist = x_cosf(angletotarget - rotCamZ) * distance;
            pan = relcamxdist/SOUND_THRESHOLD + 0.5f;
            //WAV_SetPan(sound, (int)((relcamxdist/SOUND_MULTIPLE) + 128) );
        }
        else if (Camera == 2)
        {
            float angletotarget = x_atan2f(y - posFreeCamY, x - posFreeCamX);
            float relcamxdist = x_cosf(angletotarget - rotFreeCamZ) * distance;
            pan = relcamxdist/SOUND_THRESHOLD + 0.5f;
            //WAV_SetPan(sound, (int)((relcamxdist/SOUND_MULTIPLE) + 128) );
        }
        //WAV_SetVolume(sound, (int)(255 - (2 * (distance/SOUND_MULTIPLE))) );
        //WAV_Play(sound);
        volume = 1.0f - distance/SOUND_THRESHOLD;
        wavPlay_VolPanPitch(sound, cfg_sfx_volume*volume, pan, 1.0f);
    }
}

int AIPathID(int team, int member)
{
    return (NUM_ENEMIES*team) + member + 1;
}

void AI::Spawn()
{
    Alive = 1;
    SpawnTimer = 0;
    LockedOnTeam = -1;
    Health = 100.0f;

    do
    {
        posTankX = x_randf(2*TANK_RADIUS, GROUND_LENGTH - 2*TANK_RADIUS);
        posTankY = x_randf(2*TANK_RADIUS, GROUND_HEIGHT - 2*TANK_RADIUS);
    } while (MapCollision(posTankX, posTankY, TANK_RADIUS));

    Height = 0;
    HoverOffset = x_randi(0, 1000);
    posTankLastX = posTankX;
    posTankLastY = posTankY;
    rotTank = x_randf(0, 2*PI);
    CannonAllowShoot = 1;

    NextX = 0;
    NextY = 0;

    CannonAggro = x_randi(CANNON_AGGRO_MIN, CANNON_AGGRO_MAX);
    LaserBias = x_randi(LASER_BIAS_MIN, LASER_BIAS_MAX);
    SpeedBias = x_randi(SPEED_BIAS_MIN, SPEED_BIAS_MAX);
    RadiusBias = x_randi(RADIUS_BIAS_MIN, RADIUS_BIAS_MAX);
    OffenseBias = x_randi(0, 10);
}

void SpawnPlayer()
{
    PlayerAlive = 1;
    SpawnTimer = 0;
    PlayerHealth = 100;
    Boost = 100;
    Heat = 0;
    AllowShoot = 1;
    AllowBoost = 1;
    rotPlayer = PI_2;
    rotCurrent = PI_2;

    do
    {
        posPlayerX = x_randf(2*TANK_RADIUS, GROUND_LENGTH - 2*TANK_RADIUS);
        posPlayerY = x_randf(2*TANK_RADIUS, GROUND_HEIGHT - 2*TANK_RADIUS);
    } while (MapCollision(posPlayerX, posPlayerY, TANK_RADIUS));

    PlayerHeight = 0;
    posPlayerLastX = posPlayerX;
    posPlayerLastY = posPlayerY;
    camOffsetX = 0;
    camOffsetY = 0;
    rotCamZ = 0;
    rotReticle = 0;

    CountAllowCannon = 0;
    CountAllowLaser = 0;
    NumMines = START_MINES;
}

#endif
