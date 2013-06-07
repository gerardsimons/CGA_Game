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
#include "Background.h"

#include "BMPImage.h"

#include "mesh.h"
#include "terrain.h"

#include <time.h>

#include "loadppm.h"


//std::vector<SpaceShip>

using namespace std;

unsigned int W_fen = 1200;  // largeur fenetre (default: 800)
unsigned int H_fen = 800;  // hauteur fenetre
int zNear = 1;
int zFar = 400;

float rotateX = 0;
float rotateY = 0;
int mouseX,mouseY;

// control modes
enum DisplayModeType {GAME=1, CAMERA=2, LIGHT=3};
// set default mode
DisplayModeType displayMode = GAME;

// timer
clock_t initTimer;
clock_t shootTimer;
clock_t playerShootTimer = 0;

bool WIN = false;

// current FLOW
int CUR_FLOW = 2;
//int CUR_FLOW = GameSettings::NUMBER_OF_FLOWS+1; // skip directly to final boss

// ANIMATION STEP BOSS
float sinX = 0.0;

// BOSS FLOW ??
bool bossEnabled = false;

float BackgroundColor[]={0,0,0};

void updateCamera();

std::vector<Terrain> terrains;
Model *boss;
Background *background;

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
			if(WIN == false)
			{
				if(key == 'd') // right
				{
							//printf("Move right \n");
							playerSpaceShip.updateX(playerSpaceShip.getPositionX()+.05);
							playerSpaceShip.getAssistent()->updatePivot(
									(playerSpaceShip.getPositionX()+(GameSettings::AIRPLANE_SIZE[0]/2)),
									(playerSpaceShip.getPositionY()+(GameSettings::AIRPLANE_SIZE[1]/2))
							);


				}
				if(key == 'a') // left
				{
							//printf("Move left \n");
							playerSpaceShip.updateX(playerSpaceShip.getPositionX()-.05);
							playerSpaceShip.getAssistent()->updatePivot(
									(playerSpaceShip.getPositionX()+(GameSettings::AIRPLANE_SIZE[0]/2)),
									(playerSpaceShip.getPositionY()+(GameSettings::AIRPLANE_SIZE[1]/2))
							);

				}
				if(key == 'w')	//up
				{
							//printf("Move up \n");
							playerSpaceShip.updateY(playerSpaceShip.getPositionY()+.05);
							playerSpaceShip.getAssistent()->updatePivot(
									(playerSpaceShip.getPositionX()+(GameSettings::AIRPLANE_SIZE[0]/2)),
									(playerSpaceShip.getPositionY()+(GameSettings::AIRPLANE_SIZE[1]/2))
							);

				}
				if(key == 's')	//down
				{
							//printf("Move down \n");
							playerSpaceShip.updateY(playerSpaceShip.getPositionY()-.05);
							playerSpaceShip.getAssistent()->updatePivot(
									(playerSpaceShip.getPositionX()+(GameSettings::AIRPLANE_SIZE[0]/2)),
									(playerSpaceShip.getPositionY()+(GameSettings::AIRPLANE_SIZE[1]/2))
							);

				}
				if(key == ' ')	//shoot
				{
					printf("is locked ? %i \n", playerSpaceShip.isLocked());
					if(!playerSpaceShip.isLocked())
					{
						//printf("Fire!!! \n");
						playerSpaceShip.shoot();
						playerShootTimer = clock();
					}
				}

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
	background->draw();

	//Draw terrains
	for(int i = 0 ; i < terrains.size() ; i++)
	{
		terrains[i].display();
	}

	drawLights();
	// render player spaceship
	playerSpaceShip.display();


	// render opponent spaceships
	for(unsigned int i = 0; i<opponents.size(); i++)
	{
		//printf("main: draw opponent %f", i);
		opponents.at(i).display();
	}

	if(bossEnabled)
	{
		printf("Drawing boss...\n");
		boss->drawModel();
		boss->drawBossBullets();
	}

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

    //Set light to camera for testing;
    //LightManager::LightPos[0] = CamPos;

    //printf("CamPos=(%f,%f,%f)\n",CamPos[0],CamPos[1],CamPos[2]);
    //xRot
    //glPushMatrix();
    glTranslatef(-CamPos[0],-CamPos[1],-CamPos[2]);

    glRotatef(CamRot[0],1,0,0);
    glRotatef(CamRot[1],0,1,0);
    glRotatef(CamRot[2],0,0,1);
}

