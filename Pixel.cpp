#include "Pixel.h"
#include <Arduino.h>

Pixel::Pixel(int pixelNr, int red, int green, int blue)
{
  _pixelNr = pixelNr;
  _red = red;
  _green = green;
  _blue = blue;
  _currentRed = 0;
  _currentGreen = 0;
  _currentBlue = 0;
  _currentFade = 0;
  _fadingIn = true;
  _done = false;
}

int Pixel::red()
{
  return _currentRed;
}

int Pixel::green()
{
  return _currentGreen;
}

int Pixel::blue()
{
  return _currentBlue;
}

int Pixel::number()
{
  return _pixelNr;
}

bool Pixel::done()
{
  return _done;
}

void Pixel::fade(int amount)
{
  if (_fadingIn)
  {
    _currentFade += amount;
    if (_currentFade >= 255)
    {
      _currentFade = 255;
      _fadingIn = false;
    }
  }
  else
  {
    _currentFade -= amount;
    if (_currentFade <= 0)
    {
      _currentFade = 0;
      _done = true;
    }
  }

  _currentRed = map(_currentFade, 0, 255, 0, _red);
  _currentBlue = map(_currentFade, 0, 255, 0, _blue);
  _currentGreen = map(_currentFade, 0, 255, 0, _green);
}
