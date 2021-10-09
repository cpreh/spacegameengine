//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vf/convert/vector_type.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/vf/dynamic/element_type.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <fcppt/text.hpp>

D3DDECLTYPE
sge::d3d9::vf::convert::vector_type(sge::renderer::vf::dynamic::vector const &_vector)
{
  if (_vector.element_type() != sge::renderer::vf::dynamic::element_type::float_)
    throw sge::renderer::unsupported(
        FCPPT_TEXT("D3D9 only supports float vectors for pos or texpos!"),
        FCPPT_TEXT(""),
        FCPPT_TEXT(""));

  switch (_vector.element_count().get())
  {
  case 1u:
    return D3DDECLTYPE_FLOAT1;
  case 2u:
    return D3DDECLTYPE_FLOAT2;
  case 3u:
    return D3DDECLTYPE_FLOAT3;
  case 4u:
    return D3DDECLTYPE_FLOAT4;
  }

  throw sge::renderer::exception(
      FCPPT_TEXT("vf::pos, vf::extra or vf::texpos sizes of > 4 are not supported!"));
}
