#include "generated/UltraFiltrationTTGO_menu.h"
#include <Preferences.h>

Preferences preferences;

#define RELAY_1_PIN 32

unsigned long lastFlushTimeInSec = 0;

String createKey(AnalogMenuItem *menuItem) {
    return "m" + String(menuItem->getId());
}

void initDefaultPreferenceFloat(AnalogMenuItem *menuItem, float defaultValue) {
    String keyString = createKey(menuItem);
    const char* key = keyString.c_str();
    
    if(!preferences.isKey(key)) {
        preferences.putFloat(key, defaultValue);
    }
    menuItem->setFromFloatingPointValue(preferences.getFloat(key));
}

void initMenuByPreferences() {
    initDefaultPreferenceFloat(&menuDuration, 3.0);
    initDefaultPreferenceFloat(&menuInterval, 11.0);
}

void relayOn() {
    Serial.println("Switch relay on");
    lastFlushTimeInSec = millis() / 1000;
    digitalWrite(RELAY_1_PIN, LOW);
}

void relayOff() {
    Serial.println("Switch relay off");
    digitalWrite(RELAY_1_PIN, HIGH);
}

boolean isRelayOn() {
    return digitalRead(RELAY_1_PIN) == LOW;
}

void setup() {
    Serial.begin(115200);

    setupMenu();
    renderer.turnOffResetLogic();

    preferences.begin("Ultra", false);
    initMenuByPreferences();

    pinMode(RELAY_1_PIN, OUTPUT);
    digitalWrite(RELAY_1_PIN, HIGH);

    taskManager.scheduleFixedRate(1000, [] {
        Serial.println("Start flush job...");

        Serial.println("LastFlushTimeInSec: " + String(lastFlushTimeInSec));

        unsigned long nowInSec = millis() / 1000;
        if(nowInSec > lastFlushTimeInSec + (menuInterval.getAsFloatingPointValue() * 60)) {
            if(!isRelayOn()) {
                relayOn();
            }
        }
        if(isRelayOn()) {
            if(nowInSec - lastFlushTimeInSec > menuDuration.getAsFloatingPointValue()) {
                relayOff();
            }
        }

        float durationTilNextFlushInSec = (lastFlushTimeInSec + (menuInterval.getAsFloatingPointValue() * 60)) - nowInSec;
        Serial.println("durationTilNextFlushInSec: " + String(durationTilNextFlushInSec));
        menuNextFlush.setFromFloatingPointValue(durationTilNextFlushInSec / 60);

    }, TIME_MILLIS);
}

void loop() {
    taskManager.runLoop();
}

void updatePreferenceByMenuItemFloat(AnalogMenuItem* menuItem) {
    const String key = createKey(menuItem);
    preferences.putFloat(key.c_str(), menuItem->getAsFloatingPointValue());
}

void CALLBACK_FUNCTION onDurationChanged(int id) {
    updatePreferenceByMenuItemFloat(&menuDuration);
}

void CALLBACK_FUNCTION onIntervalChanged(int id) {
    updatePreferenceByMenuItemFloat(&menuInterval);
}

void CALLBACK_FUNCTION onManualFlush(int id) {
    lastFlushTimeInSec = 0;
}
