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

#if !defined(_SCENE_H)
#define _SCENE_H

#include <list>

class Sprite;

class Scene
{
public:
    typedef std::list<Sprite*>::iterator _iterator;
protected:
    std::list<Sprite*>  Sprites;					// Collection of sprites
    Sprite*             TouchedSprite;              // Sprite that was last touched
public:
    Scene();
    virtual ~Scene();
    virtual void    Init();                         // Initialise the scene
    virtual void    Release();                      // Release the scene
    virtual void    Update();                       // Update the scene
    virtual void    Draw();                         // Draw the scene

    void            AddSprite(Sprite *sprite);      // Add a sprite to the scene
    void            RemoveSprite(Sprite *sprite);   // Remove a sprite from the scene
};

#endif  // _SCENE_H
