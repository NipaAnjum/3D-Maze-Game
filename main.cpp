/// NIPA ANJUM
/// ROLL - 1607055
/// CSE- 4208

#include"main.h"

const int windowWidth = 1000;
const int windowHeight = 700;
const float windowRatio = 1.0*windowWidth/windowHeight;

int wired=0;
float x=0, y=0;
extern GLuint makeaTree;

GLfloat Ex = 80, Tex=80; //62
GLfloat Ey = 10, Tey=10; //48
GLfloat Ez = 113, Tez=113; //132

GLfloat Cx = 80, Tcx=80;//62
GLfloat Cy = 10, Tcy=10;//48
GLfloat Cz = -505, Tcz=-505;//-488

GLfloat Ux = 0;
GLfloat Uy = 1;
GLfloat Uz = 0;

GLfloat fl=8, fr=8, fb=8, ft=8, fn=4, ff=5000;

bool diff1=true, spec1=true, amb1=true, diff2=true, spec2=true, amb2=true, em=true, spot_em=true, objEm=true;
bool sunLight=true, spotLight=false, e=true, tower1Light=false, tower2Light=false;
float spot_exp=128;
bool rotationOn=true, starRotate=true, show_score=false;

static int flag=1, flag2=1, flag3=1, flag4=1, balloon_flag=1, balloon_run=1, still=0;
int mov=0, completed[2]= {0}, comp=0;

float up=0, down=0, lft=0, rght=0, frnt=0, bck=0;

extern int next, next_side;

int cnt, score;
clock_t start,en_d,now;
char t[2], score_t[2];

GLfloat rotat_scene=0;
GLfloat rotat=0, rotatstar=0;

unsigned int textureID[100];

int clikd=0;
float wcsClkDn[3],wcsClkUp[3];
class point1
{
public:
    point1()
    {
        x=0;
        y=0;
    }
    int x;
    int y;
} clkpt[2];
int flag_m=0;
GLint viewport[4]; //var to hold the viewport info
GLdouble modelview[16]; //var to hold the modelview info
GLdouble projection[16]; //var to hold the projection matrix info

void scsToWcs(float sx,float sy, float wcsv[3] )
{

    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
    GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
    glGetDoublev( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info

    winX = sx;
    winY = (float)viewport[3] - (float)sy;
    winZ = 0;

    //get the world coordinates from the screen coordinates
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
    wcsv[0]=worldX;
    wcsv[1]=worldY;
    wcsv[2]=worldZ;


}
void processMouse(int button, int state, int x, int y)
{
    properties(1,0,0,true,60);
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(flag_m!=1)
        {
            flag_m=1;
            clkpt[0].x=x;
            clkpt[0].y=y;
        }


        scsToWcs(clkpt[0].x,clkpt[0].y,wcsClkDn);
        cout<<"\nD: "<<x<<" "<<y<<" wcs: "<<wcsClkDn[0]<<", "<<wcsClkDn[1]<<", "<<"0";
    }
    else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if (flag_m==1)
        {
            clkpt[1].x=x;
            clkpt[1].y=y;
            flag_m=0;
        }
        float wcs[3];
        scsToWcs(clkpt[1].x,clkpt[1].y,wcsClkUp);
        cout<<"\nU: "<<x<<" "<<y<<" wcs: "<<wcsClkUp[0]<<", "<<wcsClkUp[1]<<", "<<"0";

        clikd=!clikd;
    }
}

void properties(float colR=0.5, float colG=0.5, float colB=0.5, bool em=false, float shine=60)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { colR*0.5, colG*0.5, colB*0.5, 1.0 };
    GLfloat mat_diffuse[] = { colR, colG, colB, 1.0 };
    GLfloat mat_specular[] = { 1, 1, 1, 1.0 };
    GLfloat mat_emission[] = {colR*0.5, colG*0.5, colB*0.5, 1.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    if(em)
        glMaterialfv( GL_FRONT, GL_EMISSION, mat_emission);

}

