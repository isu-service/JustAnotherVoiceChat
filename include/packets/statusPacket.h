/*
 * File: include/statusPacket.h
 * Date: 20.07.2018
 *
 * MIT License
 *
 * Copyright (c) 2018 JustAnotherVoiceChat
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "networkPacket.h"

namespace javic {
    namespace packets {
        typedef enum {
            STATUS_PACKET_TYPE_UNKNOWN = 0,
        } statusPacketType_t;

        class StatusPacket : public NetworkPacket {
        private:
            bool _talking;
            bool _microphoneMuted;
            bool _speakersMuted;

        public:
            StatusPacket() : NetworkPacket(STATUS_PACKET_TYPE_UNKNOWN) {
                _talking = false;
                _microphoneMuted = false;
                _speakersMuted = false;
            }

            StatusPacket(statusPacketType_t type) : NetworkPacket(type) {
                _talking = false;
                _microphoneMuted = false;
                _speakersMuted = false;
            }

            enet_uint8 channel() const override {
                return PACKET_CHANNEL_STATUS;
            }

            void setTalking(bool talking) {
                _talking = talking;
            }

            bool talking() const {
                return _talking;
            }

            void setMicrophoneMuted(bool microphoneMuted) {
                _microphoneMuted = microphoneMuted;
            }

            bool microphoneMuted() const {
                return _microphoneMuted;
            }

            void setSpeakersMuted(bool speakersMuted) {
                _speakersMuted = speakersMuted;
            }

            bool speakersMuted() const {
                return _speakersMuted;
            }

            friend class cereal::access;

            template<class Archive>
            void serialize(Archive &ar) {
                ar(CEREAL_NVP(_type),
                   CEREAL_NVP(_talking),
                   CEREAL_NVP(_microphoneMuted),
                   CEREAL_NVP(_speakersMuted)
                );
            }
        };
    }
}