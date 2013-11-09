#include "textentry.h"
#include "widget.h"

TextEntry::TextEntry(QWidget *parent) :
    QTextEdit(parent)
{

}


void TextEntry::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        Widget* w = Widget::Instance();
        w->sendMessage();
    }
    else
        QTextEdit::keyPressEvent(event);

}


