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

#include "Audio.h"
#include "Ball.h"
#include "GameScene.h"

Ball::Ball() : Sprite()
{
}

void Ball::Reset()
{
    int surface_width = Iw2DGetSurfaceWidth();
    int surface_height = Iw2DGetSurfaceHeight();

    // Give ball a random position
    Position.x = (float)(IwRandMinMax(0, surface_width) - surface_width / 2);
    Position.y = (float)(IwRandMinMax(0, surface_height) - surface_height / 2);

    // Give ball a random velocity
    Velocity.x = (float)(IwRandMinMax(0, surface_width) - surface_width / 2) / 30;
    Velocity.y = (float)(IwRandMinMax(0, surface_height) - surface_height / 2) / 30;
}

void Ball::Update()
{
    // Move ball
    Position += Velocity;

    // Wrap ball with edges of display
    int surface_width = Iw2DGetSurfaceWidth();
    int surface_height = Iw2DGetSurfaceHeight();
    int w = (int)Image->GetWidth();
    int h = (int)Image->GetHeight();
    int left = -w / 2;
    int right = surface_width + w / 2;
    int top = -h / 2;
    int bottom = surface_height + h / 2;
    if (Position.x < left)
        Position.x += right;
    else if (Position.x > right)
        Position.x -= right;
    if (Position.y < top)
        Position.y += bottom;
    else if (Position.y > bottom)
        Position.y -= bottom;

    Sprite::Update();
}

void Ball::Event_BeginTouch()
{
    // Dont tap red balls
    if (Colour == 0xff4040ff)
    {
        // Reset the game
        ((GameScene*)Parent)->NotifyResetGame();
    }
    else
    {
        // User tapped a white ball so reset it
        Reset();
        ((GameScene*)Parent)->NewBall();
        g_pAudio->PlaySound("hit.wav");
    }
}

void Ball::Event_EndTouch()
{
}

