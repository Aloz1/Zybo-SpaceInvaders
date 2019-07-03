set workspace [lindex $argv 0]
set hwspec $workspace/[lindex $argv 1]

set core [lindex $argv 2]
set os [lindex $argv 3]

set hwproj hw1
set bspproj bsp_${os}1

setws ${workspace}
createhw -name ${hwproj} -hwspec ${hwspec}
createbsp -name ${bspproj} -hwproject ${hwproj} -proc ${core} -os ${os}
importprojects ${workspace}
