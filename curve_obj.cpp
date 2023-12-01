#include"main.h"

const int L=50;
const int n1t = 20; //chala
const int n2t = 10;
const int n1theta = 4; //chala
const int n2theta = 20;

GLfloat ctrlpoints[L+1][3] =
{
     {3.8, -3.85, 0}, {4.2, -3.45, 0}, { 4.75, -2.75, 0},
     {5.3, -1.925, 0}, {5.925, -0.825, 0}, {6.2, -0.525, 0},
     {6.25, -0.425, 0}, {6.725, 0.0249999, 0}, //chala nt=20, ntheta=4 0-7

     {2.525, -5.375, 0}, {3.55, -5.025, 0}, {5.725, -3.775, 0},
     {6.7, -2.525, 0}, {7.85, -1.25, 0}, {8.425, -0.55, 0},
     {8.325, -0.0250002, 0}, //pahar 8-14

     {1.35, -0.85, 0}, {1.55, -1.15, 0}, {1.725, -1.525, 0},
     {1.95, -1.925, 0}, {2.3, -2.65, 0}, {3.45, -2.875, 0},
     { 4.85, -2.9, 0}, {5.8, -2.175, 0}, {6.35, -1.5, 0},
     {6.4, -0.8, 0}, {6.4, -0.35, 0}, {6.4, -0.25, 0},
     {6.425, -0.0500001, 0}, // balloon 15-27

     {2.425, -3.15, 0}, {2.1, -3.275, 0}, { 1.8, -3.325, 0},
     {1.425, -3.325, 0}, {1.275, -3.375, 0}, {1.075, -3.4, 0},
     {0.475, -3.55, 0}, {0.025, -3.375, 0}, {-0.325, -2.9, 0},
     {-0.375, -2.625, 0}, {-0.45, -2.275, 0}, {-0.45, -2.05, 0},
     {-0.5, -1.3, 0}, {-0.5, -0.5, 0}, {-0.475, 0.0500002, 0}, // seat 28-32

     {7.575, 1.875, 0}, {6.725, 1.675, 0}, {5.6, 1.5, 0},
     {4.4, 1.1, 0}, {3.375, 0.95, 0}, {2.55, 0.9, 0},
     {2.275, 0.925, 0} // rope 33-39
};

long long nCr(int n, int r)
{
    if(r > n / 2) r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for(i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve ( double t,  float xy[2], int start, int finish)
{
    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0, n=start; i<=(finish-start), n<=finish; i++, n++)
    {
        int ncr=nCr((finish-start),i);
        double oneMinusTpow=pow(1-t,double((finish-start)-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints[n][0];
        y+=coef*ctrlpoints[n][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //return y;
}

///////////////////////
void setNormal(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
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

    glNormal3f(-Nx,-Ny,-Nz);
}

void Bezier(int start, int finish, int nt, int ntheta)
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = ctrlpoints[L][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve( t,  xy, start, finish);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve( t,  xy, start, finish);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= ntheta; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}

void bCurve(int start, int finish, int nt)
{
    int i;
    float x, y, z;
    float x1, y1, z1;

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve( t,  xy, start, finish);
    x = xy[0];
    y = xy[1];
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        t+=dt;
        BezierCurve( t,  xy, start, finish);
        x1 = xy[0];
        y1 = xy[1];
        z=0;
        z1=0;

       glLineWidth(5);
       glBegin( GL_LINE_STRIP );
       glVertex3f (x, y, z);
       glVertex3f (x1, y1, z1);
       glEnd();
        x = x1;
        y = y1;
    }
}
