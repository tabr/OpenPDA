//*****************************************************************************
//
// Author		: Trotzky Vasily
// Date			: apr 2017
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
#ifndef IOCONF_SELECTOR_H_
#define IOCONF_SELECTOR_H_

#ifdef IOCONF_MCU_SPECIFIC_FILE
//	#if IOCONF_MCU_SPECIFIC == STM8S003F3P6
//        #include "IOCONF/stm8s003f3p6.h"
//    #endif

//#define INCLUDE_MCU_SPECIFIC(x) <IOCONF/x.h>
//#include INCLUDE_MCU_SPECIFIC(IOCONF_MCU_SPECIFIC)
#define STRINGIFY(x) #x
#define TOSTRING(a) STRINGIFY(IOCONF/a)
#include TOSTRING(IOCONF_MCU_SPECIFIC_FILE)

#else //#ifdef IOCONF_MCU_SPECIFIC_FILE
    #include "IOCONF_DefaultConf.h"
#endif

#endif//IOCONF_SELECTOR_H_
