#ifndef TIME_CLASS_H
#define TIME_CLASS_H

class TimeClass
    {
  public:
    volatile uint8_t second;//63 = 6bits
    volatile uint8_t minute;//63 = 6bits
    volatile uint8_t hour;//31 = 5bits
    
#ifdef TIME_TEST_NEW_STORAGE
    struct TimeStorage_t
      {
      uint8_t second : 6;
      uint8_t minute : 6;
      uint8_t hour : 5;
      uint8_t day : 7;
      } TimeStorage;
#endif  
  void operator ++ (int)//postfix
    {
    this->IncrementSeconds();
    }
  void operator ++ (void)//prefix
    {
    this->IncrementSeconds();
    //return c.second;
    }
  void operator -- (int)//postfix
    {
    this->DecrementSeconds();
    }  
  void operator -- (void)//prefix
    {
    this->DecrementSeconds();
    }  
  uint8_t GetRawSecond(void)
    {
    return this->second;
    }
  uint8_t GetRawMinute(void)
    {
    return this->minute;
    }
  uint8_t GetRawHour(void)
    {
    return this->hour;
    }
  uint8_t GetSecond(void)
    {
    return this->GetRawSecond();
    }
  uint8_t GetMinute(void)
    {
    return this->GetRawMinute();
    }
  uint8_t GetHour(void)
    {
    return (this->hour % 24);
    }
  uint8_t GetDay(void)
    {
    return (this->hour / 24);
    }
  uint16_t AsMinutesPassed(void)
    {
    return this->AsMinutesPassed(this->hour, this->minute);
    }
  uint16_t AsMinutesPassed(uint8_t hours, uint8_t minutes)
    {
    return (hours * 60) + minutes;
    }
  bool IsNotEmpty(void)
    {
    return !(this->IsEmpty());
    }
  bool IsEmpty(void)
    {
    return ( (this->second | this->minute | this->hour) == 0);
    }

  void SetTime(TimeClass& t)
    {
    this->hour  = t.hour;
    this->minute  = t.minute;
    this->second  = t.second;
    }
  void SetTime(uint8_t set_hour, uint8_t set_minute, uint8_t set_second)
    {
    this->hour  = set_hour;
    this->minute  = set_minute;
    this->second  = set_second;
    }
  void SetTime(uint16_t seconds)
    {
    this->SetTime((uint32_t)seconds);
    }
  void SetTime(uint32_t seconds)
    {
    this->hour  = seconds/(60*60);
    seconds    = seconds%(60*60);
    this->minute  = seconds/60;
    this->second  = seconds%60;
    }
  void DecrementSeconds (void)
    {
    --this->second;
    this->Update();
    }
  void IncrementSeconds (void)
    {
    ++this->second;
    this->Update();
    }
  void Update(void)
    {
    //обработка декремента
    if (this->second == 255)
      {
      this->second  = 59;
      --this->minute;
      }
    if (this->minute == 255)
      {
      this->minute  = 59;
      --this->hour;
      }
    if (this->hour == 255)
      {
      this->hour  = 23;
      }


    if (this->second > 59)
      {
      this->second  = 0;
      ++this->minute;
      }
    if (this->minute > 59)
      {
      this->minute  = 0;
      ++this->hour;
      }
    if (this->hour > 99)
      {
      this->hour  = 0;
      }
    }
  #ifdef _AVR_ATXMEGA128A1U_H_INCLUDED
  void UpdateTimeFromRTC(void)
    {
    while (RTC.CNT > 0)
      {
      RTC.CNT--;
      this->IncrementSeconds();
      //this->++;
      }
    }
  #endif
  TimeClass (void)
    {
    this->hour    = 0;
    this->minute  = 0;
    this->second  = 0;
    }
  protected:
  private:
  };

