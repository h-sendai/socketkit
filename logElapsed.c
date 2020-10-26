#include "logElapsed.h"

/*************************************************************************
	System : KEK MLF Module Tester.
	Author : wada@bbtech.co.jp
	Description : BBT MLF Utilites for Linux
	$KMM_TESTER_BEGIN_LICENSE$
	$KMM_TESTER_END_LICENSE$
*************************************************************************/

/****************************************************************
 *fprintf with time - for logging function
 *****************************************************************/
int fprintf_elapsed(struct timeval start, FILE *pFILE,const char *fmt,...)
{
    struct timeval tv, elapsed;
	int nRET = -1;
	if( pFILE != NULL)
	{
		nRET = -2;
		char buff[2048];
	    va_list ap;
		va_start(ap, fmt);
		int n = vsnprintf(buff ,sizeof(buff)-2, fmt, ap);
		va_end(ap);
		if( n > 0 ){
            gettimeofday(&tv, NULL);
            timersub(&tv, &start, &elapsed);
			nRET = 0;
            nRET += fprintf(pFILE, "%ld.%06ld ", elapsed.tv_sec, elapsed.tv_usec);
			nRET += fprintf(pFILE,buff);
		}
	}
	return nRET;
}
