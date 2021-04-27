class PlayerInterface
	{
	public:
//		virtual void DealDamage(DamageValue_t value, DamageSource_t damageSrc, DamageClass::AGGRESSOR_SOURCE aggressorSrc)	= 0;
		virtual void DealDamage(DamageClass Damage)         = 0;
		virtual void Revive(void)                           = 0;
		virtual bool IsDead(void)                           = 0;
		virtual bool IsAlive(void)                          = 0;
		virtual void Kill(DamageSource_t damageSrc)         = 0;
		virtual PlayerHealth_t GetCurrentHealth(void)       = 0;
		virtual PlayerHealth_t GetMaxHealth(void)           = 0;
		virtual Percent_t GetHealthPercent(void)            = 0;
	protected:
	private:
		virtual void SetHealth(PlayerHealth_t value)        = 0;
		virtual void HealthDecrase(PlayerHealth_t value)    = 0;
		virtual void Die(void)                              = 0;
	};