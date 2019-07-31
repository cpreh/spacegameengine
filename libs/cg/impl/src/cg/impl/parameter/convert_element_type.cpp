//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/impl/parameter/convert_element_type.hpp>
#include <sge/cg/parameter/element_type.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


CGtype
sge::cg::impl::parameter::convert_element_type(
	sge::cg::parameter::element_type const _type
)
{
	switch(
		_type
	)
	{
	case sge::cg::parameter::element_type::double_:
		return CG_DOUBLE;
	case sge::cg::parameter::element_type::double1:
		return CG_DOUBLE1;
	case sge::cg::parameter::element_type::double2:
		return CG_DOUBLE2;
	case sge::cg::parameter::element_type::double3:
		return CG_DOUBLE3;
	case sge::cg::parameter::element_type::double4:
		return CG_DOUBLE4;
	case sge::cg::parameter::element_type::double1x1:
		return CG_DOUBLE1x1;
	case sge::cg::parameter::element_type::double1x2:
		return CG_DOUBLE1x2;
	case sge::cg::parameter::element_type::double1x3:
		return CG_DOUBLE1x3;
	case sge::cg::parameter::element_type::double1x4:
		return CG_DOUBLE1x4;
	case sge::cg::parameter::element_type::double2x1:
		return CG_DOUBLE2x1;
	case sge::cg::parameter::element_type::double2x2:
		return CG_DOUBLE2x2;
	case sge::cg::parameter::element_type::double2x3:
		return CG_DOUBLE2x3;
	case sge::cg::parameter::element_type::double2x4:
		return CG_DOUBLE2x4;
	case sge::cg::parameter::element_type::double3x1:
		return CG_DOUBLE3x1;
	case sge::cg::parameter::element_type::double3x2:
		return CG_DOUBLE3x2;
	case sge::cg::parameter::element_type::double3x3:
		return CG_DOUBLE3x3;
	case sge::cg::parameter::element_type::double3x4:
		return CG_DOUBLE3x4;
	case sge::cg::parameter::element_type::double4x1:
		return CG_DOUBLE4x1;
	case sge::cg::parameter::element_type::double4x2:
		return CG_DOUBLE4x2;
	case sge::cg::parameter::element_type::double4x3:
		return CG_DOUBLE4x3;
	case sge::cg::parameter::element_type::double4x4:
		return CG_DOUBLE4x4;

	case sge::cg::parameter::element_type::float_:
		return CG_FLOAT;
	case sge::cg::parameter::element_type::float1:
		return CG_FLOAT1;
	case sge::cg::parameter::element_type::float2:
		return CG_FLOAT2;
	case sge::cg::parameter::element_type::float3:
		return CG_FLOAT3;
	case sge::cg::parameter::element_type::float4:
		return CG_FLOAT4;
	case sge::cg::parameter::element_type::float1x1:
		return CG_FLOAT1x1;
	case sge::cg::parameter::element_type::float1x2:
		return CG_FLOAT1x2;
	case sge::cg::parameter::element_type::float1x3:
		return CG_FLOAT1x3;
	case sge::cg::parameter::element_type::float1x4:
		return CG_FLOAT1x4;
	case sge::cg::parameter::element_type::float2x1:
		return CG_FLOAT2x1;
	case sge::cg::parameter::element_type::float2x2:
		return CG_FLOAT2x2;
	case sge::cg::parameter::element_type::float2x3:
		return CG_FLOAT2x3;
	case sge::cg::parameter::element_type::float2x4:
		return CG_FLOAT2x4;
	case sge::cg::parameter::element_type::float3x1:
		return CG_FLOAT3x1;
	case sge::cg::parameter::element_type::float3x2:
		return CG_FLOAT3x2;
	case sge::cg::parameter::element_type::float3x3:
		return CG_FLOAT3x3;
	case sge::cg::parameter::element_type::float3x4:
		return CG_FLOAT3x4;
	case sge::cg::parameter::element_type::float4x1:
		return CG_FLOAT4x1;
	case sge::cg::parameter::element_type::float4x2:
		return CG_FLOAT4x2;
	case sge::cg::parameter::element_type::float4x3:
		return CG_FLOAT4x3;
	case sge::cg::parameter::element_type::float4x4:
		return CG_FLOAT4x4;

	case sge::cg::parameter::element_type::int_:
		return CG_INT;
	case sge::cg::parameter::element_type::int1:
		return CG_INT1;
	case sge::cg::parameter::element_type::int2:
		return CG_INT2;
	case sge::cg::parameter::element_type::int3:
		return CG_INT3;
	case sge::cg::parameter::element_type::int4:
		return CG_INT4;
	case sge::cg::parameter::element_type::int1x1:
		return CG_INT1x1;
	case sge::cg::parameter::element_type::int1x2:
		return CG_INT1x2;
	case sge::cg::parameter::element_type::int1x3:
		return CG_INT1x3;
	case sge::cg::parameter::element_type::int1x4:
		return CG_INT1x4;
	case sge::cg::parameter::element_type::int2x1:
		return CG_INT2x1;
	case sge::cg::parameter::element_type::int2x2:
		return CG_INT2x2;
	case sge::cg::parameter::element_type::int2x3:
		return CG_INT2x3;
	case sge::cg::parameter::element_type::int2x4:
		return CG_INT2x4;
	case sge::cg::parameter::element_type::int3x1:
		return CG_INT3x1;
	case sge::cg::parameter::element_type::int3x2:
		return CG_INT3x2;
	case sge::cg::parameter::element_type::int3x3:
		return CG_INT3x3;
	case sge::cg::parameter::element_type::int3x4:
		return CG_INT3x4;
	case sge::cg::parameter::element_type::int4x1:
		return CG_INT4x1;
	case sge::cg::parameter::element_type::int4x2:
		return CG_INT4x2;
	case sge::cg::parameter::element_type::int4x3:
		return CG_INT4x3;
	case sge::cg::parameter::element_type::int4x4:
		return CG_INT4x4;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
