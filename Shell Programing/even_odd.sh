echo "Enter a number:"
read num
if [ "$num" -eq "$num" ] 2>/dev/null; then
    if [ $((num % 2)) -eq 0 ]; then
        echo "$num is even."
    else
        echo "$num is odd."
    fi
else
    echo "Invalid input. Please enter a valid number."
fi
