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

#include <QDesktopServices>
#include <QUrl>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}
//----------------------------------------------------------------------
void MainWindow::createConnects()
{
    //tray
    connect(trIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showHide(QSystemTrayIcon::ActivationReason)));

    // menu file
    connect(ui->action_File_Close, SIGNAL(triggered()), this, SLOT(close()));


    // menu about
    connect(ui->action_About_About, SIGNAL(triggered()), about, SLOT(show()));
    connect(ui->action_About_About_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->action_About_Site, SIGNAL(triggered()), this, SLOT(aboutOpenSite()));
}
//----------------------------------------------------------------------
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
//----------------------------------------------------------------------
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
//----------------------------------------------------------------------
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
//----------------------------------------------------------------------
void MainWindow::aboutOpenSite()
{
    QDesktopServices::openUrl(QUrl(GL_WEB_SITE));
}
//----------------------------------------------------------------------
