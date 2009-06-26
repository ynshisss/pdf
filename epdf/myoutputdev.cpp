#include "qbusybar.h"
#include "myoutputdev.h"
#include <QRubberBand>
#include <QMouseEvent>

OutputLabel::OutputLabel(QWidget *parent) : QLabel(parent)
{
	rubberBand = NULL;
	setBackgroundRole(QPalette::Base);
	setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	setScaledContents(true);
	resize(0, 0);
	//setAttribute(Qt::WA_OpaquePaintEvent);
}

OutputLabel::~OutputLabel()
{
}

QRubberBand * OutputLabel::getRubberBand()
{
	if(!rubberBand){
		rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
	}
	return rubberBand;

}

void OutputLabel::mousePressEvent(QMouseEvent *e)
{
	origin = e->pos();
	if(!rubberBand) {
		rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
	}
	rubberBand->hide();
	rubberBand->setGeometry(QRect(origin, QSize()));
	rubberBand->show();
}

void OutputLabel::mouseMoveEvent(QMouseEvent *e)
{
	QRect r = QRect(origin, e->pos()).normalized();
	int x = r.x() < 0 ? 0 : r.x();
	int y = r.y() < 0 ? 0 : r.y();
	int w = r.width()+x > size().width() ? size().width()-x : r.width();
	w = r.x() < 0 ? w + r.x() : w;
	int h = r.height()+y > size().height() ? size().height()-y: r.height();
	h = r.y() < 0 ? h + r.y() : h;

	rubberBand->setGeometry(x, y, w, h);
	emit visibleChanged(rubberBand->geometry());
}

void OutputLabel::mouseReleaseEvent(QMouseEvent *e)
{
	if(rubberBand->size().isEmpty())
		return;
	emit selectionChanged(rubberBand->geometry());
}

//*************************************************************
//MyOutputDev
//*************************************************************

MyOutputDev::MyOutputDev(QWidget *parent) : QOutputDev(parent)
{
	m_isbusy = false;

	m_outlabel = new OutputLabel;
	setWidget( m_outlabel );
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	m_counter = new QLabel(this);
	m_counter->setFixedWidth(100);
	m_counter->setAlignment(Qt::AlignCenter);
	addScrollBarWidget(m_counter, Qt::AlignLeft);
 
	m_busybar = new QBusyBar(this);
	m_busybar->setFixedWidth(100);
	m_busybar->hide();
	addScrollBarWidget(m_busybar, Qt::AlignLeft); 

	connect(m_outlabel, SIGNAL(visibleChanged(const QRect &)),
			this, SLOT(setVisible(const QRect &)));
	connect(m_outlabel, SIGNAL(selectionChanged(const QRect &)),
			this, SIGNAL(selectionChanged(const QRect &)));
}

MyOutputDev::~MyOutputDev()
{
}

void MyOutputDev::setVisible(const QRect &rect)
{
	QPoint c = rect.center();
	ensureVisible(c.x(), c.y(), rect.width()/2+5, rect.height()/2+5);
}

void MyOutputDev::startPage(int pn, GfxState *st)
{
	m_outlabel->getRubberBand()->hide();
	QOutputDev::startPage(pn, st);
}

void MyOutputDev::setPageCount(int actp, int maxp)
{
	m_counter->setText(QString("%1 / %2").arg(actp).arg(maxp));
}

void MyOutputDev::setBusy( bool b)
{
	if(b != m_isbusy) {
		if(b) {
			m_busybar->beginBusy();
			m_busybar->show();
			m_counter->hide();
		}else {
			m_counter->show();
			m_busybar->hide();
			m_busybar->endBusy();
		}
		m_isbusy = b;
	}
}

bool MyOutputDev::isBusy() const
{
	return m_isbusy;
}

QRect MyOutputDev::selection() const
{
	return m_outlabel->getRubberBand()->geometry();
}

void MyOutputDev::setSelection(const QRect &r, bool scrollto)
{
	m_outlabel->getRubberBand()->setGeometry(r.normalized());
	m_outlabel->getRubberBand()->show();
	if(scrollto){
		QPoint c = r.center();
		ensureVisible(c.x(), c.y(), r.width()/2+5, r.height()/2+5);
	}
}

void MyOutputDev::keyPressEvent(QKeyEvent *e)
{
}

void MyOutputDev::drawContents()
{
	QPixmap *tmp = this->getMyPixmap();
	if(tmp) {
		m_outlabel->setPixmap(*tmp);
		m_outlabel->adjustSize();
	}
}
