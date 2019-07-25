#!/bin/bash

#pid=$1
#echo $pid
#interval=1
#while true
#do
#    echo $(date +"%y-%m_%d %H:%M:%S") >> proc_memlog.txt
#    cat /proc/$pid/status|grep -e VmRSS >> proc_memlog.txt

	
cat /proc/$PID/status

cat /proc/$PID/status | grep RSS >> "$LOG"

interval=60 
if [ "$1" != "" ]
then
interval=$1
fi
echo "检查时间间隔(单位秒)："$interval
datetime=`date +'%Y%m%d'`
echo""> /home/桌面/linux暑假培訓/2019.7.16簡易服務器集羣監控系統-$datetime
while :
do
echo `date +'%Y%m%d %H:%M:%S'` >> /home/桌面/linux暑假培訓/2019.7.16簡易服務器集羣監控系統-$datetime
cat /proc/meminfo | grep -E 'MemTotal|MemFree|Cached' |grep -v SwapCached|xargs >>/home/桌面/linux暑假培訓/2019.7.16簡易服務器集羣監控系統-$datetime 
top -b -d 1 -n 1 |grep -E "PID.*USER|load|Cpu|Data" >> /home/桌面/linux暑假培訓/2019.7.16簡易服務器集羣監控系統-$datetime
sleep $interval
echo "-------------------------------------" >> /home/桌面/linux暑假培訓/2019.7.16簡易服務器集羣監控系統-$datetime





PROCESS=进程名
LOG="/mnt/memlog.txt"

sleep 10

#删除上次的监控文件
if [ -f "$LOG" ];then 
    rm "$LOG"
fi

#过滤出需要的进程ID
PID=$(ps | grep $PROCESS | grep -v 'grep' | awk '{print $1;}')

while [ "$PID" != "" ]    
do
    cat /proc/$PID/status | grep RSS >> "$LOG"#过滤出VmRSS行
    sleep 5
    PID=$(ps | grep $PROCESS | grep -v 'grep' | awk '{print $1;}')
done
done

#截取top的内存使用数
#如果文件存在，重命名
if [ -a memory.txt ]
then
    mv memory.txt memory_at_`date +%H:%M:%S`.txt
fi
#如果没有输入参数，默认60s检查一次
if [ $# -eq 0 ]
then
    DREAM=60
else
    DREAM=$1
fi
echo "检查内存时间间隔(秒)：${DREAM}"
#当前内存数
RES_NOW=2
#上一次内存数
RES_BEF=1
#一致时退出
while [ $RES_NOW -ne $RES_BEF ]
do
    RES_BEF=$RES_NOW
    #取现在内存
    RES_NOW=$(top -d 1 -n 1|grep 'DataAccessEngin'|cut -d " " -f 14)
    TIME=`date +'%y%m%d %H:%M:%S'`
    #输出
    echo "${TIME}进程使用内存数=[$RES_NOW]"
    echo "${TIME}  ${RES_NOW}">>memory.txt
    sleep $DREAM
done

echo "结束"



==============================================================
eval $(ps -aux --sort=-%cpu -h | awk -v num=0 \
    '{ if ($3 < 50) {exit} else {printf("cpupid["num"]=%d;", $2}'\
    )

if [[ ${cpunum} -gt 0 || ${memnum} -gt 0 ]]; then
    sleep 5
else
    exit 0
fi

NowTime=`date +"%Y-%m-%d__%H:%M:%S"`

if [[ ${cpunum} -gt 0 ]]; then
    for i in ${cpupid[*]}; do
        eval $(ps -aux -q $i -h | awk -v num=0 \
            '{if ($3 < 50) {exit} else {printf("")}}')















