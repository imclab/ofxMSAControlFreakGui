//
//  Renderer.cpp
//  ofxMSAControlFreak example
//
//  Created by Memo Akten on 28/12/2012.
//
//

#pragma once

#include "ofMain.h"


namespace msa {
    namespace controlfreak {
        namespace gui {
            
            class Control;
            class Config;
            
            class Renderer {
            private:
                friend class Gui;
                friend class Control;
                friend class LayoutManager;
                
                ~Renderer();
                
                static Renderer &instance();
                
                void add(Control *c);
                void clearControls();
                void draw();
                
                void setToolTip(Control* control, string s, int x = -1, int y = -1);
                
                static Renderer *renderer;
                
                vector<Control*> controls;
                map<Control*, Control*> controlsMap;    // just to check if it's already added, bit ghetto
                
                struct {
                    string s;
                    int x;
                    int y;
                    Control* control;
                } tooltip;
                
                Renderer();
                
                void drawToolTip();
//                
//                void update();
//                void mouseMoved(ofMouseEventArgs &e);
//                void mousePressed(ofMouseEventArgs &e);
//                void mouseDragged(ofMouseEventArgs &e);
//                void mouseReleased(ofMouseEventArgs &e);
//                void keyPressed(ofKeyEventArgs &e);
//                void keyReleased(ofKeyEventArgs &e);

            };
            
        }
    }
}