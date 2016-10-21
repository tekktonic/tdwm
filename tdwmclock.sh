#!/bin/sh
set -e
while [ true ]; do
	xsetroot -name "| `date +'%a %b %e %H:%M'` | `tdwmbatt` |"
	sleep 60
done
