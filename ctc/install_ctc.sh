#!/bin/sh

# Generated automatically by encore at 2011-07-22 14:24:36.185198"
echo "Installing CTC driver..."

INSMOD_ARGS=`awk -f transfer2insmod.awk CTC /etc/transfer.ref`

if [ x"$INSMOD_ARGS" == x"" ] ; then
    echo "No CTC declared in /etc/transfer.ref, exiting"
    exit 1
fi

INSMOD_CMD="insmod ctc.ko $INSMOD_ARGS"
echo "installing ctc by insmod ctc $INSMOD_ARGS"
sh -c "$INSMOD_CMD"

MAJOR=`cat /proc/devices | awk '$2 == "ctc" {print $1}'`
if [ -z "$MAJOR" ]; then
	echo "driver ctc not installed!"
	exit 1
fi

MINORS=`awk '/^#\+#/ && $6 == "CTC" { printf("%s ", $7) }' /etc/transfer.ref`
echo "creating device nodes for driver ctc, major $MAJOR, minors $MINORS"
for MINOR in $MINORS; do
    rm -f /dev/ctc.$MINOR
    mknod /dev/ctc.$MINOR c $MAJOR $MINOR
done
