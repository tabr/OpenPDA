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
#ifndef AVR_GPIOIMPLEMENTATION_HPP_
#define AVR_GPIOIMPLEMENTATION_HPP_

#ifndef NEIVERIO_HPP_
    #error "Do not include this file directly. Use #include\"neiverio.hpp\" instead!"
#endif

//define to know what MCU we are running on
//#define NEIVERIO_STM8_PORT_
//#define NEIVERIO_STM32_PORT_
#define NEIVERIO_AVR_PORT_
//#define NEIVERIO_XMEGA_PORT_

namespace IO
{
    namespace Private
    {
        struct NativePortBase: public GpioBase
        {	
            typedef uint8_t DataT;
            enum{ Width = sizeof(DataT) * 8 };
            
            struct IOInternals
            {                            
                typedef NativePortBase Base; //do we need this????
            };
        };//struct NativePortBase
    	
        //template parematers is PORT DDR and PIN GPIO geristers from datasheet
        template<class PORTx, class DDRx, class PINx >
    	class PortImplimentation: public NativePortBase
        {            
        public:           
            //=============Generic API. Everybody should implement and respect it==============
    		static void Write(DataT value){ PORTx::Set(value); }
            static DataT Read(){ return PORTx::Get(); }
            static DataT PinRead(){ return PINx::Get(); }
            static void Set(DataT value){ PORTx::Or(value); }
    		static void Clear(DataT value){ PORTx::And( (DataT)~value ); }
            static void ClearAndSet(DataT clearMask, DataT value){ PORTx::AndOr((DataT)~clearMask, value); }
    		static void Toggle(DataT value){ PORTx::Xor(value); }                        

            template<DataT value>
    		static void Set(){ PORTx::Or(value); }
    		template<DataT value>
    		static void Clear(){ PORTx::And((DataT)~value); }
            template<DataT clearMask, DataT value>
    		static void ClearAndSet(){ PORTx::AndOr((DataT)~clearMask, value); }
            template<DataT value>
    		static void Toggle(){ PORTx::Xor(value); }

            struct Configure
            {   
                template<DataT MASK>
                static void OutPushPull_Slow(){ OutPushPull_Fast<MASK>(); }
                template<DataT MASK>
                static void OutPushPull_Medium(){ OutPushPull_Fast<MASK>(); }
                template<DataT MASK>
                static void OutPushPull_Fast(){ DDRx::Or(MASK); }
                template<DataT MASK>
                static void OutOpenDrain_Slow(){ }      //Open Drain is not supported on AVR
                template<DataT MASK>
                static void OutOpenDrain_Medium(){ }    //Open Drain is not supported on AVR
                template<DataT MASK>
                static void OutOpenDrain_Fast(){ }      //Open Drain is not supported on AVR
            
                template<DataT MASK>
                static void InFloating(){ DDRx::And( (DataT)~MASK ); PORTx::And( (DataT)~MASK ); }
                template<DataT MASK>
                static void InPullUp(){ DDRx::And( (DataT)~MASK ); PORTx::Or(MASK); }
                template<DataT MASK>
                static void InPullDown(){ InFloating<MASK>(); } //Pull down is not supported on AVR
                template<DataT MASK>
                static void InAnalog(){ InFloating<MASK>(); }

                template<DataT MASK>
                static void EnableAF(){ }   //there is no special bit for AF in AVR
                template<DataT MASK>
                static void DisableAF(){ }  //there is no special bit for AF in AVR
                template<DataT MASK>
                static void EnableInterrupt(){  } //Interrupt register is not in GPIO module, so empty
                template<DataT MASK>
                static void DisableInterrupt(){  } //Interrupt register is not in GPIO module, so empty
            };

            //=============Hardware specific API for maximum flexibility======================            
            //TPin will expose this API to users as Pxn::HWSpecificAPI::HWSpecific_method();
            //Some operations may need MASK to work, TPin will provide it.
            template< DataT MASK=0 >
            struct HWSpecificAPI
            {
                static void GlobalPullupDisable()
                  {
                  #ifdef _AVR_ATMEGA168PA_H_INCLUDED
                  MCUCR |= 1 << PUD;
                  #else
                  SFIOR |= 1 << PUD;
                  #endif
                  }
                static void GlobalPullupEnable()
                  {
                  #ifdef __AVR_ATmega168PA__
                  MCUCR &= (DataT)~(1 << PUD);
                  #else
                  SFIOR &= (DataT)~(1 << PUD);
                  #endif
                  }
                static volatile DataT &GetPORTRegReference(){ return PORTx::GetReference(); }
                static volatile DataT &GetDDRRegReference(){ return DDRx::GetReference(); }
                static volatile DataT &GetPINRegReference(){ return PINx::GetReference(); }
            };            
    	};//PortImplimentation
    }//namespace Private


#define PORT_REGS_WRAPPER(PORT_LETTER) \
	IO_REG_WRAPPER(PORT ## PORT_LETTER, Out ## PORT_LETTER, uint8_t);\
	IO_REG_WRAPPER(DDR ## PORT_LETTER, Dir ## PORT_LETTER, uint8_t);\
	IO_REG_WRAPPER(PIN ## PORT_LETTER, In ## PORT_LETTER, uint8_t);

#define MAKE_PORT(PORT_LETTER, className, ID) \
    namespace Private{ PORT_REGS_WRAPPER(PORT_LETTER) }\
        struct className: public Private::PortImplimentation<Private::Out ## PORT_LETTER,\
                                                            Private::Dir ## PORT_LETTER,\
                                                            Private::In ## PORT_LETTER>\
        {\
            enum{Id = ID};\
        };

#ifdef PORTA
    #define USE_PORTA
    MAKE_PORT(A, Porta, 'A')
#endif
#ifdef PORTB
    #define USE_PORTB
    MAKE_PORT(B, Portb, 'B')
#endif
#ifdef PORTC
    #define USE_PORTC
    MAKE_PORT(C, Portc, 'C')
#endif
#ifdef PORTD
    #define USE_PORTD
    MAKE_PORT(D, Portd, 'D')
#endif
#ifdef PORTE
    #define USE_PORTE
    MAKE_PORT(E, Porte, 'E')
#endif
#ifdef PORTF
    #define USE_PORTF
    MAKE_PORT(F, Portf, 'F')
#endif
#ifdef PORTG
    #define USE_PORTG
    MAKE_PORT(G, Portg, 'G')
#endif
#ifdef PORTH
    #define USE_PORTH
    MAKE_PORT(H, Porth, 'H')
#endif
#ifdef PORTI
    #define USE_PORTI
    MAKE_PORT(I, Porti, 'I')
#endif
#ifdef PORTJ
    #define USE_PORTJ
    MAKE_PORT(J, Portj, 'J')
#endif
#ifdef PORTK
    #define USE_PORTK
    MAKE_PORT(K, Portk, 'K')
#endif
#ifdef PORTQ
    #define USE_PORTQ
    MAKE_PORT(Q, Portq, 'Q')
#endif
#ifdef PORTR
    #define USE_PORTR
    MAKE_PORT(R, Portr, 'R')
#endif    
}//namespace IO
#endif //AVR_GPIOIMPLEMENTATION_HPP_

