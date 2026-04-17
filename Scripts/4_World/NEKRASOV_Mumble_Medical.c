// Модуль №72: Рефлексия Медицины (Эпоха Анны 1928)
modded class PlayerBase
{
	// Основной триггер на завершение лечения
	override void OnActionEndServer(ActionData action_data)
	{
		super.OnActionEndServer(action_data);
		
		// Если предмет в руках имеет медицинский тип
		if (action_data.m_MainItem && action_data.m_MainItem.IsMedicalItem())
		{
			GenerateNekrasovMedicalThought();
		}
	}

	void GenerateNekrasovMedicalThought()
	{
		// Получаем текущий вес эпохи 1928
		float annaWeight = GetMemoryFocus().GetWeight(1928);
		
		if (annaWeight > 0.6) // Если Анна доминирует в сознании
		{
			// Массив фраз Анны (Архаичный стиль)
			TStringArray annaPhrases = {
				"Потерпи, родненький, бог даст — утихнет...",
				"Рана чистая, как совесть, затянется скоро.",
				"Стежок к стежку, а жизнь — в узду.",
				"Трава лечит, а рука молитвой правит."
			};
			
			string selectedPhrase = annaPhrases.GetRandomElement();
			SendToMumble(selectedPhrase); // Отправка в систему рефлексии
		}
	}
};
