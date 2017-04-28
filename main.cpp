#include <QDebug>
#include <iostream>
#include <unistd.h>
#include <xsSamServer/xssamserver.h>
#include <xslib/xslib.h>

#define CERROR(check, text) { if(check) { qWarning() << "[ERR] " << text << endl; \
                                          return -1; }                      }

#define OK 0

#define endl "\n"

using namespace std;

QString sysApp;
QString netAddress;
QString netPasswd;
QString netPort;

Rcon* rcClient;
Fetch* input;

QString inputBuffer;

void connect()
{
    xsConsole() << "Serious Manager " << " by Luca \"Nobel3D\" Gasperini" << endl
                << "Enter your server ip -> ";
    xsConsole() >> netAddress;
    xsConsole() << "Enter your server port ->";
    xsConsole() >> netPort;

    xsConsole() << "Trying to connect: " << netAddress << "\n";
    rcClient = new Rcon;
    if(rcClient->Connect(netAddress, netPort.toInt()) != 0)
        return;
}
void login()
{
    xsConsole() << "Login -> ";
    if(rcClient->Login(xsConsole::ReadPasswd()) != 0)
        return;
    xsConsole() << endl;
}

void start()
{
    input = new Fetch(rcClient);
    input->start();

    while(inputBuffer != "quit")
    {
        sleep(1);
        if(input->flag == 1)
        {
            xsConsole() << input->strData;
            xsConsole() << "[" << rcClient->getAddress() << ":" << rcClient->getPort() << "]$ ";
        }
        xsConsole() >> inputBuffer;
        rcClient->WriteStream(inputBuffer);
    }
    rcClient->Close();
}

int main(int argc, char **argv)
{
    connect();
    login();
    start();
    return 0;
}
