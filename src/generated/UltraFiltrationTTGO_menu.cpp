/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

// Generated for Arduino ESP32 by TcMenu 4.3.1 on 2024-10-07T07:56:22.698511711Z.

#include <tcMenu.h>
#include "UltraFiltrationTTGO_menu.h"
#include "../ThemeDarkModeTraditionalBuilder.h"

// Global variable declarations
const PROGMEM  ConnectorLocalInfo applicationInfo = { "UltraFiltrationTTGO", "7d595025-5ca6-49c9-93a5-8969f94583b0" };

TFT_eSPI gfx;
TfteSpiDrawable gfxDrawable(&gfx, 0);
GraphicsDeviceRenderer renderer(30, applicationInfo.name, &gfxDrawable);

// Global Menu Item declarations
const PROGMEM AnyMenuInfo minfoManualFlush = { "manualFlush", 4, 0xffff, 0, onManualFlush };
ActionMenuItem menuManualFlush(&minfoManualFlush, nullptr, INFO_LOCATION_PGM);
const PROGMEM AnalogMenuInfo minfoNextFlush = { "nextFlush", 3, 8, 180, NO_CALLBACK, 0, 1, "min" };
AnalogMenuItem menuNextFlush(&minfoNextFlush, 0, &menuManualFlush, INFO_LOCATION_PGM);
const PROGMEM AnalogMenuInfo minfoInterval = { "interval", 2, 6, 180, onIntervalChanged, 0, 1, "min" };
AnalogMenuItem menuInterval(&minfoInterval, 0, &menuNextFlush, INFO_LOCATION_PGM);
const PROGMEM AnalogMenuInfo minfoDuration = { "duration", 1, 4, 120, onDurationChanged, 0, 1, "sec" };
AnalogMenuItem menuDuration(&minfoDuration, 5, &menuInterval, INFO_LOCATION_PGM);

void setupMenu() {
    // First we set up eeprom and authentication (if needed).
    setSizeBasedEEPROMStorageEnabled(true);
    // Now add any readonly, non-remote and visible flags.
    menuManualFlush.setReadOnly(true);
    menuNextFlush.setReadOnly(true);

    // Code generated by plugins and new operators.
    gfx.begin();
    gfx.setRotation(1);
    renderer.setUpdatesPerSecond(10);
    switches.init(internalDigitalIo(), SWITCHES_NO_POLLING, true);
    menuMgr.initForEncoder(&renderer, &menuDuration, 26, 27, 25);
    installDarkModeTraditionalTheme(renderer, MenuFontDef(nullptr, 2), MenuFontDef(nullptr, 2), true, BaseGraphicalRenderer::TITLE_FIRST_ROW, false);
}

