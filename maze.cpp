#include"main.h"

//GLfloat rot = 0;
float player_x = 80;
float player_y = -2;
float player_z = 105;

int l=44;
//float tx=156,ty=98,tz=6;

//float tx=82.5,ty=9.2,tz=107;

float angleX = 0;
float angleY = 0;
float angleZ = 0;

bool no_move = false;
int rotat_player=0, swing=1, dir=0;

int next, next_side, whichBall=1;

float ballX=60, ballY=3, ballZ=60;
float ballx2=40, bally2=3, ballz2=68;
float wally=0;
float spike_x=27.5,spike_y=-10,spike_z=85;
float star1_x=10, star1_y=0,star1_z=80;
float star2_x=20, star2_y=0,star2_z=60;
float star3_x=70, star3_y=0, star3_z=70;
float star4_x=90, star4_y=0, star4_z=55;
float star5_x=10, star5_y=0, star5_z=10;
float star6_x=10, star6_y=0, star6_z=20;
float star7_x=10, star7_y=0, star7_z=30;
int stp=0, score_flag[10]={0};
bool star1_flag=false, star2_flag=false, star3_flag=false, star4_flag=false, star5_flag=false, star6_flag=false, star7_flag=false;
bool spike_flag=false, wall_flag=false;


float wall_height=10, wall_length=5, wall_width=100;
float tower_height=40, tower_width=2, tower_length=2, tower_gap=20, base_height=2, base_width=20, base_length=20, base_gap=20, base_wall=15;
float ladder_height=32, ladder_width=0.5, ladder_length=0.5, ladder_gap=5, step_height_width=0.5, step_length=2;

