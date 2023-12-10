#include <QCoreApplication>
#include <QTextStream>
#include "inventory.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Inventory inventory;

    qInfo() << "Available Commands:";
    qInfo() << "add item <name> <quantity>";
    qInfo() << "remove item <name> <quantity>";
    qInfo() << "save";
    qInfo() << "load";
    qInfo() << "list";
    qInfo() << "quit";

    QTextStream stream(stdin);

    while(true)
    {
        qInfo() << "Enter a command";
        QString line = stream.readLine();
        QStringList list = line.split(" ");
        if(list.size() <= 0)
        {
            break;
        }

        QString command = list.at(0).toUpper();
        if(command == "QUIT")
        {
            //a.exit(0);
            break;
        }

        if(command == "LIST") inventory.list();
        if(command == "LOAD") inventory.load();
        if(command == "SAVE") inventory.save();

        if(command == "ADD" || command == "REMOVE")
        {
            if(list.size() < 3)
            {
                qWarning() << "Not enough info";
                continue;
            }

            QString name = list.at(1);
            bool ok;
            int quantity;
            quantity = list.at(2).toInt(&ok);
            if(!ok)
            {
                qWarning() << "Invalid quantity!";
                continue;
            }
            if(command == "ADD") inventory.add(name, quantity);
            if(command == "REMOVE") inventory.remove(name, quantity);
        }
    }

    inventory.save();
    qInfo() << "Complete";

    //return a.exec();
    return 0;
}
