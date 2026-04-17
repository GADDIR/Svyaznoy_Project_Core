// Модуль №74: Агро-Рефлексия (Эпоха Анны 1928)
modded class PlayerBase
{
    // Слушаем завершение действий с землей и растениями
    override void OnActionEndServer(ActionData action_data)
    {
        super.OnActionEndServer(action_data);

        // Проверяем типы действий: вскапывание, посадка, полив
        if (IsAgroAction(action_data.m_Action))
        {
            GenerateNekrasovAgroThought();
        }
    }

    bool IsAgroAction(ActionBase action)
    {
        // Проверка на принадлежность к садоводству
        return action.Type() == ActionDigGardenPlot || action.Type() == ActionPlantSeed || action.Type() == ActionWaterPlant;
    }

    void GenerateNekrasovAgroThought()
    {
        float annaWeight = GetMemoryFocus().GetWeight(1928);
        
        if (annaWeight > 0.5) // Если связь с Анной крепка
        {
            TStringArray agroPhrases = {
                "Земля-матушка всё стерпит, всех прокормит...",
                "Положишь семечко — вынешь жизнь.",
                "Руки в земле, а душа в небесах.",
                "Трудись, и горе отступит. Земля тишину любит."
            };
            
            SendToMumble(agroPhrases.GetRandomElement());
            
            // Скрытый бонус: небольшой реген стамины за мирный труд
            if (GetStaminaHandler())
                GetStaminaHandler().SyncStamina(5);
        }
    }
}

