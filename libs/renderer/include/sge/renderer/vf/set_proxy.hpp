//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_SET_PROXY_HPP_INCLUDED
#define SGE_RENDERER_VF_SET_PROXY_HPP_INCLUDED

#include <sge/renderer/vf/label_value_type.hpp>
#include <sge/renderer/vf/proxy.hpp>


namespace sge::renderer::vf
{

template<
	typename Label,
	typename Part,
	typename Constness
>
void
set_proxy(
	sge::renderer::vf::proxy<
		Part,
		Constness
	> _proxy,
	Label const &,
	sge::renderer::vf::label_value_type<
		Part,
		Label
	> const &_value
)
{
	_proxy. template set<
		Label
	>(
		_value
	);
}

}

#endif
