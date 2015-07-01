#include <sge/gui/impl/draw_image_repeat.hpp>
#include <sge/gui/impl/draw_sprite.hpp>
#include <sge/gui/impl/image_sprite_choices.hpp>
#include <sge/gui/impl/sprite_type_choices.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/repetition.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/types/repetition.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


void
sge::gui::impl::draw_image_repeat(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sge::texture::part const &_texture,
	sge::rucksack::rect const _rect
)
{
	typedef
	sge::sprite::types::repetition<
		sge::gui::impl::sprite_type_choices
	>
	repetition_type;

	sge::gui::impl::draw_sprite(
		_renderer,
		_context,
		sge::sprite::object<
			sge::gui::impl::image_sprite_choices<
				sge::sprite::config::texture_coordinates::repetition,
				sge::sprite::config::texture_size_option::never
			>
		>(
			sge::sprite::roles::pos{} =
				_rect.pos(),
			sge::sprite::roles::texture0{} =
				sge::texture::const_optional_part_ref(
					_texture
				),
			sge::sprite::roles::repetition{} =
				fcppt::math::vector::structure_cast<
					repetition_type,
					fcppt::cast::int_to_float_fun
				>(
					fcppt::math::dim::to_vector(
						_rect.size()
					)
				)
				/
				fcppt::math::vector::structure_cast<
					repetition_type,
					fcppt::cast::int_to_float_fun
				>(
					fcppt::math::dim::to_vector(
						_texture.size()
					)
				),
			sge::sprite::roles::size{} =
				_rect.size()
		)
	);
}
