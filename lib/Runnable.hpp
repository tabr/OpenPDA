#ifndef RUNNABLE_H
#define RUNNABLE_H

class Runnable
	{
	public:
		uint8_t counter;//счетчик оставшегося времени
		Runnable* nextItem;
		void setNext(Runnable &r)
			{
			this->nextItem	= &r;
			}
		virtual void Task(void)	= 0;
		/*void Task (void* Obj)
			{
			this->m_Obj	= Obj;
			}*/
		virtual uint8_t getRepeatTime(void)	= 0;
		Runnable(void): counter(0),nextItem(NULL), m_Obj(NULL)
			{
			}
		void SetLinkedObject(void* Obj)
			{
			this->m_Obj	= Obj;
			}
		bool HasLinkedObject(void)
			{
			return (this->m_Obj != NULL);
			}
		void* GetLinkedObject(void)
			{
			return this->m_Obj;
			}
	protected:
	private:
		void* m_Obj;
	};

#endif