void LoadTexture(const char*filename, int index)
{
    glGenTextures(1, &textureID[index]);
    glBindTexture(GL_TEXTURE_2D, textureID[index]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, textureID[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void light0(float x, float y, float z)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0}; //.5.5.5
    GLfloat light_diffuse[]  = { 1, 1, 1, 1.0 }; //111
    GLfloat light_specular[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_position[] = {x, y, z, 0.0 };

    glEnable( GL_LIGHT0);
    if(sunLight && amb1) glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    else glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
    if(sunLight && diff1) glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    else glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
    if(sunLight && spec1) glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    else glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);

    glLightfv( GL_LIGHT0, GL_POSITION, light_position);


}
void light1(float x, float y, float z, float cutoff=50)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1};
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1};
    GLfloat light_diffuse[]  = { 1, 1, 0, 1 };
    GLfloat light_specular[] = { 0.8, 0.8, 0.8, 1 };
    GLfloat light_position[] = { x, y, z, 1 };
    //GLfloat light_attenuation[] = {1,0.0014,0.000007};

    glEnable( GL_LIGHT1);
    if(spotLight && amb2) glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
    else glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);
    if(spotLight && diff2) glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    else glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);
    if(spotLight && spec2) glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    else glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);

    /*glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, light_attenuation[0]);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, light_attenuation[1]);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, light_attenuation[2]);*/
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);

    GLfloat spt_dir[] = {0,-1,0,1};
    GLfloat spt_cut[] = {cutoff};
    //GLfloat spt_exp[] = {spot_exp};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spt_dir);
    //glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, spt_exp);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spt_cut);

}

void light2(float x, float y, float z, float cutoff=50)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1};
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1};
    GLfloat light_diffuse[]  = { 1, 1, 0, 1 };
    GLfloat light_specular[] = { 0.8, 0.8, 0.8, 1 };
    GLfloat light_position[] = { x, y, z, 1 };

    glEnable( GL_LIGHT2);
    if(tower1Light && amb2) glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
    else glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);
    if(tower1Light && diff2) glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    else glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);
    if(tower1Light && spec2) glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    else glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);

    glLightfv( GL_LIGHT2, GL_POSITION, light_position);

    GLfloat spt_dir[] = {0,-1,0,1};
    GLfloat spt_cut[] = {cutoff};
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spt_dir);
    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spt_cut);
}

void light3(float x, float y, float z, float cutoff=50)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1};
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1};
    GLfloat light_diffuse[]  = { 1, 1, 0, 1 };
    GLfloat light_specular[] = { 0.8, 0.8, 0.8, 1 };
    GLfloat light_position[] = { x, y, z, 1 };

    glEnable( GL_LIGHT3);
    if(tower2Light && amb2) glLightfv( GL_LIGHT3, GL_AMBIENT, light_ambient);
    else glLightfv( GL_LIGHT3, GL_AMBIENT, no_light);
    if(tower2Light && diff2) glLightfv( GL_LIGHT3, GL_DIFFUSE, light_diffuse);
    else glLightfv( GL_LIGHT3, GL_DIFFUSE, no_light);
    if(tower2Light && spec2) glLightfv( GL_LIGHT3, GL_SPECULAR, light_specular);
    else glLightfv( GL_LIGHT3, GL_SPECULAR, no_light);

    glLightfv( GL_LIGHT3, GL_POSITION, light_position);

    GLfloat spt_dir[] = {0,-1,0,1};
    GLfloat spt_cut[] = {cutoff};
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spt_dir);
    glLightfv(GL_LIGHT3, GL_SPOT_CUTOFF, spt_cut);
}

void spot_light()
{
    if(spotLight)
    {
        glPushMatrix();
        glTranslatef(player_x+2.5,player_y+20,player_z-2.5); //50,45,50
        glScalef(0.5,0.5,0.2);
        properties(1,1,0,e,60);
        glutSolidSphere(2,50,50);
        glPopMatrix();
        glPushMatrix();
        light1(player_x+2.5,player_y+20,player_z-2.5, 50);
        glPopMatrix();
    }
}

