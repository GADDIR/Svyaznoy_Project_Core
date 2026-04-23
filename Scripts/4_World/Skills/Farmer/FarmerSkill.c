class FarmerSkill
{
    // Основной метод запуска процесса
    void OnUpdate(ExpansionAIBase bot)
    {
        // Проверка: работает только для Алексея Николаевича
        if (bot.GetIdentityName() != "AN_NEKRASOV_82") return;

        ItemBase itemInHands = ItemBase.Cast(bot.GetHumanInventory().GetEntityInHands());
        
        // Если в руках мотыга — ищем место под грядку
        if (itemInHands && itemInHands.IsInherited(Hoe))
        {
            TryStartFarming(bot);
        }
    }

    private void TryStartFarming(ExpansionAIBase bot)
    {
        vector pos = bot.GetPosition();
        string surfaceType;
        GetGame().SurfaceGetType(pos, pos, surfaceType);

        // Копаем только там, где растет трава или есть земля
        if (surfaceType.Contains("grass") || surfaceType.Contains("dirt"))
        {
            if (!IsAreaOccupied(pos))
            {
                // Имитация создания грядки
                GetGame().CreateObjectEx("GardenPlot", pos, ECE_PLACE_ON_SURFACE);
                
                // Запуск анимации копания (ActionDigGardenPlot)
                bot.StartCommand_Action(DayZPlayerConstants.CMD_ACTIONFB_DIGMANI, DayZPlayerConstants.STANCE_ERECT);
            }
        }
    }

    private bool IsAreaOccupied(vector pos)
    {
        array<Object> objects = new array<Object>;
        GetGame().GetObjectsAtPosition3D(pos, 2.0, objects, null);
        foreach (Object obj : objects)
        {
            if (obj.IsInherited(GardenPlot)) return true;
        }
        return false;
    }
}