void animate()
{
	if(WIN && playerSpaceShip.getPositionX()<5)
	{
		playerSpaceShip.updateX(playerSpaceShip.getPositionX()+.05);
		playerSpaceShip.getAssistent()->updatePivot(
				(playerSpaceShip.getPositionX()+(GameSettings::AIRPLANE_SIZE[0]/2)),
				(playerSpaceShip.getPositionY()+(GameSettings::AIRPLANE_SIZE[1]/2))
		);
	}

	/*
	 * BULLET LOCK
	 */
	clock_t currentTimer = clock();
	printf("-BULLET LOCK CHECK; cur[ %f ] - pstime[ %f ] > BUL_LOCK[ %f ]\n", (float)currentTimer, (float)playerShootTimer, GameSettings::BULLET_LOCK );
	printf("-RESULT; %f > BUL_LOCK[ %f ]\n", ((float)currentTimer-(float)playerShootTimer), GameSettings::BULLET_LOCK );
	if( ( (float)currentTimer - (float)playerShootTimer ) > GameSettings::BULLET_LOCK && playerSpaceShip.isLocked() )
	{
		//printf("unlocked\n");
		// playerShootTimer = (float)currentTimer;
		playerSpaceShip.setBulletLock(false);
	}
	else if ( ((float)currentTimer - (float)playerShootTimer) <= GameSettings::BULLET_LOCK && !playerSpaceShip.isLocked() )
	{
		//printf("locked\n");
		playerSpaceShip.setBulletLock(true);
	}

	//LightManager::moveLight(0,.1f,0,0);


	if(bossEnabled == true && (boss->getPositionX() > 3.0f) )
	{
		boss->move(-0.02f, 0.0f, 0.0f);
	}
	else if(bossEnabled == true && (boss->getPositionX() <= 3.0f) )
	{
		sinX+=0.1f;
		boss->moveToY(((float)0.5*sin(sinX)+1.0f));
		// TODO: vary x
		//boss->moveToX(((float)0.5*sin(sinX)+3.0f));
	}

	// animate player's bullets
	for(unsigned int i = 0; i< playerSpaceShip.getBulletList()->size(); i++)
	{
		Bullet curBullet = playerSpaceShip.getBulletList()->at(i);
		playerSpaceShip.getBulletList()->at(i).updateX( curBullet.getPositionX()+GameSettings::BULLET_SPEED  );
	}

	// TODO: SIMPLIFY... // not working proper..., still called in OpponentSpaceShip

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
				if( playerSpaceShip.getBulletList()->at(i).hasCollision( opponents.at(j) ) ) // hit opponentSpaceShip?
				{
					// register in order to avoid problems within the for loop
					dumpOppList.push_back( j );
					dumpBulList.push_back( i );
				}
			}
			if( bossEnabled )
			{
				//printf("Positions PLAYER: %f;  %f\n", playerSpaceShip.getPositionX(), playerSpaceShip.getPositionY());
				//printf("Positions BOSS: %f;  %f\n", boss->getPositionX(), boss->getPositionY());
				if( playerSpaceShip.getBulletList()->at(i).hasCollision( boss ) ) // hit Final Boss?
				{
					// register in order to avoid problems within the for loop
					dumpBulList.push_back( i );
					boss->decreaseHealth();
					printf( "BOSS HEALTH %f \n", boss->getHealth() );
					if( boss->getHealth() <= 0 )
					{
						bossEnabled = false;

						printf("YOU WIN");

						WIN = true;
						//TODO boss needs to be killed
						//boss->kill();
					}
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
				playerSpaceShip.decreaseHealth();
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
	 * FINAL BOSS BULLET --> PLAYER UPDATE
	 */
	for(unsigned int i = 0; i< boss->getBulletList()->size(); i++)
	{
		Bullet curBullet = boss->getBulletList()->at(i);
		if( curBullet.hasCollision( playerSpaceShip.getAssistent() ) )	// bullet out of range ?
		{
			printf("# BAM!!! Saved by the bell =) \n");
			// register in order to avoid problems within the for loop
			dumpBulList.push_back( i );
		}

		if( curBullet.hasCollision( playerSpaceShip ) ) // collision with a bullet?
		{
			// register in order to avoid problems within the for loop
			printf("# Collision with bullet of FINAL BOSS: WE ARE HIT!! \n");
			playerSpaceShip.decreaseHealth();
			dumpBulList.push_back( i );
		}

	}
	// remove bullets
	for(unsigned int i = 0; i< dumpBulList.size(); i++)
	{
		boss->removeBullet( dumpBulList.at(i) );
	}
	dumpBulList.clear();
	// remove opponents
	for(unsigned int i = 0; i< dumpOppList.size(); i++)
	{
		opponents.erase( opponents.begin() + dumpOppList.at(i) );
	}
	dumpOppList.clear();


	/*
	 * SHIP --> OPPONENT UPDATE
	 */
	for (unsigned int j = 0; j< opponents.size(); j++ )
	{
		if( playerSpaceShip.hasCollision( opponents.at(j) ) ) // collision with an opponent
		{
			printf("Collision with opponent \n");
			// register in order to avoid problems within the for loop
			playerSpaceShip.decreaseHealth();
			dumpOppList.push_back( j );
		}
	}
	// remove opponents
	for(unsigned int i = 0; i< dumpOppList.size(); i++)
	{
		opponents.erase( opponents.begin() + dumpOppList.at(i) );
	}
	dumpOppList.clear();

	/*
	 * OPPONENT --> ASSISTENT SPACESHIP
	 */
	for (unsigned int j = 0; j< opponents.size(); j++ )
	{
		if( opponents.at(j).hasCollision( playerSpaceShip.getAssistent() ) ) // assisten hits opponent?
		{
			printf("Assistent collision with opponent \n");
			// register in order to avoid problems within the for loop
			dumpOppList.push_back( j );
		}
	}
	// remove opponents
	for(unsigned int i = 0; i< dumpOppList.size(); i++)
	{
		opponents.erase( opponents.begin() + dumpOppList.at(i) );
	}
	dumpOppList.clear();



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
				if ( (boss->getHealth() > 0) )
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
	else if( (CUR_FLOW-1) >= GameSettings::NUMBER_OF_FLOWS &&
			 ((float)currentTimer - (float)shootTimer ) > GameSettings::NEXT_FLOW_TIME &&
			 bossEnabled
			)
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

	LightManager::addLight(Vec3Df(0,3,0),Vec3Df(1.0f,1.0f,1.0f),Vec3Df(1.0f,1.0f,1.0f),1.0f,1.0f);


	//LightManager::addLight(Vec3Df(3,3,0),Vec3Df(1,1,1),Vec3Df(1,1,1),0.0f,5.0f);
	//LightManager::addLight(Vec3Df(6,3,0),Vec3Df(1,1,1),Vec3Df(1,1,1),0.0f,5.0f);
}

void initTextures()
{

		GameSettings::Texture.resize(6);
		GameSettings::Texture[0]=0;
		GameSettings::Texture[1]=0;
		GameSettings::Texture[2]=0;
		GameSettings::Texture[3]=0;
		GameSettings::Texture[4]=0;
		GameSettings::Texture[5]=0;

		BMPImage image("ufo_small.bmp",true);
		glGenTextures(1, &GameSettings::GameSettings::Texture[0]);
		glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[0]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.width, image.height,GL_RGBA, GL_UNSIGNED_BYTE, image.data);

		BMPImage image2("ufo_opp_small.bmp",true);
		glGenTextures(1, &GameSettings::GameSettings::Texture[1]);
		glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[1]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image2.width, image2.height,GL_BGRA, GL_UNSIGNED_BYTE, image2.data);


		BMPImage image3("bullet_small.bmp",true);
		glGenTextures(1, &GameSettings::GameSettings::Texture[2]);
		glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[2]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image3.width, image3.height,GL_BGRA, GL_UNSIGNED_BYTE, image3.data);

		PPMImage imageSand("sand.ppm");
		glGenTextures(1, &GameSettings::Texture[3]);
		glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[3]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, imageSand.sizeX, imageSand.sizeY,
			GL_RGB, GL_UNSIGNED_BYTE, imageSand.data);

		BMPImage image4("ufo_assistent_small.bmp",true);
		glGenTextures(1, &GameSettings::GameSettings::Texture[4]);
		glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[4]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image4.width, image4.height,GL_RGBA, GL_UNSIGNED_BYTE, image4.data);

		printf("Loading the universe dude...");

		BMPImage galaxyImg("galaxy24bit.bmp",false);
		glGenTextures(1, &GameSettings::GameSettings::Texture[5]);
		glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[5]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, galaxyImg.width, galaxyImg.height,GL_BGR, GL_UNSIGNED_BYTE, galaxyImg.data);

		/*
		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, imageTest.width, imageTest.height,0,
							GL_RGBA, GL_UNSIGNED_BYTE, imageTest.data);*/

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




