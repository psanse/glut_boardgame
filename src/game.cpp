//game.cpp: entry point for a general outline of baordgame using glut and OpenGL
//			configures basic glut parameters and defines a scene wrapper for all 
//			call backs
//author:pss
//date of creation: 9/5/16

#include <iostream>
#include "boardgl.h"
#include "glut.h"

#define GRID_SIZE	5		//4x4 grid board

//call back declarations
void OnDraw(void); 
void OnKeyboardDown(unsigned char key, int x, int y); 
void OnMouseClick(int button,int state, int x,int y);
//void OnTimer(int value); 

////////////////////////////////////////////////
//global objects which make the world
Board gameboard(GRID_SIZE);
BoardGL scene(&gameboard);

///////////////////////////////////////////////

int main(int argc,char* argv[]){
	//GL Initialization stuff
	glutInit(&argc, argv);
	glutInitWindowSize(800,600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");

	
	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick);
  //glutTimerFunc(25,OnTimer,0);    //set timer if required

	//set light and perspective
	scene.init();
	
	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();	

	return 0;   
}

void OnDraw(void){
	scene.Draw();
	glutSwapBuffers();
}

void OnKeyboardDown(unsigned char key, int x_t, int y_t){
	scene.KeyDown(key);
	glutPostRedisplay();
}

void OnMouseClick(int b,int state, int x,int y){
//captures clicks with mouse and if CTRL or SHIFT is pressed before
	bool down=(state==GLUT_DOWN);
	int button;
	if(b==GLUT_LEFT_BUTTON){
		button=MOUSE_LEFT_BUTTON;
	}
	if(b==GLUT_RIGHT_BUTTON){
		button=MOUSE_RIGHT_BUTTON;
		cout<<"MOUSE_RIGHT_BUTTON"<<endl;
	}
		
	int specialKey = glutGetModifiers();
	bool ctrlKey= (specialKey & GLUT_ACTIVE_CTRL)? true:false ;
	bool sKey= specialKey & GLUT_ACTIVE_SHIFT ;

		
	scene.MouseButton(x,y,b,down,sKey,ctrlKey);
	glutPostRedisplay();
}


//void OnTimer(int value){
	//****	

	//no borrar estas lineas
//	glutTimerFunc(25,OnTimer,0);
//	glutPostRedisplay();
//}
