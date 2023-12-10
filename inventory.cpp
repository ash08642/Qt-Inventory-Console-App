#include "inventory.h"

Inventory::Inventory(QObject *parent)
    : QObject{parent}
{
    load();
}

void Inventory::add(QString name, int quantity)
{
    if(items.contains(name))    // if item exists update the quantity
    {
        items[name] += quantity;
    }
    else    // else add a new key value pair
    {
        items.insert(name,quantity);
    }
}

void Inventory::remove(QString name, int quantity)
{
    if(items.contains(name))    // if item exists update the quantity
    {
        items[name] -= quantity;
        if(items.value(name) > 0)
        {
            items.remove(name);
            qInfo() << "Item" << name << "removed";
        }
    }
    else
    {
        qWarning() << "Item:" << name << "does not exist";
    }
}

void Inventory::list()
{
    qInfo() << "Items: " << items.size();
    foreach (QString key, items.keys()) {
        qInfo() << key << "=" << items.value(key);
    }
}

void Inventory::save()
{
    QFile file("inventory.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
        qCritical() << "Could not save file:" << file.errorString();
        return;
    }

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_6_6);

    int len = items.size();
    stream << len;

    qInfo() << "Number of items to save:" << len;

    foreach (QString key, items.keys()) {
        qInfo() << "Saving:" << key;
        stream << key;
        stream << items.value(key);
    }

    file.close();
    qInfo() << "File Saved Succesfully";
}

void Inventory::load()
{
    QFile file("inventory.txt");

    if(!file.exists())
    {
        qWarning() << "File does not exist";
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Could not save file:" << file.errorString();
        return;
    }

    QDataStream stream(&file);
    if(stream.version() != QDataStream::Qt_6_6)
    {
        qCritical() << "Wrong data stream version";
        file.close();
        return;
    }

    items.clear();
    int max;
    stream >> max;
    qInfo() << "Number of items to load:" << max;

    for(int i = 0; i < max; i++)
    {
        QString key;
        int quantity;

        stream >> key;
        stream >> quantity;

        items.insert(key,quantity);
    }

    file.close();
    qInfo() << "File Loaded Succesfully";
}
