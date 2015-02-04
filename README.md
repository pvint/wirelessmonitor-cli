# wirelessmonitor-cli
A simple CLI/Daemon to monitor when a WIFI link is up or down. 

This could be used to play a sound when a link is acquired or lost, to start or stop a download, start a backup, 
or anything else you may want to happen when a link is acquired or lost.

Usage: 
wirelessmonitor [options]
Options:
 -h --help      Show help (this message)
 -D --daemon    Run in background. (no output)
 -i --isup      Test if an interface is up and exit.
 -v --verbose   Show extra information
 -q --quiet     Suppress output --up "command"  Run command when interface comes up (f.e. --up "/usr/bin/play /path/beep.ogg"
 --down "command"       Run command when interface comes up (f.e. --down "/usr/bin/play /path/beep.ogg"
