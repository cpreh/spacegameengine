//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SPRITE_OBJECT_IMPL_HPP_INCLUDED

#include <sge/sprite/color.hpp> // IWYU pragma: keep
#include <sge/sprite/object_decl.hpp> // IWYU pragma: export
#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/config/is_normal_size.hpp>
#include <sge/sprite/detail/assign_post.hpp>
#include <sge/sprite/detail/assign_pre.hpp>
#include <sge/sprite/detail/destroy.hpp>
#include <sge/sprite/detail/get_center.hpp>
#include <sge/sprite/detail/get_pos.hpp>
#include <sge/sprite/detail/get_size.hpp>
#include <sge/sprite/detail/set_center.hpp>
#include <sge/sprite/detail/set_pos.hpp>
#include <sge/sprite/detail/set_size.hpp>
#include <sge/sprite/detail/unlink.hpp> // IWYU pragma: keep
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/depth.hpp>
#include <sge/sprite/roles/point_size.hpp>
#include <sge/sprite/roles/repetition.hpp>
#include <sge/sprite/roles/rotation.hpp>
#include <sge/sprite/roles/texture.hpp>
#include <sge/sprite/roles/texture_coordinates.hpp>
#include <sge/sprite/roles/texture_point_pos.hpp>
#include <sge/sprite/roles/texture_point_size.hpp>
#include <sge/sprite/types/center.hpp> // IWYU pragma: keep
#include <sge/sprite/types/pos.hpp> // IWYU pragma: keep
#include <sge/sprite/types/basic/dim_impl.hpp> // IWYU pragma: keep
#include <sge/sprite/types/basic/homogenous_pair_impl.hpp> // IWYU pragma: keep
#include <sge/sprite/types/basic/vector_impl.hpp> // IWYU pragma: keep
#include <fcppt/record/get.hpp>
#include <fcppt/record/label_value_type.hpp>
#include <fcppt/record/set.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename Choices>
template <typename... Args, typename>
sge::sprite::object<Choices>::object(Args &&..._args) : elements_{std::forward<Args>(_args)...}
{
  sge::sprite::detail::assign_post(*this);
}

template <typename Choices>
sge::sprite::object<Choices>::object(object const &_other) : elements_(_other.elements_)
{
  sge::sprite::detail::assign_post(*this);
}

template <typename Choices>
sge::sprite::object<Choices>::object(object &&_other) noexcept
    : elements_(std::move(_other.elements_))
{
  sge::sprite::detail::assign_post(*this);
}

template <typename Choices>
sge::sprite::object<Choices> &sge::sprite::object<Choices>::operator=(object const &_other)
{
  if (this == &_other)
  {
    return *this;
  }

  sge::sprite::detail::assign_pre(*this, _other);

  elements_ = _other.elements_;

  sge::sprite::detail::assign_post(*this);

  return *this;
}

template <typename Choices>
sge::sprite::object<Choices> &sge::sprite::object<Choices>::operator=(object &&_other) noexcept
{
  sge::sprite::detail::assign_pre(*this, _other);

  elements_ = std::move(_other.elements_);

  sge::sprite::detail::assign_post(*this);

  return *this;
}

namespace sge::sprite
{
template <typename Choices>
object<Choices>::~object()
{
  sge::sprite::detail::destroy(*this);
}
}

template <typename Choices>
typename sge::sprite::object<Choices>::unit sge::sprite::object<Choices>::x() const
{
  return this->pos().x();
}

template <typename Choices>
typename sge::sprite::object<Choices>::unit sge::sprite::object<Choices>::y() const
{
  return this->pos().y();
}

template <typename Choices>
typename sge::sprite::object<Choices>::vector sge::sprite::object<Choices>::pos() const
{
  return sge::sprite::detail::get_pos<Choices>(this->elements_);
}

template <typename Choices>
typename sge::sprite::object<Choices>::vector sge::sprite::object<Choices>::center() const
{
  return sge::sprite::detail::get_center<Choices>(this->elements_);
}

template <typename Choices>
typename sge::sprite::object<Choices>::unit sge::sprite::object<Choices>::w() const
{
  return this->size().w();
}

template <typename Choices>
typename sge::sprite::object<Choices>::unit sge::sprite::object<Choices>::h() const
{
  return this->size().h();
}

template <typename Choices>
typename sge::sprite::object<Choices>::dim sge::sprite::object<Choices>::size() const
{
  static_assert(
      sge::sprite::config::is_normal_size<typename Choices::size_choice>::value,
      "This can only be used with config::normal_size");

  return sge::sprite::detail::get_size<Choices>(this->elements_);
}

template <typename Choices>
typename sge::sprite::object<Choices>::point_size_type
sge::sprite::object<Choices>::point_size() const
{
  return this->get<sge::sprite::roles::point_size>();
}

template <typename Choices>
typename sge::sprite::object<Choices>::texture_point_pos_type
sge::sprite::object<Choices>::texture_point_pos() const
{
  return this->texture_point_pos_level<0>();
}

template <typename Choices>
template <sge::sprite::texture_level Level>
typename sge::sprite::object<Choices>::texture_point_pos_type
sge::sprite::object<Choices>::texture_point_pos_level() const
{
  return this->get<sge::sprite::roles::texture_point_pos<Level>>();
}

template <typename Choices>
typename sge::sprite::object<Choices>::texture_point_size_type
sge::sprite::object<Choices>::texture_point_size() const
{
  return this->texture_point_size_level<0>();
}

template <typename Choices>
template <sge::sprite::texture_level Level>
typename sge::sprite::object<Choices>::texture_point_size_type
sge::sprite::object<Choices>::texture_point_size_level() const
{
  return this->get<sge::sprite::roles::texture_point_size<Level>>();
}

