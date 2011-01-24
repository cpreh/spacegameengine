SET(
	SGE_PROCESS_FILES
	include/sge/process/argument_list.hpp
	include/sge/process/call.hpp
	include/sge/process/exit_code.hpp
	include/sge/process/output.hpp
	include/sge/process/symbol.hpp
	src/process/call.cpp
	src/process/output.cpp
)

ADD_SGE_BASE_LIBRARY(
	process
	""
)
