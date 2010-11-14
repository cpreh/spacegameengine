#ifndef SGE_SHADER_VF_TO_STRING_HPP_INCLUDED
#define SGE_SHADER_VF_TO_STRING_HPP_INCLUDED

#include <sge/shader/format_printer.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <fcppt/string.hpp>
#include <boost/mpl/for_each.hpp>

namespace sge
{
namespace shader
{
template<typename Format>
renderer::glsl::string const
vf_to_string()
{
	fcppt::string s;
	boost::mpl::for_each<typename Format::elements>(
		format_printer(
			s));
	return s;
}
}
}

#endif
