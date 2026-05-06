#include "PubSubClient_ErrorStrings.h"
#include "PubSubClient.h"

const __FlashStringHelper* PubSubClientErrorToString(PubSubClientResult r) {
    switch (r) {
        case PubSubClientResult::HeaderReadError_FirstByte: return F("HeaderReadError_FirstByte");
        case PubSubClientResult::HeaderReadError_FirstByteQoSInvalid: return F("HeaderReadError_FirstByteQoSInvalid");
        case PubSubClientResult::HeaderReadError_FirstByteTypeInvalid: return F("HeaderReadError_FirstByteTypeInvalid");
        case PubSubClientResult::HeaderReadError_VariableLength: return F("HeaderReadError_VariableLength");
        case PubSubClientResult::HeaderReadError_VariableLengthCorruption: return F("HeaderReadError_VariableLengthCorruption");
        case PubSubClientResult::PayloadReadError: return F("PayloadReadError");
        case PubSubClientResult::PreBufferOverflowError: return F("PreBufferOverflowError");

        case PubSubClientResult::PreBufferOverflowError_Payload: return F("PreBufferOverflowError_Payload");
        case PubSubClientResult::PreBufferOverflowError_Topic: return F("PreBufferOverflowError_Topic");
        case PubSubClientResult::ProtocolError_LengthMismatch: return F("ProtocolError_LengthMismatch");
        case PubSubClientResult::PublishHeaderReadError_PacketId: return F("PublishHeaderReadError_PacketId");
        case PubSubClientResult::PublishHeaderReadError_TopicLengthLSB: return F("PublishHeaderReadError_TopicLengthLSB");
        case PubSubClientResult::PublishHeaderReadError_TopicLengthMSB: return F("PublishHeaderReadError_TopicLengthMSB");
        case PubSubClientResult::Success: return F("Success");
        default:
            return F("UnknownError");
    }
    return F("Unknown error");
}