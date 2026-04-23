class GreenPathSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // Если бот перемещается к цели (торговец, схрон, огород)
        if (bot.GetNavigation().IsMoving())
        {
            AdjustRouteToCover(bot);
        }
    }

    private void AdjustRouteToCover(ExpansionAIBase bot)
    {
        vector currentPos = bot.GetPosition();
        string surfaceType;
        GetGame().SurfaceGetType(currentPos[0], currentPos[2], surfaceType);

        // 1. Избегание дорог: Если под ногами асфальт или гравий — ускоряемся до спринта
        if (surfaceType.Contains("asphalt") || surfaceType.Contains("gravel") || surfaceType.Contains("road"))
        {
            bot.GetNavigation().SetMovementSpeed(ExpansionHAL_MovementSpeed.SPRINT);
            Print("[AN_NEKRASOV_82] Я на открытой дороге. Ухожу в зелёнку!");
        }
        // 2. Лесной коридор: Если рядом лес (Forest) — бот строит путь через него
        else if (surfaceType.Contains("forest") || surfaceType.Contains("grass"))
        {
            bot.GetNavigation().SetMovementSpeed(ExpansionHAL_MovementSpeed.WALK); // Двигаемся тише
        }
    }
}

