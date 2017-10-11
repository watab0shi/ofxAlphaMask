#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
  w = ofGetWidth();
  h = ofGetHeight();
  
  srcFbo.allocate( w, h, GL_RGB );
  srcFbo.begin();
  {
    ofClear( 0 );
  }
  srcFbo.end();
  
  maskFbo.allocate( w, h, GL_RGB );
  maskFbo.begin();
  {
    ofClear( 0 );
  }
  maskFbo.end();
  
  ofBackground( 0, 255, 0 );
}

//--------------------------------------------------------------
void ofApp::update()
{
  // 元画像 背景グラデーション
  srcFbo.begin();
  {
    ofClear( 0 );
    
    float   hue = ofGetFrameNum() % 255;
    ofColor c1  = ofColor::fromHsb( hue, 255, 255 );
    ofColor c0  = ofColor( 255 );
    ofBackgroundGradient( c0, c1 );
  }
  srcFbo.end();
  
  // マスク画像作成 マウス位置に白丸
  maskFbo.begin();
  {
    ofClear( 0 );
    
    ofFill();
    ofSetColor( 255 );
    ofDrawCircle( mouseX, mouseY, 200 );
  }
  maskFbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
  // srcFbo を maskFbo でアルファマスク 黒 -> a = 0.0, 白 -> a = 1.0
  alphaMask.begin( maskFbo.getTexture() );
  {
    ofSetColor( 255 );
    srcFbo.draw( 0, 0 );
  }
  alphaMask.end();
  
  // 確認用
  ofPushMatrix();
  {
    ofScale( scale, scale );
    
    srcFbo.draw( 0, 0 );
    maskFbo.draw( w, 0 );
  }
  ofPopMatrix();
  
  ofDrawBitmapStringHighlight( "src",                4, h * scale - 6 );
  ofDrawBitmapStringHighlight( "mask",   w * scale + 4, h * scale - 6 );
  ofDrawBitmapStringHighlight( "result",             4, h         - 6 );
}

