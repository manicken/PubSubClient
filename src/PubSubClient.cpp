/*

  PubSubClient.cpp - A simple client for MQTT.
  Nick O'Leary
  http://knolleary.net
*/

#include "PubSubClient.h"
#include "Arduino.h"

// both macros are wrapped in classic do {}while(0); to make it "statement-safe"
// not that it's used in statements right now but you never know
#define IF_NOT_SUCCESS_DISCONNECT_TRYSENDERROR(res) \
do { \
    if (res != PubSubClientResult::Success) {\
        disconnect();\
        if (onErrorCallback) {\
            onErrorCallback(this->callbackContexts, res, PubSubClientErrorType::FramingError);\
        }\
    }\
} while(0);

#define IF_NOT_SUCCESS_DISCONNECT_TRYSENDERROR_RETURN(res) \
do { \    
    if (res != PubSubClientResult::Success) {\
        disconnect();\
        if (onErrorCallback) {\
            onErrorCallback(this->callbackContexts, res, PubSubClientErrorType::FramingError);\
        }\
        return false;\
    }\
} while(0);

PubSubClient::PubSubClient() {
    this->_state = MQTT_DISCONNECTED;
    this->_client = NULL;
    //this->stream = NULL;
    setOnPublishHeaderCallback(NULL, NULL);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}

PubSubClient::PubSubClient(Client& client) {
    this->_state = MQTT_DISCONNECTED;
    setClient(client);
    //this->stream = NULL;
    setOnPublishHeaderCallback(NULL, NULL);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}

