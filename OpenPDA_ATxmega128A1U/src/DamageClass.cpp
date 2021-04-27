// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * DamageClass.cpp
 *
 * Created: 09.01.2016 2:24:09
 *  Author: tabr
 */ 
bool DamageClass::isDamageSourceValid(DamageSource_t dmg_value)
	{
	return ((dmg_value > 0) && (dmg_value <= GameCFG.GetDamageSourceNum()));
	}



DamageSourceContainerClass::DamageSourceContainerClass(void)
	{
	this->Constructor(GameCFG.GetDamageSourceNum());
	}
DamageSourceContainerClass::DamageSourceContainerClass(DamageSourceCounter_t num)
	{
	this->Constructor(num);
	}
void DamageSourceContainerClass::Constructor(DamageSourceCounter_t num)
	{
	this->containerSize	= num + 1;
	this->container	= new DamageDefenceValue_t[this->containerSize];
	memset(this->container, 0, this->containerSize);
	}
DamageDefenceValue_t DamageSourceContainerClass::GetDefenceFrom(DamageSource_t src)
	{
	return this->container[src];
	}
void DamageSourceContainerClass::SetDefenceFrom(DamageSource_t src, DamageDefenceValue_t value)
	{
	this->container[src]	= value;
	}
