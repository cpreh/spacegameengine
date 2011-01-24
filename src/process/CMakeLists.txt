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

APPEND_SOURCE_DIR_AND_MAKE_GROUPS(
	"${SGE_PROCESS_FILES}"
	SGE_PROCESS_FILES_ABS
)

ADD_LIBRARY(
	sgeprocess
	SHARED
	${SGE_PROCESS_FILES_ABS}
)

TARGET_LINK_LIBRARIES(
	sgeprocess
	sgecore
)

INSTALL(
	TARGETS
	sgeprocess
	DESTINATION
	lib
)

INSTALL(
	DIRECTORY
	${CMAKE_SOURCE_DIR}/include/sge/process
	DESTINATION
	include/sge
)
