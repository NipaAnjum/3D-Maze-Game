#include"main.h"
GLfloat Ex_l2 = 84, Tex_l2=84; //80
GLfloat Ey_l2 = 6, Tey_l2=8; //40
GLfloat Ez_l2 = 108, Tez_l2=108; //120

GLfloat Cx_l2 = 84, Tcx_l2=84;//80;
GLfloat Cy_l2 = 6, Tcy_l2=8;//40;
GLfloat Cz_l2 = -512, Tcz_l2=-512;//-500;


float player2_x = 80;
float player2_y = 0;
float player2_z = 105;

int maze[15][15]=
{
    1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
    1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,
    1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1,
    1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1
};

void maze_l2()
{
    float scale=1;
    glPushMatrix();
    for(int i=0; i<15; i++){
    for(int j=0; j<15; j++){
        if(maze[i][j] == 1){  // Means there is a cube there
            glPushMatrix();
            glScalef(7,7,6.5);
            glTranslatef(j * scale, 0, i * scale);
            maze_cube(1,1,0,true,60);
            glPopMatrix();
        }
    }
}
glPopMatrix();
}

void player_l2()
{
    glPushMatrix();
    glTranslatef(player2_x, player2_y, player2_z);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[8]);
    glPushMatrix();
    glScalef(5,2,5);
    maze_cube(1,1,0,spot_em,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void game_l2()
{
    glPushMatrix();
    ///environment
    glPushMatrix();
    drawSkybox(1);
    glPopMatrix();

    ///the maze
    glPushMatrix();
    draw_maze();
    glPopMatrix();

    ///the player
    glPushMatrix();
    //glTranslatef(player_x, 2+player_y, player_z);
    //glRotatef(dir*90, 0, 1, 0);
    //glScalef(0.2,0.2,0.2);
    player_l2();
    glPopMatrix();

    ///the reel
    glPushMatrix();
    draw_reel();
    glPopMatrix();

    ///the obstacle
    ///1
    /*glPushMatrix();
    draw_obstacles();
    glPopMatrix();
    ///2
    glPushMatrix();
    drawObstacles();
    glPopMatrix();
    ///3
    glPushMatrix();
    draw_wall();
    glPopMatrix();
    ///4
    glPushMatrix();
    draw_spike();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20,20,20);
    glScalef(2,5,2);
    draw_curve();
    glPopMatrix();*/

    ///light sources
    /*glPushMatrix();
    light0(400,500,-640);
    glPopMatrix();

    glPushMatrix();
    light1(player_x,player_y+15,player_z);
    glPopMatrix();*/

    /*glPushMatrix();
    //glScalef(10,10,10);
    axis();
    glPopMatrix();*/

    glPushMatrix();
    tree();
    glPopMatrix();

    glPopMatrix();
}

void display_l2(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 5000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(Ex_l2,Ey_l2,Ez_l2, Cx_l2,Cy_l2,Cz_l2, 0,1,0);

    glRotatef(rotat_scene, 0,1,0);
    glPushMatrix();
    game_l2();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}
