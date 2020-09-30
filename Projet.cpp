#include <projet.h>

#include <FenGenere.h>

Projet::Projet(){

        // Groupe : Définition de la classe
        nom = new QLineEdit;
        prenom = new QLineEdit;

        QFormLayout *definitionLayout = new QFormLayout;
        definitionLayout->addRow("&Nom :", nom);
        definitionLayout->addRow("&Prénom :", prenom);

        QGroupBox *groupDefinition = new QGroupBox("Le nom et le prénom");
        groupDefinition->setLayout(definitionLayout);

        // Groupe : Niveau

        niveau1 = new QRadioButton("Première année cycle préparatoire");
        niveau2 = new QRadioButton("Deuxième année cycle préparatoire");
        niveau3 = new QRadioButton("Première année cycle d'ingénieur");
        niveau4 = new QRadioButton("Deuxième année cycle d'ingénieur");
        niveau5 = new QRadioButton("Troisième année cycle d'ingénieur");

        QVBoxLayout *optionsLayout = new QVBoxLayout;
        optionsLayout->addWidget(niveau1);
        optionsLayout->addWidget(niveau2);
        optionsLayout->addWidget(niveau3);
        optionsLayout->addWidget(niveau4);
        optionsLayout->addWidget(niveau5);

        QGroupBox *groupOptions = new QGroupBox("Le Niveau");
        groupOptions->setLayout(optionsLayout);

        // Groupe : Classe

        info   = new QRadioButton("Génie informatique");
        indus  = new QRadioButton("Génie industriel");
        reseau = new QRadioButton("Génie réseau et télécom");
        gpmc   = new QRadioButton("Génie céramique");

        QVBoxLayout *classLayout = new QVBoxLayout;
        classLayout->addWidget(info);
        classLayout->addWidget(indus);
        classLayout->addWidget(reseau);
        classLayout->addWidget(gpmc);

        groupCommentaires = new QGroupBox("La Filiére (Réserver pour le cycle d'ingénieur)");
        groupCommentaires->setCheckable(true);
        groupCommentaires->setChecked(false);
        groupCommentaires->setLayout(classLayout);

        // Groupe : Commentaires

        LaVille = new QLineEdit;
        cin = new QLineEdit;
        DateDeNaissance = new QDateEdit;
        DateDeNaissance->setDate(QDate::currentDate());
        DateDeCreation = new QDateEdit;
        DateDeCreation->setDate(QDate::currentDate());

        QFormLayout *commentairesLayout = new QFormLayout;
        commentairesLayout->addRow("La &Ville :", LaVille);
        commentairesLayout->addRow("Le &Cin :", cin);
        commentairesLayout->addRow("La Date de &naissance :", DateDeNaissance);
        commentairesLayout->addRow("La Da&te de création :", DateDeCreation);

        QGroupBox *groupInfos = new QGroupBox("D'autre informations (Facultatives)");
        groupInfos->setLayout(commentairesLayout);

        // Layout : boutons du bas (g?n?rer, quitter...)
        generer = new QPushButton("&Générer !");
        quitter = new QPushButton("&Quitter");

        PDF = new QPushButton("Télécharger le fichier");

        QHBoxLayout *boutonsLayout = new QHBoxLayout;
        boutonsLayout->setAlignment(Qt::AlignRight);

        boutonsLayout->addWidget(PDF);
        boutonsLayout->addWidget(generer);
        boutonsLayout->addWidget(quitter);


        // D?finition du layout principal, du titre de la fen?tre, etc.

        QVBoxLayout *layoutPrincipal = new QVBoxLayout;
        layoutPrincipal->addWidget(groupDefinition);
        layoutPrincipal->addWidget(groupOptions);
        layoutPrincipal->addWidget(groupCommentaires);
        layoutPrincipal->addWidget(groupInfos);
        layoutPrincipal->addLayout(boutonsLayout);

        this->setLayout(layoutPrincipal);
        setWindowTitle("La formulaire d'inscription");
        resize(400, 450);


        // Connexions des signaux et des slots
        connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
        connect(generer, SIGNAL(clicked()), this, SLOT(genererCode()));

        connect(PDF, SIGNAL(clicked()), this, SLOT(SavePDF()));
}

