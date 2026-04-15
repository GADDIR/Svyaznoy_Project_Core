// ПЯТИУРОВНЕВАЯ ПАМЯТЬ А.Н. НЕКРАСОВА + РЕФЛЕКСЫ (ВЕРСИЯ 1.2)
class AN_MemoryController
{
    // --- БАЗОВЫЕ ДАННЫЕ ---
    private vector m_LastAnchorPos;
    private ref map<string, vector> m_SessionCache;
    
    // --- ЭКСТРЕННАЯ ПАМЯТЬ (Reflex Buffer) ---
    private vector m_ThreatVector;    // Точка угрозы (Вектор)
    private string m_ActiveTrigger;   // Тип: SHOT, NOISE, PAIN
    private float  m_ReflexTTL;       // Срок жизни (5-15 сек)
    private bool   m_IsMumbleBlocked; // Радиомолчание
    private float  m_TargetDistance;  // Расчет дистанции для СВД

    void AN_MemoryController(PlayerBase player)
    {
        m_SessionCache = new map<string, vector>;
        m_LastAnchorPos = player.GetPosition();
    }

    // РЕГИСТРАЦИЯ УГРОЗЫ (С учетом приоритетов)
    void RegisterReflex(vector pos, string type)
    {
        // Выстрел важнее хруста ветки
        if (m_ActiveTrigger == "SHOT" && type == "NOISE") return; 

        m_ThreatVector = pos;
        m_ActiveTrigger = type;

        // Тайминги из Реестра
        if (type == "SHOT")  m_ReflexTTL = 15.0; // Правило 2: Фантом
        if (type == "PAIN")  m_ReflexTTL = 3.0;  // Правило 3: Сторона боли
        if (type == "NOISE") m_ReflexTTL = 7.0;  // Правило 4: Акустический фокус
    }

    void OnUpdate(float timeslice, PlayerBase player)
    {
        // 1. ЛОГИКА "ЧИСТОЙ ДОСКИ"
        if (m_ReflexTTL > 0)
        {
            m_ReflexTTL -= timeslice;
            ExecuteEmergencyLogic(player);
        }
        else
        {
            m_ActiveTrigger = ""; 
            m_IsMumbleBlocked = false;
        }

        // 2. ПРОВЕРКА ДИСТАНЦИИ (Короткая память 500м)
        if (vector.Distance(player.GetPosition(), m_LastAnchorPos) > 500)
        {
            m_SessionCache.Clear();
            m_LastAnchorPos = player.GetPosition();
        }
    }

    private void ExecuteEmergencyLogic(PlayerBase player)
    {
        // Правило 1: ПРЕРЫВАНИЕ БЫТА
        player.InterruptCurrentAction(); 

        // Правило 4: ТИШИНА (Блокировка Mumble)
        m_IsMumbleBlocked = true;

        // Правило 6: СБРОС ТЯЖЕЛЫХ ПРЕДМЕТОВ (Лейка/Кастрюля)
        EntityAI item = player.GetHumanInventory().GetEntityInHands();
        if (item)
        {
            if (item.IsHeavyItem()) 
                player.PhysicalPredictiveDropItem(item); 
            else 
                player.ServerStoreEntityStepOne(item); 
        }

        // --- НОВЫЕ ДАННЫЕ (ПРАВИЛА 2 И 5) ---

        // Правило 2: ВЕКТОРНЫЙ ФАНТОМ (Удержание взгляда на цели)
        if (m_ActiveTrigger == "SHOT" || m_ActiveTrigger == "PAIN")
        {
            // Некрасов "дорисовывает" цель за деревом и держит там фокус
            player.GetInputController().SetFocusLookAt(m_ThreatVector);
        }

        // Правило 5: СНАРЯД В ПАТРОННИКЕ (Авто-зероинг СВД)
        if (player.GetHumanInventory().GetEntityInHands().IsInherited(SVD_Base))
        {
            m_TargetDistance = vector.Distance(player.GetPosition(), m_ThreatVector);
            // Выставляем поправку на ПСО-1 автоматически
            player.GetWeaponManager().SetZeroing(m_TargetDistance);
        }
    }
}
