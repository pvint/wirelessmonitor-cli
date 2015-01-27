/* Wireless Connection Monitor
 * |  Copyright (C) 2012 Paul Vint
 * |
 * |  Author:  Paul Vint pjvint@gmail.com
 * |  |
 * |  This program is free software which I release under the GNU General Public
 * |  License. You may redistribute and/or modify this program under the terms
 * |  of that license as published by the Free Software Foundation; either
 * |  version 2 of the License, or (at your option) any later version.
 * |
 * |  This program is distributed in the hope that it will be useful,
 * |  but WITHOUT ANY WARRANTY; without even the implied warranty of
 * |  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * |  GNU General Public License for more details.
 * |
 * |  To get a copy of the GNU General Puplic License,  write to the
 * |  Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>	/* for sleep(int seconds) */
#include <stdio.h>
#include <getopt.h>



/* flags for all the differenct stuff */
#define ACTIVE       (1 << 0) /* this interface is alive now */ 
#define SHOW         (1 << 1) /* show or don't show this interface */
#define SHOW_LINK    (1 << 2) /* show link quality of this interface */
#define SHOW_LEVEL   (1 << 3) /* show level of this interface */ 
#define SHOW_NOISE   (1 << 4) /* show noise on this interface */
#define SHOW_BITRATE (1 << 5) /* show bit rate on this interface */
#define HIDE_NAME    (1 << 6) /* show name of this interface */


