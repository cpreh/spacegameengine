//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gui/impl/renderer/scoped.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/gui/renderer/base_unique_ptr.hpp>
#include <sge/gui/renderer/create_scoped.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::gui::renderer::base_unique_ptr
sge::gui::renderer::create_scoped(
	sge::renderer::device::ffp_ref const _renderer,
	sge::renderer::context::ffp_ref const _context
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::gui::renderer::base
		>(
			fcppt::make_unique_ptr<
				sge::gui::impl::renderer::scoped
			>(
				_renderer,
				_context
			)
		);
}
