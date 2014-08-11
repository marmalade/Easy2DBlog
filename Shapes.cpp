#include "s3e.h"
#include "Iw2D.h"

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

		// Render filled rectangle
		Iw2DSetColour(0xff00ffff);
		Iw2DFillRect(CIwFVec2(-50.0f, -100.0f), CIwFVec2(100.0f, 200.0f));

		// Render filled arc
		Iw2DSetColour(0xffff00ff);
		Iw2DFillArc(CIwFVec2(0, 0), CIwFVec2(100.0f, 100.0f), 0, 1.8 * PI);
		
		// Flip the surface buffer to screen
		Iw2DSurfaceShow();

		// Sleep to allow the OS to process events etc.
		s3eDeviceYield(0);
	}
	
	// Shut down Iw2D
	Iw2DTerminate();
	
	return 0;
}