template <typename Choices>
typename sge::sprite::object<Choices>::depth_type sge::sprite::object<Choices>::z() const
{
  return this->get<sge::sprite::roles::depth>();
}

template <typename Choices>
typename sge::sprite::object<Choices>::rotation_type sge::sprite::object<Choices>::rotation() const
{
  return this->get<sge::sprite::roles::rotation>();
}

template <typename Choices>
typename sge::sprite::object<Choices>::repetition_type
sge::sprite::object<Choices>::repetition() const
{
  return this->get<sge::sprite::roles::repetition>();
}

template <typename Choices>
typename sge::sprite::object<Choices>::texture_coordinates_type
sge::sprite::object<Choices>::texture_coordinates() const
{
  return this->texture_coordinates_level<0>();
}

template <typename Choices>
template <sge::sprite::texture_level Level>
typename sge::sprite::object<Choices>::texture_coordinates_type
sge::sprite::object<Choices>::texture_coordinates_level() const
{
  return this->get<sge::sprite::roles::texture_coordinates<Level>>();
}

template <typename Choices>
typename sge::sprite::object<Choices>::color_type sge::sprite::object<Choices>::color() const
{
  return this->get<sge::sprite::roles::color>();
}

template <typename Choices>
typename sge::sprite::object<Choices>::texture_type sge::sprite::object<Choices>::texture() const
{
  return this->texture_level<0>();
}

template <typename Choices>
template <sge::sprite::texture_level Level>
typename sge::sprite::object<Choices>::texture_type const &
sge::sprite::object<Choices>::texture_level() const
{
  return this->get<sge::sprite::roles::texture<Level>>();
}

template <typename Choices>
void sge::sprite::object<Choices>::x(unit const _x)
{
  this->pos(vector(_x, this->y()));
}

template <typename Choices>
void sge::sprite::object<Choices>::y(unit const _y)
{
  this->pos(vector(this->x(), _y));
}

template <typename Choices>
void sge::sprite::object<Choices>::z(depth_type const _depth)
{
  this->set<sge::sprite::roles::depth>(_depth);
}

template <typename Choices>
void sge::sprite::object<Choices>::pos(vector const _pos)
{
  sge::sprite::detail::set_pos<Choices>(this->elements_, pos_type(_pos));
}

template <typename Choices>
void sge::sprite::object<Choices>::center(vector const _center)
{
  sge::sprite::detail::set_center<Choices>(this->elements_, center_type(_center));
}

template <typename Choices>
void sge::sprite::object<Choices>::w(unit const _w)
{
  this->size(dim(_w, this->h()));
}

template <typename Choices>
void sge::sprite::object<Choices>::h(unit const _h)
{
  this->size(dim(this->w(), _h));
}

template <typename Choices>
void sge::sprite::object<Choices>::size(dim const _dim)
{
  sge::sprite::detail::set_size<Choices>(this->elements_, _dim);
}

template <typename Choices>
void sge::sprite::object<Choices>::point_size(point_size_type const _point_size)
{
  this->set<sge::sprite::roles::point_size>(_point_size);
}

template <typename Choices>
void sge::sprite::object<Choices>::texture_point_pos(texture_point_pos_type const _point_pos)
{
  this->texture_point_pos_level<0>(_point_pos);
}

template <typename Choices>
template <sge::sprite::texture_level Level>
void sge::sprite::object<Choices>::texture_point_pos_level(texture_point_pos_type const _point_pos)
{
  this->set<sge::sprite::roles::texture_point_pos<Level>>(_point_pos);
}

template <typename Choices>
void sge::sprite::object<Choices>::texture_point_size(texture_point_size_type const _point_size)
{
  this->texture_point_size_level<0>(_point_size);
}

template <typename Choices>
template <sge::sprite::texture_level Level>
void sge::sprite::object<Choices>::texture_point_size_level(
    texture_point_size_type const _point_size)
{
  this->set<sge::sprite::roles::texture_point_size<Level>>(_point_size);
}

template <typename Choices>
void sge::sprite::object<Choices>::texture(texture_type const _texture)
{
  this->texture_level<0>(_texture);
}

template <typename Choices>
template <sge::sprite::texture_level Level>
void sge::sprite::object<Choices>::texture_level(texture_type const _texture)
{
  this->set<sge::sprite::roles::texture<Level>>(_texture);
}

template <typename Choices>
void sge::sprite::object<Choices>::rotation(rotation_type const _rotation)
{
  this->set<sge::sprite::roles::rotation>(_rotation);
}

template <typename Choices>
void sge::sprite::object<Choices>::repeat(repetition_type const _repeat)
{
  this->set<sge::sprite::roles::repetition>(_repeat);
}

template <typename Choices>
void sge::sprite::object<Choices>::texture_coordinates(texture_coordinates_type const &_coordinates)
{
  this->texture_coordinates_level<0>(_coordinates);
}

template <typename Choices>
template <sge::sprite::texture_level Level>
void sge::sprite::object<Choices>::texture_coordinates_level(
    texture_coordinates_type const &_coordinates)
{
  this->set<sge::sprite::roles::texture_coordinates<Level>>(_coordinates);
}

template <typename Choices>
void sge::sprite::object<Choices>::color(color_type const &_color)
{
  this->set<sge::sprite::roles::color>(_color);
}

template <typename Choices>
template <typename Role>
inline fcppt::record::
    label_value_type<typename sge::sprite::object<Choices>::element_type, Role> const &
    sge::sprite::object<Choices>::get() const
{
  return fcppt::record::get<Role>(this->elements_);
}

template <typename Choices>
template <typename Role>
inline void
sge::sprite::object<Choices>::set(fcppt::record::label_value_type<element_type, Role> const &_value)
{
  fcppt::record::set<Role>(this->elements_, _value);
}

#endif
