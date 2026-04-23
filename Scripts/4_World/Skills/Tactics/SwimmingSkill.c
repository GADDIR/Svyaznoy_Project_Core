class SwimmingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Проверка глубины: если воды выше пояса — переходим в режим плаванья
        float waterDepth = GetGame().GetWaterDepth(bot.GetPosition());
        
        if (waterDepth > 1.2)
        {
            HandleSwimming(bot);
        }
    }

    private void HandleSwimming(ExpansionAIBase bot)
    {
        // 2. Убираем оружие (копье/арбалет) за спину, чтобы освободить руки
        if (bot.GetHumanInventory().GetEntityInHands() != null)
        {
            bot.StartAction(ActionStoreItemInInventory);
        }

        // 3. Контроль стамины: если стамина на исходе — бот не плывет на глубину
        if (bot.GetStatStamina().Get() < 10.0)
        {
            bot.GetNavigation().Stop(); // Замереть и держаться на воде (Tread Water)
            Print("[AN_NEKRASOV_82] Слишком устал, чтобы плыть. Отдыхаю на воде.");
        }
        else
        {
            bot.GetNavigation().SetMovementSpeed(ExpansionHAL_MovementSpeed.WALK); // Плывем тихо
            Print("[AN_NEKRASOV_82] Пересекаю водную преграду.");
        }
    }
}

