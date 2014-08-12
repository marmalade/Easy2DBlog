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

#include "Scene.h"
#include "Sprite.h"
#include "Input.h"

Scene::Scene() : TouchedSprite(0)
{
}

Scene::~Scene()
{
}

void Scene::Init()
{
}

void Scene::Release()
{
    for (_iterator it = Sprites.begin(); it != Sprites.end(); ++it)
    {
       (*it)->Release();
       delete *it;
    }
    Sprites.clear();
}

void Scene::AddSprite(Sprite *sprite)
{
    Sprites.push_back(sprite);
    sprite->setParent(this);
}

void Scene::RemoveSprite(Sprite *sprite)
{
    Sprites.remove(sprite);
}

void Scene::Update()
{
    // Iterate through all sprites updating them
    for (_iterator it = Sprites.begin(); it != Sprites.end(); ++it)
    {
        (*it)->Update();
    }

    if (TouchedSprite == 0)
    {
        // Check for user starting to touch an object in the world
        if (g_pInput->m_Touched && !g_pInput->m_PrevTouched)
        {
            for (_iterator it = Sprites.begin(); it != Sprites.end(); ++it)
            {
                if ((*it)->isTouchable())
                {
                    // Calculate distance from touch position to centre of sprite
                    Sprite* sprite = *it;
                    CIwFVec2 pos = sprite->getPosition();
                    float dx = pos.x - g_pInput->m_X;
                    float dy = pos.y - g_pInput->m_Y;
                    float d = dx * dx + dy * dy;
                    float d2 = sprite->getHitRadius();
                    d2 *= d2;
                    if (d < d2)
                    {
                        (*it)->Event_BeginTouch();
                        TouchedSprite = *it;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        // Player released touch so send end touch event to Sprite (only if it is still being touched)
        if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
        {
            g_pInput->Reset(true);
            if (TouchedSprite->isTouchable())
            {
                // Calculate distance from touch position to centre of sprite
                CIwFVec2 pos = TouchedSprite->getPosition();
                float dx = pos.x - g_pInput->m_X;
                float dy = pos.y - g_pInput->m_Y;
                float d = dx * dx + dy * dy;
                float d2 = TouchedSprite->getHitRadius();
                d2 *= d2;
                if (d < d2)
                    TouchedSprite->Event_EndTouch();
            }
            TouchedSprite = 0;
        }
    }
}

void Scene::Draw()
{
    // Iterate through all sprites drawing them
    for (_iterator it = Sprites.begin(); it != Sprites.end(); ++it)
    {
        (*it)->Draw();
    }
}

