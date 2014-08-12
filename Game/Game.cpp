/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */

#include "s3e.h"			// Marmalade s3e API
#include "Iw2D.h"			// Marmalade Iw2D API
#include "GameScene.h"		// Game Scene class
#include "Input.h"			// Basic input wrapper API
#include "Audio.h"			// Basic audio wrapper API

// FRAME_TIME is the amount of time that a single frame should last in seconds
#define FRAME_TIME  (30.0f / 1000.0f)

// Main entry point for the application
int main()
{
    // Initialise Iw2D
    Iw2DInit();
    
    // Initialise the input system
    g_pInput = new Input();

    // Initialise the audio system
    g_pAudio = new Audio();
    
    // Create a scene and add a bunch of sprites
    GameScene* scene = new GameScene();
    scene->Init();
    
    // Wait for a quit request from the host OS
    while (!s3eDeviceCheckQuitRequest())
    {
        // Get current system time time in milliseconds
        uint64 new_time = s3eTimerGetMs();

        // Clear background to blue
        Iw2DSurfaceClear(0xff8080);

        // Update input system
        g_pInput->Update();

        // Update audio system
        g_pAudio->Update();

        // Update and render scene
        scene->Update();
        scene->Draw(); 

        // Flip the surface buffer to screen
        Iw2DSurfaceShow();

        // Lock frame rate to 30 frames per second
        int yield = (int)(FRAME_TIME * 1000 - (s3eTimerGetMs() - new_time));
        if (yield < 0)
            yield = 0;
        s3eDeviceYield(yield);	// Yield to OS
    }

    // Clean up sprite manager

    // Cleanup
    scene->Release();
    delete scene;
    delete g_pAudio;
    delete g_pInput;

    Iw2DTerminate();
    
    return 0;
}
