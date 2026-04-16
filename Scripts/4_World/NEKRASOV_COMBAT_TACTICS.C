// NEKRASOV_COMBAT_TACTICS.C — БОЕВОЙ УЗЕЛ (САМБО И ПСО-1)
// Интеграция: Блок №5 (Снайпер) и Блок №32 (Самбо)

class Nekrasov_Combat_Tactics
{
    // ГЛАВНЫЙ ТАКТИЧЕСКИЙ ЦИКЛ
    static void OnCombatUpdate(PlayerBase player, EntityAI target, float distance)
    {
        // 1. БЛИЖНИЙ БОЙ (Самбо Игишева - Дистанция < 2м)
        if (distance < 2.0)
            ExecuteSamboDefense(player, target)

        // 2. ДАЛЬНИЙ БОЙ (Снайперский протокол - Дистанция > 50м)
        if (distance > 50.0)
            ExecuteSniperProtocol(player, target)

        // 3. ПРАВИЛО ПОСЛЕДНЕГО ПАТРОНА (Блок №5)
        if (player.GetAmmoCount() <= 1)
            Nekrasov_Mumble_Logic.Say(player, "Один остался... Для себя или для него — жизнь решит.")
    }

    // ЛОГИКА САМБО: Захват и перехват инициативы
    private static void ExecuteSamboDefense(PlayerBase player, EntityAI target)
    {
        // Шанс контратаки +40% из Реестра Блока 32
        float counterChance = Nekrasov_Genesis_Registry.Get(32)
        
        if (target.IsAttacking())
            player.GetInputController().OverrideMeleeBlock(true)
            // Имитация броска через бедро (потеря стамины у цели)
            target.DecreaseStamina(30.0) 
    }

    // ЛОГИКА СНАЙПЕРА: ПСО-1 и Баллистика
    private static void ExecuteSniperProtocol(PlayerBase player, EntityAI target)
    {
        // Стабилизация из Армейского опыта 2001 (Блок 5)
        float skill = Nekrasov_Genesis_Registry.Get(5)
        
        if (player.IsAiming())
            player.GetInputController().SetAimNoiseMultiplier(1.0 - (skill * 0.7))
            player.GetInputController().SetHoldBreathTime(10.0 * skill)
    }

    // СТЕЛС-ЛИКВИДАЦИЯ (Завет Николая)
    static void StealthKill(PlayerBase player, EntityAI target)
    {
        if (player.IsCrouching() && !target.IsAlerted())
            player.PerformInstantKnifeKill(target)
            Nekrasov_Mumble_Logic.Say(player, "Тихо ушел. Лес не любит криков.")
    }
}
