# СТРУКТУРА ПРОЕКТА «СВЯЗНОЙ» (FINAL SYNC)

## 1. ТЕЛО (ENTITIES) — Scripts/4_World/Entities/ManBase/
- **PlayerBase.c**: Единственная точка входа. Здесь ID-фильтр и ссылка на логику.
- **Svyaznoy_NPC.c**: Специализированная сущность ветерана.

## 2. РАЗУМ (CLASSES) — Scripts/4_World/Classes/
- **Svyaznoy_Logic.c**: Центральный процессор.
- **Svyaznoy_Knowledge_Base.c**: Инстинкты (Крафт/Поиск).
- **Svyaznoy_Medical_Protocol.c**: Иммунитет (К.У.Л.А.К.).
- **Svyaznoy_Agro_Memory.c**: Память грядок.
- **Svyaznoy_Combat_Reflex.c**: Боевые рефлексы.
- **Svyaznoy_Base_Defense.c**: Оборона Приюта.
- **Svyaznoy_Mumble_Memory.c**: Голос и Личность.
- **Svyaznoy_Chat_Logic.c**: Транслятор мыслей.

## 3. ФУНДАМЕНТ (3_GAME) — Scripts/3_Game/
- **Svyaznoy_Constants.c**: Координаты Сектора 900 и лимиты.

## 4. СВЯЗЬ (5_MISSION) — Scripts/5_Mission/
- **missionServer.c**: Спавн и серверный рапорт.
