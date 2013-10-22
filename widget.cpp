#include <QHostAddress>
#include <iostream>
#include <QMessageBox>
#include "widget.h"
#include "ui_widget.h"




Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    initMapCmdId();

    /*************************
     *  Connection to server *
     ************************/
    QHostAddress hostname;
    hostname.setAddress("127.0.0.1");
    m_socket = new QTcpSocket;
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(networkErrorHandler(QAbstractSocket::SocketError)));
    m_socket->connectToHost(hostname, 3074);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendMessage()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::initMapCmdId()
{
    m_commandIdMap["msg"] = 1;
    m_commandIdMap["who"] = 3;
    m_commandIdMap["list"] = 5;
    m_commandIdMap["topic"] = 6;
    m_commandIdMap["kick"] = 7;
    m_commandIdMap["ban"] = 8;
    m_commandIdMap["op"] = 9;
    m_commandIdMap["deop"] = 20;
    m_commandIdMap["join"] = 21;
    m_commandIdMap["nick"] = 22;
    m_commandIdMap["leave"] = 23;
    m_commandIdMap["unban"] = 24;
    m_commandIdMap["banlist"] = 25;
}


void Widget::sendMessage(void)
{
    QString data = ui->textEdit->toPlainText().trimmed(); // get a string containing the text typed without whitespaces caracters from the start and the end
    QLocale l;      // used to get a string from a number

    if(data[0] == '/')
    {
       QString commandName;
       QRegExp sep("/s | " "");
       commandName = data.mid(1).section(sep ,0, 0, QString::SectionSkipEmpty);     // get the command name without the / caracter behind

       quint16 cmdId = getIdFromCommandName(commandName);
       if(cmdId == 0)
           QMessageBox::critical(this, "Unknown command", "Sorry, we don't know this command ...");
       else
       {
           QString id = l.toString(cmdId);                  // get a string containing the value of command ID
           QString test = QString("%u").arg(cmdId, 0);      // get a string of 2 bytes containing the command ID
           QMessageBox::information(this, "test", l.toString(test.size()));     // test if the test string size is 2 bytes
           QMessageBox::information(this, "Command", "You are trying to send command : " + commandName + " : " + id); // display the command sent and the id corresponding
       }
    }
    else{
        if(!data.isEmpty())
            QMessageBox::information(this, "Message", "You are trying to send a message !" + l.toString(data.size()));
        else
            QMessageBox::information(this, "Empty message", "You are trying to send an empty message !");
    }
    // test size <= 510 octets
    if(!data.isEmpty())
    {
        m_socket->write(data.toUtf8());
    }

}



void Widget::networkErrorHandler(QAbstractSocket::SocketError)
{
    QMessageBox::critical(this, "Network critical error", m_socket->errorString());
    this->close();
}


quint16 Widget::getIdFromCommandName(const QString &commandName)
{
    quint16 cmdId;
    std::map<QString, quint16>::iterator it;

    it = this->m_commandIdMap.find(commandName);
    if(it == m_commandIdMap.end())
        return 0;

    cmdId = it->second;

    return cmdId;
}


