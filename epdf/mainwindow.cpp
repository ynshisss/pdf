#include <QStackedWidget>
#include <QMenu>
#include <QToolBar>
#include <QLineEdit>
#include <QAction>
#include <QVariant>
#include <QIcon>
#include <QSizePolicy>
#include <QLineEdit>
#include <QFileInfo>
#include <QtDebug>

#include "mainwindow.h"
#include "myoutputdev.h"
#include "library/fileselector.h"
#include "xpdf/PDFDoc.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("Epdf"));
    setWindowIcon(QIcon(tr(":/qpdf_icon")));

    m_busy = false;
    m_pages = 0;
    m_zoom = 72;
    m_currentpage = 0;
    m_fullscreen = false;
    m_renderok = false;
	m_doc = NULL;

    createToolBars();

    m_filesel = new FileSelector();
	connect(m_filesel, SIGNAL(closeMe()), this, SLOT(closeFileSelector()));
	connect(m_filesel, SIGNAL(fileSelected(const QString &)),
			this, SLOT(openFile(const QString &)));

    m_outdev = new MyOutputDev();
	connect(m_outdev, SIGNAL(selectionChanged(const QRect&)),
			this, SLOT(copyToClipboard(const QRect&)));

    m_stack = new QStackedWidget();
    m_stack->addWidget(m_outdev);
    m_stack->addWidget(m_filesel);


    setCentralWidget(m_stack);
    openFile();
}

MainWindow::~MainWindow()
{
	delete m_doc;
}


void MainWindow::createToolBars()
{
    QAction *act = 0;

    m_pm_zoom = new QMenu(tr("Zoom"));
    act = m_pm_zoom->addAction(tr("Fit to width"));
    act->setData(QVariant(1));
    act = m_pm_zoom->addAction(tr("Fit to page"));
    act->setData(QVariant(2));
    m_pm_zoom->addSeparator();
    act = m_pm_zoom->addAction(tr("50%"));
    act->setData(QVariant(50));
    act = m_pm_zoom->addAction(tr("75%"));
    act->setData(QVariant(75));
    act = m_pm_zoom->addAction(tr("100%"));
    act->setData(QVariant(100));
    act = m_pm_zoom->addAction(tr("125%"));
    act->setData(QVariant(125));
    act = m_pm_zoom->addAction(tr("150%"));
    act->setData(QVariant(150));
    act = m_pm_zoom->addAction(tr("200%"));
    act->setData(QVariant(200));
    connect(m_pm_zoom, SIGNAL(triggered(QAction*)),
            this, SLOT(setZoom(QAction*)));

    m_tb_menu = addToolBar(tr("menu"));
    m_tb_menu->addAction(tr("Zoom"))->setMenu(m_pm_zoom);
    m_tb_menu->setMovable(false);

    m_tb_tool = addToolBar(tr("tool"));
    m_tb_tool->setMovable(false);
    m_tb_tool->addAction(QIcon(tr(":/fileopen")), tr("Open..."),
                         this, SLOT(openFile()));
    m_tb_tool->addSeparator();
    m_to_find = m_tb_tool->addAction(QIcon(tr(":/find")), tr("Find..."),
                                     this, SLOT(toggleFindBar()));
    m_to_find->setCheckable(true);
    m_tb_tool->addSeparator();
    m_to_full = m_tb_tool->addAction(QIcon(tr(":/fullscreen")),
                                     tr("Fullscreen"), this,
                                     SLOT(toggleFullscreen()));
    m_to_full->setCheckable(true);
    m_tb_tool->addSeparator();
    m_tb_tool->addAction(QIcon(tr(":/fastback")), tr("First page"),
                         this, SLOT(firstPage()));
    m_tb_tool->addAction(QIcon(tr(":/back")), tr("Previous page"),
                         this, SLOT(prevPage()));
    m_tb_tool->addAction(QIcon(tr(":/down")), tr("Goto Page..."),
                         this, SLOT(gotoPageDialog()));
    m_tb_tool->addAction(QIcon(tr(":/forward")), tr("Next page"),
                         this, SLOT(nextPage()));
    m_tb_tool->addAction(QIcon(tr(":/fastforward")), tr("Last page"),
                         this, SLOT(lastPage()));

    addToolBarBreak();
    m_tb_find = addToolBar(tr("search"));
    m_tb_find->setMovable(false);
    m_tb_find->hide();

    m_findedit = new QLineEdit();
    m_tb_find->addWidget(m_findedit);
    m_tb_find->addAction(QIcon(tr(":/find")), tr("Find..."),
                         this, SLOT(findText()));
    m_tb_find->addAction(QIcon(tr(":/next")), tr("Next"),
                         this, SLOT(findText()));

}

void MainWindow::setBusy( bool b )
{
	if( b != m_busy ){
		m_busy = b;
		m_outdev->setBusy( m_busy );
		setEnabled( !m_busy );
	}
}

bool MainWindow::busy() const
{
	return m_busy;
}

void MainWindow::renderPage()
{
}

void MainWindow::delayedInit()
{
	
}

void MainWindow::closeFileSelector()
{
	m_tb_menu->show();
	m_tb_tool->show();
	m_tb_find->hide();
	m_to_find->setChecked(false);
	m_stack->setCurrentWidget(m_outdev);
}

void MainWindow::updateCaption()
{
	QString cap = "";
	if ( !m_currentdoc.isEmpty() )
		cap = QString("%1 - ").arg(m_currentdoc);
	cap += "EPdf";
	setWindowTitle( cap );
}

void MainWindow::copyToClipboard(const QRect &r)
{
}

void MainWindow::firstPage ( )
{
}
void MainWindow::prevPage ( )
{
}
void MainWindow::nextPage ( )
{
}
void MainWindow::lastPage ( )
{
}
void MainWindow::gotoPage ( int n )
{
}
void MainWindow::setZoom ( QAction* aid)
{
}
void MainWindow::gotoPageDialog ( )
{
}
void MainWindow::toggleFullscreen ( )
{
    if(m_to_full->isChecked())
    {
        showFullScreen();
    }else{
        showMaximized();
    }
}
void MainWindow::toggleFindBar ( )
{
    if(m_to_find->isChecked())
    {
        m_tb_find->show();
        m_findedit->setFocus();
    }else{
        m_tb_find->hide();
    }
}
void MainWindow::findText ( const QString &str)
{
}
void MainWindow::findText ( )
{
}
void MainWindow::openFile ( )
{
    m_tb_menu->hide();
    m_tb_tool->hide();
    m_tb_find->hide();
    m_stack->setCurrentWidget(m_filesel);
}
void MainWindow::openFile ( const QString &f )
{
	QFileInfo fi(f);
	if(fi.exists())
	{
		
	}
}
//    void MainWindow::openFile ( const DocLnk &f ){}
void MainWindow::setDocument ( const QString & )
{
}
QMenu * MainWindow::createPopupMenu()
{
	return NULL;
}
