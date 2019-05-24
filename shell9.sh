#!/bin/bash
#!/bin/bash
Max=0
Second=0
Third=0
MaxString=0
SecondString=0
ThirdString=0
function Fliter() {
  FliterFile=$1
    file ${FliterFile} | grep -q -w "text"
  if [[ $? -eq 0 ]]; then
    echo 0
  else
    echo 1
  fi
}
function FindFile() {
  local File=$1
  for i in `cat ${File} | tr -c -s "A-Za-z" "\n"`; do
    echo $i
    if [[ ${Max} -lt ${#i} ]]; then
      Third=${#SecondString}
      ThirdString=$SecondString
      Second=${#MaxString}
      SecondString=$MaxString
      Max=${#i}
      MaxString=${i}
      
    fi
  done
}
function FindDir() {
  local DirName=$1
  for i in `ls -A ${DirName}`; do
    if [[ -d ${DirName}/${i} ]]; then
      FindDir ${DirName}/${i}
    elif [[ -f ${DirName}/${i} ]]; then
      Check=`Fliter ${DirName}/${i}`
      if [[ ${Check} -eq 0 ]]; then
        FindFile ${DirName}/${i}
      fi
    fi
  done
}
for i in $@; do
    if [[  -d $i ]]; then
       FindDir $i
    elif [[ -f $i ]]; then
       Check=`FliterFile $i`
       if [[ ${Check} -eq 0 ]]; then
          FindFile $i
       fi
    else
       echo "wrong file"
       exit
    fi
done
printf "MaxString=%s, Max=%d\n" ${MaxString} ${Max}
printf "SecondString=%s, Second=%d\n" ${SecondString} ${Second}
printf "ThirdString=%s, Third=%d\n" ${ThirdString} ${Third}
