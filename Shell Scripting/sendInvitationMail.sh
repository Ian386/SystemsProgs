#!/bin/bash

# Department Chairman of Computing has heard about your Unix shell
# scripting Prowess in creating mail merge service, he wants your services to
# invite students to a webinar hosted by JhubAfrica . The department
# wants to send the invitation letter below to a webinar addressed to each
# student personally.
# “Inviting the you as our computing student to our 21st Open
# Webinar on skills optimization by jhubAfrica scheduled for
# Friday, 29th November from 5:00 P.M. The Zoom link for
# joining in on Friday is as given below. We shall also broadcast
# the webinar on our youtube channel. Youtube link:
# https://youtu.be/ONVTA7LKMIs
# The chairman has a text file that contains the names of the persons and the email
# of persons they want to send to. Implement this mail merge in linux bash and
# should work with all popular browsers .



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