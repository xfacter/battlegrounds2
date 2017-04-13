/**
 * This file belongs to the 'Battlegrounds 2' game project.
 * Copyright 2009 xfacter
 * Copyright 2016 wickles
 * This work is licensed under the GPLv3
 * subject to all terms as reproduced in the included LICENSE file.
 */

#include "main.h"

#define LINE_HEIGHT (12)

PSP_MODULE_INFO("Battlegrounds2", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER|THREAD_ATTR_VFPU);

char title_text[] = "Battlegrounds2";

u8 __attribute__((aligned(16))) tankList[128];
u8 __attribute__((aligned(16))) mineList[32];
u8 __attribute__((aligned(16))) flagList[64];
u8 __attribute__((aligned(16))) groundList[32];
u8 __attribute__((aligned(16))) cellList[32];
u8 __attribute__((aligned(16))) roundcellList[32];
u8 __attribute__((aligned(16))) reticleList[128];
u8 __attribute__((aligned(16))) spatialretList[256];

xTexture ground_tex0;
xTexture ground_tex1;
xTexture ground_tex2;

xTexture tech_tex0;
xTexture tech_tex1;
xTexture tech_tex2;

xTexture part_tex;
xTexture smoke_tex;

//xTexture sky_tex_top;
xTexture sky_tex_bottom;
xTexture sky_tex_front;
xTexture sky_tex_back;
xTexture sky_tex_left;
xTexture sky_tex_right;

xTexture font;

xExplosion* flag_smoke[MAX_TEAMS];

xExplosion* explosion1;
xExplosion* explosion2;
xExplosion* explosion_smoke;

xExplosion* boost_glow;
xExplosion* laser_part;
xExplosion* cannon_trail;

xExplosion* tank_glow;

xConsole bg3dConsole(16, 256, 2.0f, 2.0f);

wavout_wavinfo_t* background_music;
wavout_wavinfo_t* CannonSound;
wavout_wavinfo_t* ExplosionSound;
wavout_wavinfo_t* LaserSound;

u8 difficulty = medium;

int CreateExplosion(float x, float y, float z, float radius, float speed, int team, int member, float damage)
{
    explosion1->vel_range.x = speed; explosion1->vel_range.y = speed; explosion1->vel_range.z = speed;
    explosion1->Explode(x, y, z, 100);
    explosion2->vel_range.x = speed*0.5f; explosion2->vel_range.y = speed*0.5f; explosion2->vel_range.z = speed*0.5f;
    explosion2->Explode(x, y, z, 50);
    explosion_smoke->Explode(x, y, z, 35);

    Sound_3D(ExplosionSound, x, y);

    if (team < 0 || damage <= 0) return 0;

    int points = 0;
    float explosiondist;
    if (PlayerAlive)
    {
        if ((explosiondist = CircleCollision(posPlayerX, posPlayerY, 0, x, y, radius)) >= 0)
        {
            PlayerHealth -= (team == PLAYER_TEAM ? FF_DMG_PERCENT : 1) * damage * ((radius - explosiondist)*x_inverse(radius));
            if (PlayerHealth <= 0)
            {
                if (team == PLAYER_TEAM)
                {
                    points--;
                    if (member == PLAYER_MEMBER) bg3dConsole.Print(0x0000bf, "You committed suicide!");
                }
                else
                {
                    points++;
                    bg3dConsole.Print(0x0000bf, "An enemy killed you with cannons!");
                }
            }
        }
    }
    for (int t = 0; t < MAX_TEAMS; t++)
    {
        if (TeamInPlay[t])
        {
            for (int i = 0; i < NUM_ENEMIES - (t == PLAYER_TEAM ? 1 : 0); i++)
            {
                if (Enemy[t][i].Alive)
                {
                    if ((explosiondist = CircleCollision(Enemy[t][i].posTankX, Enemy[t][i].posTankY, 0, x, y, radius)) >= 0)
                    {
                        Enemy[t][i].Health -= (t == team ? FF_DMG_PERCENT : 1) * damage * ((radius - explosiondist)*x_inverse(radius));
                        if (Enemy[t][i].Health <= 0)
                        {
                            if (team == t)
                            {
                                points--;
                                if (team == PLAYER_TEAM && member == PLAYER_MEMBER) bg3dConsole.Print(0x0000bf, "You killed a teammate with cannons!");
                            }
                            else
                            {
                                points++;
                                if (team == PLAYER_TEAM && member == PLAYER_MEMBER) bg3dConsole.Print(0xbf0000, "You killed an enemy with cannons!");
                            }
                        }
                    }
                }
            }
        }
    }
    return points;
}

void DisplayScores(int x, int y)
{
    int height = 2*5 + LINE_HEIGHT;
    for (int t = 0; t < MAX_TEAMS; t++)
    {
        if (TeamInPlay[t]) height += LINE_HEIGHT*NUM_ENEMIES;
    }

    xDrawRectSolid(x, y, 260, height, 0x60000000);
    int line = 5;
    xText2DPrintf(&font, x+5, y+line, 0xffffffff, 10, 1.0f, 1, 0, "            K   D   C   R");
    line += LINE_HEIGHT;
    xText2DPrintf(&font, x+5, y+line, TeamColor[1][PLAYER_TEAM], 10, 1.0f, 1, 0, "Player:   %3i %3i %3i %3i", Score, Deaths, Caps, Returns);
    line += LINE_HEIGHT;
    for (int t = 0; t < MAX_TEAMS; t++)
    {
        if (TeamInPlay[t])
        {
            for (int i = 0; i < NUM_ENEMIES - (t == PLAYER_TEAM ? 1 : 0); i++)
            {
                if (t == 0) sprintf(buffer, "Blue%02i:   %3i %3i %3i %3i", i+1, Enemy[t][i].Score, Enemy[t][i].Deaths, Enemy[t][i].Caps, Enemy[t][i].Returns);
                else if (t == 1) sprintf(buffer, "Red%02i:    %3i %3i %3i %3i", i+1, Enemy[t][i].Score, Enemy[t][i].Deaths, Enemy[t][i].Caps, Enemy[t][i].Returns);
                else if (t == 2) sprintf(buffer, "Yellow%02i: %3i %3i %3i %3i", i+1, Enemy[t][i].Score, Enemy[t][i].Deaths, Enemy[t][i].Caps, Enemy[t][i].Returns);
                else if (t == 3) sprintf(buffer, "Green%02i:  %3i %3i %3i %3i", i+1, Enemy[t][i].Score, Enemy[t][i].Deaths, Enemy[t][i].Caps, Enemy[t][i].Returns);
                xText2DPrintf(&font, x+5, y+line, TeamColor[1][t], 10, 1.0f, 1, 0, buffer);
                line += LINE_HEIGHT;
            }
        }
    }
}

void SetMipmapFilter()
{
    if (Camera == 0)
    {
        sceGuTexFilter(GU_LINEAR, GU_LINEAR);
    }
    else
    {
        sceGuTexFilter(GU_NEAREST_MIPMAP_LINEAR, GU_NEAREST_MIPMAP_LINEAR);
    }
}

void SetGroundTex()
{
    if (Camera == 0)
    {
        ground_tex0.SetImage(0, 0);
        ground_tex0.SetImage(0, 1);
        ground_tex1.SetImage(0, 2);
        ground_tex2.SetImage(0, 3);
    }
    else
    {
        ground_tex0.SetImage(3, 0);
        ground_tex0.SetImage(3, 1);
        ground_tex1.SetImage(3, 2);
        ground_tex2.SetImage(3, 3);
    }
}

void SetCellTex()
{
    if (Camera == 0)
    {
        tech_tex0.SetImage(0, 0);
        tech_tex0.SetImage(0, 1);
        tech_tex1.SetImage(0, 2);
        tech_tex2.SetImage(0, 3);
    }
    else
    {
        tech_tex0.SetImage(3, 0);
        tech_tex0.SetImage(3, 1);
        tech_tex1.SetImage(3, 2);
        tech_tex2.SetImage(3, 3);
    }
}

