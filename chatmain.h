#pragma once
#include <QHostAddress>
#include <QNetworkDatagram>
#include <QObject>
#include <QUdpSocket>
#include <QtQml>
quint16 port = 888888;
class chatmain : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUdpSocket socket READ socket WRITE setSocket NOTIFY socketChanged)
    QML_ELEMENT
public:
    explicit chatmain(QObject* parent = nullptr);
    void read();
    void write(const QHostAddress address, const unsigned short port, char* writedata);
    void broadcast(const unsigned short port, char* writedata);
    void multicast(const QHostAddress address, const unsigned short port, char* writedata);
    ~chatmain();
    QUdpSocket socket() const;
    void setSocket(QUdpSocket socket);

public slots:

private:
    QUdpSocket _socket;
signals:
    socketChanged();
}
