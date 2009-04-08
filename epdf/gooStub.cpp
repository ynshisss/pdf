
extern "C" {

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>

#include "goo/gmem.h"
}
#include "goo/gtypes.h"
#include "goo/gfile.h"
#include "goo/GString.h"

#include <QDir>


// replacement stubs to simplify (and speed up) operations

void *gmalloc ( int size )                   { return malloc ( size ); }
void *grealloc ( void *p, int size )         { return realloc ( p, size ); }
void gfree ( void *p )                       { free ( p ); }
char *copyString ( char *str )               { return strdup ( str ); }
char *getLine(char *buf, int size, FILE *f)  { return fgets ( buf, size, f ); }
GString *getHomeDir ( )                      { return new GString ( QDir::homePath().toLocal8Bit ( )); }
GString *appendToPath ( GString *path, char *fileName )   { return new GString ( QDir ( path-> getCString ( )). absoluteFilePath ( fileName ).toLocal8Bit ( )); }

// mostly taken from XPDF, but simplified...

GBool openTempFile ( GString **name, FILE **f, char *mode, char *ext )
{
	char *s, *p;
	int fd;
	
	if ( !ext ) 
		ext = ".tmp";
	
	if (!( s = tmpnam ( 0 ))) 
		return gFalse;
			
	*name = new GString ( s );

	s = (*name)-> getCString ( );
	if (( p = strrchr ( s, '.' ))) 
		(*name)-> del ( p - s, (*name)-> getLength ( ) - ( p - s ));
	
	(*name)-> append ( "_qpdf" );
	(*name)-> append ( ext );
	
	fd = open ((*name)-> getCString ( ), O_WRONLY | O_CREAT | O_EXCL, 0600 );
	
	if ( fd < 0 || !( *f = fdopen ( fd, mode ))) {
		delete *name;
		return gFalse;
	}
	
	return gTrue;	
}
