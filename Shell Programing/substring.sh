#!/bin/bash

# Function to find and display substring occurrences
find_substring() {
    local full_string="$1"
    local substring="$2"
    
    len_full=${#full_string}
    len_sub=${#substring}
    
    left_count=0
    right_count=0
    
    echo "Searching for '$substring' in '$full_string'"
    
    for (( i = 0; i <= len_full - len_sub; i++ )); do
        if [[ "${full_string:i:len_sub}" == "$substring" ]]; then
            left_count=$((left_count + 1))
            echo "Found at position $((i + 1)) (Left to Right)"
        fi
    done
    
    reversed_full_string=$(echo "$full_string" | rev)
    
    for (( i = 0; i <= len_full - len_sub; i++ )); do
        if [[ "${reversed_full_string:i:len_sub}" == "$substring" ]]; then
            right_count=$((right_count + 1))
            position=$((len_full - i - len_sub + 1))
            echo "Found at position $position (Right to Left)"
        fi
    done
    
    echo "Total occurrences (Left to Right): $left_count"
    echo "Total occurrences (Right to Left): $right_count"
}

# Read input from user
echo -n "Enter the full string: "
read input_string

echo -n "Enter the substring to search: "
read search_substring

find_substring "$input_string" "$search_substring"
