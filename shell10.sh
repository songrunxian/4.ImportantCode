#!/bin/bash
TimeBegin=`date +%s`
RestBegin=0
flag=0

function CheckMin() {
    TimeNow=`date +%s`
    TimeBetween=$[ ( ${TimeNow} - ${TimeBegin} ) / 60  ]
    if [[ ${TimeBetween} -ge 45 && ${flag} -eq 0  ]]; then
        flag=1
        return 2
    fi
    if [[ ${TimeBetween} -ge 5 && ${flag} -eq 1 ]]; then
        flag=0
        return 1
    fi
    return 0
}

function CheckZero() {
    Mini=`date +%M`
    if [[ ${Mini} == "00"  ]]; then
        return 1
    fi
    return 0
}

while [[ true  ]]; do
   sleep 40
   CheckMin
   if [[ $? -eq 2 ]]; then
       echo "45"
   elif [[ $? -eq 1 ]]; then
       echo "rest time out"
   fi
   TimeBegin=`date +%s`
   CheckZero
   if [[ $? -eq 1  ]]; then
       echo "00"
   fi
done
