#!/bin/bash

database_file="database.txt"

# Create database file if it doesn't exist
touch "$database_file"

# Function to create a new record
insert_record() {
    echo "$1:$2:$3" >> "$database_file"
    echo "Record inserted successfully."
}

# Function to delete a record by roll number
delete_record() {
    sed -i "/^$1:/d" "$database_file"
    echo "Record deleted successfully."
}

# Function to update a record by roll number
update_record() {
    sed -i "s/^$1:.*/$1:$2:$3/" "$database_file"
    echo "Record updated successfully."
}

# Function to view all records
view_records() {
    cat "$database_file"
}

# Read operation from user
echo "Available operations:"
echo "1. Insert"
echo "2. Delete"
echo "3. Update"
echo "4. View All Records"
echo -n "Select an operation (1/2/3/4): "
read operation

case $operation in
    1)
        echo -n "Enter Roll Number: "
        read roll
        echo -n "Enter Name: "
        read name
        echo -n "Enter Address: "
        read address
        insert_record "$roll" "$name" "$address"
        ;;
    2)
        echo -n "Enter Roll Number to delete: "
        read roll
        delete_record "$roll"
        ;;
    3)
        echo -n "Enter Roll Number to update: "
        read roll
        echo -n "Enter New Name: "
        read name
        echo -n "Enter New Address: "
        read address
        update_record "$roll" "$name" "$address"
        ;;
    4)
        view_records
        ;;
    *)
        echo "Invalid operation."
        ;;
esac

