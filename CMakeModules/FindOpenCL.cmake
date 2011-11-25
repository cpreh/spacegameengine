if(
	CMAKE_SIZEOF_VOID_P EQUAL 8
)
	set(OPENCL_64BIT TRUE)
else()
	set(OPENCL_64BIT FALSE)
endif()

if(WIN32)
	if(
		$ENV{ATISTREAMSDKROOT}
	)
		if(
			OPENCL_64BIT
		)
			set(
				OPENCL_LIBRARYDIR
				"$ENV{ATISTREAMSDKROOT}/lib/x86_64"
			)
		else()
			set(
				OPENCL_LIBRARYDIR
				"$ENV{ATISTREAMSDKROOT}/lib/x86"
			)
		endif()
	else()
		if(
			OPENCL_64BIT
		)
			set(
				OPENCL_NVIDIA_ROOT
				"$ENV{ProgramW6432}/NVIDIA GPU Computing Toolkit/CUDA/v4.0"
			)

			set(
				OPENCL_LIBRARY_HINT
				"${OPENCL_NVIDIA_ROOT}/lib/x64"
			)
		else()
			set(
				OPENCL_NVIDIA_ROOT
				"$ENV{ProgramFiles}/NVIDIA GPU Computing Toolkit/CUDA/v4.0"
			)

			set(
				OPENCL_LIBRARY_HINT
				"${OPENCL_NVIDIA_ROOT}/lib/Win32"
			)
		endif()

		set(
			OPENCL_INCLUDE_HINT
			"${OPENCL_NVIDIA_ROOT}/include"
		)
	endif()

	unset(OPENCL_NVIDIA_ROOT)
else()
	set(
		OPENCL_INCLUDE_HINT
		"/opt/cuda/include;/opt/local/cuda/include"
	)

	if(
		OPENCL_64BIT
	)
		set(
			OPENCL_LIBRARY_HINT
			"/opt/cuda/lib64;/opt/local/cuda/lib64"
		)
	else()
		set(
			OPENCL_LIBRARY_HINT
			"/opt/cuda/lib32;/opt/local/cuda/lib32"
		)
	endif()
endif()

unset(OPENCL_64BIT)

find_path(
	OPENCL_INCLUDE_DIR
	CL/cl.h
	PATHS
	"${OPENCL_INCLUDEDIR}"
	HINTS
	"${OPENCL_INCLUDE_HINT}"
)

unset(OPENCL_INCLUDE_HINT)

find_library(
	OPENCL_LIBRARY
	OpenCL
	PATHS
	"${OPENCL_LIBRARYDIR}"
	HINTS
	"${OPENCL_LIBRARY_HINT}"
)

unset(OPENCL_LIBRARY_HINT)

include(
	FindPackageHandleStandardArgs
)

find_package_handle_standard_args(
	OPENCL
	DEFAULT_MSG
	OPENCL_LIBRARY
	OPENCL_INCLUDE_DIR
)

if(
	OPENCL_FOUND
)
	set(
		OPENCL_INCLUDE_DIRS
		"${OPENCL_INCLUDE_DIR}"
	)

	set(
		OPENCL_LIBRARIES
		"${OPENCL_LIBRARY}"
	)
endif()

mark_as_advanced(
	OPENCL_LIBRARY
	OPENCL_INCLUDE_DIR
)
