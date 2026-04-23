class SurvivalSkill
{
    private const float NEED_THRESHOLD = 1500.0; 

    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. САНИТАРНЫЙ КОНТРОЛЬ: Слив опасных жидкостей (кроме чая и супа)
        CheckAndPurgeUnsafeLiquids(bot);

        // 2. Проверка Жажды
        if (bot.GetStatWater().Get() < NEED_THRESHOLD)
        {
            ProcessConsumption(bot, "WaterBottle"); // Пьем только из проверенной тары
            return; 
        }

        // 3. Проверка Голода
        if (bot.GetStatEnergy().Get() < NEED_THRESHOLD)
        {
            Edible_Base food = Edible_Base.Cast(bot.GetInventory().FindEntityInInventory("Edible_Base"));
            if (food)
            {
                ProcessConsumption(bot, food.GetType());
            }
            else if (HasItem(bot, "PeachesCan") && HasItem(bot, "CanOpener"))
            {
                OpenAndEat(bot, "PeachesCan");
            }
        }
    }

    private void CheckAndPurgeUnsafeLiquids(ExpansionAIBase bot)
    {
        array<EntityAI> items = new array<EntityAI>;
        bot.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        foreach (EntityAI item : items)
        {
            ItemBase container = ItemBase.Cast(item);
            // Если это тара, в ней есть жидкость и это НЕ пустая бутылка
            if (container && container.IsLiquidContainer() && container.GetQuantity() > 0)
            {
                // ИСКЛЮЧЕНИЯ: Не сливаем чай (горячий) или суп (в кастрюле)
                if (container.GetTemperature() > 30) continue; 

                // ПРОВЕРКА: Если вода "дикая" (не верифицирована ботом как чистая)
                if (!IsWaterVerifiedClean(container))
                {
                    Print("[AN_NEKRASOV_82] Подозрительная вода в " + container.GetType() + ". Сливаю для безопасности.");
                    bot.TakeItemToHands(container);
                    bot.StartAction(ActionEmptyBottleBase); 
                }
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

        // ПРОВЕРКА №2: На сырое мясо
        if (item.IsInherited(Meat_Base) && !item.IsFoodCooked())
        {
            Print("[AN_NEKRASOV_82] Мясо сырое. Нужна жарка.");
            return; 
        }

        if (bot.GetHumanInventory().CanAddEntityInHands(item))
        {
            bot.TakeItemToHands(item);
            if (item.IsInherited(WaterBottle))
                bot.StartAction(ActionConsume);
            else
                bot.StartAction(ActionEat);
        }
    }

    private bool IsWaterVerifiedClean(ItemBase container)
    {
        // Здесь логика метки: бот считает воду чистой только если сам её набрал из Well или вскипятил
        // Вся найденная в мире вода по умолчанию не имеет этой метки
        return container.IsItemClean(); 
    }

    private bool HasItem(ExpansionAIBase bot, string className)
    {
        return bot.GetInventory().FindEntityInInventory(className) != null;
    }

    private void OpenAndEat(ExpansionAIBase bot, string food)
    {
        Print("[AN_NEKRASOV_82] Пытаюсь открыть консервы...");
        bot.TakeItemToHands(food);
    }
}
