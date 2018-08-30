print() {
	for fileOrDirectory in $1/* ; do
		if [ -d "$fileOrDirectory" ] ; then
			print $fileOrDirectory
		else
			if [ -f "$fileOrDirectory" ]; then
				echo $fileOrDirectory >>  rendu.txt
				cat $fileOrDirectory >> rendu.txt
				echo "\nresultat:" >> rendu.txt
				./expert-system $fileOrDirectory >> rendu.txt 2>&1
				if [ $? == 0 ];  then
					cat Log.txt >> rendu.txt
				fi
				echo "\n*******************************\n\n" >> rendu.txt
			else
				 echo "$fileOrDirectory is not valid" >> rendu.txt;
			fi
		fi
	done
}
rm rendu.txt
print $1
echo "script finish" | tee -a rendu.txt
