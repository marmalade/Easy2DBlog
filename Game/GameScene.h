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

#if !defined(_GAMESCENE_H)
#define _GAMESCENE_H

#include "Scene.h"

class GameScene : public Scene
{
    /// Properties
    /// Properties End
protected:
    CIw2DImage* BallImage;
    int			BallsCount;
    bool		ResetGame;
public:
    GameScene();

    void    Init();
    void	Release();
    void    Update();

    void    Reset();
    void    NewBall();
    void	NotifyResetGame();
};

#endif  // _GAMESCENE_H
