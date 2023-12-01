#include"main.h"

int skybox[6];
float balloon_x=-82.5, balloon_y=80, balloon_z=-100,balloon_rotate=0;

GLuint makeaTree, mysphereID;
/*SKY_FRONT 0
SKY_RIGHT 1
SKY_LEFT 2
SKY_BACK 3
SKY_TOP 4
FIELD 5*/
void makeCylinder(float height, float base)
{
    GLUquadric *obj = gluNewQuadric();
    properties(0.545, 0.271, 0.075, false, 60);
    glPushMatrix();
    glRotatef(-90, 1.0,0.0,0.0);
    gluCylinder(obj, base,base-(0.2*base), height, 20,20);
    glPopMatrix();
    glutSwapBuffers();
}

void makeTree(float height, float base)
{

    float angle;
    makeCylinder(height, base);
    glTranslatef(0.0, height, 0.0);
    height -= height*.2;
    base-= base*0.3;
    for(int a= 0; a<3; a++)
    {
        angle = rand()%50+20;
        if(angle >48)
            angle = -(rand()%50+20);
        if (height >1)
        {
            glPushMatrix();
            glRotatef(angle,1,0.0,1);
            makeTree(height,base);
            glPopMatrix();

        }
        else
        {
            glPushMatrix();
            properties(0.000, 0.502, 0.000,objEm,60);
            glutSolidSphere(.2,10,10);
            //makeSphere();
            glPopMatrix();
        }
    }
}

void mountain()
{
    glPushMatrix();
    properties(0.000, 0.392, 0.000,objEm,60);
    glTranslatef(440,-126.5,-570);
    glScalef(50,50,20);
    glRotatef(90,0,0,1);
    Bezier(8,14,n2t,n2theta);
    glPopMatrix();

    glPushMatrix();
    properties(0.000, 0.392, 0.000,objEm,60);
    glTranslatef(92,-126.5,-676);
    glScalef(50,50,20);
    glRotatef(90,0,0,1);
    Bezier(8,14,n2t,n2theta);
    glPopMatrix();

    glPushMatrix();
    properties(0.000, 0.392, 0.000,objEm,60);
    glTranslatef(-438,-160,-664);
    glScalef(50,65,20);
    glRotatef(90,0,0,1);
    Bezier(8,14,n2t,n2theta);
    glPopMatrix();
}

void drawSkybox(double D)
{
    float env_height = 200, env_width = 700, env_length = 700;
    glTranslatef(0,env_height,0);
    glScalef(env_width,env_height,env_length);
    glEnable(GL_TEXTURE_2D);

    /* Sides */
    glBindTexture(GL_TEXTURE_2D,textureID[1]); //front 1
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    properties(0.529, 0.808, 0.922,objEm,60);
    glTexCoord2f(0,0);
    glVertex3f(-D,-D,-D);
    glTexCoord2f(1,0);
    glVertex3f(+D,-D,-D);
    glTexCoord2f(1,1);
    glVertex3f(+D,+D,-D);
    glTexCoord2f(0,1);
    glVertex3f(-D,+D,-D);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,textureID[0]); //right 0
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    properties(0.529, 0.808, 0.922,objEm,60);
    glTexCoord2f(0,0);
    glVertex3f(+D,-D,-D);
    glTexCoord2f(1,0);
    glVertex3f(+D,-D,+D);
    glTexCoord2f(1,1);
    glVertex3f(+D,+D,+D);
    glTexCoord2f(0,1);
    glVertex3f(+D,+D,-D);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,textureID[2]); //back 2
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    properties(0.529, 0.808, 0.922,objEm,60);
    glTexCoord2f(0,0);
    glVertex3f(+D,-D,+D);
    glTexCoord2f(1,0);
    glVertex3f(-D,-D,+D);
    glTexCoord2f(1,1);
    glVertex3f(-D,+D,+D);
    glTexCoord2f(0,1);
    glVertex3f(+D,+D,+D);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,textureID[3]); //left 3
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    properties(0.529, 0.808, 0.922,objEm,60);
    glTexCoord2f(0,0);
    glVertex3f(-D,-D,+D);
    glTexCoord2f(1,0);
    glVertex3f(-D,-D,-D);
    glTexCoord2f(1,1);
    glVertex3f(-D,+D,-D);
    glTexCoord2f(0,1);
    glVertex3f(-D,+D,+D);
    glEnd();

    /* Top and Bottom */
    glBindTexture(GL_TEXTURE_2D,textureID[4]); //top 4
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    properties(0.529, 0.808, 0.922,objEm,60);
    glTexCoord2f(0,0);
    glVertex3f(-D,+D,+D);
    glTexCoord2f(0,1);
    glVertex3f(+D,+D,+D);
    glTexCoord2f(1,1);
    glVertex3f(+D,+D,-D);
    glTexCoord2f(1,0);
    glVertex3f(-D,+D,-D);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,textureID[5]); //down 5
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    properties(0.133, 0.545, 0.133,objEm,60);
    glTexCoord2f(20,20);
    glVertex3f(+D,-D,-D);
    glTexCoord2f(0,20);
    glVertex3f(-D,-D,-D);
    glTexCoord2f(0,0);
    glVertex3f(-D,-D,+D);
    glTexCoord2f(20,0);
    glVertex3f(+D,-D,+D);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
