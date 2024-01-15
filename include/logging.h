#ifndef LOGGING_H
#define LOGGING_H

// Check for Arduino environment
#if defined(__AVR__) || defined(__arm__) || defined(ESP8266) || defined(ESP32)
#include <Arduino.h>
#define LOG_TUPLE(t) Serial.println("TUPLE ID: %s\nTUPLE SIZE: %d\n", t->id, t->size)
#define PART_LINE() Serial.println("--------------------------------------------------\n")
#else
// Non-Arduino environments
#include <stdio.h>
#define LOG_TUPLE(t) printf("TUPLE ID: %s\nTUPLE SIZE: %d\n", t->id, t->size)
#define PART_LINE() printf("--------------------------------------------------\n")
#endif

#endif