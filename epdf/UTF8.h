#include <QByteArray>
#include <QString>
#include <QChar>
#include <string.h>

static int mapUTF8 ( Unicode u, char *buf, int bufSize ) 
{
	QByteArray utf = QString ( QChar ( u )). toUtf8 ( );
	int len = utf. length ( );
	
	if ( len <= bufSize ) {
		::memcpy ( buf, utf. data ( ), len );
		return len;
	}
	else
		return 0;
}

static int mapUCS2 ( Unicode u, char *buf, int bufSize) 
{
	if (u <= 0xffff) {
		if (bufSize < 2)
			return 0;

		buf[0] = (char)((u >> 8) & 0xff);
		buf[1] = (char)(u & 0xff);
		return 2;
	} 
	else 
		return 0;
}