void tree_top()
{
    properties(0.678, 1.000, 0.184, objEm, 60);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[11]);
    glBegin(GL_TRIANGLES);
    // Front
    glTexCoord2f(0.5, 1.0);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Right
    glTexCoord2f(0.5, 1.0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Back
    glTexCoord2f(0.5, 1.0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left
    glTexCoord2f(0.5, 1.0);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glEnd();   // Done drawing the pyramid

    glDisable(GL_TEXTURE_2D);

}

void tree_bottom()
{
    properties(0.545, 0.271, 0.075,objEm,60);
    glEnable(GL_TEXTURE_2D);
    GLUquadricObj *wood = gluNewQuadric();
    glPushMatrix();
    gluQuadricTexture(wood, true);
    glBindTexture(GL_TEXTURE_2D, textureID[12]);
    glRotatef (90, 0.0, 1.0, 0.0);
    glRotatef (-90, 1.0, 0.0, 0.0);
    gluCylinder(wood, 5, 5, 10, 100, 100);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void tree()
{
    for(float i=0; i<2; i+=0.5)
    {
        //right 1
        glPushMatrix();
        glTranslatef(110,25,i*100);
        glScalef(4,20,4);
        tree_top();
        glPopMatrix();

        //right 2
        glPushMatrix();
        glTranslatef(140,25,i*100*0.5);
        glScalef(4,20,4);
        tree_top();
        glPopMatrix();

        //middle 1
        /*glPushMatrix();
        glTranslatef(i*100,25,-10);
        glScalef(4,20,4);
        tree_top();
        glPopMatrix();

        //middle 2
        glPushMatrix();
        glTranslatef(i*0.7*100,25,-30);
        glScalef(4,20,4);
        tree_top();
        glPopMatrix();*/

        //left 1
        glPushMatrix();
        glTranslatef(-15,25,i*60);
        glScalef(4,20,4);
        tree_top();
        glPopMatrix();

        //left 2
        glPushMatrix();
        glTranslatef(-30,25,i*60*0.7);
        glScalef(4,20,4);
        tree_top();
        glPopMatrix();
    }
    for(float i=0; i<2; i+=0.5)
    {
        //right
        glPushMatrix();
        glTranslatef(110,0,i*100);
        glScalef(0.2,0.5,0.2);
        tree_bottom();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(140,0,i*100*0.5);
        glScalef(0.2,0.5,0.2);
        tree_bottom();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(-15,0,i*60);
        glScalef(0.2,0.5,0.2);
        tree_bottom();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-30,0,i*60*0.7);
        glScalef(0.2,0.5,0.2);
        tree_bottom();
        glPopMatrix();

        //middle
        /*glPushMatrix();
        glTranslatef(i*100,0,-10);
        glScalef(0.2,0.5,0.2);
        tree_bottom();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(i*0.7*100,0,-30);
        glScalef(0.2,0.5,0.2);
        tree_bottom();
        glPopMatrix();*/
    }

        /*glPushMatrix();
        glTranslatef(0,0,-10);
        glScalef(5,5,1);
        glCallList(makeaTree);
        glPopMatrix();*/

        /*glPushMatrix();
        glTranslatef(60,0,-10);
        glScalef(5,5,2);
        glCallList(makeaTree);
        glPopMatrix();*/
}

void balloon()
{
    properties(0.804, 0.522, 0.247, objEm, 60);
    glPushMatrix();
    glTranslatef(10,50,0);
    glRotatef(90,0,0,1);
    glScalef(15,10,10);
    Bezier(15,27,40,20);
    glPopMatrix();
}

void seat()
{
    properties(0.722, 0.525, 0.043, objEm, 60);
    glPushMatrix();
    glTranslatef(10,30,0);
    glRotatef(90,0,0,1);
    glScalef(5,2,2);
    Bezier(28,42,40,20);
    glPopMatrix();
}

void rope()
{
    properties(0.722, 0.525, 0.043, objEm, 60);
    GLUquadricObj *cylinder_rope = gluNewQuadric();
    ///left
    glPushMatrix();
    glTranslatef(15,40,0);
    glRotatef(-10,1,0,0);
    glRotatef(-90,1,0,0);
    gluCylinder(cylinder_rope, 0.5, 0.2, 35, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,40,0);
    glRotatef(10,1,0,0);
    glRotatef(-90,1,0,0);
    gluCylinder(cylinder_rope, 0.5, 0.2, 35, 50, 50);
    glPopMatrix();

    ///right
    glPushMatrix();
    glTranslatef(5,40,0);
    glRotatef(-10,1,0,0);
    glRotatef(-90,1,0,0);
    gluCylinder(cylinder_rope, 0.5, 0.2, 35, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,40,0);
    glRotatef(10,1,0,0);
    glRotatef(-90,1,0,0);
    gluCylinder(cylinder_rope, 0.5, 0.2, 35, 50, 50);
    glPopMatrix();

    ///-z
    glPushMatrix();
    glTranslatef(10,40,5);
    glRotatef(5,1,0,0);
    glRotatef(-5,0,0,1);
    glRotatef(-90,1,0,0);
    gluCylinder(cylinder_rope, 0.5, 0.2, 35, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,40,5);
    glRotatef(5,1,0,0);
    glRotatef(5,0,0,1);
    glRotatef(-90,1,0,0);
    gluCylinder(cylinder_rope, 0.5, 0.2, 35, 50, 50);
    glPopMatrix();

    ///z
    glPushMatrix();
    glTranslatef(10,40,-5);
    glRotatef(-5,1,0,0);
    glRotatef(-5,0,0,1);
    glRotatef(-90,1,0,0);
    gluCylinder(cylinder_rope, 0.5, 0.2, 35, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,40,-5);
    glRotatef(-5,1,0,0);
    glRotatef(5,0,0,1);
    glRotatef(-90,1,0,0);
    gluCylinder(cylinder_rope, 0.5, 0.2, 35, 50, 50);
    glPopMatrix();
    /*glPushMatrix();
    bCurve(44,50,40);
    glPopMatrix();*/
}

void air_balloon()
{
    glPushMatrix();
    glTranslatef(balloon_x, balloon_y, balloon_z);
    //glRotatef(balloon_rotate,0,1,0);
    glPushMatrix();
    balloon();
    rope();
    seat();
    glPopMatrix();
    glPopMatrix();
}

