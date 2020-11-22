#ifndef PixelCreator_h
#define PixelCreator_h

#include "Pixel.h"

class PixelCreator
{
public:
    PixelCreator() {}

    virtual Pixel* create(int pixelNr) const = 0;
};

class AllColoursCreator : public PixelCreator
{
public:
    AllColoursCreator() {};

    virtual Pixel* create(int pixelNr) const
    {
        return new Pixel(pixelNr, random(255), random(255), random(255));
    }
};

class RedAndGreenCreator : public PixelCreator
{
public:
    RedAndGreenCreator() {};

    virtual Pixel* create(int pixelNr) const
    {
        int r = random(10);
        int red = 0;
        int green = 0;
        if (r > 7) // more chance of green than red
            red = 255;
        else
            green = 255;
        return new Pixel(pixelNr, red, green, 0);
    }
};

#endif
