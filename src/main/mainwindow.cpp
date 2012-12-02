/*
  The basis for creating an application
  (QMainwindow)

  Tray + translate + about dialog + mainwindow

  Author: Sapronov Alexander
  E-mail: sapronov.alexander92@gmail.com
  */

#include "ui_mainwindow.h" /// ui

#include "defines.h" /// defines
#include "mainwindow.h" ///
#include "about.h" /// aboutdialog
#include "debughelper.h"
#include "filecommon.h"

#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QProgressDialog>

#include <QDesktopWidget> /// moved to center

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    about(new AboutDialog(this))
{
    ui->setupUi(this);

    createActions(); // create action for tray
    createTrayIcon(); // add actionts to tray menu
    createConnects(); // moved func
    trIcon->show();  //display tray

    //    ui->LEInputFolder->setText(QDir::currentPath());
    //    ui->LEOutputFolder->setText(QDir::currentPath() + "/output");

    QString t_str = "/home/files/Develop/git/QCSMnist/QCSMnist/resources/testData";
    ui->LEInputTestDataFolder->setText(t_str);

    t_str = "/home/files/Develop/git/QCSMnist/QCSMnist-build/build/bin/testData/output";
    ui->LEOutputTestDataFolder->setText(t_str);

    t_str = "/home/files/Develop/git/QCSMnist/QCSMnist/resources/trainData";
    ui->LEInputTrainDataFolder->setText(t_str);

    t_str = "/home/files/Develop/git/QCSMnist/QCSMnist-build/build/bin/trainData/output";
    ui->LEOutputTrainDataFolder->setText(t_str);


    /// moved to center desktop
    QRect rect = QApplication::desktop()->availableGeometry(this);
    this->move(rect.width() / 2 - this->width() / 2,
               rect.height() / 2 - this->height() / 2);
    /// maximized
    //    this->showMaximized();

}

