#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#include "logging.h"

U0 LOG_check()
{
	FILE *f;
	
	if((f = fopen("LOGFILES.log", "r")) != NULL){
		fclose(f);
	}else{
		f = fopen("LOGFILES.log", "w");
		fprintf(f, "#########################\n");
		fprintf(f, "LOGFILES SYNTHESIS ENGINE\n");
		fprintf(f, "Author: Júlio Dias\n");
		fprintf(f, "#########################\n");
		fclose(f);
	}

	return;
}

S8 *LOG_date()
{
	time_t t = time(NULL);
	struct tm time = {0};
	S8 *date;
	
	time = *localtime(&t);
	
	strftime(date, 22, "[%Y-%m-%d %H:%M:%S]", &time);
	
	return date;

}

U0 LOG_init()
{
	S8 *date;
	LOG_check();
	date = LOG_date();
	FILE *f;
	f = fopen("LOGFILES.log", "a");

	fprintf(f, "\n\n----------NEW RUN----------\n");
	fprintf(f, "---%s---\n", date);
	fclose(f);
	return;
}

U0 LOG_error(S8 *output, ...)
{
	va_list ap;
	FILE *f;
	
	f = fopen("LOGFILES.log", "a");

	printf("[ERROR] ");
	
	fprintf(f, "\n[ERROR] ");

	va_start(ap, output);
	vfprintf(stdout, output, ap);
	vfprintf(f, output, ap);
	va_end(ap);

	printf("\n");
	
	fclose(f);
	exit(1);
}

U0 LOG_info(S8 *output, ...)
{
	va_list ap;
	FILE *f;
	
	f = fopen("LOGFILES.log", "a");

	printf("[INFO] ");

	fprintf(f, "\n[INFO] ");

	va_start(ap, output);
	vfprintf(stdout, output, ap);
	vfprintf(f, output, ap);
	va_end(ap);

	printf("\n");
	
	fclose(f);
	return;
}
