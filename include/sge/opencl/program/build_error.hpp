#ifndef SGE_OPENCL_PROGRAM_BUILD_ERROR_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_BUILD_ERROR_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/symbol.hpp>
#include <sge/exception.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace opencl
{
namespace program
{
class SGE_CLASS_SYMBOL build_error
:
	public sge::exception
{
public:
	SGE_SYMBOL explicit build_error(
		fcppt::string const &);

	SGE_SYMBOL fcppt::string const &
	message() const;

	SGE_SYMBOL
	virtual ~build_error() throw();
private:
	fcppt::string message_;
};
}
}
}

#endif
