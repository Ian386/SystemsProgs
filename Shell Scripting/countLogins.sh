#!/bin/bash

#NAME: IAN NDOLO MWAU
#REG NO: SCT211-0034/2022

echo "Enter the user's uid: "
read userid

# Checking if the UID is numerical
if [[ ! $userid =~ ^[0-9]+$ ]]; then
    echo "Invalid UID"
    exit 1
fi

#get username
username=$(getent passwd $userid | cut -d: -f1)

# check if user exists
if [ -z $username ]; then
    echo "User does not exist"
    exit 1
fi

# get list of login sessions for the specified username
logins=$(who | grep "^$username")

if [ -z "$logins" ]; then
    echo "$username is not logged on currently"
else
    # get number of logins
    numLogins=$(echo "$logins" | wc -l)

    # display logins
    echo "$username is logged on $numLogins times"
    echo "$logins"
fi
