#include <QStackedWidget>
#include <QMenu>
#include <QToolBar>
#include <QLineEdit>
#include <QIcon>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Epdf"));
    setWindowIcon(QIcon(tr(":/qpdf_icon")));
    setTool
    m_busy = false;
    m_pages = 0;
    m_zoom = 72;
    m_currentpage = 0;
    m_fullscreen = false;
    m_renderok = false;

    createToolBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createToolBar()
{

}
