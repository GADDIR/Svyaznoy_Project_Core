/*
    УЗЕЛ 76.E: АВАРИЙНОЕ УБЕЖИЩЕ
    Файл: NEKRASOV_Agro_Memory_15.c
    Связь: emergency_safehouse.md
    Назначение: Логика временных точек выживания при потере основной сети.
*/

modded class NEKRASOV_Agro_Memory
{
    protected bool m_NEKRASOV_IsEmergencyMode;
    protected vector m_NEKRASOV_LastEmergencyPoint;

    override void Init()
    {
        super.Init();
        m_NEKRASOV_IsEmergencyMode = false;
        m_NEKRASOV_LastEmergencyPoint = "0 0 0";
    }

    // Логика активации: Переход в режим "Аварийного выживания"
    // Если Синхронизация (Узел 10) ниже 0.2 — АН ищет Аварийное убежище
    void NEKRASOV_ActivateEmergencyProtocol(vector pos)
    {
        m_NEKRASOV_IsEmergencyMode = true;
        m_NEKRASOV_LastEmergencyPoint = pos;
        
        // Интеграция с Mumble: "Сеть потеряна. Ухожу на запасной узел."
    }

    // Протокол "Минимум": Ограничение комфорта
    // В аварийном убежище нельзя использовать Очаг (Узел 13) — слишком опасно
    override bool NEKRASOV_IsHearthReady()
    {
        if (m_NEKRASOV_IsEmergencyMode) return false; // Запрет на дым/свет
        return super.NEKRASOV_IsHearthReady();
    }

    // Рефлекс: Восстановление статов в аварийном режиме идет медленнее, 
    // но скрытность (Узел 13) максимальна
    float NEKRASOV_GetEmergencyStealthModifier()
    {
        return 0.1; // Риск обнаружения почти нулевой
    }
}
