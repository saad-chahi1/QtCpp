#include "FenGenere.h"


FenGenere::FenGenere(QString &code, QWidget *parent = 0) : QDialog(parent)
{
    codeGenere = new QTextEdit();
    codeGenere->setPlainText(code);
    codeGenere->setReadOnly(true);
    codeGenere->setFont(QFont("Courier"));
    codeGenere->setLineWrapMode(QTextEdit::NoWrap);
    fermer = new QPushButton("Fermer");

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(codeGenere);
    layoutPrincipal->addWidget(fermer);

    resize(350, 490);
    setLayout(layoutPrincipal);
    connect(fermer, SIGNAL(clicked()), this, SLOT(accept()));
}
