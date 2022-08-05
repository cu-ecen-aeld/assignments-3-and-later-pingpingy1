#include <stdio.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>

int main(int argc, char **argv)
{
	openlog(NULL, 0, LOG_USER);

	if (argc < 3) {
		syslog(LOG_ERR, "Parameter not specified");
		return 1;
	}

	const char *writefile = argv[1];
	const char *writestr = argv[2];
	FILE *file = fopen(writefile, "w");

	fwrite(writestr, sizeof(char), strlen(writestr), file);
	syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

	if (fclose(file) == -1) {
		syslog(LOG_ERR, "Could not create file\n");
		return 1;
	}
	
	if (errno == 0)
		return 0;

	syslog(LOG_ERR, "%s\n", strerror(errno));
	return 1;
}
