#ifdef WIN32
#include <Windows.h>
#endif
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "traqueboule.h"

#include "SpaceShip.h"
#include "OpponentSpaceShip.h"
#include "GameSettings.h"

#include "mesh.h"
#include "terrain.h"



//std::vector<SpaceShip>

using namespace std;

unsigned int W_fen = 1200;  // largeur fenetre (default: 800)
unsigned int H_fen = 800;  // hauteur fenetre
int zNear = 1;
int zFar = 10;

// control modes
enum DisplayModeType {GAME=1, CAMERA=2, LIGHT=3};
// set default mode
DisplayModeType displayMode = GAME;

float BackgroundColor[]={0,0,0};

float LightPos[4] = {0,3,2,1};
std::vector<Vec3Df> LightColor;

Vec3Df CamPos = Vec3Df(0.0f,0.0f,-4.0f);

//vector<float> SurfaceVertices3f;

Terrain *terrain;

void createVertices(int,int,float);
void drawSurface();
void drawLight();

//SpaceShip * s = new SpaceShip();

// init player space ship with position
SpaceShip playerSpaceShip;
// opponent space ship vector
std::vector<OpponentSpaceShip> opponents;

void keyboard(unsigned char key, int x, int y)
{
    printf("key %d pressed at %d,%d\n",key,x,y);

	if ((key>='1')&&(key<='9'))
	{
		displayMode = (DisplayModeType) (key- '0');
		printf("Changed mode to %d\n",displayMode);
	}

	switch (displayMode)
	{
		case GAME:
		{
			if(key == 'd') // right
			{
						printf("Move right \n");
						playerSpaceShip.updateX(playerSpaceShip.getPositionX()+.05);

			}
			if(key == 'a') // left
			{
						printf("Move left \n");
						playerSpaceShip.updateX(playerSpaceShip.getPositionX()-.05);

			}
			if(key == 'w')	//up
			{
						printf("Move up \n");
						playerSpaceShip.updateY(playerSpaceShip.getPositionY()+.05);

			}
			if(key == 's')	//down
			{
						printf("Move down \n");
						playerSpaceShip.updateY(playerSpaceShip.getPositionY()-.05);

			}
			if(key == ' ')	//shoot
			{
						printf("Fire!!! \n");
						playerSpaceShip.shoot();
			}
		}
		case CAMERA:
		{
			if(key == 'd') // right
			{
						printf("Move CAM right \n");
						printf("Campos old: %f \n",CamPos[0]);
						CamPos[0] = CamPos[0]+0.1f;
						printf("Campos new: %f \n",CamPos[0]);


			}
			if(key == 'a') // left
			{
						printf("Move CAM  left \n");
						CamPos[0] = CamPos[0]-0.1f;

			}
			if(key == 'w')	//up
			{
						printf("Move CAM  up \n");
						CamPos[0] = CamPos[1]+0.1f;

			}
			if(key == 's')	//down
			{
						printf("Move CAM  down \n");
						CamPos[0] = CamPos[1]-0.1f;

			}

		}
		case LIGHT:
		{

		}
	}



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

	// render player spaceship
	playerSpaceShip.display();

	// render opponent spaceships
	for(unsigned int i = 0; i<opponents.size(); i++)
	{
		//printf("main: draw opponent %f", i);
		opponents.at(i).display();
	}

}

void animate()
{
	/*
	Bullet curBullet;
	// animate player's bullets
	for(unsigned int i = 0; i< playerSpaceShip.getBulletList().size(); i++)
	{
		curBullet = playerSpaceShip.getBulletList().at(i);
		curBullet.updateX( (curBullet.getPositionX()+GameSettings::BULLET_SPEED)  );

	}*/

	// detect collision
	for(unsigned int i = 0; i< playerSpaceShip.getBulletList().size(); i++)
	{
		for(unsigned int j = 0; j< opponents.size(); j++)
		{
			if( playerSpaceShip.getBulletList().at(i).hasCollision( opponents.at(j) ) ) // collision with a bullet?
			{
				// remove opponentSpaceShip
				OpponentSpaceShip curOpp = opponents.at(j);
				opponents.erase(opponents.begin() + j);
				//delete curOpp;

				// remove bullet
				//Bullet curBul = playerSpaceShip.getBulletList().at(i);
				playerSpaceShip.removeBullet(i);
			}
		}
	}

	// animate opponents
	for(unsigned int i = 0; i<opponents.size(); i++)
	{
		opponents.at(i).updateX(opponents.at(i).getPositionX() - GameSettings::OPPONENT_SPEED);
	}

}

void idle()
{
	CamPos=getCameraPosition();
	glutPostRedisplay();
}

void spaceShipSetUp()
{

	// init player spaceship
	playerSpaceShip = SpaceShip(-1,0);

	// init opponents
	opponents.push_back( OpponentSpaceShip(2,0) );
	opponents.push_back( OpponentSpaceShip(2,.5) );
	opponents.push_back( OpponentSpaceShip(2,1) );
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
	//terrain->display();
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
    
    // Game Set Up
    spaceShipSetUp();


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

    animate();

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

