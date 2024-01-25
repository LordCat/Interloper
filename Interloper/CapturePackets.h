#pragma once

#ifndef CAPTURE_PACKET_H
#define CAPTURE_PACKET_H

#include <string>
#include <coroutine>

class capturePacket {
public:
    // Constructor
    capturePacket(const std::string& sInterface);

    // Coroutine to start packet capture
    struct CaptureCoroutine {
        class promise_type {
        public:
            std::suspend_never initial_suspend() { return {}; }
            std::suspend_never final_suspend() noexcept { return {}; }

            void return_void() {}
            void unhandled_exception() {}

            // This function constructs an instance of CaptureCoroutine
            CaptureCoroutine get_return_object() {
                return CaptureCoroutine{ std::coroutine_handle<promise_type>::from_promise(*this) };
            }
        };

        // Coroutine handle
        std::coroutine_handle<promise_type> coro_Handle;

        // Coroutine constructor 
        CaptureCoroutine(std::coroutine_handle<promise_type> coroutine)
            : coro_Handle(coroutine) {}

        // Awaiting able type for suspending and resuming the coroutine
        struct awaiter {
            bool await_ready() const { return false; }
            void await_suspend(std::coroutine_handle<> coroutine) const;
            void await_resume() const {}
        };
    };

    // Function to start capture
    CaptureCoroutine startCapture();

private:
    std::string selectedInterface;

    // Function to perform the actual packet capture
    void startCaptureAsync(std::coroutine_handle<> coroutine);
};

#endif
