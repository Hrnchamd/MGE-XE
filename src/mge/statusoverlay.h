#pragma once

struct IDirect3DDevice9;

namespace StatusOverlay {
    enum Priority {
        PriorityNormal = 1,
        PriorityWarning = 5,
        PriorityError = 10
    };

    bool init(IDirect3DDevice9* device);
    void release();
    void show(IDirect3DDevice9* device);
    void setStatus(const char* s, int priority = PriorityNormal);
    void setFPS(float fps);
    void showLastStatus();
};
