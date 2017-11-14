#include "flac.h"
#define DR_FLAC_IMPLEMENTATION
#include "dr_flac.h"

FLAC_EXPORT enum flac_error flac_open(char *path, flac_file *file){
  drflac_file handle = drflac__open_file_handle(path);
  if(handle == NULL){
    return FLAC_OPEN_FAILED;
  }

  drflac *flac = drflac_open(drflac__on_read_stdio, drflac__on_seek_stdio, (void *)handle);
  if(file == NULL){
    drflac__close_file_handle(file);
    return FLAC_BAD_FILE;
  }

  *file = flac;
  return FLAC_NO_ERROR;
}

FLAC_EXPORT void flac_free(flac_file *file){
  drflac_close((drflac *)file);
}

FLAC_EXPORT uint8_t flac_channels(flac_file *file){
  return ((drflac *)file)->channels;
}

FLAC_EXPORT uint32_t flac_sample_rate(flac_file *file){
  return ((drflac *)file)->sampleRate;
}

FLAC_EXPORT uint8_t flac_bits_per_sample(flac_file *file){
  return ((drflac *)file)->bitsPerSample;
}

FLAC_EXPORT uint64_t flac_sample_count(flac_file *file){
  return ((drflac *)file)->totalSampleCount;
}

FLAC_EXPORT uint64_t flac_frame_count(flac_file *file){
  return ((drflac *)file)->totalSampleCount /
    ((drflac *)file)->channels;
}

FLAC_EXPORT uint64_t flac_read_s16(void *data, uint64_t samples, flac_file *file){
  return drflac_read_s16((drflac *)file, samples, data);
}

FLAC_EXPORT uint64_t flac_read_s32(void *data, uint64_t samples, flac_file *file){
  return drflac_read_s32((drflac *)file, samples, data);
}

FLAC_EXPORT uint64_t flac_read_f32(void *data, uint64_t samples, flac_file *file){
  return drflac_read_f32((drflac *)file, samples, data);
}

FLAC_EXPORT enum flac_error flac_seek(uint64_t sample, flac_file *file){
  sample *= ((drflac *)file)->channels;
  if(((drflac *)file)->totalSampleCount < sample){
    return FLAC_SEEK_TOO_FAR;
  }
  if(drflac_seek_to_sample((drflac *)file, sample) == DRFLAC_FALSE){
    return FLAC_SEEK_FAILED;
  }
  return FLAC_NO_ERROR;
}

FLAC_EXPORT char *flac_strerror(enum flac_error error){
  switch(error){
  case FLAC_NO_ERROR: return "No error ocurred.";
  case FLAC_OPEN_FAILED: return "The file could not be opened.";
  case FLAC_BAD_FILE: return "The file was not of the proper FLAC format.";
  case FLAC_SEEK_TOO_FAR: return "Tried to seek to a position outside of the range of the file.";
  case FLAC_SEEK_FAILED: return "Failed to seek to the requested position";
  default: return "Unknown error code.";
  }
}

