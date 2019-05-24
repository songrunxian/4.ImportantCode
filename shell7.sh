#!/bin/bash
declare -a a
i=0
while [[ $i -lt 1000 ]]; do
    a=(${a[*]} 0)
    i=$[ $i + 1 ]
done

i=2

while [[ $[ $i * $i ] -lt 1000 ]]
do 
    if [[ ${a[$i]} -eq 0 ]]; then
        j=$[ 2 * $i ]
        while [[ $j -lt 1000 ]]; do
            a[$j]=1
            j=$[ ${j} + ${i}  ]
        done
    fi
    i=$[ $i + 1 ]
done

echo ${a[*]}
i=2
sum=0
while [[ $i -lt 1000 ]]; do
    if [[ ${a[$i]} -eq 0 ]]; then
        echo $i
    fi
   i=$[ ${i} + 1 ] 
   sum=$[ ${i} + ${sum} ]
done
echo $sum
