#include <QHostAddress>
#include <iostream>
#include <QMessageBox>
#include "widget.h"
#include "ui_widget.h"
#include "command.h"
#include <QKeyEvent>
#include "invoker.h"
#include "message.h"
#include "frame.h"
#include "client.h"

Widget* Widget::s_instance = 0;

Widget* Widget::Instance()
{
    if(s_instance == 0)
        s_instance = new Widget;


    return s_instance;
}


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    initMapCmdId();


    m_client = Client::Instance();
    m_client->connect("127.0.0.1", 3074);

    connect(m_client->getSocket(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(networkErrorHandler(QAbstractSocket::SocketError)));


    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(m_client->getSocket(), SIGNAL(readyRead()), this, SLOT(onDataReceived()));

    // Test on tree Widget

    QObject::connect(ui->treeWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(onChannelSelected(QModelIndex)));

    ui->treeWidget->setHeaderLabel("CHANNELS");
    QStringList n("toto");
    QTreeWidgetItem *test_tree_item1 = new QTreeWidgetItem(ui->treeWidget, n);
    ui->treeWidget->addTopLevelItem(test_tree_item1);


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



void Widget::displayError(const QString &error)
{
    QMessageBox messageBox(this);
    messageBox.setWindowTitle("An error occured");
    messageBox.setText(error);
    messageBox.setIcon(QMessageBox::Warning);
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.setDefaultButton(QMessageBox::Ok);
    messageBox.setWindowState(Qt::WindowActive);

    messageBox.exec();
}



QTextEdit* Widget::getInputArea(void) const
{
    return ui->textEdit;
}

QTextEdit* Widget::getOutputArea(void) const
{
    return ui->textEdit_2;
}

QTreeWidget* Widget::getTree(void) const
{
    return ui->treeWidget;
}


void Widget::sendMessage(void)
{

    using namespace TOSERVER;

    QString data = ui->textEdit->toPlainText().simplified(); // get a string containing the text typed without whitespaces caracters from the start and the end
    QLocale l;      // used to get a string from a number


    if(data.isEmpty())
    {
        this->displayError(QString("You are trying to send an empty message !"));
        return;
    }

    if(data.size() > 509)
    {
        this->displayError(QString("Text entry overflow, can't eval message/command !"));
        return;
    }

    quint8 cmdCode;
    if(data[0] == '/')
    {
       QString commandName;
       QRegExp sep("/s | " "");
       commandName = data.mid(1).section(sep ,0, 0, QString::SectionSkipEmpty);     // get the command name without the / caracter behind
       cmdCode = getIdFromCommandName(commandName);
       data = data.section(sep, 1);
    }

    else
        cmdCode = C_PUBMSG;

    Command* c;

   //std::cout<<"size of data : "<<<<std::endl;
   switch(cmdCode)
   {
   case(C_PRIVMSG): c = new privmsg(data); break;
   case(C_PUBMSG): c = new pubmsg(data); break;
   //case(C_GWHO): c = new GWHOCommand(data); break;
   //case(C_CWHO): c = new CWHOCommand(data); break;
   //case(C_LIST): c = new LISTCommand(data); break;
   //case(C_TOPIC): c = new TOPICCommand(data); break;
   //case(C_KICK): c = new KICKCommand(data); break;
   //case(C_BAN): c = new BANCommand(data); break;
   //case(C_OP): c = new OPCommand(data); break;
   //case(C_DEOP): c = new DEOPCommand(data); break;
   case(C_JOIN): c = new join(data); break;
   //case(C_NICK): c = new NICKCommand(data); break;
   //case(C_LEAVE): c = new LEAVECommand(data); break;
   //case(C_UNBAN): c = new UNBANCommand(data); break;
   //case(C_BANLIST): c = new BANLISTCommand(data); break;
   default: this->displayError(QString("Sorry, we don't know this command ...")); return;
   }

  // if(!c->verify())
   //     return;

   c->execute();
        this->getInputArea()->clear();

}





void Widget::networkErrorHandler(QAbstractSocket::SocketError)
{
    QMessageBox::critical(this, "Network critical error", m_client->getSocket()->errorString());
    this->close();
}


quint8 Widget::getIdFromCommandName(const QString &commandName)
{
    quint8 cmdCode;
    std::map<QString, quint8>::iterator it;

    it = this->m_commandIdMap.find(commandName);
    if(it == m_commandIdMap.end())
        return 0;

    cmdCode = it->second;

    return cmdCode;
}

void Widget::onChannelSelected(QModelIndex index)
{
    QString content;        // text of the index selected

    content = QString(index.data().toByteArray());

    ui->textEdit->setText(content);
}

