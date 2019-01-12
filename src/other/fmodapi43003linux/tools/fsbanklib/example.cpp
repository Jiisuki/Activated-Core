/*
    This example builds the fsb's require for the designer api examples
*/

#include "fsbanklib.h"

#include <stdio.h>

#define NUM_TUTORIAL_FILES   59
#define NUM_STREAMING_FILES  1

// FMOD 3 Defines
#define FSOUND_HW3D  0x00001000  /* Attempts to make samples use 3d hardware acceleration. (if the card supports it) */
#define FSOUND_2D    0x00002000  /* Tells software (not hardware) based sample not to be included in 3d processing. */
#define FSOUND_HW2D  0x00080000  /* 2D hardware sounds.  allows hardware specific effects */
#define FSOUND_3D    0x00100000  /* 3D software sounds */

/* 
 * Sample defaults: { mindistance, maxdistance, deffreq, defvol, defpan, defpri, varfreq, varvol,
 *                    varpan, mode, quality, optimizesamplerate, optimizedratereduction, buildflags }
 */ 
FSBANK_SAMPLE_DEFAULTS hw3d    = { -1.0f, -1.0f, -1, -1, -2, -1, -1, -1, -1, FSOUND_HW3D,           -1, false, 100.0f, 0 };
FSBANK_SAMPLE_DEFAULTS hw2d    = { -1.0f, -1.0f, -1, -1, -2, -1, -1, -1, -1, FSOUND_HW2D,           -1, false, 100.0f, 0 };
FSBANK_SAMPLE_DEFAULTS sw3d    = { -1.0f, -1.0f, -1, -1, -2, -1, -1, -1, -1, FSOUND_3D,             -1, false, 100.0f, 0 };
FSBANK_SAMPLE_DEFAULTS sw2d    = { -1.0f, -1.0f, -1, -1, -2, -1, -1, -1, -1, FSOUND_2D,             -1, false, 100.0f, 0 };
FSBANK_SAMPLE_DEFAULTS sw2d3d  = { -1.0f, -1.0f, -1, -1, -2, -1, -1, -1, -1, FSOUND_2D | FSOUND_3D, -1, false, 100.0f, 0 };

char *tutorialfiles[NUM_TUTORIAL_FILES] =
{
    "../../fmoddesignerapi/examples/media/music/flsh-idle-05.ogg",
    "../../fmoddesignerapi/examples/media/cycle-stop.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-d.ogg",
    "../../fmoddesignerapi/examples/media/note.ogg",
    "../../fmoddesignerapi/examples/media/ambient_two.ogg",
    "../../fmoddesignerapi/examples/media/music/state-race-finish.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-a.ogg",
    "../../fmoddesignerapi/examples/media/max_play_behavior_two.ogg",
    "../../fmoddesignerapi/examples/media/music/state-idle-fadeout.ogg",
    "../../fmoddesignerapi/examples/media/car/onmid.ogg",
    "../../fmoddesignerapi/examples/media/sequence-three.ogg",
    "../../fmoddesignerapi/examples/media/car/offhigh.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-drums-d.ogg",
    "../../fmoddesignerapi/examples/media/car/idle.ogg",
    "../../fmoddesignerapi/examples/media/car/offlow.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-c.ogg",
    "../../fmoddesignerapi/examples/media/music/state-race-02a.ogg",
    "../../fmoddesignerapi/examples/media/music/flsh-idle-02.ogg",
    "../../fmoddesignerapi/examples/media/drum-loop.ogg",
    "../../fmoddesignerapi/examples/media/music/state-idle-01.ogg",
    "../../fmoddesignerapi/examples/media/sequence-start.ogg",
    "../../fmoddesignerapi/examples/media/music/state-race-01a.ogg",
    "../../fmoddesignerapi/examples/media/ambient_one_four.ogg",
    "../../fmoddesignerapi/examples/media/music/flsh-idle-01.ogg",
    "../../fmoddesignerapi/examples/media/max_play_behavior_one.ogg",
    "../../fmoddesignerapi/examples/media/cycle-start.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-alt-c.ogg",
    "../../fmoddesignerapi/examples/media/music/state-idle-02.ogg",
    "../../fmoddesignerapi/examples/media/ambient_three.ogg",
    "../../fmoddesignerapi/examples/media/car/offmid.ogg",
    "../../fmoddesignerapi/examples/media/music/excited.ogg",
    "../../fmoddesignerapi/examples/media/music/flsh-idle-04.ogg",
    "../../fmoddesignerapi/examples/media/car/onlow.ogg",
    "../../fmoddesignerapi/examples/media/music/state-idle-03.ogg",
    "../../fmoddesignerapi/examples/media/sequence-four.ogg",
    "../../fmoddesignerapi/examples/media/music/state-race-02b.ogg",
    "../../fmoddesignerapi/examples/media/sequence-one.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-drums-a.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-alt-d.ogg",
    "../../fmoddesignerapi/examples/media/music/flsh-idle-03.ogg",
    "../../fmoddesignerapi/examples/media/ambient_one_loop.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-bass-a.ogg",
    "../../fmoddesignerapi/examples/media/interactive_music_2.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-b.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-alt-a.ogg",
    "../../fmoddesignerapi/examples/media/max_play_behavior_four.ogg",
    "../../fmoddesignerapi/examples/media/cycle-sustain.ogg",
    "../../fmoddesignerapi/examples/media/music/state-race-start.ogg",
    "../../fmoddesignerapi/examples/media/music/relaxed.ogg",
    "../../fmoddesignerapi/examples/media/music/state-race-01b.ogg",
    "../../fmoddesignerapi/examples/media/car/onhigh.ogg",
    "../../fmoddesignerapi/examples/media/sequence-two.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-drums-b.ogg",
    "../../fmoddesignerapi/examples/media/interactive_music_3.ogg",
    "../../fmoddesignerapi/examples/media/sequence-end.ogg",
    "../../fmoddesignerapi/examples/media/max_play_behavior_three.ogg",
    "../../fmoddesignerapi/examples/media/interactive_music_1.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-drums-c.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-alt-b.ogg"
};

