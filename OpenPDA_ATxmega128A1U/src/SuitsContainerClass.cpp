// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * SuitsContainerClass.cpp
 *
 * Created: 06.05.2017 20:33:15
 *  Author: tabr
 */ 


/*
void SuitsContainerClass::setContainerSize(SuitsContainerSize_t size)
	{
	this->containerSize	= size;
//	this->container		= (SuiteInstance*)MemoryManager.allocate (size * sizeof(SuiteInstance));
	this->container		= new SuitTemplateInstance[size];
	}
*/
void SuitsContainerClass::RegisterNew(SuitTemplateInstance* s)
	{
	if (this->container == NULL)
		{
		this->container	= s;
		}
	else
		{
		this->container->AddNode(s);
		}
	this->containerSize++;
	}
SuitID_t SuitsContainerClass::getRegisteredSuitsNum(void)
	{
	return this->containerSize;
	}
SuitName_t SuitsContainerClass::GetSuitName(SuitID_t SID)
	{
	return this->getSuiteInstance(SID)->GetName();
	}
SuitTemplateInstance* SuitsContainerClass::getSuiteInstance(const SuitID_t SID)
	{
	return static_cast<SuitTemplateInstance*>(this->GetNode(SID));
	/*
	if (this->containerSize == 0)
		{
		TODO("if 0");
		//return (SuiteInstance)NULL;
		}
	if (suiteID > this->containerSize)
		{
		return &this->container[0];
		}
	return &this->container[suiteID];
	*/
	}
SuitTemplateInstance* SuitsContainerClass::GetContainer(void)
	{
	return this->container;
	}