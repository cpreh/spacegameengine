#ifndef SGE_SMART_PTR_POLICIES_HPP_INCLUDED
#define SGE_SMART_PTR_POLICIES_HPP_INCLUDED

namespace sge
{
	template<typename T> struct heap_deleter {
		void delete_(T* t) { delete t; }
	protected:
		~heap_deleter(){}
	};

	template<typename T> struct heap_array_deleter {
		void delete_(T* t) { delete[] t; }
	protected:
		~heap_array_deleter(){}
	};

	template<typename T> struct com_deleter {
		void delete_(T* t) { t->Release(); }
	protected:
		~com_deleter(){}
	};
}

#endif