FSBANK_SAMPLE_DEFAULTS *tutorialdefaults[NUM_TUTORIAL_FILES] =
{
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d3d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw3d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d3d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw3d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d3d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw3d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw2d,
    &sw3d,
    &sw2d,
    &sw2d,
    &sw2d
};

char *streamingfiles[NUM_STREAMING_FILES] =
{
    "../../fmoddesignerapi/examples/media/interactive_music_6channel.ogg"
};

FSBANK_SAMPLE_DEFAULTS *streamingdefaults[NUM_STREAMING_FILES] =
{
    &sw2d
};

void Update(int index, int memused, void *userdata)
{
    printf("UPDATE : File %d, memory used %d kb\n", index, memused / 1024);
}

void Debug(const char *debugstring, void *userdata)
{
    printf("DEBUG  : %s\n", debugstring);
}

int main(void)
{
    FSBANK_RESULT result;

    result = FSBank_Init();
    if (result != FSBANK_OK)
    {
        printf("ERROR\n");
        return -1;
    }

    result = FSBank_SetUpdateCallback(Update, 0);
    if (result != FSBANK_OK)
    {
        printf("ERROR\n");
        return -1;
    }

    result = FSBank_SetDebugCallback(Debug, 0);
    if (result != FSBANK_OK)
    {
        printf("ERROR\n");
        return -1;
    }

    printf("Building tutorial_bank.fsb...\n");
    result = FSBank_Build(FSBANK_BUILDMODE_SINGLE, FSBANK_FORMAT_PCM, FSBANK_PLATFORM_PC, FSBANK_BUILD_COMPRESSIONCACHING, 0, "tutorial_bank.fsb", NUM_TUTORIAL_FILES, &tutorialfiles[0], &tutorialdefaults[0], 0, 50);
    if (result != FSBANK_OK)
    {
        printf("ERROR\n");
        return -1;
    }
    printf("done.\n");

    printf("Building streaming_bank.fsb...\n");
    result = FSBank_Build(FSBANK_BUILDMODE_SINGLE, FSBANK_FORMAT_PCM, FSBANK_PLATFORM_PC, FSBANK_BUILD_COMPRESSIONCACHING, 0, "streaming_bank.fsb", NUM_STREAMING_FILES, &streamingfiles[0], &streamingdefaults[0], 0, 50);
    printf("done.\n");

    result = FSBank_Close();
    if (result != FSBANK_OK)
    {
        printf("ERROR\n");
        return -1;
    }

    return 0;
}
