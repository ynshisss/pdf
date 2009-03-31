#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QWidget>
#include <QListWidgetItem>
class QListWidget;

#include <qhbox.h>
#include <qvbox.h>
#include <qtoolbutton.h>


#include "qpeglobal.h"
#include "filemanager.h"
#include "applnk.h"

class QPopupMenu;
class QPushButton;
class FileSelectorView;

class FileSelectorItem : public QListWidgetItem
{
public:
    FileSelectorItem( QListWidget *parent, const DocLnk& f );
    ~FileSelectorItem();

    DocLnk file() const { return fl; }

private:
    DocLnk fl;
};

class FileSelectorPrivate;
class FileSelector : public QWidget
{
    Q_OBJECT

public:
    FileSelector( const QString &mimefilter, QWidget *parent,
                  const char *name=0, bool newVisible = TRUE,
                  bool closeVisible = TRUE );
    ~FileSelector();
    void setNewVisible( bool b );
    void setCloseVisible( bool b );
    void setTypeComboVisible( bool b = TRUE );
    void setCategorySelectVisible( bool b = TRUE );
    void reread();
    int fileCount();
    DocLnk selectedDocument() const
    {
	const DocLnk* rp = ((FileSelector*)this)->selected();
	if (!rp) {
	    DocLnk r;
	    return r;
	}
	DocLnk r(*rp);
	delete rp;
	return r;
    }

    QValueList<DocLnk> fileList() const
    {
	((FileSelector*)this)->fileCount(); // ensure all loaded when this is extended

	QValueList<DocLnk> list;
	FileSelectorItem *item = (FileSelectorItem *)((QListView*)view)->firstChild();
	while (item) {
	    list.append(item->file());
	    item = (FileSelectorItem *)item->nextSibling();
	}

	return list;
    }

signals:
    void fileSelected( const DocLnk & );
    void newSelected( const DocLnk & );
    void closeMe();

private slots:
    void createNew();
    void fileClicked( int, QListViewItem *, const QPoint &, int );
    // pressed to get 'right down'
    void filePressed( int, QListViewItem *, const QPoint &, int );
    void fileClicked( QListViewItem *);
    void typeSelected( const QString &type );
    void catSelected( int );
    void cardMessage( const QCString &, const QByteArray &);

private:
    void updateView();
    void updateWhatsThis();

private:
    // RESOLVE please -zecke@handhelds.org
    const DocLnk *selected() QPE_DEPRECATED; // use selectedDocument()  luckily no compiler is putting the access into the symbol name
    FileSelectorView *view;
    QString filter;
    QToolButton *buttonNew, *buttonClose;
    FileSelectorPrivate *d;
};

#endif
