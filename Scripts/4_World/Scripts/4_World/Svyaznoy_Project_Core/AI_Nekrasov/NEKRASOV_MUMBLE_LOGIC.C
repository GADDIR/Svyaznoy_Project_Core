// NEKRASOV_MUMBLE_LOGIC.C — РЕЧЕВОЙ МОДУЛЬ И ВНУТРЕННИЙ МОНОЛОГ
// Интеграция с Реестром Генезиса и Буфером Памяти

class Nekrasov_Mumble_Logic
{
    // Главный метод: Сказать фразу в зависимости от ситуации
    static void Say(PlayerBase player, string situation)
    {
        string phrase = ""
        
        // 1. Блок №1: Гигиенический террор (Анна Петровна)
        if (situation == "DIRTY_HANDS")
            phrase = "Мама Анна говорила: грязь — союзник смерти. Сначала мойся."

        // 2. Блок №31: Дедовская школа (Николай)
        if (situation == "RADIO_TUNING")
            phrase = "Чуть левее... вот теперь чистый пошел. Поет, родная. Как дед учил."
        
        if (situation == "WEAPON_CLEAN")
            phrase = "Инструмент — твои вторые руки. Николай халтуры не прощал."

        // 3. Блок №32: Самбо (Мухаммед Игишев)
        if (situation == "COMBAT_CLINCH")
            phrase = "Дыши ровнее, бактерия. Центр тяжести потерял — считай, проиграл."

        // 4. Блок №35/36: Тайное Кредо (Адвентизм)
        if (situation == "SEE_PORK")
            phrase = "Дед свинины в дом не вносил, и я не стану. Отойди, нечистое."

        // 5. Блок №8: Банов (Радиомолчание)
        if (situation == "LONG_SILENCE" && player.IsLone())
            phrase = "Эфир молчит... В Гатчине сейчас, небось, тоже дожди..."

        // Вывод в чат/голос (Mumble)
        if (phrase != "")
            player.SayMumble(phrase)
    }
}
