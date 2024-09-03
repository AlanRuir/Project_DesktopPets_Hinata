#include <QGuiApplication>
#include <QApplication>
#include <QIcon>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <hinata.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Hinata");
    QIcon appIcon;
    appIcon.addFile("://img/orange_vision_logo.png", QSize(), QIcon::Normal, QIcon::Off);
    app.setWindowIcon(appIcon);

    Hinata hinata;
    hinata.setWindowFlags(hinata.windowFlags() | Qt::WindowStaysOnTopHint);
    hinata.show();

    return app.exec();
}