#!/usr/bin/python

import os
import socket
import time
import sys

if len(sys.argv) != 4 :
    print "Usage: $" + sys.argv[0] + " <serveripaddr> <portno>  <string_length> "
    sys.exit(1);

port = int(sys.argv[2])
ipaddr = sys.argv[1]

s = socket.socket(socket.AF_INET , socket.SOCK_STREAM)
s.connect((ipaddr , port))

i = int(sys.argv[3]);

#while True :
sendbuffer = 'a' * i
s.send(sendbuffer)
i = i + 1
time.sleep(1)

