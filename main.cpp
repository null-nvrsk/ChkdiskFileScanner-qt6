#include <QCoreApplication>
#include <QtDebug>

#include <settings.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Settings appSettings;
    appSettings.load();

    appSettings.save();
    return a.exec();
}
