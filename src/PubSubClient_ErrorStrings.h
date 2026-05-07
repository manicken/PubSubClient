
#pragma once

enum class PubSubClientResult; // forward declaration

#if  (defined(_WIN32) || defined(__linux__) || defined(__APPLE__))
#define __FlashStringHelper char
#else
class __FlashStringHelper;
#endif

const __FlashStringHelper* PubSubClientErrorToString(PubSubClientResult r);