void axis()
{
    float length = 15;
    float width = 0.3;

    // X-axis red
    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,width,width);
    glTranslatef(-0.5,-0.5,-0.5);
    glColor3f(1,0,0);
    draw_cube(1,0,0, objEm, 60);
    glPopMatrix();

    // Y-axis green
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    glColor3f(0,1,0);
    draw_cube(0,1,0, objEm, 60);
    glPopMatrix();

    // Z-axis blue
    glPushMatrix();
    glTranslatef(0,0,length/2);
    glScalef(width,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    glColor3f(0,0,1);
    draw_cube(0,0,1, objEm, 60);
    glPopMatrix();
}

void game()
{
    glPushMatrix();
    glRotatef(rotat_scene,0,1,0);
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
    draw_player();
    glPopMatrix();

    ///the reel
    glPushMatrix();
    draw_reel();
    glPopMatrix();

    ///the obstacle
    ///1
    glPushMatrix();
    draw_obstacles();
    glPopMatrix();
    ///2
    glPushMatrix();
    drawObstacles();
    glPopMatrix();
    ///3
    if(wall_flag)
    {
        glPushMatrix();
        draw_wall();
        glPopMatrix();
    }
    ///4
    if(spike_flag)
    {
        glPushMatrix();
        draw_spike();
        glPopMatrix();
    }

    ///points
    //collision_detection();
    if(star1_flag)
    {
        glPushMatrix();
        star1();
        glPopMatrix();
    }
    if(star2_flag)
    {
        glPushMatrix();
        star2();
        glPopMatrix();
    }
    if(star3_flag)
    {
        glPushMatrix();
        star3();
        glPopMatrix();
    }
    if(star4_flag)
    {
        glPushMatrix();
        star4();
        glPopMatrix();
    }
    if(star5_flag)
    {
        glPushMatrix();
        star5();
        glPopMatrix();
    }
    if(star6_flag)
    {
        glPushMatrix();
        star6();
        glPopMatrix();
    }
    if(star7_flag)
    {
        glPushMatrix();
        star7();
        glPopMatrix();
    }

    glPushMatrix();
    mountain();
    glPopMatrix();

    glPushMatrix();
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-50,0,0);
    tower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(160,0,-20);
    glRotatef(180,0,1,0);
    tower();
    glPopMatrix();

    glPushMatrix();
    air_balloon();
    glPopMatrix();

    /*glPushMatrix();
    //glScalef(10,10,10);
    axis();
    glPopMatrix();*/
    glPopMatrix();
}

void output(char *str,int x,int y,int z)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-8, 8, -8, 8, 4, 5000);
    //glViewport(0,0,1000,700);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(80,20,116, 80,20,-504, 0,1,0);

    glPushMatrix();
    properties(1,1,0,true,60);
    glRasterPos3f(x,y,z);
    for (int i = 0; i < strlen(str); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
    }
    glPopMatrix();
}

void screenText(char *str,int x,int y,int z)
{
    glPushMatrix();
    properties(1,1,0,true,60);
    glTranslatef(x,y,z);
    glScalef(0.008,0.008,0.008);
    //glRasterPos3f(x,y,z);
    for (int i = 0; i < strlen(str); i++)
    {
        //glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,str[i]);
    }
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-fl, fr, -fb, ft, fn, ff);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(Ex,Ey,Ez, Cx,Cy,Cz, Ux,Uy,Uz);

    glPushMatrix();

    ///light sources
    glPushMatrix();
    glPushMatrix();
    light0(400,500,-640);
    glPopMatrix();
    glPushMatrix();
    spot_light();
    glPopMatrix();
    glPushMatrix();
    light3(-58,98,-10,50);
    glPopMatrix();
    glPushMatrix();
    light2(162,88,12,50); //158,98,6
    glPopMatrix();
    glPopMatrix();
    ///

    glPushMatrix();
    game();
    glPopMatrix();

    glPushMatrix();
    glPushMatrix();
    screenText("Time", player_x,player_y+13,player_z);
    glPopMatrix();
    glPushMatrix();
    sprintf(t," %d",100-cnt);
    screenText(t,player_x+4,player_y+13,player_z); //-300,300,-400
    glPopMatrix();
    if(show_score)
    {
        glPushMatrix();
        screenText("Score", player_x,player_y+15,player_z);
        glPopMatrix();
        glPushMatrix();
        sprintf(score_t," %d",score);
        screenText(score_t,player_x+4,player_y+15,player_z); //1700
        glPopMatrix();
    }
    glPopMatrix();

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

