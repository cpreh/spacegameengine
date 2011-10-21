#!/bin/bash

if [[ $1 == 'run' ]]; then
	shift
	prettify_includes.py --reserved-prefix sge --reserved-prefix majutsu --reserved-prefix awl --reserved-prefix mizuiro --reserved-prefix fcppt  "$@" 2>>/tmp/prettify_errors
else
	find examples src include \( \( -name '*.hpp' -o -name '*.cpp' \) -a ! -path 'src/model/obj/basic_tokens_decl.hpp' -a ! -path 'src/model/obj/basic_grammar_decl.hpp' -a ! -path 'src/model/obj/token.hpp' -a ! -path 'src/plugins/opengl/common.hpp' \) | xargs $0 run
fi
