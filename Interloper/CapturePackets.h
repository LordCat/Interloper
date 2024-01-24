#pragma once

#ifndef CAPTURE_PACKET_H
#define CAPTURE_PACKET_H

#include <string>
#include <coroutine>

class capturePacket {
public: 
	//constructor
	capturePacket(const std::string& interface);

	//corountine to start packet capture
	struct CaptureCoroutine { 
		capturePacket& parent;

		//awaiteable type for suspending and resuming the coroutine
		struct awaiter {
			capturePacket& parent;
			bool await_ready() const {
				return false;
			}
			void await_suspend(std::coroutine_handle<> corountine) const;
	//function to start capture
	void startCapture();

private:
	std::string selectedInterface;
};

#endif