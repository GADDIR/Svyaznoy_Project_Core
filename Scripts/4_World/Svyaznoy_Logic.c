/*
    ПРОЕКТ: СВЯЗНОЙ (Svyaznoy_Project_Core)
    ОБЪЕКТ: Алексей Некрасов (АНН-79)
    ФАЙЛ: Svyaznoy_Logic.c (ГЛАВНОЕ ЯДРО)
    ОПИСАНИЕ: Центральный процессор личности и управления модулями.
*/

class Svyaznoy_Logic
{
    // --- 🧬 ССЫЛКИ НА ИСПОЛНИТЕЛЬНЫЕ МОДУЛИ ---
    ref Svyaznoy_Medical_Protocol m_MedicalProtocol; // Медицина (100.12)
    ref Svyaznoy_Agro_Memory     m_AgroMemory;      // Агро-экономика (700)
    ref Svyaznoy_Hunter_Memory   m_HunterMemory;    // Охота/Рыбалка (100.4)
    ref Svyaznoy_Combat_Reflex   m_CombatReflex;    // Боевые рефлексы (400)
    ref Svyaznoy_Base_Defense    m_BaseDefense;     // Оборона Приюта (900)

    // --- ⚙️ СИСТЕМНЫЕ ПЕРЕМЕННЫЕ ---
    private string m_IdentityName = "Алексей Некрасов";
    private int m_CurrentState = 501; // По умолчанию: 501.1 Статика

    // --- 🏗️ КОНСТРУКТОР (ЗАПУСК СИСТЕМЫ) ---
    void Svyaznoy_Logic()
    {
        Init();
    }

    void Init()
    {
        Print("[СВЯЗНОЙ] Инициализация ядра объекта: " + m_IdentityName);

        // Материализация модулей в памяти
        m_MedicalProtocol = new Svyaznoy_Medical_Protocol();
        m_AgroMemory      = new Svyaznoy_Agro_Memory();
        m_HunterMemory    = new Svyaznoy_Hunter_Memory();
        m_CombatReflex    = new Svyaznoy_Combat_Reflex();
        m_BaseDefense     = new Svyaznoy_Base_Defense();

        Print("[СВЯЗНОЙ] Все системы синхронизированы. Статус: К ЗАПУСКУ ГОТОВ.");
    }

    // --- 🔄 ГЛАВНЫЙ ЦИКЛ ОБНОВЛЕНИЯ ---
    void OnUpdate(float timeslice)
    {
        // Здесь будет проходить проверка состояния Сейф-зоны для m_BaseDefense
        // И мониторинг жизненных показателей для m_MedicalProtocol
    }

    // --- 📡 УПРАВЛЕНИЕ РЕЖИМАМИ (State Machine) ---
    void OnStateChanged(int newState)
    {
        m_CurrentState = newState;
        Print("[СВЯЗНОЙ] Состояние изменено на: " + m_CurrentState.ToString());
        
        // Логика перехода между режимами (Мир / Осада / Сон)
    }

    // Геттеры для доступа к модулям извне
    Svyaznoy_Base_Defense GetDefense() { return m_BaseDefense; }
}
