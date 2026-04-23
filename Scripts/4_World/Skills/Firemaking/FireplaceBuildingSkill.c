class FireplaceBuildingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Нужно согреться/поесть, а готового костра нет
        if (NeedsFire(bot) && !bot.IsNearObject("Fireplace", 3.0))
        {
            BuildFireplace(bot);
        }
    }

    private void BuildFireplace(ExpansionAIBase bot)
    {
        // Выбор ОСНОВЫ (Fuel)
        ItemBase fuel = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("WoodenStick"));
        if (!fuel) fuel = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Firewood"));

        // Выбор РОЗЖИГА (Kindling) по приоритету (от дешевого к дорогому)
        ItemBase kindling = FindBestKindling(bot);

        if (fuel && kindling)
        {
            bot.TakeItemToHands(fuel);
            // Соединяем основу с розжигом
            bot.StartAction(ActionCreateFireplace); 
            Print("[AN_NEKRASOV_82] Собираю костер из " + fuel.GetType() + " и " + kindling.GetType());
        }
    }

    private ItemBase FindBestKindling(ExpansionAIBase bot)
    {
        // Список приоритетов розжига Алексея Николаевича:
        // 1. Кора (Bark) - бесплатно и бесконечно
        // 2. Бумага (Paper) - из распакованных коробок патронов
        // 3. Тряпка (Rag) - если много старой одежды
        // 4. Бинт (Bandage) - КРАЙНИЙ случай (если умирает от холода)

        ItemBase target;
        if (target = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Bark_Oak"))) return target;
        if (target = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Bark_Birch"))) return target;
        if (target = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Paper"))) return target;
        if (target = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Rag"))) return target;
        if (target = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("BandageDressing"))) return target;
        
        return null;
    }

    private bool NeedsFire(ExpansionAIBase bot) {
        return (bot.GetStatHeatComfort().Get() < 0 || bot.GetInventory().FindEntityInInventory("Meat_Base"));
    }
}

