#ifndef BALL_H_
#define BALL_H_

struct Color
{
    double r,g,b;
};

class ball{
private:
	double x,y,
		   vx,vy,
		   r,
		   m;
	Color color;
public:
	ball();
	void move();
	void bounce();
	void show() const;
	void changeColor(double r,double g,double b);
	void collide(ball &a);
};

const double pi=3.14159265;

double random(double lower, double upper);
int sign(double x);

#endif