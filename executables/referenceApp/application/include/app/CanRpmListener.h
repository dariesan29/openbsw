// Copyright 2024 Accenture.
#pragma once
#include <can/filter/BitFieldFilter.h> // pre-integration testing, to be removed later
#include <can/transceiver/AbstractCANTransceiver.h>
namespace can
{
class CanRpmListener final
: public ::can::ICANFrameListener
{
public:
    CanRpmListener(::can::ICanTransceiver* canTransceiver);
    void run();
    void shutdown();
    void frameReceived(::can::CANFrame const& frame) final;
    ::can::IFilter& getFilter() final;
private:
    ::can::BitFieldFilter _canFilter;
    ::can::ICanTransceiver* _canTransceiver;
};
} // namespace can

