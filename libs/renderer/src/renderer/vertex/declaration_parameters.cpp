//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>


sge::renderer::vertex::declaration_parameters::declaration_parameters(
	sge::renderer::vf::dynamic::format const &_format
)
:
	format_(
		_format
	)
{
}

sge::renderer::vf::dynamic::format const &
sge::renderer::vertex::declaration_parameters::format() const
{
	return format_;
}
