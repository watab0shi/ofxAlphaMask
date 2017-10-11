#pragma once

#include "ofShader.h"


class ofxAlphaMask
{
  ofShader shader;
  
public:
  ofxAlphaMask()
  {
    string fragSrc = R"(
#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex0;
uniform sampler2DRect maskTex;

void main( void ) {
  vec2  pos    = gl_TexCoord[ 0 ].st;
  vec3  src    = texture2DRect( tex0, pos ).rgb;
  float mask   = texture2DRect( maskTex, pos ).r;
  gl_FragColor = vec4( src, mask );
}
    )";
    
    shader.setupShaderFromSource( GL_FRAGMENT_SHADER, fragSrc );
    shader.linkProgram();
  }
  
  void begin( ofTexture& _tex )
  {
    shader.begin();
    shader.setUniformTexture( "maskTex", _tex, 1 );
  }
  
  void end()
  {
    shader.end();
  }
};