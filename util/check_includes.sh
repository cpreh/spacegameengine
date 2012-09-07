#!/bin/bash

INCLUDE_BINARY="check_includes"

"${INCLUDE_BINARY}" include || exit

"${INCLUDE_BINARY}" src/include || exit

"${INCLUDE_BINARY}" alda/include || exit

"${INCLUDE_BINARY}" alda/src/include || exit

function check_src() {
	"${INCLUDE_BINARY}" src/"$1"/include || exit
}

find src -name plugins -prune -o -name include -exec "${INCLUDE_BINARY}" '{}' \; || exit

function check_example() {
	"${INCLUDE_BINARY}" examples/"$1"/include || exit
	"${INCLUDE_BINARY}" examples/"$1"/src/include || exit
}

check_example rucksack/testbed

function check_subdir() {
	for i in "$1"/* ; do
		if [[ -d "${i}" && "$(basename "${i}")" != include ]] ; then
			"${INCLUDE_BINARY}" "$i"/include || exit
		fi
	done
}

check_subdir src/plugins

check_subdir tools
