# Set the field separator to a comma
BEGIN {
    FS = ","
    print "Roll Number, Name, Subject 1, Subject 2, Subject 3, Subject 4, Subject 5, Average, Grade"
}

# Process each line in the input file
{
    roll_number = $1
    name = $2
    subject1 = $3
    subject2 = $4
    subject3 = $5
    subject4 = $6
    subject5 = $7
    
    # Calculate the average
    total_marks = subject1 + subject2 + subject3 + subject4 + subject5
    average = total_marks / 5
    
    # Determine the grade
    if (subject1 >= 40 && subject2 >= 40 && subject3 >= 40 && subject4 >= 40 && subject5 >= 40) 
    {
        if (average > 90) {
            grade = "O"
        } else if (average >= 80 && average <= 90) {
            grade = "A+"
        } else if (average >= 70 && average <= 79) {
            grade = "A"
        } else if (average >= 65 && average <= 69) {
            grade = "B+"
        } else if (average >= 60 && average <= 65) {
            grade = "B"
        } else if (average >= 50 && average <= 59) {
            grade = "C+"
        } else if (average >= 45 && average <= 49) {
            grade = "C"
        } else {
            grade = "D"
        }
    }
    else
    {
        grade = "F"
        average = "0"
    }
    
    print roll_number, name, subject1, subject2, subject3, subject4, subject5, "Total Average:" average, "Grade:" grade
}

