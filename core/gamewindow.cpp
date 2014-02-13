#include "gamewindow.h"
#include "rstorage.h"
#include <QQuickView>
#include <QtGui>
#include <QHash>

class GameWindowPrivate{
public:
    RStorage* storage;
    qreal logicalWidth;
    qreal logicalHeight;
    int   tickTimerId;
    int   fpsCnt;
    int   fpsTimerId;
    int   lastFps;
    QHash<QObject*, int> mids;
};


GameWindow::GameWindow(QQuickItem *parent) :
    QQuickItem(parent),m(new GameWindowPrivate)
{
    m->storage = new RStorage(this);
    m->logicalHeight = 570;
    m->logicalWidth = 360;
    zoomToSize(0);
    switchOrientation();
    m->fpsCnt = 0;
    m->lastFps = 0;
    m->tickTimerId = startTimer(1000/59.0);
    m->fpsTimerId = startTimer(1000);
}

RStorage *GameWindow::storage() const
{
    return m->storage;
}

GameWindow::~GameWindow()
{
    if(m!=nullptr){
        delete m;
        m = nullptr;
    }
}

inline static QWindow* getTopLevelWindow(){
    QWindowList list = QGuiApplication::topLevelWindows();
    if(list.size()==1){
        return list.at(0);
    } else {
        return nullptr;
    }
}

bool GameWindow::fullscreen() const
{
    if(this->platformType()==Android){
        return true;
    } else {
        auto view = getTopLevelWindow();
        if(view!=nullptr){
            return view->windowState()&Qt::WindowFullScreen;
        } else {
            qWarning()<<"Cannot Get QtQuick View to tell is full screen or not";
            return false;
        }
    }
}

void GameWindow::setFullscreen(bool full)
{
    if(platformType()==Android){
        qWarning()<<"set full screen is not supported in android";
    } else {
        auto view =getTopLevelWindow();
        if(view!=nullptr){
            int state = view->windowState();
            if(full){
                state |= Qt::WindowFullScreen;
            } else {
                state &= ~Qt::WindowFullScreen;
            }
            view->setWindowState(Qt::WindowState(state));
            emit this->fullscreenChanged(full);
        } else {
            qWarning()<<"There are multiple top level window, cannot set full screen";
        }
    }
}

GameWindow::PlatformType GameWindow::platformType() const
{
#ifdef Q_OS_ANDROID
    return GameWindow::Android;
#elif defined Q_OS_WIN
    return GameWindow::Windows;
#endif
}

bool GameWindow::resizeable() const
{
    if(platformType() == GameWindow::Android){
        return false;
    } else if(platformType() == GameWindow::Windows){
        return true;
    } else {
        return false;
    }
}

void GameWindow::switchOrientation()
{
    if(platformType()==GameWindow::Windows){
        qreal h = height();
        qreal w = width();
        std::swap(h,w);
        this->setHeight(h);
        this->setWidth(w);
    } else {

    }
}

qreal GameWindow::logicalWidth() const
{
    return m->logicalWidth;
}

qreal GameWindow::logicalHeight() const
{
    return m->logicalHeight;
}

void GameWindow::setLogicalWidth(qreal lw)
{
    m->logicalWidth = lw;
    emit this->logicalWidthChanged(lw);
}

void GameWindow::setLogicalHeight(qreal lh)
{
    m->logicalHeight = lh;
    emit this->logicalHeightChanged(lh);
}

QSizeF GameWindow::logicalSize() const
{
    return QSizeF(this->logicalWidth(), this->logicalHeight());
}

void GameWindow::setLogicalSize(const QSizeF &sz)
{
    this->setLogicalWidth(sz.width());
    this->setLogicalHeight(sz.height());
    emit this->logicalSizeChanged(sz);
}

int GameWindow::fps() const
{
    return m->lastFps;
}

static inline void invokeTick(QObject* obj, GameWindowPrivate* m){
    if(obj!=nullptr){
        int mid = -1;
        auto meta = obj->metaObject();
        if(m->mids.contains(obj)){
            mid = m->mids[obj];
        } else {
            for(int i=0;i<meta->methodCount();++i){
                auto me = meta->method(i);
                if(me.name()=="tick"){
                    mid = i;
                    break;
                }
            }
            m->mids.insert(obj, mid);
        }
        if(mid != -1){
            auto method = meta->method(mid);
            method.invoke(obj);
        }
        auto children = obj->children();
        for(auto t : children){
            invokeTick(t,m);
        }
    }
}


void GameWindow::timerEvent(QTimerEvent * ev)
{
    if(ev->timerId() == m->tickTimerId){
        ++m->fpsCnt;
        invokeTick(this, m);
    } else if(ev->timerId() == m->fpsTimerId){
        m->lastFps  = m->fpsCnt;
        m->fpsCnt = 0;
        emit this->fpsChanged(m->lastFps);
    }
    QQuickItem::timerEvent(ev);
}

void GameWindow::zoomToSize(int id)
{
    if(platformType() == GameWindow::Windows){
        qreal width = 570;
        qreal height = 360;
        switch(id){
        case 1:
            width = 960;
            height = 640;
            break;
        case 2:
            width = 480;
            height = 320;
            break;
        case 3:
            width = 1136;
            height = 640;
            break;
        case 4:
            width = 640;
            height = 360;
            break;
        case 5:
            width = 854;
            height = 480;
            break;
        case 6:
            width = 800;
            height = 480;
            break;
        case 7:
            width = 1027;
            height = 760;
            break;
        }
        this->setWidth(width);
        this->setHeight(height);
    }
}
