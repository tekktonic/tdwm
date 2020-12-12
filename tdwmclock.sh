#!/bin/sh
set -e
while [ true ]; do
	xsetroot -name "| `mullvad status | awk -F ' - ' '{print $1}'` | `mpc status | head -n 1 | cut -d ' ' --complement -f 1 | head -c 100` | `tdwmtemp` | `date +'%a %b %e %H:%M'` | `tdwmbatt` |"
	sleep 60
done
