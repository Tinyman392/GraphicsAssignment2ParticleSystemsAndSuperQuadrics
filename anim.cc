#include <iostream>

using std::cout;
using std::endl;

const char * header [] = 
  {
    "Display \"Animation\"  \"Screen\"  \"rgbdouble\"",
    "Format 640 480",
    "CameraAt 0 0 0", 
    "CameraUp 0 0 1",
    "CameraEye 0 -40 0",
    "CameraFOV 50" 
  };

int nlines = sizeof(header) / sizeof(char *);

int main (int argc, char * argv[])
{

  // Print out header
  
  for (int i = 0; i < nlines; i++)
    cout << header[i] << endl;

  // Loop over frames

  int frame = 0;

  for(frame = 0; ; frame++)
    {
      cout << "FrameBegin " << frame << endl;
      cout << "WorldBegin" << endl;
      
      cout << "FarLight  0 0 -1   1 1 1   0.8" << endl;
      cout << "Ka 0.5" << endl;
      cout << "Kd 0.5" << endl;

      //      cout << "Translate " << frame * 0.1  << " 0 0" << endl;
      cout << "Rotate \"Z\" " <<  frame << endl; 
      cout << "Translate 10  0  0" << endl;

      cout << "Sphere 4 -4  4  360" << endl;

      cout << "WorldEnd" << endl;
      cout << "FrameEnd" << endl;
    }

}
