/*****************************************************************************
 * Copyright (c) 2014 Ted John
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * This file is part of OpenRCT2.
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <guiddef.h>

#include "../common.h"
#include "../world/sprite.h"

typedef struct {
	char name[256];
} audio_device;

extern int gAudioDeviceCount;
extern audio_device *gAudioDevices;

#define AUDIO_MAX_VEHICLE_SOUNDS 14
#define AUDIO_MAX_RIDE_MUSIC 2

void audio_init();
void audio_quit();
void audio_get_devices();

/**
 * Represents a single directsound device.
 */
typedef struct {
	GUID guid;
	char desc[256];
	char drvname[256];
} rct_dsdevice;

/**
 * Represents a prepared sound.
 */
typedef struct rct_sound {
	struct IDirectSoundBuffer *dsbuffer;
	uint16 id;
	uint16 var_8;
	int has_caps;
	int var_0C;
	struct rct_sound* next;
} rct_sound;

typedef struct {
	uint16 id;
	sint16 volume;			// 0x02
	rct_sound sound1;		// 0x04
	uint16 sound1_id;		// 0x18
	sint16 sound1_volume;	// 0x1A
	sint16 sound1_pan;		// 0x1C
	uint16 sound1_freq;
	rct_sound sound2;		// 0x20
	uint16 sound2_id;		// 0x34
	sint16 sound2_volume;	// 0x36
	sint16 sound2_pan;		// 0x38
	uint16 sound2_freq;		// 0x3A
	// added to openrct2:
	void* sound1_channel;
	void* sound2_channel;
} rct_vehicle_sound;

typedef struct {
	uint16 id;
	sint16 panx;		// 0x2
	sint16 pany;		// 0x4
	uint16 frequency;	// 0x6
	sint16 volume;	// 0x8
	uint16 var_A;		// 0xA
} rct_vehicle_sound_params;

typedef struct {
	uint16 id;
	rct_sound sound;
} rct_other_sound;

typedef struct {
	uint8 rideid;
	uint8 tuneid;
	sint32 offset;	//0x2
	sint16 volume;	//0x6
	sint16 pan;		//0x8
	uint16 freq;	//0xA
} rct_ride_music_params;

typedef struct {
	uint8 rideid;
	uint8 tuneid;
	sint16 volume;	//0x2
	sint16 pan;		//0x4
	uint16 freq;	//0x6
	// added to openrct2:
	void* sound_channel;
} rct_ride_music;

typedef struct {
	uint32 length;
	uint32 offset;
	uint8 pathid;	//0x8
	uint8 var_9;
} rct_ride_music_info;

struct rct_sound_effect;

#define NUM_DEFAULT_MUSIC_TRACKS 46
extern rct_ride_music_info* ride_music_info_list[NUM_DEFAULT_MUSIC_TRACKS];
extern rct_vehicle_sound gVehicleSoundList[AUDIO_MAX_VEHICLE_SOUNDS];
extern rct_vehicle_sound_params gVehicleSoundParamsList[AUDIO_MAX_VEHICLE_SOUNDS];
extern rct_vehicle_sound_params *gVehicleSoundParamsListEnd;
extern rct_ride_music gRideMusicList[AUDIO_MAX_RIDE_MUSIC];
extern rct_ride_music_params gRideMusicParamsList[AUDIO_MAX_RIDE_MUSIC];
extern rct_ride_music_params *gRideMusicParamsListEnd;
extern void *gCrowdSoundChannel;
extern void *gTitleMusicChannel;
extern bool gGameSoundsOff;

