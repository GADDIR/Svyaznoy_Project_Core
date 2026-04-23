class SurvivalSkill
{
    // Пороги срабатывания инстинктов (30% от максимума)
    private const float NEED_THRESHOLD = 1500.0; 

    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot) return;

        // 1. Проверка Жажды
        if (bot.GetStatWater().Get() < NEED_THRESHOLD)
        {
            UseItem(bot, "WaterBottle");
            return; // Прерываем цикл, чтобы он сфокусировался на питье
        }

        // 2. Проверка Голода
        if (bot.GetStatEnergy().Get() < NEED_THRESHOLD)
        {
            // Сначала едим яблоко, если оно есть
            if (HasItem(bot, "Apple"))
            {
                UseItem(bot, "Apple");
            }
            // Если яблок нет, переходим к консервам (но помним про открывалку!)
            else if (HasItem(bot, "PeachesCan") && HasItem(bot, "CanOpener"))
            {
                OpenAndEat(bot, "PeachesCan");
            }
        }
    }

    private bool HasItem(ExpansionAIBase bot, string className)
    {
        return bot.GetInventory().FindEntityInInventory(className) != null;
    }

    private void UseItem(ExpansionAIBase bot, string className)
    {
        EntityAI item = bot.GetInventory().FindEntityInInventory(className);
        if (item && bot.GetHumanInventory().CanAddEntityInHands(item))
        {
            bot.TakeItemToHands(item);
            // Запуск стандартного действия использования предмета
            bot.StartAction(ActionConsume); 
        }
    }

    private void OpenAndEat(ExpansionAIBase bot, string food)
    {
        // Логика: взять открывалку -> открыть банку -> съесть
        // Это более сложный процесс, который требует последовательности анимаций
        Print("[AN_NEKRASOV_82] Пытаюсь открыть консервы...");
        bot.TakeItemToHands(food);
        // Здесь в будущем добавим вызов ActionOpenCan
    }
}

