
#include "ofxMSAControlFreakGui/src/Includes.h"

#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
//            //--------------------------------------------------------------
//            Panel::Panel(Container *parent, string s) : Container(parent, s) {
//                init();
//            }
            
            //--------------------------------------------------------------
            Panel::Panel(Container *parent, ParameterGroup* p) : Container(parent, p) {
                init();
                
//                layout.doAutoLayout = true;
//                layout.set(0, 0, 1, 0); // TODO: hack?
                
                titleButton = new BoolTitle(this, getName());
                titleButton->layout.doAffectFlow = false;
                titleButton->layout.positionMode = 1;
                titleButton->setZ(1);
                titleButton->getParameter().set(true);
                addControl(titleButton);
                
                collapseAllButton = new BoolSimpleCircle(this, "-");
                collapseAllButton->layout.doAffectFlow = false;
                collapseAllButton->layout.positionMode = 1;
                collapseAllButton->setZ(2);
                collapseAllButton->setMode(ParameterBool::kBang);
                addControl(collapseAllButton);
                
                saveButton = new BoolSimpleCircle(this, "s");
                saveButton->layout.doAffectFlow = false;
                saveButton->layout.positionMode = 1;
                saveButton->setZ(2);
                saveButton->setMode(ParameterBool::kBang);
                saveButton->getParameter().setTooltip("Save preset for '" + getPath() + "'");
                addControl(saveButton);
                
                loadButton = new BoolSimpleCircle(this, "l");
                loadButton->layout.doAffectFlow = false;
                loadButton->layout.positionMode = 1;
                loadButton->setZ(2);
                loadButton->setMode(ParameterBool::kBang);
                loadButton->getParameter().setTooltip("Load preset for '" + getPath() + "'");
                addControl(loadButton);
                
                // add wrap button only if we are the root
                if(getParent() == NULL) {
                    wrapButton = new BoolSimpleCircle(this, "w");
                    wrapButton->layout.doAffectFlow = false;
                    wrapButton->layout.positionMode = 1;
                    wrapButton->setZ(2);
                    wrapButton->setMode(ParameterBool::kToggle);
                    wrapButton->getParameter().setTooltip("Wrap");
                    addControl(wrapButton);
                    
                    scrollbar = new ScrollBar(this);
                    scrollbar->layout.doAffectFlow = false;
                    scrollbar->layout.positionMode = 2;
                    scrollbar->setZ(-1);
                    scrollbar->doIsolateOnActive = false;
                    scrollbar->layout.doIncludeInContainerRect = false;
                    scrollbar->getParameter().setTooltip("Scroll " + getPath());
                    addControl(scrollbar);
                } else {
                    wrapButton = NULL;
                    scrollbar = NULL;
                }

                
                children = new Container(this, getName() + "_children");
                children->layout.doAffectFlow = true;
                children->layout.set(0, 0, 1, 3);
                addControl(children);
                
                children->addParameters(p);
            }
            
            //--------------------------------------------------------------
            Panel::~Panel() {
                if(layoutManager) delete layoutManager;
            }
            
            //--------------------------------------------------------------
            void Panel::init() {
                disableAllEvents();
                layoutManager = NULL;
                width = 0;
                height = 0;
                paramT = dynamic_cast<ParameterGroup*>(&getParameter());
            }
            
            //--------------------------------------------------------------
            void Panel::showPanel(bool bOpen, bool bRecursive) {
                titleButton->getParameter().set(bOpen);
                if(bRecursive) {
                    for(int i=0; i<children->getNumControls(); i++) {
                        Panel *p = dynamic_cast<Panel*>(children->getControl(i));
                        if(p) p->showPanel(bOpen, true);
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Panel::onUpdate() {
                int s = titleButton->height * 0.7;
                int y = (titleButton->height - s)/2;
                int p = 3;
                
                
                collapseAllButton->layout.set(p, y, s, s);
                saveButton->layout.set(titleButton->width - (s + p) * 2, y, s, s);
                loadButton->layout.set(titleButton->width - (s + p), y, s, s);

                if(wrapButton) {
                    wrapButton->layout.set(titleButton->width - (s + p) * 3, y, s, s);
                    if(layoutManager) wrapButton->getParameter().trackVariable(&layoutManager->doWrap);
                }
                
                if(scrollbar) {
                    if(layoutManager) {// && !layoutManager->doWrap) {
                        // TODO: custom scrollbar layout
                        scrollbar->visible = true;
                        scrollbar->layout.set(0, 0, getConfig().layout.padding.x, ofGetHeight());
                        float sbheight = scrollbar->layout.height;
                        scrollbar->barThickness = sbheight / layoutManager->curRect.height;
                        layoutManager->scrollY = ofMap(scrollbar->getParameter().value(), 0, 1 - scrollbar->barThickness, 0, layoutManager->curRect.height - sbheight/2);
                    } else {
                        scrollbar->visible = false;
                    }
                }
                


                if(titleButton->getParameter().value()) {
                    titleButton->getParameter().setTooltip("Collapse panel");
                    collapseAllButton->getParameter().setName("-");
                    collapseAllButton->getParameter().setTooltip("Collapse all panels");
                } else {
                    titleButton->getParameter().setTooltip("Expand panel");
                    collapseAllButton->getParameter().setName("+");
                    collapseAllButton->getParameter().setTooltip("Expand all panel");
                }
                
                if(collapseAllButton->getParameter().value()) showPanel(!titleButton->getParameter(), true);
                
                if(loadButton->getParameter().value()) {
                    ofFileDialogResult f = ofSystemLoadDialog("Load preset", false, ofToDataPath(""));
                    if(f.bSuccess) {
                        paramT->loadXmlValues(f.filePath);
                    }
                }
                
                if(saveButton->getParameter().value()) {
                    ofFileDialogResult f = ofSystemSaveDialog(getPath() + "-defaults.xml", "Save preset");
                    if(f.bSuccess) {
                        paramT->saveXmlValues(f.getPath());
                        //                            string path = ofFilePath::getEnclosingDirectory(f.getPath(), false);//f.filePath.substr(0, f.filePath.rfind("/"));
                        //                            paramT->saveXml(false, path + "/" + getPath() + "-" + f.fileName + ".xml");
                        //                            ofDirectory dir(path + "/" + getPath());
                        //                            if(!dir.exists()) dir.create(true);
                        //                            paramT->saveXml(false, dir.getAbsolutePath() + "/" + f.fileName + ".xml");
                    }
                    
                }
            }
            
            
        }
    }
}
