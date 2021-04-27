//http://www.cs.mun.ca/~paul/cs4723/material/AVR/AVR1507/Task4/AES_driver.c
//http://www.cs.mun.ca/~paul/cs4723/material/AVR/AVR1507/Task4/AES_driver.h

#ifndef AES_CLASS_H
#define AES_CLASS_H

class AES_Class
	{
	public:
		const static uint8_t BLOCK_LENGTH		= 16;

		const static uint8_t key[BLOCK_LENGTH];
		const static uint8_t init[BLOCK_LENGTH];
		const static uint8_t lastSubkey[BLOCK_LENGTH];
		
		static void SoftwareReset(void)
			{
			AES.CTRL = AES_RESET_bm;
			}
		static void Start(void)
			{
			AES.CTRL |= AES_START_bm;
			}
		void loadKeyToRegister(void)
			{
			for (uint8_t i=0;i<this->BLOCK_LENGTH;i++)
				{
				AES.KEY	= this->key[i];
				}
			}
		void loadSubkeyToRegister(void)
			{
			for (uint8_t i=0;i<this->BLOCK_LENGTH;i++)
				{
				AES.KEY	= this->lastSubkey[i];
				}
			}
		/*bool Lastsubkey_generate(void)
			{
			this->SoftwareReset();
			this->loadKeyToRegister();
			// Load dummy data into AES state memory.
			for (uint8_t i=0;i<this->BLOCK_LENGTH;i++)
				{
				AES.STATE	= 0x00;
				}
			// Set AES in encryption mode and start AES.
			AES.CTRL = (AES.CTRL & (~AES_DECRYPT_bm)) | AES_START_bm;

			// Wait until AES is finished or an error occurs.
			while((AES.STATUS & (AES_SRIF_bm|AES_ERROR_bm) ) == 0);
			if((AES.STATUS & AES_ERROR_bm) == 0)
				{
				for (uint8_t i=0;i<this->BLOCK_LENGTH;i++)
					{
					this->lastSubkey[i]	= AES.KEY;
					}
				AES.STATUS	= AES_SRIF_bm;
				return true;
				}
			else
				{
				AES.STATUS	= AES_ERROR_bm;
				return false;
				}
			}*/
		volatile bool CBC_Decrypt(uint8_t* data) volatile
			{
			bool CBC_ok = true;
			AES.STATUS	= 0;
//			this->loadSubkeyToRegister();
			for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++)
				{
				AES.KEY		= this->lastSubkey[i];
				}
			for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++)
				{
				AES.STATE	= data[i];
				}
			/* Set AES in decryption mode and enable xor feature and start the AES. */
			AES.CTRL |= (AES_DECRYPT_bm | AES_XOR_bm | AES_START_bm);
			//AES.CTRL = (AES_DECRYPT_bm | AES_XOR_bm | AES_START_bm);
			//sei();
			while((AES.STATUS & (AES_SRIF_bm|AES_ERROR_bm) ) == 0);
			//cli();
			//return true;
			if((AES.STATUS & AES_ERROR_bm) == 0)
				{
				for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++)
					{
					AES.STATE	= this->init[i];
					}
				/* Disable XOR feature before next round. */
				AES.CTRL = AES.CTRL & (~AES_XOR_bm);
				for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++)
					{
					data[i]	= AES.STATE;
					}
				CBC_ok = true;
				}
			else
				{
				CBC_ok = false;
				}
			
			/* Turn off auto mode and xor feature. */
			AES.CTRL = (AES.CTRL & ~( AES_XOR_bm |AES_AUTO_bm));
			
			return CBC_ok;
			}
