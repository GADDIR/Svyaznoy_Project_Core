/**
 * NEKRASOV_SOCIAL_RANK.c
 * Иерархия и классификация субъектов.
 * СТРОГО: Все глобальные идентификаторы пишутся ЗАГЛАВНЫМИ БУКВАМИ.
 */

enum E_NEKRASOV_RANK
{
    BACTERIA,   // Ранг 0: Угроза или ресурс
    STRANGER,   // Ранг 1: Неизвестный
    PARTNER,    // Ранг 2: Деловое доверие
    BROTHER,    // Ранг 3: Высшая степень доверия
    LEGACY_HEIR // Ранг 4: Наследник Наследия
}

class NEKRASOV_SOCIAL_RANK
{
    // Определение ранга на основе накопленных очков доверия
    static E_NEKRASOV_RANK GET_RANK_BY_SCORE(float SCORE)
    {
        if (SCORE < -50.0) return E_NEKRASOV_RANK.BACTERIA;
        if (SCORE >= 100.0) return E_NEKRASOV_RANK.LEGACY_HEIR;
        if (SCORE >= 70.0)  return E_NEKRASOV_RANK.BROTHER;
        if (SCORE >= 30.0)  return E_NEKRASOV_RANK.PARTNER;
        
        return E_NEKRASOV_RANK.STRANGER;
    }

    // Текстовое представление для логов и MUMBLE
    static string GET_RANK_STRING(E_NEKRASOV_RANK RANK)
    {
        switch (RANK)
        {
            case E_NEKRASOV_RANK.BACTERIA:   return "БАКТЕРИЯ";
            case E_NEKRASOV_RANK.STRANGER:   return "НЕЗНАКОМЕЦ";
            case E_NEKRASOV_RANK.PARTNER:    return "ПАРТНЕР";
            case E_NEKRASOV_RANK.BROTHER:    return "БРАТ";
            case E_NEKRASOV_RANK.LEGACY_HEIR: return "НАСЛЕДНИК";
        }
        return "НЕИЗВЕСТНО";
    }
}
