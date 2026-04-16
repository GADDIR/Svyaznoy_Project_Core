// СИСТЕМА ПАМЯТИ И ИНСТИНКТОВ А.Н. НЕКРАСОВА (ВЕРСИЯ 1.3)
class NEKRASOV_MemoryController
{
    // --- [БЛОК 1: БАЗОВЫЕ ДАННЫЕ И КЭШ] ---
    private vector m_LastAnchorPos;
    private ref map<string, vector> m_SessionCache;
    
    // --- [БЛОК 2: ЭКСТРЕННАЯ ПАМЯТЬ / REFLEX BUFFER] ---
    private vector m_ThreatVector;    
    private string m_ActiveTrigger;   
    private float  m_ReflexTTL;       
    private bool   m_IsMumbleBlocked; 
    private float  m_TargetDistance;  

    // --- [БЛОК 3: ТАКТИЛЬНЫЙ СЛОЙ И ИНСТИНКТЫ] ---
    private float m_DangerSenseLevel; // Правило 2 и 4: Уровень тревоги («Чуйка»)
    private bool  m_WeatherAche;      // Правило "Погода": Ломота в костях
    private float m_StaminaThreshold; // Правило 5: Ритм дыхания

    void AN_MemoryController(PlayerBase player)
    {
        m_SessionCache = new map<string, vector>;
        m_LastAnchorPos = player.GetPosition();
        m_StaminaThreshold = 10.0; // Стамина < 10% (Инстинкт)
    }

    // РЕГИСТРАЦИЯ СИГНАЛОВ И ПРЕДЧУВСТВИЙ
    void RegisterReflex(vector pos, string type)
    {
        if (m_ActiveTrigger == "SHOT" && type == "NOISE") return; 

        m_ThreatVector = pos;
        m_ActiveTrigger = type;

        if (type == "SHOT")  m_ReflexTTL = 15.0; 
        if (type == "PAIN")  m_ReflexTTL = 3.0;  
        if (type == "NOISE") m_ReflexTTL = 7.0;
        if (type == "NEAR_MISS") m_ReflexTTL = 2.0; // Правило 1: Кожный резонанс
    }

    void OnUpdate(float timeslice, PlayerBase player)
    {
        // 1. Мониторинг погоды (Предчувствие за 30 сек до ливня)
        CheckWeatherIntuition();

        // 2. Логика "Чистой доски" и Рефлексов
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

        // 3. Короткая память (500м)
        if (vector.Distance(player.GetPosition(), m_LastAnchorPos) > 500)
        {
            m_SessionCache.Clear();
            m_LastAnchorPos = player.GetPosition();
        }
    }

    private void ExecuteEmergencyLogic(PlayerBase player)
    {
        player.InterruptCurrentAction(); 
        m_IsMumbleBlocked = true;

        // ПРАВИЛО 6 + ПРАВИЛО 1 (Пригиб при свисте пули)
        EntityAI item = player.GetHumanInventory().GetEntityInHands();
        if (m_ActiveTrigger == "NEAR_MISS" || m_ActiveTrigger == "PAIN")
        {
            player.GetInputController().OverrideStance(DayZPlayerConstants.STANCEIDX_CROUCH);
        }

        if (item)
        {
            if (item.IsHeavyItem()) player.PhysicalPredictiveDropItem(item); 
            else player.ServerStoreEntityStepOne(item); 
        }

        // ПРАВИЛО 2 и 4: Предчувствие (Нервозность/Развороты)
        if (m_DangerSenseLevel > 0.8)
        {
            player.GetInputController().SetAlertLevel(1); // Состояние взведенного курка
        }

        // ПРАВИЛО 5: Тактильный стоп-кран (Усталость)
        if (player.GetStatStamina().Get() < m_StaminaThreshold)
        {
            player.GetInputController().SetOverrideMovementSpeed(0.5); 
        }

        // Векторный фантом и Зероинг СВД (сохранены)
        if (m_ActiveTrigger == "SHOT")
        {
            player.GetInputController().SetFocusLookAt(m_ThreatVector);
            if (item && item.IsInherited(SVD_Base))
            {
                m_TargetDistance = vector.Distance(player.GetPosition(), m_ThreatVector);
                player.GetWeaponManager().SetZeroing(m_TargetDistance);
            }
        }
    }

    // НОВОЕ: Проверка погоды (Ломота в костях)
    private void CheckWeatherIntuition()
    {
        Weather weather = GetGame().GetWeather();
        if (weather && weather.GetRain().GetNext() > 0.1) // Если скоро дождь
        {
            m_WeatherAche = true; // Ломит кости
        }
        else
        {
            m_WeatherAche = false;
        }
    }
}
