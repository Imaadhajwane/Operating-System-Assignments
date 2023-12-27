array=(5 2 9 1 5 6)

while true; do
    echo -n "Enter the element to search for (integer only): "
    read search_element

    if [[ "$search_element" =~ ^[0-9]+$ ]]; then
        found=false

        for element in "${array[@]}"; do
            if [ "$element" == "$search_element" ]; then
                found=true
                break
            fi
        done

        if [ "$found" = true ]; then
            echo "$search_element found in the array."
            break
        else
            echo "$search_element not found in the array."
            break
        fi
    else
        echo "Invalid input. Please enter an integer."
    fi
done

