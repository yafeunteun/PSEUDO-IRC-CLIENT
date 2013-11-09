#ifndef TEXTENTRY_H
#define TEXTENTRY_H

#include <QTextEdit>
#include <QKeyEvent>

class TextEntry : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEntry(QWidget *parent = 0);
protected:
    void keyPressEvent(QKeyEvent *event);
    
signals:
    
public slots:
    
};

#endif // TEXTENTRY_H
