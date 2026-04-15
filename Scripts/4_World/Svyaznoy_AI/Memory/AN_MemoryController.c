// ПЯТИУРОВНЕВАЯ ПАМЯТЬ А.Н. НЕКРАСОВА + РЕЕСТР ПРАВИЛ ЭКСТРЕННОЙ ПАМЯТИ
class AN_MemoryController
{
    // --- ИСХОДНЫЕ ДАННЫЕ (Блок 1) ---
    private vector m_LastAnchorPos;
    private ref map<string, vector> m_SessionCache;
    
    // --- НОВЫЕ ДАННЫЕ: ЭКСТРЕННАЯ ПАМЯТЬ (Reflex Buffer) ---
    private vector m_ThreatVector;    // Точка в пространстве (Vector)
    private string m_ActiveTrigger;   // Тип триггера (SHOT, NOISE, PAIN)
    private float  m_ReflexTTL;       // Срок жизни (Time To Live)
    private bool   m_IsMumbleBlocked; // Режим радиомолчания

    void AN_MemoryController(PlayerBase player)
    {
        m_SessionCache = new map<string, vector>;
        m_LastAnchorPos = player.GetPosition();
    }

    // СТРАТЕГИЧЕСКИЙ ОТВЕТ: Обработка нескольких сигналов сразу
    // Выстрел (SHOT) имеет высший вес и перекрывает хруст (NOISE)
    void RegisterReflex(vector pos, string type)
    {
        if (m_ActiveTrigger == "SHOT" && type == "NOISE") return; // Игнор шума во время боя

        m_ThreatVector = pos;
        m_ActiveTrigger = type;

        // Применение таймингов из Реестра
        if (type == "SHOT")  m_ReflexTTL = 15.0; // Правило 2: Векторный Фантом
        if (type == "PAIN")  m_ReflexTTL = 3.0;  // Правило 3: Сторона боли
        if (type == "NOISE") m_ReflexTTL = 7.0;  // Правило 4: Акустический фокус
    }

    void OnUpdate(float timeslice, PlayerBase player)
    {
        // Логика "Чистой доски" (Освобождение ресурсов)
        if (m_ReflexTTL > 0)
        {
            m_ReflexTTL -= timeslice;
            ExecuteEmergencyLogic(player);
        }
        else
        {
            m_ActiveTrigger = ""; // Данные удаляются полностью
            m_IsMumbleBlocked = false;
        }

        // Твоя исходная проверка дистанции (500м)
        if (vector.Distance(player.GetPosition(), m_LastAnchorPos) > 500)
        {
            m_SessionCache.Clear();
            m_LastAnchorPos = player.GetPosition();
        }
    }

    private void ExecuteEmergencyLogic(PlayerBase player)
    {
        // Правило 1: ПРЕРЫВАНИЕ (Interrupt)
        player.InterruptCurrentAction(); 

        // Правило 4: Режим тишины (Связь с Mumble)
        m_IsMumbleBlocked = true;

        // Правило 6: Состояние «В руках»
        EntityAI item = player.GetHumanInventory().GetEntityInHands();
        if (item)
        {
            if (item.IsHeavyItem()) // Кастрюля, лейка
                player.PhysicalPredictiveDropItem(item); 
            else 
                player.ServerStoreEntityStepOne(item); // Нож, фляга -> в карман
        }
    }
}
