#/bin/bash
line1=" ___  ___  ___   _      _      _____  _____  "
line2=" |  \/  | / _ \ | |    | |    |  _  |/  __ \\ "
line3=" | .  . |/ /_\ \| |    | |    | | | || /  \/ "
line4=" | |\/| ||  _  || |    | |    | | | || |     "
line5=" | |  | || | | || |____| |____\ \_/ /| \__/\\ "
line6=" \_|  |_/\_| |_/\_____/\_____/ \___/  \____/     by jwalle "
cols=$(tput cols)
let evencheck="(($cols)%2)"
if [ $evencheck -eq 0 ]
	then
		let first=$(((cols / 2) - 24))
	else
		let first=$(((cols / 2) - 23))
fi
second=$(((cols / 2) - 23))
third=$(((cols / 2) - 37))
tput clear
printf "\033[1;91;100m"
printf '%*s\n' "$cols" '' |  tr ' ' -
printf '%s%*s%s%*s%s\n' "|" "$first" " " "$line1" "$second" " " "|"
printf '%s%*s%s%*s%s\n' "|" "$first" " " "$line2" "$second" " " "|"
printf '%s%*s%s%*s%s\n' "|" "$first" " " "$line3" "$second" " " "|"
printf '%s%*s%s%*s%s\n' "|" "$first" " " "$line4" "$second" " " "|"
printf '%s%*s%s%*s%s\n' "|" "$first" " " "$line5" "$second" " " "|"
printf '%s%*s%s%*s%s\n' "|" "$first" " " "$line6" "$third" " " "|"
for ((x = 0; x < 1; x++)); do
	printf '%s%*s%s\n' "|" "$((cols - 1))" "|"
done
printf '%*s' "$cols"  '' |  tr ' ' -
printf "\033[0m"
echo