/*
    ПРОЕКТ: СВЯЗНОЙ (Svyaznoy_Project_Core)
    ОБЪЕКТ: НЕКРАСОВ АЛЕКСЕЙ НИКОЛАЕВИЧ (АНН-79)
    ФАЙЛ:  NEKRASOV_Logic.c (ГЛАВНОЕ ЯДРО)
*/

class Svyaznoy_Logic
{
    // --- 🧬 ССЫЛКИ НА МОДУЛИ ---
    PlayerBase self;
    ref  NEKRASOV_Knowledge_Base m_Knowledge;
    ref  NEKRASOV_Medical_Protocol m_MedicalProtocol;
    ref  NEKRASOV_Agro_Memory     m_AgroMemory;
    ref  NEKRASOV_Hunter_Memory   m_HunterMemory;
    ref  NEKRASOV_Combat_Reflex   m_CombatReflex;
    ref  NEKRASOV_Base_Defense    m_BaseDefense;
    ref array<string>            m_TrustList; // Список Доверия

    // --- ⚙️ ПЕРЕМЕННЫЕ СОСТОЯНИЯ ---
    private int m_CurrentState = 501; 

    // --- 🏗️ КОНСТРУКТОР (ИНИЦИАЛИЗАЦИЯ) ---
    void  NEKRASOV_Logic(PlayerBase player)
    {
        self = player;
        
        // Материализация "Разума"
        m_Knowledge       = new  NEKRASOV_Knowledge_Base();
        m_MedicalProtocol = new  NEKRASOV_Medical_Protocol();
        m_AgroMemory      = new  NEKRASOV_Agro_Memory();
        m_HunterMemory    = new  NEKRASOV_Hunter_Memory();
        m_CombatReflex    = new  NEKRASOV_Combat_Reflex();
        m_BaseDefense     = new  NEKRASOV_Base_Defense();
        
        // Прошивка Списка Доверия
        m_TrustList = new array<string>;
        m_TrustList.Insert("7656119xxxxxxxxxx"); // ID Братства

        Print("[СВЯЗНОЙ] Ядро АН инициализировано. Системы и Список Доверия загружены.");
    }

    // --- 🔄 ГЛАВНЫЙ ЦИКЛ (ТИК-СИСТЕМА) ---
    void Update(float timeslice)
    {
        if (!self || !self.IsAlive()) return;

        // 1. Социальный резонанс (Свой-Чужой)
        CheckSocialResonance();

        // 2. Биологический мониторинг
        float thirst = self.GetStatWater().Get();
        if (thirst < 200)
        {
            Print("АН: Чувствую жажду. Требуется поиск воды.");
        }

        // 3. Запуск исполнительной логики
        m_Knowledge.Execute_ZeroCycle(self);
        
        // Здесь будут апдейты остальных модулей (Defense, Medical и т.д.)
    }

    // --- 📡 СОЦИАЛЬНЫЙ РЕЗОНАНС ---
    void CheckSocialResonance()
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man player : players)
        {
            if (vector.Distance(self.GetPosition(), player.GetPosition()) < 15.0)
            {
                string playerID = player.GetIdentity().GetPlainId();
                if (m_TrustList.Find(playerID) != -1)
                {
                    self.SetAITarget(null); // Сброс агрессии
                    // Print("АН: Резонанс со своим. Статус: СОЮЗНИК.");
                }
            }
        }
    }

    // --- 🕹️ УПРАВЛЕНИЕ РЕЖИМАМИ ---
    void OnStateChanged(int newState)
    {
        m_CurrentState = newState;
        Print("[СВЯЗНОЙ] Состояние изменено на: " + m_CurrentState.ToString());
    }
}
