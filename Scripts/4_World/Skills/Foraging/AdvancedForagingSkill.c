class AdvancedForagingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Поиск: Сканируем землю (радиус 10м)
        SearchForNatureFood(bot);

        // 2. Заготовка: Если есть костер и свежие плоды — сушим их
        if (IsFireActive(bot))
        {
            StartDryingProcess(bot);
        }
    }

    private void SearchForNatureFood(ExpansionAIBase bot)
    {
        array<Object> objects = new array<Object>;
        GetGame().GetObjectsAtPosition3D(bot.GetPosition(), 10.0, objects, null);

        foreach (Object obj : objects)
        {
            Edible_Base food = Edible_Base.Cast(obj);
            if (food && IsValuableForage(food))
            {
                // Игнорируем гнилое (4) и ядовитое
                if (food.GetHealthLevel() < 4 && !IsPoisonous(food))
                {
                    if (bot.GetInventory().CanAddEntityIntoInventory(food))
                    {
                        bot.TakeEntityToInventory(InventoryMode.PREDICTIVE, food);
                        Print("[AN_NEKRASOV_82] Нашел " + food.GetType() + " в отличном состоянии.");
                    }
                }
            }
        }
    }

    private void StartDryingProcess(ExpansionAIBase bot)
    {
        // Ищем ближайший активный костер
        Fireplace fireplace = Fireplace.Cast(bot.GetNearestObject("Fireplace", 3.0));
        if (!fireplace || !fireplace.IsIgnited()) return;

        // Перебираем инвентарь в поисках свежих (Raw) дикоросов
        array<EntityAI> items = new array<EntityAI>;
        bot.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        foreach (EntityAI item : items)
        {
            Edible_Base food = Edible_Base.Cast(item);
            // Если еда свежая и подходит для сушки
            if (food && food.GetFoodStage() == FoodStageType.RAW && IsValuableForage(food))
            {
                // Пытаемся засунуть в слот Smoking (коптильня)
                if (fireplace.GetInventory().CanAddAttachment(food))
                {
                    bot.TakeItemToHands(food);
                    bot.StartAction(ActionAttach); 
                    Print("[AN_NEKRASOV_82] Поместил " + food.GetType() + " в коптильню для заготовки.");
                    return; // За раз кладем одну единицу, чтобы не спамить
                }
            }
        }
    }

    private bool IsValuableForage(Edible_Base food) {
        string type = food.GetType();
        return type.Contains("Mushroom") || type.Contains("Apple") || type.Contains("Pear") || 
               type.Contains("Plum") || type.Contains("Canina") || type.Contains("Sambucus");
    }

    private bool IsPoisonous(Edible_Base food) {
        // Защита от мухоморов и ложных грибов
        return food.GetType().Contains("Amanita") || food.GetType().Contains("Chlorophyllum");
    }

    private bool IsFireActive(ExpansionAIBase bot) {
        return bot.IsNearObject("Fireplace", 3.0);
    }
}
