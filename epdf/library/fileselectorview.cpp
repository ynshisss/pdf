#include <QSettings>
#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QListWidgetItem>
#include <QtDebug>
#include "fileselectorview.h"

static const QString INIT = "epdf.ini";
static const QString PDF_KEY = "pdfdir";

FileSelectorView::FileSelectorView(QWidget *parent)
    : QListWidget(parent)
{

    QSettings setting(INIT, QSettings::IniFormat);
    QString str = setting.value(PDF_KEY).toString();
    dir = new QDir(str);
    if(dir->exists()){
        dir->setFilter(QDir::Files | QDir::NoSymLinks);
        dir->setSorting(QDir::Name);
        dir->setNameFilters(QStringList("*.pdf"));
        displayItem();
    }else{
        addItem(tr("Cannot find pdf!"));
    }
}

FileSelectorView::~FileSelectorView()
{
	delete dir;
	dir = NULL;
}

QListWidgetItem * FileSelectorView::createItem(const QFileInfo *info)
{
    QString fileName = info->fileName();
    QListWidgetItem *item = new QListWidgetItem(fileName);
    item->setData(Qt::UserRole, info->absoluteFilePath());
    return item;
}

void FileSelectorView::displayItem()
{
    QFileInfoList fList = dir->entryInfoList();

    int size = fList.size();
    for(int i = 0; i < size; i++)
    {
        const QFileInfo *info = &(fList.at(i));
        addItem(createItem(info));
    }

}

void FileSelectorView::refresh()
{
    dir->refresh();
    clear();
    displayItem();
}
