#ifndef INVENTORY_H
#define INVENTORY_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include <QFile>
#include <QDataStream>

class Inventory : public QObject
{
    Q_OBJECT
public:
    explicit Inventory(QObject *parent = nullptr);

    void add(QString name, int quantity);
    void remove(QString name, int quantity);
    void list();

signals:

public slots:
    void save();
    void load();

private:
    QMap<QString,int> items;
};

#endif // INVENTORY_H
