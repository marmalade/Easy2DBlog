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

#if !defined(_BALL_H)
#define _BALL_H

#include "Sprite.h"

class Ball : public Sprite
{
protected:
    /// Properties
protected:
    CIwFVec2    Velocity;   // Velocity of ball
public:
    void		setVelocity(float x, float y)	{ Velocity.x = x; Velocity.y = y; }
    CIwFVec2    getVelocity() const             { return Velocity; }
    /// Properties End
public:
    Ball();

    void    Update();

    void	Reset();

    // Event handlers
    void    Event_BeginTouch();
    void    Event_EndTouch();

};

#endif  // _BALL_H
