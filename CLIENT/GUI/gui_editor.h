#ifndef GUI_EDITOR_H
#define GUI_EDITOR_H

#include <QWidget>
#include "ui_gui_editor.h"

class GUI_Editor : public QWidget
{
    Q_OBJECT
public:
    long documentId;

    explicit GUI_Editor(QWidget *parent, long documentId);
    ~GUI_Editor();
    //se serve posso metterci un codice di ritorno
    void addUserIcon(long userId);
    void removeUserIcon(long userId);

private slots:
    void on_menuPushButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GUI_Editor *ui;
    QMap<long, QLabel*> usersIconMap;

    void setUsersBar();
    QLabel *getUserIcon(long userId);
    //adatto la size del widget in base a quanti users ci sono, ma solo fino ad un certo punto
    void updateIconsWidgetSize();
};

#endif // GUI_EDITOR_H