class DateTime5bClass
  {
  static const uint8_t MAX_RAW_SECOND = 63;//6 bit
  static const uint8_t MAX_RAW_MINUTE = 63;//6 bit
  static const uint8_t MAX_RAW_HOUR   = 31;//5 bit
  static const uint8_t MAX_RAW_DAY    = 31;//5 bit
  static const uint8_t MAX_RAW_MONTH  = 15;//4 bit
  static const uint16_t MAX_RAW_YEAR  = 16383;//14 bit

  static const uint8_t MIN_SECOND = 0;//6 bit
  static const uint8_t MIN_MINUTE = 0;//6 bit
  static const uint8_t MIN_HOUR   = 0;//5 bit
  static const uint8_t MIN_DAY    = 1;//5 bit
  static const uint8_t MIN_MONTH  = 1;//4 bit
  static const uint16_t MIN_YEAR  = 0;//14 bit

  static const uint8_t MAX_SECOND = 59;//6 bit [0..59]
  static const uint8_t MAX_MINUTE = 59;//6 bit [0..59]
  static const uint8_t MAX_HOUR   = 23;//5 bit [0..23]
  //static const uint8_t MAX_DAY    = 1;//5 bit [1..28/29/30/31]
  static const uint8_t MAX_MONTH  = 12;//4 bit [1..12]
  static const uint16_t MAX_YEAR  = 16383;//14 bit [0..16383]
  
  static const uint8_t MONTH_JANUARY  = 1;
  static const uint8_t MONTH_FEBRUARY = 2;
  static const uint8_t MONTH_MARCH    = 3;
  
  static const uint8_t days_in_month[];

  struct TimeStorage_t
  {
	  TimeStorage_t():
	  second(MIN_SECOND),
	  minute  ( MIN_MINUTE),
	  hour    (MIN_HOUR),
	  day     (MIN_DAY),
	  month   (MIN_MONTH),
	  year    (MIN_YEAR)
	  {}
	  
	  uint8_t second : 6;//[0..59]     6
	  uint8_t minute : 6;//[0..59]      12
	  uint8_t hour : 5;//[0..23]        17
	  uint8_t day : 5;//[1..31]
	  uint8_t month : 4;//[1..12]       //day+month = 372 = 9bits
	  uint16_t year : 14;//[0..16383]        //day+month+year = 16bits
  } time_storage;//5bytes

  void operator ++ (int)//postfix
	{
	this->increment_seconds();
	}
  void operator ++ (void)//prefix
	{
	this->increment_seconds();
	}
  void operator -- (int)//postfix
	{
	this->decrement_seconds();
	}
  void operator -- (void)//prefix
	{
	  this->decrement_seconds();
	}

  void decrement_seconds (void)
    {
    --this->time_storage.second;
    this->update();
    }
  void increment_seconds (void)
    {
    ++this->time_storage.second;
    this->update();
    }
  bool is_current_year_is_leap(void)
	{
	return this->is_year_is_leap(this->time_storage.year);
	}
  bool is_year_is_leap(uint16_t year)
	{
	if (this->time_storage.year % 400 == 0)
		{
		return true;
		}
	else
		{
		if (this->time_storage.year % 4 == 0)
			{
			if (this->time_storage.year % 100 != 0)
				{
				return true;
				}
			}
		}
	return false;
	}
  uint8_t get_current_month_days_num(void)
	{
	//uint8_t days = this->days_in_month[this->time_storage.month];
	if (this->time_storage.month == MONTH_FEBRUARY)
		{
		if (this->is_current_year_is_leap())
			{
			//++days;
			return 29;
			}
		return 28;
		}
	return this->days_in_month[this->time_storage.month];
	//return days;
	}
  inline uint8_t days_in_month_v2(const uint8_t mo, const bool leap_yr=false) //test it!
  {
	  switch(mo)
	  {
		  case 2:
		  return leap_yr ? 29 : 28;
		  break;
		  
		  case 4:
		  case 6:
		  case 9:
		  case 11:
		  return 30;
		  break;
		  
	  }
	  return 31;
  }
  void update(void)
    {
    //дней в году: 365,2425
    //Високосный год:
    //Если делится на 4  ,НО не делится на 100, кросе тех ,что делится на 400
    //1) ТО есть, если делится на 400 - високосный
    //2) Иначе, если делится на 4, но не делится на 100 - високосный
    //if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))
    
    //обработка декремента
    if (this->time_storage.second == MAX_RAW_SECOND)
      {
      this->time_storage.second  = MAX_SECOND;
	  if (--this->time_storage.minute == MAX_RAW_MINUTE)
		 {
		 this->time_storage.minute  = MAX_MINUTE;
	     if (--this->time_storage.hour == MAX_RAW_HOUR)
		     {
		     this->time_storage.hour  = MAX_HOUR;
		 	 if (--this->time_storage.day == 0)//hmm
				
		 		{
		 		//this->time_storage.day  = day?;
		 		//--month
		 		--this->time_storage.month;//prev day (0 mean december too xD)
		 		this->time_storage.day = this->days_in_month[this->time_storage.month];
		 		//First decrement , than getting a day
				//February... can calculate now, because year can't be decrement if not is February =)
				if (this->time_storage.month == MONTH_FEBRUARY)
					{
					if (this->is_current_year_is_leap())
						{
						++this->time_storage.day;//a hack
						}
					}
		 		if (this->time_storage.month == 0)//hmm
		 			{
		 			this->time_storage.month  = MAX_MONTH;
		 			if (this->time_storage.year > 0)
		 				{
		 				--this->time_storage.year;
		 				}
		 			}
		 		}
		     }
		 
	     }
      } 

    
    
    
//Increment
    if (this->time_storage.second > MAX_SECOND)
      {
      this->time_storage.second  = MIN_SECOND;
	  if (++this->time_storage.minute > MAX_MINUTE)
		{
		this->time_storage.minute  = MIN_MINUTE;
		if (++this->time_storage.hour > MAX_HOUR)
			{
		    this->time_storage.hour  = MIN_HOUR;
		    //day need to be incremented, but (31)++ would be 0, (30)++ would be 31, so...
		    //++this->time_storage.day;
		    if (this->time_storage.day == this->get_current_month_days_num())//mean we need to increment last day, so next would be 1st
				{
			    this->time_storage.day = MIN_DAY;
			    //and increment month
			    if (++this->time_storage.month > MAX_MONTH)
					{
				    this->time_storage.month = MIN_MONTH;
				    if (this->time_storage.year < MAX_RAW_YEAR)
						{
					    ++this->time_storage.year;
						}
					}
				}
		    else
				{
			    ++this->time_storage.day;
				}
			}
		}
      }
    }
  #ifdef _AVR_ATXMEGA128A1U_H_INCLUDED
  void UpdateTimeFromRTC(void)
    {
    while (RTC.CNT > 0)
      {
      RTC.CNT--;
      this->increment_seconds();
      }
    }
  #endif

  protected:
  private:
  };
