//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/core.hpp>
#include <sge/d3d9/system.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/renderer/core.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/system_unique_ptr.hpp>
#include <sge/renderer/caps/system.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/name.hpp>


sge::d3d9::core::core(
	fcppt::log::context &_log_context
)
:
	sge::renderer::core(),
	log_{
		_log_context,
		sge::log::location(),
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("d3d9")
			}
		)
	}
{
}

sge::d3d9::core::~core()
{
}

sge::renderer::system_unique_ptr
sge::d3d9::core::create_system(
	sge::window::system &
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::system
		>(
			fcppt::make_unique_ptr<
				sge::d3d9::system
			>(
				log_
			)
		);
}

sge::renderer::caps::system_field
sge::d3d9::core::caps() const
{
	return
		sge::renderer::caps::system_field{
			sge::renderer::caps::system::ffp
		};
}
