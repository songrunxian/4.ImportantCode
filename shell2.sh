TimeNow=`date +%s`
TimeLast=$[(${TimeNow} - ${TimeLogin}) / 60]
DateNow=`date +"%Y-%m-%d %H:%M"`
User=`whoami`
echo "${DateNow} ${User} lasted ${TimeLast} minutes" >> /var/log/login.log
