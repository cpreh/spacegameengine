#include <sge/type_name.hpp>
#include <sge/iconv.hpp>
#ifdef SGE_HAS_GNU_DEMANGLE
#include <cxxabi.h>
#include <sge/scoped_ptr.hpp>
#include <sge/c_deleter.hpp>
#endif

sge::string const sge::type_name(
	sge::type_info const &ti)
{
#ifdef SGE_HAS_GNU_DEMANGLE
	int status;

	scoped_ptr< 
		char,
		c_deleter
		> name( 
		abi::__cxa_demangle(
			ti.get().name(), 
			0, 
			0, 
			&status));
	
	// demangling failed?
	if (status)
		return iconv(ti.get().name());
	
	return iconv(name.get());
#else
	return iconv(
		ti.get().name());
#endif
}
