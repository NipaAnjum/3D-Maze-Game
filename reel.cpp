#include"main.h"

GLfloat red, green, blue;
int r = 0;
int b = 0;
int g = 0;

void draw_hub(void)
{
    GLUquadricObj *hub_sphere = gluNewQuadric();

    glPushMatrix();

    glScalef(10,10,10);
    glRotatef (rotat, 0.0f, 0.0f, 1.0f);

    properties(0.412, 0.412, 0.412,true,60);
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, hub);

    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, textureID[7]);
    glEnable(GL_TEXTURE_2D);
    glutSolidTorus (1, 2, 60, 40); //inner hub ring
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);

    //pivot, just add more detail and make the middle look cool
    glEnable(GL_TEXTURE_2D);
    gluQuadricTexture(hub_sphere, true);
    glBindTexture(GL_TEXTURE_2D,textureID[7]);
    glPushMatrix();
    glScalef(1.0, 1.0, 2.0);
    glPushMatrix();
    gluSphere(hub_sphere, 2, 30, 30); // this one forms a nice central hub
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

}

void draw_rings(void)
{
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,textureID[7]);
    glPushMatrix();

    properties(0.412, 0.412, 0.412,true,60);

    glScalef(10,10,10);
    glRotatef (rotat, 0.0f, 0.0f, 1.0f);

    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[7]);
    glPushMatrix();
    glTranslatef (0.0, 0.0, -0.15);
    glutSolidTorus (0.3, 15, 60, 40); //outer ring closer
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, textureID[7]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef (0.0, 0.0, 0.15); //outer ring further
    glutSolidTorus (0.3, 15, 60, 40);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
}

void draw_spokes(void)
{
    glEnable(GL_TEXTURE_2D);
    int x = 0;

    GLUquadricObj *adamsQuad = gluNewQuadric();

    gluQuadricTexture(adamsQuad, true);
    glBindTexture(GL_TEXTURE_2D,textureID[7]);

    glPushMatrix();
    glScalef(10,10,10);
    glRotatef (rotat, 0.0f, 0.0f, 1.0f); //rotation call

    glPushMatrix();

    properties(0.184, 0.310, 0.310,true,60);

    for(x=0; x<350; x++) //for loop, goes round entire wheel
    {
        glPushMatrix();
        glTranslatef (0.0, 0.0, 0.15);
        glRotatef (90, 1.0, 0.0, 0.0);
        glRotatef (x, 0.0, 1.0, 0.0);
        gluCylinder(adamsQuad, 0.5, 0.05, 15, 5, 5);
        glPopMatrix();

        x+=20;

        //spokes drawn at 20 degree intervals
    }


    //same again, but for other side
    for(x=0; x<350; x++)
    {
        glPushMatrix();
        glTranslatef (0.0, 0.0, -0.15);
        glRotatef (90, 1.0, 0.0, 0.0);
        glRotatef (x, 0.0, 1.0, 0.0);
        gluCylinder(adamsQuad, 0.5, 0.05, 15, 5, 5);
        glPopMatrix();

        x+=20;
    }


    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void random_colour(void)
{
    for(int a = 0; a<20; a++)
    {
        //three random numbers generated to give differing values of red, green and blue
        r = ((rand() % 500) + 1);
        g = ((rand() % 500) + 1);
        b = ((rand() % 500) + 1);

        red = (r/100); //convert integers to decimal values
        green = (g/100);
        blue = (b/100);
        properties(red, green, blue, true, 128);
    }
}

void draw_pods(void)
{
    GLUquadricObj *pod = gluNewQuadric();
    int z = 0;

    glPushMatrix();
    glScalef(10,10,10);

    glPushMatrix();
    glRotatef (rotat, 0.0f, 0.0f, 1.0f);

    for(z=0; z<350; z++)
    {

        glEnable(GL_TEXTURE_2D);
        gluQuadricTexture(pod, true);
        glBindTexture(GL_TEXTURE_2D,textureID[7]);
        glPushMatrix();
        glRotatef(z, 0.0, 0.0, 1.0);
        glTranslatef(16.5, 0.0, 0.0);
        glScalef(10.0, 10.0, 13.0);
        random_colour();  //call the colour method
        gluSphere(pod, 0.12, 15, 15);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        //glEnable(GL_TEXTURE_2D);
        //glBindTexture(GL_TEXTURE_2D,textureID[7]);
        glPushMatrix();
        glRotatef(z, 0.0, 0.0, 1.0);
        glTranslatef(16.5, 0.0, 0.0);
        glScalef(10.0, 10.0, 13.0);
        properties(0.000, 0.000, 0.000,true,60);
        glutWireSphere(0.13, 10, 8);
        glPopMatrix();
        //glDisable(GL_TEXTURE_2D);
        z+=20;
    }

    glPopMatrix();
    glPopMatrix();
}

//supporting stand of the eye
//
void draw_stand(void)
{
    glEnable(GL_TEXTURE_2D);
    GLUquadricObj *myStand = gluNewQuadric();

    gluQuadricTexture(myStand, true);
    glBindTexture(GL_TEXTURE_2D,textureID[7]);

    properties(0.412, 0.412, 0.412,true,60);

    glPushMatrix();
    glScalef(10,10,10);
    // move both cylinders behind the eye
    glTranslatef(0.0, 0.0, -0.3);

    // rotate, so they are at an angle
    glPushMatrix();
    glRotatef (105, 1.0, 0.0, 0.0);
    glRotatef (20, 0.0, 1.0, 0.0);
    gluCylinder(myStand, 1.5, 1.4, 23, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glRotatef (105, 1.0, 0.0, 0.0);
    glRotatef (-20, 0.0, 1.0, 0.0);
    gluCylinder(myStand, 1.5, 1.4, 23, 10, 10);
    glPopMatrix();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void draw_reel(void)
{
    glPushMatrix();
    glTranslatef(0,200,-300);
    glPushMatrix();
    draw_hub();
    draw_rings();
    draw_spokes();
    draw_pods();
    draw_stand();
    glPopMatrix();
    glPopMatrix();
}
