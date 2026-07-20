#!/bin/sh

n1=$(printf "%s" "$FT_NBR1"\
	|sed "s/'/0/g"\
	|sed 's/\\/1/g'\
	|sed 's/"/2/g'\
	|sed 's/?/3/g'\
	|sed 's/!/4/g')
	n2=$(printf "%s" "$FT_NBR2"| tr "mrdoc" "01234")

	echo "obase = 13; ibase = 5; $n1 + $n2" \
		|bc \
		|tr '0123456789ABC' 'gtaio luSnemf'
