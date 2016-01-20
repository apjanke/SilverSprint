//
//  GFXGlobal.cpp
//  GoldsprintsFX
//
//  Created by Charlie Whitney on 8/27/14.
//
//

#include "GFXGlobal.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gfx;

GFXGlobal* GFXGlobal::mInstance = NULL;
 
GFXGlobal * GFXGlobal::getInstance(){
    if (!mInstance){
        mInstance = new GFXGlobal();
        
        mInstance->uiFont = ci::Font( loadAsset("fonts/UbuntuMono-R.ttf"), 35 );
        mInstance->texFont = gl::TextureFont::create( mInstance->uiFont );
        mInstance->countdownFont = gl::TextureFont::create( ci::Font( loadAsset("fonts/UbuntuMono-R.ttf"), 235 ) );
        
        mInstance->currentRaceType = RACE_TYPE::RACE_TYPE_TIME;
    }
    return mInstance;
}

void GFXGlobal::setScale( const ci::Rectf &scaledRect )
{
    vec2 sc( (float)getWindowWidth() / 1920.0, (float)getWindowHeight() / 1080.0);
    mScreenScale = vec2( min(sc.x, sc.y) );
    
    mScreenOffset = scaledRect.getUpperLeft();
}

ci::vec2 GFXGlobal::localToGlobal( ci::vec2 pos ){
    return (vec2(pos - mScreenOffset) / mScreenScale);
}

std::string addZ(int n) {
    return (n<10? "0":"") + to_string(n);
}

std::string addZ100(int n) {
    if( n>100 ) {
        return to_string(n);
    }else if(n>10) {
        return "0" + to_string(n);
    }
    return "00" + to_string(n);
}

std::string GFXGlobal::toTimestampPrecise( int millis ){
    //    millis = 755020;
    // millis = 12048;
    
    int ms = millis % 1000;
    millis = (millis - ms) / 1000;
    int secs = millis % 60;
    millis = (millis - secs) / 60;
    int mins = millis % 60;
    
    return addZ(mins) + ":" + addZ(secs) + ":" + addZ100(ms);
}

std::string GFXGlobal::toTimestamp( int millis ){
    //    millis = 755020;
    // millis = 12048;
    
    int ms = millis % 1000;
    millis = (millis - ms) / 1000;
    int secs = millis % 60;
    millis = (millis - secs) / 60;
    int mins = millis % 60;
    
    while( ms > 100 ){
        ms /= 10.0;
    }
    
    return addZ(mins) + ":" + addZ(secs) + ":" + addZ(ms);
}