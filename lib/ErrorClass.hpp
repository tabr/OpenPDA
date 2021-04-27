/*
 * ErrorClass.h
 *
 * Created: 28.01.2016 0:46:50
 *  Author: tabr
 */ 


#ifndef ERRORCLASS_H_
#define ERRORCLASS_H_


class ErrorClass
	{
	public:
		enum CODES
			{
			ERROR_NO_ERRORS,
			ERROR_DAMAGE_SOURCE_ALREADY_SET,//method bool SetDamageSourcesNum(DamageSourcesNum_t num) can be called only once!
			ERROR_DAMAGE_SOURCE_OVF,//num is bigger than max
			ERROR_MULTIBYTE_ID_BIGGER_THAN_MAX,
			CODES_MAXIMUM,
			};
		void SetError(ErrorClass::CODES code);
		ErrorClass::CODES GetLastError(void);
	protected:
	private:
		ErrorClass::CODES lastCode=CODES::ERROR_NO_ERRORS;
	};


#endif /* ERRORCLASS_H_ */