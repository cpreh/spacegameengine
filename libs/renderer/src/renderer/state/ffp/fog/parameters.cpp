//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/fog/parameters.hpp>
#include <sge/renderer/state/ffp/fog/variant.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::renderer::state::ffp::fog::parameters::parameters(
	sge::renderer::state::ffp::fog::variant _variant
)
:
	variant_(
		std::move(
			_variant
		)
	)
{
}

sge::renderer::state::ffp::fog::variant const &
sge::renderer::state::ffp::fog::parameters::variant() const
{
	return
		variant_;
}
