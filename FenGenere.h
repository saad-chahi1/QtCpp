#ifndef FENGENERE_H
#define FENGENERE_H

#include <QtWidgets>


class FenGenere : public QDialog
{
    public:
        FenGenere(QString &code, QWidget *parent);

    private:
        QTextEdit *codeGenere;
        QPushButton *fermer;
};

#endif // FENGENERE_H
