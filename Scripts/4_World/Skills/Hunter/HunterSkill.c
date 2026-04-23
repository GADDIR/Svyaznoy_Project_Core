class HunterSkill
{
    private const float SCAN_RADIUS = 150.0; // Радиус поиска дичи

    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot) return;

        // 1. Условие: Охота начинается, только если в руках есть оружие
        Weapon weapon = Weapon.Cast(bot.GetHumanInventory().GetEntityInHands());
        if (!weapon) return;

        // 2. Если бот голоден, приоритет охоты вырастает
        if (bot.GetStatEnergy().Get() < 3000)
        {
            SearchAndHunt(bot, weapon);
        }
    }

    private void SearchAndHunt(ExpansionAIBase bot, Weapon weapon)
    {
        EntityAI targetAnimal = GetNearestAnimal(bot, SCAN_RADIUS);
        
        if (targetAnimal)
        {
            float distance = vector.Distance(bot.GetPosition(), targetAnimal.GetPosition());

            // 3. Логика сближения
            if (distance > 30.0)
            {
                // Скрытное сближение (на корточках, если позволяет скрипт)
                bot.GetNavigation().SetTarget(targetAnimal.GetPosition(), ExpansionHAL_Mode.WALK);
            }
            else
            {
                // 4. Прицеливание и выстрел
                bot.GetTargetManager().SetTarget(targetAnimal);
                
                // Если пистолет с глушителем (MK2), бот стреляет увереннее
                if (weapon.IsInherited(MKII_Pistol))
                {
                    bot.StartAction(ActionShootTarget);
                }
            }
        }
    }

    private EntityAI GetNearestAnimal(ExpansionAIBase bot, float range)
    {
        // Поиск объектов класса Animal_Base (куры, кабаны, косули)
        array<Object> objects = new array<Object>;
        GetGame().GetObjectsAtPosition3D(bot.GetPosition(), range, objects, null);
        
        foreach (Object obj : objects)
        {
            if (obj.IsInherited(Animal_Base) && obj.IsAlive())
            {
                return EntityAI.Cast(obj);
            }
        }
        return null;
    }
}

