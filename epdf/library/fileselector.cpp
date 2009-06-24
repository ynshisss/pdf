#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QListWidgetItem>
#include <QIcon>
#include "fileselector.h"
#include "fileselectorview.h"


FileSelector::FileSelector(QWidget *parent) : QWidget(parent)
{
    QToolButton *buttonFresh = new QToolButton();
    buttonFresh->setAutoRaise(true);
    buttonFresh->setIcon(QIcon(tr(":/update")));
    buttonFresh->setToolTip(tr("Refresh the document"));
    buttonFresh->setFixedSize(18, 20);

    QToolButton *buttonClose = new QToolButton();
    buttonClose->setAutoRaise(true);
    buttonClose->setIcon(QIcon(tr(":/close")));
    buttonClose->setToolTip(tr("Close the File Selector"));
    buttonClose->setFixedSize(18, 20);
    connect(buttonClose, SIGNAL(clicked()), this, SIGNAL(closeMe()));

    QHBoxLayout *hbTool = new QHBoxLayout();
    hbTool->setContentsMargins(4,1,2,1);
    hbTool->setSpacing(5);
    hbTool->addStretch();
    hbTool->addWidget(buttonFresh);
    hbTool->addWidget(buttonClose);

    view = new FileSelectorView();
    view->setSpacing(1);
    view->setAlternatingRowColors(true);
    connect(view, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(fileClicked(QListWidgetItem*)));
    connect(buttonFresh, SIGNAL(clicked()), view, SLOT(refresh()));

    QVBoxLayout *vbl = new QVBoxLayout(this);
    vbl->setContentsMargins(0, 0, 0, 0);
    vbl->setSpacing(0);
    vbl->addLayout(hbTool);
    vbl->addWidget(view);

}

FileSelector::~FileSelector()
{
}

void FileSelector::fileClicked(QListWidgetItem *item)
{
    if( !item || item->data(Qt::UserRole).isNull())
        return;
    emit fileSelected(item->data(Qt::UserRole).toString());
}



