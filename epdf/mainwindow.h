#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
class QStackedWidget;
class QMenu;
class QToolBar;
class QLineEdit;
class QAction;
class FileSelector;
class OutputDev;
//class PDFDoc;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

public slots:
    void firstPage ( );
    void prevPage ( );
    void nextPage ( );
    void lastPage ( );
    void gotoPage ( int n );
    void setZoom ( QAction*);
    void gotoPageDialog ( );
    void toggleFullscreen ( );
    void toggleFindBar ( );
    void findText ( const QString & );
    void findText ( );
    void openFile ( );
    void openFile ( const QString & );
//    void openFile ( const DocLnk & );
    void setDocument ( const QString & );
    virtual QMenu * createPopupMenu ();

private:
    void createToolBars();
private slots:
	void closeFileSelector();

private:
    QStackedWidget *m_stack;
    FileSelector *m_filesel;
    OutputDev *m_outdev;
	//PDFDoc *m_doc;

    QToolBar *m_tb_menu, *m_tb_tool, *m_tb_find;
    QLineEdit *m_findedit;
    QMenu *m_pm_zoom;
    QAction *m_to_find, *m_to_full;

    bool m_fullscreen;
    bool m_busy;
    bool m_renderok;
    int m_currentpage;
    int m_pages;
    int m_zoom;

};

#endif // MAINWINDOW_H
