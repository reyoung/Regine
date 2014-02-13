#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QQuickItem>

class RStorage;
class GameWindowPrivate;
class GameWindow : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(GameWindow)
    Q_PROPERTY(RStorage* storage READ storage NOTIFY storageChanged)
    Q_PROPERTY(bool fullscreen READ fullscreen WRITE setFullscreen NOTIFY fullscreenChanged)
    Q_PROPERTY(PlatformType platformType READ platformType NOTIFY platformTypeChanged)
    Q_PROPERTY(bool resizeable READ resizeable NOTIFY resizeableChanged)
    Q_PROPERTY(qreal logicalHeight READ logicalHeight WRITE setLogicalHeight NOTIFY logicalHeightChanged)
    Q_PROPERTY(qreal logicalWidth READ logicalWidth WRITE setLogicalWidth NOTIFY logicalWidthChanged)
    Q_PROPERTY(QSizeF logicalSize READ logicalSize WRITE setLogicalSize NOTIFY logicalSizeChanged)
    Q_ENUMS(PlatformType)
public:
    enum PlatformType{
        Windows,
        Android
    };

    explicit GameWindow(QQuickItem *parent = 0);

    RStorage *storage()const;

    virtual ~GameWindow();

    bool fullscreen()const;

    void setFullscreen(bool full=true);

    PlatformType platformType()const;

    bool resizeable()const;

    void switchOrientation();

    qreal logicalWidth()const;

    qreal logicalHeight()const;

    void setLogicalWidth(qreal lw);

    void setLogicalHeight(qreal lh);

    QSizeF logicalSize()const;

    void setLogicalSize(const QSizeF& sz);

signals:
    void storageChanged(RStorage* );
    void fullscreenChanged(bool );
    void platformTypeChanged(PlatformType);
    void resizeableChanged(bool);
    void logicalWidthChanged(qreal lw);
    void logicalHeightChanged(qreal);
    void logicalSizeChanged(QSizeF);
private:
    void zoomToSize(int id);
private:
    GameWindowPrivate* m;
};

#endif // GAMEWINDOW_H