//bool AES_CBC_encrypt(uint8_t * plaintext, uint8_t * ciphertext, uint8_t * key, uint8_t * init, uint16_t block_count)
bool AES_CBC_encrypt(uint8_t * plaintext, uint8_t * ciphertext, uint16_t block_count)
	{
  	bool CBC_ok = true;
	AES.STATUS	= 0;
  	/* The first encryption uses the initialization vector. */

	//uint8_t * temp_init = init;
	for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++)
		{
		//AES.STATE =  *(temp_init++);
		AES.STATE	= this->init[i];
		}

	/* Set AES in encryption mode and enables the XOR feature and the AUTO start
	 * mode. */
	AES.CTRL = (AES.CTRL & (~AES_DECRYPT_bm))| AES_XOR_bm |AES_AUTO_bm;

	/* Temporary values used to reduce memory access. */
	uint8_t * temp_plaintext = plaintext;
	uint8_t * temp_ciphertext = ciphertext;

	for(uint8_t blocks_left = block_count; blocks_left > 0; blocks_left--)
		{

		/* Load key into AES key memory. */
		//uint8_t * temp_key = key;
		for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++)
			{
			//AES.KEY =  *(temp_key++);
			AES.KEY		= this->key[i];
			}

		/* Load plaintext into AES state memory. Auto starts. */
		for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++)
			{
			AES.STATE =  *(temp_plaintext++);
			}
		do
			{
			/* Wait until AES is finished or an error occurs. */
			}
		while((AES.STATUS & (AES_SRIF_bm|AES_ERROR_bm) ) == 0);

		/* If not error. */
		if((AES.STATUS & AES_ERROR_bm) == 0)
			{

			/* Store result. */
			uint8_t * temp = temp_ciphertext;
			for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++)
				{
				*(temp++) = AES.STATE;
				}
			temp_ciphertext = temp;
			}
		else
			{
			CBC_ok = false;
			}
		}

	/* Turn off auto mode and xor feature. */
	AES.CTRL = (AES.CTRL & ~( AES_XOR_bm |AES_AUTO_bm));

	return CBC_ok;
}
bool AES_encrypt(uint8_t * plaintext, uint8_t * ciphertext, uint8_t * key)
{
	bool encrypt_ok;

	/* Load key into AES key memory. */
	uint8_t * temp_key = key;
	for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++){
		AES.KEY =  *(temp_key++);
	}

	/* Load data into AES state memory. */
	uint8_t * temp_plaintext = plaintext;
	for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++){
		AES.STATE =  *(temp_plaintext++);
	}

	/* Set AES in encryption mode and start AES. */
	AES.CTRL = (AES.CTRL & (~AES_DECRYPT_bm)) | AES_START_bm;

	do{
		/* Wait until AES is finished or an error occurs. */
	}while((AES.STATUS & (AES_SRIF_bm|AES_ERROR_bm) ) == 0);

	/* If not error. */
	if((AES.STATUS & AES_ERROR_bm) == 0){
		/* Store the result. */
		uint8_t * temp_ciphertext = ciphertext;
		for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++){
			*(temp_ciphertext++) = AES.STATE;
		}
		encrypt_ok = true;
		}else{
		encrypt_ok = false;

	}
	return encrypt_ok;
}
bool AES_decrypt(uint8_t * ciphertext, uint8_t * plaintext, uint8_t * key)
{
	bool decrypt_ok;

	/* Load key into AES key memory. */
	uint8_t * temp_key = key;
	for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++){
		AES.KEY =  *(temp_key++);
	}

	/* Load data into AES state memory. */
	uint8_t * temp_ciphertext = ciphertext;
	for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++){
		AES.STATE =  *(temp_ciphertext++);
	}

	/* Set AES in decryption mode and start the AES.*/
	AES.CTRL |= (AES_START_bm | AES_DECRYPT_bm);

	do{
		/* Wait until AES is finished or an error occurs. */
	}while((AES.STATUS & (AES_SRIF_bm|AES_ERROR_bm) ) == 0);

	/* If not error. */
	if((AES.STATUS & AES_ERROR_bm) == 0){
		/* Store the result. */
		uint8_t * temp_plaintext = plaintext;
		for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++){
			*(temp_plaintext++) = AES.STATE;
		}
		decrypt_ok = true;
		}else{
		decrypt_ok = false;

	}
	return decrypt_ok;
}
bool AES_CBC_decrypt(uint8_t * ciphertext, uint8_t * plaintext, uint8_t * key, uint8_t * init, uint16_t block_count)
{
	bool CBC_ok = true;

	/* Temporary values used to reduce memory access. */
	uint8_t * temp_plaintext = plaintext;
	uint8_t * temp_ciphertext = ciphertext;

	for(uint8_t blocks_left = block_count; blocks_left > 0; blocks_left--){

		/* Load key into AES key memory. */
		uint8_t * temp_key = key;
		for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++)
			{
			AES.KEY =  *(temp_key++);
			}

		/* Load ciphertext into AES state memory. */
		uint8_t * temp = temp_ciphertext;
		for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++)
			{
			AES.STATE =  *(temp++);
			}

		temp_ciphertext = temp;

		/* Set AES in decryption mode and enable xor feature and start the AES. */
		AES.CTRL |= (AES_DECRYPT_bm | AES_XOR_bm | AES_START_bm);

		do{
			/* Wait until AES is finished or an error occurs. */
		}while((AES.STATUS & (AES_SRIF_bm|AES_ERROR_bm) ) == 0);

		/* If not error. */
		if((AES.STATUS & AES_ERROR_bm) == 0){

			/* The first block is xored with the initialization vector. */
			if(blocks_left == block_count){
				/* Load into AES state memory. */
				uint8_t * temp_init = init;
				for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++){
					AES.STATE =  *(temp_init++);
				}
			}
			/* The other blocks is xored with the previous ciphertext block. */
			else{
				/* Load into AES state memory. */
				uint8_t * last_ciphertext = temp_ciphertext - (this->BLOCK_LENGTH*2);
				for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++){
					AES.STATE =  *(last_ciphertext++);
				}
			}

			/* Disable XOR feature before next round. */
			AES.CTRL = AES.CTRL & (~AES_XOR_bm);

			/* Store the result. */
			uint8_t * temp = temp_plaintext;
			for(uint8_t i = 0; i < this->BLOCK_LENGTH; i++){
				*(temp++) = AES.STATE;
			}
			temp_plaintext = temp;
			}else{
			CBC_ok = false;
		}

	}
	return CBC_ok;
}



		AES_Class(void)
			{
			//this->Lastsubkey_generate();
			}
	protected:
	private:
	};
