#include "chatmain.h"

chatmain::chatmain(QObject *parent = nullptr)
{
    _socket = new QUdpSocket(parent);
    if (!QUdpSocket::bind(port)) {
        perror("bind error!");
        exit(1);
    }
}

void chatmain::read()
{
    char *data[];
    quint16 *port2 = nullptr;
    QHostAddress *address = nullptr;
    if (QUdpSocket::hasPendingDatagrams() != -1) {
        quint64 q64;
        q64 = QUdpSocket::pendingDatagramSize();
        int i = QUdpSocket::readDatagram(data, q64, address, port2);
        if (i == -1) {
            perror("readDatagram error!");
            exit(1);
        }
    }
}

void chatmain::write(const QHostAddress address, const unsigned short port, char *writedata)
{
    _socket.writeDatagram(QNetworkDatagram(writedata, address, port));
}

void chatmain::broadcast(const unsigned short port, char *writedata)
{
    _socket.writeDatagram(QNetworkDatagram(writedata, QHostAddress::Broadcast, port));
}

//组播ip必须是D类ip
//D类IP段 224.0.0.0 到 239.255.255.255
//且组播地址不能是224.0.0.1
void chatmain::multicast(const QHostAddress address, const unsigned short port, char *writedata)
{
    _socket.bind(QHostAddress::AnyIPv4, port); //根据Qt示例，组播的话IPv4和v6分开的
    _socket.joinMulticastGroup(address);       //QHostAddress("224.0.0.2")
    _socket.writeDatagram(QNetworkDatagram(writedata, address, port)); //QHostAddress("224.0.0.2")
}

chatmain::~chatmain()
{
    _socket.disconnectFromHost();
    _socket.close();
    _socket.abort();
}
