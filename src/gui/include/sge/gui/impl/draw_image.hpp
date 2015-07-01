#ifndef SGE_GUI_IMPL_DRAW_IMAGE_HPP_INCLUDED
#define SGE_GUI_IMPL_DRAW_IMAGE_HPP_INCLUDED

#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/texture/part_fwd.hpp>


namespace sge
{
namespace gui
{
namespace impl
{

void
draw_image(
	sge::renderer::device::ffp &,
	sge::renderer::context::ffp &,
	sge::texture::part const &,
	sge::rucksack::vector
);

}
}
}

#endif