static void resizeWindow(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-8.0, 8.0, -8.0, 8.0, 4, 5000);
    glMatrixMode (GL_MODELVIEW);
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    usleep(100);
    float x_bar, z_bar, r, theta, dx, dz, dx_norm, dz_norm, r_bar=1, anglePerStep=5;

    x_bar=Cx-Ex;
    z_bar=Cz-Ez;
    r=sqrt(x_bar*x_bar+z_bar*z_bar);

    if(x_bar==0)
        theta = 90;
    else
        theta=atan(z_bar/x_bar) * 180 / PI; //1radia=180/pi

    if((z_bar>0 && theta<0) || (z_bar<0 && theta>0))
        theta += 180;

    dx = r_bar*cos(theta * PI / 180);
    dz = r_bar*sin(theta * PI / 180);

    dx_norm = r_bar*cos((theta-90) * PI / 180);
    dz_norm = r_bar*sin((theta-90) * PI / 180);

    switch ( key )
    {
    /*case '1':
        ty-=2; cout<<"ty"<<ty<<endl; break;
    case '3':
        tz-=2; cout<<"tz"<<tz<<endl; break;
    case '5':
        tx-=2; cout<<"bx"<<tx<<endl; break;
    case '2':
        ty+=2; cout<<"ty"<<ty<<endl; break;
    case '4':
        tz+=2; cout<<"tz"<<tz<<endl; break;
    case '6':
        tx+=2; cout<<"bx"<<tx<<endl; break;
    case '7':
        balloon_rotate++; break;
    case '8':
        balloon_rotate--; break;*/
    case 's':
        stp=4;
        break;
    case 13:
        if(stp==4 || stp==3 || stp==1)
        {
            if(stp==1 && completed[0]==0)
            {
                star1_flag=true;
                star2_flag=true;
                star3_flag=true;
                star4_flag=true;
                star5_flag=true;
                star6_flag=true;
                star7_flag=true;
                spike_flag=true;
                wall_flag=true;
                show_score=true;
                comp++;
                completed[0]=1;
            }
            if(stp==3 && completed[0]==1)
            {
                star1_flag=true;
                star2_flag=true;
                star3_flag=true;
                star4_flag=true;
                star5_flag=true;
                star6_flag=true;
                star7_flag=true;
                spike_flag=true;
                wall_flag=true;
                show_score=true; //score=0; //completed=1;
            }
            stp=2;
            start=clock();
            player_x=80;
            player_y=-2;
            player_z=105;
            Ex=80;
            Ey=10;
            Ez=113;
            Cx=80;
            Cy=10;
            Cz=-505;
            Tex=80;
            Tey=10;
            Tez=113;
            Tcx=80;
            Tcy=10;
            Tcz=-505;
        }
        break;

    case 'z':
        theta-=anglePerStep;
        theta = theta * PI / 180;

        Cx=r*cos(theta)+Ex;
        Cz=r*sin(theta)+Ez;
        break;
    case 'x':
        theta+=anglePerStep;
        theta = theta * PI / 180;

        Cx=r*cos(theta)+Ex;
        Cz=r*sin(theta)+Ez;
        break;

    case 'g':
        if(sunLight == false)
        {
            sunLight = true;
            spotLight=false;
            e=false;
            objEm=true;
            glEnable( GL_LIGHT0);
            glDisable( GL_LIGHT1);
        }
        else if(sunLight == true)
        {
            sunLight = false;
            spotLight=true;
            e=true;
            objEm=false;
            glDisable( GL_LIGHT0);
            glEnable( GL_LIGHT1);
        }
        break;
    case 'h':
        if(spotLight == false && sunLight==false)
        {
            spotLight = true;
            e=true;
            glEnable( GL_LIGHT1);
        }
        else if(spotLight == true && sunLight==false)
        {
            spotLight = false;
            e=false;
            glDisable( GL_LIGHT1);
        }
        break;
    case 'y':
        if(tower1Light == false)
        {
            tower1Light = true;
            glEnable( GL_LIGHT2);
        }
        else if(tower1Light == true)
        {
            tower1Light = false;
            glDisable( GL_LIGHT2);
        }
        break;

    case 't':
        if(tower2Light == false)
        {
            tower2Light = true;
            glEnable( GL_LIGHT3);
        }
        else if(tower2Light == true)
        {
            tower2Light = false;
            glDisable( GL_LIGHT3);
        }
        break;

    case 'b':
        Ex=player_x+2.5, Ey=player_y+9, Ez=player_z+1.5;
        Tex=Ex, Tey=Ey, Tez=Ez;
        Tcx=Cx, Tcy=Cy, Tcz=Cz;
        fl=1, fr=1, fb=1, ft=1, fn=0.5;
        break;

    case 'i':
        //if(frnt<=150)
        //{
            //cout<<Ez<<" z "<<Cz<<endl;
            frnt+=2;
            bck-=2;
            Ez-=2;
            Cz-=2;
            Tez=Ez;
            Tcz=Cz;
            //cout<<frnt<<"frnt "<<endl;
        //}
        break;
    case 'm':
        //if(bck<=50)
        //{
            //cout<<Ez<<" z "<<Cz<<endl;
            frnt-=2;
            bck+=2;
            Ez+=2;
            Cz+=2;
            Tez=Ez;
            Tcz=Cz;
            //cout<<bck<<"bck "<<endl;
        //}
        break;

    case 'j':
        if(down<=0)
        {
            //cout<<Ey<<" y "<<Cy<<endl;
            down+=2;
            up-=2;
            Ey-=2;
            Cy-=2;
            Tey=Ey;
            Tcy=Cy;
            //cout<<down<<"down "<<endl;
        }
        break;
    case 'k':
        if(up<=200)
        {
            //cout<<Ey<<" y "<<Cy<<endl;
            down-=2;
            up+=2;
            Ey+=2;
            Cy+=2;
            Tey=Ey;
            Tcy=Cy;
            //cout<<up<<"up "<<endl;
        }
        break;

    case 'u':
        //if(lft<=150)
        //{
            //cout<<Ex<<" x "<<Cx<<endl;
            lft+=2;
            rght-=2;
            Ex-=2;
            Cx-=2;
            Tex=Ex;
            Tcx=Cx;
            //cout<<lft<<"lft "<<endl;
        //}
        break;
    case 'o':
        //if(rght<=100)
        //{
            //cout<<Ex<<" x "<<Cx<<endl;
            lft-=2;
            rght+=2;
            Ex+=2;
            Cx+=2;
            Tex=Ex;
            Tcx=Cx;
            //cout<<rght<<"lft "<<endl;
        //}
        break;

    case 'p':
        if(still==0)
        {
            still=1;
            Ex=46;
            Ey=96;
            Ez=144;
            Cx=46;
            Cy=96;
            Cz=-476;
        }
        else
        {
            still=0;
            Ex=Tex;
            Ey=Tey;
            Ez=Tez;
            Cx=Tcx;
            Cy=Tcy;
            Cz=Tcz;
        }
        break;

    // rotating the whole scene
    case ',':
        //rot--;
        rotat_scene++;
        break;
    case '.':
        //rot++;
        rotat_scene--;
        break;

    case 'f':
        balloon_run = ! balloon_run;
        break;

    //rotate the reel
    case 'r':
        rotationOn = !rotationOn; // value of r is inverted when pressed
        break;

    case 27:	// Escape key
        exit(1);
    }
    glutPostRedisplay();
}
void welcomeScreen(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glPushMatrix();
    output("Maze Solving Game", 50,70,50);
    glPopMatrix();
    glPushMatrix();
    output("Nipa Anjum (1607055)", 50,50,50);
    glPopMatrix();
    glPushMatrix();
    output("CSE - 4208", 50,30,50);
    glPopMatrix();
    glPushMatrix();
    output("Press 's' to see instructions", 100,0,50);
    glPopMatrix();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void winScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glPushMatrix();
    output("Congratulations! You have completed the game.", 10,60,10);
    glPopMatrix();
    glPushMatrix();
    output("You completed the game in ", 10, 40, 10);
    glPopMatrix();
    glPushMatrix();
    output(t, 10, 20, 10); //150
    glPopMatrix();
    glPushMatrix();
    output("sec", 30, 20, 10); //170
    glPopMatrix();
    if(show_score)
    {
        glPushMatrix();
        output("Score", 10, 0, 10); //150
        glPopMatrix();
        glPushMatrix();
        output(score_t, 40, 0, 10); //170
        glPopMatrix();
    }
    if(comp==1)
    {
        glPushMatrix();
        output("press ESC to end.", 10, -30, 10);
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        output("press ENTER for the next level.", 50, -30, 10);
        glPopMatrix();
    }
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}
void endScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    score=0;
    glPushMatrix();
    output("You have lost the game...", 0,50,0);
    glPopMatrix();
    glPushMatrix();
    output("Press ENTER to start again.", 0,0,0);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void instructions()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glPushMatrix();
    output("INSTRUCTIONS:",50,130,50);
    glBegin(GL_LINES);
    glVertex3f(0,120,50);
    glVertex3f(150,120,50);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    output("Use Arrow Keys to move left, right, forward, backward", 0,100,50);
    glPopMatrix();
    glPushMatrix();
    output("In level one, be safe from the red fire balls!", 0,80,50);
    glPopMatrix();
    glPushMatrix();
    output("In level two, collect coins to make score!", 0,60,50);
    glPopMatrix();
    glPushMatrix();
    output("In level two, be safe from the rock wall and sharp spikes!", 0,40,50);
    glPopMatrix();
    glPushMatrix();
    output("Press 'p' to see the full maze.", 0,20,50);
    glPopMatrix();
    glPushMatrix();
    output("Press 'b' for self-playing mode.", 0,0,50);
    glPopMatrix();
    glPushMatrix();
    output("press ENTER to start now", 100,-30,50);
    glPopMatrix();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void myFunc()
{
    if(stp==0) welcomeScreen();
    else if(stp==1) winScreen();
    else if (stp==2)display();
    else if (stp==3) endScreen();
    else if (stp==4) instructions();
    //welcomeScreen();
    //display();    //instructions();
}

