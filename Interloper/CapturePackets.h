#pragma once

#ifndef CAPTURE_PACKET_H
#define CAPTURE_PACKET_H

#include <string>
#include <coroutine>

class capturePacket {
public: 
	//constructor
	capturePacket(const std::string& sInterface);

	//corountine to start packet capture
	struct CaptureCoroutine {
		capturePacket& parent;

		//promise type for co-routine
		struct promise_type {
			std::suspend_never intital_suspend() { return {}; }
			std::suspend_never final_suspend() noexcept { return {}; }

			void return_void() {}
			void unhandled_expection() {}
		};

		//co-routien handle
		std::coroutine_handle<promise_type> coro_Handle;

		//co-routine constructor 
		CaptureCoroutine(capturePacket& p, std::coroutine_handle<promise_type> coroutine)
			: parent(p), coro_Handle(coroutine) {}

		//awaiting able type for suspending and resuming the co-rountine
		struct awaiter {
			capturePacket& parent;
			bool await_ready() const { return false; }
			void await_suspend(std::coroutine_handle<> coroutine) const;
			void await_resume() const {}
		};

		awaiter operator co_await() const { return { parent }; }

	};



	//function to start capture
	CaptureCoroutine startCapture();

private:
	std::string selectedInterface;

	// Function to perform the actual packet capture
	void startCaptureAsync(std::coroutine_handle<> coroutine);
};

#endif