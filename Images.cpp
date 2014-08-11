#include "s3e.h"
#include "Iw2D.h"
#include <stdio.h>

// Main entry point for the application
int main()
{
	// Initialise Iw2D
	Iw2DInit();
	
	// Get surface width and height
	int surface_width = Iw2DGetSurfaceWidth();
	int surface_height = Iw2DGetSurfaceHeight();

	// Rotation angle of rectangle
	float angle = 0;
	
	// Load the ball image
	CIw2DImage* image1 = Iw2DCreateImage("ball.png");
	
	// Wait for a quit request from the host OS
	while (!s3eDeviceCheckQuitRequest())
	{
		// Clear background to blue
		Iw2DSurfaceClear(0xff8080);

		// Set up a transform
		CIwFMat2D mat;
		mat.SetRot(angle);
		mat.ScaleRot(2.0f);
		mat.SetTrans(CIwFVec2((float)surface_width / 2, (float)surface_height / 2));
		Iw2DSetTransformMatrix(mat);
		angle += 0.01f;

		// Draw the ball
		Iw2DDrawImage(image1, CIwFVec2(-image1->GetWidth() / 2, -image1->GetHeight() / 2));

		// Flip the surface buffer to screen
		Iw2DSurfaceShow();

		// Sleep to allow the OS to process events etc.
		s3eDeviceYield(0);
	}
	
	// Clean-up images
	delete image1;
	
	// Shut down Iw2D
	Iw2DTerminate();
	
	return 0;
}
