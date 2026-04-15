// NEKRASOV_TRUST_SYSTEM.C — СОЦИАЛЬНЫЙ АУДИТ И РЕЗОНАНС
// Интеграция: Блок №7 (Учет), Блок №8 (Прагматизм), Блок №9 (Лояльность)

class Nekrasov_Trust_System
{
    // Реестр: ID Игрока -> Баллы доверия
    private ref map<string, float> m_TrustRegistry
    private const float PERMANENT_ALLY_THRESHOLD = 500.0

    void Nekrasov_Trust_System()
    {
        m_TrustRegistry = new map<string, float>
    }

    // ГЛАВНЫЙ АУДИТ (Вызывается при контакте)
    void AuditSubject(PlayerBase player, PlayerBase target)
    {
        string id = target.GetIdentity().GetId()
        float currentTrust = GetTrust(id)

        // 1. ОЦЕНКА ЖЕСТА (Блок №7)
        if (target.GetInHands() == null)
            currentTrust += 5.0
        
        // 2. ЧЕРНАЯ МЕТКА (Агрессия = Мгновенный враг)
        if (target.IsAggressiveTo(player))
            currentTrust = -100.0
            Nekrasov_Mumble_Logic.Say(player, "Один раз предал — в мох ляжешь. Бактерия.")

        m_TrustRegistry.Set(id, currentTrust)
    }

    // РАСЧЕТ ПОЛЕЗНОСТИ (Блок №9: Ресурсная лояльность)
    void OnResourceReceived(PlayerBase player, string id, float value)
    {
        float currentTrust = GetTrust(id)
        currentTrust += value
        
        if (currentTrust >= PERMANENT_ALLY_THRESHOLD)
            Nekrasov_Mumble_Logic.Say(player, "Вероятность найти замену такому человеку мала. Пользуйся моим костром.")
            
        m_TrustRegistry.Set(id, currentTrust)
    }

    // СТАТУС ВЕЧНОГО ДРУГА
    bool IsPermanentAlly(string id)
    {
        if (GetTrust(id) >= PERMANENT_ALLY_THRESHOLD)
            return true
            
        return false
    }

    float GetTrust(string id)
    {
        if (m_TrustRegistry.Contains(id))
            return m_TrustRegistry.Get(id)
            
        return 0.0 // Чистый лист (Блок №7)
    }
}
