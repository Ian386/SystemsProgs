#!/bin/bash

#NAME: IAN NDOLO MWAU
#REG NO: SCT211-0034/2022

# Check if nmap is installed
if ! command -v nmap &> /dev/null; then
    echo "Error: nmap is not installed."
    exit 1
fi

# Prompt for the IP range to scan
echo -n "Enter the IP address range to scan: "
read ipRange

# Run nmap to scan the network for active hosts
echo "Ping scan for hosts'$ipRange'..."
scanResults=$(nmap -sn "$ipRange")

# display hosts that are up
echo "Scan Results:"
echo "$scanResults" | while read -r currLine; do
    if [[ $currLine == *"Host is up"* ]]; then
        # Extract the IP address from the previous line using a regex
        ip=$(echo "$prevLine" | grep -oE '([0-9]{1,3}\.){3}[0-9]{1,3}')
        echo "$ip - Status: Yes"
    fi
    prevLine=$currLine
done
