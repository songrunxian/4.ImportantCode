#!/bin/bash
StartTime=`date +%s`
flag=0
flag1=0
while [[ a=a ]];do
 TimeNow=`date +%s`
 if [[ $[ $TimeNow - $StartTime ] -eq 2700 &&  $flag -eq 0  ]]; then
     StartTime=$TimeNow
     flag=1
     echo "rest"
     notify-send "rest"
 fi
 
 if [[ $[ $TimeNow - $StartTime  ] -eq 600  && $flag -eq 1  ]]; then
     StartTime=$TimeNow
     flag=0
     echo "study"
     notify-send "study"
 fi

 MinuteNow=`date +%M`
 if [[ $MinuteNow -eq 00 && $flag1 -eq 0 ]]; then
     flag1=1
     notify-send `date +%H`
 fi

 if [[ $MinuteNow -ne 00  ]]; then
     flag1=0
 fi

done
