#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>


class Client : public QObject
{
    Q_OBJECT

public:
    static Client* Instance();
    QTcpSocket* getSocket(void) const;
    void connect(QString hostname = "127.0.0.1", quint16 port = 3074);
private:
    Client(QObject *parent = 0);
    QTcpSocket *m_socket;
    static Client* s_instance;

public slots:
    void onDataReceived(void);


};


#endif // CLIENT_H