int main(int argc, char **argv)
{
    xLibSetupCallbacks();
    x_auto_srand();
    xLibDtInit();
    xCtrlInit();
    xGuInit(1024*1024, X_SCISSOR_TEST|X_DEPTH_TEST|X_CULL_FACE|X_CLIP_PLANES, 0);
    xGuFrameStart();
    sceGuEnable(GU_LIGHTING);
    sceGuEnable(GU_LIGHT0);
    ScePspFVector3 lightPosition = {0.0f, 0.0f, 10000.0f};
    sceGuLight( 0, GU_POINTLIGHT, GU_AMBIENT_AND_DIFFUSE, &lightPosition );
    sceGuLightColor( 0, GU_AMBIENT, 0xff3f3f3f);
    sceGuLightColor( 0, GU_DIFFUSE, 0xffffffff);
    sceGuAmbient(0xff4f4f4f);
    xGuPerspective(70.0f, PERSPECT_NEAR, PERSPECT_FAR);
    xGuFrameEnd();

    wavInit();

    pspDebugScreenInit();

    scePowerSetClockFrequency(333, 333, 166);

    sceKernelDcacheWritebackAll();

    {
        xTexture splash;
        splash.LoadTGA("./textures/splash.tga");
        for (short alpha = 255; alpha > 0; alpha -= 6)
        {
            xGuFrameStart();
            xDrawTexture(0, 0, &splash);
            xDrawScreen(alpha << 24 | 0x000000);
            xGuFrameEnd();
            xGuSwapBuffers(1);
        }
        for (short alpha = 0; alpha < 255; alpha += 6)
        {
            xGuFrameStart();
            xDrawTexture(0, 0, &splash);
            xDrawScreen(alpha << 24 | 0x000000);
            xGuFrameEnd();
            xGuSwapBuffers(1);
        }
        //splash.Free();
    }

    ground_tex0.LoadTGA("./textures/ground1.tga");
    ground_tex0.Swizzle();
    ground_tex0.MoveToVRAM();
    ground_tex1.LoadTGA("./textures/ground2.tga");
    ground_tex1.Swizzle();
    ground_tex1.MoveToVRAM();
    ground_tex2.LoadTGA("./textures/ground3.tga");
    ground_tex2.Swizzle();
    ground_tex2.MoveToVRAM();

    part_tex.LoadTGA("./textures/particle.tga");
    part_tex.Swizzle();
    part_tex.GrayscaleToAlpha();
    part_tex.MoveToVRAM();
    smoke_tex.LoadTGA("./textures/smoke.tga");
    smoke_tex.Swizzle();
    smoke_tex.GrayscaleToAlpha();
    smoke_tex.MoveToVRAM();

    tech_tex0.LoadTGA("./textures/tech1.tga");
    tech_tex0.Swizzle();
    tech_tex0.MoveToVRAM();
    tech_tex1.LoadTGA("./textures/tech2.tga");
    tech_tex1.Swizzle();
    tech_tex1.MoveToVRAM();
    tech_tex2.LoadTGA("./textures/tech3.tga");
    tech_tex2.Swizzle();
    tech_tex2.MoveToVRAM();

    //sky_tex_top.LoadTGA("./textures/skybox_top.tga");
    //sky_tex_top.Swizzle();
    sky_tex_bottom.LoadTGA("./textures/skybox_bottom.tga");
    sky_tex_bottom.Swizzle();
    sky_tex_front.LoadTGA("./textures/skybox_front.tga");
    sky_tex_front.Swizzle();
    sky_tex_back.LoadTGA("./textures/skybox_back.tga");
    sky_tex_back.Swizzle();
    sky_tex_left.LoadTGA("./textures/skybox_left.tga");
    sky_tex_left.Swizzle();
    sky_tex_right.LoadTGA("./textures/skybox_right.tga");
    sky_tex_right.Swizzle();

    font.LoadTGA("./textures/font.tga");
    font.Swizzle();
    //font.MoveToVRAM();

    background_music = wavLoad("./sounds/music.wav");
    background_music->playloop = 1;
    wavPlay(background_music);
    CannonSound = wavLoad("./sounds/cannon.wav");
    ExplosionSound = wavLoad("./sounds/explosion.wav");
    LaserSound = wavLoad("./sounds/laser.wav");

    {
        ScePspFVector3 source, source_range, velocity, vel_range, gravity;
        source.x = 0; source.y = 0; source.z = 0;
        source_range.x = 0; source_range.y = 0; source_range.z = 0;
        gravity.x = 0; gravity.y = 0; gravity.z = 0;

        velocity.x = 0; velocity.y = 0; velocity.z = 0;
        vel_range.x = 750; vel_range.y = 750; vel_range.z = 750;
        explosion1 = new xExplosion(100*EXPLOSION_CACHE);
        explosion1->SetAll(&source, &source_range, &velocity, &vel_range, &gravity, 0.1f, 0.2f);
        explosion2 = new xExplosion(50*EXPLOSION_CACHE);
        explosion2->SetAll(&source, &source_range, &velocity, &vel_range, &gravity, 0.1f, 0.2f);

        source_range.x = 0; source_range.y = 0; source_range.z = 0;
        velocity.x = 0; velocity.y = 0; velocity.z = 200;
        vel_range.x = 100; vel_range.y = 100; vel_range.z = 100;
        explosion_smoke = new xExplosion(35*EXPLOSION_CACHE);
        explosion_smoke->SetAll(&source, &source_range, &velocity, &vel_range, &gravity, 0.5f, 1.0f);

        source_range.x = 0.5f*TANK_RADIUS; source_range.y = 0.5f*TANK_RADIUS; source_range.z = 0;
        velocity.x = 0; velocity.y = 0; velocity.z = 0;
        vel_range.x = 100; vel_range.y = 100; vel_range.z = 25;
        boost_glow = new xExplosion(200);
        boost_glow->SetAll(&source, &source_range, &velocity, &vel_range, &gravity, 0.5f, 1.0f);

        velocity.x = 0; velocity.y = 0; velocity.z = -50;
        source_range.x = 0.5f*TANK_RADIUS; source_range.y = 0.5f*TANK_RADIUS; source_range.z = 0;
        vel_range.x = 0; vel_range.y = 0; vel_range.z = 10;
        tank_glow = new xExplosion(200);
        tank_glow->SetAll(&source, &source_range, &velocity, &vel_range, &gravity, 0.1f, 0.2f);

        source_range.x = 0; source_range.y = 0; source_range.z = 0;
        velocity.x = 0; velocity.y = 0; velocity.z = 0;
        vel_range.x = 0; vel_range.y = 0; vel_range.z = 0;
        laser_part = new xExplosion(250);
        laser_part->SetAll(&source, &source_range, &velocity, &vel_range, &gravity, 0.1f, 0.2f);
        cannon_trail = new xExplosion(200);
        cannon_trail->SetAll(&source, &source_range, &velocity, &vel_range, &gravity, 0.1f, 0.2f);

        source.z = 15.0f;
        source_range.x = 0; source_range.y = 0; source_range.z = 0;
        velocity.x = 0; velocity.y = 0; velocity.z = 0;
        vel_range.x = 100; vel_range.y = 100; vel_range.z = 0;
        for (int i = 0; i < MAX_TEAMS; i++)
        {
            flag_smoke[i] = new xExplosion(75);
            flag_smoke[i]->SetAll(&source, &source_range, &velocity, &vel_range, &gravity, 1.0f, 1.5f);
        }
    }

    for (int i = 0; i < 72*3; i++)
    {
        roundcell[i].x *= ROUND_BLOCK_RADIUS;
        roundcell[i].y *= ROUND_BLOCK_RADIUS;
        roundcell[i].z *= WALL_HEIGHT;
    }

    xVertSoftNormals(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(reticle1)/sizeof(CNVertexF), reticle1);
    xVertSoftNormals(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(reticle2)/sizeof(CNVertexF), reticle2);
    xVertSoftNormals(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(mine)/sizeof(CNVertexF), mine);
    xVertSoftNormals(GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(Stripe)/sizeof(NVertexF), Stripe);
    xVertSoftNormals(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(cannon)/sizeof(CNVertexF), cannon);
    xVertSoftNormals(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(dome)/sizeof(CNVertexF), dome);
    xVertSoftNormals(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(base)/sizeof(CNVertexF), base);
    xVertSoftNormals(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(ret1)/sizeof(CNVertexF), ret1);
    xVertSoftNormals(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(ret2)/sizeof(CNVertexF), ret2);
    xVertSoftNormals(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(ret3)/sizeof(CNVertexF), ret3);
    xVertSoftNormals(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(ret4)/sizeof(CNVertexF), ret4);
    xVertSoftNormals(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(ret5)/sizeof(CNVertexF), ret5);
    xVertSoftNormals(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(retsmall)/sizeof(CNVertexF), retsmall);
    xVertSoftNormals(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(roundcell)/sizeof(CNVertexF), roundcell);

    sceGuStart(GU_CALL, tankList);
    xVertTranslate(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(cannon)/sizeof(CNVertexF), cannon, &cannonPos);
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 120*3, 0, cannon);
    xVertTranslate(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(dome)/sizeof(CNVertexF), dome, &domePos);
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 112*3, 0, dome);
    xVertTranslate(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(base)/sizeof(CNVertexF), base, &basePos);
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 168*3, 0, base);
    xVertTranslate(GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(Stripe)/sizeof(NVertexF), Stripe, &domePos);
    sceGuDrawArray(GU_TRIANGLES, GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 7*3, 0, Stripe);
    sceGuFinish();

    sceGuStart(GU_CALL, mineList);
    sceGuDrawArray( GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 96*3, 0, mine);
    sceGuFinish();

    sceGuStart(GU_CALL, flagList);
    xVertTranslate(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(pole)/sizeof(CNVertexF), pole, &polePos);
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 10*3, 0, pole);
    xVertTranslate(GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(flag)/sizeof(NVertexF), flag, &flagPos);
    sceGuDrawArray(GU_TRIANGLES, GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, 0, flag);
    sceGuFinish();

    sceGuStart(GU_CALL, groundList);
    sceGuDrawArray( GU_TRIANGLES, GU_TEXTURE_32BITF|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 6, 0, ground);
    sceGuFinish();

    sceGuStart(GU_CALL, cellList);
    sceGuDrawArray( GU_TRIANGLES, GU_TEXTURE_32BITF|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 10*3, 0, cell);
    sceGuFinish();

    sceGuStart(GU_CALL, roundcellList);
    sceGuDrawArray( GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 72*3, 0, roundcell);
    sceGuFinish();

    sceGuStart(GU_CALL, reticleList);
    sceGuDrawArray(GU_TRIANGLE_FAN, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 8, 0, reticle1);
    sceGuDrawArray(GU_TRIANGLE_FAN, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 8, 0, reticle2);
    sceGuDrawArray(GU_TRIANGLE_FAN, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 8, 0,
                   xVertNewRotatedZ(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, 8, reticle1, PI));
    sceGuDrawArray(GU_TRIANGLE_FAN, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 8, 0,
                   xVertNewRotatedZ(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, 8, reticle2, PI));
    sceGuFinish();

    sceGuStart(GU_CALL, spatialretList);
    xVertTranslate(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(ret1)/sizeof(CNVertexF), ret1, &ret1Pos);
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, 0, ret1);
    xVertTranslate(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(ret2)/sizeof(CNVertexF), ret2, &ret2Pos);
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, 0, ret2);
    xVertTranslate(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(ret3)/sizeof(CNVertexF), ret3, &ret3Pos);
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, 0, ret3);
    xVertTranslate(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(ret4)/sizeof(CNVertexF), ret4, &ret4Pos);
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, 0, ret4);
    xVertTranslate(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, sizeof(ret5)/sizeof(CNVertexF), ret5, &ret5Pos);
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, 0, ret5);
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, 0,
                   xVertNewTranslated(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, 12*3, retsmall, &retsmall1Pos));
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, 0,
                   xVertNewTranslated(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, 12*3, retsmall, &retsmall2Pos));
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, 0,
                   xVertNewTranslated(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, 12*3, retsmall, &retsmall3Pos));
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, 0,
                   xVertNewTranslated(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, 12*3, retsmall, &retsmall4Pos));
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, 0,
                   xVertNewTranslated(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, 12*3, retsmall, &retsmall5Pos));
    xVertTranslate(GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF, 12*3, retsmall, &retsmall6Pos);
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, 0, retsmall);
    sceGuFinish();

    bool main_loop = 1;
    while(xLibRunning() && main_loop)
    {
        int game_state = 0;
        {
            int MenuOption = 1;
            NUM_ENEMIES = 2;

            xTexture background;
            background.LoadTGA("./textures/background.tga");

            xLibDirectory maps(32, 32);
            maps.Read("./maps/", ".bgm");

            bool main_menu = 1;
            while(xLibRunning() && main_menu)
            {
                dt = xLibDtGet();
                bg3dConsole.UpdateConsole(dt);
                xCtrlRead(dt);
                if (xCtrlTap(PSP_CTRL_UP) && MenuOption > 1) MenuOption -= 1;
                if (xCtrlTap(PSP_CTRL_DOWN) && MenuOption < 4) MenuOption += 1;
                if (xCtrlTap(PSP_CTRL_CROSS))
                {
                    if (MenuOption == 1) //Start Game
                    {
                        xLibDirectory maps(32, 32);
                        maps.Read("./maps/", ".bgm");

                        int MenuOption2 = 1;
                        bool map_menu = 1;
                        while(xLibRunning() && map_menu)
                        {
                            dt = xLibDtGet();
                            xCtrlRead(dt);
                            if (xCtrlTap(PSP_CTRL_UP) && MenuOption2 > 1) MenuOption2 -= 1;
                            if (xCtrlTap(PSP_CTRL_DOWN) && MenuOption2 < maps.NumFiles() + 2) MenuOption2 += 1;
                            if (xCtrlTap(PSP_CTRL_LEFT))
                            {
                                if (MenuOption2 == 1 && NUM_ENEMIES > 1) NUM_ENEMIES -= 1;
                                if (MenuOption2 == 2 && difficulty > easy) difficulty -= 1;
                            }
                            if (xCtrlTap(PSP_CTRL_RIGHT))
                            {
                                if (MenuOption2 == 1 && NUM_ENEMIES < MAX_ENEMIES) NUM_ENEMIES += 1;
                                if (MenuOption2 == 2 && difficulty < hard) difficulty += 1;
                            }
                            if (xCtrlTap(PSP_CTRL_CIRCLE)) map_menu = 0;
                            if (xCtrlTap(PSP_CTRL_CROSS) && MenuOption2 > 2)
                            {
                                //map chosen, load map and exit menu
                                sprintf(buffer, "./maps/%s", maps[MenuOption2 - 3]);
                                if (map.LoadMap(buffer))
                                {
                                    if (SetupAstar())
                                    {
                                        game_state = 1;
                                        main_menu = 0;
                                        map_menu = 0;
                                    }
                                    else
                                    {
                                        //EndAstar();
                                        map.Free();
                                        bg3dConsole.Print(0xffffff, "A* failed to initialize.");
                                    }
                                }
                                else
                                {
                                    bg3dConsole.Print(0xffffff, "Failed to load map.");
                                }
                            }
                            bg3dConsole.UpdateConsole(dt);
                            xGuFrameStart();
                            xDrawTexture(0, 0, &background);
                            xText2DPrintf(&font, 240, 10, 0xFF0000FF, 0, 2.0f, 1, 1, title_text);
                            int line = 40;
                            xText2DPrintf(&font, 240, line, (MenuOption2 == 1 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Enemies: %i", NUM_ENEMIES);
                            line += LINE_HEIGHT;
                            xText2DPrintf(&font,240, line, (MenuOption2 == 2 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1,
                                       "Difficulty: %s", difficulty == easy ? "Easy" : (difficulty == medium ? "Medium" : "Hard"));
                            for (int i = 0; i < maps.NumFiles(); i++)
                            {
                                line += LINE_HEIGHT;
                                xText2DPrintf(&font, 240, line, (MenuOption2 == i+3 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, maps[i]);
                            }
                            bg3dConsole.RenderConsole(&font, 5, 256 - 5*LINE_HEIGHT, 0, 5*LINE_HEIGHT, LINE_HEIGHT, 1);
                            xGuFrameEnd();
                            xGuSwapBuffers(0);
                        }
                    }
                    else if (MenuOption == 2) //Map Editor
                    {
                        xLibDirectory maps(32, 32);
                        maps.Read("./maps/", ".bgm");

                        int MenuOption2 = 1;
                        bool map_menu = 1;
                        while(xLibRunning() && map_menu)
                        {
                            dt = xLibDtGet();
                            xCtrlRead(dt);
                            if (xCtrlTap(PSP_CTRL_UP) && MenuOption2 > 1) MenuOption2 -= 1;
                            if (xCtrlTap(PSP_CTRL_DOWN) && MenuOption2 < maps.NumFiles() + 1) MenuOption2 += 1;
                            if (xCtrlTap(PSP_CTRL_CIRCLE)) map_menu = 0;
                            if (xCtrlTap(PSP_CTRL_CROSS))
                            {
                                if (MenuOption2 == 1) //new map
                                {
                                    int length = 8;
                                    int height = 8;
                                    int MenuOption3 = 1;
                                    bool editor_menu = 1;
                                    while(xLibRunning() && editor_menu)
                                    {
                                        dt = xLibDtGet();
                                        xCtrlRead(dt);
                                        if (xCtrlTap(PSP_CTRL_UP) && MenuOption3 > 1) MenuOption3 -= 1;
                                        if (xCtrlTap(PSP_CTRL_DOWN) && MenuOption3 < 3) MenuOption3 += 1;
                                        if (xCtrlTap(PSP_CTRL_CIRCLE)) editor_menu = 0;
                                        if (xCtrlTap(PSP_CTRL_LEFT) && length*height > 2)
                                        {
                                            if (MenuOption3 == 1) length -= 1;
                                            if (MenuOption3 == 2) height -= 1;
                                        }
                                        if (xCtrlTap(PSP_CTRL_RIGHT))
                                        {
                                            if (MenuOption3 == 1 && length < 64) length += 1;
                                            if (MenuOption3 == 2 && height < 64) height += 1;
                                        }
                                        if (xCtrlTap(PSP_CTRL_CROSS) && MenuOption3 == 3)
                                        {
                                            while(xCtrlRead(dt));
                                            map.Create(length, height);
                                            game_state = 2;
                                            main_menu = 0;
                                            map_menu = 0;
                                            editor_menu = 0;
                                        }
                                        bg3dConsole.UpdateConsole(dt);
                                        xGuFrameStart();
                                        xDrawTexture(0, 0, &background);
                                        xText2DPrintf(&font, 240, 10, 0xFF0000FF, 0, 2.0f, 1, 1, title_text);
                                        int line = 40;
                                        xText2DPrintf(&font, 240, line, (MenuOption3 == 1 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Length: %i", length);
                                        line += LINE_HEIGHT;
                                        xText2DPrintf(&font, 240, line, (MenuOption3 == 2 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Height: %i", height);
                                        line += LINE_HEIGHT;
                                        xText2DPrintf(&font, 240, line, (MenuOption3 == 3 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Create");
                                        bg3dConsole.RenderConsole(&font, 5, 256 - 5*LINE_HEIGHT, 0, 5*LINE_HEIGHT, LINE_HEIGHT, 1);
                                        xGuFrameEnd();
                                        xGuSwapBuffers(0);
                                    }
                                }
                                else //already created map
                                {
                                    //map chosen, load map and exit menu
                                    while(xCtrlRead(dt));
                                    sprintf(buffer, "./maps/%s", maps[MenuOption2 - 2]);
                                    if (map.LoadMap(buffer))
                                    {
                                        game_state = 2;
                                        main_menu = 0;
                                        map_menu = 0;
                                    }
                                    else bg3dConsole.Print(0xffffff, "Failed to load map.");
                                }
                            }
                            if (xCtrlTap(PSP_CTRL_TRIANGLE) && MenuOption2 > 1)
                            {
                                //ask if sure want to delete map
                                int MenuOption3 = 1;
                                bool asking = 1;
                                while(xLibRunning() && asking)
                                {
                                    dt = xLibDtGet();
                                    xCtrlRead(dt);
                                    if (xCtrlTap(PSP_CTRL_UP) && MenuOption3 > 1) MenuOption3 -= 1;
                                    if (xCtrlTap(PSP_CTRL_DOWN) && MenuOption3 < 2) MenuOption3 += 1;
                                    if (xCtrlTap(PSP_CTRL_CIRCLE)) asking = 0;
                                    if (xCtrlTap(PSP_CTRL_CROSS))
                                    {
                                        if (MenuOption3 == 1) //Yes, delete
                                        {
                                            sprintf(buffer, "./maps/%s", maps[MenuOption2 - 2]);
                                            remove(buffer);
                                            maps.Read("./maps/", ".bgm");
                                            if (MenuOption2 > maps.NumFiles() + 1) MenuOption2 = maps.NumFiles() + 1;
                                            asking = 0;
                                        }
                                        else if (MenuOption3 == 2) //No, continue
                                        {
                                            asking = 0;
                                        }
                                    }
                                    bg3dConsole.UpdateConsole(dt);
                                    xGuFrameStart();
                                    xDrawTexture(0, 0, &background);
                                    xText2DPrintf(&font, 240, 10, 0xFF0000FF, 0, 2.0f, 1, 1, title_text);
                                    xText2DPrintf(&font, 240, 40, 0xFFFFFFFF, 0, 1.0f, 1, 1, "Really delete map?");
                                    int line = 60;
                                    xText2DPrintf(&font, 240, line, (MenuOption3 == 1 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Yes");
                                    line += LINE_HEIGHT;
                                    xText2DPrintf(&font, 240, line, (MenuOption3 == 2 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "No");
                                    bg3dConsole.RenderConsole(&font, 5, 256 - 5*LINE_HEIGHT, 0, 5*LINE_HEIGHT, LINE_HEIGHT, 1);
                                    xGuFrameEnd();
                                    xGuSwapBuffers(0);
                                }
                            }
                            bg3dConsole.UpdateConsole(dt);
                            xGuFrameStart();
                            xDrawTexture(0, 0, &background);
                            xText2DPrintf(&font, 240, 10, 0xFF0000FF, 0, 2.0f, 1, 1, title_text);
                            int line = 40;
                            xText2DPrintf(&font, 240, line, (MenuOption2 == 1 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "New Map");
                            for (int i = 0; i < maps.NumFiles(); i++)
                            {
                                line += LINE_HEIGHT;
                                xText2DPrintf(&font, 240, line, (MenuOption2 == i+2 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, maps[i]);
                            }
                            bg3dConsole.RenderConsole(&font, 5, 256 - 5*LINE_HEIGHT, 0, 5*LINE_HEIGHT, LINE_HEIGHT, 1);
                            xGuFrameEnd();
                            xGuSwapBuffers(0);
                        }
                    }
                    else if (MenuOption == 3) //Options
                    {
                        //volume and deadzone settings
                        int MenuOption2 = 1;
                        bool options_menu = 1;
                        while(xLibRunning() && options_menu)
                        {
                            dt = xLibDtGet();
                            xCtrlRead(dt);
                            if (xCtrlTap(PSP_CTRL_UP) && MenuOption2 > 1) MenuOption2 -= 1;
                            if (xCtrlTap(PSP_CTRL_DOWN) && MenuOption2 < 3) MenuOption2 += 1;
                            if (xCtrlPress(PSP_CTRL_LEFT))
                            {
                                if (MenuOption2 == 1) //deadzone
                                {
                                    if (cfg_analog_deadzone > 0) cfg_analog_deadzone -= 1;
                                }
                                else if (MenuOption2 == 2) //sfx volume
                                {
                                    if (cfg_sfx_volume > 0) cfg_sfx_volume -= 0.5f*dt;
                                    if (cfg_sfx_volume < 0) cfg_sfx_volume = 0;
                                }
                                else if (MenuOption2 == 3) //bg volume
                                {
                                    if (cfg_bg_volume > 0) cfg_bg_volume -= 0.5f*dt;
                                    if (cfg_bg_volume < 0) cfg_bg_volume = 0;
                                    adjustVolume(0, cfg_bg_volume);
                                }
                            }
                            if (xCtrlPress(PSP_CTRL_RIGHT))
                            {
                                if (MenuOption2 == 1) //deadzone
                                {
                                    if (cfg_analog_deadzone < 100) cfg_analog_deadzone += 1;
                                }
                                else if (MenuOption2 == 2) //sfx volume
                                {
                                    if (cfg_sfx_volume < 1) cfg_sfx_volume += 0.5f*dt;
                                    if (cfg_sfx_volume > 1) cfg_sfx_volume = 1;
                                }
                                else if (MenuOption2 == 3) //bg volume
                                {
                                    if (cfg_bg_volume < 1) cfg_bg_volume += 0.5f*dt;
                                    if (cfg_bg_volume > 1) cfg_bg_volume = 1;
                                    adjustVolume(0, cfg_bg_volume);
                                }
                            }
                            if (xCtrlTap(PSP_CTRL_CIRCLE))
                            {
                                options_menu = 0;
                            }
                            bg3dConsole.UpdateConsole(dt);
                            xGuFrameStart();
                            xDrawTexture(0, 0, &background);
                            xText2DPrintf(&font, 240, 10, 0xFF0000FF, 0, 2.0f, 1, 1, title_text);
                            int line = 40;
                            xText2DPrintf(&font, 240, line, (MenuOption2 == 1 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Analog Deadzone: %u", cfg_analog_deadzone);
                            line += LINE_HEIGHT;
                            xText2DPrintf(&font, 240, line, (MenuOption2 == 2 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "SFX Volume");
                            line += LINE_HEIGHT;
                            xDrawRectSolid(240 - (SETTINGS_BOX_LENGTH>>1), line, SETTINGS_BOX_LENGTH, SETTINGS_BOX_HEIGHT, 0xaf3f3f3f);
                            xDrawRectSolid(240 - (SETTINGS_BOX_LENGTH>>1) + (int)(cfg_sfx_volume*SETTINGS_BOX_LENGTH) - (SETTINGS_POS_LENGTH>>1), line,
                                           SETTINGS_POS_LENGTH, SETTINGS_BOX_HEIGHT, (MenuOption2 == 2 ? 0xcfafafaf : 0xaf7f7f7f));
                            line += LINE_HEIGHT;
                            xText2DPrintf(&font, 240, line, (MenuOption2 == 3 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Music Volume");
                            line += LINE_HEIGHT;
                            xDrawRectSolid(240 - (SETTINGS_BOX_LENGTH>>1), line, SETTINGS_BOX_LENGTH, SETTINGS_BOX_HEIGHT, 0xaf3f3f3f);
                            xDrawRectSolid(240 - (SETTINGS_BOX_LENGTH>>1) + (int)(cfg_bg_volume*SETTINGS_BOX_LENGTH) - (SETTINGS_POS_LENGTH>>1), line,
                                           SETTINGS_POS_LENGTH, SETTINGS_BOX_HEIGHT, (MenuOption2 == 3 ? 0xcfafafaf : 0xaf7f7f7f));
                            bg3dConsole.RenderConsole(&font, 5, 256 - 5*LINE_HEIGHT, 0, 5*LINE_HEIGHT, LINE_HEIGHT, 1);
                            xGuFrameEnd();
                            xGuSwapBuffers(0);
                        }
                    }
                    else if (MenuOption == 4) //Exit Game
                    {
                        main_loop = 0;
                        main_menu = 0;
                    }
                }
                bg3dConsole.UpdateConsole(dt);
                xGuFrameStart();
                xDrawTexture(0, 0, &background);
                xText2DPrintf(&font, 240, 10, 0xFF0000FF, 0, 2.0f, 1, 1, title_text);
                int line = 40;
                xText2DPrintf(&font, 240, line, (MenuOption == 1 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Start Game");
                line += LINE_HEIGHT;
                xText2DPrintf(&font, 240, line, (MenuOption == 2 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Map Editor");
                line += LINE_HEIGHT;
                xText2DPrintf(&font, 240, line, (MenuOption == 3 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Options");
                line += LINE_HEIGHT;
                xText2DPrintf(&font, 240, line, (MenuOption == 4 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Exit Game");
                bg3dConsole.RenderConsole(&font, 5, 256 - 5*LINE_HEIGHT, 0, 5*LINE_HEIGHT, LINE_HEIGHT, 1);
                xGuFrameEnd();
                xGuSwapBuffers(0);
            }
        }

        if (game_state == 1)
        {
            SpawnPlayer();
            for (int t = 0; t < MAX_TEAMS; t++)
            {
                if (TeamInPlay[t])
                {
                    for (int i = 0; i < NUM_ENEMIES; i++) Enemy[t][i].Spawn();
                    SpawnFlag(t);
                }
            }
            Game();
            map.Free();
            EndAstar();
        }

        if (game_state == 2)
        {
            MapEditor();
            map.Free();
        }
    }

    wavoutStopPlay();
    sceGuTerm();

    sceKernelExitGame();
    return 0;
}

#define EDIT_PAUSE_Y (60)
#define EDIT_PAUSE_HEIGHT (60)
#define EDIT_PAUSE_MARGINS (160)

void PauseEditor()
{
    //pause menu for game
    int MenuOption = 1;
    bool paused = 1;
    while(xLibRunning() && paused)
    {
        dt = xLibDtGet();
        xCtrlRead(dt);
        if (xCtrlTap(PSP_CTRL_UP) && MenuOption > 1) MenuOption -= 1;
        if (xCtrlTap(PSP_CTRL_DOWN) && MenuOption < 4) MenuOption += 1;
        if ((xCtrlTap(PSP_CTRL_LEFT) || xCtrlTap(PSP_CTRL_RIGHT)) && MenuOption == 2) cfg_show_fps = !cfg_show_fps;
        if (xCtrlTap(PSP_CTRL_CIRCLE) || xCtrlTap(PSP_CTRL_START))
        {
            while(xCtrlRead(dt));
            paused = 0;
        }
        if (xCtrlTap(PSP_CTRL_CROSS))
        {
            while(xCtrlRead(dt));
            if (MenuOption == 1) //resume
            {
                paused = 0;
            }
            else if (MenuOption == 3) //Save map
            {
                if (!map.Valid())
                {
                    bg3dConsole.Print(0xffffff, "Map not valid. Maps require at least");
                    bg3dConsole.Print(0xffffff, "a blue flag and one other flag.");
                }
                else
                {
                    xLibDirectory my_maps(32, 32);
                    my_maps.Read("./maps/", ".bgm");
                    bool map_saved = 0;
                    int i = 1;
                    while (!map_saved)
                    {
                        sprintf(buffer, "mymap%02i.bgm", i);
                        bool map_exists = 0;
                        for (int j = 0; j < my_maps.NumFiles(); j++)
                        {
                            if (!stricmp(my_maps[j], buffer)) map_exists = 1;
                        }
                        if (!map_exists)
                        {
                            sprintf(buffer2, "./maps/%s", buffer);
                            map.SaveMap(buffer2);
                            map_saved = 1;
                        }
                        i += 1;
                    }
                }
            }
            else if (MenuOption == 4) //quit
            {
                in_game = 0;
                paused = 0;
            }
        }
        bg3dConsole.UpdateConsole(dt);
        xGuFrameStart();
        DrawEditor();
        xDrawRectSolid(EDIT_PAUSE_MARGINS, EDIT_PAUSE_Y, 480 - 2*EDIT_PAUSE_MARGINS, EDIT_PAUSE_HEIGHT, 0x60000000);
        xText2DPrintf(&font, 240, 10, 0xFF0000FF, 0, 2.0f, 1, 1, title_text);
        int line = EDIT_PAUSE_Y + 5;
        xText2DPrintf(&font, 240, line, (MenuOption == 1 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Resume");
        line += LINE_HEIGHT;
        xText2DPrintf(&font, 240, line, (MenuOption == 2 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Show FPS? %s", (cfg_show_fps ? "Yes" : "No "));
        line += LINE_HEIGHT;
        xText2DPrintf(&font, 240, line, (MenuOption == 3 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Save Map");
        line += LINE_HEIGHT;
        xText2DPrintf(&font, 240, line, (MenuOption == 4 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Quit Game");
        if (cfg_show_fps)
        {
            xText2DPrintf(&font, 1, 258, 0xFFFFFFFF, 0, 1.0f, 1, 0, "FPS: %f", xLibDtFps(dt));
        }
        bg3dConsole.RenderConsole(&font, 5, 256 - 5*LINE_HEIGHT, 0, 5*LINE_HEIGHT, LINE_HEIGHT, 1);
        xGuFrameEnd();
        xGuSwapBuffers(0);
    }
}

float cursor_x;
float cursor_y;

float editor_x;
float editor_y;

#define CAM_FOLLOW_X (2000.0f)
#define CAM_FOLLOW_Y (1100.0f)

void MapEditor()
{
    for (int i = 0; i < MAX_TEAMS; i++) flag_smoke[i]->KillSystem();
    explosion1->KillSystem();
    explosion2->KillSystem();
    explosion_smoke->KillSystem();
    boost_glow->KillSystem();
    laser_part->KillSystem();
    cannon_trail->KillSystem();
    tank_glow->KillSystem();

    Camera = 0;
    zoom[0] = ZOOM_MAX;
    cursor_x = 0;
    cursor_y = 0;
    editor_x = 0;
    editor_y = 0;
    in_game = 1;
    xLibDtInit();
    while (xLibRunning() && in_game)
    {
        dt = xLibDtGet();
        xCtrlRead(dt);

        if (xCtrlTap(PSP_CTRL_START))
        {
            PauseEditor();
            xLibDtInit();
        }

        int x = (int)(cursor_x/CELL_LENGTH);
        int y = (int)(cursor_y/CELL_LENGTH);

        if (xCtrlPress(PSP_CTRL_RTRIGGER)) map.SetFeature(x, y, '0');

        if (xCtrlPress(PSP_CTRL_UP) && !TeamInPlay[0]) map.SetFeature(x, y, 'a');
        if (xCtrlPress(PSP_CTRL_RIGHT) && !TeamInPlay[1]) map.SetFeature(x, y, 'b');
        if (xCtrlPress(PSP_CTRL_DOWN) && !TeamInPlay[2]) map.SetFeature(x, y, 'c');
        if (xCtrlPress(PSP_CTRL_LEFT) && !TeamInPlay[3]) map.SetFeature(x, y, 'd');

        if (xCtrlPress(PSP_CTRL_CROSS)) map.SetFeature(x, y, '1');
        if (xCtrlPress(PSP_CTRL_SQUARE)) map.SetFeature(x, y, '2');
        if (xCtrlPress(PSP_CTRL_TRIANGLE)) map.SetFeature(x, y, '6');
        if (xCtrlPress(PSP_CTRL_CIRCLE)) map.SetFeature(x, y, '5');

        if (x_absf(xCtrlAnalogX()) > (float)cfg_analog_deadzone)
        {
            cursor_x += dt*(xCtrlPress(PSP_CTRL_LTRIGGER) ? 40.0f : 20.0f)*(xCtrlAnalogX());
        }
        if (x_absf(xCtrlAnalogY()) > (float)cfg_analog_deadzone)
        {
            cursor_y += dt*(xCtrlPress(PSP_CTRL_LTRIGGER) ? 40.0f : 20.0f)*(xCtrlAnalogY());
        }

        if (cursor_x < 0) cursor_x = 0;
        if (cursor_y < 0) cursor_y = 0;

        if (cursor_x > GROUND_LENGTH - 0.01f*CELL_LENGTH) cursor_x = GROUND_LENGTH - 0.01f*CELL_LENGTH;
        if (cursor_y > GROUND_HEIGHT - 0.01f*CELL_LENGTH) cursor_y = GROUND_HEIGHT - 0.01f*CELL_LENGTH;

        if (editor_x > cursor_x + CAM_FOLLOW_X) editor_x = cursor_x + CAM_FOLLOW_X;
        if (editor_x < cursor_x - CAM_FOLLOW_X) editor_x = cursor_x - CAM_FOLLOW_X;
        if (editor_y > cursor_y + CAM_FOLLOW_Y) editor_y = cursor_y + CAM_FOLLOW_Y;
        if (editor_y < cursor_y - CAM_FOLLOW_Y) editor_y = cursor_y - CAM_FOLLOW_Y;

        rotReticle += 2.5f * dt;


        for (int i = 0; i < MAX_TEAMS; i++)
        {
            if (TeamInPlay[i]) flag_smoke[i]->Explode(FlagSpawnX[i], FlagSpawnY[i], 0.0f, 1);
            flag_smoke[i]->UpdateSystem(dt);
        }

        bg3dConsole.UpdateConsole(dt);
        xGuFrameStart();
        DrawEditor();
        if (cfg_show_fps)
        {
            xText2DPrintf(&font, 1, 258, 0xFFFFFFFF, 0, 1.0f, 1, 0, "FPS: %f", xLibDtFps(dt));
        }
        bg3dConsole.RenderConsole(&font, 5, 256 - 5*LINE_HEIGHT, 0, 5*LINE_HEIGHT, LINE_HEIGHT, 1);
        xGuFrameEnd();
        xGuSwapBuffers(0);
    }
}

void DrawEditor()
{
    cam.x = editor_x; cam.y = editor_y; cam.z = zoom[0];
    xGumSetCameraPos(cam.x, cam.y, cam.z);

    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);

    xDrawSkybox(0, 0, 0, 0, &sky_tex_bottom, 0, 1, SKYBOX_SUBDIV, -SKYBOX_OFFSET, -SKYBOX_OFFSET, -0.5f*SKYBOX_HEIGHT, SKYBOX_LENGTH, SKYBOX_LENGTH, SKYBOX_HEIGHT);

    sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
    sceGuTexFilter(GU_LINEAR, GU_LINEAR);

    for (int x = 0; x < map.Length(); x++)
    {
        for (int y = 0; y < map.Height(); y++)
        {
            if (map.Feature(x, y) == '1')
            {
                xGumSetPos(x*CELL_LENGTH + cellPos.x, y*CELL_LENGTH + cellPos.y, cellPos.z);
                SetCellTex();
                SetMipmapFilter();
                sceGuEnable(GU_TEXTURE_2D);
                sceGuColor(0xffffffff);
                xGumCallList(cellList);
                sceGuDisable(GU_TEXTURE_2D);
            }
            else
            {
                if (map.Feature(x, y) == '2')
                {
                    xGumSetPos(x*CELL_LENGTH + cellPos.x, y*CELL_LENGTH + cellPos.y, cellPos.z);
                    xGumScaleMulti(0.5f, 0.5f, 1.0f);
                    SetCellTex();
                    SetMipmapFilter();
                    sceGuEnable(GU_TEXTURE_2D);
                    sceGuColor(0xffffffff);
                    xGumCallList(cellList);
                    sceGuDisable(GU_TEXTURE_2D);
                }
                else if (map.Feature(x, y) == '5')
                {
                    xGumSetPos(x*CELL_LENGTH + cellPos.x, y*CELL_LENGTH + cellPos.y, cellPos.z);
                    xGumCallList(roundcellList);
                }
                else if (map.Feature(x, y) == '6')
                {
                    xGumSetPos(x*CELL_LENGTH + cellPos.x, y*CELL_LENGTH + cellPos.y, cellPos.z);
                    xGumScaleMulti(0.5f, 0.5f, 1.0f);
                    xGumCallList(roundcellList);
                }
                else if (map.Feature(x, y) >= 'a' && map.Feature(x, y) <= 'd')
                {
                    xGumSetPos((x+0.5f)*CELL_LENGTH, (y+0.5f)*CELL_LENGTH, 0.0f);
                    sceGuColor(TeamColor[0][map.Feature(x, y) - 'a']);
                    xGumCallList(flagList);
                }
                xGumSetPos(x*CELL_LENGTH, y*CELL_LENGTH, 0);
                SetGroundTex();
                SetMipmapFilter();
                sceGuEnable(GU_TEXTURE_2D);
                sceGuColor(0xffffffff);
                xGumCallList(groundList);
                sceGuDisable(GU_TEXTURE_2D);
            }
        }
    }

    for (int x = -1; x < map.Length() + 1; x++)
    {
        SetCellTex();
        SetMipmapFilter();
        sceGuEnable(GU_TEXTURE_2D);
        sceGuColor(0xffffffff);
        xGumSetPos((x+0.5f)*CELL_LENGTH, -CELL_LENGTH*0.5f, 0.0f);
        xGumCallList(cellList);
        xGumSetPos((x+0.5f)*CELL_LENGTH, GROUND_HEIGHT + 0.5f*CELL_LENGTH, 0.0f);
        xGumCallList(cellList);
        sceGuDisable(GU_TEXTURE_2D);
    }

    for (int y = 0; y < map.Height(); y++)
    {
        SetCellTex();
        SetMipmapFilter();
        sceGuEnable(GU_TEXTURE_2D);
        sceGuColor(0xffffffff);
        xGumSetPos(-CELL_LENGTH*0.5f, (y+0.5f)*CELL_LENGTH, 0.0f);
        xGumCallList(cellList);
        xGumSetPos(GROUND_LENGTH + 0.5f*CELL_LENGTH, (y+0.5f)*CELL_LENGTH, 0.0f);
        xGumCallList(cellList);
        sceGuDisable(GU_TEXTURE_2D);
    }

    xGumSetPos(cursor_x, cursor_y, WALL_HEIGHT);
    sceGumRotateZ(rotReticle);
    sceGuEnable(GU_BLEND);
    xGumCallList(reticleList);
    sceGuDisable(GU_BLEND);

    for (int i = 0; i < MAX_TEAMS; i++) flag_smoke[i]->RenderSystem(&smoke_tex, 75.0f, TeamColor[0][i], 0);
}

#define GAME_PAUSE_Y (60)
#define GAME_PAUSE_HEIGHT (70)
#define GAME_PAUSE_MARGINS (120)

void PauseGame()
{
    //pause menu for game
    int MenuOption = 1;
    bool paused = 1;
    while(xLibRunning() && paused)
    {
        dt = xLibDtGet();
        xCtrlRead(dt);
        if (xCtrlTap(PSP_CTRL_UP) && MenuOption > 1) MenuOption -= 1;
        if (xCtrlTap(PSP_CTRL_DOWN) && MenuOption < 5) MenuOption += 1;
        if (xCtrlTap(PSP_CTRL_LEFT) || xCtrlTap(PSP_CTRL_RIGHT))
        {
            if (MenuOption == 2) cfg_show_fps = !cfg_show_fps;
            if (MenuOption == 3) cfg_show_health = !cfg_show_health;
            if (MenuOption == 4)
            {
                Player_Lock_Team = -1;
                Player_Lock_Member = -1;
                cfg_target_lock = !cfg_target_lock;
            }
        }
        if (xCtrlTap(PSP_CTRL_CIRCLE) || xCtrlTap(PSP_CTRL_START))
        {
            paused = 0;
        }
        if (xCtrlTap(PSP_CTRL_CROSS))
        {
            if (MenuOption == 1) //resume
            {
                paused = 0;
            }
            else if (MenuOption == 5) //quit
            {
                in_game = 0;
                paused = 0;
            }
        }
        bg3dConsole.UpdateConsole(dt);
        xGuFrameStart();
        DrawGame();
        xDrawRectSolid(GAME_PAUSE_MARGINS, GAME_PAUSE_Y, 480 - 2*GAME_PAUSE_MARGINS, GAME_PAUSE_HEIGHT, 0x60000000);
        xText2DPrintf(&font, 240, 10, 0xFF0000FF, 0, 2.0f, 1, 1, title_text);
        int line = GAME_PAUSE_Y + 5;
        xText2DPrintf(&font, 240, line, (MenuOption == 1 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Resume");
        line += LINE_HEIGHT;
        xText2DPrintf(&font, 240, line, (MenuOption == 2 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Show FPS? %s", (cfg_show_fps ? "Yes" : "No ") );
        line += LINE_HEIGHT;
        xText2DPrintf(&font, 240, line, (MenuOption == 3 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Show Enemy Health? %s", (cfg_show_health ? "Yes" : "No "));
        line += LINE_HEIGHT;
        xText2DPrintf(&font, 240, line, (MenuOption == 4 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Target Lock? %s", (cfg_target_lock ? "Yes" : "No "));
        line += LINE_HEIGHT;
        xText2DPrintf(&font, 240, line, (MenuOption == 5 ? 0xFF0000FF : 0xFFFFFFFF), 0, 1.0f, 1, 1, "Quit Game");
        if (cfg_show_fps)
        {
            xText2DPrintf(&font, 1, 258, 0xFFFFFFFF, 0, 1.0f, 1, 0, "FPS: %f", xLibDtFps(dt));
        }
        bg3dConsole.RenderConsole(&font, 5, 256 - 5*LINE_HEIGHT, 0, 5*LINE_HEIGHT, LINE_HEIGHT, 1);
        xGuFrameEnd();
        xGuSwapBuffers(0);
    }
}

void Game()
{
    for (int i = 0; i < MAX_TEAMS; i++) flag_smoke[i]->KillSystem();
    explosion1->KillSystem();
    explosion2->KillSystem();
    explosion_smoke->KillSystem();
    boost_glow->KillSystem();
    laser_part->KillSystem();
    cannon_trail->KillSystem();
    tank_glow->KillSystem();

    ResetGame();
    xLibDtInit();
    while(xLibRunning() && in_game)
    {
        dt = xLibDtGet();
        xCtrlRead(dt);

        if (PlayerAlive && Camera > 1) Camera = 0;

        if (xCtrlTap(PSP_CTRL_START))
        {
            PauseGame();
            xLibDtInit();
        }
        if (xCtrlTap(PSP_CTRL_TRIANGLE))
        {
            Camera += 1;
            if (Camera > 2 || (PlayerAlive && Camera > 1)) Camera = 0;
        }

        if (Camera != 2)
        {
            if (xCtrlTap(PSP_CTRL_CIRCLE))
            {
                bool MineOut = 0;
                for (int i = 0; i < MINE_CACHE; i++)
                {
                    if (MinePrimed[i] && MineLinked[i])
                    {
                        //remote detonation
                        Score += CreateExplosion(posMineX[i], posMineY[i], 0, MINE_EXPL_RADIUS, 1400.0f, PLAYER_TEAM, PLAYER_MEMBER, MINE_DMG);
                        MinePrimed[i] = 0;
                        MineOut = 1;
                    }
                }
                if (PlayerAlive && !MineOut && NumMines > 0)
                {
                    for (int i = 0; i < MINE_CACHE; i++)
                    {
                        if (!MinePrimed[i])
                        {
                            //play WAV
                            MinePrimed[i] = 1;
                            MineLinked[i] = 1;
                            posMineX[i] = posPlayerX;
                            posMineY[i] = posPlayerY;
                            NumMines--;
                            break;
                        }
                    }
                }
            }
        }

        //if (!ThirdPerson)
        if (Camera == 0)
        {
            if ((xCtrlPress(PSP_CTRL_UP)) && zoom[0] > ZOOM_MIN)
            {
                zoom[0] -= 500.0f * dt;
                if (zoom[0] < ZOOM_MIN) zoom[0] = ZOOM_MIN;
            }
            if ((xCtrlPress(PSP_CTRL_DOWN)) && zoom[0] < ZOOM_MAX)
            {
                zoom[0] += 500.0f * dt;
                if (zoom[0] > ZOOM_MAX) zoom[0] = ZOOM_MAX;
            }
        }
        //else
        else if (Camera == 1)
        {
            if (xCtrlPress(PSP_CTRL_UP))
            {
                if (xCtrlPress(PSP_CTRL_RTRIGGER))
                {
                    if (zoom[1] > ZOOM_THIRD_MIN)
                    {
                        zoom[1] -= 500.0f * dt;
                        if (zoom[1] < ZOOM_THIRD_MIN) zoom[1] = ZOOM_THIRD_MIN;
                    }
                }
                else if (rotCamX > CAM_X_MIN)
                {
                    rotCamX -= dt;
                    if (rotCamX < CAM_X_MIN) rotCamX = CAM_X_MIN;
                }
            }
            if (xCtrlPress(PSP_CTRL_DOWN))
            {
                if (xCtrlPress(PSP_CTRL_RTRIGGER))
                {
                    if (zoom[1] < ZOOM_THIRD_MAX)
                    {
                        zoom[1] += 500.0f * dt;
                        if (zoom[1] > ZOOM_THIRD_MAX) zoom[1] = ZOOM_THIRD_MAX;
                    }
                }
                else if (rotCamX < CAM_X_MAX)
                {
                    rotCamX += dt;
                    if (rotCamX > CAM_X_MAX) rotCamX = CAM_X_MAX;
                }
            }
            if (xCtrlPress(PSP_CTRL_LEFT)) rotCamZ += dt;
            if (xCtrlPress(PSP_CTRL_RIGHT)) rotCamZ -= dt;
        }
        else if (Camera == 2)
        {
            //PlayerAlive = 0;

            if (xCtrlPress(PSP_CTRL_DOWN) && FreeCamSpeed > FREE_CAM_SPEED_MIN) FreeCamSpeed -= FREE_CAM_ACCEL * dt;
            if (xCtrlPress(PSP_CTRL_UP) && FreeCamSpeed < FREE_CAM_SPEED_MAX) FreeCamSpeed += FREE_CAM_ACCEL * dt;
            if (FreeCamSpeed < FREE_CAM_SPEED_MIN) FreeCamSpeed = FREE_CAM_SPEED_MIN;
            if (FreeCamSpeed > FREE_CAM_SPEED_MAX) FreeCamSpeed = FREE_CAM_SPEED_MAX;

            //forward
            if (xCtrlPress(PSP_CTRL_RTRIGGER))
            {
                posFreeCamX += FreeCamSpeed * dt * -x_sinf(rotFreeCamZ) * -x_cosf(rotFreeCamX);
                posFreeCamY += FreeCamSpeed * dt * -x_cosf(rotFreeCamZ) * -x_cosf(rotFreeCamX);
                posFreeCamZ += FreeCamSpeed * dt * /* -x_sinf(rotFreeCamZ) * */ -x_sinf(rotFreeCamX);
            }
            //backward
            if (xCtrlPress(PSP_CTRL_CROSS))
            {
                posFreeCamX -= FreeCamSpeed * dt * -x_sinf(rotFreeCamZ) * -x_cosf(rotFreeCamX);
                posFreeCamY -= FreeCamSpeed * dt * -x_cosf(rotFreeCamZ) * -x_cosf(rotFreeCamX);
                posFreeCamZ -= FreeCamSpeed * dt * /* -x_sinf(rotFreeCamZ) * */ -x_sinf(rotFreeCamX);
            }
            //left
            if (xCtrlPress(PSP_CTRL_SQUARE))
            {
                posFreeCamX += FreeCamSpeed * dt * -x_sinf(rotFreeCamZ + PI_2) /* * -x_cosf(rotFreeCamX) */;
                posFreeCamY += FreeCamSpeed * dt * -x_cosf(rotFreeCamZ + PI_2) /* * -x_cosf(rotFreeCamX) */;
                //posFreeCamZ += FreeCamSpeed * dt * -x_sinf(rotFreeCamZ + PI_2) * -x_sinf(rotFreeCamX);
            }
            //right
            if (xCtrlPress(PSP_CTRL_CIRCLE))
            {
                posFreeCamX += FreeCamSpeed * dt * -x_sinf(rotFreeCamZ - PI_2) /* * -x_cosf(rotFreeCamX) */;
                posFreeCamY += FreeCamSpeed * dt * -x_cosf(rotFreeCamZ - PI_2) /* * -x_cosf(rotFreeCamX) */;
                //posFreeCamZ += FreeCamSpeed * dt * -x_sinf(rotFreeCamZ - PI_2) * -x_sinf(rotFreeCamX);
            }
            //control rotation
            if (x_absf(xCtrlAnalogX()) > (float)cfg_analog_deadzone) rotFreeCamZ += (xCtrlAnalogX()) * 0.01f * dt;
            if (x_absf(xCtrlAnalogY()) > (float)cfg_analog_deadzone) rotFreeCamX += (xCtrlAnalogY()) * 0.01f * dt;
            //if (rotFreeCamX < -(5*PI)/12) rotFreeCamX = -(5*PI)/12;
            if (rotFreeCamX < -PI_2 + 0.1f) rotFreeCamX = -PI_2 + 0.1f;
            //if (rotFreeCamX > (5*PI)/12) rotFreeCamX = (5*PI)/12;
            if (rotFreeCamX > PI_2 - 0.1f) rotFreeCamX = PI_2 - 0.1f;
        }

        if (PlayerAlive && Camera != 2)
        {
            if (xCtrlPress(PSP_CTRL_SQUARE) && !CountAllowCannon && AllowShoot)
            {
                for (int i = 0; i < CANNON_CACHE; i++)
                {
                    if (!ShootingCannon[i])
                    {
                        //WAV_SetPan(CannonSound, 128);
                        //WAV_SetVolume(CannonSound, 255);
                        //WAV_Play(CannonSound);
                        wavPlay_VolPanPitch(CannonSound, cfg_sfx_volume*1.0f, 0.5f, 1.0f);
                        CountAllowCannon = 1;
                        CannonAllowTimer = 0;
                        Heat += 20.0f;
                        if (Heat >= 100)
                        {
                            Heat = 100;
                            AllowShoot = 0;
                        }

                        ShootingCannon[i] = 1;
                        BallHeading[i] = rotPlayer;
                        BallCos[i] = x_cosf(rotPlayer);
                        BallSin[i] = x_sinf(rotPlayer);
                        BallFallSpeed[i] = -2;
                        posBallX[i] = posPlayerX + (22.0f * x_cosf(rotPlayer) );
                        posBallY[i] = posPlayerY + (22.0f * x_sinf(rotPlayer) );
                        posBallZ[i] = 47.0f + PlayerHeight;
                        break;
                    }
                }
            }
            if (xCtrlPress(PSP_CTRL_CROSS) && !CountAllowLaser && AllowShoot)
            {
                for (int i = 0; i < LASER_CACHE; i++)
                {
                    if (!ShootingLaser[i])
                    {
                        //WAV_SetPan(LaserSound, 128);
                        //WAV_SetVolume(LaserSound, 255);
                        //WAV_Play(LaserSound);
                        wavPlay_VolPanPitch(LaserSound, cfg_sfx_volume*1.0f, 0.5f, 1.0f);
                        CountAllowLaser = 1;
                        LaserAllowTimer = 0;
                        Heat += 4.0f;
                        if (Heat >= 100)
                        {
                            Heat = 100;
                            AllowShoot = 0;
                        }

                        ShootingLaser[i] = 1;
                        LaserMoveTimer[i] = 0;
                        LaserHeading[i] = rotPlayer;
                        LaserCos[i] = x_cosf(rotPlayer);
                        LaserSin[i] = x_sinf(rotPlayer);
                        posLaserX[i] = posPlayerX + (22.0f * x_cosf(rotPlayer) );
                        posLaserY[i] = posPlayerY + (22.0f * x_sinf(rotPlayer) );
                        posLaserZ[i] = 47.0f + PlayerHeight;
                        break;
                    }
                }
            }

            posPlayerLastX = posPlayerX;
            posPlayerLastY = posPlayerY;

            if (x_absf(xCtrlAnalogX()) > (float)cfg_analog_deadzone || x_absf(xCtrlAnalogY()) > (float)cfg_analog_deadzone)
            {
                float padDist = x_sqrtf( SQR(xCtrlAnalogX()) + SQR(xCtrlAnalogY()) );
                if (padDist > 128) padDist = 128;
                rotCurrent = x_atan2f(xCtrlAnalogY(), xCtrlAnalogX());
                if (rotCurrent < -PI_2) rotCurrent += 2*PI;
                float tempx = 0;
                float tempy = 0;
                //if (!ThirdPerson)
                if (Camera == 0)
                {
                    tempx = x_cosf(rotCurrent);
                    tempy = x_sinf(rotCurrent);
                }
                //else
                if (Camera == 1)
                {
                    tempx = x_cosf(rotCamZ + rotCurrent);
                    tempy = x_sinf(rotCamZ + rotCurrent);
                }

                if (xCtrlPress(PSP_CTRL_LTRIGGER) && AllowBoost)
                {
                    Boost -= 50.0f * (padDist/128) * dt;
                    if (Boost <= 0)
                    {
                        Boost = 0;
                        AllowBoost = 0;
                    }
                    tempx *= 2;
                    tempy *= 2;

                    boost_glow->Explode(posPlayerX, posPlayerY, PlayerHeight + TANK_LOW + 0.5f*TANK_LOW_SECT_HEIGHT, 3);
                }

                posPlayerX += tempx * padDist * 3.0f * dt;
                camOffsetX -= tempx * padDist * 0.02f;
                posPlayerY += tempy * padDist * 3.0f * dt;
                camOffsetY -= tempy * padDist * 0.02f;

                //collision
                if (posPlayerX != posPlayerLastX || posPlayerY != posPlayerLastY)
                {
                    for (int t = 0; t < MAX_TEAMS; t++)
                    {
                        if (TeamInPlay[t])
                        {
                            for (int i = 0; i < NUM_ENEMIES - (t == PLAYER_TEAM ? 1 : 0); i++)
                            {
                                if (Enemy[t][i].Alive && CircleCollision(posPlayerX, posPlayerY, TANK_RADIUS, Enemy[t][i].posTankX, Enemy[t][i].posTankY, TANK_RADIUS) >= 0)
                                {
                                    //angle from enemy
                                    float temprot = x_angle_to_target(Enemy[t][i].posTankX, Enemy[t][i].posTankY, posPlayerX, posPlayerY);
                                    posPlayerX = Enemy[t][i].posTankX + ( x_cosf(temprot) * 2*TANK_RADIUS);
                                    posPlayerY = Enemy[t][i].posTankY + ( x_sinf(temprot) * 2*TANK_RADIUS);
                                    break;
                                }
                            }
                        }
                    }
                }

                for (int x = 0; x < map.Length(); x++)
                {
                    for (int y = 0; y < map.Height(); y++)
                    {
                        if (map.Feature(x, y) == '1')
                        {
                            if (posPlayerX + TANK_RADIUS > BLOCK_X_LEFT*CELL_LENGTH && posPlayerX - TANK_RADIUS < BLOCK_X_RIGHT*CELL_LENGTH &&
                                posPlayerY + TANK_RADIUS > BLOCK_Y_BOTTOM*CELL_LENGTH && posPlayerY - TANK_RADIUS < BLOCK_Y_TOP*CELL_LENGTH)
                            {
                                float distance = x_sqrtf( SQR( posPlayerX - BLOCK_X_CENTER*CELL_LENGTH ) + SQR( posPlayerY - BLOCK_Y_CENTER*CELL_LENGTH ) );
                                if (distance < SQUARE_RADIUS + TANK_RADIUS)
                                {
                                    float temprot = x_angle_to_target(BLOCK_X_CENTER*CELL_LENGTH, BLOCK_Y_CENTER*CELL_LENGTH, posPlayerX, posPlayerY);
                                    //left
                                    if (temprot > (3*PI)/4 || temprot < -(3*PI)/4) posPlayerX = BLOCK_X_LEFT*CELL_LENGTH - TANK_RADIUS;
                                    //top
                                    if (temprot >= PI/4 && temprot <= (3*PI)/4) posPlayerY = BLOCK_Y_TOP*CELL_LENGTH + TANK_RADIUS;
                                    //right
                                    if (temprot > -PI/4 && temprot < PI/4) posPlayerX = BLOCK_X_RIGHT*CELL_LENGTH + TANK_RADIUS;
                                    //bottom
                                    if (temprot >= -(3*PI)/4 && temprot <= -PI/4) posPlayerY = BLOCK_Y_BOTTOM*CELL_LENGTH - TANK_RADIUS;
                                }
                            }
                        }
                        else if (map.Feature(x, y) == '2')
                        {
                            if (posPlayerX + TANK_RADIUS > BLOCK_SMALL_X_LEFT*CELL_LENGTH && posPlayerX - TANK_RADIUS < BLOCK_SMALL_X_RIGHT*CELL_LENGTH &&
                                posPlayerY + TANK_RADIUS > BLOCK_SMALL_Y_BOTTOM*CELL_LENGTH && posPlayerY - TANK_RADIUS < BLOCK_SMALL_Y_TOP*CELL_LENGTH)
                            {
                                float distance = x_sqrtf( SQR( posPlayerX - BLOCK_X_CENTER*CELL_LENGTH ) + SQR( posPlayerY - BLOCK_Y_CENTER*CELL_LENGTH ) );
                                if (distance < SQUARE_SMALL_RADIUS + TANK_RADIUS)
                                {
                                    float temprot = x_angle_to_target(BLOCK_X_CENTER*CELL_LENGTH, BLOCK_Y_CENTER*CELL_LENGTH, posPlayerX, posPlayerY);
                                    //left
                                    if (temprot > (3*PI)/4 || temprot < -(3*PI)/4) posPlayerX = BLOCK_SMALL_X_LEFT*CELL_LENGTH - TANK_RADIUS;
                                    //top
                                    if (temprot >= PI/4 && temprot <= (3*PI)/4) posPlayerY = BLOCK_SMALL_Y_TOP*CELL_LENGTH + TANK_RADIUS;
                                    //right
                                    if (temprot > -PI/4 && temprot < PI/4) posPlayerX = BLOCK_SMALL_X_RIGHT*CELL_LENGTH + TANK_RADIUS;
                                    //bottom
                                    if (temprot >= -(3*PI)/4 && temprot <= -PI/4) posPlayerY = BLOCK_SMALL_Y_BOTTOM*CELL_LENGTH - TANK_RADIUS;
                                }
                            }
                        }
                        else if (map.Feature(x, y) == '5')
                        {
                            if (posPlayerX + TANK_RADIUS > BLOCK_X_LEFT*CELL_LENGTH && posPlayerX - TANK_RADIUS < BLOCK_X_RIGHT*CELL_LENGTH &&
                                posPlayerY + TANK_RADIUS > BLOCK_Y_BOTTOM*CELL_LENGTH && posPlayerY - TANK_RADIUS < BLOCK_Y_TOP*CELL_LENGTH)
                            {
                                float distance = x_sqrtf( SQR( posPlayerX - BLOCK_X_CENTER*CELL_LENGTH ) + SQR( posPlayerY - BLOCK_Y_CENTER*CELL_LENGTH ) );
                                if (distance < ROUND_BLOCK_RADIUS + TANK_RADIUS)
                                {
                                    float temprot = x_angle_to_target(BLOCK_X_CENTER*CELL_LENGTH, BLOCK_Y_CENTER*CELL_LENGTH, posPlayerX, posPlayerY);
                                    posPlayerX = BLOCK_X_CENTER*CELL_LENGTH + ( x_cosf(temprot) * (ROUND_BLOCK_RADIUS + TANK_RADIUS) );
                                    posPlayerY = BLOCK_Y_CENTER*CELL_LENGTH + ( x_sinf(temprot) * (ROUND_BLOCK_RADIUS + TANK_RADIUS) );
                                }
                            }
                        }
                        else if (map.Feature(x, y) == '6')
                        {
                            if (posPlayerX + TANK_RADIUS > BLOCK_SMALL_X_LEFT*CELL_LENGTH && posPlayerX - TANK_RADIUS < BLOCK_SMALL_X_RIGHT*CELL_LENGTH &&
                                posPlayerY + TANK_RADIUS > BLOCK_SMALL_Y_BOTTOM*CELL_LENGTH && posPlayerY - TANK_RADIUS < BLOCK_SMALL_Y_TOP*CELL_LENGTH)
                            {
                                float distance = x_sqrtf( SQR( posPlayerX - BLOCK_X_CENTER*CELL_LENGTH ) + SQR( posPlayerY - BLOCK_Y_CENTER*CELL_LENGTH ) );
                                if (distance < ROUND_BLOCK_SMALL_RADIUS + TANK_RADIUS)
                                {
                                    float temprot = x_angle_to_target(BLOCK_X_CENTER*CELL_LENGTH, BLOCK_Y_CENTER*CELL_LENGTH, posPlayerX, posPlayerY);
                                    posPlayerX = BLOCK_X_CENTER*CELL_LENGTH + ( x_cosf(temprot) * (ROUND_BLOCK_SMALL_RADIUS + TANK_RADIUS) );
                                    posPlayerY = BLOCK_Y_CENTER*CELL_LENGTH + ( x_sinf(temprot) * (ROUND_BLOCK_SMALL_RADIUS + TANK_RADIUS) );
                                }
                            }
                        }
                    }
                }

                if (posPlayerX - TANK_RADIUS < 0) posPlayerX = TANK_RADIUS;
                if (posPlayerX + TANK_RADIUS > GROUND_LENGTH) posPlayerX = GROUND_LENGTH - TANK_RADIUS;
                if (posPlayerY - TANK_RADIUS < 0) posPlayerY = TANK_RADIUS;
                if (posPlayerY + TANK_RADIUS > GROUND_HEIGHT) posPlayerY = GROUND_HEIGHT - TANK_RADIUS;

                if (!xCtrlPress(PSP_CTRL_RTRIGGER) || (cfg_target_lock && Player_Lock_Team < 0))
                {
                    if (Camera == 0) rotPlayer = rotCurrent;
                    else if (Camera == 1) rotPlayer = rotCamZ + rotCurrent;
                }

                rotCamZ = x_ease_to_angle(rotCamZ, rotPlayer - PI_2, 0.99f, dt);
            }
        }

        posReticleX = posPlayerX + 1200.0f*x_cosf(rotPlayer);
        posReticleY = posPlayerY + 1200.0f*x_sinf(rotPlayer);
        rotReticle += 2.5f * dt;

        if (PlayerAlive) tank_glow->Explode(posPlayerX, posPlayerY, PlayerHeight + TANK_LOW, 1);

        if (cfg_target_lock && PlayerAlive)
        {
            if (Player_Lock_Team < 0)
            {
                if (xCtrlTap(PSP_CTRL_RTRIGGER))
                {
                    //find enemy near reticle, set locked variables to identify him
                    for (int t = 0; t < MAX_TEAMS; t++)
                    {
                        if (TeamInPlay[t] && t != PLAYER_TEAM)
                        {
                            for (int i = 0; i < NUM_ENEMIES; i++)
                            {
                                if (Enemy[t][i].Alive && CircleCollision(posPlayerX, posPlayerY, ENEMY_HOOK, Enemy[t][i].posTankX, Enemy[t][i].posTankY, 0) >= 0)
                                {
                                    float temprot = x_angle_to_target(posPlayerX, posPlayerY, Enemy[t][i].posTankX, Enemy[t][i].posTankY);
                                    if (x_absf(x_angle_diff(temprot, rotPlayer)) < PLAYER_LOCK_ANGLE)
                                    {
                                        Player_Lock_Team = t;
                                        Player_Lock_Member = i;
                                        break;
                                    }
                                }
                            }

                            if (Player_Lock_Team >= 0) break;
                        }
                    }
                }
            }
            if (Player_Lock_Team >= 0 && Player_Lock_Member >= 0)
            {
                float x_cur = Enemy[Player_Lock_Team][Player_Lock_Member].posTankX;
                float x_last = Enemy[Player_Lock_Team][Player_Lock_Member].posTankLastX;
                float y_cur = Enemy[Player_Lock_Team][Player_Lock_Member].posTankY;
                float y_last = Enemy[Player_Lock_Team][Player_Lock_Member].posTankLastY;
                if (xCtrlPress(PSP_CTRL_RTRIGGER))
                {
                    //locked on to enemy, set player rotation to follow him
                    float distance = x_sqrtf(SQR(posPlayerX - x_cur) + SQR(posPlayerY - y_cur));
                    float movementoffset = distance/(2000.0f*dt);
                    rotPlayer = x_angle_to_target(posPlayerX, posPlayerY, x_cur + movementoffset*(x_cur - x_last), y_cur + movementoffset*(y_cur - y_last));
                }

                if (!xCtrlPress(PSP_CTRL_RTRIGGER) || !Enemy[Player_Lock_Team][Player_Lock_Member].Alive || (SQR(posPlayerX - x_cur) + SQR(posPlayerY - y_cur)) > SQR(ENEMY_HOOK))
                {
                    //unlock, reset variables
                    Player_Lock_Team = -1;
                    Player_Lock_Team = -1;
                }
            }
        }

        if (CountAllowLaser)
        {
            LaserAllowTimer += 15.0f * dt;
            if (LaserAllowTimer > 3.0f) CountAllowLaser = 0;
        }

        for (int i = 0; i < LASER_CACHE; i++)
        {
            if (ShootingLaser[i])
            {
                posLaserLastX[i] = posLaserX[i];
                posLaserLastY[i] = posLaserY[i];
                posLaserLastZ[i] = posLaserZ[i];
                LaserMoveTimer[i] += 7.5f * dt;
                posLaserX[i] += LASER_SPEED * LaserCos[i] * 1000.0f * dt;
                posLaserY[i] += LASER_SPEED * LaserSin[i] * 1000.0f * dt;
                laser_part->Explode(posLaserX[i], posLaserY[i], posLaserZ[i], 1);
                laser_part->Explode(posLaserX[i] - 10.0f*LaserCos[i], posLaserY[i] - 10.0f*LaserSin[i], posLaserZ[i], 1);
                laser_part->Explode(posLaserX[i] - 20.0f*LaserCos[i], posLaserY[i] - 20.0f*LaserSin[i], posLaserZ[i], 1);
                if (LaserMoveTimer[i] > 10.0f) ShootingLaser[i] = 0;

                if (posLaserX[i] < 0 || posLaserX[i] > GROUND_LENGTH ||
                    posLaserY[i] < 0 || posLaserY[i] > GROUND_HEIGHT ||
                    !ObjectVisible(posLaserLastX[i], posLaserLastY[i], posLaserX[i], posLaserY[i], 5.0f)) ShootingLaser[i] = 0;
                else
                {
                    for (int t = 0; t < MAX_TEAMS; t++)
                    {
                        if (TeamInPlay[t])
                        {
                            for (int j = 0; j < NUM_ENEMIES - (t == PLAYER_TEAM ? 1 : 0); j++)
                            {
                                if ((Enemy[t][j].posTankX - posLaserX[i])*(Enemy[t][i].posTankX - posLaserLastX[i]) < 0 ||
                                    (Enemy[t][j].posTankY - posLaserY[i])*(Enemy[t][i].posTankY - posLaserLastY[i]) < 0)
                                {
                                    if (InterpolatedTankCollision(t, j, posLaserX[i], posLaserY[i], posLaserZ[i], posLaserLastX[i], posLaserLastY[i], posLaserLastZ[i], 1.0f))
                                    {
                                        ShootingLaser[i] = 0;
                                        Enemy[t][j].Health -= ((t == PLAYER_TEAM) ? (FF_DMG_PERCENT) : (1)) * LASER_DMG;
                                        if (Enemy[t][j].Health <= 0)
                                        {
                                            if (t == PLAYER_TEAM)
                                            {
                                                Score--;
                                                bg3dConsole.Print(0x0000bf, "You killed a teammate with lasers!");
                                            }
                                            else
                                            {
                                                Score++;
                                                bg3dConsole.Print(0xbf0000, "You killed an enemy with lasers!");
                                            }
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if (CountAllowCannon)
        {
            CannonAllowTimer += 15.0f * dt;
            if (CannonAllowTimer > 10.0f) CountAllowCannon = 0;
        }

        for (int i = 0; i < CANNON_CACHE; i++)
        {
            if (ShootingCannon[i])
            {
                posBallLastX[i] = posBallX[i];
                posBallLastY[i] = posBallY[i];
                posBallLastZ[i] = posBallZ[i];
                BallFallSpeed[i] += CANNON_GRAVITY * dt;
                posBallX[i] += BALL_SPEED * BallCos[i] * 1000.0f * dt;
                posBallY[i] += BALL_SPEED * BallSin[i] * 1000.0f * dt;
                posBallZ[i] -= BallFallSpeed[i] * 30.0f * dt;
                cannon_trail->Explode(posBallX[i], posBallY[i], posBallZ[i], 1);
                cannon_trail->Explode(posBallX[i] - 10.0f*BallCos[i], posBallY[i] - 10.0f*BallSin[i], posBallZ[i], 1);

                bool Collision = 0;
                if (posBallZ[i] <= 0 ||
                    posBallX[i] < 0 || posBallX[i] > GROUND_LENGTH ||
                    posBallY[i] < 0 || posBallY[i] > GROUND_HEIGHT ||
                    !ObjectVisible(posBallLastX[i], posBallLastY[i], posBallX[i], posBallY[i], 5.0f)) Collision = 1;
                else
                {
                    for (int t = 0; t < MAX_TEAMS; t++)
                    {
                        if (TeamInPlay[t])
                        {
                            for (int j = 0; j < NUM_ENEMIES - (t == PLAYER_TEAM ? 1 : 0); j++)
                            {
                                if ((Enemy[t][j].posTankX - posBallX[i])*(Enemy[t][i].posTankX - posBallLastX[i]) < 0 ||
                                    (Enemy[t][j].posTankY - posBallY[i])*(Enemy[t][i].posTankY - posBallLastY[i]) < 0)
                                {
                                    if (InterpolatedTankCollision(t, j, posBallX[i], posBallY[i], posBallZ[i], posBallLastX[i], posBallLastY[i], posBallLastZ[i], 1.0f))
                                    {
                                        Collision = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }

                if (Collision)
                {
                    Score += CreateExplosion(posBallX[i], posBallY[i], posBallZ[i], EXPLOSION_RADIUS, 750.0f, PLAYER_TEAM, PLAYER_MEMBER, CANNON_DMG);
                    ShootingCannon[i] = 0;
                }
            }
        }

        for (int i = 0; i < MINE_CACHE; i++)
        {
            if (MinePrimed[i])
            {
                for (int t = 0; t < MAX_TEAMS; t++)
                {
                    if (TeamInPlay[t])
                    {
                        if (t != PLAYER_TEAM)
                        {
                            for (int h = 0; h < NUM_ENEMIES - (t == PLAYER_TEAM ? 1 : 0); h++)
                            {
                                if (Enemy[t][h].Alive && CircleCollision(Enemy[t][h].posTankX, Enemy[t][h].posTankY, TANK_RADIUS, posMineX[i], posMineY[i], MINE_DET_RADIUS) >= 0)
                                {
                                    //detonate!
                                    Score += CreateExplosion(posMineX[i], posMineY[i], 0, MINE_EXPL_RADIUS, 1400.0f, PLAYER_TEAM, PLAYER_MEMBER, MINE_DMG);
                                    MinePrimed[i] = 0;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (PlayerAlive)
        {
            for (int i = 0; i < MAX_TEAMS; i++)
            {
                if (TeamInPlay[i])
                {
                    if (!FlagHeld(i))
                    {
                        if (CircleCollision(posPlayerX, posPlayerY, TANK_RADIUS, posFlagX[i], posFlagY[i], 0) >= 0)
                        {
                            if (i == PLAYER_TEAM)
                            {
                                if (!FlagHome(i))
                                {
                                    Returns += 1;
                                    SpawnFlag(i);
                                    bg3dConsole.Print(0xbf0000, "You returned your flag!");
                                }
                            }
                            else if (HoldingFlag(PLAYER_TEAM, PLAYER_MEMBER) < 0)
                            {
                                GiveFlag(i, PLAYER_TEAM, PLAYER_MEMBER);
                            }
                        }
                    }
                }
            }

            if (HoldingFlag(PLAYER_TEAM, PLAYER_MEMBER) >= 0)
            {
                if (FlagHome(PLAYER_TEAM) && CircleCollision(posPlayerX, posPlayerY, TANK_RADIUS, FlagSpawnX[PLAYER_TEAM], FlagSpawnY[PLAYER_TEAM], 0) >= 0)
                {
                    //flag captured
                    bg3dConsole.Print(0xbf0000, "You captured a flag!");
                    bg3dConsole.Printf(TeamColor[1][PLAYER_TEAM], "%s team captured a flag!", TeamColorName[PLAYER_TEAM]);
                    Caps += 1;
                    SpawnFlag(HoldingFlag(PLAYER_TEAM, PLAYER_MEMBER));
                }
            }
        }

        if (PlayerHealth <= 0)
        {
            if (PlayerAlive)
            {
                CreateExplosion(posPlayerX, posPlayerY, TANK_DOME_CENTER_HEIGHT + PlayerHeight, EXPLOSION_RADIUS, 750.0f, -1, -1, 0);
                PlayerHealth = 0;
                Boost = 0;
                Heat = 0;
                Player_Lock_Team = -1;
                Player_Lock_Member = -1;
                for (int i = 0; i < MINE_CACHE; i++) MineLinked[i] = 0;
                if (HoldingFlag(PLAYER_TEAM, PLAYER_MEMBER) >= 0) DropFlag(HoldingFlag(PLAYER_TEAM, PLAYER_MEMBER));
                Deaths += 1;
                SpawnTimer = 0;
                PlayerAlive = 0;
            }

            SpawnTimer += dt;
            if (SpawnTimer >= 5.0f && xCtrlPress(PSP_CTRL_LTRIGGER)) SpawnPlayer();
        }

        if (Heat > 0) Heat -= 12.5f * dt;
        if (PlayerAlive && Boost < 100) Boost += 7.5f * dt;
        if (Heat < 0) Heat = 0;
        if (Boost > 100) Boost = 100;
        if (!AllowShoot && Heat <= 50) AllowShoot = 1;
        if (!AllowBoost && Boost >= 25) AllowBoost = 1;

        Timer += 10.0f * dt;
        PlayerHeight = 5.0f * x_sinf(Timer) + 10.0f;

        AITimer += 50.0f * dt;
        if (AITimer > 10.0f)
        {
            for (int t = 0; t < MAX_TEAMS; t++)
            {
                if (TeamInPlay[t])
                {
                    for (int i = 0; i < NUM_ENEMIES - (t == PLAYER_TEAM ? 1 : 0); i++)
                    {
                        //manage AI
                        if (Enemy[t][i].Alive)
                        {
                            if (Enemy[t][i].LockedOnTeam < 0) //not locked on
                            {
                                if (PlayerAlive && t != PLAYER_TEAM)
                                {
                                    if (CircleCollision(Enemy[t][i].posTankX, Enemy[t][i].posTankY, ENEMY_HOOK, posPlayerX, posPlayerY, 0) >= 0)
                                    {
                                        if (ObjectVisible(Enemy[t][i].posTankX, Enemy[t][i].posTankY, posPlayerX, posPlayerY, 10.0f))
                                        {
                                            Enemy[t][i].LockedOnTeam = 0;
                                            Enemy[t][i].LockedOnMember = -1;
                                            if (x_randi(1, 1000) < 500) Enemy[t][i].StrafeDir = 0;
                                            else Enemy[t][i].StrafeDir = 1;
                                        }
                                    }
                                }
                                for (int t2 = 0; t2 < MAX_TEAMS; t2++)
                                {
                                    if (TeamInPlay[t2] && t2 != t)
                                    {
                                        for (int j = 0; j < NUM_ENEMIES - (t2 == PLAYER_TEAM ? 1 : 0); j++)
                                        {
                                            if (Enemy[t2][j].Alive)
                                            {
                                                if (CircleCollision(Enemy[t][i].posTankX, Enemy[t][i].posTankY, TANK_RADIUS, Enemy[t2][j].posTankX, Enemy[t2][j].posTankY, ENEMY_HOOK) >= 0)
                                                {
                                                    if (ObjectVisible(Enemy[t][i].posTankX, Enemy[t][i].posTankY, Enemy[t2][j].posTankX, Enemy[t2][j].posTankY, 10.0f))
                                                    {
                                                        Enemy[t][i].LockedOnTeam = t2;
                                                        Enemy[t][i].LockedOnMember = j;
                                                        if (x_randi(1, 1000) < 500) Enemy[t][i].StrafeDir = 0;
                                                        else Enemy[t][i].StrafeDir = 1;
                                                    }

                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else //locked on
                            {
                                if ( (Enemy[t][i].LockedOnMember < 0 && PlayerAlive) || (Enemy[t][i].LockedOnMember >= 0 && Enemy[L_TEAM][L_MEMBER].Alive) )
                                {
                                    if (Enemy[t][i].CannonAllowShoot)
                                    {
                                        for (int j = 0; j < CANNON_CACHE; j++)
                                        {
                                            if (!Enemy[t][i].ShootingCannon[j])
                                            {
                                                Sound_3D(CannonSound, Enemy[t][i].posTankX, Enemy[t][i].posTankY);

                                                //shoot cannon
                                                Enemy[t][i].ShootingCannon[j] = 1;
                                                Enemy[t][i].BallHeading[j] = Enemy[t][i].rotTank;
                                                Enemy[t][i].BallCos[j] = x_cosf(Enemy[t][i].rotTank);
                                                Enemy[t][i].BallSin[j] = x_sinf(Enemy[t][i].rotTank);
                                                Enemy[t][i].BallFallSpeed[j] = -2;
                                                Enemy[t][i].posBallX[j] = Enemy[t][i].posTankX + (22.0f * x_cosf(Enemy[t][i].rotTank) );
                                                Enemy[t][i].posBallY[j] = Enemy[t][i].posTankY + (22.0f * x_sinf(Enemy[t][i].rotTank) );
                                                Enemy[t][i].posBallZ[j] = 47.0f + Enemy[t][i].Height;

                                                Enemy[t][i].CannonAllowShoot = 0;
                                                Enemy[t][i].CannonAllowTimer = 0;
                                                break;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (x_randi(1, 1000) < (int)((difficulty == easy ? 0.50f : (difficulty == medium ? 0.75f : 1.00f) ) * Enemy[t][i].LaserBias))
                                        {
                                            for (int j = 0; j < LASER_CACHE; j++)
                                            {
                                                if (!Enemy[t][i].ShootingLaser[j])
                                                {
                                                    //shoot laser
                                                    Sound_3D(LaserSound, Enemy[t][i].posTankX, Enemy[t][i].posTankY);

                                                    Enemy[t][i].ShootingLaser[j] = 1;
                                                    Enemy[t][i].LaserMoveTimer[j] = 0;
                                                    Enemy[t][i].LaserHeading[j] = Enemy[t][i].rotTank;
                                                    Enemy[t][i].LaserCos[j] = x_cosf(Enemy[t][i].rotTank);
                                                    Enemy[t][i].LaserSin[j] = x_sinf(Enemy[t][i].rotTank);
                                                    Enemy[t][i].posLaserX[j] = Enemy[t][i].posTankX + (22.0f * x_cosf(Enemy[t][i].rotTank) );
                                                    Enemy[t][i].posLaserY[j] = Enemy[t][i].posTankY + (22.0f * x_sinf(Enemy[t][i].rotTank) );
                                                    Enemy[t][i].posLaserZ[j] = 47.0f + Enemy[t][i].Height;
                                                    break;
                                                }
                                            }
                                        }
                                    }

                                    float distance = 0;
                                    if (Enemy[t][i].LockedOnMember < 0)
                                    {
                                        distance = x_sqrtf( SQR(posPlayerX - Enemy[t][i].posTankX) + SQR(posPlayerY - Enemy[t][i].posTankY) );
                                    }
                                    else
                                    {
                                        distance = x_sqrtf( SQR(Enemy[L_TEAM][L_MEMBER].posTankX - Enemy[t][i].posTankX) +
                                                         SQR(Enemy[L_TEAM][L_MEMBER].posTankY - Enemy[t][i].posTankY) );
                                    }

                                    if (distance > ENEMY_RELEASE)
                                    {
                                        Enemy[t][i].LockedOnTeam = -1;
                                        Enemy[t][i].LockedOnMember = 0;

                                        pathStatus[AIPathID(t, i)] = 0;
                                    }
                                }
                                else
                                {
                                    Enemy[t][i].LockedOnTeam = -1;
                                    Enemy[t][i].LockedOnMember = 0;

                                    pathStatus[AIPathID(t, i)] = 0;
                                }

                                if (x_randi(1, 1000) < 25) Enemy[t][i].StrafeDir = !Enemy[t][i].StrafeDir;
                            }
                        }
                    }
                }
            }
            AITimer = 0;
        }

        for (int t = 0; t < MAX_TEAMS; t++)
        {
            if (TeamInPlay[t])
            {
                for (int i = 0; i < NUM_ENEMIES - (t == PLAYER_TEAM ? 1 : 0); i++)
                {
                    if (Enemy[t][i].Alive)
                    {
                        tank_glow->Explode(Enemy[t][i].posTankX, Enemy[t][i].posTankY, Enemy[t][i].Height + TANK_LOW, 1);

                        if (!Enemy[t][i].CannonAllowShoot)
                        {
                            Enemy[t][i].CannonAllowTimer += (difficulty == easy ? 0.25f : (difficulty == medium ? 0.5f : 1.00f) ) * 15.0f * dt;
                            if (Enemy[t][i].CannonAllowTimer >= Enemy[t][i].CannonAggro) Enemy[t][i].CannonAllowShoot = 1;
                        }

                        Enemy[t][i].posTankLastX = Enemy[t][i].posTankX;
                        Enemy[t][i].posTankLastY = Enemy[t][i].posTankY;

                        if (Enemy[t][i].LockedOnTeam < 0) //not locked on
                        {
                            int ID = AIPathID(t, i);

                            /*new Pathfinding:
                                  if near enemy flag and flag is visible, get it.
                                  otherwise find path, if offensebias is towards a flag, head to the SPAWN... not the actual location (unrealistic)
                                  get random coord in next path loc, check if its visible, get new one if it isnt (do..while loop)
                                  */

                            //reimplement OffenseBias?

                            bool busy = 0;
                            for (int j = 0; j < MAX_TEAMS; j++)
                            {
                                if (TeamInPlay[j] && !FlagHeld(j) && ((HoldingFlag(t, i) < 0 && j != t) || (HoldingFlag(t, i) >= 0 && j == t)) &&
                                    CircleCollision(Enemy[t][i].posTankX, Enemy[t][i].posTankY, 0, posFlagX[j], posFlagY[j], ENEMY_FLAG_RADIUS) >= 0 &&
                                    ObjectVisible(Enemy[t][i].posTankX, Enemy[t][i].posTankY, posFlagX[j], posFlagY[j], 10.0f))
                                {
                                    Enemy[t][i].rotTank = x_angle_to_target(Enemy[t][i].posTankX, Enemy[t][i].posTankY, posFlagX[j], posFlagY[j]);
                                    Enemy[t][i].posTankX += x_cosf(Enemy[t][i].rotTank) * 128 * 3 * dt;
                                    Enemy[t][i].posTankY += x_sinf(Enemy[t][i].rotTank) * 128 * 3 * dt;
                                    busy = 1;
                                    pathStatus[ID] = 0;
                                    break;
                                }
                            }

                            if (!busy)
                            {
                                if (HoldingFlag(t, i) >= 0 && FlagHome(t) &&
                                    ObjectVisible(Enemy[t][i].posTankX, Enemy[t][i].posTankY, FlagSpawnX[t], FlagSpawnY[t], 10.0f))
                                {
                                    Enemy[t][i].rotTank = x_angle_to_target(Enemy[t][i].posTankX, Enemy[t][i].posTankY, FlagSpawnX[t], FlagSpawnY[t]);
                                    Enemy[t][i].posTankX += x_cosf(Enemy[t][i].rotTank) * 128 * 3 * dt;
                                    Enemy[t][i].posTankY += x_sinf(Enemy[t][i].rotTank) * 128 * 3 * dt;
                                    busy = 1;
                                    pathStatus[ID] = 0;
                                }
                            }

                            if (!busy)
                            {
                                if (pathStatus[ID] <= 0) //no path found
                                {
                                    if (HoldingFlag(t, i) >= 0 && FlagHome(t))
                                    {
                                        pathStatus[ID] = FindPath(ID, (int)(Enemy[t][i].posTankX/CELL_LENGTH), (int)(Enemy[t][i].posTankY/CELL_LENGTH),
                                                                      (int)(FlagSpawnX[t]/CELL_LENGTH),        (int)(FlagSpawnY[t]/CELL_LENGTH));
                                    }
                                    else
                                    {
                                        int random = x_randi(0, 20);
                                        if (random < MAX_TEAMS && random != t && TeamInPlay[random])
                                        {
                                            pathStatus[ID] = FindPath(ID, (int)(Enemy[t][i].posTankX/CELL_LENGTH), (int)(Enemy[t][i].posTankY/CELL_LENGTH),
                                                                          (int)(FlagSpawnX[random]/CELL_LENGTH),   (int)(FlagSpawnY[random]/CELL_LENGTH));
                                        }
                                        else
                                        {
                                            int x = 0;
                                            int y = 0;
                                            do
                                            {
                                                x = x_randi(0, map.Length() - 1);
                                                y = x_randi(0, map.Height() - 1);
                                            } while(!walkable[x][y]);

                                            pathStatus[ID] = FindPath(ID, (int)(Enemy[t][i].posTankX/CELL_LENGTH), (int)(Enemy[t][i].posTankY/CELL_LENGTH), x, y);
                                        }
                                    }
                                    for (int j = 0; j < 10; j++)
                                    {
                                        Enemy[t][i].NextX = x_randf(PATH_X_LEFT*CELL_LENGTH, PATH_X_RIGHT*CELL_LENGTH);
                                        Enemy[t][i].NextY = x_randf(PATH_Y_BOTTOM*CELL_LENGTH, PATH_Y_TOP*CELL_LENGTH);
                                        if (ObjectVisible(Enemy[t][i].posTankX, Enemy[t][i].posTankY, Enemy[t][i].NextX, Enemy[t][i].NextY, 20.0f))
                                        {
                                            break;
                                        }
                                        if (j == 9) pathStatus[ID] = 0;
                                    }
                                }
                                else
                                {
                                    Enemy[t][i].rotTank = x_angle_to_target(Enemy[t][i].posTankX, Enemy[t][i].posTankY, Enemy[t][i].NextX, Enemy[t][i].NextY);
                                    Enemy[t][i].posTankX += x_cosf(Enemy[t][i].rotTank) * 128 * 3 * dt;
                                    Enemy[t][i].posTankY += x_sinf(Enemy[t][i].rotTank) * 128 * 3 * dt;
                                    if (!ObjectVisible(Enemy[t][i].posTankX, Enemy[t][i].posTankY, Enemy[t][i].NextX, Enemy[t][i].NextY, 20.0f)) pathStatus[ID] = 0;
                                    if (CircleCollision(Enemy[t][i].posTankX, Enemy[t][i].posTankY, TANK_RADIUS, Enemy[t][i].NextX, Enemy[t][i].NextY, TANK_RADIUS) >= 0)
                                    {
                                        UpdatePath(ID);
                                        for (int j = 0; j < 10; j++)
                                        {
                                            Enemy[t][i].NextX = x_randf(PATH_X_LEFT*CELL_LENGTH, PATH_X_RIGHT*CELL_LENGTH);
                                            Enemy[t][i].NextY = x_randf(PATH_Y_BOTTOM*CELL_LENGTH, PATH_Y_TOP*CELL_LENGTH);
                                            if (ObjectVisible(Enemy[t][i].posTankX, Enemy[t][i].posTankY, Enemy[t][i].NextX, Enemy[t][i].NextY, 20.0f))
                                            {
                                                break;
                                            }
                                            if (j == 9) pathStatus[ID] = 0;
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            float x_cur = L_MEMBER < 0 ? posPlayerX : Enemy[L_TEAM][L_MEMBER].posTankX;
                            float x_last = L_MEMBER < 0 ? posPlayerLastX : Enemy[L_TEAM][L_MEMBER].posTankLastX;
                            float y_cur = L_MEMBER < 0 ? posPlayerY : Enemy[L_TEAM][L_MEMBER].posTankY;
                            float y_last = L_MEMBER < 0 ? posPlayerLastY : Enemy[L_TEAM][L_MEMBER].posTankLastY;

                            float distance = x_sqrtf( SQR(x_cur - Enemy[t][i].posTankX) + SQR(y_cur - Enemy[t][i].posTankY) );
                            float movementoffset = distance/(2000.0f*dt);
                            if (difficulty == easy) movementoffset *= 0;
                            else if (difficulty == medium) movementoffset *= 0.5f;
                            else movementoffset *= 1;
                            //angle to player/offset
                            float temprot = x_angle_to_target(Enemy[t][i].posTankX, Enemy[t][i].posTankY, x_cur + movementoffset*(x_cur - x_last), y_cur + movementoffset*(y_cur - y_last));
                            Enemy[t][i].rotTank = temprot;
                            if (Enemy[t][i].StrafeDir) temprot += PI_2;
                            else temprot -= PI_2;
                            //sideways motion
                            Enemy[t][i].posTankX += x_cosf(temprot) * Enemy[t][i].SpeedBias * dt;
                            Enemy[t][i].posTankY += x_sinf(temprot) * Enemy[t][i].SpeedBias * dt;
                            //maintaining a certain distance from enemy
                            if (distance < 500) distance = 500;
                            Enemy[t][i].posTankX += (distance - Enemy[t][i].RadiusBias) * x_cosf(Enemy[t][i].rotTank) * 0.5f * dt;
                            Enemy[t][i].posTankY += (distance - Enemy[t][i].RadiusBias) * x_sinf(Enemy[t][i].rotTank) * 0.5f * dt;
                            if (!ObjectVisible(Enemy[t][i].posTankX, Enemy[t][i].posTankY,
                                 Enemy[t][i].posTankX + 0.25f*CELL_LENGTH*x_cosf(temprot),
                                 Enemy[t][i].posTankY + 0.25f*CELL_LENGTH*x_sinf(temprot), 10.0f))
                            {
                                Enemy[t][i].StrafeDir = !Enemy[t][i].StrafeDir;
                            }
                            if (!ObjectVisible(Enemy[t][i].posTankX, Enemy[t][i].posTankY, x_cur, y_cur, 10.0f))
                            {
                                if (difficulty > easy)
                                {
                                    int ID = AIPathID(t, i);
                                    pathStatus[ID] = FindPath(ID, (int)(Enemy[t][i].posTankX/CELL_LENGTH), (int)(Enemy[t][i].posTankY/CELL_LENGTH),
                                                                  (int)(x_cur/CELL_LENGTH), (int)(y_cur/CELL_LENGTH));
                                }
                                Enemy[t][i].LockedOnTeam = -1;
                                Enemy[t][i].LockedOnMember = 0;
                            }
                        }

                        for (int j = 0; j < MAX_TEAMS; j++)
                        {
                            if (TeamInPlay[j])
                            {
                                if (!FlagHeld(j))
                                {
                                    if (CircleCollision(Enemy[t][i].posTankX, Enemy[t][i].posTankY, TANK_RADIUS, posFlagX[j], posFlagY[j], 0) >= 0)
                                    {
                                        if (j == t)
                                        {
                                            if (!FlagHome(j))
                                            {
                                                Enemy[t][i].Returns += 1;
                                                SpawnFlag(t);
                                            }
                                        }
                                        else if (HoldingFlag(t, i) < 0)
                                        {
                                            GiveFlag(j, t, i);
                                        }
                                    }
                                }
                            }
                        }

                        if (HoldingFlag(t, i) >= 0)
                        {
                            if (FlagHome(t) && CircleCollision(Enemy[t][i].posTankX, Enemy[t][i].posTankY, TANK_RADIUS, FlagSpawnX[t], FlagSpawnY[t], 0) >= 0)
                            {
                                //flag captured
                                bg3dConsole.Printf(TeamColor[1][t], "%s team captured a flag!", TeamColorName[t]);
                                Enemy[t][i].Caps += 1;
                                SpawnFlag(HoldingFlag(t, i));
                            }
                        }

                        if (Enemy[t][i].Health <= 0)
                        {
                            Enemy[t][i].Health = 0;
                            CreateExplosion(Enemy[t][i].posTankX, Enemy[t][i].posTankY, TANK_DOME_CENTER_HEIGHT + Enemy[t][i].Height, EXPLOSION_RADIUS, 750.0f, -1, -1, 0);
                            if (HoldingFlag(t, i) >= 0) DropFlag(HoldingFlag(t, i));
                            Enemy[t][i].Deaths += 1;
                            Enemy[t][i].SpawnTimer = 0;
                            Enemy[t][i].Alive = 0;

                            pathStatus[AIPathID(t, i)] = 0;
                        }


                        //collision
                        if (Enemy[t][i].posTankX != Enemy[t][i].posTankLastX || Enemy[t][i].posTankY != Enemy[t][i].posTankLastY)
                        {
                            if (PlayerAlive)
                            {
                                    if (PlayerAlive && CircleCollision(Enemy[t][i].posTankX, Enemy[t][i].posTankY, TANK_RADIUS, posPlayerX, posPlayerY, TANK_RADIUS) >= 0)
                                    {
                                        //angle from player
                                        float temprot = x_angle_to_target(posPlayerX, posPlayerY, Enemy[t][i].posTankX, Enemy[t][i].posTankY);
                                        Enemy[t][i].posTankX = posPlayerX + ( x_cosf(temprot) * 2*TANK_RADIUS);
                                        Enemy[t][i].posTankY = posPlayerY + ( x_sinf(temprot) * 2*TANK_RADIUS);
                                    }
                            }

                            for (int t2 = 0; t2 < MAX_TEAMS; t2++)
                            {
                                if (TeamInPlay[t2])
                                {
                                    for (int j = 0; j < NUM_ENEMIES - (t2 == PLAYER_TEAM ? 1 : 0); j++)
                                    {
                                        if (t2 != t || j != i)
                                        {
                                            //if (TankCollision(t2, j, Enemy[t][i].posTankX, Enemy[t][i].posTankY, 0, TANK_RADIUS))
                                            if (Enemy[t2][j].Alive &&
                                                CircleCollision(Enemy[t][i].posTankX, Enemy[t][i].posTankY, TANK_RADIUS, Enemy[t2][j].posTankX, Enemy[t2][j].posTankY, TANK_RADIUS) >= 0)
                                            {
                                                //angle from other enemy
                                                float temprot = x_angle_to_target(Enemy[t2][j].posTankX, Enemy[t2][j].posTankY, Enemy[t][i].posTankX, Enemy[t][i].posTankY);
                                                Enemy[t][i].posTankX = Enemy[t2][j].posTankX + ( x_cosf(temprot) * 2*TANK_RADIUS);
                                                Enemy[t][i].posTankY = Enemy[t2][j].posTankY + ( x_sinf(temprot) * 2*TANK_RADIUS);
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        for (int x = 0; x < map.Length(); x++)
                        {
                            for (int y = 0; y < map.Height(); y++)
                            {
                                if (map.Feature(x, y) == '1')
                                {
                                    if (Enemy[t][i].posTankX + TANK_RADIUS > BLOCK_X_LEFT*CELL_LENGTH && Enemy[t][i].posTankX - TANK_RADIUS < BLOCK_X_RIGHT*CELL_LENGTH &&
                                        Enemy[t][i].posTankY + TANK_RADIUS > BLOCK_Y_BOTTOM*CELL_LENGTH && Enemy[t][i].posTankY - TANK_RADIUS < BLOCK_Y_TOP*CELL_LENGTH)
                                    {
                                        float distance = x_sqrtf( SQR( Enemy[t][i].posTankX - BLOCK_X_CENTER*CELL_LENGTH ) + SQR( Enemy[t][i].posTankY - BLOCK_Y_CENTER*CELL_LENGTH ) );
                                        if (distance < SQUARE_RADIUS + TANK_RADIUS)
                                        {
                                            float temprot = x_angle_to_target(BLOCK_X_CENTER*CELL_LENGTH, BLOCK_Y_CENTER*CELL_LENGTH, Enemy[t][i].posTankX, Enemy[t][i].posTankY);
                                            //left
                                            if (temprot > (3*PI)/4 || temprot < -(3*PI)/4) Enemy[t][i].posTankX = BLOCK_X_LEFT*CELL_LENGTH - TANK_RADIUS;
                                            //top
                                            if (temprot >= PI/4 && temprot <= (3*PI)/4) Enemy[t][i].posTankY = BLOCK_Y_TOP*CELL_LENGTH + TANK_RADIUS;
                                            //right
                                            if (temprot > -PI/4 && temprot < PI/4) Enemy[t][i].posTankX = BLOCK_X_RIGHT*CELL_LENGTH + TANK_RADIUS;
                                            //bottom
                                            if (temprot >= -(3*PI)/4 && temprot <= -PI/4) Enemy[t][i].posTankY = BLOCK_Y_BOTTOM*CELL_LENGTH - TANK_RADIUS;
                                        }
                                    }
                                }
                                else if (map.Feature(x, y) == '2')
                                {
                                    if (Enemy[t][i].posTankX + TANK_RADIUS > BLOCK_SMALL_X_LEFT*CELL_LENGTH && Enemy[t][i].posTankX - TANK_RADIUS < BLOCK_SMALL_X_RIGHT*CELL_LENGTH &&
                                        Enemy[t][i].posTankY + TANK_RADIUS > BLOCK_SMALL_Y_BOTTOM*CELL_LENGTH && Enemy[t][i].posTankY - TANK_RADIUS < BLOCK_SMALL_Y_TOP*CELL_LENGTH)
                                    {
                                        float distance = x_sqrtf( SQR( Enemy[t][i].posTankX - BLOCK_X_CENTER*CELL_LENGTH ) + SQR( Enemy[t][i].posTankY - BLOCK_Y_CENTER*CELL_LENGTH ) );
                                        if (distance < SQUARE_SMALL_RADIUS + TANK_RADIUS)
                                        {
                                            float temprot = x_angle_to_target(BLOCK_X_CENTER*CELL_LENGTH, BLOCK_Y_CENTER*CELL_LENGTH, Enemy[t][i].posTankX, Enemy[t][i].posTankY);
                                            //left
                                            if (temprot > (3*PI)/4 || temprot < -(3*PI)/4) Enemy[t][i].posTankX = BLOCK_SMALL_X_LEFT*CELL_LENGTH - TANK_RADIUS;
                                            //top
                                            if (temprot >= PI/4 && temprot <= (3*PI)/4) Enemy[t][i].posTankY = BLOCK_SMALL_Y_TOP*CELL_LENGTH + TANK_RADIUS;
                                            //right
                                            if (temprot > -PI/4 && temprot < PI/4) Enemy[t][i].posTankX = BLOCK_SMALL_X_RIGHT*CELL_LENGTH + TANK_RADIUS;
                                            //bottom
                                            if (temprot >= -(3*PI)/4 && temprot <= -PI/4) Enemy[t][i].posTankY = BLOCK_SMALL_Y_BOTTOM*CELL_LENGTH - TANK_RADIUS;
                                        }
                                    }
                                }
                                else if (map.Feature(x, y) == '5')
                                {
                                    if (Enemy[t][i].posTankX + TANK_RADIUS > BLOCK_X_LEFT*CELL_LENGTH && Enemy[t][i].posTankX - TANK_RADIUS < BLOCK_X_RIGHT*CELL_LENGTH &&
                                        Enemy[t][i].posTankY + TANK_RADIUS > BLOCK_Y_BOTTOM*CELL_LENGTH && Enemy[t][i].posTankY - TANK_RADIUS < BLOCK_Y_TOP*CELL_LENGTH)
                                    {
                                        float distance = x_sqrtf( SQR( Enemy[t][i].posTankX - BLOCK_X_CENTER*CELL_LENGTH ) + SQR( Enemy[t][i].posTankY - BLOCK_Y_CENTER*CELL_LENGTH ) );
                                        if (distance < ROUND_BLOCK_RADIUS + TANK_RADIUS)
                                        {
                                            float temprot = x_angle_to_target(BLOCK_X_CENTER*CELL_LENGTH, BLOCK_Y_CENTER*CELL_LENGTH, Enemy[t][i].posTankX, Enemy[t][i].posTankY);
                                            Enemy[t][i].posTankX = BLOCK_X_CENTER*CELL_LENGTH + ( x_cosf(temprot) * (ROUND_BLOCK_RADIUS + TANK_RADIUS) );
                                            Enemy[t][i].posTankY = BLOCK_Y_CENTER*CELL_LENGTH + ( x_sinf(temprot) * (ROUND_BLOCK_RADIUS + TANK_RADIUS) );
                                        }
                                    }
                                }
                                else if (map.Feature(x, y) == '6')
                                {
                                    if (Enemy[t][i].posTankX + TANK_RADIUS > BLOCK_SMALL_X_LEFT*CELL_LENGTH && Enemy[t][i].posTankX - TANK_RADIUS < BLOCK_SMALL_X_RIGHT*CELL_LENGTH &&
                                        Enemy[t][i].posTankY + TANK_RADIUS > BLOCK_SMALL_Y_BOTTOM*CELL_LENGTH && Enemy[t][i].posTankY - TANK_RADIUS < BLOCK_SMALL_Y_TOP*CELL_LENGTH)
                                    {
                                        float distance = x_sqrtf( SQR( Enemy[t][i].posTankX - BLOCK_X_CENTER*CELL_LENGTH ) + SQR( Enemy[t][i].posTankY - BLOCK_Y_CENTER*CELL_LENGTH ) );
                                        if (distance < ROUND_BLOCK_SMALL_RADIUS + TANK_RADIUS)
                                        {
                                            float temprot = x_angle_to_target(BLOCK_X_CENTER*CELL_LENGTH, BLOCK_Y_CENTER*CELL_LENGTH, Enemy[t][i].posTankX, Enemy[t][i].posTankY);
                                            Enemy[t][i].posTankX = BLOCK_X_CENTER*CELL_LENGTH + ( x_cosf(temprot) * (ROUND_BLOCK_SMALL_RADIUS + TANK_RADIUS) );
                                            Enemy[t][i].posTankY = BLOCK_Y_CENTER*CELL_LENGTH + ( x_sinf(temprot) * (ROUND_BLOCK_SMALL_RADIUS + TANK_RADIUS) );
                                        }
                                    }
                                }
                            }
                        }

                        if (Enemy[t][i].posTankX - TANK_RADIUS < 0) Enemy[t][i].posTankX = TANK_RADIUS;
                        if (Enemy[t][i].posTankX + TANK_RADIUS > GROUND_LENGTH) Enemy[t][i].posTankX = GROUND_LENGTH - TANK_RADIUS;
                        if (Enemy[t][i].posTankY - TANK_RADIUS < 0) Enemy[t][i].posTankY = TANK_RADIUS;
                        if (Enemy[t][i].posTankY + TANK_RADIUS > GROUND_HEIGHT) Enemy[t][i].posTankY = GROUND_HEIGHT - TANK_RADIUS;

                        if (MapCollision(Enemy[t][i].posTankX, Enemy[t][i].posTankY, 0)) Enemy[t][i].Health = 0;


                        Enemy[t][i].Height = 5.0f*x_sinf(Timer+Enemy[t][i].HoverOffset) + 10.0f;
                    }
                    else
                    {
                        Enemy[t][i].SpawnTimer += dt;
                        if (Enemy[t][i].SpawnTimer > 5.0f) Enemy[t][i].Spawn();
                    }

                    //handle actions
                    for (int j = 0; j < LASER_CACHE; j++)
                    {
                        if (Enemy[t][i].ShootingLaser[j])
                        {
                            Enemy[t][i].posLaserLastX[j] = Enemy[t][i].posLaserX[j];
                            Enemy[t][i].posLaserLastY[j] = Enemy[t][i].posLaserY[j];
                            Enemy[t][i].posLaserLastZ[j] = Enemy[t][i].posLaserZ[j];
                            Enemy[t][i].LaserMoveTimer[j] += 7.5f * dt;
                            Enemy[t][i].posLaserX[j] += LASER_SPEED * Enemy[t][i].LaserCos[j] * 1000.0f * dt;
                            Enemy[t][i].posLaserY[j] += LASER_SPEED * Enemy[t][i].LaserSin[j] * 1000.0f * dt;
                            laser_part->Explode(Enemy[t][i].posLaserX[j], Enemy[t][i].posLaserY[j], Enemy[t][i].posLaserZ[j], 1);
                            laser_part->Explode(Enemy[t][i].posLaserX[j] - 10.0f*Enemy[t][i].LaserCos[j], Enemy[t][i].posLaserY[j] - 10.0f*Enemy[t][i].LaserSin[j], Enemy[t][i].posLaserZ[j], 1);
                            laser_part->Explode(Enemy[t][i].posLaserX[j] - 20.0f*Enemy[t][i].LaserCos[j], Enemy[t][i].posLaserY[j] - 20.0f*Enemy[t][i].LaserSin[j], Enemy[t][i].posLaserZ[j], 1);
                            if (Enemy[t][i].LaserMoveTimer[j] > 10.0f) Enemy[t][i].ShootingLaser[j] = 0;

                            if (Enemy[t][i].posLaserX[j] < 0 || Enemy[t][i].posLaserX[j] > GROUND_LENGTH ||
                                Enemy[t][i].posLaserY[j] < 0 || Enemy[t][i].posLaserY[j] > GROUND_HEIGHT ||
                                !ObjectVisible(Enemy[t][i].posLaserLastX[j], Enemy[t][i].posLaserLastY[j], Enemy[t][i].posLaserX[j], Enemy[t][i].posLaserY[j], 5.0f))
                            {
                                Enemy[t][i].ShootingLaser[j] = 0;
                            }
                            else if ((posPlayerX - Enemy[t][i].posLaserX[j])*(posPlayerX - Enemy[t][i].posLaserLastX[j]) < 0 ||
                                     (posPlayerY - Enemy[t][i].posLaserY[j])*(posPlayerY - Enemy[t][i].posLaserLastY[j]) < 0)
                            {
                                if (InterpolatedTankCollision(PLAYER_TEAM, PLAYER_MEMBER, Enemy[t][i].posLaserX[j], Enemy[t][i].posLaserY[j], Enemy[t][i].posLaserZ[j],
                                                                                          Enemy[t][i].posLaserLastX[j], Enemy[t][i].posLaserLastY[j], Enemy[t][i].posLaserLastZ[j], 1.0f))
                                {
                                    Enemy[t][i].ShootingLaser[j] = 0;
                                    PlayerHealth -= ((PLAYER_TEAM == t) ? (FF_DMG_PERCENT) : (1)) * LASER_DMG;
                                    if (PlayerHealth <= 0)
                                    {
                                        if (PLAYER_TEAM == t) Enemy[t][i].Score--;
                                        else Enemy[t][i].Score++;
                                        bg3dConsole.Print(0x0000bf, "An enemy killed you with lasers!");
                                    }
                                }
                            }
                            else
                            {
                                for (int t2 = 0; t2 < MAX_TEAMS; t2++)
                                {
                                    if (TeamInPlay[t2])
                                    {
                                        for (int k = 0; k < NUM_ENEMIES - (t2 == PLAYER_TEAM ? 1 : 0); k++)
                                        {
                                            if (t2 != t || k != i)
                                            {
                                                if ((Enemy[t2][k].posTankX - Enemy[t][i].posLaserX[j])*(Enemy[t2][j].posTankX - Enemy[t][i].posLaserLastX[j]) < 0 ||
                                                    (Enemy[t2][k].posTankY - Enemy[t][i].posLaserY[j])*(Enemy[t2][j].posTankY - Enemy[t][i].posLaserLastY[j]) < 0)
                                                {
                                                    if (InterpolatedTankCollision(t2, k, Enemy[t][i].posLaserX[j], Enemy[t][i].posLaserY[j], Enemy[t][i].posLaserZ[j],
                                                                                         Enemy[t][i].posLaserLastX[j], Enemy[t][i].posLaserLastY[j], Enemy[t][i].posLaserLastZ[j], 1.0f))
                                                    {
                                                        Enemy[t][i].ShootingLaser[j] = 0;
                                                        Enemy[t2][k].Health -= ((t2 == t) ? (FF_DMG_PERCENT) : (1)) * LASER_DMG;
                                                        if (Enemy[t2][k].Health <= 0)
                                                        {
                                                            if (t2 == t) Enemy[t][i].Score--;
                                                            else Enemy[t][i].Score++;
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    for (int j = 0; j < CANNON_CACHE; j++)
                    {
                        if (Enemy[t][i].ShootingCannon[j])
                        {
                            Enemy[t][i].posBallLastX[j] = Enemy[t][i].posBallX[j];
                            Enemy[t][i].posBallLastY[j] = Enemy[t][i].posBallY[j];
                            Enemy[t][i].posBallLastZ[j] = Enemy[t][i].posBallZ[j];
                            Enemy[t][i].BallFallSpeed[j] += CANNON_GRAVITY * dt;
                            Enemy[t][i].posBallX[j] += BALL_SPEED * Enemy[t][i].BallCos[j] * 1000.0f * dt;
                            Enemy[t][i].posBallY[j] += BALL_SPEED * Enemy[t][i].BallSin[j] * 1000.0f * dt;
                            Enemy[t][i].posBallZ[j] -= Enemy[t][i].BallFallSpeed[j] * 30.0f * dt;
                            cannon_trail->Explode(Enemy[t][i].posBallX[j], Enemy[t][i].posBallY[j], Enemy[t][i].posBallZ[j], 1);
                            cannon_trail->Explode(Enemy[t][i].posBallX[j] - 10.0f*Enemy[t][i].BallCos[j], Enemy[t][i].posBallY[j] - 10.0f*Enemy[t][i].BallSin[j], Enemy[t][i].posBallZ[j], 1);

                            bool Collision = 0;
                            if (Enemy[t][i].posBallZ[j] <= 0 ||
                                Enemy[t][i].posBallX[j] < 0 || Enemy[t][i].posBallX[j] > GROUND_LENGTH ||
                                Enemy[t][i].posBallY[j] < 0 || Enemy[t][i].posBallY[j] > GROUND_HEIGHT ||
                                !ObjectVisible(Enemy[t][i].posBallLastX[j], Enemy[t][i].posBallLastY[j], Enemy[t][i].posBallX[j], Enemy[t][i].posBallY[j], 5.0f) ||
                             (((posPlayerX - Enemy[t][i].posBallX[j])*(posPlayerX - Enemy[t][i].posBallLastX[j]) < 0 ||
                               (posPlayerY - Enemy[t][i].posBallY[j])*(posPlayerY - Enemy[t][i].posBallLastY[j]) < 0) &&
                                InterpolatedTankCollision(PLAYER_TEAM, PLAYER_MEMBER, Enemy[t][i].posBallX[j], Enemy[t][i].posBallY[j], Enemy[t][i].posBallZ[j],
                                                                                      Enemy[t][i].posBallLastX[j], Enemy[t][i].posBallLastY[j], Enemy[t][i].posBallLastZ[j], 1.0f)))
                            {
                                Collision = 1;
                            }
                            else
                            {
                                for (int t2 = 0; t2 < MAX_TEAMS; t2++)
                                {
                                    if (TeamInPlay[t2])
                                    {
                                        for (int k = 0; k < NUM_ENEMIES - (t2 == PLAYER_TEAM ? 1 : 0); k++)
                                        {
                                            if (t2 != t || k != i)
                                            {
                                                if ((Enemy[t2][k].posTankX - Enemy[t][i].posBallX[j])*(Enemy[t2][j].posTankX - Enemy[t][i].posBallLastX[j]) < 0 ||
                                                    (Enemy[t2][k].posTankY - Enemy[t][i].posBallY[j])*(Enemy[t2][j].posTankY - Enemy[t][i].posBallLastY[j]) < 0)
                                                {
                                                    if (InterpolatedTankCollision(t2, k, Enemy[t][i].posBallX[j], Enemy[t][i].posBallY[j], Enemy[t][i].posBallZ[j],
                                                                                         Enemy[t][i].posBallLastX[j], Enemy[t][i].posBallLastY[j], Enemy[t][i].posBallLastZ[j], 1.0f))
                                                    {
                                                        Collision = 1;
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            if (Collision)
                            {
                                Enemy[t][i].Score += CreateExplosion(Enemy[t][i].posBallX[j], Enemy[t][i].posBallY[j], Enemy[t][i].posBallZ[j], EXPLOSION_RADIUS, 750.0f, t, i, CANNON_DMG);
                                Enemy[t][i].ShootingCannon[j] = 0;
                            }
                        }
                    }
                }
            }
        }

        camOffsetX = x_ease_to_target(camOffsetX, 0.0f, 1.5f, dt);
        camOffsetY = x_ease_to_target(camOffsetY, 0.0f, 1.5f, dt);

        UpdateFlags();

        explosion1->UpdateSystem(dt);
        explosion2->UpdateSystem(dt);
        explosion_smoke->UpdateSystem(dt);
        boost_glow->UpdateSystem(dt);
        tank_glow->UpdateSystem(dt);
        laser_part->UpdateSystem(dt);
        cannon_trail->UpdateSystem(dt);
        for (int i = 0; i < MAX_TEAMS; i++)
        {
            if (TeamInPlay[i])
            {
                flag_smoke[i]->Explode(posFlagX[i], posFlagY[i], 15.0f, 1);
                flag_smoke[i]->Explode(FlagSpawnX[i], FlagSpawnY[i], 0.0f, 1);
                flag_smoke[i]->UpdateSystem(dt);
            }
        }

        bg3dConsole.UpdateConsole(dt);

        xGuFrameStart();
        DrawGame();
        if (Camera != 2) DrawHUD();
        if (!PlayerAlive)
        {
            if (SpawnTimer <= 5.0f) sprintf(buffer, "Spawn in %i.", (int)(5.0f - SpawnTimer) + 1);
            else sprintf(buffer, "Press L to spawn.");
            xText2DPrintf(&font, 240, 5, 0xffffffff, 0, 1.0f, 1, 1, buffer);
        }
        if (cfg_show_fps)
        {
            xText2DPrintf(&font, 1, 258, 0xFFFFFFFF, 0, 1.0f, 1, 0, "FPS: %f", xLibDtFps(dt));
        }
        if (xCtrlPress(PSP_CTRL_SELECT)) DisplayScores(120, 20);
        bg3dConsole.RenderConsole(&font, 5, 256 - 5*LINE_HEIGHT, 0, 5*LINE_HEIGHT, LINE_HEIGHT, 1);
        xGuFrameEnd();
        xGuSwapBuffers(0);
    }
}

void DrawGame( void )
{
    if (Camera == 0)
    {
        cam.x = posPlayerX + camOffsetX; cam.y = posPlayerY + camOffsetY; cam.z = zoom[0];
        xGumSetCameraPos(cam.x, cam.y, cam.z);
    }
    else if (Camera == 1)
    {
        sceGumMatrixMode(GU_VIEW);
        sceGumLoadIdentity();
        cam.x = posPlayerX + ( zoom[1] * x_sinf(rotCamZ) * x_cosf(rotCamX) );
        cam.y = posPlayerY - ( zoom[1] * x_cosf(rotCamZ) * x_cosf(rotCamX) );
        cam.z = zoom[1] * x_sinf(rotCamX);
        ScePspFVector3 center = {posPlayerX, posPlayerY, 0.0f};
        ScePspFVector3 up = {0.0f, 0.0f, 1.0f};
        sceGumLookAt(&cam, &center, &up);
        sceGumMatrixMode(GU_MODEL);
    }
    else if (Camera == 2)
    {
        sceGumMatrixMode(GU_VIEW);
        sceGumLoadIdentity();
        cam.x = posFreeCamX; cam.y = posFreeCamY; cam.z = posFreeCamZ;
        ScePspFVector3 center = {posFreeCamX + ( -x_sinf(rotFreeCamZ) * -x_cosf(rotFreeCamX) ),
                                 posFreeCamY + ( -x_cosf(rotFreeCamZ) * -x_cosf(rotFreeCamX) ),
                                 posFreeCamZ + ( -x_sinf(rotFreeCamX) )};
        ScePspFVector3 up = {0.0f, 0.0f, 1.0f};
        sceGumLookAt(&cam, &center, &up);
        sceGumMatrixMode(GU_MODEL);
    }

    xGuBlendDefault();

    xDrawSkybox(&sky_tex_left, &sky_tex_right, &sky_tex_back, &sky_tex_front, &sky_tex_bottom, 0,
                1, SKYBOX_SUBDIV, -SKYBOX_OFFSET, -SKYBOX_OFFSET, -0.5f*SKYBOX_HEIGHT, SKYBOX_LENGTH, SKYBOX_LENGTH, SKYBOX_HEIGHT);

    sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);

    for (int x = 0; x < map.Length(); x++)
    {
        for (int y = 0; y < map.Height(); y++)
        {
            if (map.Feature(x, y) == '1')
            {
                xGumSetPos(x*CELL_LENGTH + cellPos.x, y*CELL_LENGTH + cellPos.y, cellPos.z);
                SetCellTex();
                SetMipmapFilter();
                sceGuEnable(GU_TEXTURE_2D);
                sceGuColor(0xffffffff);
                xGumCallList(cellList);
                sceGuDisable(GU_TEXTURE_2D);
            }
            else
            {
                if (map.Feature(x, y) == '2')
                {
                    xGumSetPos(x*CELL_LENGTH + cellPos.x, y*CELL_LENGTH + cellPos.y, cellPos.z);
                    SetCellTex();
                    SetMipmapFilter();
                    xGumScaleMulti(0.5f, 0.5f, 1.0f);
                    sceGuEnable(GU_TEXTURE_2D);
                    sceGuColor(0xffffffff);
                    xGumCallList(cellList);
                    sceGuDisable(GU_TEXTURE_2D);
                }
                else if (map.Feature(x, y) == '5')
                {
                    xGumSetPos(x*CELL_LENGTH + cellPos.x, y*CELL_LENGTH + cellPos.y, cellPos.z);
                    xGumCallList(roundcellList);
                }
                else if (map.Feature(x, y) == '6')
                {
                    xGumSetPos(x*CELL_LENGTH + cellPos.x, y*CELL_LENGTH + cellPos.y, cellPos.z);
                    xGumScaleMulti(0.5f, 0.5f, 1.0f);
                    xGumCallList(roundcellList);
                }
                xGumSetPos(x*CELL_LENGTH, y*CELL_LENGTH, 0);
                SetGroundTex();
                SetMipmapFilter();
                sceGuEnable(GU_TEXTURE_2D);
                sceGuColor(0xffffffff);
                xGumCallList(groundList);
                sceGuDisable(GU_TEXTURE_2D);
            }
        }
    }

    for (int x = -1; x < map.Length() + 1; x++)
    {
        SetCellTex();
        SetMipmapFilter();
        sceGuEnable(GU_TEXTURE_2D);
        sceGuColor(0xffffffff);
        xGumSetPos((x+0.5f)*CELL_LENGTH, -CELL_LENGTH*0.5f, 0.0f);
        xGumCallList(cellList);
        xGumSetPos((x+0.5f)*CELL_LENGTH, GROUND_HEIGHT + 0.5f*CELL_LENGTH, 0.0f);
        xGumCallList(cellList);
        sceGuDisable(GU_TEXTURE_2D);
    }

    for (int y = 0; y < map.Height(); y++)
    {
        SetCellTex();
        SetMipmapFilter();
        sceGuEnable(GU_TEXTURE_2D);
        sceGuColor(0xffffffff);
        xGumSetPos(-CELL_LENGTH*0.5f, (y+0.5f)*CELL_LENGTH, 0.0f);
        xGumCallList(cellList);
        xGumSetPos(GROUND_LENGTH + 0.5f*CELL_LENGTH, (y+0.5f)*CELL_LENGTH, 0.0f);
        xGumCallList(cellList);
        sceGuDisable(GU_TEXTURE_2D);
    }

    if (PlayerAlive)
    {
        xGumSetPos(posPlayerX, posPlayerY, PlayerHeight);
        sceGumRotateZ(rotPlayer);

        sceGuColor(TeamColor[0][PLAYER_TEAM]);
        xGumCallList(tankList);
    }

    if (PlayerAlive)
    {
        sceGuEnable(GU_BLEND);

        xGumSetPos(posReticleX, posReticleY, 0.0f);
        sceGumRotateZ(rotReticle);
        xGumCallList(reticleList);

        xGumSetPos(posPlayerX, posPlayerY, 0.0f);
        sceGumRotateZ(rotPlayer);
        xGumCallList(spatialretList);

        sceGuDisable(GU_BLEND);
    }

    for (int i = 0; i < MINE_CACHE; i++)
    {
        if (MinePrimed[i])
        {
            xGumSetPos(posMineX[i], posMineY[i], 0);
            xGumCallList(mineList);
        }
    }

    for (int t = 0; t < MAX_TEAMS; t++)
    {
        if (TeamInPlay[t])
        {
            xGumSetPos(posFlagX[t], posFlagY[t], posFlagZ[t]);
            sceGumRotateZ(rotFlag[t]);
            sceGuColor(TeamColor[0][t]);
            xGumCallList(flagList);

            for (int i = 0; i < NUM_ENEMIES - (t == PLAYER_TEAM ? 1 : 0); i++)
            {
                if (Enemy[t][i].Alive)
                {
                    xGumSetPos(Enemy[t][i].posTankX, Enemy[t][i].posTankY, Enemy[t][i].Height);
                    sceGumRotateZ(Enemy[t][i].rotTank);

                    xGumFrustumCullStart(-TANK_RADIUS, -TANK_RADIUS, TANK_LOW, TANK_RADIUS, TANK_RADIUS, TANK_LOW + TANK_HEIGHT);
                    sceGuColor(TeamColor[0][t]);
                    xGumCallList(tankList);
                    xGumFrustumCullEnd();

                    if (cfg_show_health)
                    {
                        if (Camera == 0) sceGuDisable(GU_DEPTH_TEST);
                        xDraw3DRect(Enemy[t][i].posTankX, Enemy[t][i].posTankY + (Camera == 0 ? 75.0f : 0.0f), (Camera == 0 ? 25.0f : 100.0f), 100.0f, 15.0f, 0x507F7F7F);
                        xDraw3DRect(Enemy[t][i].posTankX, Enemy[t][i].posTankY + (Camera == 0 ? 75.0f : 0.0f), (Camera == 0 ? 25.0f : 100.0f), Enemy[t][i].Health, 15.0f, 0x7F0000FF);
                        if (Camera == 0) sceGuEnable(GU_DEPTH_TEST);
                    }
                }
            }
        }
    }

    if (cfg_target_lock && Player_Lock_Team >= 0 && Player_Lock_Member >= 0)
    {
        float x = Enemy[Player_Lock_Team][Player_Lock_Member].posTankX;
        float y = Enemy[Player_Lock_Team][Player_Lock_Member].posTankY;
        xDraw3DRect(x, y, 50.0f, 100.0f, 100.0f, 0x3f0000ff);
    }

    //since they dont write to Z buffer, need to sort them accordingly. first is in the back.
    tank_glow->RenderSystem(&part_tex, 25.0f, GU_RGBA(0,255,230,0), 0);
    for (int i = 0; i < MAX_TEAMS; i++) flag_smoke[i]->RenderSystem(&smoke_tex, 75.0f, TeamColor[0][i], 0);
    explosion_smoke->RenderSystem(&smoke_tex, 100.0f, GU_RGBA(40,40,40,0), 0);
    explosion1->RenderSystem(&smoke_tex, 100.0f, GU_RGBA(255,150,0,0), 0);
    explosion2->RenderSystem(&smoke_tex, 100.0f, GU_RGBA(255,255,0,0), 0);
    boost_glow->RenderSystem(&part_tex, 40.0f, GU_RGBA(0,255,255,0), 0);
    laser_part->RenderSystem(&part_tex, 25.0f, GU_RGBA(0,255,100,0), 0);
    cannon_trail->RenderSystem(&smoke_tex, 25.0f, GU_RGBA(30,30,30,0), 0);
}

void DrawHUD( void )
{
    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
    sceGuDisable(GU_DEPTH_TEST);
    sceGuEnable(GU_BLEND);

    xDrawRectSolid(4, 4, 102, 7, GU_COLOR(0.5f, 0.5f, 0.5f, 0.3f));
    xDrawRectSolid(5, 5, 100, 5, GU_COLOR(0.6f, 0.6f, 0.6f, 0.4f));
    xDrawRectSolid(5, 5, (int)PlayerHealth, 1, GU_COLOR(1.0f, 0.0f, 0.0f, 0.5f));
    xDrawRectSolid(5, 6, (int)PlayerHealth, 1, GU_COLOR(0.9f, 0.0f, 0.0f, 0.5f));
    xDrawRectSolid(5, 7, (int)PlayerHealth, 1, GU_COLOR(0.8f, 0.0f, 0.0f, 0.5f));
    xDrawRectSolid(5, 8, (int)PlayerHealth, 1, GU_COLOR(0.9f, 0.0f, 0.0f, 0.5f));
    xDrawRectSolid(5, 9, (int)PlayerHealth, 1, GU_COLOR(1.0f, 0.0f, 0.0f, 0.5f));
    xDrawRectSolid(4, 15, 102, 7, GU_COLOR(0.5f, 0.5f, 0.5f, 0.3f));
    xDrawRectSolid(5, 16, 100, 5, GU_COLOR(0.6f, 0.6f, 0.6f, 0.4f));
    xDrawRectSolid(5, 16, (int)Boost, 1, GU_COLOR(0.0f, 0.94f, 1.00f, 0.5f));
    xDrawRectSolid(5, 17, (int)Boost, 1, GU_COLOR(0.0f, 0.86f, 0.94f, 0.5f));
    xDrawRectSolid(5, 18, (int)Boost, 1, GU_COLOR(0.0f, 0.82f, 0.82f, 0.5f));
    xDrawRectSolid(5, 19, (int)Boost, 1, GU_COLOR(0.0f, 0.86f, 0.94f, 0.5f));
    xDrawRectSolid(5, 20, (int)Boost, 1, GU_COLOR(0.0f, 0.94f, 1.00f, 0.5f));
    xDrawRectSolid(4, 26, 102, 7, GU_COLOR(0.5f, 0.5f, 0.5f, 0.3f));
    xDrawRectSolid(5, 27, 100, 5, GU_COLOR(0.6f, 0.6f, 0.6f, 0.4f));
    xDrawRectSides(5, 27, (int)Heat, 5, GU_COLOR(0.0f, 0.0f, 1.0f, 0.5f), GU_COLOR(Heat/100.0f, 0.0f, 1.0f - (Heat/100.0f), 0.5f));

    sceGuDrawArray(GU_TRIANGLE_FAN, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 26, 0, radar1);
    sceGuDrawArray(GU_TRIANGLE_FAN, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 26, 0, radar2);
    sceGuDrawArray(GU_LINES, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 4, 0, radarlines);

    for (int t = 0; t < MAX_TEAMS; t++)
    {
        if (TeamInPlay[t])
        {
            for (int i = 0; i < NUM_ENEMIES - (t == PLAYER_TEAM ? 1 : 0); i++)
            {
                if (Enemy[t][i].Alive)
                {
                    float distance = 0;
                    if ((distance = CircleCollision(posPlayerX, posPlayerY, RADAR_REAL_RADIUS, Enemy[t][i].posTankX, Enemy[t][i].posTankY, 0)) >= 0)
                    {
                        float x = 0;
                        float y = 0;
                        if (Camera == 0)
                        {
                            x = ((Enemy[t][i].posTankX - posPlayerX)/RADAR_REAL_RADIUS) * RADAR_SCREEN_RADIUS + RADAR_CENTER_X;
                            y = ((posPlayerY - Enemy[t][i].posTankY)/RADAR_REAL_RADIUS) * RADAR_SCREEN_RADIUS + RADAR_CENTER_Y;
                        }
                        else
                        {
                            float angletotarget = x_angle_to_target(posPlayerX, posPlayerY, Enemy[t][i].posTankX, Enemy[t][i].posTankY);
                            x = ((x_cosf(angletotarget - rotCamZ)*distance)/RADAR_REAL_RADIUS) * RADAR_SCREEN_RADIUS + RADAR_CENTER_X;
                            y = ((-x_sinf(angletotarget - rotCamZ)*distance)/RADAR_REAL_RADIUS) * RADAR_SCREEN_RADIUS + RADAR_CENTER_Y;
                        }
                        xDrawPixel((int)x, (int)y, TeamColor[1][t]);
                    }
                }
            }
        }
    }

    sceGuDisable(GU_BLEND);
    sceGuEnable(GU_DEPTH_TEST);
}
