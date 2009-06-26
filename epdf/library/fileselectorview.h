#ifndef FILESELECTORVIEW_H
#define FILESELECTORVIEW_H
#include <QListWidget>
class QDir;
class QListWidgetItem;
class QFileInfo;

class FileSelectorView : public QListWidget
{
    Q_OBJECT
public:
    FileSelectorView(QWidget *parent = 0);
    ~FileSelectorView();

public slots:
    void refresh();

private:
    void displayItem();
    QListWidgetItem * createItem(const QFileInfo *info);

private:
    QDir *dir;
};

#endif // FILESELECTORVIEW_H
