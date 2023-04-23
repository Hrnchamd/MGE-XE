#pragma once

class MWInitPatch {
public:
    static void disableIntroMovies();
    static void patchTextureLoading();
    static void patchUIInit();
    static void patchFrameTimer();
};
