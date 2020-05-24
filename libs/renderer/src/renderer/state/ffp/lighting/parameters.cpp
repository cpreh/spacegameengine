//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/lighting/parameters.hpp>
#include <sge/renderer/state/ffp/lighting/variant.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::renderer::state::ffp::lighting::parameters::parameters(
	sge::renderer::state::ffp::lighting::variant _variant
)
:
	variant_(
		std::move(
			_variant
		)
	)
{
}

sge::renderer::state::ffp::lighting::variant const &
sge::renderer::state::ffp::lighting::parameters::variant() const
{
	return
		variant_;
}
