for i in **/*.hpp; do
	output=$(echo "$i" | tr '/.' '_' | tr '[:lower:]' '[:upper:]');
	count=$(grep "${output}_INCLUDED" $i | wc -l);
	if [ $count -le 1 ]; then
		echo "file: $i, search for: $output, returned: $count";
	fi;
done
