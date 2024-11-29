#!/bin/bash

#NAME: IAN NDOLO MWAU
#REG NO: SCT211-0034/2022

count=0
num_sum=0


# Function to check if the input is a whole number or a decimal number
ValidateNum() {
    if [[ $1 =~ ^-?[0-9]+(\.[0-9]+)?$ ]]; then
        return 0
    fi
    
    echo "'$1' is not a valid number. Please enter a valid number."
        return 1
}

# Loop to take input from the user
while [ $count -lt 6 ]; do
    echo -n "Enter $(($count + 1)) number: "
    read read_num

    # Validate read_num
    if ValidateNum "$read_num"; then
        num_sum=$(echo "$num_sum + $read_num" | bc)
        count=$((count + 1))
    fi
done


echo "The sum of the 6 numbers is: $num_sum"
