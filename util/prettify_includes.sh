#!/usr/bin/env bash

LIBS=(--library sge --library awl --library mizuiro --library fcppt)
DIRS=(examples libs plugins tests)

prettify_includes "${LIBS[@]}" "${DIRS[@]}"

prettify_includes --library control_config "${LIBS[@]}" tools/control_config
