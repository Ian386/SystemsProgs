#!/bin/bash

#NAME: IAN NDOLO MWAU
#REG NO: SCT211-0034/2022



inputFile="students.txt"
logFile="mailMerge.txt"

# Check if the input file exists
if [ ! -f $inputFile ]; then
    echo "$inputFile does not exist"
    exit 1
fi

#clear the log file
echo "Mail Merge Log - $(date)" > "$logFile"


# Define the email subject and body template
subject="Invitation to Webinar on Skills Optimization by JhubAfrica"
emailBody="Inviting you as our computing student to our 21st Open Webinar on skills optimization by JhubAfrica scheduled for Friday, 29th November from 5:00 P.M. The Zoom link for joining in on Friday is as given below. We shall also broadcast the webinar on our YouTube channel. YouTube link: https://youtu.be/ONVTA7LKMIs"


# Read the input file line by line
while IFS=',' read -r name email; do
    # Skip empty lines or improperly formatted lines
    if [[ -z "$name" || -z "$email" ]]; then
        echo "Skipped an improperly formatted or empty line." >> "$logFile"
        continue
    fi

    # Personalize the email body
    personalized_body="Dear $name,\n\n$emailBody\n\nBest Regards,\nDepartment of Computing"

    # Send the email
    echo -e "$personalized_body" | mail -s "$subject" "$email"

    # Log the status
    if [ $? -eq 0 ]; then
        echo "Successfully sent email to: $name <$email>" >> "$logFile"
    else
        echo "Failed to send email to: $name <$email>" >> "$logFile"
    fi
done < "$inputFile"

echo "Mail merge completed. Check the log file '$logFile' for details."