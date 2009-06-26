#ifndef MYOUTPUTDEV_H
#define MYOUTPUTDEV_H

#include "qoutputdev.h"

#include <QWidget>
#include <QRect>
#include <QPoint>
#include <QLabel>
class GfxState;
class QRubberBand;
class QBusyBar;

//------------------------------------------------------------------------
//OutputLabel
//------------------------------------------------------------------------
class OutputLabel : public QLabel
{
    Q_OBJECT
public:
	OutputLabel(QWidget *parent = 0);
	virtual ~OutputLabel();
	QRubberBand * getRubberBand();
signals:
	void selectionChanged(const QRect &sel);
	void visibleChanged(const QRect &rect);

protected:
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);
private:
	QRubberBand *rubberBand;
	QPoint origin;
};


class MyOutputDev : public QOutputDev
{
    Q_OBJECT
public:
    MyOutputDev(QWidget *parent = 0);
    virtual ~MyOutputDev();
	void setPageCount(int actp, int maxp);
	virtual void setBusy(bool b = true);
	virtual bool isBusy() const;
	QRect selection() const;
	void setSelection(const QRect &r, bool scrollto = false);
	virtual void startPage(int pn, GfxState *gs);

signals:
	void selectionChanged(const QRect &sel);

protected:
	virtual void keyPressEvent(QKeyEvent *e);
	virtual void drawContents();	
private slots:
	void setVisible(const QRect &rect);
private:
	OutputLabel *m_outlabel;
	QLabel *m_counter;
	QBusyBar *m_busybar;
	bool m_isbusy;
};

#endif // OUTPUTDEV_H
