// Copyright 2024 Accenture.
#include "app/CanRpmListener.h"
#include <can/CanLogger.h>
namespace can
{
using ::util::logger::CAN;
using ::util::logger::Logger;
CanRpmListener::CanRpmListener(::can::ICanTransceiver* canTransceiver)
: _canFilter(), _canTransceiver(canTransceiver)
{}
::can::IFilter& CanRpmListener::getFilter() { return _canFilter; }
void CanRpmListener::frameReceived(::can::CANFrame const& frame)
{
    uint8_t const* payload = frame.getPayload();
    uint16_t const rpm     = (static_cast<uint16_t>(payload[0]) << 8U) | payload[1];
    Logger::debug(
        CAN,
        "[CanRpmListener] RPM received on id=0x%X: %u RPM",
        (int)frame.getId(),
        (unsigned int)rpm);
}
void CanRpmListener::run()
{
    _canFilter.add(0x123);
    if (_canTransceiver != nullptr)
    {
        _canTransceiver->addCANFrameListener(*this);
    }
}
void CanRpmListener::shutdown()
{
    if (_canTransceiver != nullptr)
    {
        _canTransceiver->removeCANFrameListener(*this);asd
    }
}
} // namespace can
