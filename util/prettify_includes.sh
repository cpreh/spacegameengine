#!/bin/bash

if [[ $1 == 'run' ]]; then
	shift
	prettify_includes.py --reserved-prefix sge --reserved-prefix majutsu --reserved-prefix awl --reserved-prefix mizuiro --reserved-prefix fcppt  "$@" 2>>/tmp/prettify_errors
else
	SGE_MODEL_OBJ_INCLUDES="src/model/obj/include/sge/src/model/obj"
	find examples src include \( \( -name '*.hpp' -o -name '*.cpp' \) \
	-a ! -path "${SGE_MODEL_OBJ_INCLUDES}/basic_tokens_decl.hpp" \
	-a ! -path "${SGE_MODEL_OBJ_INCLUDES}/basic_grammar_decl.hpp" \
	-a ! -path "${SGE_MODEL_OBJ_INCLUDES}/token.hpp" \
	-a ! -path 'src/plugins/opengl/include/sge/opengl/common.hpp' \) \
	| xargs $0 run
fi
