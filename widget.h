#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <map>
#include <QModelIndex>
#include <QTextEdit>
#include <QTreeWidget>
#include <QAbstractSocket>

class Client;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    static Widget* Instance();
    ~Widget();
    quint8 getIdFromCommandName(const QString &commandName);
    void displayError(const QString& error);
    QTextEdit* getInputArea(void) const;
    QTextEdit* getOutputArea(void) const;
    QTreeWidget *getTree(void) const;
    Client* m_client;
    
protected:
    explicit Widget(QWidget *parent = 0);


private:
    static Widget* s_instance;
    std::map<QString, quint8> m_commandIdMap;
    Ui::Widget *ui;
    char * m_data;          // message to send (the one entered in the texEdit widget
    void initMapCmdId();

public slots:
    void sendMessage(void);
    void networkErrorHandler(QAbstractSocket::SocketError);
    void onChannelSelected(QModelIndex);
};

#endif // WIDGET_H
