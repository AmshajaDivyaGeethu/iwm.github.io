import serial
import string
import logging
import atexit
import urllib2
import sys
import simplejson
from pprint import pprint
import traceback

def closeAll(serialConnection,logger,hdlr):
    """ to safely close serial ports on exit """
    serialConnection.close()
    logger.info('Serial port closed')
    logger.removeHandler(hdlr)

def find_between( strr, first, last ):
    """ to find the substring between two string s"""
    try:
        start = strr.index( first ) + len( first )
        end = strr.index( last, start )
        return strr[start:end]
    except ValueError:
        return ""   

serialConnection=serial.Serial("/dev/ttyAMA0",9600) #specify the port and the baud rate for the serial connection
#serialConnection.open() #open the serial connection
# print "Opened Serial Connection to serialConnection"
logger = logging.getLogger('RPi2serialConnection') # for logging purposes 
hdlr = logging.FileHandler('/home/pi/Desktop/RPi2serialConnection.log')
formatter = logging.Formatter('%(asctime)s %(levelname)s %(message)s')
hdlr.setFormatter(formatter)
logger.addHandler(hdlr) 
logger.setLevel(logging.INFO)

atexit.register(closeAll, serialConnection, logger, hdlr)
   
while True:
    try:
        print "reading serial"
        reading = serialConnection.readline(); 
        # readings from controller *B1M2H3T4F5# where B is Bin, F is Fill level % , H is Humidity, T is Temperature and M is Methane level
        print reading
        bin_number = find_between(reading,'B','M')
        methane_level = find_between(reading,'M','H')
        humidity = find_between(reading,'H','T')
        temp = find_between(reading,'T','F')
        fill_level = find_between(reading,'F','#')
        get_url = 'http://tachlog.com/tliot/update_bin.php?bin_number='+bin_number+'&methane_level='+methane_number+'&methane_level='+methane_level+'&humidity='+humidity+'&temp='+temp+'&fill_level='+fill_level
        print get_url
        response = urllib2.urlopen(get_url)
        print 'save response : '+ response.read()       
        


    except Exception,e:
        traceback.print_exc()
        pass
serialConnection.close()