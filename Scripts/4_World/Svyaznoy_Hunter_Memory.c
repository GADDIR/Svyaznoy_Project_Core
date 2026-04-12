class Svyaznoy_Hunter_Memory
{
	void Svyaznoy_Hunter_Memory()
	{
		Print("[СВЯЗНОЙ-ОХОТА] Модуль загружен.");
	}

	static vector GetFishingPoint()
	{
		return "14344.6 558.8 5150.0";
	}

	static bool IsStealthRequired(float distToTarget)
	{
		if (distToTarget < 50.0)
		{
			return true;
		}
		return false;
	}

	static bool ShouldUseKnife(string weaponClass)
	{
		if (weaponClass == "CombatKnife" || weaponClass == "HuntingKnife")
		{
			return true;
		}
		return false;
	}
}
