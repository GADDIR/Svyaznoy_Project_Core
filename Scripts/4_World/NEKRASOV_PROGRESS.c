/**
 * Svyaznoy_Project_Core
 * ПРОГРЕСС И ЦЕЛИ ОБЪЕКТА: НЕКРАСОВ АЛЕКСЕЙ НИКОЛАЕВИЧ
 */
class NEKRASOV_PROGRESS
{
	// Текущие статусы выполнения (согласно PRT-QUEST-STRATEGY)
	static const int STATE_IDLE        = 0; // Ожидание цели
	static const int STATE_SEARCH      = 1; // Поиск достойных (Сбор информации)
	static const int STATE_MISSION     = 2; // Выполнение конкретной задачи
	static const int STATE_COMPLETED   = 3; // Цель достигнута

	// Переменные прогресса
	static int m_CurrentState = STATE_IDLE;
	static string m_LastObjective = "ИНИЦИАЛИЗАЦИЯ ЛИЧНОСТИ";

	// Метод фиксации этапа в Манифест
	static void SetState(int newState, string objective)
	{
		m_CurrentState = newState;
		m_LastObjective = objective;
		
		Print("[Svyaznoy_Project_Core] НЕКРАСОВ сменил вектор цели на: " + objective);
	}

	// Проверка: готов ли Некрасов давать задание игроку?
	static bool IsReadyToInteract()
	{
		return (m_CurrentState != STATE_MISSION);
	}
}
