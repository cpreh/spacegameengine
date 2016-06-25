set(
	SGE_CORE_FILES
	libs/core/include/sge/core/check_state.hpp
	libs/core/include/sge/core/detail/class_symbol.hpp
	libs/core/include/sge/core/exception.hpp
	libs/core/src/core/exception.cpp
	libs/core/src/core/include/sge/src/core/export_class_instantiation.hpp
	libs/core/src/core/include/sge/src/core/export_function_instantiation.hpp
	libs/core/src/core/include/sge/src/core/include_windows.hpp
)

add_sge_base_library(
	core
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
	TRANSITIVE_ADDITIONAL_DEPS
		fcppt_core_interface
)
