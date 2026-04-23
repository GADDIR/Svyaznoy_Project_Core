class AdvancedForagingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Поиск дикоросов в радиусе 10 метров
        SearchForNatureFood(bot);

        // 2. Логика сушки: если в инвентаре есть свежие грибы/фрукты и рядом костер
        if (HasRawNatureFood(bot) && IsFireActive(bot))
        {
            StartDryingProcess(bot);
        }
    }

    private void SearchForNatureFood(ExpansionAIBase bot)
    {
        // Бот ищет: Яблоки, Груши, Сливы, Шиповник, Бузину и 7 видов съедобных грибов
        array<Object> objects = new array<Object>;
        GetGame().GetObjectsAtPosition3D(bot.GetPosition(), 10.0, objects, null);

        foreach (Object obj : objects)
        {
            Edible_Base food = Edible_Base.Cast(obj);
            if (food && IsValuableForage(food))
            {
                // Игнорируем гнилое и ядовитое
                if (food.GetHealthLevel() < 4 && !IsPoisonous(food))
                {
                    bot.TakeEntityToInventory(InventoryMode.PREDICTIVE, food);
                    Print("[AN_NEKRASOV_82] Нашел ценный дар леса: " + food.GetType());
                }
            }
        }
    }

    private void StartDryingProcess(ExpansionAIBase bot)
    {
        // Навык ветерана: положить гриб в слот коптильни костра (Smoking Slot)
        // Сушеный гриб — лучший перекус туриста.
        Print("[AN_NEKRASOV_82] Заготавливаю сухофрукты и сушеные грибы на зиму.");
    }

    private bool IsValuableForage(Edible_Base food) {
        string type = food.GetType();
        return type.Contains("Mushroom") || type.Contains("Apple") || type.Contains("Pear") || type.Contains("Plum") || type.Contains("Canina") || type.Contains("Sambucus");
    }

    private bool IsPoisonous(Edible_Base food) {
        return food.GetType().Contains("Amanita") || food.GetType().Contains("Chlorophyllum");
    }
}

