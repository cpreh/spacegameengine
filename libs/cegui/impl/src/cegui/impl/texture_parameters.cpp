//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/impl/prefix.hpp>
#include <sge/cegui/impl/texture_parameters.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::cegui::impl::texture_parameters::texture_parameters(
	sge::cegui::impl::prefix &&_prefix,
	sge::image2d::system_ref const _image_system,
	sge::renderer::device::ffp_ref const _renderer,
	sge::renderer::texture::emulate_srgb const _emulate_srgb
)
:
	prefix_(
		std::move(
			_prefix
		)
	),
	image_system_(
		_image_system
	),
	renderer_(
		_renderer
	),
	emulate_srgb_(
		_emulate_srgb
	)
{
}

sge::cegui::impl::prefix const &
sge::cegui::impl::texture_parameters::prefix() const
{
	return
		prefix_;
}

sge::image2d::system &
sge::cegui::impl::texture_parameters::image_system() const
{
	return
		image_system_.get();
}

sge::renderer::device::ffp &
sge::cegui::impl::texture_parameters::renderer() const
{
	return
		renderer_.get();
}

sge::renderer::texture::emulate_srgb
sge::cegui::impl::texture_parameters::emulate_srgb() const
{
	return
		emulate_srgb_;
}
