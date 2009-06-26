#ifndef __FIXED_H__
#define __FIXED_H__

#include <stdlib.h>
#include <iostream>

#define _GCC_TEMPLATE_BUG_ 1

template <unsigned int SH> class fixt {
public:
	inline fixt ( int i = 0 )      : m_f ( i2f( i ) ) { }
	inline fixt ( double d )       : m_f ( d2f( d )) { }
	inline fixt ( const fixt &f ) : m_f ( f. m_f ) { }
	
	inline operator bool ( ) const   { return m_f != 0; }	
	inline operator double ( ) const { return f2d( m_f ); }
	inline operator float ( ) const  { return (float) f2d( m_f ); }
	inline operator int ( ) const    { return (int) f2i( m_f ); }

	inline fixt &operator = ( const fixt &f ) { m_f = f. m_f; return *this; }
	inline fixt &operator = ( double d )       { m_f = d2f( d ); return *this; }
	inline fixt &operator = ( float f )        { m_f = d2f( f ); return *this; }
	inline fixt &operator = ( int i )          { m_f = i2f( i ); return *this; }

	inline fixt &operator += ( const fixt &f ) { m_f += f. m_f; return *this; }
	inline fixt &operator -= ( const fixt &f ) { m_f -= f. m_f; return *this; }
	inline fixt &operator *= ( const fixt &f ) { m_f = mul ( m_f, f. m_f ); return *this; }
	inline fixt &operator /= ( const fixt &f ) { m_f = div ( m_f, f. m_f ); return *this; }

	inline fixt &operator += ( int i ) { m_f += i2f( i ); return *this; }
	inline fixt &operator -= ( int i ) { m_f -= i2f( i ); return *this; }
	inline fixt &operator *= ( int i ) { m_f *= i; return *this; }
	inline fixt &operator /= ( int i ) { m_f /= i; return *this; }

	inline fixt &operator += ( double d ) { m_f += d2f( d ); return *this; }
	inline fixt &operator -= ( double d ) { m_f -= d2f( d ); return *this; }
	inline fixt &operator *= ( double d ) { m_f = mul ( m_f, d2f( d )); return *this; }
	inline fixt &operator /= ( double d ) { m_f = div ( m_f, d2f( d )); return *this; }

	inline fixt operator - ( ) const { return fixt ( -m_f, true ); }

	inline fixt operator + ( const fixt &f ) const { return fixt ( m_f + f. m_f, true ); }
	inline fixt operator - ( const fixt &f ) const { return fixt ( m_f - f. m_f, true ); }
	inline fixt operator * ( const fixt &f ) const { return fixt ( mul ( m_f, f. m_f ), true ); }
	inline fixt operator / ( const fixt &f ) const { return fixt ( div ( m_f, f. m_f ), true ); }

	inline fixt operator + ( double d ) const { return fixt ( m_f + d2f( d ), true ); }
	inline fixt operator - ( double d ) const { return fixt ( m_f - d2f( d ), true ); }
	inline fixt operator * ( double d ) const { return fixt ( mul ( m_f, d2f( d )), true ); }
	inline fixt operator / ( double d ) const { return fixt ( div ( m_f, d2f( d )), true ); }

	inline fixt operator + ( int i ) const { return fixt ( m_f + i2f( i ), true ); }
	inline fixt operator - ( int i ) const { return fixt ( m_f - i2f( i ), true ); }
	inline fixt operator * ( int i ) const { return fixt ( m_f * i, true ); }
	inline fixt operator / ( int i ) const { return fixt ( m_f / i, true ); }

	inline bool operator <  ( const fixt &f ) const { return m_f < f. m_f; }
	inline bool operator >  ( const fixt &f ) const { return m_f > f. m_f; }
	inline bool operator <= ( const fixt &f ) const { return m_f <= f. m_f; }
	inline bool operator >= ( const fixt &f ) const { return m_f >= f. m_f; }
	inline bool operator == ( const fixt &f ) const { return m_f == f. m_f; }
	inline bool operator != ( const fixt &f ) const { return m_f != f. m_f; }

	inline bool operator <  ( double d ) const { return m_f < d2f( d ); }
	inline bool operator >  ( double d ) const { return m_f > d2f( d ); }
	inline bool operator <= ( double d ) const { return m_f <= d2f( d ); }
	inline bool operator >= ( double d ) const { return m_f >= d2f( d ); }
	inline bool operator == ( double d ) const { return m_f == d2f( d ); }
	inline bool operator != ( double d ) const { return m_f != d2f( d ); }

	inline bool operator <  ( int i ) const { return m_f < i2f( i ); }
	inline bool operator >  ( int i ) const { return m_f > i2f( i ); }
	inline bool operator <= ( int i ) const { return m_f <= i2f( i ); }
	inline bool operator >= ( int i ) const { return m_f >= i2f( i ); }
	inline bool operator == ( int i ) const { return m_f == i2f( i ); }
	inline bool operator != ( int i ) const { return m_f != i2f( i ); }

#if _GCC_TEMPLATE_BUG_
public: 
#else
private:
#endif
	typedef int fix_t;

	inline static double f2d ( fix_t f )   { return ((double) f ) / ((double) ( 1 << SH )); }
	inline static fix_t  d2f ( double d )  { return (fix_t) ( d * ((double) ( 1 << SH ))); }
	
	inline static int    f2i ( fix_t f )   { return (int) ( f >> SH ); }
	inline static fix_t  i2f ( int i )     { return (fix_t) ( i << SH ); }	
	
	inline static fix_t mul ( fix_t m1, fix_t m2 )	{ return (fix_t) ((((long long int) m1 ) * m2 ) >> SH ); }	
	inline static fix_t div ( fix_t d1, fix_t d2 )	{ return (fix_t) ((((long long int) d1 ) << SH ) / d2 ); }
	
	fixt ( fix_t f, bool /*dummy*/ ) : m_f ( f ) { }

	//data
	fix_t m_f;

// friends:		
#if !_GCC_TEMPLATE_BUG_
	friend fixt operator + <> ( int i, const fixt &f );
	friend fixt operator - <> ( int i, const fixt &f );
	friend fixt operator * <> ( int i, const fixt &f );
	friend fixt operator / <> ( int i, const fixt &f );

	friend fixt operator + <> ( double d, const fixt &f );
	friend fixt operator - <> ( double d, const fixt &f );
	friend fixt operator * <> ( double d, const fixt &f );
	friend fixt &operator / <> ( double d, const fixt<SH> &f );

	friend bool operator <  <> ( double d, const fixt &f );
	friend bool operator >  <> ( double d, const fixt &f );
	friend bool operator <= <> ( double d, const fixt &f );
	friend bool operator >= <> ( double d, const fixt &f );
	friend bool operator == <> ( double d, const fixt &f );
	friend bool operator != <> ( double d, const fixt &f );

	friend bool operator <  <> ( int i, const fixt &f );
	friend bool operator >  <> ( int i, const fixt &f );
	friend bool operator <= <> ( int i, const fixt &f );
	friend bool operator >= <> ( int i, const fixt &f );
	friend bool operator == <> ( int i, const fixt &f );
	friend bool operator != <> ( int i, const fixt &f );
	
	friend long int lrint ( const fixt &f );
	friend fixt sqrt ( const fixt &f );
	friend fixt fabs ( const fixt &f );
#endif
};