void mySpecialFunc(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if (dir != 2) dir = 2;
        //cout<<player_z<<"z"<<endl;
        else if(next>=1 && still==0)
        {
            player_z-=1;
            Ez-=1;
            Cz-=0.5;
            Tez=Ez;
            Tcz=Cz;
        }
        break;
    case GLUT_KEY_DOWN:
        if (dir != 0) dir = 0;
        //cout<<player_z<<"z"<<endl;
        else if(still==0)
        {
            player_z+=1;
            Ez+=1;
            Cz+=0.5;
            Tez=Ez;
            Tcz=Cz;
        }
        break;
    case GLUT_KEY_LEFT:
        if (dir != 3) dir = 3;
        //cout<<player_x<<"x"<<endl;
        else if(next_side>=1 && still==0)
        {
            player_x-=1;
            Ex-=1;
            Cx-=0.5;
            Tex=Ex;
            Tcx=Cx;
        }
        break;
    case GLUT_KEY_RIGHT:
        if (dir != 1) dir = 1;
        //cout<<player_x<<"x"<<endl;
        else if(still==0)
        {
            player_x+=1;
            Ex+=1;
            Cx+=0.5;
            Tex=Ex;
            Tcx=Cx;
        }
        break;
    }
    swing = (swing == 1) ? -1 : 1;
}
void idle()
{
    if (rotationOn == true)
    {
        rotat+=0.5f;
    }

    if (starRotate == true)
    {
        rotatstar+=2.0f;
    }

    if(stp==2)
    {
        en_d=clock();
        cnt=(en_d-start)/CLOCKS_PER_SEC;


        if(cnt==100)
        {
            stp=3;
        }
        else if((cnt<100) && (player_z<=0))
        {
            stp=1;
        }
    }
    glutPostRedisplay();
}

