#ifdef WIN32
#include <Windows.h>
#endif
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "traqueboule.h"
#include "Model.h"

#include "SpaceShip.h"
#include "OpponentSpaceShip.h"
#include "GameSettings.h"

#include "mesh.h"
#include "terrain.h"

#include <time.h>

#include "loadppm.h"



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

// timer
clock_t initTimer;
clock_t shootTimer;

// current FLOW
int CUR_FLOW = 2;

// BOSS FLOW ??
bool bossEnabled = false;

float BackgroundColor[]={0,0,0};

void updateCamera();

Terrain *terrain;
Model *boss;

void drawLights();

//SpaceShip * s = new SpaceShip();

// init player space ship with position
SpaceShip playerSpaceShip;
// opponent space ship vector
std::vector<OpponentSpaceShip> opponents;

void keyboard(unsigned char key, int x, int y)
{
    //printf("key %d pressed at %d,%d\n",key,x,y);

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
						playerSpaceShip.updateX(playerSpaceShip.getPositionX()+.05);
						playerSpaceShip.getAssistent()->updatePivot(
								(playerSpaceShip.getPositionX()+(GameSettings::AIRPLANE_SIZE[0]/2)),
								(playerSpaceShip.getPositionY()+(GameSettings::AIRPLANE_SIZE[1]/2))
						);


			}
			if(key == 'a') // left
			{
						playerSpaceShip.updateX(playerSpaceShip.getPositionX()-.05);
						playerSpaceShip.getAssistent()->updatePivot(
								(playerSpaceShip.getPositionX()+(GameSettings::AIRPLANE_SIZE[0]/2)),
								(playerSpaceShip.getPositionY()+(GameSettings::AIRPLANE_SIZE[1]/2))
						);

			}
			if(key == 'w')	//up
			{
						playerSpaceShip.updateY(playerSpaceShip.getPositionY()+.05);
						playerSpaceShip.getAssistent()->updatePivot(
								(playerSpaceShip.getPositionX()+(GameSettings::AIRPLANE_SIZE[0]/2)),
								(playerSpaceShip.getPositionY()+(GameSettings::AIRPLANE_SIZE[1]/2))
						);

			}
			if(key == 's')	//down
			{
						playerSpaceShip.updateY(playerSpaceShip.getPositionY()-.05);
						playerSpaceShip.getAssistent()->updatePivot(
								(playerSpaceShip.getPositionX()+(GameSettings::AIRPLANE_SIZE[0]/2)),
								(playerSpaceShip.getPositionY()+(GameSettings::AIRPLANE_SIZE[1]/2))
						);

			}
			if(key == ' ')	//shoot
			{
					printf("Fire!!! \n");
					playerSpaceShip.shoot();
			}
			break;
		}
		case CAMERA:
		{
			if(key == 'd') // right
			{

						GameSettings::updateCamera(0.1f,0.0f,0.0f);
			}
			if(key == 'a') // left
			{

						GameSettings::updateCamera(-0.1f,0.0f,0.0f);

			}
			if(key == 'w')	//up
			{
						GameSettings::updateCamera(0.0f,0.1f,0.0f);

			}
			if(key == 's')	//down
			{
						GameSettings::updateCamera(0.0f,-0.1f,0.0f);

			}
			if(key == 'z') // right
			{

						GameSettings::updateCamera(0.0f,0.0f,0.1f);
			}
			if(key == 'x') // left
			{

						GameSettings::updateCamera(0.0f,0.0f,-0.1f);

			}
			if(key == 'h') //xRot
			{

				GameSettings::updateCameraRot(1.0f,0.0f,0.0f);
			}
			if(key == 'j')
			{

				GameSettings::updateCameraRot(-1.0f,0.0f,0.0f);

			}
			if(key == 'i') //yRot
			{

				GameSettings::updateCameraRot(0.0f,1.0f,0.0f);
			}
			if(key == 'k') // left
			{
				GameSettings::updateCameraRot(0.0f,-1.0f,0.0f);

			}
			if(key == 'o') // right
			{
				GameSettings::updateCameraRot(0.0f,0.0f,1.0f);
			}
			if(key == 'l') // left
			{

				GameSettings::updateCameraRot(0.0f,0.0f,0.1f);

			}
			if(key == 'p') // toggle specular lighting
			{

				LightManager::SpecularHardness += 0.05f;

			}
			updateCamera();
			break;

		}
		case LIGHT:
		{
			break;
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
	drawLights();
	// render player spaceship
	playerSpaceShip.display();

	// render opponent spaceships
	for(unsigned int i = 0; i<opponents.size(); i++)
	{
		//printf("main: draw opponent %f", i);
		opponents.at(i).display();
	}

	terrain->display();
	boss->drawModel();
	boss->drawBossBullets();

	// render assistent
	playerSpaceShip.getAssistent()->display();

}

