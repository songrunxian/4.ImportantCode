awk '/MemTotal/{total=$2}/MemFree/{free=$2}END{print (total-free)/1024}'  /proc/meminfo

awk '/SwapTotal/{total=$2}/SwapFree/{free=$2}END{print (total-free)/1024}'  /proc/meminfo

a=`awk '/pgpgin/{print $2}' /proc/vmstat`
sleep 240
b=`awk '/pgpgin/{print $2}' /proc/vmstat`
ioin=$(((b-a)/240))

a=`awk '/pgpgout/{print $2}' /proc/vmstat`
sleep 240
b=`awk '/pgpgout/{print $2}' /proc/vmstat`
ioout=$(((b-a)/240))

