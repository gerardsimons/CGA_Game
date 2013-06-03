#ifdef WIN32
#include <Windows.h>
#endif
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "traqueboule.h"
#include "mesh.h"
#include "terrain.h"



//std::vector<SpaceShip>

using namespace std;

unsigned int W_fen = 800;  // largeur fenetre
unsigned int H_fen = 800;  // hauteur fenetre
int zNear = 1;
int zFar = 10;

float BackgroundColor[]={0,0,0};

float LightPos[4] = {0,3,2,1};
std::vector<Vec3Df> LightColor;

Vec3Df CamPos = Vec3Df(0.0f,2.0f,-4.0f);

//vector<float> SurfaceVertices3f;

Terrain *terrain;

void drawSurface();
void drawLight();

//SpaceShip * s = new SpaceShip();


void keyboard(unsigned char key, int x, int y)
{
    printf("key %d pressed at %d,%d\n",key,x,y);
}





/************************************************************
 * Appel des diff\E9rentes fonctions de dessin
************************************************************/


void dealWithUserInput(int x, int y)
{

}

void draw( )
{
	//glutSolidSphere(1.0 ,10,10);
	glLightfv(GL_LIGHT0,GL_POSITION,LightPos);
	drawLight();
	drawSurface();
	drawLight();
}

void idle()
{
	CamPos=getCameraPosition();
	glutPostRedisplay();
}


void createTerrain(int xSize, int ySize, float surfaceSize)
{
	//12 vertices per loop
	
	terrain = new Terrain(xSize,ySize,surfaceSize);
	//Move to terrain class
}

void drawSurface()
{
	//printf("-------------------|| DRAW SURFACE ||-------------------\n");
	//printf("Triangle %d\n",t/3);
	//Moved to terrain
	terrain->display();
	//printf("--------------------------------------------------------\n");
}

void display(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);


/************************************************************
 * Programme principal
 ************************************************************/
int main(int argc, char** argv)
{
    glutInit (&argc, argv);


    // couches du framebuffer utilisees par l'application
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

    // position et taille de la fenetre
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(W_fen,H_fen);
    glutCreateWindow(argv[0]);	

    // Initialisation du point de vue
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,-4);
    tbInitTransform();     // initialisation du point de vue
    tbHelp();                      // affiche l'aide sur la traqueboule

    //glDisable( GL_LIGHTING );
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    
    //ss->display();


    createTerrain(10,10,1);
    // cablage des callback
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMouseFunc(tbMouseFunc);    // traqueboule utilise la souris
    glutMotionFunc(tbMotionFunc);  // traqueboule utilise la souris
    glutIdleFunc(idle);


    glEnable( GL_LIGHTING );
        glEnable( GL_LIGHT0 );
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_NORMALIZE);


    // Details sur le mode de trac\E9
    glEnable( GL_DEPTH_TEST );            // effectuer le test de profondeur
    glShadeModel(GL_SMOOTH);

    // Effacer tout
    glClearColor (BackgroundColor[0],BackgroundColor[1], BackgroundColor[2], 0.0);
    glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT); // la couleur et le z
   

    // lancement de la boucle principale
    glutMainLoop();

    return 0;  // instruction jamais ex\E9cut\E9e
}

//function to draw coordinate axes with a certain length (1 as a default)
void drawCoordSystem(float length=1)
{
	//draw simply colored axes

	//remember all states of the GPU
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//deactivate the lighting state
	glDisable(GL_LIGHTING);
	//draw axes
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(length,0,0);

		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,length,0);

		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,length);
	glEnd();

	//reset to previous state
	glPopAttrib();
}


/************************************************************
 * Fonctions de gestion opengl \E0 ne pas toucher
 ************************************************************/
// Actions d'affichage
// Ne pas changer
void display(void)
{
    glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT); // la couleur et le z

	glLoadIdentity();  // repere camera

    tbVisuTransform(); // origine et orientation de la scene

    drawCoordSystem();

    draw();    

    glutSwapBuffers();
}

//function that draws the light source as a sphere
void drawLight()
{
	//remember all states of the GPU
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//deactivate the lighting state
	glDisable(GL_LIGHTING);
	//yellow sphere at light position
	glColor3f(1,1,0);
	glPushMatrix();
	glTranslatef(LightPos[0], LightPos[1], LightPos[2]);
	glutSolidSphere(0.1,6,6);
	glPopMatrix();

	//reset to previous state
	glPopAttrib();
}

// pour changement de taille ou desiconification
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (50, (float)w/h, zNear, zFar);
    glMatrixMode(GL_MODELVIEW);
}

