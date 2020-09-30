#include <QApplication>
#include <QLineEdit>
#include <QtWidgets>
#include <QPrinter>
#include <projet.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    Projet fenetre;

    fenetre.show();

    return app.exec();
}
