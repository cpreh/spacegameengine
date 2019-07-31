//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_TEXTURE_PARAMETERS_HPP_INCLUDED
#define SGE_CEGUI_IMPL_TEXTURE_PARAMETERS_HPP_INCLUDED

#include <sge/cegui/impl/prefix.hpp>
#include <sge/cegui/impl/texture_parameters_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace cegui
{
namespace impl
{

class texture_parameters
{
public:
	texture_parameters(
		sge::cegui::impl::prefix const &,
		sge::image2d::system &,
		sge::renderer::device::ffp &,
		sge::renderer::texture::emulate_srgb
	);

	sge::cegui::impl::prefix const &
	prefix() const;

	sge::image2d::system &
	image_system() const;

	sge::renderer::device::ffp &
	renderer() const;

	sge::renderer::texture::emulate_srgb
	emulate_srgb() const;
private:
	sge::cegui::impl::prefix prefix_;

	fcppt::reference<
		sge::image2d::system
	> image_system_;

	fcppt::reference<
		sge::renderer::device::ffp
	> renderer_;

	sge::renderer::texture::emulate_srgb emulate_srgb_;
};

}
}
}

#endif
