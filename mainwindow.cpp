#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Jathu's Notepad");

    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_New_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());

}


void MainWindow::on_action_Open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"open");
    QFile file(filename);
    currentFile=filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot open file : "+file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text=in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSaveAs_triggered()
{
    QString filename =QFileDialog::getSaveFileName(this,"save as");
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot save file : "+file.errorString());
        return;
    }
    currentFile=filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    file.close();



}


void MainWindow::on_actionSave_2_triggered()
{
    QFile file(currentFile);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot save file : "+file.errorString());
        return;
    }

    setWindowTitle(currentFile);
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    QMessageBox msgBox;
    msgBox.setText("The document has been saved.");
    msgBox.exec();
    file.close();

}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();

}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();

}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();

}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();

}

