#include "crdt_controller.h"
#include <iostream>

CRDT_controller::CRDT_controller(GUI_MyTextEdit& textEdit, GUI_ToolsBar& toolbar): textEdit(textEdit), toolbar(toolbar){
    QObject::connect(toolbar.findChild<QPushButton*>("italicPushButton"), &QPushButton::clicked, this, &CRDT_controller::setItalic);
}

void CRDT_controller::setItalic(){
}
