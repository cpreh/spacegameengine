//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_NOISE_SAMPLE_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_NOISE_SAMPLE_PARAMETERS_DECL_HPP_INCLUDED

#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sge::noise
{

template <typename Noise>
class sample_parameters
{
public:
  FCPPT_DECLARE_STRONG_TYPEDEF(typename Noise::vector_type, position_type);

  FCPPT_DECLARE_STRONG_TYPEDEF(typename Noise::value_type, amplitude_type);

  FCPPT_DECLARE_STRONG_TYPEDEF(typename Noise::value_type, frequency_type);

  FCPPT_DECLARE_STRONG_TYPEDEF(unsigned, octaves_type);

  sample_parameters(
      position_type, amplitude_type const &, frequency_type const &, octaves_type const &);

  [[nodiscard]] position_type position() const;

  [[nodiscard]] frequency_type frequency() const;

  [[nodiscard]] amplitude_type amplitude() const;

  [[nodiscard]] octaves_type octaves() const;

private:
  position_type position_;

  amplitude_type amplitude_;

  frequency_type frequency_;

  octaves_type octaves_;
};

}

#endif
