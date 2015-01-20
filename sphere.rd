Display "Animation"  "Screen"  "rgbsingle"
Format 640 480
CameraAt 0 0 0
CameraUp 0 0 1
CameraEye 20 20 40
CameraFOV 50
WorldBegin
	PointLight 0 0 10 1 1 1 1024
	PointLight 10 0 10 1 1 1 1024
	PointLight 0 10 10 1 1 1 1024
	Surface "metal"
	Ka 0.75
	Kd 0.25
	Ks 0.25
	Color 1 0 0
	SqSphere 5 2.5 1.5 -5 5 360
WorldEnd
