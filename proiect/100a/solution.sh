#!/bin/bash

#100. a)
#Write a shell script that creates a file containing the name of each text files 
#from a folder (given as parameter) and its subfolders that contain worde 
#longer than n characters (read n  from keyboard).  The file will be ordered 
#alphabetically.



#checks if the input is a directory or not
if [ ! -d $1 ]; then
	echo "Argument is not a directory"
	exit
fi

#read input from the user
read -p "Enter value = " n
for x in `find $1 -type f`; do
    for y in `cat $x`; do
	        if [ ${#y} -gt $n ]; then
				file=`echo $x | awk -F "/" '{ print $NF }'`
				echo $file
				break
			fi
	done
done |sort -u > sort.txt
