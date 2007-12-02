#ifndef SGE_FIELD_HPP_INCLUDED
#define SGE_FIELD_HPP_INCLUDED

#include <cassert>
#include <algorithm>
#include <vector>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <boost/iterator/iterator_adaptor.hpp>
#include "math/vector.hpp"
#include "math/dim.hpp"

namespace sge
{

template<typename T,template<typename,typename>class ArrayType = std::vector,typename Alloc = std::allocator<T> >
class field
{
	public:
	typedef ArrayType<T,Alloc>                    array_type;

	// container requirements
	typedef T                                     value_type;
	typedef Alloc                                 allocator_type;
	typedef T&                                    reference;
	typedef const T&                              const_reference;
	typedef typename array_type::iterator         iterator;
	typedef typename array_type::const_iterator   const_iterator;
	typedef typename iterator::difference_type    difference_type;
	typedef typename array_type::size_type        size_type;
	typedef std::reverse_iterator<iterator>       reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	// this guarantees that dim_type::value_type, coord_type and size_type are the same so we save a few nagging conversions
	typedef size_type                             coord_type;
	typedef math::basic_vector<coord_type,2>      coord_vector_type;
	typedef math::basic_dim<coord_type,2>         dim_type;

	private:
	dim_type   dim_;
	array_type array;

	public:

	class position_iterator : public boost::iterator_adaptor<position_iterator,iterator,T,boost::bidirectional_traversal_tag>
	{
		public:
		position_iterator(iterator i,field &ref) : position_iterator::iterator_adaptor_(i),ref(ref) {}

		coord_type x() const { return ref.x(this->base()); }
		coord_type y() const { return ref.y(this->base()); }
		coord_vector_type pos() const { return ref.pos(this->base()); }

		private:
		friend class boost::iterator_core_access;
		field &ref;
	};

	// standard-ctor
	field(const allocator_type& alloc = allocator_type()) : array(alloc) {}
	// copy-ctor
	field(const field &r) : dim_(r.dim_),array(r.array) {}
	field(const dim_type &dim, const value_type& t = value_type(), const allocator_type& alloc = allocator_type()) : dim_(dim), array(alloc, field_count(), t) {}
	// same as above just without the dim type
	field(const coord_type &x,const coord_type &y, const allocator_type& alloc = allocator_type()) : dim_(x,y),array(alloc) { array.resize(field_count()); }

	template<typename Iterator>
	field(const coord_type &x,const coord_type &y,Iterator b,Iterator e,const allocator_type &alloc = allocator_type()) 
		: dim_(x,y),array(alloc) 
	{ 
		array.resize(field_count());
		std::copy(b,e,begin()); 
	}

	template<typename Iterator>
	field(const dim_type &dim_,Iterator b,Iterator e,const allocator_type &alloc = allocator_type()) 
		: dim_(dim_),array(alloc) 
	{ 
		array.resize(field_count());
		std::copy(b,e,begin()); 
	}

	// again, container requirements
	bool operator==(const field &r) const { return dim_ == r.dim_ && std::equal(begin(),end(),r.begin()); }
	bool operator!=(const field &r) const { return !(*this == *r); }
	void swap(field &r) { std::swap(dim_,r.dim_); array.swap(r.array); }
	field &operator=(const field &r) { if(&r != this) { dim_ = r.dim_; array = r.array; } return *this; }
	size_type size() const { return array.size();  }
	size_type max_size() const { return array.max_size(); }
	bool empty() const { return array.empty(); }
	iterator begin() { return array.begin(); }
	iterator end() { return array.end(); }
	const_iterator begin() const { return array.begin(); }
	const_iterator end() const { return array.end(); }
	reverse_iterator rbegin() { return array.rbegin(); }
	reverse_iterator rend() { return array.rend(); }
	const_reverse_iterator rbegin() const { return array.rbegin(); }
	const_reverse_iterator rend() const { return array.rend(); }
	position_iterator pbegin() { return position_iterator(array.begin(),*this); }
	position_iterator pend() { return position_iterator(array.end(),*this); }

	allocator_type get_allocator() const { return array.get_allocator(); }

	void zero() { std::fill(begin(),end(),value_type(0)); }
	void resize(const coord_type &x,const coord_type &y, const_reference value = value_type()) { resize(dim_type(x,y), value); }
	void resize(const dim_type &n, const_reference value = value_type()) { if (dim_ == n) return; dim_ = n; array.resize(field_count(), value); }
	value_type &pos(const coord_type &x,const coord_type &y) { return array[y * dim_.w() + x]; }
	const value_type &pos(const coord_type &x,const coord_type &y) const { return array[y * dim_.w() + x]; }
	value_type &pos(const coord_vector_type &p) { return pos(p.x(),p.y()); }
	const value_type &pos(const coord_vector_type &p) const { return pos(p.x(),p.y()); }

