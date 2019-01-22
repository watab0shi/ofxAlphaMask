#pragma once

#include "ofGraphics.h"
#include "ofShader.h"


class ofxAlphaMask
{
  static ofShader    shader;
  static std::string fragSrc;
  static bool        bLoaded;
  
public:
  ofxAlphaMask();
  
  void begin( ofTexture& _tex );
  void end();
};
