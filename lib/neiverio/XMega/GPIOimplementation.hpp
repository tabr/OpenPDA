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
#ifndef XMEGA_GPIOIMPLEMENTATION_HPP_
#define XMEGA_GPIOIMPLEMENTATION_HPP_

#ifndef NEIVERIO_HPP_
    #error "Do not include this file directly. Use #include\"neiverio.hpp\" instead!"
#endif

//define to know what MCU we are running on
//#define NEIVERIO_STM8_PORT_
//#define NEIVERIO_STM32_PORT_
//#define NEIVERIO_AVR_PORT_
#define NEIVERIO_XMEGA_PORT_

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

        template< class T >
    	class PortImplimentation: public NativePortBase
        {
			//Helper classes to access GPIO registers nice and easy
			IO_REG_WRAPPER(T::GetPORT_tRef().DIR, DIR,  DataT); /* I/O Port Data Direction */
			IO_REG_WRAPPER(T::GetPORT_tRef().DIRSET, DIRSET,  DataT); /* I/O Port Data Direction Set */
			IO_REG_WRAPPER(T::GetPORT_tRef().DIRCLR, DIRCLR, DataT);/* I/O Port Data Direction Clear */
			IO_REG_WRAPPER(T::GetPORT_tRef().DIRTGL, DIRTGL, DataT);/* I/O Port Data Direction Toggle */
			IO_REG_WRAPPER(T::GetPORT_tRef().OUT, OUT, DataT);  /* I/O Port Output */
			IO_REG_WRAPPER(T::GetPORT_tRef().OUTSET, OUTSET, DataT);
			IO_REG_WRAPPER(T::GetPORT_tRef().OUTCLR, OUTCLR, DataT);
			IO_REG_WRAPPER(T::GetPORT_tRef().OUTTGL, OUTTGL, DataT);
			IO_REG_WRAPPER(T::GetPORT_tRef().IN, IN, DataT); /* I/O port Input */
			IO_REG_WRAPPER(T::GetPORT_tRef().INTCTRL, INTCTRL, DataT); /* Interrupt Control Register */
			IO_REG_WRAPPER(T::GetPORT_tRef().INT0MASK, INT0MASK, DataT);/* Port Interrupt 0 Mask */
			IO_REG_WRAPPER(T::GetPORT_tRef().INT1MASK, INT1MASK, DataT);
			IO_REG_WRAPPER(T::GetPORT_tRef().INTFLAGS, INTFLAGS, DataT);/* Interrupt Flag Register */
			IO_REG_WRAPPER(T::GetPORT_tRef().REMAP, REMAP, DataT); /* I/O Port Pin Remap Register */
			IO_REG_WRAPPER(T::GetPORT_tRef().PIN0CTRL, PIN0CTRL, DataT); /* Pin 0 Control Register */
			IO_REG_WRAPPER(T::GetPORT_tRef().PIN1CTRL, PIN1CTRL, DataT);
			IO_REG_WRAPPER(T::GetPORT_tRef().PIN2CTRL, PIN2CTRL, DataT);
			IO_REG_WRAPPER(T::GetPORT_tRef().PIN3CTRL, PIN3CTRL, DataT);
			IO_REG_WRAPPER(T::GetPORT_tRef().PIN4CTRL, PIN4CTRL, DataT);
			IO_REG_WRAPPER(T::GetPORT_tRef().PIN5CTRL, PIN5CTRL, DataT);
			IO_REG_WRAPPER(T::GetPORT_tRef().PIN6CTRL, PIN6CTRL, DataT);
			IO_REG_WRAPPER(T::GetPORT_tRef().PIN7CTRL, PIN7CTRL, DataT);
			
			//Select PINnCTRL register by mask meta function
			template< DataT MASK, int DONTCARE=0 >
			struct PinCtrlByMask{ typedef PIN0CTRL Result; enum{Multipin=1}; };
			template< int DONTCARE >
			struct PinCtrlByMask<((DataT)1U << 0), DONTCARE >{ typedef PIN0CTRL Result; enum{Multipin=0}; };
			template< int DONTCARE >
			struct PinCtrlByMask<((DataT)1U << 1), DONTCARE >{ typedef PIN1CTRL Result; enum{Multipin=0}; };				
			template< int DONTCARE >
			struct PinCtrlByMask<((DataT)1U << 2), DONTCARE >{ typedef PIN2CTRL Result; enum{Multipin=0}; };				
			template< int DONTCARE >
			struct PinCtrlByMask<((DataT)1U << 3), DONTCARE >{ typedef PIN3CTRL Result; enum{Multipin=0}; };
			template< int DONTCARE >
			struct PinCtrlByMask<((DataT)1U << 4), DONTCARE >{ typedef PIN4CTRL Result; enum{Multipin=0}; };
			template< int DONTCARE >
			struct PinCtrlByMask<((DataT)1U << 5), DONTCARE >{ typedef PIN5CTRL Result; enum{Multipin=0}; };
			template< int DONTCARE >
			struct PinCtrlByMask<((DataT)1U << 6), DONTCARE >{ typedef PIN6CTRL Result; enum{Multipin=0}; };
			template< int DONTCARE >
			struct PinCtrlByMask<((DataT)1U << 7), DONTCARE >{ typedef PIN7CTRL Result; enum{Multipin=0}; };
        public:           
            //=============Generic API. Everybody should implement and respect it==============
    		static void Write(DataT value){ OUT::Set(value); }
            static DataT Read(){ return OUT::Get(); }
            static DataT PinRead(){ return IN::Get(); }
            static void Set(DataT value){ OUTSET::Set(value); }
    		static void Clear(DataT value){ OUTCLR::Set(value); }
            static void ClearAndSet(DataT clearMask, DataT value){ Clear(clearMask); Set(value); }
    		static void Toggle(DataT value){ OUTTGL::Set(value); }

            template<DataT value>
    		static void Set(){ OUTSET::Set(value); }
    		template<DataT value>
    		static void Clear(){ OUTCLR::Set(value); }
            template<DataT clearMask, DataT value>
    		static void ClearAndSet(){ Clear(clearMask); Set(value); }
            template<DataT value>
    		static void Toggle(){ OUTTGL::Set(value); }

            struct Configure
            {   
                template<DataT MASK>
                static void OutPushPull_Slow()
				{  
					DIRSET::Set(MASK);
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;										
					if( PinCtrlByMask<MASK>::Multipin )
						PORTCFG.MPCMASK = MASK;
					PINnCTRL::Set( PORT_SRLEN_bm | PORT_OPC_TOTEM_gc );
				}
                
				template<DataT MASK>
                static void OutPushPull_Medium(){ OutPushPull_Fast<MASK>(); }
                
				template<DataT MASK>
                static void OutPushPull_Fast()
				{
					DIRSET::Set(MASK);
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					if( PinCtrlByMask<MASK>::Multipin )					
						PORTCFG.MPCMASK = MASK;
					PINnCTRL::Set( PORT_OPC_TOTEM_gc );
				}
                
				template<DataT MASK>
                static void OutOpenDrain_Slow()
				{
					DIRSET::Set(MASK);
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					if( PinCtrlByMask<MASK>::Multipin )				
						PORTCFG.MPCMASK = MASK;
					PINnCTRL::Set( PORT_SRLEN_bm | PORT_OPC_WIREDAND_gc );
				}
                
				template<DataT MASK>
                static void OutOpenDrain_Medium(){ OutOpenDrain_Fast<MASK>(); }
                
				template<DataT MASK>
                static void OutOpenDrain_Fast()
				{
					DIRSET::Set(MASK);
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					if( PinCtrlByMask<MASK>::Multipin )
						PORTCFG.MPCMASK = MASK;						
					PINnCTRL::Set( PORT_OPC_WIREDAND_gc );					
				}
            
                template<DataT MASK>
                static void InFloating()
				{
					DIRCLR::Set(MASK);
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					if( PinCtrlByMask<MASK>::Multipin )
						PORTCFG.MPCMASK = MASK;
					PINnCTRL::Set( PORT_OPC_TOTEM_gc );
				}
                
				template<DataT MASK>
                static void InPullUp()
				{
					DIRCLR::Set(MASK);
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					if( PinCtrlByMask<MASK>::Multipin )
						PORTCFG.MPCMASK = MASK;
					PINnCTRL::Set( PORT_OPC_PULLUP_gc );
				}
                
				template<DataT MASK>
                static void InPullDown()
				{
					DIRCLR::Set(MASK);
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					if( PinCtrlByMask<MASK>::Multipin )
						PORTCFG.MPCMASK = MASK;
					PINnCTRL::Set( PORT_OPC_PULLDOWN_gc );
				}
				
                template<DataT MASK>
                static void InAnalog()
				{
					DIRCLR::Set(MASK);
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					if( PinCtrlByMask<MASK>::Multipin )
						PORTCFG.MPCMASK = MASK;
					PINnCTRL::Set( PORT_OPC_TOTEM_gc | PORT_ISC_INPUT_DISABLE_gc );
				}
				
                template<DataT MASK>
                static void EnableAF(){ }   //there is no special bit for AF in XMEGA
                template<DataT MASK>
                static void DisableAF(){ }  //there is no special bit for AF in XMEGA
                template<DataT MASK>
                static void EnableInterrupt(){  } //XMEGA has many Interrupts settings, use HWSpecificAPI to configure
                template<DataT MASK>
                static void DisableInterrupt(){  } //XMEGA has many Interrupt settings, use HWSpecificAPI to configure
            };

            //=============Hardware specific API for maximum flexibility======================            
            //TPin will expose this API to users as Pxn::HWSpecificAPI::HWSpecific_method();
            //Some operations may need MASK to work, TPin will provide it.
            template< DataT MASK=0 >
            struct HWSpecificAPI
            {
				//TODO: Add support of remapping and virtual ports
				
				//Return reference to port registers for super low level hacks )
				static PORT_t &GetGPIORegsReference(){ return T::GetPORT_tRef(); }
				
				/*
				* Set XMEGA specific output configurations
				* Apply this methosd AFTER configuring pin AS OUTPUT
				* Example: 
				* Pd0::Configure::OutPushPull_Slow(); //Now pin is configured as output TOTEM POLE(Push-pull)								
				* Pd0::HWSpecificAPI::SetOPC_BUSKEEPER(); //Then alter Output stage settings to BUSKEEPER		
				*/						
				static void SetOPC_BUSKEEPER()
				{
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					DataT temp_PINnCTRL = PINnCTRL::Get();
					if( PinCtrlByMask<MASK>::Multipin )
						PORTCFG.MPCMASK = MASK;
					PINnCTRL::Set( temp_PINnCTRL | PORT_OPC_BUSKEEPER_gc );
				}
				static void SetOPC_WIREDOR()
				{
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					DataT temp_PINnCTRL = PINnCTRL::Get();
					if( PinCtrlByMask<MASK>::Multipin )
						PORTCFG.MPCMASK = MASK;
					PINnCTRL::Set( temp_PINnCTRL | PORT_OPC_WIREDOR_gc );
				}
				static void SetOPC_WIREDORPULL()
				{
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					DataT temp_PINnCTRL = PINnCTRL::Get();
					if( PinCtrlByMask<MASK>::Multipin )
						PORTCFG.MPCMASK = MASK;
					PINnCTRL::Set( temp_PINnCTRL | PORT_OPC_WIREDORPULL_gc );
				}
				static void SetOPC_WIREDANDPULL()
				{
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					DataT temp_PINnCTRL = PINnCTRL::Get();
					if( PinCtrlByMask<MASK>::Multipin )
						PORTCFG.MPCMASK = MASK;
					PINnCTRL::Set( temp_PINnCTRL | PORT_OPC_WIREDANDPULL_gc );
				}				
				
				
				/* 
				* Interrupt related configuration. 
				* Apply this methods AFTER configuring pin AS INPUT
				* Example:
				* Pd0::Configure::InPullUp();
				* Pd0::HWSpecificAPI::SetOPC_BUSKEEPER(); //Then alter Output stage settings to BUSKEEPER		
				* Pd0::HWSpecificAPI::SetISC_FALLING();	//Int on falling edge
				* Pd0::HWSpecificAPI::EnableInINT0MASKRegister(); //Now Enabele pin in interrupt mask
				*/
				static void EnableInINT0MASKRegister(){ INT0MASK::Or(MASK); }
				static void DisableInINT0MASKRegister(){ INT0MASK::Or(MASK); }
				static void EnableInINT1MASKRegister(){ INT1MASK::Or(MASK); }
				static void DisableInINT1MASKRegister(){ INT1MASK::Or(MASK); }					
				static void SetISC_BOTHEDGES()
				{					
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					DataT temp_PINnCTRL = PINnCTRL::Get();
					if( PinCtrlByMask<MASK>::Multipin )
						PORTCFG.MPCMASK = MASK;					
					PINnCTRL::Set( temp_PINnCTRL | PORT_ISC_BOTHEDGES_gc );
				}
				static void SetISC_RISING()
				{
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					DataT temp_PINnCTRL = PINnCTRL::Get();
					if( PinCtrlByMask<MASK>::Multipin )
						PORTCFG.MPCMASK = MASK;
					PINnCTRL::Set( temp_PINnCTRL | PORT_ISC_RISING_gc );
				}
				static void SetISC_FALLING()
				{
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					DataT temp_PINnCTRL = PINnCTRL::Get();
					if( PinCtrlByMask<MASK>::Multipin )
						PORTCFG.MPCMASK = MASK;
					PINnCTRL::Set( temp_PINnCTRL | PORT_ISC_FALLING_gc );
				}
				static void SetISC_LEVEL()
				{
					typedef typename PinCtrlByMask<MASK>::Result PINnCTRL;
					DataT temp_PINnCTRL = PINnCTRL::Get();
					if( PinCtrlByMask<MASK>::Multipin )
						PORTCFG.MPCMASK = MASK;
					PINnCTRL::Set( temp_PINnCTRL | PORT_ISC_LEVEL_gc );
				}
            };            
    	};//PortImplimentation
    }//namespace Private