PubSubClient::PubSubClient(IPAddress addr, uint16_t port, Client& client) {
    this->_state = MQTT_DISCONNECTED;
    setServer(addr, port);
    setClient(client);
    //this->stream = NULL;
    setOnPublishHeaderCallback(NULL, NULL);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
/*PubSubClient::PubSubClient(IPAddress addr, uint16_t port, Client& client, Stream& stream) {
    this->_state = MQTT_DISCONNECTED;
    setServer(addr,port);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}*/
PubSubClient::PubSubClient(IPAddress addr, uint16_t port, void* callbackContext, MQTT_ON_PUBLISH_HEADER_CALLBACK_SIGNATURE, Client& client) {
    this->_state = MQTT_DISCONNECTED;
    setServer(addr, port);
    setOnPublishHeaderCallback(callbackContext, onPublishHeaderCallback);
    setClient(client);
    //this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
/*PubSubClient::PubSubClient(IPAddress addr, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client, Stream& stream) {
    this->_state = MQTT_DISCONNECTED;
    setServer(addr,port);
    setCallback(callback);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}*/

PubSubClient::PubSubClient(uint8_t *ip, uint16_t port, Client& client) {
    this->_state = MQTT_DISCONNECTED;
    setServer(ip, port);
    setClient(client);
    //this->stream = NULL;
    setOnPublishHeaderCallback(NULL, NULL);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
/*PubSubClient::PubSubClient(uint8_t *ip, uint16_t port, Client& client, Stream& stream) {
    this->_state = MQTT_DISCONNECTED;
    setServer(ip,port);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}*/
PubSubClient::PubSubClient(uint8_t *ip, uint16_t port, void* callbackContext, MQTT_ON_PUBLISH_HEADER_CALLBACK_SIGNATURE, Client& client) {
    this->_state = MQTT_DISCONNECTED;
    setServer(ip, port);
    setOnPublishHeaderCallback(callbackContext, onPublishHeaderCallback);
    setClient(client);
    //this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
/*PubSubClient::PubSubClient(uint8_t *ip, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client, Stream& stream) {
    this->_state = MQTT_DISCONNECTED;
    setServer(ip,port);
    setCallback(callback);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}*/

PubSubClient::PubSubClient(const char* domain, uint16_t port, Client& client) {
    this->_state = MQTT_DISCONNECTED;
    setServer(domain,port);
    setClient(client);
    //this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
/*PubSubClient::PubSubClient(const char* domain, uint16_t port, Client& client, Stream& stream) {
    this->_state = MQTT_DISCONNECTED;
    setServer(domain,port);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}*/
PubSubClient::PubSubClient(const char* domain, uint16_t port, void* callbackContext, MQTT_ON_PUBLISH_HEADER_CALLBACK_SIGNATURE, Client& client) {
    this->_state = MQTT_DISCONNECTED;
    setServer(domain,port);
    setOnPublishHeaderCallback(callbackContext, onPublishHeaderCallback);
    setClient(client);
    //this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
/*PubSubClient::PubSubClient(const char* domain, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client, Stream& stream) {
    this->_state = MQTT_DISCONNECTED;
    setServer(domain,port);
    setCallback(callback);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}*/

PubSubClient::~PubSubClient() {
  free(this->buffer);
}

BOOLEAN_TYPE PubSubClient::connect(const char *id) {
    return connect(id,NULL,NULL,0,0,0,0,1);
}

BOOLEAN_TYPE PubSubClient::connect(const char *id, const char *user, const char *pass) {
    return connect(id,user,pass,0,0,0,0,1);
}

BOOLEAN_TYPE PubSubClient::connect(const char *id, const char* willTopic, uint8_t willQos, BOOLEAN_TYPE willRetain, const char* willMessage) {
    return connect(id,NULL,NULL,willTopic,willQos,willRetain,willMessage,1);
}

BOOLEAN_TYPE PubSubClient::connect(const char *id, const char *user, const char *pass, const char* willTopic, uint8_t willQos, BOOLEAN_TYPE willRetain, const char* willMessage) {
    return connect(id,user,pass,willTopic,willQos,willRetain,willMessage,1);
}

BOOLEAN_TYPE PubSubClient::connect(const char *id, const char *user, const char *pass, const char* willTopic, uint8_t willQos, BOOLEAN_TYPE willRetain, const char* willMessage, BOOLEAN_TYPE cleanSession) {
    if (connected()) { return true; }
    int result = 0;


    if(_client->connected()) {
        result = 1;
    } else {
        if (domain != NULL) {
            result = _client->connect(this->domain, this->port);
        } else {
            result = _client->connect(this->ip, this->port);
        }
    }

    if (result == 1) {
        nextMsgId = 1;
        // Leave room in the buffer for header and variable length field
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        unsigned int j;

#if MQTT_VERSION == MQTT_VERSION_3_1
        uint8_t d[9] = {0x00,0x06,'M','Q','I','s','d','p', MQTT_VERSION};
#define MQTT_HEADER_VERSION_LENGTH 9
#elif MQTT_VERSION == MQTT_VERSION_3_1_1
        uint8_t d[7] = {0x00,0x04,'M','Q','T','T',MQTT_VERSION};
#define MQTT_HEADER_VERSION_LENGTH 7
#endif
        for (j = 0;j<MQTT_HEADER_VERSION_LENGTH;j++) {
            this->buffer[length++] = d[j];
        }

        uint8_t v;
        if (willTopic) {
            v = 0x04|(willQos<<3)|(willRetain<<5);
        } else {
            v = 0x00;
        }
        if (cleanSession) {
            v = v|0x02;
        }

        if(user != NULL) {
            v = v|0x80;

            if(pass != NULL) {
                v = v|(0x80>>1);
            }
        }
        this->buffer[length++] = v;

        this->buffer[length++] = ((this->keepAlive) >> 8);
        this->buffer[length++] = ((this->keepAlive) & 0xFF);

        CHECK_STRING_LENGTH(length,id)
        length = writeString(id,this->buffer,length);
        if (willTopic) {
            CHECK_STRING_LENGTH(length,willTopic)
            length = writeString(willTopic,this->buffer,length);
            CHECK_STRING_LENGTH(length,willMessage)
            length = writeString(willMessage,this->buffer,length);
        }

        if(user != NULL) {
            CHECK_STRING_LENGTH(length,user)
            length = writeString(user,this->buffer,length);
            if(pass != NULL) {
                CHECK_STRING_LENGTH(length,pass)
                length = writeString(pass,this->buffer,length);
            }
        }

        write(MQTTCONNECT,this->buffer,length-MQTT_MAX_HEADER_SIZE);

        lastInActivity = lastOutActivity = millis();

        while (!_client->available()) {
            unsigned long t = millis();
            if (t-lastInActivity >= ((int32_t) this->socketTimeout*1000UL)) {
                _state = MQTT_CONNECTION_TIMEOUT;
                _client->stop();
                return false;
            }
        }
        uint8_t llen;
        uint32_t len = readPacket(&llen);

        if (len == 4) {
            if (buffer[3] == 0) {
                lastInActivity = millis();
                pingOutstanding = false;
                _state = MQTT_CONNECTED;
                return true;
            } else {
                _state = buffer[3];
            }
        }
        _client->stop();
    } else {
        _state = MQTT_CONNECT_FAILED;
    }
    return false;
}

// reads a byte into result
BOOLEAN_TYPE PubSubClient::readByte(uint8_t * result) {
   uint32_t previousMillis = millis();
   while(!_client->available()) {
     yield();
     uint32_t currentMillis = millis();
     if(currentMillis - previousMillis >= ((int32_t) this->socketTimeout * 1000)){
       return false;
     }
   }
   *result = _client->read();
   return true;
}

// reads a byte into result[*index] and increments index
BOOLEAN_TYPE PubSubClient::readByte(uint8_t * result, uint16_t * index){
  uint16_t current_index = *index;
  uint8_t * write_address = &(result[current_index]);
  if(readByte(write_address)){
    *index = current_index + 1;
    return true;
  }
  return false;
}

uint32_t PubSubClient::readPacket(uint8_t* lengthLength) {
    uint16_t len = 0;
    if(!readByte(this->buffer, &len)) return 0;
    bool isPublish = (this->buffer[0]&0xF0) == MQTTPUBLISH;
    uint32_t multiplier = 1;
    uint32_t length = 0;
    uint8_t digit = 0;
    uint16_t skip = 0;
    uint32_t start = 0;

    // get variable length
    do {
        if (len == 5) {
            // Invalid remaining length encoding - kill the connection
            _state = MQTT_DISCONNECTED;
            _client->stop();
            return 0;
        }
        if(!readByte(&digit)) return 0;
        this->buffer[len++] = digit;
        length += (digit & 127) * multiplier;
        multiplier <<=7; //multiplier *= 128
    } while ((digit & 128) != 0);
    *lengthLength = len-1;

    if (isPublish) {
        // Read in topic length to calculate bytes to skip over for Stream writing
        if(!readByte(this->buffer, &len)) return 0;
        if(!readByte(this->buffer, &len)) return 0;
        skip = (this->buffer[*lengthLength+1]<<8)+this->buffer[*lengthLength+2];
        start = 2;
        if (this->buffer[0]&MQTTQOS1) {
            // skip message id
            skip += 2;
        }
    }
    uint32_t idx = len;

    for (uint32_t i = start;i<length;i++) {
        if(!readByte(&digit)) return 0;

        if (len < this->bufferSize) {
            this->buffer[len] = digit;
            len++;
        }
        idx++;
    }

    if (idx > this->bufferSize) {
        len = 0; // This will cause the packet to be ignored.
    }
    return len;
}

PubSubClientResult PubSubClient::readHeader() {
    uint8_t control_byte = 0;
    if(!readByte(&control_byte)) {
        return PubSubClientResult::HeaderReadError_FirstByte;
    }
    this->rx_control_byte = control_byte;
    uint8_t type = control_byte >> 4;
    if (type == 0 || type == 15) {
        return PubSubClientResult::HeaderReadError_FirstByteTypeInvalid;
    }
    if ((control_byte & MQTT_QOS_MASK) == MQTTQOS_ERROR) {
        return PubSubClientResult::HeaderReadError_FirstByteQoSInvalid;
    }
    
    uint32_t multiplier = 1;
    uint32_t length = 0;
    uint8_t digit = 0;
    uint8_t vlengthByteCount = 0;

    // get variable length
    do {
        if (vlengthByteCount == 4) {
            return PubSubClientResult::HeaderReadError_VariableLengthCorruption;
        }
        if(!readByte(&digit)) return PubSubClientResult::HeaderReadError_VariableLength;
        length += (digit & 127) * multiplier;
        multiplier <<=7; //multiplier *= 128
        vlengthByteCount++;
    } while (digit & 128);
    rx_length = length;
    return PubSubClientResult::Success;
}

PubSubClientResult PubSubClient::readPublishHeader(uint16_t& topicLength) {
    uint8_t msb, lsb;
    if(!readByte(&msb)) { return PubSubClientResult::PublishHeaderReadError_TopicLengthMSB; }
    if(!readByte(&lsb)) { return PubSubClientResult::PublishHeaderReadError_TopicLengthLSB; }
    topicLength = (msb << 8) | lsb;
    return PubSubClientResult::Success;
}

PubSubClientResult PubSubClient::readBytes(uint8_t* dest, uint32_t count) {
    uint8_t digit = 0;
    for (uint32_t i=0;i<count;i++,dest++) {
        if(!readByte(&digit)) return PubSubClientResult::PayloadReadError;
        *dest = digit;
    }
    return PubSubClientResult::Success;
}

PubSubClientResult PubSubClient::flushBytes(uint32_t count) {
    uint8_t digit = 0;
    for (uint32_t i=0;i<count;i++) {
        if(!readByte(&digit)) return PubSubClientResult::PayloadReadError;
    }
    return PubSubClientResult::Success;
}

BOOLEAN_TYPE PubSubClient::loop() {
    if (connected() == false) { return false; }

    unsigned long t = millis();
    if ((t - lastInActivity > this->keepAlive*1000UL) || (t - lastOutActivity > this->keepAlive*1000UL)) {
        if (pingOutstanding) {
            this->_state = MQTT_CONNECTION_TIMEOUT;
            _client->stop();
            return false;
        } else {
            this->buffer[0] = MQTTPINGREQ;
            this->buffer[1] = 0;
            _client->write(this->buffer,2);
            lastOutActivity = t;
            lastInActivity = t;
            pingOutstanding = true;
        }
    }
    if (_client->available() == 0) { return true; }

    PubSubClientResult res = readHeader();
    IF_NOT_SUCCESS_DISCONNECT_TRYSENDERROR_RETURN(res);

    lastInActivity = t;
    uint8_t type = rx_type();
    if (type == MQTTPUBLISH) {
        uint8_t id_msb, id_lsb;

        if (onPublishHeaderCallback == NULL) {
            res = flushBytes(rx_length);
            IF_NOT_SUCCESS_DISCONNECT_TRYSENDERROR_RETURN(res);
            return true;
        }
        uint16_t topicLengthOut = 0;
        res = readPublishHeader(topicLengthOut);
        IF_NOT_SUCCESS_DISCONNECT_TRYSENDERROR_RETURN(res);

        if (topicLengthOut > this->bufferSize) {
            res = flushBytes(topicLengthOut);
            IF_NOT_SUCCESS_DISCONNECT_TRYSENDERROR(res);

            if (onErrorCallback) {
                onErrorCallback(this->callbackContexts, PubSubClientResult::PreBufferOverflowError_Topic, PubSubClientErrorType::LogicError); // also send this
            }
            return false;
        }
        res = readBytes(this->buffer, topicLengthOut);
        IF_NOT_SUCCESS_DISCONNECT_TRYSENDERROR_RETURN(res);

        if ((uint32_t)(topicLengthOut + 2) > rx_length) {
            disconnect();
            if (onErrorCallback) {
                onErrorCallback(this->callbackContexts, PubSubClientResult::ProtocolError_LengthMismatch, PubSubClientErrorType::FramingError);
            }
            return false;
        }
        uint32_t payloadLength = (rx_length - 2 - topicLengthOut); // -2 because of topic length bytes
        if (rx_flags_qos() > 0) {
            
            if (!readByte(&id_msb) || !readByte(&id_lsb)) {
                disconnect();
                if (onErrorCallback) onErrorCallback(this->callbackContexts, PubSubClientResult::PublishHeaderReadError_PacketId, PubSubClientErrorType::FramingError);
                return false;
            }
            payloadLength -= 2;
        }

        PSC_PublishFlags flags(rx_flags());
        // here the topic is first in the buffer
        this->buffer[topicLengthOut] = '\0'; // null terminate the topic
        PubSubClientPacketReceiver context = onPublishHeaderCallback(this->callbackContexts, (char*)this->buffer, topicLengthOut, payloadLength, flags);
        
        if (context.sink != PubSubClientPayloadSink::Discard) {
            uint32_t currentBuffCapacity = 0;
            uint8_t* currBuff = NULL;
            if (context.buffer != NULL && context.capacity != 0) {
                currentBuffCapacity = context.capacity;
                currBuff = context.buffer;
            } else {
                currentBuffCapacity = this->bufferSize - topicLengthOut - 1; // represent remaining space in buffert -1 is because we added null char to topic
                currBuff = this->buffer + topicLengthOut + 1; // represent from where in buffet to write next +1 is because we added null char to topic
            }

            if (payloadLength > currentBuffCapacity) {
                res = flushBytes(payloadLength);
                IF_NOT_SUCCESS_DISCONNECT_TRYSENDERROR(res);

                if (onErrorCallback) {
                    onErrorCallback(this->callbackContexts, PubSubClientResult::PreBufferOverflowError_Payload, PubSubClientErrorType::LogicError); 
                }
                return false;
            }
            res = readBytes(currBuff, payloadLength);
            IF_NOT_SUCCESS_DISCONNECT_TRYSENDERROR_RETURN(res);

            if (rx_flags_qos() == 1) {
                this->buffer[0] = MQTTPUBACK;
                this->buffer[1] = 2;
                this->buffer[2] = id_msb;
                this->buffer[3] = id_lsb;
                _client->write(this->buffer, 4);
                lastOutActivity = t;
            }
            if (context.onPublishCompleteCallback) {
                context.onPublishCompleteCallback(this->callbackContexts, (char*)this->buffer, topicLengthOut, currBuff, payloadLength);
            }
            return true;
        } else {
            res = flushBytes(payloadLength);
            IF_NOT_SUCCESS_DISCONNECT_TRYSENDERROR_RETURN(res);

            if (rx_flags_qos() == 1) {
                this->buffer[0] = MQTTPUBACK;
                this->buffer[1] = 2;
                this->buffer[2] = id_msb;
                this->buffer[3] = id_lsb;
                _client->write(this->buffer, 4);
            }
            if (context.onPublishCompleteCallback) {
                context.onPublishCompleteCallback(this->callbackContexts, (char*)this->buffer, topicLengthOut, NULL, 0);
            }
            return true;
        }
    } else if (type == MQTTPINGREQ) {
        this->buffer[0] = MQTTPINGRESP;
        this->buffer[1] = 0;
        _client->write(this->buffer,2);
    } else if (type == MQTTPINGRESP) {
        pingOutstanding = false;
    }
    return true;
}

BOOLEAN_TYPE PubSubClient::publish(const char* topic, const char* payload) {
    return publish(topic,(const uint8_t*)payload, payload ? strnlen(payload, this->bufferSize) : 0,false);
}

BOOLEAN_TYPE PubSubClient::publish(const char* topic, const char* payload, BOOLEAN_TYPE retained) {
    return publish(topic,(const uint8_t*)payload, payload ? strnlen(payload, this->bufferSize) : 0,retained);
}

BOOLEAN_TYPE PubSubClient::publish(const char* topic, const uint8_t* payload, unsigned int plength) {
    return publish(topic, payload, plength, false);
}

BOOLEAN_TYPE PubSubClient::publish(const char* topic, const uint8_t* payload, unsigned int plength, BOOLEAN_TYPE retained) {
    if (connected()) {
        if (this->bufferSize < MQTT_MAX_HEADER_SIZE + 2+strnlen(topic, this->bufferSize) + plength) {
            // Too long
            return false;
        }
        // Leave room in the buffer for header and variable length field
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        length = writeString(topic,this->buffer,length);

        // Add payload
        uint16_t i;
        for (i=0;i<plength;i++) {
            this->buffer[length++] = payload[i];
        }

        // Write the header
        uint8_t header = MQTTPUBLISH;
        if (retained) {
            header |= 1;
        }
        return write(header,this->buffer,length-MQTT_MAX_HEADER_SIZE);
    }
    return false;
}

BOOLEAN_TYPE PubSubClient::publish_P(const char* topic, const char* payload, BOOLEAN_TYPE retained) {
    return publish_P(topic, (const uint8_t*)payload, payload ? strnlen(payload, this->bufferSize) : 0, retained);
}

BOOLEAN_TYPE PubSubClient::publish_P(const char* topic, const uint8_t* payload, unsigned int plength, BOOLEAN_TYPE retained) {
    uint8_t llen = 0;
    uint8_t digit;
    unsigned int rc = 0;
    uint16_t tlen;
    unsigned int pos = 0;
    unsigned int i;
    uint8_t header;
    unsigned int len;
    int expectedLength;

    if (!connected()) {
        return false;
    }

    tlen = strnlen(topic, this->bufferSize);

    header = MQTTPUBLISH;
    if (retained) {
        header |= 1;
    }
    this->buffer[pos++] = header;
    len = plength + 2 + tlen;
    do {
        digit = len  & 127; //digit = len %128
        len >>= 7; //len = len / 128
        if (len > 0) {
            digit |= 0x80;
        }
        this->buffer[pos++] = digit;
        llen++;
    } while(len>0);

    pos = writeString(topic,this->buffer,pos);

    rc += _client->write(this->buffer,pos);

    for (i=0;i<plength;i++) {
        rc += _client->write((char)pgm_read_byte_near(payload + i));
    }

    lastOutActivity = millis();

    expectedLength = 1 + llen + 2 + tlen + plength;

    return (rc == (unsigned int)expectedLength);
}

BOOLEAN_TYPE PubSubClient::beginPublish(const char* topic, unsigned int plength, BOOLEAN_TYPE retained) {
    if (connected()) {
        // Send the header and variable length field
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        length = writeString(topic,this->buffer,length);
        uint8_t header = MQTTPUBLISH;
        if (retained) {
            header |= 1;
        }
        size_t hlen = buildHeader(header, this->buffer, plength+length-MQTT_MAX_HEADER_SIZE);
        uint16_t rc = _client->write(this->buffer+(MQTT_MAX_HEADER_SIZE-hlen),length-(MQTT_MAX_HEADER_SIZE-hlen));
        lastOutActivity = millis();
        return (rc == (length-(MQTT_MAX_HEADER_SIZE-hlen)));
    }
    return false;
}

BOOLEAN_TYPE PubSubClient::beginPublishF(const char* topic, unsigned int plength, BOOLEAN_TYPE retained) {
    if (connected() == false) { return false; }

    // Send the header and variable length field
    uint16_t length = MQTT_MAX_HEADER_SIZE;
    length = writeString(topic,this->buffer,length);
    uint8_t header = MQTTPUBLISH;
    if (retained) {
        header |= 1;
    }
    size_t hlen = buildHeader(header, this->buffer, plength+length-MQTT_MAX_HEADER_SIZE);
    uint16_t rc = _client->write(this->buffer+(MQTT_MAX_HEADER_SIZE-hlen),length-(MQTT_MAX_HEADER_SIZE-hlen));
    lastOutActivity = millis();
    return (rc == (length-(MQTT_MAX_HEADER_SIZE-hlen)));
}

int PubSubClient::endPublish() {
 return 1;
}

size_t PubSubClient::write(uint8_t data) {
    lastOutActivity = millis();
    return _client->write(data);
}

size_t PubSubClient::write(const uint8_t *buffer, size_t size) {
    lastOutActivity = millis();
    return _client->write(buffer,size);
}

size_t PubSubClient::buildHeader(uint8_t header, uint8_t* buf, uint16_t length) {
    uint8_t lenBuf[4];
    uint8_t llen = 0;
    uint8_t digit;
    uint8_t pos = 0;
    uint16_t len = length;
    do {

        digit = len  & 127; //digit = len %128
        len >>= 7; //len = len / 128
        if (len > 0) {
            digit |= 0x80;
        }
        lenBuf[pos++] = digit;
        llen++;
    } while(len>0);

    buf[4-llen] = header;
    for (int i=0;i<llen;i++) {
        buf[MQTT_MAX_HEADER_SIZE-llen+i] = lenBuf[i];
    }
    return llen+1; // Full header size is variable length bit plus the 1-byte fixed header
}

BOOLEAN_TYPE PubSubClient::write(uint8_t header, uint8_t* buf, uint16_t length) {
    uint16_t rc;
    uint8_t hlen = buildHeader(header, buf, length);

#ifdef MQTT_MAX_TRANSFER_SIZE
    uint8_t* writeBuf = buf+(MQTT_MAX_HEADER_SIZE-hlen);
    uint16_t bytesRemaining = length+hlen;  //Match the length type
    uint8_t bytesToWrite;
    BOOLEAN_TYPE result = true;
    while((bytesRemaining > 0) && result) {
        bytesToWrite = (bytesRemaining > MQTT_MAX_TRANSFER_SIZE)?MQTT_MAX_TRANSFER_SIZE:bytesRemaining;
        rc = _client->write(writeBuf,bytesToWrite);
        result = (rc == bytesToWrite);
        bytesRemaining -= rc;
        writeBuf += rc;
    }
    return result;
#else
    rc = _client->write(buf+(MQTT_MAX_HEADER_SIZE-hlen),length+hlen);
    lastOutActivity = millis();
    return (rc == hlen+length);
#endif
}

BOOLEAN_TYPE PubSubClient::subscribe(const char* topic) {
    return subscribe(topic, 0);
}

BOOLEAN_TYPE PubSubClient::subscribe(const char* topic, uint8_t qos) {
    size_t topicLength = strnlen(topic, this->bufferSize);
    if (topic == NULL) {
        return false;
    }
    if (qos > 1) {
        return false;
    }
    if (this->bufferSize < 9 + topicLength) {
        // Too long
        return false;
    }
    if (connected()) {
        // Leave room in the buffer for header and variable length field
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        nextMsgId++;
        if (nextMsgId == 0) {
            nextMsgId = 1;
        }
        this->buffer[length++] = (nextMsgId >> 8);
        this->buffer[length++] = (nextMsgId & 0xFF);
        length = writeString((char*)topic, this->buffer,length);
        this->buffer[length++] = qos;
        return write(MQTTSUBSCRIBE|MQTTQOS1,this->buffer,length-MQTT_MAX_HEADER_SIZE);
    }
    return false;
}

BOOLEAN_TYPE PubSubClient::subscribe_fmt(const char* fmt, uint8_t qos, ...) {
    if (connected() == false) { return false; }
    //size_t topicLength = strnlen(topic, this->bufferSize);
    if (fmt == NULL) {
        return false;
    }
    if (qos > 1) { // according to MQTT 3.1.1 spec, qos = 2 is invalid for SUBSCRIBE packets, and qos>2 is generally invalid
        return false;
    }
    va_list args, args_copy;
    va_start(args, fmt);
    va_copy(args_copy, args);

    int topicLength = vsnprintf(nullptr, 0, fmt, args_copy);
    va_end(args_copy);

    if (topicLength <= 0 || (topicLength+MQTT_MAX_HEADER_SIZE+5) >= bufferSize) { // 9 is from fixed header (1) + (max)vlength byte count (4) + topic length bytes (2) + message id bytes (2) 
        va_end(args);
        return false;
    }

    uint16_t bufferPos = MQTT_MAX_HEADER_SIZE;

    // MQTT packetId must be non-zero; wrap 0 → 1
    if (++nextMsgId == 0) {
        nextMsgId = 1;
    }
    this->buffer[bufferPos++] = (nextMsgId >> 8);
    this->buffer[bufferPos++] = (nextMsgId & 0xFF);
    this->buffer[bufferPos++] = ((uint16_t)topicLength >> 8);
    this->buffer[bufferPos++] = ((uint16_t)topicLength & 0xFF);

    int written = vsnprintf((char*)(this->buffer + bufferPos), this->bufferSize - bufferPos, fmt, args);
    va_end(args);

    if (written < 0 || written != topicLength) {
        return false;  // Format string mismatch or error
    }
    bufferPos += topicLength;

    this->buffer[bufferPos++] = qos;
    return write(MQTTSUBSCRIBE | MQTTQOS1, this->buffer, bufferPos - MQTT_MAX_HEADER_SIZE);

}

BOOLEAN_TYPE PubSubClient::unsubscribe(const char* topic) {
	size_t topicLength = strnlen(topic, this->bufferSize);
    if (topic == 0) {
        return false;
    }
    if (this->bufferSize < 9 + topicLength) {
        // Too long
        return false;
    }
    if (connected()) {
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        nextMsgId++;
        if (nextMsgId == 0) {
            nextMsgId = 1;
        }
        this->buffer[length++] = (nextMsgId >> 8);
        this->buffer[length++] = (nextMsgId & 0xFF);
        length = writeString(topic, this->buffer,length);
        return write(MQTTUNSUBSCRIBE|MQTTQOS1,this->buffer,length-MQTT_MAX_HEADER_SIZE);
    }
    return false;
}

void PubSubClient::disconnect() {
    this->buffer[0] = MQTTDISCONNECT;
    this->buffer[1] = 0;
    _client->write(this->buffer,2);
    _state = MQTT_DISCONNECTED;
    _client->flush();
    _client->stop();
    lastInActivity = lastOutActivity = millis();
}

uint16_t PubSubClient::writeString(const char* string, uint8_t* buf, uint16_t pos) {
    const char* idp = string;
    uint16_t i = 0;
    pos += 2;
    while (*idp) {
        buf[pos++] = *idp++;
        i++;
    }
    buf[pos-i-2] = (i >> 8);
    buf[pos-i-1] = (i & 0xFF);
    return pos;
}

/*uint16_t PubSubClient::writeString(const char* string, uint8_t* buf, uint16_t offset) {
    const char* idp = string;
    uint16_t size = 0;
    uint16_t pos = offset;
    pos += 2;
    while (*idp) {
        buf[pos++] = *idp++;
        size++;
    }
    buf[offset] = (size >> 8);
    buf[offset+1] = (size & 0xFF);
    return pos;
}*/

BOOLEAN_TYPE PubSubClient::connected() {
    BOOLEAN_TYPE rc;
    if (_client == NULL ) {
        rc = false;
    } else {
        rc = (int)_client->connected();
        if (!rc) {
            if (this->_state == MQTT_CONNECTED) {
                this->_state = MQTT_CONNECTION_LOST;
                _client->flush();
                _client->stop();
            }
        } else {
            return this->_state == MQTT_CONNECTED;
        }
    }
    return rc;
}

PubSubClient& PubSubClient::setServer(uint8_t * ip, uint16_t port) {
    IPAddress addr(ip[0],ip[1],ip[2],ip[3]);
    return setServer(addr,port);
}

PubSubClient& PubSubClient::setServer(IPAddress ip, uint16_t port) {
    this->ip = ip;
    this->port = port;
    this->domain = NULL;
    return *this;
}

PubSubClient& PubSubClient::setServer(const char * domain, uint16_t port) {
    this->domain = domain;
    this->port = port;
    return *this;
}

PubSubClient& PubSubClient::setOnPublishHeaderCallback(void* context, MQTT_ON_PUBLISH_HEADER_CALLBACK_SIGNATURE) {
    this->callbackContexts = context;
    this->onPublishHeaderCallback = onPublishHeaderCallback;
    return *this;
}
PubSubClient& PubSubClient::setOnErrorCallback(void* context, MQTT_ON_ERROR_CALLBACK_SIGNATURE) {
    this->callbackContexts = context;
    this->onErrorCallback = onErrorCallback;
    return *this;
}

PubSubClient& PubSubClient::setClient(Client& client){
    this->_client = &client;
    return *this;
}

/*PubSubClient& PubSubClient::setStream(Stream& stream){
    this->stream = &stream;
    return *this;
}*/

int PubSubClient::state() {
    return this->_state;
}

BOOLEAN_TYPE PubSubClient::setBufferSize(uint16_t size) {
    if (size == 0) {
        // Cannot set it back to 0
        return false;
    }
    if (this->bufferSize == 0) {
        this->buffer = (uint8_t*)malloc(size);
    } else {
        uint8_t* newBuffer = (uint8_t*)realloc(this->buffer, size);
        if (newBuffer != NULL) {
            this->buffer = newBuffer;
        } else {
            return false;
        }
    }
    this->bufferSize = size;
    return (this->buffer != NULL);
}

uint16_t PubSubClient::getBufferSize() {
    return this->bufferSize;
}
PubSubClient& PubSubClient::setKeepAlive(uint16_t keepAlive) {
    this->keepAlive = keepAlive;
    return *this;
}
PubSubClient& PubSubClient::setSocketTimeout(uint16_t timeout) {
    this->socketTimeout = timeout;
    return *this;
}
