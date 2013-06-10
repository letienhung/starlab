#pragma once
#include "ControllerModePlugin.h"
using namespace Starlab;

class mode_controller : public ControllerModePlugin{
    Q_OBJECT
    Q_INTERFACES(ModePlugin)

    QIcon icon(){ return QIcon(":/icons/axial_controller.png"); }
    bool isApplicable(){ return true; }

    void create(){
        controllers() << new FrameController( Vector3(.5,.5,0) );
        controllers() << new FrameController( Vector3(-.5,0,.4) );
        
        /// Example on how to connect them
        FrameController* conncontr = new FrameController( Vector3(0,0,0) );
        connect(conncontr,SIGNAL(positionUpdated(Vector3)),this,SLOT(positionUpdated(Vector3)));
        controllers() << conncontr;
    }   
    void destroy(){ 
        controllers().clear(); 
    }
    
    /// Don't delete-reload plugin when something new is loaded
    bool documentChanged(){ return true; }
    
    
public slots:
    /// Visualize changes in plugin
    void positionUpdated(Vector3 position){
        qDebug() << position[0] << position[1] << position[2];
    }   
};