//uint8_t AES_Class::key[BLOCK_LENGTH]		= {0x94, 0x74, 0xB8, 0xE8, 0xC7, 0x3B, 0xCA, 0x7D,  0x28, 0x34, 0x76, 0xAB, 0x38, 0xCF, 0x37, 0xC2};
//pass - RH9w*¹Aq8]~PS*j?
//uint8_t AES_Class::key[BLOCK_LENGTH]		= {0x52, 0x48, 0x39, 0x77, 0x2a, 0xe2, 0x84, 0x96,  0x41, 0x71, 0x38, 0x5d, 0x7e, 0x50, 0x53, 0x2a};
const uint8_t AES_Class::key[BLOCK_LENGTH]		= {0x7c, 0x8a, 0x0a, 0x26, 0x38, 0x4a, 0xc0, 0x8c,  0x4f, 0x55, 0x73, 0x7d, 0xd7, 0x70, 0x63, 0xa8};
	
//uint8_t AES_Class::init[BLOCK_LENGTH]		= {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,  0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
const uint8_t AES_Class::init[BLOCK_LENGTH]		= {0x3b, 0xbc, 0xb8, 0xfd, 0x1d, 0xcd, 0x3d, 0xa4,  0xc5, 0x1c, 0xb8, 0xba, 0x05, 0x1e, 0x86, 0x9a};
	
const uint8_t AES_Class::lastSubkey[BLOCK_LENGTH] = {0x0e, 0x80, 0x0e, 0xc2, 0x8a, 0x11, 0xb7, 0x0a,  0x10, 0x00, 0x7b, 0x82, 0x40, 0xce, 0xc1, 0x10};

#endif