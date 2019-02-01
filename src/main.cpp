#include "src/build.h"
#include "src/ui/MainWindow.h"

#include <QFileDialog>
#include <QtCore/QSettings>
#include <src/util/AppUtils.h>
#include <QtCore/QUuid>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    //todo: Implement language support
    /**
    QTranslator translator;

    if (translator.load("Turkish.qm", QLatin1String(":/translation")))
        QApplication::installTranslator(&translator);
     **/

    QApplication::setWindowIcon(QIcon(":/drawable/ic_launcher.png"));
    QApplication::setApplicationVersion(QString(TREBLESHOT_VERSION_NAME));

    MainWindow mainWindow;
    mainWindow.show();

    return QApplication::exec();
}
