#!/bin/bash

if [ $# -ne 3 ]; then
    echo "Incorrect number of flags."
    exit 1
fi

program="./$1"
img_dir="$2"
message="$3"

files=$(find "$img_dir" -type f)

s1="sleep 0.4"
s2="eval sleep 1.6 ; clear"
clear

# -h / --help test:
echo "Running tests for (-h / --help) flag..." ; $s2
echo "$program" ; $s1 
./$program ; $s2
echo "$program -h" ; $s1
./$program -h ; $s2
echo "$program --help" ; $s1
./$program --help ; $s2

# -i / --info test:
echo "Running tests for (-i / --info) flag..." ; $s2
for file in $files; do
    echo "$program -i $file" ; $s1
    ./$program -i "$file" ; $s2
    echo "$program --info $file" ; $s1
    ./$program --info "$file" ; $s2
done

# -c / --check test:
echo "Running tests for (-c / --check) flag..." ; $s2
for file in $files; do
    echo "$program -c $file \"$message\"" ; $s1
    ./$program -c "$file" "$message" ; $s2
    echo "$program --check $file \"$message\"" ; $s1
    ./$program --check "$file" "$message" ; $s2
done

# -e / --encrypt test:
echo "Running tests for (-e / --encrypt) flag..." ; $s2
for file in $files; do
    echo "$program -e $file \"$message\"" ; $s1
    ./$program -e "$file" "$message" ; $s2
    echo "$program --encrypt $file \"$message\"" ; $s1
    ./$program --encrypt "$file" "$message" ; $s2
done

# -d / --decrypt test:
echo "Running tests for (-d / --decrypt) flag..." ; $s2
for file in $files; do
    echo "$program -d $file" ; $s1
    ./$program -d "$file" ; $s2
    echo "$program --decrypt $file" ; $s1
    ./$program --decrypt "$file"
    $s2
done
