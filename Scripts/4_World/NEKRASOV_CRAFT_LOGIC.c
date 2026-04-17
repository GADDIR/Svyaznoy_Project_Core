/**
 * NEKRASOV_CRAFT_LOGIC.c
 * Логика ремесла и технического творчества Алексея Николаевича.
 * ПРИНЦИП: "Сделано на совесть. По-нашему."
 */

class NEKRASOV_CRAFT_LOGIC
{
    // 1. ПРОВЕРКА ВОЗМОЖНОСТИ (Связь с Золотым Стандартом)
    static bool CAN_EXECUTE_CRAFT(PlayerBase player, string item_name)
    {
        // Если предмет — "хлам" или не соответствует чести, Золотой Стандарт его блокирует
        if (!NEKRASOV_GoldenStandard.VALIDATE_ITEM_TYPE(item_name))
        {
            // Некрасов не тратит время на то, что ниже его достоинства
            return false;
        }
        return true;
    }

    // 2. БОНУС КАЧЕСТВА (Связь с Генезисом 1982)
    static void APPLY_QUALITY_BONUS(ItemBase created_item)
    {
        // Профессионализм 1994 года и Генезис 1982 дают бонус к прочности
        // Вещь должна служить долго.
        float bonus = 0.2; // +20% к износостойкости
        created_item.SetHealth01("", "", created_item.GetHealth01("", "") + bonus);
        
        Print("[NEKRASOV_CRAFT] Применен стандарт качества: Износостойкость повышена.");
    }

    // 3. РЕФЛЕКСИЯ ПОСЛЕ ТРУДА (Связь с Mumble)
    static void ON_CRAFT_COMPLETE(PlayerBase player, string item_name)
    {
        // После успешного крафта Фокус смещается на удовлетворение трудом
        if (player.GetMemoryFocus().GetLegacyWeight1982() > 0.5)
        {
            // Мысли о том, что вещь будет служить исправно
            NEKRASOV_Mumble_Logic.Say("Работа любит порядок. Служить будет долго.");
        }
    }
}
