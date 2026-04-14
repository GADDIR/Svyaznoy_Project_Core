graph TD
    %% Стационарный узел
    subgraph Hearth [ОЧАГ И ПЕЧЬ]
    Home[Домашняя печь / Камин] -->|Ignition| HiddenFire[СКРЫТЫЙ ОГОНЬ]
    HiddenFire -->|Преимущество| NoLight[Нулевой световой индекс]
    HiddenFire -->|Преимущество| Temp[Длительное сохранение тепла]
    end

    %% Логика заготовки
    subgraph Processing [ПРОЦЕССИНГ РЕСУРСА]
    Raw[СЫРОЕ МЯСО / РЫБА] --> Choice{ВЫБОР МЕТОДА}
    
    Choice -->|Smoking Slot| Smoke[КОПЧЕНИЕ]
    Choice -->|Low Temp| Dry[ВЯЛЕНИЕ]
    
    Smoke --> Quinn((ВАЛЮТА ДЛЯ QUINN: Долгое хранение))
    Dry --> Logistics((ЛОГИСТИКА: Малый вес для рейдов))
    end

    %% Параллельные задачи
    subgraph MultiTask [ПРАВИЛО 30 СЕКУНД]
    Processing -->|Тайминг терпения| Workshop[Цех: Ремонт ТТсКО]
    Processing -->|Тайминг терпения| Agro[Агро: Работа с семенами]
    end

    style Smoke fill:#6e4b3a,stroke:#333,color:#fff
    style Dry fill:#d2b48c,stroke:#333,color:#000
    style HiddenFire fill:#ff4500,stroke:#333,color:#fff