template <unsigned int SH> inline fixt<SH> operator + ( int i, const fixt<SH> &f )  { return fixt<SH> ( fixt<SH>::i2f( i ) + f. m_f, true ); }
template <unsigned int SH> inline fixt<SH> operator - ( int i, const fixt<SH> &f )  { return fixt<SH> ( fixt<SH>::i2f( i ) - f. m_f, true ); }
template <unsigned int SH> inline fixt<SH> operator * ( int i, const fixt<SH> &f )  { return fixt<SH> ( i * f. m_f, true ); }
template <unsigned int SH> inline fixt<SH> operator / ( int i, const fixt<SH> &f )  { return fixt<SH> ( fixt<SH>::div ( fixt<SH>::i2f( i ), f. m_f ), true ); } 
//template <unsigned int SH> inline fixt<SH> operator / ( int i, const fixt<SH> &f )  { return fixt<SH> ( fixt<SH>::i2f ( i / fixt<SH>::f2i ( f. m_f )), true ); } 

template <unsigned int SH> inline fixt<SH> operator + ( double d, const fixt<SH> &f ) { return fixt<SH> ( fixt<SH>::d2f( d ) + f. m_f, true ); }
template <unsigned int SH> inline fixt<SH> operator - ( double d, const fixt<SH> &f ) { return fixt<SH> ( fixt<SH>::d2f( d ) - f. m_f, true ); }
template <unsigned int SH> inline fixt<SH> operator * ( double d, const fixt<SH> &f ) { return fixt<SH> ( fixt<SH>::mul ( fixt<SH>::d2f( d ), f. m_f ), true ); }
template <unsigned int SH> inline fixt<SH> operator / ( double d, const fixt<SH> &f ) { return fixt<SH> ( fixt<SH>::mul ( fixt<SH>::d2f( d ), f. m_f ), true ); }

