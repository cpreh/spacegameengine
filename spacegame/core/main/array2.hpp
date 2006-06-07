#ifndef SGE_ARRAY2_HPP_INCLUDED
#define SGE_ARRAY2_HPP_INCLUDED

#include <ostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include "../math/rect.hpp"

namespace sge
{
	template<typename Impl> class array2 {
	public:
		typedef Impl impl_type;

		typedef typename impl_type::value_type value_type;
		typedef typename impl_type::allocator_type allocator_type;

		typedef typename impl_type::size_type size_type;
		typedef typename impl_type::difference_type difference_type;

		typedef typename impl_type::iterator iterator;
		typedef typename impl_type::const_iterator const_iterator;

		typedef typename impl_type::reverse_iterator reverse_iterator;
		typedef typename impl_type::reverse_iterator const_reverse_iterator;

		typedef typename impl_type::pointer pointer;
		typedef typename impl_type::const_pointer const_pointer;
			
		typedef typename impl_type::reference reference;
		typedef typename impl_type::const_reference const_reference;

		typedef basic_rect<size_type> rect;
private:
		template<typename Iterator, typename Reference> class proxy_impl {
		public:
			Reference operator[](size_type y) const { return *(it + y*dx + x); }
			Reference at(size_type y) const
			{
				if(y > my)
					throw std::range_error("array2: y out of range!");
				return (*this)[y];
			}
		private:
			friend class array2;
			proxy_impl(Iterator it, size_type x, size_type dx, size_type my)
				: it(it), x(x), dx(dx), my(my) {}

			Iterator it;
			size_type x, dx, my;
		};

		typedef proxy_impl<iterator,reference> proxy;
		typedef proxy_impl<const_iterator,const_reference> const_proxy;
public:
		array2(size_type x = 0, size_type y = 0, const allocator_type& a = allocator_type())
			: impl(x*y,a), sx(x), sy(y) {}

		array2(size_type x, size_type y, const value_type& t, const allocator_type& a = allocator_type())
			: impl(x*y,t,a), sx(x), sy(y) {}

		void assign(const value_type& value)
		{
			impl.assign(impl.size(),value);
		}

		iterator begin() { return impl.begin(); }
		const_iterator begin() const  { return impl.begin(); }
		iterator end()  { return impl.end(); }
		const_iterator end() const  { return impl.end(); }

		reverse_iterator rbegin()  { return impl.rbegin(); }
		const_reverse_iterator rbegin() const  { return impl.rbegin(); }
		reverse_iterator rend()  { return impl.rend(); }
		const reverse_iterator rend() const  { return impl.rend(); }

		proxy operator[](size_type x) { return proxy(begin(),x,width(),height()); }
		const_proxy operator[](size_type x) const { return const_proxy(begin(),x,width(),height()); }
		proxy at(size_type x) { range_check(x); return (*this)[x]; }
		const_proxy at(size_type x) const { range_check(x); return (*this)[x]; }

		size_type size() const { return impl.size(); }
		size_type width() const { return sx; }
		size_type height() const { return sy; }
		size_type xdim() const { return width(); }
		size_type ydim() const { return height(); }

		bool empty() const { return impl.empty(); }
		size_type max_size() const { return impl.max_size(); }

		void swap(array2& x)
		{
			impl.swap(x.impl);
			std::swap(sx,x.sx);
			std::swap(sy,x.sy);
		}
		allocator_type get_allocator() const { return impl.get_allocator(); }

		pointer data() { return impl.data(); }
		const_pointer data() const { return impl.data(); }

		bool operator==(const array2& r) const
		{
			return sx == r.sx && sy == r.sy && impl == r.impl;
		}

		void assign_rect(const rect& r, const value_type& t)
		{
			for(size_type y = r.top; y < r.bottom; ++y)
				for(size_type x = r.left; x < r.right; ++x)
					(*this)[x][y] = t;
		}
	private:
		impl_type impl;
		size_type sx, sy;

		void range_check(size_type x) const
		{
			if(x >= width())
				throw std::runtime_error("array2: x out of range!");
		}
	};

	template<typename Impl> inline bool operator!=(const array2<Impl>& l, const array2<Impl>& r)
	{
		return !(l == r);
	}
}

#endif
