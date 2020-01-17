#!/usr/bin/env bash

ARGS=(--library sge --library awl --library mizuiro --library fcppt)

find examples libs plugins tests tools \( \( -name '*.hpp' -o -name '*.cpp' \) \) -exec update_headers.sh '{}' "${ARGS[@]}" \;
