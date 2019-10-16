#include "crdt_controller.h"

CRDT_controller::CRDT_controller(GUI_MyTextEdit& textEdit, GUI_ToolsBar& toolbar): textEdit(textEdit), toolbar(toolbar){}

void CRDT_controller::setItalic(){
    textEdit.setFontItalic(!textEdit.fontItalic());
    QPushButton *italicButton = toolbar.findChild<QPushButton*>("italicPushButton");
    italicButton->setChecked(!italicButton->isChecked());
}
