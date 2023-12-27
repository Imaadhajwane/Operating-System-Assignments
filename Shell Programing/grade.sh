echo -n "Enter the marks: "
read marks

if [ "$marks" -ge 90 ] && [ "$marks" -le 100 ]; then
    echo "Grade: O"
elif [ "$marks" -ge 80 ] && [ "$marks" -le 89 ]; then
    echo "Grade: E"
elif [ "$marks" -ge 70 ] && [ "$marks" -le 79 ]; then
    echo "Grade: A"
elif [ "$marks" -ge 60 ] && [ "$marks" -le 69 ]; then
    echo "Grade: B"
elif [ "$marks" -ge 50 ] && [ "$marks" -le 59 ]; then
    echo "Grade: C"
else
    echo "Grade: F"
fi
