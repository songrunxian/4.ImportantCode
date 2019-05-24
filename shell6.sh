#!/bin/bash
a=(1 2 3)
echo ${a[0]}
echo ${a[@]}
echo ${a[*]}
echo ${#a[@]}
echo ${#a[*]}
for i  in ${a[@]}
do 
    echo $i
done
a=(${a[@]} 4)
echo ${a[@]}
a[1]=5
echo ${a[@]}
unset a[1]
echo ${a[@]}
unset a
echo ${a[@]}
