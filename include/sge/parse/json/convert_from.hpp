/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_PARSE_JSON_CONVERT_FROM_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_FROM_HPP_INCLUDED

#include <sge/parse/json/detail/is_array.hpp>
#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/convert_from.hpp>
#include <fcppt/math/matrix/is_matrix.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/type_traits/is_iterable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/lexical_cast.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>

namespace sge
{
namespace parse
{
namespace json
{
// Begin forward declarations
template<typename T>
typename
boost::enable_if_c
<
	boost::is_floating_point<T>::value,
	T const
>::type
convert_from(
	sge::parse::json::value const &);

template<typename T>
typename
boost::enable_if_c
<
	boost::is_same<T,bool>::value,
	bool
>::type
convert_from(
	sge::parse::json::value const &);

template<typename T>
typename
boost::enable_if
<
	boost::mpl::and_
	<
		boost::is_integral<T>,
		boost::mpl::not_
		<
			boost::is_same<T,bool>
		>
	>,
	T const
>::type
convert_from(
	sge::parse::json::value const &);

template<typename T>
typename
boost::enable_if_c
<
	fcppt::math::matrix::is_matrix<T>::value,
	T const
>::type
convert_from(
	sge::parse::json::value const &);

template<typename T>
typename
boost::enable_if
<
	boost::mpl::and_
	<
		fcppt::type_traits::is_iterable<T>,
		boost::mpl::not_
		<
			detail::is_array<T>
		>,
		boost::mpl::not_
		<
			boost::is_same<T,fcppt::string>
		>,
		boost::mpl::not_
		<
			fcppt::math::matrix::is_matrix<T>
		>
	>,
	T const
>::type
convert_from(
	sge::parse::json::value const &);

template<typename T>
typename
boost::enable_if_c
<
	detail::is_array<T>::value,
	T const
>::type
convert_from(
	sge::parse::json::value const &);

template<typename T>
typename
boost::enable_if_c
<
	boost::is_same<T,fcppt::string>::value,
	T const
>::type
convert_from(
	sge::parse::json::value const &);

template<typename T>
typename
boost::enable_if_c
<
	boost::is_same<T,sge::parse::json::value>::value,
	sge::parse::json::value const
>::type
convert_from(
	sge::parse::json::value const &);

template<typename T>
typename
boost::enable_if
<
	boost::mpl::and_
	<
		boost::mpl::not_
		<
			boost::is_floating_point<T>
		>,
		boost::mpl::not_
		<
			boost::is_integral<T>
		>,
		boost::mpl::not_
		<
			fcppt::type_traits::is_iterable<T>
		>,
		boost::mpl::not_
		<
			boost::is_same<T,sge::parse::json::value>
		>
	>,
	T const
>::type
convert_from(
	sge::parse::json::value const &);
// End forward declarations
}
}
}

// Assume float_type
template<typename T>
typename
boost::enable_if_c
<
	boost::is_floating_point<T>::value,
	T const
>::type
sge::parse::json::convert_from(
	sge::parse::json::value const &v)
{
	return 
		static_cast<T>(
			sge::parse::json::get<sge::parse::json::float_type>(
				v));
}

// Assume bool
template<typename T>
typename
boost::enable_if_c
<
	boost::is_same<T,bool>::value,
	bool
>::type
sge::parse::json::convert_from(
	sge::parse::json::value const &v)
{
	return 
		sge::parse::json::get<bool>(v);
}

// Assume int_type
template<typename T>
typename
boost::enable_if
<
	boost::mpl::and_
	<
		boost::is_integral<T>,
		boost::mpl::not_
		<
			boost::is_same<T,bool>
		>
	>,
	T const
>::type
sge::parse::json::convert_from(
	sge::parse::json::value const &v)
{
	return 
		static_cast<T>(
			sge::parse::json::get<sge::parse::json::int_type>(
				v));
}

// Assume float_type
template<typename T>
typename
boost::enable_if_c
<
	fcppt::math::matrix::is_matrix<T>::value,
	T const