void mousePassive(int x, int y){
    mouseX = x;
    mouseY = y;
}

void mouseMotion(int x, int y){
    const float SPEED = 2;

    rotateX += (mouseX-x)/SPEED;
    rotateY += (mouseY-y)/SPEED;

    GameSettings::CamRot[1] = rotateX;
    GameSettings::CamRot[0] = rotateY;

    updateCamera();

    mousePassive(x, y);



    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit (&argc, argv);

    // couches du framebuffer utilisees par l'application
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

    //We have our own lighting of course!
    glDisable(GL_LIGHTING);
    // position et taille de la fenetre
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(W_fen,H_fen);
    glutCreateWindow(argv[0]);



    initTextures();


    updateCamera();

    // Game Set Up
    spaceShipSetUp();
    float detail[] = {.125f,.5f};
    float xModifiers[] = {1.0f,3.0f};
    float yModifiers[] = {1.0f,2.0f};
    float zModifiers[] = {1.0f,1.0f};
    float xSizes[] = {20.0f,40.0f};
    float zSizes[] = {20.0f,20.0f};
    float yStart[] = {0.0f,5.0f};
    for(int z = 0 ; z < 1 ; z++)
    {
    	//float yModifier = (float)rand()/(float)RAND_MAX * 2.0f - 0.0f;
    	//quadSize = pow(quadSize,-(z+1));
    	Terrain *terrain = new Terrain(xSizes[z],zSizes[z],detail[z],-xSizes[z]/2.0f,-zSizes[z]/2.0f-z*zSizes[z],yStart[z],xModifiers[z],yModifiers[z],zModifiers[z]);
    	terrains.push_back(*terrain);
    }
    //terrain = new Terrain(30,10,.125f,-15.0f,-5.0f);
    boss = new Model("ufo_v3.obj",6,1,1);
    background = new Background(-150,-85,-200,400,250);

    // set initial timer
    initTimer = clock();


    // cablage des callback
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMouseFunc(tbMouseFunc);    // traqueboule utilise la souris
    glutMotionFunc(tbMotionFunc);  // traqueboule utilise la souris
    // cablage des callback
    glutReshapeFunc(reshape);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_COLOR_MATERIAL);
    glutIdleFunc(idle);

    initLights();

    // Details sur le mode de trac\E9
    glEnable( GL_DEPTH_TEST );            // effectuer le test de profondeur
    glShadeModel(GL_SMOOTH);

    // Effacer tout
    //glClearColor (BackgroundColor[0],BackgroundColor[1], BackgroundColor[2], 0.0);
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
	//draw axesz
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

    glClearColor (0.0,0.0,0.0,1.0);

    glEnable( GL_TEXTURE_2D );



    //glLoadIdentity();  // repere camera
    //tbVisuTransform(); // origine et orientation de la scene


    //drawCoordSystem();

    opponentFlow();

    animate();

    draw();    

    glutSwapBuffers();

	/*
glClearColor (1.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glEnable( GL_TEXTURE_2D );

    background();
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glutSwapBuffers();
*/}



//function that draws the light source as a sphere
void drawLights()
{
	//remember all states of the GPU
	glPushAttrib(GL_ALL_ATTRIB_BITS);
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

