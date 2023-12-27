#!/bin/bash

# Function to check if a string is palindrome
is_palindrome() {
    local input="$1"
    local reversed=""
    local length=${#input}

    for (( i=$length-1; i>=0; i-- )); do
        reversed="$reversed${input:i:1}"
    done
    
    if [ "$input" == "$reversed" ]; then
        echo "Palindrome"
    else
        echo "Not a palindrome"
    fi
}

# Read input from user
echo -n "Enter a string: "
read input_string

# Remove spaces and convert to lowercase (optional)
input_string="${input_string// /}"
input_string="${input_string,,}"

is_palindrome "$input_string"