>::type
sge::parse::json::convert_from(
	sge::parse::json::value const &v)
{
	sge::parse::json::element_vector const 
		outer_array = 
			sge::parse::json::get<sge::parse::json::array>(
				v).elements,
		first_outer_vector = 
			sge::parse::json::get<sge::parse::json::array>(
				outer_array.front()).elements;

	T result(
		typename T::dim(
			static_cast<typename T::size_type>(
				outer_array.size()),
			static_cast<typename T::size_type>(
				first_outer_vector.size())));

	for(
		sge::parse::json::element_vector::size_type i = 0;
		i != outer_array.size();
		++i)
	{
		sge::parse::json::element_vector const current_inner_array = 
			sge::parse::json::get<sge::parse::json::array>(
				outer_array[i]).elements;

		if(current_inner_array.size() != first_outer_vector.size())
			throw 
				sge::parse::json::exception(
					FCPPT_TEXT("You tried to input a matrix, but the inner dimensions don't match!"));

		for(
			sge::parse::json::element_vector::size_type j = 0;
			j != current_inner_array.size();
			++j)
		{
			result[static_cast<typename T::size_type>(i)][static_cast<typename T::size_type>(j)] = 
				json::convert_from<typename T::value_type>(
					current_inner_array[j]);
		}
	}

	return result;
}


// Assume array_type (exception string)
// To be convertible, the type T needs to:
// - have begin/end
// - have value_type
// - have insert(iterator,value)
template<typename T>
typename
boost::enable_if
<
	boost::mpl::and_
	<
		fcppt::type_traits::is_iterable<T>,
		boost::mpl::not_
		<
			sge::parse::json::detail::is_array<T>
		>,
		boost::mpl::not_
		<
			boost::is_same<T,fcppt::string>
		>,
		boost::mpl::not_
		<
			fcppt::math::matrix::is_matrix<T>
		>
	>,
	T const
>::type
sge::parse::json::convert_from(
	sge::parse::json::value const &v)
{
	sge::parse::json::array const &a = 
		sge::parse::json::get<sge::parse::json::array>(
			v);

	T result;

	if(result.size() && result.size() != a.elements.size())
		throw 
			sge::parse::json::exception(
				FCPPT_TEXT("Tried to convert into an array, but the dimensions did not match. Target array has dimension ")+
				fcppt::lexical_cast<fcppt::string>(
					result.size())+
				FCPPT_TEXT(", source array has dimension ")+
				fcppt::lexical_cast<fcppt::string>(
					a.elements.size()));

	for(
		sge::parse::json::element_vector::const_iterator i = 
			a.elements.begin(); 
		i != a.elements.end(); 
		++i)
		result.insert(
			result.end(),
			json::convert_from<typename T::value_type>(
				*i));

	return result;
}

// Assume array
template<typename T>
typename
boost::enable_if_c
<
	sge::parse::json::detail::is_array<T>::value,
	T const
>::type
sge::parse::json::convert_from(
	sge::parse::json::value const &v)
{
	T result;

	sge::parse::json::array const &a = 
		sge::parse::json::get<sge::parse::json::array>(
			v);
	
	if(result.size() != a.elements.size())
		throw 
			sge::parse::json::exception(
				FCPPT_TEXT("Tried to convert into an array, but the dimensions did not match. Target array has dimension ")+
				fcppt::lexical_cast<fcppt::string>(
					result.size())+
				FCPPT_TEXT(", source array has dimension ")+
				fcppt::lexical_cast<fcppt::string>(
					a.elements.size()));

	typename T::iterator result_it = 
		result.begin();

	for(
		sge::parse::json::element_vector::const_iterator i = 
			a.elements.begin(); 
		i != a.elements.end(); 
		++i)
		*result_it++ = 
			json::convert_from<typename T::value_type>(
				*i);
	
	return result;
}

// This special case handles fcppt::string which would otherwise be
// seen as an array
template<typename T>
typename
boost::enable_if_c
<
	boost::is_same<T,fcppt::string>::value,
	T const
>::type
sge::parse::json::convert_from(
	sge::parse::json::value const &v)
{
	return 
		sge::parse::json::get<fcppt::string>(
			v);
}

// Assume...nothing. You cannot json::get for a json::value, hence
// this special case
template<typename T>
typename
boost::enable_if_c
<
	boost::is_same<T,sge::parse::json::value>::value,
	sge::parse::json::value const
>::type
sge::parse::json::convert_from(
	sge::parse::json::value const &v)
{
	return v;
}

// Everything else -> has to be a json type!
template<typename T>
typename
boost::enable_if
<
	boost::mpl::and_
	<
		boost::mpl::not_
		<
			boost::is_floating_point<T>
		>,
		boost::mpl::not_
		<
			boost::is_integral<T>
		>,
		boost::mpl::not_
		<
			fcppt::type_traits::is_iterable<T>
		>,
		boost::mpl::not_
		<
			boost::is_same<T,sge::parse::json::value>
		>
	>,
	T const
>::type
sge::parse::json::convert_from(
	sge::parse::json::value const &v)
{
	return 
		sge::parse::json::get<T>(
			v);
}

#endif
