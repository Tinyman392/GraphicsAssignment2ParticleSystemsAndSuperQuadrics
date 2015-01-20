#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <vector>
using namespace std;

//pi
#define PI 3.141592654
//angular velocity
#define aVel 2
#define rows 20
//for testing
const int numStars = 400;
const int numFrames = 200;

/*
const char * header [] = 
  {
    "Display \"Animation\"  \"Screen\"  \"rgbdouble\"",
    "Format 640 480",
    "CameraAt 0 0 0", 
    "CameraUp 0 0 1",
    "CameraEye 0 40 0",
    "CameraFOV 50" 
  };
*/

const char * header [] = 
{
    "Display \"Animation\"  \"Screen\"  \"rgbdouble\"\n",
    "Format 640 480",
    "CameraAt 0 -10 0", 
    "CameraUp 0 1 0",
    "CameraEye 75 30 20",
    "CameraFOV 50\n" 
};

//get the size of the header array
int nlines = sizeof(header) / sizeof(char *);
 
struct coord
{
	float x;
 	float y;
 	float z;
};

struct pCoord
{
	float r;
	float angle;
};

//structure for a cloud
struct star
{	
 	//brightness is used to set the color
 	coord color;
 	//size is the radius of the star
 	float size;
 	pCoord p;
 	//loss in r for each step
 	float dr;
 	float dangle;
 	int shader;
 	int brightness;
 	pCoord prev;
 	int z;
};

star initStar(bool reset);
star nPos(star s);
coord toCart(pCoord p,star s);
void drawStar(star s);
//checks if star is too far in the center
bool isEaten(pCoord p, float size);
float checkAngle(float angle);
string getSurface(int i);
 
int main()
{
	//print header
	for(int i = 0; i < nlines; i++)
	{
		cout << header[i] << endl;
	}
	
	//initial frame and balls vector
	int frame = 0;
	vector<star> stars;
	
	for(int i = 0; i < numStars; i++)
	{
		star s = initStar(false);
		stars.push_back(s);
	}
 	cout << "Background 0.5 0.6 0.7\n";
 	cout << "WorldBegin" << endl << endl;
 	
 	cout << "AmbientLight 1 1 1 1\n";
 	
 	//cout << "PointLight 0 0 0 1 1 1 512\n";
	cout << "PointLight -15 0 40 1 1 1 512\n";
	cout << "PointLight 15 0 40 1 1 1 512\n";
	cout << "PointLight 0 0 40 1 1 1 512\n\n";
	//cout << "Ka 0\n";
	//cout << "Kd 0\n";
	//cout << "Ks 0\n\n";
	
	//center of galaxy
	//cout << "Surface \"plastic\"\n";
	//cout << "Color 0 0 0\n";
	//cout << "Sphere 5 20 -20 360\n\n";
	
	cout << "Ka .75\n";
	cout << "Kd .25\n";
	cout << "Ks .25\n";
 	
 	cout << "Color 1 1 1\n";
 	cout << "XformPush\n";
	cout << "Sphere 5 -10 10 360\n";
	cout << "Surface \"plastic\"\n";
	cout << "Ka .25\n";
	cout << "Kd .75\n";
	cout << "Ks .75\n";
	cout << "Color 0 0 0\n";
	cout << "XformPush\n";
	cout << "\tRotate \"Y\" -30\n";
	cout << "\tTranslate 5 0 0\n";
	cout << "\tSphere 1 -10 10 360\n";
	cout << "XformPop\n";
	cout << "XformPush\n";
	cout << "\tRotate \"Y\" 30\n";
	cout << "\tTranslate 5 0 0\n";
	cout << "\tSphere 1 -10 10 360\n";
	cout << "XformPop\n";
	
	cout << "Translate 0 -15 0\n";
	cout << "Color 1 1 1\n";
	cout << "Ka .75\n";
	cout << "Kd .25\n";
	cout << "Ks .25\n";
	cout << "Sphere 10 -10 10 360\n";
	
	cout << "XformPush\n";
	cout << "Translate 10 0 0\n";
	cout << "Color 0 0 0\n";
	//cout << "Rotate \"Z\" 45\n";
	cout << "Sphere 1 -10 10 360\n";
	cout << "XformPop\n";
	cout << "XformPush\n";
	cout << "Rotate \"Z\" 30\n";
	cout << "Translate 10 0 0\n";
	cout << "Sphere 1 -10 10 360\n";
	cout << "XformPop\n";
	cout << "XformPush\n";
	cout << "Rotate \"Z\" 60\n";
	cout << "Translate 10 0 0\n";
	cout << "Sphere 1 -10 10 360\n";
	cout << "XformPop\n";
	
	cout << "Color 1 1 1\n";
	cout << "Translate 0 -25 0\n";
	cout << "Sphere 15 -15 15 360\n";
	cout << "Translate 0 -15 0\n";
	
	cout << "Ka .75\n";
	cout << "Kd .25\n";
	cout << "Ks .25\n";
	cout << "Color 1 1 1\n";
	cout << "PolySet \"P\"\n";
 	cout << "4 1\n";
 	cout << "30 0 300\n";
 	cout << "30 0 -300\n";
 	cout << "-25 0 -300\n";
 	cout << "-25 0 300\n";
 	cout << "0 1 2 3 -1\n";
	
	cout << "XformPop\n";
 	
 	cout << "Ka .25\n";
	cout << "Kd .75\n";
	cout << "Ks .75\n";
	cout << "Rotate \"Z\" 45\n";
	for(frame = 0; frame < numFrames; frame++)
	{
		//start frame and world blocks
		//cout << "FrameBegin " << frame << endl;
		
		//draw each star and update information
		for(int i = 0; i < numStars; i++)
		{
 			stars[i] = nPos(stars[i]);
 			drawStar(stars[i]);
		}
		//end frame and world blocks
		
		//cout << "FrameEnd" << endl << endl;
	}
	
	cout << "WorldEnd" << endl;
	
	return 0;
}
 
