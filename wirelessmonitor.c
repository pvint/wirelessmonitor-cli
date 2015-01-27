/* Wireless Connection Monitor
|  Copyright (C) 2012 Paul Vint
|
|  Author:  Paul Vint pjvint@gmail.com
|  |
|  This program is free software which I release under the GNU General Public
|  License. You may redistribute and/or modify this program under the terms
|  of that license as published by the Free Software Foundation; either
|  version 2 of the License, or (at your option) any later version.
|
|  This program is distributed in the hope that it will be useful,
|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|  GNU General Public License for more details.
|
|  To get a copy of the GNU General Puplic License,  write to the
|  Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "wirelessmonitor.h"
#include <stdio.h>
#include <getopt.h>
#include <time.h>

#define WIRELESS "/proc/net/wireless"
#define MAJOR_VERSION "0"
#define MINOR_VERSION "7"
#define PROGRAM_NAME "Wireless Monitor"


int linkStatus = 0;
int verbosity = 1;	// 0 is quiet, 1 is normal, 2 is verbose
char *upCommand = "/usr/bin/play -q /usr/share/sounds/KDE-Im-Contact-In.ogg";
char *downCommand = "/usr/bin/play -q /usr/share/sounds/KDE-Im-Contact-Out.ogg";

/*
 * cat /proc/net/wireless 
Inter-| sta-|   Quality        |   Discarded packets               | Missed | WE
 face | tus | link level noise |  nwid  crypt   frag  retry   misc | beacon | 22
 wlan2: 0000    0     0     0        0      0      0      0      0        0
*/

float getProcInfo(void) 
{
	FILE *procfile;
	char procread[256];
	char *n;

	char interface, status;
	float link, level, noise, nwid, crypt, frag, retry, misc, missedBeacon, we;
	
	if ((procfile = fopen(WIRELESS, "r")) == NULL)
	{
		return 0;
	}
	/* 2 lines header */
  	n = fgets(procread,sizeof(procread),procfile);
  	n = fgets(procread,sizeof(procread),procfile);

	
	while(fgets(procread,sizeof(procread),procfile) != NULL)
	{
		
		sscanf(procread," %s: %s %f. %f. %f %f %f %f %f %f %f %f", 
		       &interface, &status, &link, &level, &noise, &nwid, &crypt, &frag, &retry, &misc, &missedBeacon, &we);
		/* TODO: Make more info available */
		/*c = strstr(procread,"\n");
		*c = 'x';
*/
		/*printf("X%cX", procread[strlen(procread) - 1]); */
		/*procread[strlen(procread) - 2] = 'Z';*/
		/*printf("%s", procread);*/
		/* Terminate the interface name string */
		/* TODO: Something... anything... */
		/* Okay, how's this? */
		if(procread[15] != ' ')
		{
			/*printf("Not Space %c ", procread[15]);*/
			return 1;
		}
		
	}
	return (-1);
}
void displayHelp(char *progName)
{
	
	printf("Usage: %s [options]\nOptions:\n", progName);
	printf(" -h --help\tShow help (this message)\n");
	printf(" -D --daemon\tRun in background. (no output)\n");
	printf(" -i --isup\tTest if an interface is up and exit.\n");
	printf(" -v --verbose\tShow extra information\n");
	printf(" -q --quiet\tSuppress output");
	printf(" --up \"command\" \tRun command when interface comes up (f.e. --up \"/usr/bin/play /path/beep.ogg\"\n");
	printf(" --down \"command\"\tRun command when interface comes up (f.e. --down \"/usr/bin/play /path/beep.ogg\"\n");
	exit(0);
}

void printText(char *text)
{
	time_t timer;
	char tbuf[28];
	struct tm* tm_info;

	time(&timer);
	tm_info = localtime(&timer);

	strftime(tbuf, 26, "[%Y/%m/%d %H:%M:%S]", tm_info);


	// Print text to terminal, adjusting for verbosity
	switch (verbosity)
	{
		case 0:
			return; // no output
		default: 
			printf("%s - %s\n", tbuf, text);
	}
	return;
}
int main(int argc, char **argv)
{
	float info = 0;
	int opt, n;
	int testOnly = 0;
	
	static struct option long_options[] = 
	{
		{ "isup", 0, 0, 'i' },
		{ "help", 0, 0, 'h' },
		{ "daemon", 0, 0, 'D' },
		{ "verbose", 0, 0, 'v' },
		{ "quiet", 0, 0, 'q' },
		{ "up", required_argument, 0, '1' },
		{ "down", required_argument, 0, '2' },
		{ 0, 0, 0, 0 }
	};

	while ((opt = getopt_long(argc, argv, "ihDvq12", long_options, NULL)) != EOF) {
		switch (opt)
		{
			/* --up /path/to/command */
			case '1':
				if(optarg == NULL)
				{
					printf("The option -%c requires an argument\n", opt);
					exit(1);
				}
				upCommand = optarg;
				break;
			/* --down /path/to/command */
			case '2':
				if(optarg == NULL)
				{
					printf("The option -%c requires an argument\n", opt);
					exit(1);
				}
				downCommand = optarg;
				break;
			case 'i':
				testOnly = 1;
				break;
			case 'D':
				printText("Forking to background...");
				n = daemon(1,0);
				break;
			case 'v':
				verbosity = 2;
				break;
			case 'q':
				verbosity = 0;
				break;
			case 'h':
				displayHelp(argv[0]);
				exit(0);
			default:
				displayHelp(argv[0]);
		}
	}
        if (verbosity > 0)
        {
                printf("%s v%s.%s\n", PROGRAM_NAME, MAJOR_VERSION, MINOR_VERSION);
        }

	/* Polling loop */
	while(1)
	{
		info = getProcInfo();
		/*printf("%.0f\n", info);*/
		
		if (testOnly == 1)
		{
			if (info == -1)
			{
				printText("Connection is DOWN\n");
				exit(1);
			}
			else
			{
				printText("Connection is UP\n");
				exit(0);
			}
		}
		
		if (info == 1 && linkStatus == 0)
		{
			printText("WIFI is UP");
			n = system(upCommand);
			linkStatus = 1;
		}
		if (info == -1)
		{
			if (linkStatus == 1)
			{
				printText("WIFI is DOWN");
				n = system(downCommand);
			}
			linkStatus = 0;
		}
		
		sleep(5);
	}
	/* Should never get here! */
	exit(666);
}