template <unsigned int SH> inline bool operator <  ( double d, const fixt<SH> &f ) { return fixt<SH>::d2f( d ) < f. m_f; }
template <unsigned int SH> inline bool operator >  ( double d, const fixt<SH> &f ) { return fixt<SH>::d2f( d ) > f. m_f; }
template <unsigned int SH> inline bool operator <= ( double d, const fixt<SH> &f ) { return fixt<SH>::d2f( d ) <= f. m_f; }
template <unsigned int SH> inline bool operator >= ( double d, const fixt<SH> &f ) { return fixt<SH>::d2f( d ) >= f. m_f; }
template <unsigned int SH> inline bool operator == ( double d, const fixt<SH> &f ) { return fixt<SH>::d2f( d ) == f. m_f; }
template <unsigned int SH> inline bool operator != ( double d, const fixt<SH> &f ) { return fixt<SH>::d2f( d ) != f. m_f; }

template <unsigned int SH> inline bool operator <  ( int i, const fixt<SH> &f ) { return fixt<SH>::i2f( i ) < f. m_f; }
template <unsigned int SH> inline bool operator >  ( int i, const fixt<SH> &f ) { return fixt<SH>::i2f( i ) > f. m_f; }
template <unsigned int SH> inline bool operator <= ( int i, const fixt<SH> &f ) { return fixt<SH>::i2f( i ) <= f. m_f; }
template <unsigned int SH> inline bool operator >= ( int i, const fixt<SH> &f ) { return fixt<SH>::i2f( i ) >= f. m_f; }
template <unsigned int SH> inline bool operator == ( int i, const fixt<SH> &f ) { return fixt<SH>::i2f( i ) == f. m_f; }
template <unsigned int SH> inline bool operator != ( int i, const fixt<SH> &f ) { return fixt<SH>::i2f( i ) != f. m_f; }

template <unsigned int SH> inline long int lrint ( const fixt<SH> &f )
{
	return fixt<SH>::f2i (( f. m_f < 0 ) ? f. m_f - ( 1 << ( SH - 1 )) : f. m_f + ( 1 << ( SH - 1 )));
}

template <unsigned int SH> inline fixt<SH> fabs ( const fixt<SH> &f )
{
	return ( f. m_f < 0 ) ? fixt<SH> ( -f. m_f, true ) : f;
}

// roughly from QPE / qmath.h 
template <unsigned int SH> inline fixt<SH> sqrt ( const fixt<SH> &f )
{
	if ( f. m_f <= 0 )
		return fixt<SH> ( 0, true );
		
	typename fixt<SH>::fix_t a0 = 0;
	typename fixt<SH>::fix_t a1 = f. m_f; // take value as first approximation
	
	do {
		a0 = a1;
		a1 = ( a0 + fixt<SH>::div ( f. m_f, a0 )) >> 1;
	} while ( abs ( fixt<SH>::div ( a1 - a0,  a1 )) > 1 );
	
	return fixt<SH> ( a1, true );
}

#if 0 // no std::ostream needed in OPIE
template <unsigned int SH> inline std::ostream &operator << ( std::ostream &o, const fixt<SH> &f )
{
	o << double( f );
	return o;
}
#endif

#endif
