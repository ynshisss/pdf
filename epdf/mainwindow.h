#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
class QStackedWidget;
class QMenu;
class QToolBar;
class QLineEdit;
class FileSelector;
class OutputDev;

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
    void setZoom ( int z );
    void gotoPageDialog ( );
    void toggleFullscreen ( );
    void toggleFindBar ( );
    void findText ( const QString & );
    void findText ( );
    void openFile ( );
    void openFile ( const QString & );
//    void openFile ( const DocLnk & );
    void setDocument ( const QString & );
private:
    void createToolBar();

    QStackedWidget *m_stack;
    FileSelector *m_filesel;
    OutputDev *m_outdev;
    QToolBar *m_tb_menu, *m_tb_tool, *m_tb_find;
    QLineEdit *m_findedit;
    QPopupMenu *m_pm_zoom;

    bool m_fullscreen;
    bool m_busy;
    bool m_renderok;
    int m_currentpage;
    int m_pages;
    int m_zoom;

};

#endif // MAINWINDOW_H
