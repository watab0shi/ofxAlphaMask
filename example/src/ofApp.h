#pragma once

#include "ofMain.h"
#include "ofxAlphaMask.h"


class ofApp : public ofBaseApp
{
public:
  void setup();
  void update();
  void draw();
  
  int          w, h;
  ofFbo        srcFbo;// 元画像
  ofFbo        maskFbo;// マスク画像（白黒）
  ofxAlphaMask alphaMask;
  
  float        scale = .25;
};
