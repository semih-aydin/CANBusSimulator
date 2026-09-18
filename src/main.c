#include "can_bus.h"
#include "can_fuzzer.h"
#include "can_detector.h"
#include "can_logger.h"
#include "can_json.h"
#include "ecu_motor.h"
#include "ecu_abs.h"
#include "ecu_dashboard.h"
#include "ecu_airbag.h"
#include "ecu_klima.h"
#include "ecu_direksiyon.h"
#include "ecu_kabin.h"
#include "ecu_lastik.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ANOMALI_LOG  "logs/anomali.log"
#define JSON_DOSYA   "dashboard/public/can_dashboard.json"
#define ADIM_MS      100

int main()
{
    CANBus        bus;
    MotorECU      motor;
    AbsECU        abs_ecu;
    DashboardECU  dashboard;
    AirbagECU     airbag;
    KlimaECU      klima;
    DireksiyonECU direksiyon;
    KabinECU      kabin;
    LastikECU     lastik;
    CANFuzzer     fuzzer;
    CANDetector   detector;
    CANLogger     anomali_logger;
    int           adim = 0, i;
    double        timestamp;
    DashboardVeri v;

    srand(42);

    bus_baslat(&bus);
    motor_baslat(&motor, &bus);
    abs_baslat(&abs_ecu, &bus);
    dashboard_baslat(&dashboard, &bus);
    airbag_baslat(&airbag, &bus);
    klima_baslat(&klima, &bus);
    direksiyon_baslat(&direksiyon, &bus);
    kabin_baslat(&kabin, &bus);
    lastik_baslat(&lastik, &bus);
    fuzzer_baslat(&fuzzer, &bus);

    logger_baslat(&anomali_logger, ANOMALI_LOG);
    detector_baslat(&detector, &anomali_logger);

    printf("CAN Bus Simulator baslatildi.\n");

    while (1) {
        adim++;
        timestamp = adim * (ADIM_MS / 1000.0);

        motor_guncelle(&motor);
        abs_guncelle(&abs_ecu);
        airbag_guncelle(&airbag);
        klima_guncelle(&klima);
        direksiyon_guncelle(&direksiyon);
        kabin_guncelle(&kabin);
        lastik_guncelle(&lastik);

        if (adim % 50 == 0)
            fuzzer_gonder(&fuzzer, (adim / 50) % 5);

        while (bus_arbitration_calistir(&bus) != -1)
            ;

        for (i = 0; i < BUS_KUYRUK_BOYUTU; i++)
            if (bus.dolu[i])
                detector_kontrol(&detector, &bus.slots[i], timestamp);

        detector_sayac_sifirla(&detector);
        dashboard_oku(&dashboard);

        v.rpm              = dashboard.rpm;
        v.hiz              = dashboard.tekerlek_hizi[0];
        v.sicaklik         = dashboard.sicaklik;
        v.yakit            = dashboard.yakit;
        v.abs              = dashboard.abs_devrede;
        v.fren             = dashboard.fren_aktif;
        v.airbag_aktif     = dashboard.airbag_aktif;
        v.klima_hedef      = dashboard.klima_hedef;
        v.klima_kompressor = dashboard.klima_kompressor;
        v.direksiyon_aci   = dashboard.direksiyon_aci;
        v.ic_sicaklik      = dashboard.ic_sicaklik;
        v.dis_sicaklik     = dashboard.dis_sicaklik;
        v.lastik[0]        = dashboard.lastik[0];
        v.lastik[1]        = dashboard.lastik[1];
        v.lastik[2]        = dashboard.lastik[2];
        v.lastik[3]        = dashboard.lastik[3];
        json_yaz(JSON_DOSYA, &v);

        Sleep(ADIM_MS);
    }

    logger_kapat(&anomali_logger);
    return 0;
}
