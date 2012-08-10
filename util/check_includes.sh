#!/bin/sh

INCLUDE_BINARY="check_includes"

"${INCLUDE_BINARY}" include || exit

"${INCLUDE_BINARY}" src/include || exit

"${INCLUDE_BINARY}" alda/include || exit

"${INCLUDE_BINARY}" alda/src/include || exit

check_src() {
	"${INCLUDE_BINARY}" src/"$1"/include || exit
}

find src -name plugins -prune -o -name include -exec "${INCLUDE_BINARY}" '{}' \; || exit

check_example() {
	"${INCLUDE_BINARY}" examples/"$1"/include || exit
	"${INCLUDE_BINARY}" examples/"$1"/src/include || exit
}

check_example rucksack/testbed

for i in src/plugins/* ; do
	if [[ -d "${i}" ]] ; then
		"${INCLUDE_BINARY}" "$i"/include || exit
	fi
done
