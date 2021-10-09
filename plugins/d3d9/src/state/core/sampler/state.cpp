//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/core/sampler/state.hpp>

sge::d3d9::state::core::sampler::state::state(D3DSAMPLERSTATETYPE const _type, DWORD const _value)
    : type_(_type), value_(_value)
{
}

D3DSAMPLERSTATETYPE
sge::d3d9::state::core::sampler::state::type() const { return type_; }

DWORD
sge::d3d9::state::core::sampler::state::value() const { return value_; }
