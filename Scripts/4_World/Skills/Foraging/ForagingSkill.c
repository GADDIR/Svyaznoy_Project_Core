class ForagingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Бот идет или стоит в лесу/саду + он слегка проголодался
        if (bot.GetStatEnergy().Get() < 4000)
        {
            SearchForNatureFood(bot);
        }
    }

    private void SearchForNatureFood(ExpansionAIBase bot)
    {
        // Ищем объекты в радиусе 3-5 метров на земле
        array<Object> objects = new array<Object>;
        GetGame().GetObjectsAtPosition3D(bot.GetPosition(), 5.0, objects, null);

        foreach (Object obj : objects)
        {
            Edible_Base food = Edible_Base.Cast(obj);
            if (food && IsNatureFood(food))
            {
                // Проверка состояния: Некрасов не берет гнилое (Rotten)
                if (food.GetHealthLevel() < 4) 
                {
                    CollectFood(bot, food);
                    return;
                }
            }
        }
    }

    private bool IsNatureFood(Edible_Base food)
    {
        // Список того, что Мэверик узнает как еду
        string type = food.GetType();
        return (type.Contains("Mushroom") || type.Contains("Apple") || 
                type.Contains("Pear") || type.Contains("Plum") || 
                type.Contains("Sambucus") || type.Contains("Canina"));
    }

    private void CollectFood(ExpansionAIBase bot, Edible_Base food)
    {
        // Логика: Поднять и либо съесть сразу, либо убрать в карман
        if (bot.GetInventory().CanAddEntityIntoInventory(food))
        {
            bot.TakeEntityToInventory(InventoryMode.PREDICTIVE, food);
            Print("[AN_NEKRASOV_82] Нашел дикоросы: " + food.GetType());
        }
        else
        {
            bot.TakeItemToHands(food);
            bot.StartAction(ActionEat);
        }
    }
}

