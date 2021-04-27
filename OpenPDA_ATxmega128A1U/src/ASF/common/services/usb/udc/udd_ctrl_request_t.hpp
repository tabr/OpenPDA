/*
 * udd_ctrl_request_t.h
 *
 * Created: 02.05.2018 10:34:37
 *  Author: tabr
 */ 


#ifndef UDD_CTRL_REQUEST_T_H_
#define UDD_CTRL_REQUEST_T_H_

typedef struct {
  //! Data received in USB SETUP packet
  //! Note: The swap of "req.wValues" from uin16_t to le16_t is done by UDD.
  usb_setup_req_t req;

  //! Point to buffer to send or fill with data following SETUP packet
  //! This buffer must be word align for DATA IN phase (use prefix COMPILER_WORD_ALIGNED for buffer)
  uint8_t *payload;

  //! Size of buffer to send or fill, and content the number of byte transfered
  uint16_t payload_size;

  //! Callback called after reception of ZLP from setup request
  void (*callback) (void);

  //! Callback called when the buffer given (.payload) is full or empty.
  //! This one return false to abort data transfer, or true with a new buffer in .payload.
  bool(*over_under_run) (void);
} udd_ctrl_request_t;



#endif /* UDD_CTRL_REQUEST_T_H_ */