int sub_40153B(int channel);
int sub_4015E7(int channel);
int sound_channel_load_file(int channel, const char* filename, int offset);
int audio_create_timer();
int audio_remove_timer();
int sound_channel_load_file2(int channel, const char* filename, int offset);
int sound_channel_play(int channel, int a2, int volume, int pan, int frequency);
int sound_channel_stop(int channel);
int sound_channel_set_frequency(int channel, int frequency);
int sound_channel_set_pan(int channel, int pan);
int sound_channel_set_volume(int channel, int volume);
void sub_401AF3(int channel, const char* filename, int a3, int a4);
int sub_401B46(int channel);
int sound_channel_is_playing(int channel);
int audio_release();
int map_sound_effects(const char* filename);
int unmap_sound_effects();
int sound_prepare(int sound_id, rct_sound *sound, int channels, int software);
int sound_duplicate(rct_sound* newsound, rct_sound* sound);
int sound_stop(rct_sound *sound);
int sound_stop_all();
void sound_bufferlost_check();
int sound_is_playing(rct_sound* sound);
int sound_play(rct_sound* sound, int looping, int volume, int pan, int frequency);
int sound_set_frequency(rct_sound* sound, int frequency);
int sound_set_pan(rct_sound* sound, int pan);
int sound_set_volume(rct_sound* sound, int volume);
int sound_load3dparameters();
int sound_load3dposition();
int dsound_count_devices();
rct_sound* sound_begin();
rct_sound* sound_next(rct_sound* sound);
rct_sound* sound_add(rct_sound* sound);
rct_sound* sound_remove(rct_sound* sound);
int sound_bufferlost_restore(rct_sound* sound);
struct rct_sound_effect* sound_get_effect(uint16 sound_id);
int dsound_create_primary_buffer(int a, int device, int channels, int samples, int bits);
int get_dsound_devices();
int sound_play_panned(int sound_id, int ebx, sint16 x, sint16 y, sint16 z);
void stop_completed_sounds();
void start_title_music();
void stop_other_sounds();
void stop_ride_music();
void stop_crowd_sound();
void stop_title_music();
void audio_init1();
void audio_init2(int device);
void audio_close();
void pause_sounds();
void toggle_all_sounds();
void unpause_sounds();
void stop_vehicle_sounds();

typedef enum {
	SOUND_LIFT_1 = 0,
	SOUND_TRACK_FRICTION_1 = 1,
	SOUND_LIFT_2 = 2,
	SOUND_SCREAM_1 = 3,
	SOUND_CLICK_1 = 4,
	SOUND_CLICK_2 = 5,
	SOUND_PLACE_ITEM = 6,
	SOUND_SCREAM_2 = 7,
	SOUND_SCREAM_3 = 8,
	SOUND_SCREAM_4 = 9,
	SOUND_SCREAM_5 = 10,
	SOUND_SCREAM_6 = 11,
	SOUND_LIFT_3 = 12,
	SOUND_PURCHASE = 13,
	SOUND_CRASH = 14,
	SOUND_LAYING_OUT_WATER = 15,
	SOUND_WATER_1 = 16,
	SOUND_WATER_2 = 17,
	SOUND_TRAIN_WHISTLE = 18,
	SOUND_TRAIN_CHUGGING = 19,
	SOUND_WATER_SPLASH = 20,
	SOUND_HAMMERING = 21,
	SOUND_RIDE_LAUNCH_1 = 22,
	SOUND_RIDE_LAUNCH_2 = 23,
	SOUND_COUGH_1 = 24,
	SOUND_COUGH_2 = 25,
	SOUND_COUGH_3 = 26,
	SOUND_COUGH_4 = 27,
	SOUND_RAIN_1 = 28,
	SOUND_THUNDER_1 = 29,
	SOUND_THUNDER_2 = 30,
	SOUND_RAIN_2 = 31,
	SOUND_RAIN_3 = 32,
	SOUND_BALLOON_POP = 33,
	SOUND_MECHANIC_FIX = 34,
	SOUND_SCREAM_7 = 35,
	SOUND_TOILET_FLUSH = 36,
	SOUND_CLICK_3 = 37,
	SOUND_QUACK = 38,
	SOUND_NEWS_ITEM = 39,
	SOUND_WINDOW_OPEN = 40,
	SOUND_LAUGH_1 = 41,
	SOUND_LAUGH_2 = 42,
	SOUND_LAUGH_3 = 43,
	SOUND_APPLAUSE = 44,
	SOUND_HAUNTED_HOUSE_SCARE = 45,
	SOUND_HAUNTED_HOUSE_SCREAM_1 = 46,
	SOUND_HAUNTED_HOUSE_SCREAM_2 = 47,
	SOUND_48 = 48,
	SOUND_49 = 49,
	SOUND_ERROR = 50,
	SOUND_51 = 51,
	SOUND_LIFT_4 = 52,
	SOUND_LIFT_5 = 53,
	SOUND_TRACK_FRICTION_2 = 54,
	SOUND_LIFT_6 = 55,
	SOUND_LIFT_7 = 56,
	SOUND_TRACK_FRICTION_3 = 57,
	SOUND_SCREAM_8 = 58,
	SOUND_TRAM = 59,
	SOUND_DOOR_OPEN = 60,
	SOUND_DOOR_CLOSE = 61,
	SOUND_62 = 62,
	SOUND_MAXID
} RCT2_SOUND;

#endif
