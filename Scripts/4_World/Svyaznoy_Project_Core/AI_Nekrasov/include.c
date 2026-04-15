// ========================================================
// AI_Nekrasov (ID 9001982) - include.c
// Порядок загрузки: База -> Модули -> Логика -> Ядро
// ========================================================

// 1. Основание и Данные
#include "Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/Nekrasov_Genesis_Registry.c"
#include "Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/Nekrasov_Identity.c"
#include "Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/Nekrasov_Memory_Buffer.c"

// 2. Этические и речевые фильтры
#include "Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/Nekrasov_Moral_Engine.c"
#include "Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/Nekrasov_Mumble_Logic.c"

// 3. Быт, Питание и Ограничения
#include "Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/Nekrasov_Dietary_Restrictions.c"
#include "Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/Nekrasov_Food_Taboo.c"
#include "Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/Nekrasov_Lifestyle_Module.c"

// 4. Взаимодействие и Тактика
#include "Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/Nekrasov_Trust_System.c"
#include "Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/Nekrasov_Trade_Logic.c"
#include "Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/Nekrasov_Combat_Tactics.c"

// 5. Визуализация и Эффекты
#include "Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/AN_Fragile_Particles.c"

// 6. ЦЕНТРАЛЬНЫЙ ПРОЦЕССОР (Brain Core)
// Должен быть последним, чтобы видеть все вышеуказанные классы
#include "Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/Nekrasov_Brain_Core.c"