static GLfloat v_maze[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLfloat v_cube[8][3] =
{
    {-1.0, -1.0, -1.0}, //0
    {-1.0, -1.0, 1.0}, //1
    {-1.0, 1.0, -1.0}, //2
    {-1.0, 1.0, 1.0}, //3

    {1.0, -1.0, -1.0}, //4
    {1.0, -1.0, 1.0}, //5
    {1.0, 1.0, -1.0}, //6
    {1.0, 1.0, 1.0} //7
};

static GLubyte q_indices[6][4] =
{
    {3, 1, 5, 7}, //front
    {6, 4, 0, 2}, //back
    {2, 3, 7, 6}, //top
    {1, 0, 4, 5}, //bottom
    {7, 5, 4, 6}, //right
    {2, 0, 1, 3} //left
};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void draw_cube(float colR=0.5, float colG=0.5, float colB=0.5,
               bool em=false, float shine=128)
{
    properties(colR,colG,colB,em,shine);

    glBegin(GL_QUADS);
    for (GLint i=0; i<6; i++)
    {
        getNormal3p(v_cube[q_indices[i][0]][0], v_cube[q_indices[i][0]][1], v_cube[q_indices[i][0]][2],
                    v_cube[q_indices[i][1]][0], v_cube[q_indices[i][1]][1], v_cube[q_indices[i][1]][2],
                    v_cube[q_indices[i][2]][0], v_cube[q_indices[i][2]][1], v_cube[q_indices[i][2]][2]);

        glTexCoord2f(0,1);
        glVertex3fv(&v_cube[q_indices[i][0]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_cube[q_indices[i][1]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_cube[q_indices[i][2]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&v_cube[q_indices[i][3]][0]);
    }
    glEnd();
}

void maze_cube(float colR=0.5, float colG=0.5, float colB=0.5,
               bool em=false, float shine=128)
{
    properties(colR,colG,colB,em,shine);

    glBegin(GL_QUADS);
    for (GLint i=0; i<6; i++)
    {
        getNormal3p(v_maze[q_indices[i][0]][0], v_maze[q_indices[i][0]][1], v_maze[q_indices[i][0]][2],
                    v_maze[q_indices[i][1]][0], v_maze[q_indices[i][1]][1], v_maze[q_indices[i][1]][2],
                    v_maze[q_indices[i][2]][0], v_maze[q_indices[i][2]][1], v_maze[q_indices[i][2]][2]);

        glTexCoord2f(0,1);
        glVertex3fv(&v_maze[q_indices[i][0]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_maze[q_indices[i][1]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_maze[q_indices[i][2]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&v_maze[q_indices[i][3]][0]);
    }
    glEnd();
}

void collision_detection()
{
    {
        if( (player_x>=0 && player_x<=85 && player_z<=100 && player_z>=95) || (player_x>=90 && player_x<=100 && player_z<=100 && player_z>=0) || (player_x>=40 && player_x<=95 && player_z<=85 && player_z>=80) || (player_x>=50 && player_x<=95 && player_z<=30 && player_z>=25) || (player_x>=20 && player_x<=70 && player_z<=55 && player_z>=50) || (player_x>=0 && player_x<=85 && player_z<=5 && player_z>=0))
        {
            //cout<<"detected"<<endl;
            next =0;
        }
        else
            next=1;
    }

    {
        if ((player_x>=0 &&  player_x<=85 && player_z<=100 && player_z>=90) || (player_x>=15 &&  player_x<=25 && player_z<=90 && player_z>=80) || (player_x>=0 &&  player_x<=5 && player_z<=90 && player_z>=0) || (player_x>=45 &&  player_x<=50 && player_z<85 && player_z>=65) ||(player_x>=5 &&  player_x<=15 && player_z<=75 && player_z>=65))
        { //(player_x>=65 &&  player_x<=85 && player_z<=50 && player_z>=40)
            //cout<<"detected"<<endl;
            next_side =0;
        }
        else
            next_side=1;
    }

    if ((player_z<=85 && player_z>=80 && player_x>=26 && player_x<=39 && spike_y>=-7 && spike_y<=0 && spike_flag==true) || (player_z<=32 && player_z>=25 && player_x>=31 && player_x<=41 && wally<10 && wally>0 && wall_flag==true) ||  (player_x>=53 && player_x<=63 && player_z>=55 && player_z<=65 && ballZ>=55 && ballZ<=60) || (player_x<=40 && player_x>=35 && player_z>=65 && player_z<=70 && ballx2>=35 && ballx2<=40) )
    {
        Ex=80; Ey=10; Ez=113;
        Cx=80; Cy=10; Cz=-505;
        Tex=80; Tey=10; Tez=113;
        Tcx=80; Tcy=10; Tcz=-505;
        player_x = 80;
        player_z=105;
    }

    if(player_x>=7 && player_x<=10 && player_z<=80 && player_z>75)
    {
        star1_flag=false;
        if(score_flag[0]==0)
        {
            score++;
            score_flag[0]=1;
        }
    }

    if(player_x>=15 && player_x<=25 && player_z<=60 && player_z>=55)
    {
        star2_flag=false;
        if(score_flag[1]==0)
        {
            score++;
            score_flag[1]=1;
        }
    }

    if(player_x>=64 && player_x<=67 && player_z<=70 && player_z>=65)
    {
        star3_flag=false;
        if(score_flag[2]==0)
        {
            score++;
            score_flag[2]=1;
        }
    }

    if(player_x>=85 && player_x<=90 && player_z<=55 && player_z>=50)
    {
        star4_flag=false;
        if(score_flag[3]==0)
        {
            score++;
            score_flag[3]=1;
        }
    }

    if(player_x>=6 && player_x<=8 && player_z<=11 && player_z>=9)
    {
        star5_flag=false;
        if(score_flag[4]==0)
        {
            score++;
            score_flag[4]=1;
        }
    }
    if(player_x>=6 && player_x<=8 && player_z<=21 && player_z>=19)
    {
        star6_flag=false;
        if(score_flag[5]==0)
        {
            score++;
            score_flag[5]=1;
        }
    }
    if(player_x>=6 && player_x<=8 && player_z<=31 && player_z>=29)
    {
        star7_flag=false;
        if(score_flag[6]==0)
        {
            score++;
            score_flag[6]=1;
        }
    }

    //if(player_z<=0) {stp=1;}
}

void draw_maze()
{
    glPushMatrix();
    //wall 1 x->
    collision_detection();
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[6]);
    glPushMatrix();
    glScalef(wall_width-15,wall_height,wall_length); //center x=45,z=2.5
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 2 z->
    glPushMatrix();
    glTranslatef(0,0,wall_length);
    glScalef(wall_length,wall_height,wall_width - 10); //center x=2.5, z=50
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 3 z->
    glPushMatrix();
    glTranslatef(wall_width-5,0,wall_length);
    glScalef(wall_length,wall_height,wall_width - 5); //center x=97.5, z=52.5
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 4 x->
    glPushMatrix();
    glTranslatef(0,0,wall_width-5);
    glScalef(wall_width-15,wall_height,wall_length); //center x=45, z=97.5
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 5 x-> moddle one
    glPushMatrix();
    glTranslatef(wall_length+15,0,wall_width-50);
    glScalef(wall_width-50,wall_height,wall_length); //center x=30, z=52.5
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 6 x-> moddle one
    glPushMatrix();
    glTranslatef(wall_width-25,0,wall_width-30);
    glScalef(wall_width-80,wall_height,wall_length); //center x=85, z=72.5
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 7 x-> moddle one
    glPushMatrix();
    glTranslatef(wall_width-95,0,wall_width-30);
    glScalef(wall_width-90,wall_height,wall_length); //center x=30, z=95
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 8 x-> moddle one
    glPushMatrix();
    glTranslatef(wall_width-55,0,wall_width-20);
    glScalef(wall_width-50,wall_height,wall_length); //center x=70, z=87.5
    glColor3f(1,1,1);
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 9 z->
    glPushMatrix();
    glTranslatef(wall_width-55,0,wall_length+65);
    glScalef(wall_length,wall_height,wall_width - 90); //center x=47.5, z=75
    glColor3f(1,1,0);
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 10 z->
    glPushMatrix();
    glTranslatef(wall_width-80,0,wall_length+80);
    glScalef(wall_length,wall_height,wall_width - 90); //center x=22.5, z=90
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 11 x-> moddle one
    glPushMatrix();
    glTranslatef(45,0,wall_width-75);
    glScalef(wall_width-50,wall_height,wall_length); //center x=65, z=27.5
    glColor3f(1,0,0);
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 12 z->
    glPushMatrix();
    glTranslatef(wall_width-70,0,wall_length+50);
    glScalef(wall_length,wall_height,wall_width - 90); //center x=32.5, z=60
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 13 beside 6 x-> moddle one
    glPushMatrix();
    glTranslatef(wall_width-25,0,wall_width-35);
    glScalef(wall_width-80,wall_height,wall_length); //center x=85, z=72.5
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 14 z->
    glPushMatrix();
    glTranslatef(wall_width-75,0,wall_length);
    glScalef(wall_length,wall_height,wall_width - 55); //center x=25.5, z=23
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 15 x-> moddle one
    glPushMatrix();
    glTranslatef(45,0,wall_width-70);
    glScalef(wall_width-90,wall_height,wall_length); //center x=65, z=27.5
    glColor3f(1,0,0);
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();

    //wall 16 x-> moddle one
    glPushMatrix();
    glTranslatef(85,0,wall_width-70);
    glScalef(wall_width-90,wall_height,wall_length+10); //center x=65, z=27.5
    maze_cube(0.000, 0.392, 0.000,objEm,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPopMatrix();
}

void drawObstacles()
{
    properties(1.000, 0.549, 0.000,objEm,60);
    GLUquadricObj *ball = gluNewQuadric();

    glEnable(GL_TEXTURE_2D);
    gluQuadricTexture(ball, true);
    glBindTexture(GL_TEXTURE_2D,textureID[13]);
    glPushMatrix();
    glTranslatef(ballx2,bally2,ballz2);
    gluSphere (ball, 3, 15, 15);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void draw_obstacles() //float bx, float by, float bz
{
    properties(1.000, 0.549, 0.000,objEm,60);
    GLUquadricObj *ball = gluNewQuadric();

    glEnable(GL_TEXTURE_2D);
    gluQuadricTexture(ball, true);
    glBindTexture(GL_TEXTURE_2D,textureID[13]);
    glPushMatrix();
    glTranslatef(ballX,ballY,ballZ);
    gluSphere (ball, 3, 15, 15);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void draw_wall()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[14]);
    glPushMatrix();
    glTranslatef(30,wally,30);
    glScalef(wall_width-85,wall_height,wall_length/2);
    properties(	0.863, 0.863, 0.863,objEm,60);
    maze_cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void draw_spike()
{
    properties(0.412, 0.412, 0.412,objEm,60);
    glTranslatef(spike_x, spike_y, spike_z);
    glScalef(5,10,5);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[14]);
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5,1);
    glVertex3f(0.5,1,0);
    glTexCoord2f(0,0);
    glVertex3f(0,0,0);
    glTexCoord2f(1,0);
    glVertex3f(1,0,0);

    glTexCoord2f(0.5,1);
    glVertex3f(1.5,1,0);
    glTexCoord2f(0,0);
    glVertex3f(1,0,0);
    glTexCoord2f(1,0);
    glVertex3f(2,0,0);

    glTexCoord2f(0.5,1);
    glVertex3f(2.5,1,0);
    glTexCoord2f(0,0);
    glVertex3f(2,0,0);
    glTexCoord2f(1,0);
    glVertex3f(3,0,0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void star()
{
    glPushMatrix();
    properties(1,1,1,objEm,60);
    glBegin(GL_POLYGON);

    glTexCoord2f(0.5,0); glVertex3f(1,0,0);
    glTexCoord2f(1,0.5); glVertex3f(2,1,0);
    glTexCoord2f(0.5,1); glVertex3f(0,2,0);
    glTexCoord2f(0,0.5); glVertex3f(-2,1,0);
    glTexCoord2f(0,0); glVertex3f(-1,0,0);

    glEnd();
    glPopMatrix();
}

void star1()
{
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textureID[15]);
        glPushMatrix();
        glTranslatef(star1_x, star1_y, star1_z);
        glRotatef(rotatstar,0,1,0);
        glScalef(1,4,1);
        star();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
}

void star2()
{
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textureID[15]);
        glPushMatrix();
        glTranslatef(star2_x, star2_y, star2_z);
        glRotatef(rotatstar,0,1,0);
        glScalef(1,4,1);
        star();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
}

void star3()
{
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textureID[15]);
        glPushMatrix();
        glTranslatef(star3_x, star3_y, star3_z);
        glRotatef(rotatstar,0,1,0);
        glScalef(1,4,1);
        star();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
}

void star4()
{
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textureID[15]);
        glPushMatrix();
        glTranslatef(star4_x, star4_y, star4_z);
        glRotatef(rotatstar,0,1,0);
        glScalef(1,4,1);
        star();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
}

void star5()
{
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textureID[15]);
        glPushMatrix();
        glTranslatef(star5_x, star5_y, star5_z);
        glRotatef(rotatstar,0,1,0);
        glScalef(1,4,1);
        star();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
}

void star6()
{
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textureID[15]);
        glPushMatrix();
        glTranslatef(star6_x, star6_y, star6_z);
        glRotatef(rotatstar,0,1,0);
        glScalef(1,4,1);
        star();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
}

void star7()
{
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textureID[15]);
        glPushMatrix();
        glTranslatef(star7_x, star7_y, star7_z);
        glRotatef(rotatstar,0,1,0);
        glScalef(1,4,1);
        star();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
}

void draw_player()
{
    GLUquadricObj *head = gluNewQuadric();
    GLUquadricObj *body = gluNewQuadric();
    // cube player
    glPushMatrix();
    glTranslatef(player_x, player_y, player_z);
    glRotatef(dir*90, 0, 1, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[8]);
    glPushMatrix();
    glScalef(5,1,5);
    maze_cube(1,1,0,objEm,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Human
    properties(0.753, 0.753, 0.753,objEm,60);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[9]);
    glPushMatrix();
    glTranslatef(player_x+2.5, player_y+4, player_z+2);
    glScalef(0.2,0.2,0.2);
    //glRotatef(dir*90, 0, 1, 0);

    // Body
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    gluCylinder(body,2,2,20,32,32);
    glPopMatrix();

    // Head
    glPushMatrix();
    glTranslatef(0., 25, 0);

    glColor3f(1.0, 1.0, 1.0);
    glRotatef(-90, 1, 0, 0);
    glScalef(1,0.5,1);
    gluSphere(head, 10, 32, 32);
    glColor3f(0.1, 0.1, 0.1);
    glPopMatrix();

    // Left hand
    glPushMatrix();
    glTranslatef(0, 15, 0);
    glRotatef(90+30*swing, 1, 0, 0);
    glRotatef(40, 0, 1, 0);
    gluCylinder(body,2,2,12,32,32);
    glPopMatrix();

    // Right hand
    glPushMatrix();
    glTranslatef(0, 15, 0);
    glRotatef(90-30*swing, 1, 0, 0);
    glRotatef(-40, 0, 1, 0);
    gluCylinder(body,2,2,12,32,32);
    glPopMatrix();

    // Left leg
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(90-30*swing, 1, 0, 0);
    glRotatef(40, 0, 1, 0);
    gluCylinder(body,2,2,12,32,32);
    glPopMatrix();

    // Right leg
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(90+30*swing, 1, 0, 0);
    glRotatef(-40, 0, 1, 0);
    gluCylinder(body,2,2,12,32,32);
    glPopMatrix();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void tower_stand()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[16]);
    glPushMatrix();
    glTranslatef(0,tower_height,0);
    glScalef(tower_width, tower_height+10, tower_length);
    draw_cube(0.545, 0.271, 0.075, objEm, 60);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-tower_gap,tower_height,0);
    glScalef(tower_width, tower_height+8, tower_length);
    draw_cube(0.545, 0.271, 0.075, objEm, 60);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,tower_height,-tower_gap);
    glScalef(tower_width, tower_height+8, tower_length);
    draw_cube(0.545, 0.271, 0.075, objEm, 60);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-tower_gap,tower_height,-tower_gap);
    glScalef(tower_width, tower_height+8, tower_length);
    draw_cube(0.545, 0.271, 0.075, objEm, 60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void tower_base()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[17]);
    ///floor
    glPushMatrix();
    glTranslatef(-base_width/2,(2*tower_height)-base_gap,-base_length/2);
    glScalef(base_width, base_height, base_length);
    draw_cube(0.627, 0.322, 0.176,objEm,60);
    glPopMatrix();

    ///front wall
    glPushMatrix();
    glTranslatef(-base_width/2,((2*tower_height)-base_gap+base_length-base_wall)+base_height,base_length/2-base_height/2);
    glScalef(base_width, base_length-base_wall, base_height/2);
    draw_cube(0.627, 0.322, 0.176,objEm,60);
    glPopMatrix();

    ///back wall
    glPushMatrix();
    glTranslatef(-base_width/2,((2*tower_height)-base_gap+base_length-base_wall)+base_height,-(base_length+base_length/2)+base_height/2);
    glScalef(base_width, base_length-base_wall, base_height/2);
    draw_cube(0.627, 0.322, 0.176,objEm,60);
    glPopMatrix();

    ///left wall
    glPushMatrix();
    glTranslatef(-(base_length+base_length/2)+base_height/2,((2*tower_height)-base_gap+base_length-base_wall)+base_height,-base_width/2+3);
    glScalef(base_height/2, base_length-base_wall,base_width-5);
    draw_cube(0.627, 0.322, 0.176,objEm,60);
    glPopMatrix();

    ///right wall
    glPushMatrix();
    glTranslatef(base_length/2-base_height/2,((2*tower_height)-base_gap+base_length-base_wall)+base_height,-base_width/2);
    glScalef(base_height/2, base_length-base_wall,base_width-2);
    draw_cube(0.627, 0.322, 0.176,objEm,60);
    glPopMatrix();

    ///floor below
    glPushMatrix();
    glTranslatef(-base_width/2,(2*tower_height)- 2*base_gap,-base_length/2);
    glScalef(base_width, base_height, base_length);
    draw_cube(0.627, 0.322, 0.176,objEm,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void shade()
{
    ///shade
    properties(0.627, 0.322, 0.176,objEm,60);
    glPushMatrix();
    glRotatef(44,0,1,0);
    glTranslatef(0,36,-12);
    glRotatef(90,0,0,1);
    glScalef(10,10,10);
    Bezier(0,7,n1t,n1theta);
    glPopMatrix();
}

void ladder()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[16]);
    glPushMatrix();
    glTranslatef(0,-6,0);
    glRotatef(-8,0,0,1);
    glPushMatrix();
    glTranslatef(-tower_gap-20, ladder_height, -base_length-7.5);
    //glRotatef(-20,0,0,1);
    glScalef(ladder_width, ladder_height, ladder_length);
    draw_cube(0.824, 0.412, 0.118,objEm,true);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-tower_gap-20, ladder_height, -base_length-2.5);
    //glRotatef(-20,0,0,1);
    glScalef(ladder_width, ladder_height, ladder_length);
    draw_cube(0.824, 0.412, 0.118,objEm,true);
    glPopMatrix();

    for(int i=5; i<=60; i+=5)
    {
        glPushMatrix();
        //glRotatef(-20,0,0,1);
        glTranslatef(-tower_gap-20, i, -base_length-step_length*2-ladder_length*2);
        glScalef(step_height_width, step_height_width, step_length);
        draw_cube(0.824, 0.412, 0.118,objEm,true);
        glPopMatrix();
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void tower()
{
    glPushMatrix();
    shade();
    tower_base();
    tower_stand();
    ladder();
    glPopMatrix();
}

