//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/exception.hpp>
#include <sge/font/bitmap/impl/load_rect.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/member_map.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>

sge::image2d::rect sge::font::bitmap::impl::load_rect(sge::parse::json::member_map const &_members)
{
  sge::parse::json::element_vector const &elements(
      sge::parse::json::find_member_exn<sge::parse::json::array>(fcppt::make_cref(_members), "rect")
          .get()
          .elements);

  // TODO(philipp): array::from_container
  if (elements.size() != 2)
  {
    throw sge::font::exception(FCPPT_TEXT("Bogus rect detected"));
  }

  sge::parse::json::element_vector const &first_elements(
      sge::parse::json::get_exn<sge::parse::json::array>(fcppt::make_cref(elements[0].get()))
          .get()
          .elements);

  sge::parse::json::element_vector const &second_elements(
      sge::parse::json::get_exn<sge::parse::json::array>(fcppt::make_cref(elements[1].get()))
          .get()
          .elements);

  if (first_elements.size() != 2 || second_elements.size() != 2)
  {
    throw sge::font::exception(FCPPT_TEXT("Bogus rect subelements detected"));
  }

  return sge::image2d::rect(
      sge::image2d::rect::vector(
          static_cast<sge::image2d::rect::value_type>(
              sge::parse::json::get_exn<sge::parse::json::int_type>(
                  fcppt::make_cref(first_elements[0].get()))
                  .get()),
          static_cast<sge::image2d::rect::value_type>(
              sge::parse::json::get_exn<sge::parse::json::int_type>(
                  fcppt::make_cref(first_elements[1].get()))
                  .get())),
      sge::image2d::rect::dim(
          static_cast<sge::image2d::rect::value_type>(
              sge::parse::json::get_exn<sge::parse::json::int_type>(
                  fcppt::make_cref(second_elements[0].get()))
                  .get()),
          static_cast<sge::image2d::rect::value_type>(
              sge::parse::json::get_exn<sge::parse::json::int_type>(
                  fcppt::make_cref(second_elements[1].get()))
                  .get())));
}
