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

#if !defined(_SPRITE_H)
#define _SPRITE_H

#include "Iw2D.h"

class Scene;

class Sprite
{
    /// Properties
protected:
    Scene*          Parent;                 // Parent scene
    CIw2DImage*     Image;                  // The image that represents the sprite
    CIwFVec2        Position;               // Position of the sprite
    float           Angle;                  // Rotation of sprite in radians
    float           Scale;                  // Scale of sprite
    unsigned int    Colour;                 // Colour of sprite
    bool            Visible;                // Sprites visible state
    float           HitRadius;				// Radius of circle that approximately contains the sprite (used to detect when actor is touched)
    bool            Touchable;              // Touchable state of object
public:
    void        setParent(Scene* scene)             { Parent = scene; }
    Scene*      getParent()                         { return Parent; }
    void        setImage(CIw2DImage* image)         { Image = image; }
    CIw2DImage* getImage()                          { return Image; }
    void        setPosition(float x, float y)       { Position.x = x; Position.y = y; }
    CIwFVec2    getPosition() const                 { return Position; }
    void        setAngle(float angle)               { Angle = angle; }
    float       getAngle() const                    { return Angle; }
    void        setScale(float scale)               { Scale = scale; }
    float       getScale() const                    { return Scale; }
    void        setColour(unsigned int colour)      { Colour = colour; }
    unsigned int getColour() const                  { return Colour; }
    void        setVisible(bool show)               { Visible = show; }
    bool        isVisible() const                   { return Visible; }
    void        setHitRadius(float radius)			{ HitRadius = radius; }
    float       getHitRadius() const                { return HitRadius; }
    void        setTouchable(bool touchable)        { Touchable = true; }
    bool        isTouchable() const                 { return Touchable; }

    /// Properties End
protected:
    CIwFMat2D    Transform;                 // Transform matrix
public:
    Sprite();
    virtual ~Sprite();

    virtual void    Init();                 // Initialise the sprite
    virtual void    Release();              // Release the sprite
    virtual void    Update();               // Updates the sprite game object
    virtual void    Draw();                 // Renders the sprite game object

    // Event handlers
    virtual void    Event_BeginTouch() {}
    virtual void    Event_EndTouch() {}
};

#endif  // _SPRITE_H
