#!/bin/bash

# Function to perform bubble sort
bubble_sort() {
    local arr=("$@")       # Convert arguments to array
    local n=${#arr[@]}     # Get length of the array

    for ((i = 0; i < n-1; i++)); do
        for ((j = 0; j < n-i-1; j++)); do
            if ((arr[j] > arr[j+1])); then
                temp=${arr[j]}
                arr[j]=${arr[j+1]}
                arr[j+1]=$temp
            fi
        done

        # Display the array at this pass
        echo "Pass $((i+1)): ${arr[@]}"
    done

    echo "${arr[@]}"
}

# Input array from the user
echo "Enter the numbers (space-separated):"
read -a numbers

echo "Original array: ${numbers[@]}"
sorted_array=$(bubble_sort "${numbers[@]}")
echo "Sorted array:  $sorted_array"

