#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <vector>
using namespace std;

#define PI 3.141592654

#define boundY 25
#define boundX 25
const int numBalls = 100;
const int numFrames = 9;
const float windSpd = 0.75;

const char * header [] = 
{
    "Display \"Animation\"  \"Screen\"  \"rgbdouble\"\n",
    "Format 640 480",
    "CameraAt 0 0 10", 
    "CameraUp 0 0 1",
    "CameraEye 40 40 60",
    "CameraFOV 20\n" 
 };
 
 //get the size of the header array
 int nlines = sizeof(header) / sizeof(char *);
 
 struct coord
 {
 	float x;
 	float y;
 	float z;
 };
 
 //get the wind at the coordinate c
 //wind is defined by the vector field (siny, cosx);
 coord getWind(coord c);
 bool outBounds(coord c);
 float getVel(coord c);
 void setColor(int shader);
 
 //structure for a cloud
 struct ball
 {
 	//position is their current position
 	coord pos;
 	//brightness is used to set the color
 	coord color;
 	float radius;
 	coord vel;
 	//string shader;
 	coord posO;
 	int shader;
 };
 
 int main()
 {
 	//print header
 	for(int i = 0; i < nlines; i++)
 	{
 		cout << header[i] << endl;
 	}
 	
 	//initial frame and balls vector
 	int frame = 0;
 	vector<ball> balls;
 	
 	//initialize ball values
 	for(int i = 0; i < numBalls; i++)
 	{
 		ball c;
 		c.pos.x = (rand() % 400 - 200) / 100.0;
 		c.pos.y = (rand() % 500 - 250) / 100.0;
 		c.pos.z = 0;
 		
 		c.posO.x = 0;
 		c.posO.y = 0;
 		c.posO.z = 0;
 		
 		c.color.x = (rand() % 100) / 100.0;// + 0.75;
 		c.color.y = (rand() % 100) / 100.0;// + 0.75;
 		c.color.z = (rand() % 100) / 100.0;// + 0.75;
 		
 		//c.color.x = 0.25;
 		//c.color.y = 0.5;
 		//c.color.z = 0.25;
 		
 		c.radius = (rand() % 50) / 100.0;
 		
 		c.vel.x = (rand() % 100 - 50) / 100.0;
 		while(abs(c.vel.x) < 0.1)
 		{
 			c.vel.x = (rand() % 50 - 25) / 100.0;
 		}
 		c.vel.y = (rand() % 100 - 50) / 100.0;
 		while(abs(c.vel.y) < 0.1)
 		{
 			c.vel.y = (rand() % 50 - 25) / 100.0;
 		}
 		c.vel.z = (rand() % 150 + 50) / 100.0;
 		
 		balls.push_back(c);
 		
 		c.shader = rand() % 4;
 	}
 	
 	cout << "Background 0.6 0.7 0.8\n";
 	
 	//start frame and world blocks
 	cout << "WorldBegin" << endl << endl;
 	
 	cout << "\tSurface \"plastic\"\n";
 	cout << "\tKa .5\n";
 	cout << "\tKd .5\n";
 	cout << "\tKs .5\n";
 	cout << "\tPointLight 15 0 40 1 1 1 1024\n";
 	cout << "\tPointLight -15 0 40 1 1 1 1024\n";
 	cout << "\tPointLight 0 0 40 1 1 1 1024\n";
 	
 	cout << "\tAmbientLight 0.6 0.7 0.8 2\n";
 	
 	setColor(1);
 	cout << "\tColor 0.10 0.4 0.10\n";
 	cout << "\tPolySet \"P\"\n";
 	cout << "\t4 1\n";
 	cout << "\t-25 -25 0\n";
 	cout << "\t-25 20 0\n";
 	cout << "\t20 20 0\n";
 	cout << "\t20 -25 \n";
 	cout << "\t0 1 2 3 -1\n";
 	
 	for(frame = 0; frame < numFrames; frame++)
 	{	
 		//draw each ball and update information
 		for(int i = 0; i < numBalls; i++)
 		{
 			//output color of current ball
 			cout << "\tColor " << balls[i].color.x << " ";
 				cout <<	balls[i].color.y << " " << balls[i].color.z;
 				cout << "\n\n";
 			setColor(balls[i].shader);
 			
 			//cout << "\tColor 1 1 1\n\n";
 			
 			//get the magnitude of wind
 			coord w = getWind(balls[i].pos);
 			
 			balls[i].posO.x = balls[i].pos.x;
 			balls[i].posO.y = balls[i].pos.y;
 			balls[i].posO.z = balls[i].pos.z;
 			
 			//balls[i].radius *= getVel(balls[i].vel)*growthRate;
 			
 			//update coordinates
 			//based on velocity, wind, and radius
 			balls[i].pos.x += balls[i].vel.x + w.x;
 			balls[i].pos.y += balls[i].vel.y + w.y;
 			balls[i].pos.z += balls[i].vel.z;
 			
 			cout << "\tTube " << balls[i].posO.x << " ";
 				cout << balls[i].posO.y << " " << balls[i].posO.z << " ";
 				cout << balls[i].pos.x << " " << balls[i].pos.y;
 				cout << " " << balls[i].pos.z << " " << balls[i].radius;
 				cout << "\n";
 			cout << "\tXformPush\n";
 			cout << "\tTranslate " << balls[i].pos.x << " ";
 				cout << balls[i].pos.y << cout << " " << balls[i].pos.z;
 				cout << endl;
 			cout << "\tSphere " << balls[i].radius << " -20 20 360\n";
 			cout << "\tXformPop\n";
 			
 			//if we go out of bounds, we will swap the x
 			//to go the the opposite side.  The wind should help us out
 			//and bring the ball back into frame
 			//if the wind doesn't help, then we have 199 other balls!
 			if(outBounds(balls[i].pos) || balls[i].radius > 3)
 			{
 				balls[i].radius = (rand() % 50) / 100.0;
 				balls[i].pos.x = (rand() % 200 - 100) / 100.0;
 				balls[i].pos.y = (rand() % 300 - 150) / 100.0;
 				balls[i].pos.z = 0;
 				
 				balls[i].posO.x = 0;
 				balls[i].posO.y = 0;
 				balls[i].posO.z = 0;
 				
 				balls[i].vel.x = (rand() % 50 - 25) / 100.0;
 				while(abs(balls[i].vel.x) < 0.1)
 				{
 					balls[i].vel.x = (rand() % 50 - 25) / 100.0;
 				}
 				balls[i].vel.y = (rand() % 50 - 25) / 100.0;
 				while(abs(balls[i].vel.y) < 0.1)
 				{
 					balls[i].vel.y = (rand() % 50 - 25) / 100.0;
 				}
 				balls[i].vel.z = (rand() % 150 + 50) / 100.0;
 				
 				balls[i].color.x = (rand() % 100) / 100.0;// + 0.75;
 				balls[i].color.y = (rand() % 100) / 100.0;// + 0.75;
 				balls[i].color.z = (rand() % 100) / 100.0;// + 0.75;
 			}
 		}
 		
 		
 	}
 	
 	//end frame and world blocks
 	cout << "WorldEnd" << endl;
 	
 	return 0;
 }
 
 //get the wind at the coordinate c
 //wind is defined by the vector field (siny, cosx);
 coord getWind(coord c)
 {
 	coord w;
 	w.x = ((0.2-windSpd)*c.x / boundX + windSpd)*sin(c.y);
 	w.y = ((0.2-windSpd)*c.y / boundY + windSpd)*sin(c.x);
 	
 	return w;
 }
 
 bool outBounds(coord c)
 {
 	bool out = false;
 	
 	if(c.y > boundY || c.x > boundX || c.y < -boundY || c.x < -boundX)
 		out = true;
 	
 	return out;
 }
 
 float getVel(coord c)
 {
 	float vel = 0;
 	vel = sqrt(pow(c.x,2) + pow(c.x,2));
 	
 	return vel;
 }
 
 void setColor(int shader)
 {
 	string surface = "\"matte\"";
 	
 	if(shader == 0)
 	{
 		surface = "\"metal\"";
 	}
 	else if(shader == 1)
 	{
 		surface = "\"matte\"";
 	}
 	else if(shader == 2)
 	{
 		surface = "\"plastic\"";
 	}
 	else if(shader == 3)
 	{
 		surface = "\"painted plastic\"";
 	}
 	
 	cout << "\tSurface " << surface << endl;
 	
 }