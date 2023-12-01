#ifndef MAIN_H
#define MAIN_H

#define SKY_FRONT 0
#define SKY_RIGHT 1
#define SKY_LEFT 2
#define SKY_BACK 3
#define SKY_TOP 4
#define FIELD 5
#define MAZE_WALL 6
#define REEL_STEEL 7
#define BODY 8
#define SKIN 9
#define HAIR 10
#define LEAF 11
#define WOOD 12
#define FIRE 13
#define WALL 14
#define STAR 15
#define WOODEN 16
#define HUT 17

#define PI 3.14159265

#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include <iostream>
#include <sstream>
#include<bits/stdc++.h>
#include <unistd.h>
#include<MMSystem.h>
#include<time.h>
#include "G:\4.2\graphics\Project\step2\include\BmpLoader.h"
#include "reel.h"
#include "scene.h"
#include "maze.h"
#include "display.h"
#include "curve_obj.h"
#include "level.h"

using namespace std;

void properties(float, float, float, bool, float);
void draw_cube(float, float, float,
          bool, float);
void LoadTexture(const char*);

extern unsigned int textureID[100];
extern float player_z,player2_z;
extern float player_x,player2_x;
extern float player_y,player2_y;
extern GLfloat rotat, rotatstar;
//extern GLfloat rot;
extern GLfloat rotat_scene;
extern int whichBall;
extern bool objEm, spot_em;
extern float angleX, angleY, angleZ, tx,ty,tz;
extern int rotat_player, mov, swing;
extern float ballX, ballY, ballZ, ballx2, bally2, ballz2, wally, spike_x, spike_y, spike_z;
extern int dir, stp, score, score_flag[10];
extern bool star1_flag, star2_flag, star3_flag, star4_flag, star5_flag, star6_flag, star7_flag, starRotate, spike_flag, wall_flag;
extern float star1_x, star1_y, star1_z, star2_x, star2_y, star2_z, star3_x, star3_y, star3_z, star4_x, star4_y, star4_z;

extern GLfloat Ex, Tex;
extern GLfloat Ey, Tey;
extern GLfloat Ez, Tez;

extern GLfloat Cx, Tcx;
extern GLfloat Cy, Tcy;
extern GLfloat Cz, Tcz;

extern const int n1t, n2t, n1theta, n2theta;
extern int wired, curve, l;

extern float balloon_x, ballon_y, balloon_z, balloon_rotate;

#endif
