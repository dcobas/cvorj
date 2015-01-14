#!   /usr/bin/env	python
#    coding: utf8

import syslog
import time
import datetime
import sys

is_prod = False
if is_prod:
    facility = syslog.LOG_LOCAL2
    environment = 'prod'
else:
    facility = syslog.LOG_LOCAL2        # change to something else when available
    environment = 'dev'

def do_acet_logging(ident, msg, interval):
    syslog.openlog(ident, 0, facility)
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
    gendata = ( 'Environment=dev|MessageType=config|'
    'SenderType=driver|SenderDomain=encore|SenderSubdomain=ctc|'
    'SenderFile=ctc.c||'
    'gen-by=dcobas|gen-date=11.08.02T09:30:49|encore-version=libencore-7-g19438cc|' % locals())
    do_acet_logging(ident, gendata, interval)
        
        
    

