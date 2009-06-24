#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QWidget>

class FileSelectorView;

class FileSelector : public QWidget
{
    Q_OBJECT

public:
    FileSelector(QWidget *parent = 0);
    ~FileSelector();
signals:
    void fileSelected( const QString & );
    void closeMe();

private slots:
    void fileClicked(QListWidgetItem *);

private:
    FileSelectorView *view;
};
#endif // FILESELECTOR_H
