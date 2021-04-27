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
#ifndef IOREGWRAPPER_HPP_
#define IOREGWRAPPER_HPP_

#define IO_REG_WRAPPER(REG_NAME, CLASS_NAME, DATA_TYPE) \
	struct CLASS_NAME\
	{\
		typedef DATA_TYPE RegDataT;\
        static volatile RegDataT &GetReference(){ return REG_NAME; }\
		static RegDataT Get(){return REG_NAME;}\
		static void Set(RegDataT value){REG_NAME = value;}\
		static void Or(RegDataT value){REG_NAME |= value;}\
		static void And(RegDataT value){REG_NAME &= value;}\
		static void Xor(RegDataT value){REG_NAME ^= value;}\
		static void AndOr(RegDataT andMask, RegDataT orMask){REG_NAME = (REG_NAME & andMask) | orMask;}\
	}

#endif

