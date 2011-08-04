#!   /usr/bin/env	python
#    coding: utf8

import syslog
import time
import datetime
import sys

def do_acet_logging(ident, msg, interval):
    syslog.openlog(ident, 0, syslog.LOG_LOCAL2)
    while True:
        timestamp = datetime.datetime.now().strftime('%Y.%m.%d@%H:%M:%S')
        syslog.syslog('%s|time=%s' % (msg, timestamp,))
        time.sleep(interval)

if __name__ == '__main__':
    try:
        interval = float(sys.argv[1])
    except:
        interval = 20
    ident   = 'driver.encore.ctc'
    gendata = '%(ident)s gen-by=dcobas|gen-date=11.08.02@09:30:49|encore-version=libencore-7-g19438cc' % locals()
    do_acet_logging(ident, gendata, interval)
        
        
    

