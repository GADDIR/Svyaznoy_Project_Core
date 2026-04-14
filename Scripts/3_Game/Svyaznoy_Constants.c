/*
    ПРОЕКТ: СВЯЗНОЙ
    РАЗДЕЛ: 3_Game (Константы)
    ОПИСАНИЕ: Глобальные настройки Сектора 900 и лимиты систем.
*/

class Svyaznoy_Constants
{
    // --- 📍 ГЕОГРАФИЯ (Сектор 900) ---
    static const vector SECTOR_900_CENTER = "308.4 283.2 260.4";
    static const float  SHELTER_RADIUS    = 100.0; // Тот самый квадрат 100х100

    // --- 🛠️ ТЕХНИЧЕСКИЕ ЛИМИТЫ ---
    static const int    MAX_AGRO_PLOTS    = 3;     // Лимит грядок по Манифесту
    static const float  REACTION_X_DIST   = 100.0; // Радиус экстренного пробуждения
    static const float  STEALTH_ENGAGE_DIST = 150.0; // Дистанция "Тени"

    // --- 🎭 СОЦИАЛЬНЫЙ РЕЗОНАНС ---
    static const float  TRUST_ZONE_RADIUS = 15.0;  // Радиус узнавания "своих"
}
