#ifndef SGE_DINPUT_KEY_CONVERTER_HPP_INCLUDED
#define SGE_DINPUT_KEY_CONVERTER_HPP_INCLUDED

#include <vector>
#include <map>
#include "../../core/input/key_type.hpp"
#include "./di.hpp"

namespace sge
{
	namespace dinput
	{
		class key_converter {
		public:
			key_converter();
			key_code create_key_code(DWORD ofs) const;
			DWORD   create_dik(key_code key) const;
		private:
			std::vector<key_code> v;
			std::map<key_code, DWORD> vr;
		};
	}
}

#endif
