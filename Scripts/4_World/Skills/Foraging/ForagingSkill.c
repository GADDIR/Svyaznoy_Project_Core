class ForagingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Голод ниже 4000
        if (bot.GetStatEnergy().Get() < 4000)
        {
            SearchForNatureFood(bot);
        }
    }

    private void SearchForNatureFood(ExpansionAIBase bot)
    {
        array<Object> objects = new array<Object>;
        GetGame().GetObjectsAtPosition3D(bot.GetPosition(), 5.0, objects, null);

        foreach (Object obj : objects)
        {
            Edible_Base food = Edible_Base.Cast(obj);
            if (food && IsNatureFood(food))
            {
                // ВАРИАНТ: Проверка на гниль (Rotten = 4)
                if (food.GetHealthLevel() >= 4) 
                {
                    // Просто пропускаем и логируем для админки
                    Print("[AN_NEKRASOV_82] Обнаружена гниль в " + food.GetType() + ". Прохожу мимо.");
                    continue; 
                }

                CollectFood(bot, food);
                return;
            }
        }
    }

    private bool IsNatureFood(Edible_Base food)
    {
        string type = food.GetType();
        return (type.Contains("Mushroom") || type.Contains("Apple") || 
                type.Contains("Pear") || type.Contains("Plum") || 
                type.Contains("Sambucus") || type.Contains("Canina"));
    }

    private void CollectFood(ExpansionAIBase bot, Edible_Base food)
    {
        // Дополнительная проверка перед физическим контактом
        if (food.IsRuined()) return; 

        if (bot.GetInventory().CanAddEntityIntoInventory(food))
        {
            bot.TakeEntityToInventory(InventoryMode.PREDICTIVE, food);
            Print("[AN_NEKRASOV_82] Нашел чистый продукт: " + food.GetType());
        }
        else
        {
            // Если рюкзак полон — ест сразу, но только если не гнилое
            bot.TakeItemToHands(food);
            bot.StartAction(ActionEat);
        }
    }
}
