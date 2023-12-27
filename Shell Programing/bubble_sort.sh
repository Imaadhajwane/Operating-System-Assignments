echo -n "Enter the number of elements in the array: "
read n

declare -a elements

i=0
while [ $i -lt $n ]
do
    echo -n "Enter element $((i+1)): "
    read element
    elements[$i]=$element
    i=$((i+1))
done

i=0
while [ $i -lt $((n-1)) ]
do
    j=0
    while [ $j -lt $((n-i-1)) ]
    do
        if [ "${elements[$j]}" -gt "${elements[$j+1]}" ]
        then
            temp="${elements[$j]}"
            elements[$j]="${elements[$j+1]}"
            elements[$j+1]="$temp"
        fi
        j=$((j+1))
    done
    i=$((i+1))
done

echo "Sorted array: ${elements[*]}"

