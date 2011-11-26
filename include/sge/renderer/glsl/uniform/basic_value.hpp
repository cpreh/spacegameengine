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


#ifndef SGE_RENDERER_GLSL_UNIFORM_BASIC_VALUE_HPP_INCLUDED
#define SGE_RENDERER_GLSL_UNIFORM_BASIC_VALUE_HPP_INCLUDED

#include <sge/renderer/size_type.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/glsl/uniform/basic_value_fwd.hpp>
#include <fcppt/container/raw_vector_decl.hpp>


namespace sge
{
namespace renderer
{
namespace glsl
{
namespace uniform
{

/**
 * \brief A container for a uniform value
 *
 * Uniform values are arrays of glsl::int_type or renderer::scalar. These
 * arrays can be interpreted as vectors, matrices or even arrays of vectors or
 * matrices. For example, 16 float values could be a 4x4 float matrix, 4
 * vectors consisting of 4 floats each, or even 16 single float values.
 *
 * This class stores such a value. It has a raw data store, containing the int
 * or float elements, an enum which tells how the elements are to be
 * interpreted, and a size element that says how many individual elements there
 * are.
 *
 * \tparam Value The underlying element type
 * \tparam Type An enum type describing the type of the elements
*/
template<
	typename Value,
	typename Type
>
class basic_value
{
public:
	/**
	 * \brief The container used to store the values
	*/
	typedef fcppt::container::raw_vector<
		Value
	> data_type;

	/**
	 * \brief The value type
	*/
	typedef Value value_type;

	/**
	 * \brief The type of the individual elements
	*/
	typedef Type element_type;

	/**
	 * \brief A pointer to the store
	*/
	typedef typename data_type::pointer pointer;

	/**
	 * \brief A const pointer to the store
	*/
	typedef typename data_type::const_pointer const_pointer;

	/**
	 * \brief Constructs a uniform value
	 *
	 * Constructs the uniform value from \a store, containing \a elements
	 * of \a type.
	 *
	 * \param store The store to use
	 * \param elements The number of individual elements
	 * \param type The type of the elements
	 *
	 * \warning The behaviour is undefined if \a store doesn't contain
	 * exactly \a elements of type \a type
	*/
	SGE_RENDERER_SYMBOL
	basic_value(
		data_type const &store,
		renderer::size_type elements,
		Type type
	);

	/**
	 * \brief Returns a const pointer to the store
	*/
	SGE_RENDERER_SYMBOL
	const_pointer
	data() const;

	/**
	 * \brief Returns a pointer to the store
	*/
	SGE_RENDERER_SYMBOL
	pointer
	data();

	/**
	 * \brief Returns the number of individual elements
	*/
	SGE_RENDERER_SYMBOL
	renderer::size_type
	elements() const;

	/**
	 * \brief Returns the type of the elements
	*/
	SGE_RENDERER_SYMBOL
	Type
	type() const;
private:
	data_type data_;

	renderer::size_type elements_;

	Type type_;
};

}
}
}
}

#endif