MainWindow::~MainWindow()
{
    delete ui;
}
//------------------------------------------------------------------------------
void MainWindow::createConnects()
{
    //tray
    connect(trIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showHide(QSystemTrayIcon::ActivationReason)));

    // menu file
    connect(ui->action_File_Close, SIGNAL(triggered()), this, SLOT(close()));

    // buttons
    connect(ui->pBBrowseInputTestDataFolder, SIGNAL(clicked()), SLOT(browseInputTestDataFolder()));
    connect(ui->pBBrowseOutputTestDataFolder, SIGNAL(clicked()), SLOT(browseOutputTestDataFolder()));
    connect(ui->pBBrowseInputTrainDataFolder, SIGNAL(clicked()), SLOT(browseInputTrainDataFolder()));
    connect(ui->pBBrowseOutputTrainDataFolder, SIGNAL(clicked()), SLOT(browseOutputTrainDataFolder()));
    connect(ui->pBGenerate, SIGNAL(clicked()), SLOT(generateSets()));

    // menu about
    connect(ui->action_About_About, SIGNAL(triggered()), about, SLOT(show()));
    connect(ui->action_About_About_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->action_About_Site, SIGNAL(triggered()), this, SLOT(aboutOpenSite()));
}
//------------------------------------------------------------------------------
void MainWindow::showHide(QSystemTrayIcon::ActivationReason r)
{
    if (r == QSystemTrayIcon::Trigger)
    {
        if ( !this->isVisible() )
        {
            this->show();
        }
        else
        {
            this->hide();
        }
    }
}
//------------------------------------------------------------------------------
void MainWindow::createTrayIcon()
{
    trIcon = new QSystemTrayIcon();  //init
    trIcon->setIcon(QIcon(":/images/img.png"));  //set ico

    trayIconMenu = new QMenu(this);  // create menu
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trIcon->setContextMenu(trayIconMenu); //set menu
}
//------------------------------------------------------------------------------
void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("&Hide"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("&Expand"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("Q&uit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
}
//------------------------------------------------------------------------------
void MainWindow::aboutOpenSite()
{
    QDesktopServices::openUrl(QUrl(GL_WEB_SITE));
}

//------------------------------------------------------------------------------
void MainWindow::browseInputTestDataFolder()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this
                                                          , tr("Select input folder")
                                                          , ""
                                                          , options);
    if (!directory.isEmpty())
    {
        ui->LEInputTestDataFolder->setText(directory);
        ui->LEOutputTestDataFolder->setText(directory + "/output/");

        //        loadListFilesToTable();
    }
}
//------------------------------------------------------------------------------
void MainWindow::browseOutputTestDataFolder()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this
                                                          , tr("Select output folder")
                                                          , ""
                                                          , options);
    if (!directory.isEmpty())
        ui->LEOutputTestDataFolder->setText(directory);
}
//------------------------------------------------------------------------------
void MainWindow::browseInputTrainDataFolder()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this
                                                          , tr("Select input folder")
                                                          , ""
                                                          , options);
    if (!directory.isEmpty())
    {
        ui->LEInputTrainDataFolder->setText(directory);
        ui->LEOutputTrainDataFolder->setText(directory + "/output/");

        //        loadListFilesToTable();
    }
}
//------------------------------------------------------------------------------
void MainWindow::browseOutputTrainDataFolder()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this
                                                          , tr("Select output folder")
                                                          , ""
                                                          , options);
    if (!directory.isEmpty())
        ui->LEOutputTrainDataFolder->setText(directory);
}
//------------------------------------------------------------------------------
void MainWindow::generateSets()
{
    myDebug() << "generate sets";
    QStringList numbers;
    if (ui->checkB_0->isChecked())
        numbers << "0";
    if (ui->checkB_1->isChecked())
        numbers << "1";
    if (ui->checkB_2->isChecked())
        numbers << "2";
    if (ui->checkB_3->isChecked())
        numbers << "3";
    if (ui->checkB_4->isChecked())
        numbers << "4";
    if (ui->checkB_5->isChecked())
        numbers << "5";
    if (ui->checkB_6->isChecked())
        numbers << "6";
    if (ui->checkB_7->isChecked())
        numbers << "7";
    if (ui->checkB_8->isChecked())
        numbers << "8";
    if (ui->checkB_9->isChecked())
        numbers << "9";


    QProgressDialog progressDialog("", "It's not Cancel", 0, 100);
    progressDialog.setValue(0);
    progressDialog.setGeometry(750, 300, 400, 170);
    progressDialog.show();

    QLabel overallLabel(&progressDialog);
    overallLabel.setGeometry(11, 10, 378, 20);
    overallLabel.setText("Generate...");
    overallLabel.show();


    for (int i = 0; i < numbers.size(); i++)
    {
        //        myDebug() << numbers.at(i);
        generateSet(numbers.at(i));
        progressDialog.setValue(100 * i / numbers.size());
        QApplication::processEvents();
    }
}
//------------------------------------------------------------------------------
void MainWindow::generateSet(QString number)
{
    QStringList listImages;
    listImages = getListImages(number, ui->LEInputTestDataFolder->text());
    // test data
    int testData = ui->spinBTestData->value();
    int trainData = ui->spinBTrainData->value();


    QStringList testImages;
    QStringList trainImages;

    // create output folders
    QDir dir(ui->LEOutputTestDataFolder->text());
    dir.mkpath(ui->LEOutputTestDataFolder->text());

    QDir dir2(ui->LEOutputTrainDataFolder->text());
    dir2.mkpath(ui->LEOutputTrainDataFolder->text());


    int t_count;

    int numberCount;
    // generate test set
    if (!listImages.isEmpty())
    {
        numberCount = getCountNumberTest(number.toInt());
        for (int i = 0; i < testData; i++)
        {
            QString t_number;
            do
            {
                t_count = rand() % numberCount;
                t_number = ui->LEInputTestDataFolder->text() + "/" + QString(number + "_%1").arg(t_count, 5, 10, QChar('0'))
                        + ".bmp";
            } while (testImages.contains(t_number));

            testImages << listImages.at(t_count);
            QImage img(listImages.at(t_count));
            QString t_path = ui->LEOutputTestDataFolder->text() +
                    "/" + QString(number + "_%1").arg(i, 5, 10, QChar('0'))
                    + ".bmp";

            img.save(t_path);
        }
    }

    //    myDebug() << testImages.size();


    listImages = getListImages(number, ui->LEInputTrainDataFolder->text());
    // generate train set

    if (!listImages.isEmpty())
    {
        numberCount = getCountNumberTrain(number.toInt());
        for (int i = 0; i < trainData; i++)
        {
            QString t_number;
            do
            {
                t_count = rand() % numberCount;
                t_number = ui->LEInputTrainDataFolder->text() + "/" + QString(number + "_%1").arg(t_count, 5, 10, QChar('0'))
                        + ".bmp";
            } while (trainImages.contains(t_number));

            testImages << listImages.at(t_count);
            QImage img(listImages.at(t_count));
            QString t_path = ui->LEOutputTrainDataFolder->text() +
                    "/" + QString(number + "_%1").arg(i, 5, 10, QChar('0'))
                    + ".bmp";
//            myDebug() << t_path;

            img.save(t_path);
        }
    }
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

