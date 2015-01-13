#include <GL\glut.h>
#include <cmath>
#include <cstdlib>
#include "ball.h"



ball::ball()
{
	x=random(-1,1);y=random(-1,1);
	vx=random(0,0.01);vy=random(0,0.01);
	r=random(0.05,0.15);
	m=r*r;
	color.r=random(0,1);color.g=random(0,1);color.b=random(0,1);
}

void ball::move()
{
	x+=vx;
	y+=vy;
}

void ball::bounce()
{
	if (x>1-r){x=2*(1-r)-x;vx=-vx;}
	else if (x<-1+r) {x=2*(-1+r)-x;vx=-vx;}
	if (y>1-r){y=2*(1-r)-y;vy=-vy;}
	else if (y<-1+r) {y=2*(-1+r)-y;vy=-vy;}
}

void ball::show() const
{
	glColor3f(color.r,color.g,color.b);
	glBegin(GL_POLYGON);
	    for(double theta=0;theta<=2*pi;theta+=pi/60)
	        glVertex2f(x+r*cos(theta),y+r*sin(theta));    
    glEnd();
}

void ball::changeColor(double r,double g,double b) 
{
	color.r=r;color.g=g;color.b=b;
}

void ball::collide(ball &a)
{
	double d,s,sin,cos,v_vert,av_vert,v0,v1,v2,v3;
	d=sqrt((x-a.x)*(x-a.x)+(y-a.y)*(y-a.y));
	sin=(a.y-y)/d;
	cos=(a.x-x)/d;
	if ((s=r+a.r-d)>0)
	{   //分离
		x+=sign(x-a.x)*s*a.m/(m+a.m);
		y+=sign(y-a.y)*s*a.m/(m+a.m);
		a.x+=sign(a.x-x)*s*m/(m+a.m);
		a.y+=sign(a.y-y)*s*m/(m+a.m);
		//速度分解
		v_vert=vy*cos-vx*sin;
		v0=vy*sin+vx*cos;
		av_vert=a.vy*cos-a.vx*sin;
		v1=a.vy*sin+a.vx*cos;
		//速度交换
		v2=(m*v0-a.m*v0+2*a.m*v1)/(m+a.m);
		v3=(2*m*v0-m*v1+a.m*v1)/(m+a.m);
		//正交分解
		vx=v2*cos-v_vert*sin;
		vy=v2*sin+v_vert*cos;
		a.vx=v3*cos-av_vert*sin;
		a.vy=v3*sin+av_vert*cos;
	}
}



double random(double lower, double upper)
{
	int x = rand() % 10000;
	double d = (double) x;
	d = d / 10000 * (upper - lower) + lower;
	return d;
}

int sign(double x)
{
	if (x>0) return 1;
	else if (x<0) return -1;
	else return 0;
}

