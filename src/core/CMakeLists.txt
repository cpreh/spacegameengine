set(
	SGE_CORE_FILES
	include/sge/core/check_state.hpp
	include/sge/core/detail/class_symbol.hpp
	include/sge/core/exception.hpp
	src/core/exception.cpp
	src/core/include/sge/src/core/export_class_instantiation.hpp
	src/core/include/sge/src/core/export_function_instantiation.hpp
	src/core/include/sge/src/core/include_windows.hpp
)

add_sge_base_library(
	core
	INCLUDE_DIRS
		"${fcppt_INCLUDE_DIRS}"
	TRANSITIVE_INCLUDE_DIRS
		"${fcppt_INCLUDE_DIRS}"
)
