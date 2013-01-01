#pragma once

#include "ofxMSAControlFreakGui/src/ControlParameterT.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolBase : public ControlParameterT<ParameterBool> {
            public:
                
                //--------------------------------------------------------------
                BoolBase(Panel *parent, string s) : ControlParameterT<ParameterBool>(parent, s) {
                }
                
                //--------------------------------------------------------------
                BoolBase(Panel *parent, Parameter *p) : ControlParameterT<ParameterBool>(parent, p) {
                }
                
                //--------------------------------------------------------------
                void toggle() {
                    if(!parameter) return;
                    parameter->setValue(!parameter->getValue());
                }
                
                //--------------------------------------------------------------
                void keyPressed( int key ) {
                    if(key==keyboardShortcut) toggle();
                }
                
                //--------------------------------------------------------------
                void onKeyEnter() {
                    toggle();
                }
                
                //--------------------------------------------------------------
                void onPress(int x, int y, int button) {
                    if(!parameter) return;
                    if(button == 0) {
                        if(parameter->getMode() == ParameterBool::kBang || parameter->getMode() == ParameterBool::kPush) parameter->setValue(true);
                        else toggle();
                    }
                }
                
                //--------------------------------------------------------------
                void onRelease(int x, int y, int button) {
                    if(parameter->getMode() == ParameterBool::kPush) parameter->setValue(false);
                }
                
                //--------------------------------------------------------------
                void onDraw() {
                    if(parameter->getMode() == ParameterBool::kBang && parameter->getValue()) parameter->setValue(false);
                }
            };
            
        }
    }
}