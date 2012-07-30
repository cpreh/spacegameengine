#include <sge/graph/object.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/graph/scalar.hpp>
#include <sge/renderer/device.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <sge/texture/part_raw_ref.hpp>

sge::graph::object::object(
	sge::renderer::dim2 &_dim,
	sge::renderer::device &_renderer
)
:
texture_(
	_renderer.create_planar_texture(
		sge::renderer::texture::planar_parameters(
			_dim,
			sge::image::color::format::l8,
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::capabilities_field(
				sge::renderer::texture::capabilities::render_target
			)
		)
	)
),
sprite_object_(
	sprite_parameters()
	.pos(
		sprite_object::vector::null()
	)
	.texture(
		fcppt::make_shared_ptr<
			sge::texture::part_raw_ref
		>(
			fcppt::ref(
				*texture_
			)
		)
	)
	.texture_size()
),
sprite_buffers_(
	_renderer,
	sge::sprite::buffers::option::dynamic
)
{

}

void
sge::graph::object::push(
	sge::graph::scalar _datum)
{
}

void
sge::graph::object::render(
	sge::renderer::context::object &_context)
{
	sge::sprite::process::one(
		_context,
		sprite_object_,
		sprite_buffers_
	);
}

sge::graph::object::~object()
{
}
