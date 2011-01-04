INCLUDE(CheckCXXSourceRuns)

CHECK_CXX_SOURCE_RUNS(
        "#include <unistd.h>
        #include <cstdlib>
        int main()
        {
          return _POSIX_VERSION >= 200100
                 ? EXIT_SUCCESS
                 : EXIT_FAILURE;
        }"
        ICONV_HAVE_POSIX
)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PATH(
	ICONV_INCLUDE_DIR
	NAMES iconv.h
	PATHS ${ICONV_ROOT}/include
)

IF(
	ICONV_HAVE_POSIX
)
	FIND_PACKAGE_HANDLE_STANDARD_ARGS(
		ICONV
		DEFAULT_MSG
		ICONV_INCLUDE_DIR
	)
ELSE()

	FIND_LIBRARY(
		ICONV_LIBRARY
		NAMES libiconv
		PATHS ${ICONV_ROOT}/lib
	)

	FIND_PACKAGE_HANDLE_STANDARD_ARGS(
		ICONV
		DEFAULT_MSG
		ICONV_INCLUDE_DIR
		ICONV_LIBRARY
	)
ENDIF()

# TODO: check for the iconv signature
