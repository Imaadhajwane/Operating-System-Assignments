while true; do
    read -p "Enter the first number: " num1
    read -p "Enter the second number: " num2

    if [[ ! "$num1" =~ ^[0-9]+$ || ! "$num2" =~ ^[0-9]+$ ]]; then
        echo "Invalid input. Please enter valid numbers."
    else
        sum=$((num1 + num2))
        echo "The sum of $num1 and $num2 is: $sum"
        break
    fi
done
