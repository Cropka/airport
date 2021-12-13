#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include <QObject>
#include "resource.h"

class ResourceFactory : public QObject
{
    Q_OBJECT
public:
    explicit ResourceFactory(QObject *parent = nullptr);
    virtual Resource* createResource() = 0;
signals:

};

#endif // RESOURCEFACTORY_H
