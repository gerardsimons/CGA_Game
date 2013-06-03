#ifdef WIN32
#include <Windows.h>
#endif
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "traqueboule.h"
#include "mesh.h"


using namespace std;

unsigned int W_fen = 800;  // largeur fenetre
unsigned int H_fen = 800;  // hauteur fenetre
int zNear = 1;
int zFar = 10;

float BackgroundColor[]={0,0,0};

std::vector<Vec3Df> LightPos;
std::vector<Vec3Df> LightColor;

Vec3Df CamPos = Vec3Df(0.0f,2.0f,-4.0f);

vector<float> SurfaceVertices3f;

void createVertices(int,int,float);
void drawSurface();

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
	drawSurface();
}

void idle()
{
	CamPos=getCameraPosition();
	glutPostRedisplay();
}


void createTerrain(int xSize, int ySize, float surfaceSize)
{
	//12 vertices per loop
	int i = 0;
	SurfaceVertices3f.resize(ySize * xSize * 12);
	for(float x = 0 ; x < xSize ; x += surfaceSize)
	{
		for(float y = 0 ; y < ySize ; y += surfaceSize)
		{
			
				//define 
			SurfaceVertices3f[i]=x;
			SurfaceVertices3f[i+1]=y;
			SurfaceVertices3f[i+2]=cos(x);

			SurfaceVertices3f[i+3]=x+surfaceSize;
			SurfaceVertices3f[i+4]=y;
			SurfaceVertices3f[i+5]=cos(x+surfaceSize) + sin(y);

			SurfaceVertices3f[i+6]=x+surfaceSize;
			SurfaceVertices3f[i+7]=y+surfaceSize;
			SurfaceVertices3f[i+8]=cos(x+surfaceSize) + sin(y+surfaceSize);

			SurfaceVertices3f[i+9]=x;
			SurfaceVertices3f[i+10]=y+surfaceSize;
			SurfaceVertices3f[i+11]=cos(x) + sin(y+surfaceSize);
			
			i += 12;
		}
	}
}

void drawSurface()
{
	//printf("-------------------|| DRAW SURFACE ||-------------------\n");
	//printf("Triangle %d\n",t/3);
	glBegin(GL_QUADS);
	//printf("SurfaceVertices3f.size() = %d\n",SurfaceVertices3f.size());
	for (int vIndex = 0 ; vIndex < SurfaceVertices3f.size() ; vIndex += 3)
	{
		//glTexCoord2fv(&(SurfaceTexCoords2f[2*vIndex]));
		//glNormal3fv(&(SurfaceNormals3f[3*vIndex]));
		//glColor3fv(&(SurfaceColors3f[3*vIndex]));

		float *vertex = &(SurfaceVertices3f[vIndex]);

		//printf("Drawing vertex #%d = (%f,%f,%f)\n",i,&vertex,&(vertex+1),&(vertex+2));

		glVertex3f(*vertex,*(vertex+1),*(vertex+2));
	}
	glEnd();

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

    glDisable( GL_LIGHTING );
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    
    createTerrain(3,3,1);
    // cablage des callback
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMouseFunc(tbMouseFunc);    // traqueboule utilise la souris
    glutMotionFunc(tbMotionFunc);  // traqueboule utilise la souris
    glutIdleFunc(idle);


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

    draw();    

    glutSwapBuffers();
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

