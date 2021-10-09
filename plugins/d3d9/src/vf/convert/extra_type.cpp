//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vf/convert/extra_type.hpp>
#include <sge/d3d9/vf/convert/extra_type_visitor.hpp>
#include <sge/renderer/vf/dynamic/extra.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/variant/object_impl.hpp>

D3DDECLTYPE
sge::d3d9::vf::convert::extra_type(sge::renderer::vf::dynamic::extra const &_extra)
{
  return fcppt::variant::apply(sge::d3d9::vf::convert::extra_type_visitor(), _extra.type());
}
