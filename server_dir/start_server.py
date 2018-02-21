#!/usr/bin/python

import os
import sys


if len(sys.argv) != 3 :
    print "Usage: " + sys.argv[0] + " <ip_address> <starting_portno>"
    sys.exit(1);

ip_address = sys.argv[1]
portno = int(sys.argv[2])

while True :
    command = "./server " + ip_address + " " + str(portno)
    os.system(command)
    portno = portno + 1