#define MAKE_PORT(portName, className, ID) \
class className :public Private::PortImplimentation<className>{\
	static PORT_t &GetPORT_tRef(){return portName;}\
	friend class Private::PortImplimentation<className>;\
	public:\
	enum{Id = ID};\
};


#ifdef PORTA
    #define USE_PORTA
    MAKE_PORT(PORTA, Porta, 'A')
#endif
#ifdef PORTB
    #define USE_PORTB
    MAKE_PORT(PORTB, Portb, 'B')
#endif
#ifdef PORTC
    #define USE_PORTC
    MAKE_PORT(PORTC, Portc, 'C')
#endif
#ifdef PORTD
    #define USE_PORTD
    MAKE_PORT(PORTD, Portd, 'D')
#endif
#ifdef PORTE
    #define USE_PORTE
    MAKE_PORT(PORTE, Porte, 'E')
#endif
#ifdef PORTF
    #define USE_PORTF
    MAKE_PORT(PORTF, Portf, 'F')
#endif
#ifdef PORTG
    #define USE_PORTG
    MAKE_PORT(PORTG, Portg, 'G')
#endif
#ifdef PORTH
    #define USE_PORTH
    MAKE_PORT(PORTH, Porth, 'H')
#endif
#ifdef PORTI
    #define USE_PORTI
    MAKE_PORT(PORTI, Porti, 'I')
#endif
#ifdef PORTJ
    #define USE_PORTJ
    MAKE_PORT(PORTJ, Portj, 'J')
#endif
#ifdef PORTK
    #define USE_PORTK
    MAKE_PORT(PORTK, Portk, 'K')
#endif
#ifdef PORTQ
    #define USE_PORTQ
    MAKE_PORT(PORTQ, Portq, 'Q')
#endif
#ifdef PORTR
    #define USE_PORTR
    MAKE_PORT(PORTR, Portr, 'R')
#endif    
}//namespace IO
#endif //AVR_GPIOIMPLEMENTATION_HPP_

