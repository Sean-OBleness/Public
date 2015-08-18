#!/usr/bin/python
'''
@author: Sean O'Bleness
'''

import os
import pwd
import grp
import sys
import getpass
import time
from stat import *
import multiprocessing 

def Driver():
    print ('\033[1m' + 'Seek Script\n ---version 1.0   July, 2015---\n' + '\033[0m')
         
    exetype = GetTypes()
    searchString = raw_input('\033[1m' + '\nEnter Search String: ' + '\033[0m')

    Walkabout(GetData(), exetype, searchString)

def GetData():
    top = raw_input('\033[1m' + '\nENTER TOP LEVEL DIRECTORY: ' + '\033[0m')
    return top

def GetTypes():
    include = raw_input('\033[1m' + '\nENTER TYPES TO SEARCH FOR IN COMMA SEP. LIST: ' + '\033[0m')
    return include.split(',')

def doSearch(filename, searchString):
    os.system("SearchLine \"%s\" \"%s\"" %(searchString, filename))

def Walkabout(top, exetype, searchString):   
    for f in os.listdir(top):
        try:
            pathname = os.path.join(top, f)
            mode = os.stat(pathname).st_mode
            
            if (S_ISDIR(mode) and not(os.path.islink(pathname))):
                Walkabout(pathname, exetype, searchString)
                    
            elif (S_ISREG(mode) and not(os.path.islink(pathname))):
                temp = f.split('.')
                type = temp[len(temp)-1]
                for g in exetype:
                    if (type == g):
			filename = os.path.join(top, f)
			doSearch(filename, searchString)
			#mp.Process(target = doSearch, args=(filename, searchString))
                        
              
                
        except OSError: 
            e = sys.exc_info()[0]
            #print top + ": Error: %s" % e
            return
           
Driver()
    
