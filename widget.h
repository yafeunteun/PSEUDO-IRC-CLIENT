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
    static Widget* Instance();
    ~Widget();
    quint16 getIdFromCommandName(const QString &commandName);
    void displayError(const QString& error);
    QTcpSocket* getSocket(void) const;
    
protected:
    explicit Widget(QWidget *parent = 0);

private:
    static Widget* s_instance;
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