/**
 * Call this when you changed the camera position so that OpenGL redraws the scene
 */
void updateCamera()
{
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    Vec3Df CamPos = GameSettings::CamPos;
    Vec3Df CamRot = GameSettings::CamRot;
    printf("CamPos=(%f,%f,%f)\n",CamPos[0],CamPos[1],CamPos[2]);
    //xRot
    //glPushMatrix();
    glTranslatef(-CamPos[0],-CamPos[1],-CamPos[2]);

    glRotatef(CamRot[0],1,0,0);
    glRotatef(CamRot[1],0,1,0);
    glRotatef(CamRot[2],0,0,1);
}

void animate()
{

	//Light animations
	LightManager::animateLights();

	//boss->rotate(0.0f,0.7f,0.0f);
	// TODO: doesnt work yet
	if(bossEnabled == true && (boss->getPositionX() > 3.0f) )
	{
		boss->move(-0.02f, 0.0f, 0.0f);
	}

	// animate player's bullets
	for(unsigned int i = 0; i< playerSpaceShip.getBulletList()->size(); i++)
	{
		Bullet curBullet = playerSpaceShip.getBulletList()->at(i);
		playerSpaceShip.getBulletList()->at(i).updateX( curBullet.getPositionX()+GameSettings::BULLET_SPEED  );
	}

	// TODO: SIMPLIFY... // not working propper..., still called in OpponentSpaceShip

	// animate opponent's bullets
	for (unsigned int j = 0; j< opponents.size(); j++ )
	{
		for(unsigned int i = 0; i< opponents.at(j).getBulletList()->size(); i++)
		{
			Bullet curBullet = opponents.at(j).getBulletList()->at(i);
			opponents.at(j).getBulletList()->at(i).updateX( curBullet.getPositionX()-GameSettings::BULLET_SPEED  );
		}
	}
	// animate final boss' bullets
	for(unsigned int i = 0; i< boss->getBulletList()->size(); i++)
	{
		Bullet curBullet = boss->getBulletList()->at(i);
		boss->getBulletList()->at(i).updateX( curBullet.getPositionX()-GameSettings::BULLET_SPEED  );
	}

	// animate assistent
	// TODO: currently in the Assistentclass


	// BUG: multiple planes on same position --> bullit collision -> error
	std::vector< int > dumpBulList;
	std::vector< int > dumpOppList;
	/*
	 * BULLET --> OPPONENT // ASSISTENT UPDATE
	 */

	// detect collision
	for(unsigned int i = 0; i<playerSpaceShip.getBulletList()->size(); i++)
	{
		if(playerSpaceShip.getBulletList()->at(i).outOfRange() )	// bullit out of range ?
		{
			// register in order to avoid problems within the for loop
			dumpBulList.push_back( i );
		}
		else
		{
			for (unsigned int j = 0; j< opponents.size(); j++ )
			{
				if( playerSpaceShip.getBulletList()->at(i).hasCollision( opponents.at(j) ) ) // collision with a bullet?
				{
					// register in order to avoid problems within the for loop
					dumpOppList.push_back( j );
					dumpBulList.push_back( i );
				}
			}
		}

	}
	// remove bullets
	for(unsigned int i = 0; i< dumpBulList.size(); i++)
	{
		playerSpaceShip.removeBullet( dumpBulList.at(i) );
	}
	dumpBulList.clear();
	// remove opponents
	for(unsigned int i = 0; i< dumpOppList.size(); i++)
	{
		opponents.erase( opponents.begin() + dumpOppList.at(i) );
	}
	dumpOppList.clear();


	/*
	 * OPPONENT BULLET --> PLAYER
	 */

	// detect collision
	for (unsigned int j = 0; j< opponents.size(); j++ )
	{
		for(unsigned int i = 0; i<opponents.at(j).getBulletList()->size(); i++)
		{

			if( opponents.at(j).getBulletList()->at(i).hasCollision( playerSpaceShip.getAssistent() ) )	// bullit out of range ?
			{
				printf("# BAM!!! Saved by the bell =) \n");
				// register in order to avoid problems within the for loop
				dumpBulList.push_back( i );
			}

			if( opponents.at(j).getBulletList()->at(i).hasCollision( playerSpaceShip ) ) // collision with a bullet?
			{
				// register in order to avoid problems within the for loop
				printf("# Collision with bullet: WE ARE HIT!! \n");
				dumpBulList.push_back( i );
			}
		}

		// remove bullets
		for(unsigned int i = 0; i< dumpBulList.size(); i++)
		{
			opponents.at(j).removeBullet( dumpBulList.at(i) );
		}
		dumpBulList.clear();
	}

	/*
	 * SHIP --> OPPONENT UPDATE
	 */
	for (unsigned int j = 0; j< opponents.size(); j++ )
	{
		if( playerSpaceShip.hasCollision( opponents.at(j) ) ) // collision with an opponent
		{
			// register in order to avoid problems within the for loop
			printf("game over!! \n");
		}
	}

	// animate opponents
	for(unsigned int i = 0; i<opponents.size(); i++)
	{
		opponents.at(i).updateX(opponents.at(i).getPositionX() - GameSettings::OPPONENT_SPEED);
	}

}

