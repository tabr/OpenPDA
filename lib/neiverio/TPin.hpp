//*****************************************************************************
// Author		: Konstantin Chizhov
// Date			: 2010
// All rights reserved.
//
// Massively patched by Trotskiy Vasily
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
#ifndef TPIN_HPP_
#define TPIN_HPP_

#ifndef NEIVERIO_HPP_
    #error "Do not include this file directly. Use #include\"neiverio.hpp\" instead!"
#endif

#include <stdint.h>
#include "boost_static_assert.h"
#include "TPinExtensions.hpp"

namespace IO
{
    namespace Private
    {
    	template<class PORT, uint8_t PIN, class CONFIG_PORT = PORT>
    	class TPinImplementation
    	{                
    		BOOST_STATIC_ASSERT(PIN < PORT::Width);              	    	
            static const typename PORT::DataT MASK = (typename PORT::DataT)1U << PIN;
        public:    		            
            struct IOInternals //We need this to be public for pin lists implementation
            {
                typedef PORT Port;
                typedef typename PORT::DataT PortDataT;
    		    typedef CONFIG_PORT ConfigPort;
                static const bool Inverted = false;
    		    static const uint8_t PortPinNumber = PIN;
            };
            
    		static void Set(bool val)
    		{
    			if( val )
                    PORT::template Set<MASK>();
    			else
    				PORT::template Clear<MASK>();
    		}
    		static void Set(){ Set(true); }
    		static void Clear(){ Set(false); }		
    		static void Toggle(){ PORT::template Toggle<MASK>(); }
    		static bool IsSet(){ return PORT::PinRead() & MASK; }
            
            struct Configure
            {          
                //Generic config API. Should be implemented on every platform.
                static void OutPushPull_Slow(){ CONFIG_PORT::Configure::template OutPushPull_Slow<MASK>(); }
                static void OutPushPull_Medium(){ CONFIG_PORT::Configure::template OutPushPull_Medium<MASK>(); }
                static void OutPushPull_Fast(){ CONFIG_PORT::Configure::template OutPushPull_Fast<MASK>(); }
                static void OutOpenDrain_Slow(){ CONFIG_PORT::Configure::template OutOpenDrain_Slow<MASK>(); }
                static void OutOpenDrain_Medium(){ CONFIG_PORT::Configure::template OutOpenDrain_Medium<MASK>(); }
                static void OutOpenDrain_Fast(){ CONFIG_PORT::Configure::template OutOpenDrain_Fast<MASK>(); }
            
                static void InFloating(){ CONFIG_PORT::Configure::template InFloating<MASK>(); }
                static void InPullUp(){ CONFIG_PORT::Configure::template InPullUp<MASK>(); }
                static void InPullDown(){ CONFIG_PORT::Configure::template InPullDown<MASK>(); }
                static void InAnalog(){ CONFIG_PORT::Configure::template InAnalog<MASK>(); }

                static void EnableAF(){ CONFIG_PORT::Configure::template EnableAF<MASK>(); }
                static void DisableAF(){ CONFIG_PORT::Configure::template DisableAF<MASK>(); }
                static void EnableInterrupt(){ CONFIG_PORT::Configure::template EnableInterrupt<MASK>(); }
                static void DisableInterrupt(){ CONFIG_PORT::Configure::template DisableInterrupt<MASK>(); }
            };
            //Gives access to optional hardware specific port API
            typedef typename PORT::template HWSpecificAPI<MASK> HWSpecificAPI;
    	};//class TPinImplementation

        template<class PORT, uint8_t PIN, class CONFIG_PORT = PORT>
    	class InvertedPinImplementation: public TPinImplementation<PORT, PIN, CONFIG_PORT>
    	{
            static const typename PORT::DataT MASK = (typename PORT::DataT)1U << PIN;
    	public:
            struct IOInternals
            {
                typedef PORT Port;
                typedef typename PORT::DataT PortDataT;
    		    typedef CONFIG_PORT ConfigPort;
                static const bool Inverted = true;
    		    static const uint8_t PortPinNumber = PIN;
            };    		
                        
    		static void Set(bool val)
    		{
    			if( val )
    				PORT::template Clear<MASK>();
    			else
    				PORT::template Set<MASK>();
    		}
    		static void Set(){ Set(true); }
    		static void Clear(){ Set(false); }
    	};//class InvertedPinImplementation
        
        //Just put together interfaces of TPinImplementation and TPinInterfaceExtension
        template< class PORT, uint8_t PIN, class CONFIG_PORT = PORT >
        class TPin: public TPinImplementation<PORT, PIN, CONFIG_PORT>, public TPinInterfaceExtension< TPinImplementation<PORT, PIN, CONFIG_PORT> >
        { };

        //Just put together interfaces of InvertedPinImplementation and TPinInterfaceExtension
        template< class PORT, uint8_t PIN, class CONFIG_PORT = PORT >
        class InvertedPin: public InvertedPinImplementation<PORT, PIN, CONFIG_PORT>, public TPinInterfaceExtension< InvertedPinImplementation<PORT, PIN, CONFIG_PORT> >
        { };    	
    }// namespace Private
}// namespace IO
#endif

