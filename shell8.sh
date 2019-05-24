#!/bin/bash
declare -a a
i=0
while [[ $i -lt 1000 ]]; do
    a=(${a[*]} 0)
    i=$[ $i + 1 ]
done
i=2
while [[ $i -lt 1000 ]]; do
    if [[ ${a[$i]} -eq 0 ]]; then
        a[0]=$[ a[0] + 1 ]
        a[a[0]]=$i
    fi
    j=1
    while [[ $j -lt ${a[0]} || $j -eq ${a[0]} ]]; do
        if [[ $[ a[$j] * $i  ]  -lt 1000  ]]; then
            a[$[ a[$j] * $i]]=1
        fi
        j=$[ $j + 1 ]
    done
    i=$[ $i + 1 ]
done
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
