#pragma once

#ifndef PcapGather_H
#define PcapGather_H
#endif

#include "pcap.h"
#include <coroutine>
#include <optional>



struct PacketCaptureAwaiter {
	pcap_t* handle;
	pc
};