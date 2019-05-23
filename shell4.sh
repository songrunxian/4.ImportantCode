#!/bin/bash
year=$1;

function isleapyear() {
    year=$1
    if [[ $[year%4] -eq 0 || $[year%100] -ne 0 ]]; then
        echo 366;
    elif [[ $[year%400] -eq 0 ]]; then
        echo 366;
    else
        echo 365;
    fi
}
i=0
sum=0
this=0
while [[ i -lt $2 || i -eq $2 ]]; do
    j=$[$year+$i]
    this=`isleapyear ${j}`
    sum=$[ ${sum}+${this} ]
    i=$(($i+1))
done
echo $sum;
