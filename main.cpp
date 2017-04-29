#include <unistd.h>
#include <xsSamServer/xssamserver.h>
#include <xslib/xslib.h>

xsSamServer* sam;
QString buffer;

void connect()
{
    QString address, port;
    xsConsole() << "Serious Manager " << " by Luca \"Nobel3D\" Gasperini" << endl
                << "Enter your server ip -> ";
    xsConsole() >> address;
    xsConsole() << "Enter your server port ->";
    xsConsole() >> port;

    xsConsole() << "Trying to connect: " << address << "\n";
    sam = new xsSamServer(address,port.toInt());
    sam->Connect();
    do {
    xsConsole() << "Login -> ";
    } while(sam->Login(xsConsole::ReadPasswd()) == FAIL);
}

int main(int argc, char **argv)
{

    connect();
    sam->Start();

    while(true)
    {
        buffer = xsConsole::Shell(sam->server->getAddress(), sam->server->getPort());
        if(buffer == "quit")
            break;
        sam->server->WriteStream(buffer);
        sleep(1);
        xsConsole() << sam->input->strData;
    }
    sam->server->Close();
    return 0;
}
