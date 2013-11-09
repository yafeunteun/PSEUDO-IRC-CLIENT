#include "frame.h"
#include <iostream>


Frame::Frame(QByteArray &frame)
{
    QDataStream *stream = new QDataStream(frame);
    stream->readRawData((char*)&m_size, 2);
    stream->readRawData((char*)&m_id, 2);
    stream->readRawData((char*)&m_code, 1);
    quint16 arg_size = (m_size) - 3;        // 2 bytes for id; 1 byte for command code
    char args[arg_size];
    stream->readRawData(args, arg_size);
    delete stream;

    args[arg_size] = '\0';
    std::cout<<m_size<<std::endl;
    std::cout<<m_id<<std::endl;
    //std::cout<<(int)code<<std::endl;
    std::cout<<args;

    m_argList = getArg(args);

}

QByteArray Frame::getReadyToSendFrame(QString data, quint16 id, quint8 code)
{
    quint16 size = data.size()+3; // 2 for m_id; 1 for m_code;
    quint16 _id(id);
    quint8 _code(code);

    data.replace(QChar(' '), QChar('\n'));
    data[size-3] = QChar('\n');
    size++; // we just have added \n character


    QByteArray frame((char*)&size, 2);
    frame.append((char*)&_id, 2);
    frame.append((char*)&_code, 1);
    frame.append(data);

    return frame;

}

QStringList Frame::getArg(char*  data)
{
    QString args(data);
    args.section('\n', 0);
    QStringList list = args.split('\n', QString::SkipEmptyParts);

    return list;
}


quint16 Frame::getSize(void) const
{
    return m_size;
}
quint16 Frame::getId(void) const
{
    return m_id;
}
quint8 Frame::getCode(void) const
{
    return m_code;
}
QStringList Frame::getArgList(void) const
{
    return m_argList;
}


