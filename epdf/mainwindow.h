#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
class QStackedWidget;
class QMenu;
class QToolBar;
class QLineEdit;
class QAction;
class FileSelector;
class MyOutputDev;
class PDFDoc;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    virtual QMenu * createPopupMenu ();

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

protected:
    void createToolBars();
	//void setFullscreen( bool b = true);
	void setBusy( bool b = true );
	bool busy() const;
	void renderPage();

private slots:
	void delayedInit();
	void closeFileSelector();
	void updateCaption();
	void copyToClipboard(const QRect &);

private:
    QStackedWidget *m_stack;
    FileSelector *m_filesel;
    MyOutputDev *m_outdev;
	PDFDoc *m_doc;

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

	QString m_currentdoc;
};

#endif // MAINWINDOW_H
