#include "s3e.h"
#include "Iw2D.h"
#include <list>

class Sprite
{
    /// Properties
protected:
    CIw2DImage*     Image;                  // The image that represents the sprite
    CIwFVec2        Position;               // Position of the sprite
    float           Angle;                  // Rotation of sprite in radians
    float           Scale;                  // Scale of sprite
    unsigned int    Colour;                 // Colour of sprite
    bool            Visible;                // Sprites visible state
public:
    void        setImage(CIw2DImage* image) { Image = image; }
    CIw2DImage* getImage()                  { return Image; }
    void        setPosition(float x, float y) { Position.x = x; Position.y = y; }
    CIwFVec2    getPosition() const         { return Position; }
    void        setAngle(float angle)       { Angle = angle; }
    float       getAngle() const            { return Angle; }
    void        setScale(float scale)       { Scale = scale; }
    float       getScale() const            { return Scale; }
    void        setColour(unsigned int colour) { Colour = colour; }
    unsigned int getColour() const           { return Colour; }
    void        setVisible(bool show)       { Visible = show; }
    bool        isVisible() const           { return Visible; }

    /// Properties End
protected:
    CIwFMat2D    Transform;                 // Transform matrix
public:
    Sprite() : Image(0), Position(0,0), Angle(0), Scale(1), Colour(0xffffffff), Visible(true) {}
    virtual ~Sprite() {}

    virtual void    Update()                // Updates the sprite game object
    {
        Angle += 0.01f;
    }

    virtual void    Draw()                  // Renders the sprite game object
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
};

// Main entry point for the application
int main()
{
    // Initialise Iw2D
    Iw2DInit();
    
    // Get surface width and height
    int surface_width = Iw2DGetSurfaceWidth();
    int surface_height = Iw2DGetSurfaceHeight();

    // Load the ball image
    CIw2DImage* image1 = Iw2DCreateImage("ball.png");

    // Create a bunch of sprites
    std::list<Sprite*>* Sprites = new std::list<Sprite*>();
    for (int t = 0; t < 10; t++)
    {
        Sprite* sprite = new Sprite();
        sprite->setPosition((float)IwRandMinMax(0, surface_width), (float)IwRandMinMax(0, surface_height));
        sprite->setImage(image1);
        Sprites->push_back(sprite);
    }
    
    // Wait for a quit request from the host OS
    while (!s3eDeviceCheckQuitRequest())
    {
        // Clear background to blue
        Iw2DSurfaceClear(0xff8080);

        // Update and render sprites
        for (std::list<Sprite*>::iterator it = Sprites->begin(); it != Sprites->end(); ++it)
        {
            (*it)->Update();
            (*it)->Draw();
        }

        // Flip the surface buffer to screen
        Iw2DSurfaceShow();

        // Sleep to allow the OS to process events etc.
        s3eDeviceYield(0);
    }

    // Clean up sprites
    for (std::list<Sprite*>::iterator it = Sprites->begin(); it != Sprites->end(); ++it)
        delete *it;
    delete Sprites;

    // Clean-up images
    delete image1;
    
    // Shut down Iw2D
    Iw2DTerminate();
    
    return 0;
}
