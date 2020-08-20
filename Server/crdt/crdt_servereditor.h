#ifndef CRDT_SERVEREDITOR_H
#define CRDT_SERVEREDITOR_H

#include <QObject>
#include <QVector>
#include <QMutex>
#include "crdt_symbol.h"
#include "crdt_message.h"

class CRDT_ServerEditor : public QObject {

    Q_OBJECT

private:
    QString percorsoFile;
    QVector<CRDT_Symbol> _symbols;
    QVector<CRDT_Symbol>::iterator trovaPosizione(QVector<int> pos);
    int confrontaPos(QVector<int> pos, QVector<int> currentPos);

public:
    QMutex* mutex;
    explicit CRDT_ServerEditor(QString percorsoFile, QObject *parent = nullptr);
    ~CRDT_ServerEditor();
    void saveInFilesystem();
    void loadFromFilesystem();
    QByteArray retrieveCurrentCrdt();

public slots:
    void process(const CRDT_Message& m);
};

#endif // CRDT_SERVEREDITOR_H