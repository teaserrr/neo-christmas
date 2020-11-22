#ifndef Pixel_h
#define Pixel_h

class Pixel
{
  public:
    Pixel(int pixelNr, int red, int green, int blue);
    void fade(int amount);
    int red();
    int green();
    int blue();
    int number();
    bool done();
    
  private:
    int _pixelNr;
    int _red;
    int _green;
    int _blue;
    int _currentRed;
    int _currentGreen;
    int _currentBlue;
    int _currentFade;
    bool _fadingIn;
    bool _done;
};

#endif
