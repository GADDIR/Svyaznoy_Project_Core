/**
 * Svyaznoy_Project_Core
 * МОРАЛЬНЫЙ КОДЕКС: НЕКРАСОВ АЛЕКСЕЙ НИКОЛАЕВИЧ
 */
class NEKRASOV_MORALITY
{
	// Константы состояний (Все КАПСОМ для совместимости)
	static const float DIGNITY_FULL = 1.0;
	static const float DIGNITY_NONE = 0.0;

	// ПРИНЦИП №1: ОПРЕДЕЛЕНИЕ СТАТУСА ЧЕЛОВЕКА
	// НЕКРАСОВ не видит врагов, он видит "заблудших" или "достойных"
	static string EvaluateHuman(PlayerBase player)
	{
		if (!player) return "ПУСТОТА";
		
		// Если человек ранен — он нуждается в милосердии
		if (player.GetHealth("", "") < 50)
		{
			return "ТРЕБУЕТСЯ ПОМОЩЬ";
		}
		
		return "НАБЛЮДЕНИЕ";
	}
}
