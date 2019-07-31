//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/blend/combined.hpp>
#include <sge/renderer/state/core/blend/dest.hpp>
#include <sge/renderer/state/core/blend/source.hpp>


sge::renderer::state::core::blend::combined::combined(
	sge::renderer::state::core::blend::source const _source,
	sge::renderer::state::core::blend::dest const _dest
)
:
	source_(
		_source
	),
	dest_(
		_dest
	)
{
}

sge::renderer::state::core::blend::source
sge::renderer::state::core::blend::combined::source() const
{
	return source_;
}

sge::renderer::state::core::blend::dest
sge::renderer::state::core::blend::combined::dest() const
{
	return dest_;
}
