#pragma once

#include "ofxMSAControlFreakGui/src/controls/BoolBase.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolButton : public BoolBase {
            public:
                
                //--------------------------------------------------------------
                BoolButton(Panel *parent, string s) : BoolBase(parent, s) {}

                //--------------------------------------------------------------
                BoolButton(Panel *parent, Parameter *p) : BoolBase(parent, p) {}
                
                //--------------------------------------------------------------
                void onDraw() {
                    if(!parameter) return;
                    
                    if(parameter->getName().empty()) return;
                    
                    // draw bg
                    ofFill();
                    setToggleColor(parameter->getValue());
                    ofRect(0, 0, width, height);
                    
                    drawText(3, 15);
//                    drawBorder();
                    
                    BoolBase::onDraw();
                }
            };
            
        }
    }
}