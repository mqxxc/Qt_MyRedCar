#include <QtWidgets/QApplication>
#include"awaken_replica.h"
#include<QTimer>
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    awaken_replica kl;
    QTimer::singleShot(10, [&a, &kl]() {
        kl.sendAwaken();
        a.quit();
        });
    a.exec();
    return 0;
}
