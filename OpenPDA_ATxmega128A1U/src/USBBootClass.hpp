#pragma once
/* 
* USBBootClass.h
*
* Created: 01.05.2018 12:19:47
* Author: tabr
*/

//#define F_CPU 32000000UL
#ifndef __USBBOOTCLASS_HPP__
#define __USBBOOTCLASS_HPP__
#include "usb/protocol.h"
//#include "typedefs.h"
#include "unionsFixed.h"
#include <util/delay.h>
#include <string.h>
//#include "usb/TWI_c.h"
#include "usb/protocol.h"
//#include "M25P05.c"
//extern FlashMemoryClass<MediaFlashSPI> MediaMemory;
/*
struct udd_sram_data {
  #if XMEGA_A1U
  #  if (0!=((USB_DEVICE_MAX_EP+1)%4))
  uint8_t padding_align[16 - ((USB_DEVICE_MAX_EP + 1) *
  sizeof(uint32_t)) % 16];
  #  endif
  #endif
  uint32_t fifo[USB_DEVICE_MAX_EP + 1];
  USB_EP_t ep_ctrl[2 * (USB_DEVICE_MAX_EP + 1)];
  uint16_t frame_number;
};*/
#include "udd_ctrl_request_t.hpp"
class USBBootClass
  {
  //variables
  public:
    uint8_t outgoingData [UDI_HID_REPORT_OUT_SIZE];
    uint8_t incomingData [UDI_HID_REPORT_IN_SIZE];
    uint8_t writeBufferTop							= 0;
    uint8_t writeBufferBottom						= 0;
    uint8_t writeBuffers[(USB_WRITE_BUFFERS_NUM * USB_PAYLOAD_SIZE)];
    uint8_t commandProcessing				= 0;
    uint8_t selectedMemory					= 0;
    uint8_t addressH						= 0;
    uint8_t addressM						= 0;
    uint8_t addressL						= 0;
    bool isAwaitingForData					= false;
    COMPILER_WORD_ALIGNED
    uint8_t udi_hid_generic_report_in[UDI_HID_REPORT_IN_SIZE];
    COMPILER_WORD_ALIGNED
    uint8_t udi_hid_generic_report_out[UDI_HID_REPORT_OUT_SIZE];
    COMPILER_WORD_ALIGNED
    uint8_t udi_hid_generic_report_feature[UDI_HID_REPORT_FEATURE_SIZE];
    COMPILER_WORD_ALIGNED
    uint8_t udi_hid_generic_rate;
    //! To store current protocol of HID generic
    COMPILER_WORD_ALIGNED
    uint8_t udi_hid_generic_protocol;
    //! To signal if the report IN buffer is free (no transfer on going)
    bool udi_hid_generic_b_report_in_free;

    /*
    #if XMEGA_A1U
    COMPILER_ALIGNED(16)
    #else
    COMPILER_ALIGNED(4) //! Caution seems GCC does not handle 2 alignment properly
    #endif
    volatile udd_sram_data udd_sram;
    */

    udd_ctrl_request_t udd_g_ctrlreq;

    //! HID report descriptor for standard HID generic
    UDC_DESC_STORAGE udi_hid_generic_report_desc_t udi_hid_generic_report_desc = { {
      0x06, 0xFF, 0xFF,	// 04|2   , Usage Page (vendor defined?)
      0x09, 0x01,	// 08|1   , Usage      (vendor defined
      0xA1, 0x01,	// A0|1   , Collection (Application)
      // IN report
      0x09, 0x02,	// 08|1   , Usage      (vendor defined)
      0x09, 0x03,	// 08|1   , Usage      (vendor defined)
      0x15, 0x00,	// 14|1   , Logical Minimum(0 for signed byte?)
      0x26, 0xFF, 0x00,	// 24|1   , Logical Maximum(255 for signed byte?)
      0x75, 0x08,	// 74|1   , Report Size(8) = field size in bits = 1 byte
      // 94|1   , ReportCount(size) = repeat count of previous item
      0x95, sizeof(this->udi_hid_generic_report_in),
      0x81, 0x02,	// 80|1   , IN report (Data,Variable, Absolute)
      // OUT report
      0x09, 0x04,	// 08|1   , Usage      (vendor defined)
      0x09, 0x05,	// 08|1   , Usage      (vendor defined)
      0x15, 0x00,	// 14|1   , Logical Minimum(0 for signed byte?)
      0x26, 0xFF, 0x00,	// 24|1   , Logical Maximum(255 for signed byte?)
      0x75, 0x08,	// 74|1   , Report Size(8) = field size in bits = 1 byte
      // 94|1   , ReportCount(size) = repeat count of previous item
      0x95, sizeof(this->udi_hid_generic_report_out),
      0x91, 0x02,	// 90|1   , OUT report (Data,Variable, Absolute)
      // Feature report
      0x09, 0x06,	// 08|1   , Usage      (vendor defined)
      0x09, 0x07,	// 08|1   , Usage      (vendor defined)
      0x15, 0x00,	// 14|1   , LogicalMinimum(0 for signed byte)
      0x26, 0xFF, 0x00,	// 24|1   , Logical Maximum(255 for signed byte)
      0x75, 0x08,	// 74|1   , Report Size(8) =field size in bits = 1 byte
      0x95, sizeof(this->udi_hid_generic_report_feature),	// 94|x   , ReportCount in byte
      0xB1, 0x02,	// B0|1   , Feature report
      0xC0	// C0|0   , End Collection
    }
  };



    bool isWriteBufferEmpty(void)
      {
      return (this->writeBufferTop == this->writeBufferBottom);
      }
    bool isWriteBufferFull(void)
      {
      // empty if ((writeBufferTop + 1) == writeBufferBottom)
      // то есть, если голова в следующий раз догонит зад
      uint8_t writeBufferTopTemp	= ((this->writeBufferTop + 1) & USB_WRITE_BUFFERS_MASK);
      return (writeBufferTopTemp == this->writeBufferBottom);
      }
    void writeBuffer_IncrementTop(void)
      {
      this->writeBufferTop++;
      this->writeBufferTop	&= USB_WRITE_BUFFERS_MASK;
      }
    void writeBuffer_IncrementBottom(void)
      {
      this->writeBufferBottom++;
      this->writeBufferBottom	&= USB_WRITE_BUFFERS_MASK;
      }
    void writeBuffer_Write(uint8_t *data, uint8_t size)
      {
      memcpy (&this->writeBuffers[(this->writeBufferTop * USB_PAYLOAD_SIZE)], data, size);
      writeBuffer_IncrementTop();
      }
    void CommandProcess(void);
    void my_callback_generic_set_feature(uint8_t *report_feature)
    	{
    	switch (report_feature[PACKET_FEATURE_STRUCTURE_COMMAND])
    		{
    		case COMMAND_WB_RESET_BUFFERS:
          this->CleanBuffers();
    			udi_hid_generic_send_report_in(this->outgoingData);
    		break;
    		case COMMAND_SELECT_MEMORY:
    			if (report_feature[PACKET_FEATURE_STRUCTURE_SM_MEMORY] < PDAMEMORY_ERROR && report_feature[PACKET_FEATURE_STRUCTURE_SM_MEMORY] > PDAMEMORY_NONE)//заменить бы на что-то вроде "isMemoryGood()"
    				{
    				this->selectedMemory		= report_feature[PACKET_FEATURE_STRUCTURE_SM_MEMORY];
    				this->commandProcessing	= report_feature[PACKET_FEATURE_STRUCTURE_SM_COMMAND];
    				}
    			break;
    		case COMMAND_READ:
    		case COMMAND_WRITE:
    			this->commandProcessing	= report_feature[PACKET_FEATURE_STRUCTURE_RW_COMMAND];
    			this->addressH			= report_feature[PACKET_FEATURE_STRUCTURE_RW_ADDRESS_H];
    			this->addressM			= report_feature[PACKET_FEATURE_STRUCTURE_RW_ADDRESS_M];
    			this->addressL			= report_feature[PACKET_FEATURE_STRUCTURE_RW_ADDRESS_L];

	    	break;
	    	
	    	case COMMAND_WB_GET_STATUS:
	    		
//    			outgoingData[PACKET_RESPOND_GWBS_BUFFER_STATUS]		= writeBuffersStatus;
	    		this->outgoingData[PACKET_RESPOND_GWBS_TOP]       = this->writeBufferTop;
	    		this->outgoingData[PACKET_RESPOND_GWBS_BOTTOM]    = this->writeBufferBottom;
	    		//outgoingData[PACKET_RESPOND_GWBS_BUSYBUF_MASK]	= writeBuffer_NumBusyBuffersMask;//getFirstFreeWriteBufferID();
	    		udi_hid_generic_send_report_in(this->outgoingData);
	    	break;
	    	}
	    
	    }
    void my_callback_generic_report_out(uint8_t *bufferData)
    	{
    	//uint8_t bufferID;
    	//if (!isAwaitingForData)
    	//	return;
    	switch(bufferData[PACKET_GENERIC_STRUCTURE_COMMAND])
    		{
    		case COMMAND_WB_WRITE:
    			{
    			/*uint8_t bufferID	= bufferData[PACKET_SETBUFFER_STRUCTURE_BUFFERID];
    			if (bufferID >= USB_WRITE_BUFFERS_NUM)
    				{
    				return;
    				}*/
    			this->writeBuffer_Write(&bufferData[USB_BUFFER_START_SECTION_PAYLOAD], USB_PAYLOAD_SIZE);
    			//memcpy(&writeBuffers[(bufferID * USB_PAYLOAD_SIZE)], &bufferData[USB_BUFFER_START_SECTION_PAYLOAD], USB_PAYLOAD_SIZE);
    //			sbi(writeBuffer_NumBusyBuffersMask,bufferID);
    			}
    		break;
    		}
    	}
  protected:
  private:
    UNION_UINT32 addressProcessing;
  //functions
  public:
    void CleanBuffers(void)
      {
      this->writeBufferBottom = 0;
      this->writeBufferTop    = 0;
      }
  	//USBBootClass();
  	//~USBBootClass();
  protected:
  private:
  	//USBBootClass( const USBBootClass &c );
  	//USBBootClass& operator=( const USBBootClass &c );
  
  }; //USBBootClass

#endif //__USBBOOTCLASS_HPP__