void update(int value)
{
    if(flag)
    {
        ballZ += 0.2f;
        if(ballZ>80)
        {
            flag=0;

        }
    }
    if (!flag)
    {
        ballZ -= 0.2f;
        if(ballZ<60)
        {
            flag=1;

        }
    }
    if(flag2)
    {
        ballx2 += 0.2f;
        if(ballx2>40)
        {
            flag2=0;

        }
    }
    if (!flag2)
    {
        ballx2 -= 0.2f;
        if(ballx2<20)
        {
            flag2=1;

        }
    }

    if(flag3)
    {
        wally += 0.2f;
        if(wally>15)
        {
            flag3=0;

        }
    }
    if (!flag3)
    {
        wally -= 1;
        if(wally<0)
        {
            flag3=1;

        }
    }

    if(flag4)
    {
        spike_y += 0.1;
        if(spike_y>1)
        {
            flag4=0;

        }
    }
    if (!flag4)
    {
        spike_y -= 0.2;
        if(spike_y<-11)
        {
            flag4=1;

        }
    }
    if(balloon_run==1)
    {
        if(balloon_flag)
        {
            balloon_x += 2;
            if(balloon_x>502)
            {
                balloon_flag=0;

            }
        }
        if (!balloon_flag)
        {
            balloon_x -= 2;
            if(balloon_x<-377)
            {
                balloon_flag=1;

            }
        }
    }

    glutPostRedisplay(); //Tell GLUT that the display has changed

    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, update, 0);
}

