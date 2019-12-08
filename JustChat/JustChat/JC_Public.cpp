#include "JC_Public.h"
#include <ctime>

QString generate_id( int digits )
{
	QString hash = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	qint32 len = hash.size();
	qsrand( time( 0 ) );
	QString id;
	for ( qint32 i = 0; i < digits; ++i )
		id += hash[qrand() % len];
	return id;
}
