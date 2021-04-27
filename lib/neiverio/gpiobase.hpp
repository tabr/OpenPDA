//*****************************************************************************
//
// Author		: Konstantin Chizhov
// Date			: 2010
// All rights reserved.

// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
// Redistributions of source code must retain the above copyright notice, 
// this list of conditions and the following disclaimer.

// Redistributions in binary form must reproduce the above copyright notice, 
// this list of conditions and the following disclaimer in the documentation and/or 
// other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//*****************************************************************************
#ifndef GPIOBASE_HPP_
#define GPIOBASE_HPP_

#ifndef NEIVERIO_HPP_
    #error "Do not include this file directly. Use #include\"neiverio.hpp\" instead!"
#endif

#include <stdint.h>

namespace IO
{
    namespace Private
    {    
    	template<uint32_t x>
    	class PopulatedBits
    	{
    		static const uint32_t x1 = (x & 0x55555555) + ((x >> 1) & 0x55555555);
    		static const uint32_t x2 = (x1 & 0x33333333) + ((x1 >> 2) & 0x33333333);
    		static const uint32_t x3 = (x2 & 0x0f0f0f0f) + ((x2 >> 4) & 0x0f0f0f0f);
    		static const uint32_t x4 = (x3 & 0x00ff00ff) + ((x3 >> 8) & 0x00ff00ff);
    	public:
    		static const uint32_t value = (x4 & 0x0000ffff) + ((x4 >> 16) & 0x0000ffff);
    	};

        struct GpioBase
    	{
        private:
    		GpioBase(); //Private ctor        
    	};
    }//namespace Private
}
#endif