void myTextures()
{
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\sky_front.bmp", SKY_FRONT);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\sky_right.bmp", SKY_RIGHT);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\sky_left.bmp", SKY_LEFT);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\sky_back.bmp", SKY_BACK);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\sky_top.bmp", SKY_TOP);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\field.bmp", FIELD);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\maze_wall.bmp", MAZE_WALL);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\steel.bmp", REEL_STEEL);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\body.bmp", BODY);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\skin.bmp", SKIN);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\hair.bmp", HAIR);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\leaf.bmp", LEAF);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\wood.bmp", WOOD);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\fire.bmp", FIRE);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\obstacle_wall.bmp", WALL);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\star.bmp", STAR);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\wooden.bmp", WOODEN);
    LoadTexture("G:\\4.2\\graphics\\Project\\step2\\bmp\\hut.bmp", HUT);
}

void print()
{
    printf("INSTRUCTIONS\n");
    printf("For changing gluLookAt points:\n");
    printf("1. i - zoom in\n2. m - zoom out\n3. u - left\n4. o - right\n5. j - down\n6. k - up\n7. z - rotate left\n8. x - rotate right\n");
    printf("For controlling lights:\n");
    printf("1. g - sun light control\n2. h - player head light control\n3. y - right tower light\n4. t - left tower light\n");
    printf("For Stopping the wheel:\n");
    printf("1. r - controls the wheel rotation\n");
    printf("For controlling the hot air balloon:\n");
    printf("1. f - controls the movement of the hot air balloon\n");
    printf("For changing view position:\n");
    printf("1. b - Seems to look through player's eye.\n");
}
int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(40,40);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Maze Solving Game");

    makeaTree=glGenLists(1);
    glNewList(makeaTree, GL_COMPILE);
    makeTree(4,0.2);
    glEndList();

    myTextures();
    print();

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );

    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);

    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(mySpecialFunc);
    glutDisplayFunc(myFunc);
    glutIdleFunc(idle);
    glutReshapeFunc(resizeWindow);
    glutMouseFunc(processMouse);
    //glutIdleFunc(animate);

    glutTimerFunc(25, update, 0);
    sndPlaySound("G:\\4.2\\graphics\\Project\\step2\\music1.wav", SND_ASYNC|SND_LOOP);
    glutMainLoop();

    return 0;
}