star initStar(bool reset)
{
	//we need to set
	//color
	//size
	//r
	//angle
	//dr
	//dangle
	//shader
	
	star s;
	/*
	s.color.x = (rand() % 25 / 100.0) + 0.75;
	s.color.y = (rand() % 25 / 100.0) + 0.75;
	s.color.z = (rand() % 25 / 100.0) + 0.75;
	*/
	s.color.x = 1;
	s.color.y = 0;
	s.color.z = 0;
	
	s.size = (rand() % 50 / 1000.0) + 0.1;
	
	//if(reset)
	//	s.p.r = rand() % 5 + 15;
	//else
		//s.p.r = (rand() % 17000 / 100.0) + 3;
	
	s.p.r = (rand() % 500 / 100.0) + 1.0;
	
	s.p.angle = rand() % 300 / 100.0;
	s.p.angle = checkAngle(s.p.angle);
	
	s.dr = (rand() %  20) + 10;
	s.dangle = (rand() % 5 / 100.0) + .1;
	
	s.shader = rand() % 4;
	
	s.brightness = rand() % 50 + 150;
	
	s.prev.r = 0;
	s.prev.angle = 0;
	s.z = rand() % 3000/1000.0 -1.5;
	
	//cout << "#Z: " << z << endl;
	
	return s;
}

star nPos(star s)
{
	s.prev = s.p;
	s.p.r = s.p.r + s.dr;
	//s.p.angle = s.p.angle + s.dangle;
	s.p.angle += aVel / s.p.r;
	s.p.angle = checkAngle(s.p.angle);
	
	//if(s.p.r < 10)
	//	s.size *= 0.5;
	
	//check if star is in the center of galaxy
	if(isEaten(s.p, s.size))
		s = initStar(true);
	
	
	
	return  s;
}

coord toCart(pCoord p, star s)
{
	//convert pCoord p to coord c
	coord c;
	c.x = p.r*cos(p.angle);
	c.y = p.r*sin(p.angle);
	c.z = s.z;
	
	cout << "#Z: " << c.z << endl;
	
	return c;
}

void drawStar(star s)
{
	//output surface information
	cout << "Surface " << getSurface(s.shader) << endl;
	cout << "Color " << s.color.x << " " << s.color.y << " " << s.color.z;
		cout << endl;
	
	coord c,c2;
	c = toCart(s.p,s);
	c2 = toCart(s.prev,s);
	
	//cout << "XformPush\n";
	//cout << "\tTranslate " << c.x << " " << c.y << " " << c.z << endl;
	//cout << "PointLight " << c.x << " " << c.y << " " << c.z << " ";
	//	cout << s.color.x << " " << s.color.y;
	//	cout << " " << s.color.z << " " << s.brightness << endl;
	cout << "Tube " << c2.x << " " << c2.y << " " << c2.z << " ";
		cout << c.x << " " << c.y << " " << c.z << " " << s.size;
		cout << endl;
	//cout << "XformPop\n\n";
}

bool isEaten(pCoord p, float size)
{
	if(p.r > 20)
		return true;
	//else if(size < 0.01)
	//	return true;
	return false;
}

float checkAngle(float angle)
{
	if(angle > 2*PI)
	{
		angle -= 2*PI;
		return angle;
	}
	
	return angle;
}

string getSurface(int i)
{
	string surface = "\"metal\"";
	
	if(i == 0)
		surface = "\"matte\"";
	else if(i == 1)
		surface = "\"metal\"";
	else if(i == 2)
		surface = "\"plastic\"";
	else if(i == 4)
		surface = "\"painted plastic\"";
	
	return surface;
}