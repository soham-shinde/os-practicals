#!/bin/bash

address_book_file="address_book.txt"

# Function to create a new address book
create_address_book() {
    touch "$address_book_file"
    echo "Address book created successfully."
}

# Function to view the address book
view_address_book() {
    if [ -e "$address_book_file" ]; then
        cat "$address_book_file"
    else
        echo "Address book is empty. Please create it first."
    fi
}

# Function to insert a record
insert_record() {
    echo "Enter Name: "
    read name
    echo "Enter Phone Number: "
    read phone
    echo "Enter Email: "
    read email

    echo "Name: $name, Phone: $phone, Email: $email" >> "$address_book_file"
    echo "Record inserted successfully."
}

# Function to delete a record
delete_record() {
    echo "Enter Name to delete: "
    read name

    if [ -e "$address_book_file" ]; then
        grep -v "$name" "$address_book_file" > temp.txt
        mv temp.txt "$address_book_file"
        echo "Record deleted successfully."
    else
        echo "Address book is empty. Please create it first."
    fi
}

# Function to modify a record
modify_record() {
    echo "Enter Name to modify: "
    read name

    if [ -e "$address_book_file" ]; then
        grep -v "$name" "$address_book_file" > temp.txt
        mv temp.txt "$address_book_file"

        echo "Enter New Name: "
        read new_name
        echo "Enter New Phone Number: "
        read new_phone
        echo "Enter New Email: "
        read new_email

        echo "Name: $new_name, Phone: $new_phone, Email: $new_email" >> "$address_book_file"
        echo "Record modified successfully."
    else
        echo "Address book is empty. Please create it first."
    fi
}

# Main menu
while true; do
    echo "Address Book Options:"
    echo "a) Create address book"
    echo "b) View address book"
    echo "c) Insert a record"
    echo "d) Delete a record"
    echo "e) Modify a record"
    echo "f) Exit"
    read -p "Enter your choice: " choice

    case "$choice" in
        a) create_address_book ;;
        b) view_address_book ;;
        c) insert_record ;;
        d) delete_record ;;
        e) modify_record ;;
        f) echo "Exiting. Goodbye!"; exit ;;
        *) echo "Invalid choice. Please select a valid option."
    esac
done
