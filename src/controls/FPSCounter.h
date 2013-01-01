#pragma once

#include "ofxMSAControlFreakGui/src/ControlParameterT.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class FPSCounter : public ControlParameterT<Parameter> {
            public:
                FPSCounter(Panel *parent) : ControlParameterT<Parameter>(parent, NULL) {}
                
                void onDraw() {
                    glPushMatrix();
                    glTranslatef(x, y, 0);
                    
                    ofEnableAlphaBlending();
                    ofFill();
                    setBGColor();
                    ofRect(0, 0, width, height);
                    
                    setTextColor();
                    getConfig().drawString("FPS: " + ofToString(ofGetFrameRate()), 3, 15);
                    
                    glPopMatrix();
                }
            };
            
        }
    }
}