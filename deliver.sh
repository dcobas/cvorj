#!	/bin/sh
#
# delivery script for ctc driver
# automatically generated by encore $(date)s
#

DRIVER=ctc
CPU=L865
KVER=2.6.24.7-rt27

# get arguments
CMD=
while getopts hn o ; do
    case "$o" in
       n)	CMD=echo ;;	# dry-run
       [h?])	echo >&2 "usage: $0 [-n] ACC={lab|oper|oplhc} [CPU=<cpu>] [KVER=<kernel>]"
		exit 1 ;;
    esac
done
shift `expr $OPTIND - 1`

while [ x"$1" != x"" ] ; do
    case $1 in
	ACC=*)  ACC=`echo $1 | sed 's!ACC=!!'` ;;
	CPU=*)  CPU=`echo $1 | sed 's!CPU=!!'` ;;
	KVER=*) KVER=`echo $1 | sed 's!KVER=!!'` ;;
        *)	echo >&2 "usage: $0 [-n] ACC={lab|oper|oplhc} [CPU=<cpu>] [KVER=<kernel>]"
		exit 1 ;;
    esac
    shift
done

if [ x$ACC == x"" -o x$CPU == x"" -o KVER == x"" ] ; then
	echo "please specify ACC, CPU and KVER"
	echo "usage: $0 ACC=<accel> CPU=<cpu> KVER=<kver>"
	echo "    default CPU=L865, default KVER=2.6.24.7-rt27"
	exit 1
fi

echo "# delivering to ACC=$ACC CPU=$CPU KVER=$KVER"

# delivery paths
DRIVER_PATH=/acc/dsc/$ACC/$CPU/$KVER/$DRIVER/
LIB_PATH=/acc/local/$CPU/dg/encore/$DRIVER/

# deliverable items
LIBS="lib$DRIVER.$CPU.a lib${DRIVER}user.$CPU.a lib${DRIVER}user.h lib$DRIVER.h ${DRIVER}_regs.h vmeio.h"
INSTPROGS="install_$DRIVER.sh transfer2insmod.awk"
DRIVER_OBJECT="$DRIVER.ko"
# SOLIBS="$DRIVER.$CPU.so"

${CMD} mkdir -p $DRIVER_PATH $LIB_PATH
${CMD} dsc_install $INSTPROGS $DRIVER_OBJECT $SOLIBS $DRIVER_PATH
${CMD} dsc_install $LIBS $LIB_PATH
for i in $INSTPROGS; do
    ${CMD} chmod 755 $DRIVER_PATH/$i
done

