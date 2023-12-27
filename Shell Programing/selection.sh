#!/bin/bash



# Function to perform selection sort

selection_sort() {

    local arr=("$@")       # Convert arguments to array

    local n=${#arr[@]}     # Get length of the array



    for ((i = 0; i < n-1; i++)); do

        min_index=$i



        # Find the index of the minimum element in the remaining unsorted array

        for ((j = i+1; j < n; j++)); do

            if ((arr[j] < arr[min_index])); then

                min_index=$j

            fi

        done



        # Swap arr[i] and arr[min_index]

        temp=${arr[i]}

        arr[i]=${arr[min_index]}

        arr[min_index]=$temp

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

sorted_array=$(selection_sort "${numbers[@]}")

echo "Sorted array: $sorted_array"

