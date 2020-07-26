//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/impl/image_codec.hpp>
#include <sge/cegui/impl/renderer.hpp>
#include <sge/cegui/impl/renderer_ref.hpp>
#include <sge/cegui/impl/resource_provider.hpp>
#include <sge/cegui/impl/scoped_system.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/System.h>
#include <fcppt/config/external_end.hpp>


sge::cegui::impl::scoped_system::scoped_system(
	sge::cegui::impl::renderer_ref const _renderer,
	fcppt::reference<
		sge::cegui::impl::image_codec
	> const _image_codec,
	fcppt::reference<
		sge::cegui::impl::resource_provider
	> const _resource_provider
)
{
	CEGUI::System::create(
		_renderer.get(),
		// Resource provider
		&_resource_provider.get(),
		// XML parser
		nullptr,
		&_image_codec.get(),
		// Script module,
		nullptr,
		// config file
		"",
		// log file
		"CEGUI.log"
	);
}

sge::cegui::impl::scoped_system::~scoped_system()
{
	CEGUI::System::destroy();
}