	reference front() { return array.front(); }
	const_reference front() const { return array.front(); }
	reference back() { return array.back(); }
	const_reference back() const { return array.back(); }

	value_type x(const const_iterator &p) const { if (w() == 0) throw std::range_error("width is zero, cannot execute x()"); return std::distance(begin(),p) % w(); }
	value_type y(const const_iterator &p) const { if (w() == 0) throw std::range_error("width is zero, cannot execute y()"); return std::distance(begin(),p) / w(); }
	coord_vector_type pos(const const_iterator &p) const { if (w() == 0) throw std::range_error("width is zero, cannot execute pos()"); return coord_vector_type(x(p),y(p)); }

	void blur()
	{
		for (coord_type y = coord_type(0); y < h(); ++y)
		{
			for (coord_type x = coord_type(0); x < w(); ++x)
			{
				unsigned adjacent = 9;
				value_type sum = pos(x,y);
				
				if (x != coord_type(0))
					sum += pos(x-coord_type(1),y);
				else
					--adjacent;

				if (x < w()-coord_type(1))
					sum += pos(x+coord_type(1),y);
				else
					--adjacent;

				if (y != coord_type(0))
					sum += pos(x,y-coord_type(1));
				else
					--adjacent;

				if (y < h()-coord_type(1))
					sum += pos(x,y+coord_type(1));
				else
					--adjacent;

				if (x != coord_type(0) && y != coord_type(0))
					sum += pos(x-coord_type(1),y-coord_type(1));
				else
					--adjacent;

				if (x < w()-coord_type(1) && y != coord_type(0))
					sum += pos(x+coord_type(1),y-coord_type(1));
				else
					--adjacent;

				if (y < h()-coord_type(1) && x != coord_type(0))
					sum += pos(x-coord_type(1),y+coord_type(1));
				else
					--adjacent;

				if (y < h()-coord_type(1) && x < w()-coord_type(1))
					sum += pos(x+coord_type(1),y+coord_type(1));
				else
					--adjacent;

				pos(x,y) = sum / value_type(adjacent);
			}
		}
	}

	void add_border(const coord_type &halfsize)
	{
		if (halfsize == coord_type(0))
			return;

		// old array
		array_type old = array;
		// new dimension
		dim_type new_dim(dim_.w()+coord_type(2)*halfsize,dim_.h()+coord_type(2)*halfsize);
		
		// change size and set to zero. here, zero() cannot be used because this uses a different array size
		array.resize(new_dim.w()*new_dim.h());
		std::fill(array.begin(),array.end(),value_type(0));

		iterator i = array.begin() + halfsize * new_dim.w() + halfsize,j = old.begin();
		for (coord_type y = coord_type(0); y < new_dim.h()-coord_type(2)*halfsize; ++y)
		{
			std::copy(j,j+dim_.w(),i);
			i += new_dim.w();
			j += dim_.w();
		}

		dim_ = new_dim;
	}

	void crop(const coord_vector_type &start,const dim_type &new_dim)
	{
		if (w() == 0 && h() == 0)
			throw std::range_error("width and height are zero, cannot crop");

		// save old array
		array_type old = array;

		// check for invalid values
		if (start.x() + new_dim.w() > w() && start.y() + new_dim.h() > h() && new_dim.w() == coord_type(0) && new_dim.h() == coord_type(0))
			throw std::invalid_argument("invalid arguments to crop function");

		if (start == coord_vector_type(coord_type(0),coord_type(0)) && new_dim == dim_)
			return;

		array.resize(new_dim.w()*new_dim.h());
		const_iterator old_it = old.begin() + w()*start.y() + start.x();
		iterator new_it = array.begin();

		for (coord_type y = coord_type(0); y < new_dim.h(); ++y)
		{
			std::copy(old_it,old_it + new_dim.w(),new_it);
			new_it += new_dim.w();
			old_it += w();
		}

		dim_ = new_dim;
	}

	/*
	template<typename Interpolator>
	void resample(const dim_type &new_size)
	{
		// TODO: Das hier programmieren
		Interpolator interpolator;
	}
	*/

	coord_type w() const { return dim_.w(); }
	coord_type h() const { return dim_.h(); }
	coord_type field_count() const { return dim_.w()*dim_.h(); }
	dim_type dim() const { return dim_; }
};
typedef field<space_unit> space_field;
}

template<typename T,typename Ch,typename Traits>
std::basic_ostream<Ch,Traits> &operator<<(std::basic_ostream<Ch,Traits> &stream,const sge::field<T> &field)
{
	for (sge::space_field::size_type y = 0; y < field.h(); ++y)
	{
		for (sge::space_field::size_type x = 0; x < field.w(); ++x)
			stream << field.pos(x,y) << stream.widen(' ');
		stream << stream.widen('\n');
	}
	return stream;
}

#endif