void opponentFlow()
{
	//printf(" ### cur flow: %i \n", CUR_FLOW);
	clock_t currentTimer = clock();

	if( opponents.size() <= 1 )
	{
		//printf("t waiting: %f \n", ((float)currentTimer-(float)initTimer));
		if( ( (float)currentTimer - (float)initTimer ) > GameSettings::NEXT_FLOW_TIME/5 )
		{
			// TODO introduce randomly with random directions...
			initTimer = currentTimer;

			if( CUR_FLOW >= GameSettings::NUMBER_OF_FLOWS )
			{
				// TODO eindbaas
				bossEnabled = true;
			}
			else
			{

				float max = CUR_FLOW;
				if(CUR_FLOW > 4) { max = 4; }
				float incrX = 0.0f;

				// flow
				for( signed int i = 1; i<=CUR_FLOW; i++ )
				{
					incrX = 1.0f*floor(i/ (max+.05));
					int j = i % ((int)max);
					OpponentSpaceShip oppShip = OpponentSpaceShip(4+incrX, float( (j/max )*1.5 ) );
					opponents.push_back( oppShip );
					//oppShip.shoot();
					clock_t shootTimer = clock();
				}

			}
			CUR_FLOW++;
		}
	}
	// opponent spaceships shoot
	// TODO dirty fix CUR_FLOW-1
	if( (CUR_FLOW-1) < GameSettings::NUMBER_OF_FLOWS && ( (float)currentTimer - (float)shootTimer ) > GameSettings::NEXT_FLOW_TIME )
	{
		printf(" OppSpaceShip: INCOMING \n");
		shootTimer = currentTimer;
		for(unsigned int i = 0; i<opponents.size(); i++)
		{
			opponents.at(i).shoot();
		}
	}
	// final boss shoots
	// TODO dirty fix CUR_FLOW-1
	else if( (CUR_FLOW-1) >= GameSettings::NUMBER_OF_FLOWS && ( (float)currentTimer - (float)shootTimer ) > GameSettings::NEXT_FLOW_TIME )
	{
		shootTimer = currentTimer;
		printf(" BOSS: INCOMING \n");
		boss->shoot();
	}

}

