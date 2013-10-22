#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <map>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    quint16 getIdFromCommandName(const QString &commandName);
    
private:
    std::map<QString, quint16> m_commandIdMap;
    Ui::Widget *ui;
    QTcpSocket *m_socket;
    char * m_data;          // message to send (the one entered in the texEdit widget
    void initMapCmdId();

public slots:
    void sendMessage(void);
    void networkErrorHandler(QAbstractSocket::SocketError);
};

#endif // WIDGET_H
