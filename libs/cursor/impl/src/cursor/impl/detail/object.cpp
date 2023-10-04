//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cursor/hotspot.hpp>
#include <sge/cursor/impl/detail/object.hpp>
#include <sge/input/const_processor_ref.hpp>
#include <sge/input/processor.hpp> // NOLINT(misc-include-cleaner)
#include <sge/input/cursor/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/sprite/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single_impl.hpp> // NOLINT(misc-include-cleaner)
#include <sge/sprite/buffers/with_declaration_impl.hpp> // NOLINT(misc-include-cleaner)
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/process/all.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/state/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <sge/sprite/state/parameters_impl.hpp> // NOLINT(misc-include-cleaner)
#include <sge/texture/const_part_ref.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/to_signed.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

sge::cursor::detail::object::object(
    sge::input::const_processor_ref const _processor,
    sge::renderer::device::ffp_ref const _renderer,
    sge::texture::const_part_ref const _texture,
    sge::cursor::hotspot const _hotspot)
    : processor_{_processor},
      texture_{_texture},
      hotspot_{_hotspot},
      sprite_buffers_{
          fcppt::reference_to_base<sge::renderer::device::core>(_renderer),
          sge::sprite::buffers::option::dynamic},
      sprite_state_{_renderer, sprite_state_parameters()}
{
}

sge::cursor::detail::object::~object() = default;

void sge::cursor::detail::object::draw(sge::renderer::context::ffp &_context)
{
  using sprite_vector = std::vector<sprite_object>;

  auto sprites(fcppt::algorithm::map_optional<sprite_vector>(
      processor_.get().cursors(),
      [this](sge::input::cursor::shared_ptr const &_cursor)
      { return this->make_sprite(_cursor->position()); }));

  sge::sprite::process::all(
      _context,
      sge::sprite::geometry::make_random_access_range(sprites),
      sprite_buffers_,
      sge::sprite::compare::default_(),
      sprite_state_);
}

sge::cursor::hotspot sge::cursor::detail::object::hotspot() const { return hotspot_; }

sge::cursor::detail::object::optional_sprite sge::cursor::detail::object::make_sprite(
    sge::input::cursor::optional_position const &_opt_pos) const
{
  return fcppt::optional::map(
      _opt_pos,
      [this](sge::input::cursor::position const &_pos)
      {
        return sprite_object{
            sge::sprite::roles::pos{} =
                _pos - fcppt::math::vector::
                           structure_cast<sge::input::cursor::position, fcppt::cast::size_fun>(
                               fcppt::math::vector::to_signed(this->hotspot_.get())),
            sge::sprite::roles::texture0{} = this->texture_};
      });
}
