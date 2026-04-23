class SurvivalSkill
{
    private const float NEED_THRESHOLD = 1500.0; 

    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Проверка Жажды
        if (bot.GetStatWater().Get() < NEED_THRESHOLD)
        {
            ProcessConsumption(bot, "WaterBottle");
            return; 
        }

        // 2. Проверка Голода
        if (bot.GetStatEnergy().Get() < NEED_THRESHOLD)
        {
            // Ищем любую еду (фрукты, овощи, грибы)
            Edible_Base food = Edible_Base.Cast(bot.GetInventory().FindEntityInInventory("Edible_Base"));
            if (food)
            {
                ProcessConsumption(bot, food.GetType());
            }
            // Если еды нет, пробуем открыть консервы
            else if (HasItem(bot, "PeachesCan") && HasItem(bot, "CanOpener"))
            {
                OpenAndEat(bot, "PeachesCan");
            }
        }
    }

    private void ProcessConsumption(ExpansionAIBase bot, string className)
    {
        EntityAI item = bot.GetInventory().FindEntityInInventory(className);
        if (!item) return;

        // ПРОВЕРКА №1: На гниль (Rotten)
        if (item.GetHealthLevel() >= 4 || item.IsRuined())
        {
            Print("[AN_NEKRASOV_82] Продукт " + className + " сгнил. Выбрасываю.");
            bot.PredictiveDropEntity(item); 
            return;
        }

        // ПРОВЕРКА №2: На сырое мясо (Защита от сальмонеллеза)
        if (item.IsInherited(Meat_Base) && !item.IsFoodCooked())
        {
            Print("[AN_NEKRASOV_82] Мясо сырое. Есть нельзя, нужно пожарить.");
            // Здесь сработает навык CookingSkill
            return; 
        }

        // Если безопасно — едим/пьем
        if (bot.GetHumanInventory().CanAddEntityInHands(item))
        {
            bot.TakeItemToHands(item);
            if (item.IsInherited(WaterBottle))
                bot.StartAction(ActionConsume);
            else
                bot.StartAction(ActionEat);
        }
    }

    private bool HasItem(ExpansionAIBase bot, string className)
    {
        return bot.GetInventory().FindEntityInInventory(className) != null;
    }

    private void OpenAndEat(ExpansionAIBase bot, string food)
    {
        Print("[AN_NEKRASOV_82] Пытаюсь открыть консервы...");
        bot.TakeItemToHands(food);
        // В будущем здесь вызов ActionOpenCan через скрипт
    }
}
