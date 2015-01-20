#include <iostream>
using namespace std;

#define PI 3.141592654
#define numQuads 200
#define frames 200
#define windSpd 1

const char * header [] = 
{
    "Display \"Animation\"  \"Screen\"  \"rgbsingle\"",
    "Format 640 480",
    "CameraAt 0 0 0", 
    "CameraUp 0 0 1",
    "CameraEye 20 20 40",
    "CameraFOV 50" 
 };

int nlines = sizeof(header) / sizeof(char *);
void drawS(float R, float n, float e);
void drawT(float R, float r, float n, float e);

int main (int argc, char * argv[])
{
	float R;
	float r;
	float n;
	float e;
	bool sph;
	
	if(argc == 4)
	{
		R = atof(argv[1]);
		n = atof(argv[2]);
		e = atof(argv[3]);
		sph = true;
	}
	else if(argc == 5)
	{
		R = atof(argv[1]);
		r = atof(argv[2]);
		n = atof(argv[3]);
		e = atof(argv[4]);
		sph = false;
	}
	else
	{
		cout << "Wrong input!\n";
		return 1;
	}
	
  	// Print out header
  	for (int i = 0; i < nlines; i++)
    	cout << header[i] << endl;
    
    cout << "WorldBegin\n";
    
    cout << "\tPointLight 0 0 10 1 1 1 1024\n";
    cout << "\tPointLight 10 0 10 1 1 1 1024\n";
    cout << "\tPointLight 0 10 10 1 1 1 1024\n";
    
    cout << "\tSurface \"metal\"\n";
    cout << "\tKa 0.75\n";
    cout << "\tKd 0.25\n";
    cout << "\tKs 0.25\n";
    
    cout << "\tColor 1 0 0\n";
    if(sph)
    	drawS(R,n,e);
    else
    	drawT(R,r,n,e);
    
    cout << "WorldEnd\n";
    
    return 0;
}

void drawS(float R, float n, float e)
{
	cout << "\tSqSphere " << R << " " << n << " " << e << " -" << R << " ";
		cout << R << " 360\n"; 
	
	
	//cout << "Sphere " << R << " -" << R << " " << R << " 360\n";
}
void drawT(float R, float r, float n, float e)
{
	float phi = 180;
	cout << "\tSqTorus " << R << " " << r << " " << n << " " << e;
		cout << " -" << phi << " " << phi << " 360\n";
}