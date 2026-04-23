class AdvancedCookingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || !HasRawFood(bot)) return;

        // Ищем ближайший источник тепла
        Object heatSource = FindBestHeatSource(bot);
        
        if (heatSource)
        {
            StartCookingProcess(bot, heatSource);
        }
    }

    private void StartCookingProcess(ExpansionAIBase bot, Object source)
    {
        // Логика адаптации под объект:
        if (source.IsInherited(Fireplace)) {
            // Обычный костер - используем палку/треногу
            CookOnFireplace(bot, source);
        }
        else if (source.IsInherited(BarrelHoles_ColorBase)) {
            // Бочка-печь/Мангал - ставим кастрюлю сверху
            CookOnBarrel(bot, source);
        }
        else if (source.GetType().Contains("Oven") || source.GetType().Contains("Fireplace_Indoor")) {
            // Домашняя печь или камин - используем внутренние слоты
            CookIndoor(bot, source);
        }
    }

    private bool HasRawFood(ExpansionAIBase bot) {
        return bot.GetInventory().FindEntityInInventory("Meat_Base") != null;
    }

    private Object FindBestHeatSource(ExpansionAIBase bot) {
        // Поиск в радиусе 3 метров: Печь > Бочка > Костер
        return bot.GetNearestObject("HouseWithFireplace", 3.0); 
    }
}

