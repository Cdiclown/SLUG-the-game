#pragma once

// struttura dati per il tipo di evento
enum tipo_evento {
    CREATURA_MOSSA,
    CREATURA_ELIMINATA,
    VITA_DIMINUITA_C,
    STANZA_MODIFICATA,
    VITA_MODIFICATA_S,
    INVENTARIO_MODIFICATO,
    CREATURA_RACCOLTA,
    PUNTEGGIO_MODIFICATO
};

// classe per gestire gli eventi
class EventoStanze {
    public:
        EventoStanze(tipo_evento);
        tipo_evento id;
};