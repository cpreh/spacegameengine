#!/bin/sh

INCLUDE_BINARY="check_includes"

"${INCLUDE_BINARY}" include

"${INCLUDE_BINARY}" | grep -v plugins

"${INCLUDE_BINARY}" SGE_:src/plugins
