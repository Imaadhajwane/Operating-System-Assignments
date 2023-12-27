declare -a numbers

for ((i = 1; i <= 10; i++)); do
    while true; do
        read -p "Enter number $i: " num

        if [[ ! "$num" =~ ^[0-9]+$ ]]; then
            echo "Invalid input. Please enter a valid number."
        else
            numbers+=("$num")
            break
        fi
    done
done

sorted_numbers=($(printf '%s\n' "${numbers[@]}" | sort -nr))

second_largest=${sorted_numbers[1]}

echo "The second largest number is: $second_largest"
