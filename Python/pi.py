#!/usr/bin/python

__author__ = "Sean O'Bleness"
__date__ = "March 14, 2015"
__version__ = "1.2"


import math
import os
import time
from optparse import OptionParser
import sys

k = 0.0
total = 0.0

def Main(watch, args):

	while 1:
		try:
			upperbound = float(args[0])
			break
		except ValueError:
			print "Not a Number, try again "

	Calculate(k, total, upperbound, watch)

	sys.exit(0)

def Calculate(k, total, upperbound, watch):

	while((k+1)!=upperbound):

		if k%2==0:
			total = total+(1.0/((2.0*k)+1.0))
		else:
			total = total-(1.0/((2.0*k)+1.0))
		k=k+1.0
		if watch:
			p = total * 4.0
			print p
	print total * 4.0
	return 

if __name__=="__main__":
	parser = OptionParser()

	parser.add_option('-w', '--watch', 
		action="store_true", dest="watcht", default=False,
		help="Running total of PI displayed.")

	parser.add_option('-V', '--version',
        	action="store_true", dest="version", default=False,
		help="Display version information and exit.")

	(opts, args) = parser.parse_args()

	if(opts.version):
		print ""
		print "Pi Calculator"
		print __author__
		print __version__
		print __date__
		sys.exit(0)

	if len(args) != 1:
		print "ERROR: specify upper bound \neg: pi -w 10000"
		sys.exit()

	Main(opts.watcht, args)
	



