#!/bin/sh

CHANGE=$1;
NEGATIVE="no";
if [ `echo $CHANGE | head -c 1` == "-" ]; then
	NEGATIVE="yes";
fi
echo $NEGATIVE;

if [ `pgrep pulseaudio` ]; then
	if [ $NEGATIVE == "yes" ]; then
		AMOUNT=`echo $CHANGE | tail - -c +2`
		echo $AMOUNT
		pactl set-sink-volume @DEFAULT_SINK@ -$AMOUNT%
	else
		pactl set-sink-volume @DEFAULT_SINK@ +$CHANGE%;
	fi;
else
	if [ $NEGATIVE == "yes" ]; then
		AMOUNT=`echo $CHANGE | tail - -c +2`
		amixer set Master $AMOUNT%-
	else
		amixer set Master $CHANGE%+
	fi;
fi;
