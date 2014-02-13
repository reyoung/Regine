#include "regine.h"
#include <QCoreApplication>



void initRegine(const QString &orgname, const QString &appname)
{
    QCoreApplication::setOrganizationName(orgname);
    QCoreApplication::setApplicationName(appname);

    qmlRegisterType<RStorage>("Regine", 1,0,"RStorage");
    qmlRegisterType<GameWindow>("Regine", 1,0,"GameWindow");
}
