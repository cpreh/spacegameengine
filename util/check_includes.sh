#!/bin/bash

INCLUDE_BINARY="check_includes"

find examples libs plugins -name include -exec "${INCLUDE_BINARY}" '{}' \; || exit
