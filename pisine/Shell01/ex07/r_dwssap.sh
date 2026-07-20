cat /etc/passwd | grep -v '^#' |awk -F: NR%2==0{print $1}| rev | sort -r |sed -n "${FT_LINE1} ${FT_LINE2} p" | awk 'BEGIN {first=1} {if (!first) printf(", "); print $0; first=0;}' 
