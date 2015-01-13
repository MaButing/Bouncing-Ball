#include <GL\glut.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "ball.h"

int n;
ball *balls;

void DrawIt(void){
glClearColor(1.0, 1.0, 1.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT);


for (int i=0;i<n;i++)
{   
	for (int j=i+1;j<n;j++)
		balls[i].collide(balls[j]);
	balls[i].bounce();
    balls[i].move();
    balls[i].show();
}

glFlush();
}


void Tick(int n) {
glutTimerFunc(20, Tick, 0);
glutPostRedisplay();
}

int main(int argc, char *argv[]){

std::cout<<"How many balls do you want to have?";
std::cin>>n;

balls=new ball [n];

glutInit(&argc, argv);
glutInitWindowPosition(100, 100);
glutInitWindowSize(400, 400);
glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
glutCreateWindow("Bouncing Ball");
glutDisplayFunc(DrawIt);
glutTimerFunc(20, Tick, 0);
glutMainLoop();
delete [] balls;
return 0;
}