void Projet::genererCode()
{

    // On v?rifie que le nom de la classe n'est pas vide, sinon on arr?te
    if (nom->text().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Veuillez entrer Votre nom ");
        return; // Arr?t de la m?thode
    }
    else if (prenom->text().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Veuillez entrer Votre prenom ");
        return; // Arr?t de la m?thode
    }

    // Si tout va bien, on g?n?re le code
    QString code;

        code += "Date de création : " + DateDeCreation->date().toString() + "\n\n";
        code += "####################################\n";
        code += "####################################\n";
        code += "Le nom d'étudiant : " + nom->text() + "\n";
        code += "Le prenom d'étudiant : " + prenom->text() + "\n";
        code += "Le cin d'étudiant : " + cin->text() + "\n";
        code += "La Ville : " + LaVille->text() + "\n";
        code += "Date de Naissance : " + DateDeNaissance->date().toString() + "\n\n\n";

    if (niveau1->isChecked())
    {
        code += "#Première année cycle préparatoire\n";
    }
    else if (niveau2->isChecked())
    {
        code += "#Deuxière année cycle préparatoire\n";
    }
    else if (niveau3->isChecked())
    {
        code += "#Première année cycle d'ingénieur\n";
    }
    else if (niveau4->isChecked())
    {
        code += "#deuxième année cycle d'ingénieur\n";
    }
    else if (niveau5->isChecked())
    {
        code += "#troisième année cycle d'ingénieur\n";
    }

    if (info->isChecked())
    {
        code += "#Génie informatique\n";
    }
    else if (indus->isChecked())
    {
        code += "#Génie industriel\n";
    }
    else if (reseau->isChecked())
    {
        code += "#Génie réseau et télécom\n";
    }
    else if (gpmc->isChecked())
    {
        code += "#Génie Procédés et Matériaux Céramiques\n";
    }

    //la base de donnees
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("qtdb");
    db.setPassword("");

    QSqlQuery query;
                query.prepare("INSERT INTO sample1.db (nom, prenom, dateNaissance, dateCreation, cin) VALUES (:nom, :prenom, :dateDeNaissance, :dateDeCreation, :cin))");
                query.bindValue(":nom", nom->text());
                query.bindValue(":prenom", prenom->text());
                query.bindValue(":dateNaissance", DateDeNaissance->date().toString());
                query.bindValue(":dateCreation", DateDeCreation->date().toString());
                query.bindValue(":cin", cin->text());
                query.exec();

    if (db.open())
    {
        QMessageBox::information(this, "Connection", "les informations sont stockeés dans la BDD ");
        // On cr?e puis affiche la fen?tre qui affichera le code g?n?r?, qu'on lui envoie en param?tre
        FenGenere *fenetreCode = new FenGenere(code, this);
        fenetreCode->exec();
        return; // Arr?t de la m?thode
    }else{
        QMessageBox::warning(this, "Erreur", "les informations ne sont pas stockeés dans la BDD ");
        // On cr?e puis affiche la fen?tre qui affichera le code g?n?r?, qu'on lui envoie en param?tre
        FenGenere *fenetreCode = new FenGenere(code, this);
        fenetreCode->exec();
        return; // Arr?t de la m?thode
    }


}
void Projet::SavePDF(){
    QString code;

        code += "############################# Le fichier d'inscription #############################\n\n";
        code += "Date de création : " + DateDeCreation->date().toString() + "\n\n";
        code += "########################################################################\n";
        code += "\n########################################################################\n";
        code += "\nLe nom d'étudiant : " + nom->text() + "\n";
        code += "Le prenom d'étudiant : " + prenom->text() + "\n";
        code += "Le cin d'étudiant : " + cin->text() + "\n";
        code += "La Ville : " + LaVille->text() + "\n";
        code += "Date de Naissance : " + DateDeNaissance->date().toString() + "\n\n\n";

    if (niveau1->isChecked())
    {
        code += "#Première année cycle préparatoire\n";
    }
    else if (niveau2->isChecked())
    {
        code += "#Deuxière année cycle préparatoire\n";
    }
    else if (niveau3->isChecked())
    {
        code += "#Première année cycle d'ingénieur\n";
    }
    else if (niveau4->isChecked())
    {
        code += "#deuxième année cycle d'ingénieur\n";
    }
    else if (niveau5->isChecked())
    {
        code += "#troisième année cycle d'ingénieur\n";
    }

    if (info->isChecked())
    {
        code += "#Génie informatique\n";
    }
    else if (indus->isChecked())
    {
        code += "#Génie industriel\n";
    }
    else if (reseau->isChecked())
    {
        code += "#Génie réseau et télécom\n";
    }
    else if (gpmc->isChecked())
    {
        code += "#Génie Procédés et Matériaux Céramiques\n\n\n";

    }
    code += "\n\n\n########################################################################\n";
    code += "Vous avez fait l'inscription via une application crée par le framework Qt creator et c++\net puisque nous sommes dans une période s'insiste de prendre les mésures de sécurité je voudrais donc vous inviter\nà partager l'application chez vous pour facilité l'inscription scolaire";
    code += "\n########################################################################\n";
    code += "\n\n\nMERCI POUR VOTRE COLLABORATION.\n";

        const QString filename("C:/Users/user/Desktop/Catalogue.pdf");

        QPdfWriter pdfwriter(filename);
        pdfwriter.setPageSize(QPageSize(QPageSize::A4));
        pdfwriter.setPageMargins(QMargins(30, 30, 30, 30));
        QPainter painter(&pdfwriter);

        painter.setFont(QFont("Times", 10));
        QRect r = painter.viewport();
        painter.drawText(r, Qt::AlignLeft, code);
        painter.end();

}
void Projet::on_pushButton_clicked()
{
    SavePDF();
}
