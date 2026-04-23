class TentPlacementSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Поиск палатки в инвентаре (Гражданская, Средняя, Большая или Автомобильная)
        TentBase tent = TentBase.Cast(bot.GetInventory().FindEntityInInventory("TentBase"));
        
        if (tent && NeedsToPitchTent(bot, tent))
        {
            PitchTentLogic(bot, tent);
        }
    }

    private void PitchTentLogic(ExpansionAIBase bot, TentBase tent)
    {
        // 2. Выбор места (ровная поверхность и отсутствие препятствий)
        // Бот "понимает", что большую палатку нельзя ставить в густом лесу
        
        if (tent.CanPlaced(bot, bot.GetPosition()))
        {
            bot.TakeItemToHands(tent);
            
            // Запуск процесса установки
            bot.StartAction(ActionTogglePlaceObject); // Вход в режим размещения
            bot.StartAction(ActionPlaceObject);       // Установка
            
            // 3. После установки - ОБЯЗАТЕЛЬНО открыть входы (зипперы)
            bot.StartAction(ActionOpenTents); 
            
            Print("[AN_NEKRASOV_82] Устанавливаю палатку: " + tent.GetType());
        }
    }

    private bool NeedsToPitchTent(ExpansionAIBase bot, TentBase tent)
    {
        // Устанавливаем, если мы на базе и в радиусе 15м нет другой нашей палатки
        return bot.IsInSafeZone() && !bot.IsNearObject(tent.GetType(), 15.0);
    }
}

