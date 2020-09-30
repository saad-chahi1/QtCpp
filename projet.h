#ifndef PROJET_H
#define PROJET_H

#include <QtWidgets>
#include <QtCore>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QtSql>
#include <QSqlDatabase>

class Projet : public QWidget
{
    Q_OBJECT

    public:
    Projet();

    public slots:
    void genererCode();
    void SavePDF();
    void on_pushButton_clicked();

    private:
    QLineEdit *nom;
    QLineEdit *prenom;

    QPushButton *PDF;

    QRadioButton *niveau1;
    QRadioButton *niveau2;
    QRadioButton *niveau3;
    QRadioButton *niveau4;
    QRadioButton *niveau5;

    QRadioButton *info;
    QRadioButton *indus;
    QRadioButton *reseau;
    QRadioButton *gpmc;

    QGroupBox *groupCommentaires;
    QDateEdit *DateDeNaissance;
    QDateEdit *DateDeCreation;
    QLineEdit *LaVille;
    QLineEdit *cin;

    QPushButton *generer;
    QPushButton *quitter;
};


#endif // PROJET_H
