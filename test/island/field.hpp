#ifndef FIELD_HPP_INCLUDED
#define FIELD_HPP_INCLUDED

#include <vector>
#include <algorithm>
#include "../../src/math/vector.hpp"
#include "../../src/math/dim.hpp"

template<typename T>
class field
{
	public:
	typedef unsigned                              coord_type;
	typedef sge::math::basic_vector<coord_type,2> coord_vector_type;
	typedef T                                     value_type;
	typedef sge::math::dim<unsigned,2>            dim_type;
	typedef std::vector<value_type>               array_type;
	typedef typename array_type::iterator         iterator;
	typedef typename array_type::const_iterator   const_iterator;

	private:
	dim_type   dim_;
	array_type array;

	public:
	field() {}
	field(const dim_type &dim) : dim_(dim) { array.resize(field_count()); }
	field(const dim_type::value_type &x,const dim_type::value_type &y) : dim_(x,y) { array.resize(field_count()); }

	iterator begin() { return array.begin(); }
	iterator end() { return array.end(); }

	const_iterator begin() const { return array.begin(); }
	const_iterator end() const { return array.end(); }

	void zero()
	{
		std::fill(begin(),end(),value_type(0));
	}

	void resize(const dim_type &n)
	{
		dim_ = n;
		array.resize(field_count());
	}

	value_type &pos(const coord_vector_type &p)
	{
		return array[p.y() * dim_.w() + p.x()];
	}

	value_type &pos(const coord_type &x,const coord_type &y)
	{
		return array[y * dim_.w() + x];
	}

	void blur()
	{
		for (coord_type y = 0; y < height(); ++y)
		{
			for (coord_type x = 0; x < width(); ++x)
			{
				unsigned adjacent = 9;
				value_type sum = pos(x,y);
				
				if (x != 0)
					sum += pos(x-1,y);
				else
					--adjacent;

				if (x < width()-1)
					sum += pos(x+1,y);
				else
					--adjacent;

				if (y != 0)
					sum += pos(x,y-1);
				else
					--adjacent;

				if (y < height()-1)
					sum += pos(x,y+1);
				else
					--adjacent;

				if (x != 0 && y != 0)
					sum += pos(x-1,y-1);
				else
					--adjacent;

				if (x < width()-1 && y != 0)
					sum += pos(x+1,y-1);
				else
					--adjacent;

				if (y < height()-1 && x != 0)
					sum += pos(x-1,y+1);
				else
					--adjacent;

				if (y < height()-1 && x < width()-1)
					sum += pos(x+1,y+1);
				else
					--adjacent;

				pos(x,y) = sum / value_type(adjacent);
			}
		}
	}

	void add_border(dim_type::value_type halfsize)
	{
		// Altes Array
		array_type old = array;
		// Neue Dimensionen
		dim_type new_dim(dim_.w()+2*halfsize,dim_.h()+2*halfsize);
		
		// Groesse andern, auf 0 setzen
		array.resize(new_dim.w()*new_dim.h());
		std::fill(array.begin(),array.end(),value_type(0));

		iterator i = array.begin() + 2 * halfsize * new_dim.w() + halfsize,j = old.begin();
		for (coord_type y = 0; y < height(); ++y)
		{
			std::copy(j,j+dim_.w(),i);
			i += new_dim.w();
			j += dim_.w();
		}

		dim_ = new_dim;
	}

	dim_type::value_type width() const { return dim_.w(); }
	dim_type::value_type height() const { return dim_.h(); }
	dim_type::value_type field_count() const { return dim_.w()*dim_.h(); }
	dim_type dim() const { return dim_; }
};
typedef field<sge::space_unit> space_field;

#endif