const uint8_t days_in_month[] = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //0 mean December in decrement

/*
class DateTime_UnixModClass
  {
  public:
  uint32_t get_seconds_passed(void)
    {
    return this->sec_counter;
    }
  uint32_t get_minutes_passed(void)
    {
    return this->get_seconds_passed() / 60;
    }
  uint32_t get_hours_passed(void)
    {
    return this->get_minutes_passed() / 60;
    }
  uint32_t get_days_passed(void)
    {
    return this->get_hours_passed() / 24;
    }
  //how to get months??!
  
  uint8_t get_current_second(void)
    {
    return this->get_seconds_passed() % 60;
    }
  uint8_t get_current_minute(void)
    {
    return ( this->get_seconds_passed() / 60 ) % 60;
    }
  uint8_t get_current_hour(void)
    {
    return ( this->get_seconds_passed() / (60*60) ) % 24;
    }
  uint8_t get_current_day(void)
    {
    return 28 + (x + Math.floor(x / 8)) % 2 + 2 % x + Math.floor((2 - ((y % 4) * ((y % 100) + (y % 400)) + 2) % ((y % 4) * ((y % 100) + (y % 400)) + 1)) / x) + Math.floor(1/x) - Math.floor((1 - ((y % 4) * ((y % 100) + (y % 400)) + 2) % ((y % 4) * ((y % 100) + (y % 400)) + 1))/x);
    }
  DateTime_UnixModClass(void)
    {
    this->sec_counter = 0;
    }
  DateTime_UnixModClass(uint32_t sec)
    {
    this->sec_counter = sec;
    }
  protected:
  private:
  uint32_t sec_counter;
  };
*/
#endif