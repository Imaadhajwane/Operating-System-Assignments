#!/bin/bash

# Function to generate and print Fibonacci series
fibonacci_series() {
    local terms="$1"
    a=0
    b=1

    echo "Fibonacci series up to $terms terms:"
    for (( i = 1; i <= terms; i++ )); do
        echo -n "$a "
        fn=$((a + b))
        a=$b
        b=$fn
    done
    echo
}

# Read the number of terms from the user
echo -n "Enter the number of terms in Fibonacci series: "
read num_terms

fibonacci_series "$num_terms"
