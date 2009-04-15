#include <sge/gui/default_cursor.hpp>
#include <sge/renderer/device.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/object.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/structure_cast.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/text.hpp>
#include <sge/media.hpp>

sge::gui::default_cursor::default_cursor(
	sge::image::loader_ptr const il,
	sge::renderer::device_ptr const rend)
:
	sprite_(
		sge::sprite::parameters()
			.texture(
				texture::const_part_ptr(
					make_shared_ptr<
						texture::no_fragmented
					>(
						rend->create_texture(
						il->load(
							media_path()/SGE_TEXT("gui")/SGE_TEXT("cursor.png"))->view(),
						renderer::filter::linear,
						renderer::resource_flags::readable))))
			.size(
				sprite::texture_dim)
			.depth(
				static_cast<sprite::depth_type>(0))),
	click_(16,16)
{
}

void sge::gui::default_cursor::pos(
	point const &p)
{
	sprite_.pos() = sge::structure_cast<sge::sprite::point>(
		p);
}

sge::gui::point const sge::gui::default_cursor::pos() const
{
	return sge::structure_cast<sge::gui::point>(
		sprite_.pos());
}

sge::sprite::object const sge::gui::default_cursor::sprite() const
{
	return sprite_;
}

sge::sprite::object &sge::gui::default_cursor::mutable_sprite()
{
	return sprite_;
}

sge::gui::default_cursor::~default_cursor() {}
