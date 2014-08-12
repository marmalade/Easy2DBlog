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

#include "Sprite.h"

Sprite::Sprite() : Parent(0), Image(0), Position(0,0), Angle(0), Scale(1), Colour(0xffffffff), Visible(true), HitRadius(1.0f), Touchable(false)
{
}

Sprite::~Sprite()
{
}

void Sprite::Init()
{
}

void Sprite::Release()
{
}

void Sprite::Update()
{
}

void Sprite::Draw()
{
    if (Visible)
    {
        // Build transform
        Transform.SetRot(Angle);
        Transform.ScaleRot(Scale);
        Transform.SetTrans(Position);
        Iw2DSetTransformMatrix(Transform);
        Iw2DSetColour(Colour);

        // Render image
        if (Image != 0)
            Iw2DDrawImage(Image, CIwFVec2(-Image->GetWidth() / 2, -Image->GetHeight() / 2));
    }
}

