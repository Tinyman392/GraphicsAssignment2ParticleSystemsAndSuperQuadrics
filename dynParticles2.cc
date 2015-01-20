#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <vector>
using namespace std;

#define PI 3.141592654

#define boundY 10
#define boundX 10
const int numBalls = 200;
const int numFrames = 3000;
const float growthRate = 0.1;
const float windSpd = 1.5;

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
    "CameraAt 0 0 0", 
    "CameraUp 0 1 0",
    "CameraEye 0 0 40",
    "CameraFOV 30\n" 
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
 
 //structure for a cloud
 struct ball
 {
 	//position is their current position
 	coord pos;
 	//brightness is used to set the color
 	coord color;
 	float radius;
 	coord vel;
 	string shader;
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
 		c.pos.z = 1;
 		
 		c.color.x = (rand() % 100) / 100.0;// + 0.75;
 		c.color.y = (rand() % 100) / 100.0;// + 0.75;
 		c.color.z = (rand() % 100) / 100.0;// + 0.75;
 		
 		//c.radius = ((rand() % 50) / 100.0);
 		c.radius = 0.5;
 		
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
 		c.vel.z = (rand() % 150 + 50) / 100;
 		
 		balls.push_back(c);
 	}
 	
 	for(frame = 0; ; frame++)
 	{
 		//start frame and world blocks
 		cout << "FrameBegin " << frame << endl;
 		cout << "WorldBegin" << endl << endl;
 		
 		cout << "\tSurface \"metal\"\n";
 		cout << "\tKa .5\n";
 		cout << "\tKd .5\n";
 		cout << "\tKs .5\n";
 		cout << "\tPointLight 0 0 0 1 1 1 8\n";
 		cout << "\tPointLight -15 0 40 1 1 1 1024\n";
 		cout << "\tPointLight 15 0 40 1 1 1 1024\n";
 		cout << "\tPointLight 0 0 40 1 1 1 1024\n";
 		
 		cout << "\tColor 0 0 0\n";
 		cout << "\tSphere 0.5 10 -10 360\n";
 		
 		//draw each ball and update information
 		for(int i = 0; i < numBalls; i++)
 		{
 			//output color of current ball
 			cout << "\tColor " << balls[i].color.x << " ";
 				cout <<	balls[i].color.y << " " << balls[i].color.z;
 				cout << "\n\n";
 			
 			//output render current by by translating
 			//then drawing it as a sphere
 			cout << "\tXformPush\n";
 			cout << "\tTranslate " << balls[i].pos.x << " ";
 				cout << balls[i].pos.y << " " << balls[i].pos.z << "\n";
 			cout << "\tSphere " << balls[i].radius << " -10 10 360\n";
 			cout << "\tXformPop\n\n";
 			
 			//get the magnitude of wind
 			coord w = getWind(balls[i].pos);
 			
 			cout << "#\tv: " << balls[i].vel.x << " " << balls[i].vel.y;
 			cout << endl;
 			
 			//get new velocity
 			//balls[i].vel.x += w.x;
 			//balls[i].vel.y += w.y;
 			
 			//update coordinates
 			//based on velocity, wind, and radius
 			balls[i].pos.x += w.x;//balls[i].vel.x + w.x;
 			balls[i].pos.y += w.y;//balls[i].vel.y + w.y;
 			balls[i].pos.z += w.z;//balls[i].vel.z;
 			
 			//balls[i].radius *= 1 + getVel(balls[i].vel)*growthRate;
 			
 			//if we go out of bounds, we will swap the x
 			//to go the the opposite side.  The wind should help us out
 			//and bring the ball back into frame
 			//if the wind doesn't help, then we have 199 other balls!
 			if(outBounds(balls[i].pos) ||  
 			   balls[i].pos.z > 40)
 			{
 				//balls[i].radius = ((rand() % 50) / 100.0);
 				balls[i].radius = 0.5;
 				balls[i].pos.x = (rand() % 200 - 100) / 100.0;
 				balls[i].pos.y = (rand() % 300 - 150) / 100.0;
 				balls[i].pos.z = 1;
 				
 				balls[i].vel.x = (rand() % 30 - 15) / 100.0;
 				while(abs(balls[i].vel.x) < 0.1)
 				{
 					balls[i].vel.x = (rand() % 30 - 15) / 100.0;
 				}
 				balls[i].vel.y = (rand() % 30 - 15) / 100.0;
 				while(abs(balls[i].vel.y) < 0.1)
 				{
 					balls[i].vel.y = (rand() % 30 - 15) / 100.0;
 				}
 				balls[i].vel.z = (rand() % 150 + 50) / 100;
 				
 				balls[i].color.x = (rand() % 100) / 100.0;// + 0.75;
 				balls[i].color.y = (rand() % 100) / 100.0;// + 0.75;
 				balls[i].color.z = (rand() % 100) / 100.0;// + 0.75;
 			}
 		}
 		
 		//end frame and world blocks
 		cout << "WorldEnd" << endl;
 		cout << "FrameEnd" << endl << endl;
 	}
 	
 	return 0;
 }
 
 //get the wind at the coordinate c
 //wind is defined by the vector field (siny, cosx);
 coord getWind(coord c)
 {
 	coord w;
 	w.x = windSpd*sin(c.y);
 	w.y = windSpd*sin(c.x);
 	w.z = windSpd*sin(c.z);
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