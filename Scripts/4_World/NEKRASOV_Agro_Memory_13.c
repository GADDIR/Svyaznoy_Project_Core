/*
    УЗЕЛ 76.V: СВЕТОВАЯ МАСКИРОВКА И РИСКИ
    Файл: NEKRASOV_Agro_Memory_13.c
    Связь: fire_stealth.md
    Назначение: Расчет заметности Очага и штрафы за демаскировку.
*/

modded class NEKRASOV_Agro_Memory
{
    // Уровни заметности из fire_stealth.md
    protected float m_NEKRASOV_StealthExposure;

    override void Init()
    {
        super.Init();
        m_NEKRASOV_StealthExposure = 0.0;
    }

    // Логика: Оценка безопасности огня
    // Согласно fire_stealth.md: открытый костер ночью = 100% риск.
    void NEKRASOV_AuditFireStealth(FireplaceBase fireplace)
    {
        if (!fireplace || !fireplace.IsBurning()) 
        {
            m_NEKRASOV_StealthExposure = 0.0;
            return;
        }

        float timeOfDay = GetGame().GetDayTime(); // Получаем время суток
        bool isNight = (timeOfDay < 6 || timeOfDay > 20);
        
        // Расчет демаскировки: Ночь + Открытый огонь = Максимальный риск
        if (isNight)
        {
            m_NEKRASOV_StealthExposure = 1.0;
            // Интеграция с Mumble: "Слишком светло. Эфир дрожит от моей неосторожности."
        }
        
        // Проверка типа (камин внутри дома безопаснее костра в поле)
        if (fireplace.IsIndoor())
        {
            m_NEKRASOV_StealthExposure *= 0.3; // Снижение риска в помещении
        }
    }

    // Влияние на Сеть Приютов (Узел 6): 
    // Если риск высокий — стабильность скрытого поста падает
    float NEKRASOV_GetStealthPenalty()
    {
        return m_NEKRASOV_StealthExposure;
    }
}
