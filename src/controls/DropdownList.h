#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class DropdownList : public Control {
            public:
                
                //--------------------------------------------------------------
                DropdownList(Container *parent, ParameterPtr p) : Control(parent, p) {
                    paramT = dynamic_cast<ParameterNamedIndex*>(getParameter().get());
                }

                //--------------------------------------------------------------
                void setup() {
                    width   = getConfig().layout.columnWidth;
                    height  = getConfig().layout.buttonHeight;
                }

                //--------------------------------------------------------------
                void onDragOutside(int x, int y, int button) {
                    int a = this->y + height;
                    int b = this->y + height + getConfig().layout.dropdownListTextHeight * paramT->getNumLabels();
                    int v = floor(ofMap(y + getConfig().layout.dropdownListTextHeight/2, a, b, 0, paramT->getNumLabels()-1, true));
                    paramT->setValue(v);
                }
                
                //--------------------------------------------------------------
                void onDraw() {
                    ofFill();
                    setBGColor();
                    ofRect(0, 0, width, height);
                    
                    setTextColor();
                    getConfig().drawString(getName() + ": " + paramT->getSelectedLabel(), getConfig().layout.textPos.x, getConfig().layout.textPos.y);
                    
                    int ty = height/3;
                    int tl = ty*1.5;
                    ofTriangle(width - ty - tl, ty, width - ty, ty, width - ty - tl/2, height - ty);
                    
                    if(isActive()) {
                        int numLabels = paramT->getNumLabels();
                        setBGColor();
                        ofRect(0, height, width, getConfig().layout.dropdownListTextHeight * (numLabels + 0.5));
                        
                        ofNoFill();
                        ofSetLineWidth(1);
                        setBorderColor();
                        ofRect(0, height, width, getConfig().layout.dropdownListTextHeight * (numLabels + 0.5));
                        ofFill();
                        
                        for(int i=0; i < numLabels; i++) {
                            setTextColor();
                            float curY = height + i*getConfig().layout.dropdownListTextHeight;
                            if(i == paramT->getValue()) {
                                ofRect(0, curY+3, width, getConfig().layout.dropdownListTextHeight);
                                setBGColor();
                            }
                            
                            getConfig().drawString(paramT->getLabel(i), getConfig().layout.textPos.x, curY + getConfig().layout.textPos.y);
                        }
                    }
                }
                
            protected:
                ParameterNamedIndex *paramT;
            };
            
        }
    }
}