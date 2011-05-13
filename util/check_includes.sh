#!/bin/sh

INCLUDE_BINARY="check_includes"

"${INCLUDE_BINARY}" include || exit

"${INCLUDE_BINARY}" src SGE_ | grep -v plugins

"${INCLUDE_BINARY}" src/plugins SGE_ || exit
