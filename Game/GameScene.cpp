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

#include "Iw2D.h"
#include "Audio.h"
#include "GameScene.h"
#include "Input.h"
#include "Ball.h"

#define MAX_BALLS	20

GameScene::GameScene() : Scene(), BallImage(0), BallsCount(0), ResetGame(false)
{
}

void GameScene::Init()
{
    Scene::Init();

    // Load the ball image
    BallImage = Iw2DCreateImage("ball.png");

    // Create initial ball
    NewBall();
}

void GameScene::Release()
{
    // Clean-up images
    if (BallImage != 0)
        delete BallImage;

    Scene::Release();
}

void GameScene::NotifyResetGame()
{
    ResetGame = true;
}

void GameScene::Reset()
{
    // Reset the game
    for (_iterator it = Sprites.begin(); it != Sprites.end(); ++it)
    {
       (*it)->Release();
       delete *it;
    }
    Sprites.clear();
    ResetGame = false;
    TouchedSprite = 0;
    BallsCount = 0;
    NewBall();
    g_pAudio->PlaySound("wrong.wav");
}

void GameScene::NewBall()
{
    // Create a new ball
    if (BallsCount >= MAX_BALLS)
        return;

    // Get surface width and height
    int surface_width = Iw2DGetSurfaceWidth();
    int surface_height = Iw2DGetSurfaceHeight();

    // Create a ball
    Ball* ball = new Ball();
    ball->Init();
    ball->setImage(BallImage);
    if (BallsCount & 1)
        ball->setColour(0xff4040ff);
    ball->setHitRadius((float)BallImage->GetWidth() / 2);
    ball->setTouchable(true);
    ball->Reset();
    AddSprite(ball);

    BallsCount++;
}

void GameScene::Update()
{
    Scene::Update();
    // If user didnt hit a ball then rset game
    if (g_pInput->m_Touched && !g_pInput->m_PrevTouched && TouchedSprite == 0)
    {
        NotifyResetGame();
    }

    if (ResetGame)
        Reset();
}

