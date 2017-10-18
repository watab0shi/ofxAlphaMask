#include "ofxAlphaMask.h"

ofShader ofxAlphaMask::shader;

string   ofxAlphaMask::fragSrc = R"(
#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex0;
uniform sampler2DRect maskTex;
uniform float         alpha;

void main( void ) {
  vec2  pos    = gl_TexCoord[ 0 ].st;
  vec3  src    = texture2DRect( tex0, pos ).rgb;
  float mask   = texture2DRect( maskTex, pos ).r;
  gl_FragColor = vec4( src, mask * alpha );
}
)";

bool ofxAlphaMask::bLoaded = false;


//--------------------------------------------------------------
ofxAlphaMask::ofxAlphaMask()
{
  if( ofxAlphaMask::bLoaded ) return;
  
  ofxAlphaMask::shader.setupShaderFromSource( GL_FRAGMENT_SHADER, fragSrc );
  ofxAlphaMask::shader.linkProgram();
  ofxAlphaMask::bLoaded = true;
}

//--------------------------------------------------------------
void ofxAlphaMask::begin( ofTexture& _tex )
{
  ofxAlphaMask::shader.begin();
  ofxAlphaMask::shader.setUniformTexture( "maskTex", _tex, 1 );
  ofxAlphaMask::shader.setUniform1f( "alpha", ofGetStyle().color.a / 255. );
}

//--------------------------------------------------------------
void ofxAlphaMask::end()
{
  ofxAlphaMask::shader.end();
}
