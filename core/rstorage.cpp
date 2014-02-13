#include "rstorage.h"
#include <QtCore>

class RStoragePrivate {
public:
    QString databaseName;

    QSettings settings;
};


RStorage::RStorage(QQuickItem *parent) :
    QQuickItem(parent),m(new RStoragePrivate)
{
    this->m->settings.beginGroup("tmp");
    this->setDatabaseName("storage.db");
}

QString RStorage::databaseName() const
{
    return this->m->databaseName;
}

void RStorage::setDatabaseName(const QString &name)
{
    this->m->databaseName = name;
    m->settings.endGroup();
    m->settings.beginGroup(name);
    emit this->databaseNameChanged(name);
}


void RStorage::put(const QString &key, const QVariant &val)
{
    m->settings.setValue(key, val);
}

QVariant RStorage::get(const QString &key) const
{
    QVariant retv = m->settings.value(key);
    return retv;
}

QStringList RStorage::getAllKeys() const
{
    QStringList retv = m->settings.childKeys();
    return retv;
}

bool RStorage::clear(const QString &key)
{
    bool rm = false;
    if(m->settings.contains(key)){
        m->settings.remove(key);
        rm = true;
    }
    return rm;
}

void RStorage::clearAll()
{
    m->settings.remove("");
}

RStorage::~RStorage()
{
    if(m!=nullptr){
        delete m;
        m = nullptr;
    }
}
