#pragma once

#ifndef PcapGather_H
#define PcapGather_H
#endif

#include <coroutine>
#include <optional>
#include <pcap.h>



struct PacketCaptureAwaiter {
	pcap_t* handle;
	pc
};