#include "s3e.h"
#include "Iw2D.h"

// Main entry point for the application
int main()
{
	// Initialise Iw2D
	Iw2DInit();
	
	// Wait for a quit request from the host OS
	while (!s3eDeviceCheckQuitRequest())
	{
		// Clear background to blue
		Iw2DSurfaceClear(0xff8080);

		// TODO: Update game

		// TODO: Render game
		
		// Flip the surface buffer to screen
		Iw2DSurfaceShow();

		// Sleep to allow the OS to process events etc.
		s3eDeviceYield(0);
	}
	
	// Shut down Iw2D
	Iw2DTerminate();
	
	return 0;
}
