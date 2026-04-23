class ButcherSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Проверка: Есть ли рядом убитое животное?
        EntityAI deadAnimal = GetNearestDeadAnimal(bot, 3.0);
        if (!deadAnimal) return;

        // 2. Проверка инструмента: Есть ли нож в руках или в инвентаре?
        ItemBase knife = GetKnife(bot);
        if (knife)
        {
            StartButchering(bot, deadAnimal, knife);
        }
    }

    private EntityAI GetNearestDeadAnimal(ExpansionAIBase bot, float range)
    {
        array<Object> objects = new array<Object>;
        GetGame().GetObjectsAtPosition3D(bot.GetPosition(), range, objects, null);
        
        foreach (Object obj : objects)
        {
            Animal_Base animal = Animal_Base.Cast(obj);
            if (animal && !animal.IsAlive()) return animal;
        }
        return null;
    }

    private ItemBase GetKnife(ExpansionAIBase bot)
    {
        // Ищем любой нож (кухонный, охотничий, боевой)
        return ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Knife_Base"));
    }

    private void StartButchering(ExpansionAIBase bot, EntityAI animal, ItemBase knife)
    {
        // Берем нож в руки, если он еще не там
        if (bot.GetHumanInventory().GetEntityInHands() != knife)
        {
            bot.TakeItemToHands(knife);
        }

        // Запуск анимации разделки
        if (!bot.IsActionRunning())
        {
            bot.StartAction(ActionSkinning);
            Print("[AN_NEKRASOV_82] Разделываю добычу...");
        }
    }
}

