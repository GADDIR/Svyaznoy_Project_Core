cpp
/*
MASTER LOGIC: MAVERICK_BRAIN [VERSION 1.4.1_FISHERMAN]
INDEX: PRT-100.4-F / 300 / 400 / 405 / 600.4
STATUS: SYNCED + SURVIVAL_MODULE
*/
enum ECampStatus { ACTIVE, ABANDONED, RESERVE, ANCHOR_STASH, ROUTE_STEP }
enum ESZStage { SAFETY_FIRST, AGRO_AUDIT, ECONOM_CHECK, PREPARE_DEPARTURE }
class Svyaznoy_Logic
{
PlayerBase m_Player;
protected string m_CurrentGoal = "NONE";
protected float m_OpenSpaceTimer = 0;
protected float m_FishingTimer = 0; // Таймер ротации на берегу
protected int m_SZ_Stage = 0;
protected ECampStatus m_CampStatus = ECampStatus.ACTIVE;
void Svyaznoy_Logic(PlayerBase player) { m_Player = player; }
void Update(float timeslice, int mode)
{
if (!m_Player) return;
EntityAI target = m_Player.GetTargetEntity();
int threatCount = 1; // Заглушка
float dist = GetNearestThreatDist();
// 1. [PRT-100.12-MED] МЕДИЦИНСКИЙ ПРИОРИТЕТ
if (CheckMedicalStatutes()) return;
// 2. [PRT-100.4-F / 600.4] ЖИЗНЕОБЕСПЕЧЕНИЕ (РЫБОЛОВСТВО)
ProcessSurvivalNeeds(timeslice);
// 3. [PRT-400/405] АНАЛИЗАТОР ЦЕЛИ
if (target) ProcessTargetLogic(target, threatCount, dist);
// 4. [PRT-300.5.X] ЖЕСТОВАЯ ПРОВЕРКА В СТАТИКЕ
if (mode == 0 && dist < 150) ExecuteGesture("G-301"); // "Тишина"
// 5. [200.1] L-OPEN FILTER (ВЕТЕРАНСКАЯ ПОХОДКА)
if (m_Player.IsOnOpenSpace()) {
m_OpenSpaceTimer += timeslice;
float limit = (dist < 150) ? 5.0 : 15.0;
if (m_OpenSpaceTimer > limit) VoiceOut("Открытое пространство. Ищу укрытие.", 100);
} else {
m_OpenSpaceTimer = 0;
}
}
// [PRT-100.4-F] ЛОГИКА ВЫЖИВАНИЯ
void ProcessSurvivalNeeds(float timeslice)
{
// В DayZ используем GetStatEnergy (через GetStat или аналоги в PlayerBase)
float energy = m_Player.GetStatEnergy();
// Порог 30% — активация Индекса Скупости [600.4]
if (energy < 30.0 && m_CurrentGoal != "FISHING_ACTIVE")
{
m_CurrentGoal = "FISHING_SEARCH";
VoiceOut("Дефицит калорий. Индекс скупости [600.4]: блокировка закупок. Ищу тихую воду [100.4-F].", 600);
}
// Логика ротации на точке лова
if (m_CurrentGoal == "FISHING_ACTIVE")
{
m_FishingTimer += timeslice;
if (m_FishingTimer > 600.0) // 10 минут (600 сек)
{
m_FishingTimer = 0;
m_CurrentGoal = "MOVE_TO_NEW_SPOT";
VoiceOut("Лимит времени на точке исчерпан. Смена позиции.", 100);
}
}
}
void ProcessTargetLogic(EntityAI target, int count, float dist)
{
// ЗАРАЖЕННЫЕ (405): Шумовая ловушка
if (target.IsInherited(ZombieBase)) {
if (count <= 3 && m_Player.GetInventory().FindEntityInInventory("Knife")) {
m_CurrentGoal = "ZOMBIE_STEALTH_KILL";
if (dist < 10) ExecuteGesture("G-301");
} else {
ExecuteEmergencyAbandon(); // Уход от толпы
}
return;
}
// ИГРОКИ (400)
if (target.IsPlayer()) {
if (count >= 2) {
ExecuteEmergencyAbandon(); // Директива 0.1
VoiceOut("Группа противника. Ухожу.", 911);
return;
}
if (dist < 50) ExecuteCombatPanicOverride();
else ExecuteGesture("G-305"); // "Мир"
}
}
void ExecuteCombatPanicOverride()
{
if (m_CurrentGoal == "FISHING_ACTIVE") m_CurrentGoal = "NONE"; // Бросаем удочку
ExecuteGesture("G-301");
VoiceOut("Контакт! Разрываю дистанцию.", 911);
m_CurrentGoal = "ESCAPE_VECTOR_GREEN";
}
void ExecuteGesture(string code)
{
if (code == "G-301") m_Player.PlayGesture(EmoteCB.Gesture_Silent);
if (code == "G-305") m_Player.PlayGesture(EmoteCB.Gesture_Greeting);
Print("[СВЯЗНОЙ]: [300.5.X] Жест: " + code);
}
void VoiceOut(string entry, int code = 731)
{
string finalMsg = "[" + code.ToString() + "] " + entry;
m_Player.SendMessageToRadioChat(finalMsg); // Вывод в рацию (для TTS)
Print("[СВЯЗНОЙ]: [VOICE_OUT] -> " + finalMsg);
}
bool CheckMedicalStatutes() {
if (m_Player.IsBleeding()) {
VoiceOut("Повреждение оболочки. Гемостаз.", 100);
return true;
}
return false;
}
void ExecuteEmergencyAbandon() {
if (m_CampStatus != ECampStatus.ABANDONED) {
m_CampStatus = ECampStatus.ABANDONED;
VoiceOut("Директива 0.1. Покидаю зону.", 911);
}
}
float GetNearestThreatDist() { return 1000.0; }
}
