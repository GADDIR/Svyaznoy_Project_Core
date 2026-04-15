// ЗОЛОТОЙ СТАНДАРТ А.Н. НЕКРАСОВА (12 КЛЮЧЕВЫХ УЗЛОВ ЛИЧНОСТИ)
// Основано на ревизии Генезиса (Блоки 1-8)

class AN_GoldenStandard
{
    // --- ЛОГИКА ВЫСШЕГО ПРИОРИТЕТА (ГЛУБОКАЯ ПАМЯТЬ) ---
    static const bool  m_L_HygieneTerror     = true // Гатчина 1982: Грязь = Смерть
    static const float m_L_SocialNeed        = 0.0  // Детсад: Потребность в общении отсутствует
    static const bool  m_L_AuthorityDistrust = true // Отчисление: Недоверие к авторитетам
    static const bool  m_L_RadioSilence      = true // 2021: Тишина — залог выживания

    // --- ТЕХНИЧЕСКИЙ И БОЕВОЙ ПОТЕНЦИАЛ (ПОСТОЯННАЯ ПАМЯТЬ) ---
    static const float m_P_BallisticScale    = 1.0  // Школа: Мир как математическая формула
    static const bool  m_P_ResilienceMode    = true // Диплом: Принцип вечной автономности
    static const float m_P_MapMastery        = 1.0  // Банов 2021: Знание каждого кабеля в Секторе

    // --- ОПЕРАТИВНЫЕ МНОЖИТЕЛИ (ВРЕМЕННАЯ ПАМЯТЬ) ---
    static const float m_O_SignalIntuition   = 2.0  // Радиожурнал: Рация как орган чувств
    static const float m_O_SystemicVision    = 1.5  // Университет: Видит систему, а не детали
    static const float m_O_SoloEfficiency    = 2.0  // Работа: Один в поле — хозяин

    // --- РЕФЛЕКСЫ И ТАКТИКА (ЭКСТРЕННАЯ ПАМЯТЬ) ---
    static const float m_E_SVD_Expertise     = 1.0  // ВУС Снайпер: Выстрел как инстинкт
    static const float m_E_Scan360           = 2.0  // Армия: Осмотр горизонта каждые 15 сек

    // ГЛАВНЫЙ ФИЛЬТР ПОВЕДЕНИЯ
    static bool ValidateAction(PlayerBase player, string actionType)
    {
        // Пример работы стандарта: запрет на еду грязными руками
        if (actionType == "EAT" && player.GetStatDirtyHands().Get() > 0)
            return false
        
        // Пример: запрет на лишний шум, если активен режим тишины
        if (m_L_RadioSilence && player.IsMakingTooMuchNoise())
            return false

        return true
    }
}
