#!/bin/bash

# Function to perform arithmetic operations
perform_arithmetic() {
    local num1="$1"
    local num2="$2"
    local operation="$3"
    
    case "$operation" in
        "+")
            result=$((num1 + num2))
            echo "Result: $result"
            ;;
        "-")
            result=$((num1 - num2))
            echo "Result: $result"
            ;;
        "*")
            result=$((num1 * num2))
            echo "Result: $result"
            ;;
        "/")
            if [ $num2 -ne 0 ]; then
                result=$((num1 / num2))
                echo "Result: $result"
            else
                echo "Cannot divide by zero."
            fi
            ;;
        *)
            echo "Invalid operation."
            ;;
    esac
}

# Read input from user
echo -n "Enter the first integer: "
read number1

echo -n "Enter the second integer: "
read number2

echo -n "Enter arithmetic operation (+, -, *, /): "
read arithmetic_operation

perform_arithmetic "$number1" "$number2" "$arithmetic_operation"