void initLights()
{
	//LightManager::addLight(GameSettings::CamPos,Vec3Df(1,1,1),Vec3Df(1,1,1),10.0f,10.0f);
	//LightManager::addLight(Vec3Df(3,3,0),Vec3Df(1,1,1),Vec3Df(1,1,1),10.0f,10.0f);

	LightManager::addLight(Vec3Df(2,3,0),Vec3Df(1,1,1),Vec3Df(1,1,1),0.0f,5.0f);
	//LightManager::addLight(Vec3Df(3,3,0),Vec3Df(1,1,1),Vec3Df(1,1,1),0.0f,5.0f);
	//LightManager::addLight(Vec3Df(6,3,0),Vec3Df(1,1,1),Vec3Df(1,1,1),0.0f,5.0f);
}

void initTextures()
{

		GameSettings::Texture.resize(4);
		GameSettings::Texture[0]=0;
		GameSettings::Texture[1]=0;
		GameSettings::Texture[2]=0;
		GameSettings::Texture[3]=0;

		PPMImage image("ufo.ppm");
		glGenTextures(1, &GameSettings::Texture[0]);
		glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[0]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.sizeX, image.sizeY,
			GL_RGB, GL_UNSIGNED_BYTE, image.data);
		glBindTexture(GL_TEXTURE_2D, 0);

		PPMImage image2("ufo_opp.ppm");
		glGenTextures(1, &GameSettings::Texture[1]);
		glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[1]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image2.sizeX, image2.sizeY,
			GL_RGB, GL_UNSIGNED_BYTE, image2.data);
		glBindTexture(GL_TEXTURE_2D, 1);

		PPMImage image3("bullet.ppm");
		glGenTextures(1, &GameSettings::Texture[2]);
		glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[2]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image3.sizeX, image3.sizeY,
			GL_RGB, GL_UNSIGNED_BYTE, image3.data);
		glBindTexture(GL_TEXTURE_2D, 1);

		PPMImage imageSand("sand.ppm");
		glGenTextures(1, &GameSettings::GameSettings::Texture[3]);
		glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[3]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, imageSand.sizeX, imageSand.sizeY,
			GL_RGB, GL_UNSIGNED_BYTE, imageSand.data);
		glBindTexture(GL_TEXTURE_2D, 0);
}

void idle()
{
	glutPostRedisplay();
}

void spaceShipSetUp()
{

	// init player spaceship
	playerSpaceShip = SpaceShip(-1,0);

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

    updateCamera();

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    
    // Game Set Up
    spaceShipSetUp();

    terrain = new Terrain(20,20,0.2f,-10.0f,-8.0f);


    initTextures();

    boss = new Model("ufo_v3.obj",6,1,1);
    //boss = new Model("DavidHeadCleanMax.obj",0,0,0);

    // set initial timer
    initTimer = clock();


    // cablage des callback
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMouseFunc(tbMouseFunc);    // traqueboule utilise la souris
    glutMotionFunc(tbMotionFunc);  // traqueboule utilise la souris
    glutIdleFunc(idle);

    initLights();

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
		//Red is x
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(length,0,0);
		//green is y
		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,length,0);
		//blue is z
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

    /*
    glLoadIdentity();  // repere camera
    tbVisuTransform(); // origine et orientation de la scene
    */

    drawCoordSystem();

    opponentFlow();

    animate();

    draw();    

    glutSwapBuffers();
}

//function that draws the light source as a sphere
void drawLights()
{
	//remember all states of the GPU
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//deactivate the lighting state
	glDisable(GL_LIGHTING);

	for(int i = 0 ; i < LightManager::LightPos.size() ; i++)
	{
		Vec3Df LightPos = LightManager::LightPos[i];
		Vec3Df LightColor = LightManager::DiffuseColor[i];
		//yellow sphere at light position
		glColor3f(LightColor[0],LightColor[1],LightColor[2]);
		glPushMatrix();
		glTranslatef(LightPos[0], LightPos[1], LightPos[2]);
		glutSolidSphere(0.1,6,6);
		glPopMatrix();
	}
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
    //updateCamera();
}

