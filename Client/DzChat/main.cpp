#include "MainWindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "DzChat_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QFile qss(":/sytle/stylesheet.qss");

    if(qss.open(QFile::ReadOnly))
    {
        qDebug() << "open qss Success";
        QString style = QLatin1String(qss.readAll());
        qDebug() << style;
        a.setStyleSheet(style);
        qss.close();
    }
    else{
        qDebug("Open qss failed");
    }

    MainWindow w;
    w.show();
    return a.exec();
}
