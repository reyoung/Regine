#ifndef RSTORAGE_H
#define RSTORAGE_H

#include <QQuickItem>


class RStoragePrivate;
class RStorage : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(RStorage)
    Q_PROPERTY(QString databaseName READ databaseName WRITE setDatabaseName NOTIFY databaseNameChanged)

public:
    explicit RStorage(QQuickItem *parent = 0);
    QString databaseName()const;
    void setDatabaseName(const QString& name);

    /// Put Keys Into Storage, which will presist to device
    /// @param key: Presist key
    /// @param val: object to save
    /// @note: emit signal databaseNameChanged
    Q_INVOKABLE void put(const QString& key, const QVariant& val);

    /// Get Object From Storage
    /// @param key: Presist key
    /// @return: object that saved
    Q_INVOKABLE QVariant get(const QString& key)const;

    /// Get all keys of this storage
    /// @return: key array
    Q_INVOKABLE QStringList getAllKeys()const;

    /// Remove key and its value from storage
    Q_INVOKABLE bool clear(const QString& key);

    /// Clear All Keys in storage
    Q_INVOKABLE void clearAll();


    virtual ~RStorage();
signals:
    void databaseNameChanged(QString newName);
private:
    RStoragePrivate* m;
};

#endif // RSTORAGE_H
