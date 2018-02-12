#!/bin/bash

command="socat -d -d pty,raw,echo=0 pty,raw,echo=0"

FEEDPAUSE=0.2
ports=
portcount=0

echo "Creating virtual Serialport!..."

# start socat and use a new pipe 3
# doesn't work as it should...
exec 3< <( 2>&3 $command)

for i in 1 2; do
    read <&3 line;
    ports[$portcount]=$(echo "$line" | awk '{ print $7 }')
    portcount=$(( $portcount + 1 ))
    echo "ports array:"
    printf '%s\n' "${ports[@]}"
done

# parse socat output to get input fd and output fd


# feed serial port
while true; do
    echo "feed"
    sleep $FEEDPAUSE
done
