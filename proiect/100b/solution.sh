#!/bin/bash

#100. b)
#Write a shell script that takes groups  of 3 parameters  (a name of a file a 
#word and a number k).For each groups, print all the lines from the file that 
#contain the word exactly k times.


#checks if the input is a file or not
if [ ! -f $1 ]; then
	echo "Input is not a file"
	exit
fi

while [ $# -ne 0 ]; do
	file=$1
	word=$2
	k=$3
	while read line; do
		rez=`echo $line | grep -o "$word" | wc -l`
		if [ $rez -eq $k ]; then
			echo  $line
		fi 
	done < $file
	shift
	shift
	shift
done
