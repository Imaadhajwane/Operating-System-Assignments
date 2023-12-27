#!/bin/bash



# Function to perform insertion sort

insertion_sort() {

    local arr=("$@")       # Convert arguments to array

    local n=${#arr[@]}     # Get length of the array



    for ((i = 1; i < n; i++)); do

        key=${arr[i]}

        j=$((i - 1))



        # Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position

        while ((j >= 0 && arr[j] > key)); do

            arr[j+1]=${arr[j]}

            j=$((j - 1))

        done

        arr[j+1]=$key

    done



    echo "${arr[@]}"

}



# Prompt user for the number of elements

read -p "Enter the number of elements: " num_elements



# Input array

numbers=()

for ((i = 1; i <= num_elements; i++)); do

    read -p "Enter element $i: " element

    numbers+=("$element")

done



echo "Original array: ${numbers[@]}"

sorted_array=$(insertion_sort "${numbers[@]}")

echo "Sorted array: $sorted_array"

