#!/bin/bash
Len=( 0 0 0 )
Str=( 0 0 0 )
Path=( 0 0 0 )
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
    if [[ ${#i} -ge ${Len[0]} ]]; then
            Len[2]=${Len[1]}
            Str[2]=${Str[1]}
            Path[2]=${Path[1]}
            Len[1]=${Len[0]}
            Str[1]=${Str[0]}
            Path[1]=${Path[0]}
            Len[0]=${#i}
            Str[0]=${i}
            Path[0]=${File}
        elif [[ ${#i} -ge ${Len[1]} ]]; then
            Len[2]=${Len[1]}
            Str[2]=${Str[1]}
            Path[2]=${Path[1]}
            Len[1]=${#i}
            Str[1]=${i}
            Path[1]=${File}
        elif [[ ${#i} -ge ${Len[2]} ]]; then
            Len[2]=${#i}
            Str[2]=${i}
            Path[2]=${File}
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
       Check=`Fliter $i`
       if [[ ${Check} -eq 0 ]]; then
          FindFile $i
       fi
    else
       echo "wrong file"
       exit
    fi
done

echo "${Len[0]}:${Str[0]}:${Path[0]}:`grep ${Str[0]} -n ${Path[0]}| cut -d ":" -f 1`"
echo "${Len[1]}:${Str[1]}:${Path[1]}:`grep ${Str[1]} -n ${Path[1]}| cut -d ":" -f 1`"
echo "${Len[2]}:${Str[2]}:${Path[2]}:`grep ${Str[2]} -n ${Path[2]}| cut -d ":" -f 1`"

