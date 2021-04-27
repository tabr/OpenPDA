// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
void Class_HAL::IOInit(void)
{
this->EnvironmentRarioModule.IOInit();
}
void Class_HAL::HardwareInitialization(void)
{
this->EnvironmentRarioModule.HardwareInitialization();
}
Interface_Driver_Clock* Class_HAL::GetClock(void)
{
return this->Clock;
}
Class_HAL::Class_HAL(Interface_Driver_Clock* c)
{
this->Clock  = c;
}
