class NEKRASOV_MaverickController : Managed {
    // Ссылки на основные модули разума
    protected ref NEKRASOV_WorldState m_WorldState;
    protected ref NEKRASOV_Planner    m_Planner;
    protected ref NEKRASOV_Personality m_Personality;
    
    protected PlayerBase m_MaverickEntity; // Ссылка на самого персонажа в мире

    void NEKRASOV_MaverickController(PlayerBase player) {
        m_MaverickEntity = player;
        
        // Инициализация уровней системы NEKRASOV
        m_WorldState = new NEKRASOV_WorldState();
        m_Planner    = new NEKRASOV_Planner();
        m_Personality = new NEKRASOV_Personality(1.0, 0.5); // Агрессивный, но общительный
        
        Print("NEKRASOV AI: Маверик запущен. Система активна.");
    }

    // Главный цикл (Тик) разума Маверика
    void OnUpdate(float timeslice) {
        if (!m_MaverickEntity || !m_MaverickEntity.IsAlive()) return;

        // 1. УРОВЕНЬ ТЕЛА: Опрос датчиков (голод, жажда, раны)
        UpdateBodyNeeds();

        // 2. УРОВЕНЬ РАЗУМА: Если текущий план пуст — строим новый
        if (!HasPlan()) {
            MakeNewPlan();
        }

        // 3. УРОВЕНЬ ПОВЕДЕНИЯ: Выполняем шаг текущего плана
        ExecutePlanStep(timeslice);
    }

    protected void UpdateBodyNeeds() {
        // Маверик проверяет свои показатели
        float energy = m_MaverickEntity.GetStatEnergy().Get();
        m_WorldState.SetState("is_hungry", energy < 500);
        
        // Проверка безопасности (есть ли рядом враги)
        // m_WorldState.SetState("is_safe", CheckSurroundings());
    }

    protected void MakeNewPlan() {
        // NEKRASOV решает, что делать дальше
        // Цель по умолчанию: ВЫЖИТЬ
        // m_Planner.Plan(m_WorldState, Goal_Survival, m_AvailableActions);
    }
    
    protected bool HasPlan() {
        // Проверка, есть ли у Маверика текущая задача
        return false; // Заглушка
    }

    protected void ExecutePlanStep(float delta) {
        // Здесь Маверик двигает телом (бежит, ест, стреляет)
    }
}
