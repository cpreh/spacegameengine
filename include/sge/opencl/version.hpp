#ifndef SGE_OPENCL_VERSION_HPP_INCLUDED
#define SGE_OPENCL_VERSION_HPP_INCLUDED

#include <sge/opencl/symbol.hpp>
#include <string>

namespace sge
{
namespace opencl
{
class version
{
public:
	typedef
	unsigned
	unit;

	SGE_OPENCL_SYMBOL explicit
	version(
		std::string const &);

	SGE_OPENCL_SYMBOL unit
	major_part() const;

	SGE_OPENCL_SYMBOL unit
	minor_part() const;

	SGE_OPENCL_SYMBOL std::string const &
	platform_specific() const;
private:
	unit major_;
	unit minor_;
	std::string platform_specific_;
};
}
}

#endif
