#ifndef __LIBFLAC_H__
#define __LIBFLAC_H__
#ifdef __cplusplus
extern "C" {
#endif

#if defined FLAC_STATIC
#  define FLAC_EXPORT
#elif defined _MSC_VER
#  if defined FLAC_BUILD
#    define FLAC_EXPORT __declspec(dllexport)
#  else
#    define FLAC_EXPORT __declspec(dllimport)
#  endif
#elif defined __GNUC__
#  if defined FLAC_BUILD
#    define FLAC_EXPORT __attribute__((visibility("default")))
#  else
#    define FLAC_EXPORT
#  endif
#else
#  define FLAC_EXPORT
#endif
#include <stdint.h>

  typedef void *flac_file;

  FLAC_EXPORT enum flac_error{
    FLAC_NO_ERROR,
    FLAC_OPEN_FAILED,
    FLAC_BAD_FILE,
    FLAC_SEEK_TOO_FAR,
    FLAC_SEEK_FAILED
  };

  FLAC_EXPORT enum flac_error flac_open(char *path, flac_file *file);
  FLAC_EXPORT void flac_free(flac_file *file);
  FLAC_EXPORT uint8_t flac_channels(flac_file *file);
  FLAC_EXPORT uint32_t flac_sample_rate(flac_file *file);
  FLAC_EXPORT uint8_t flac_bits_per_sample(flac_file *file);
  FLAC_EXPORT uint64_t flac_sample_count(flac_file *file);
  FLAC_EXPORT uint64_t flac_read_s16(void *data, uint64_t samples, flac_file *file);
  FLAC_EXPORT uint64_t flac_read_s32(void *data, uint64_t samples, flac_file *file);
  FLAC_EXPORT uint64_t flac_read_f32(void *data, uint64_t samples, flac_file *file);
  FLAC_EXPORT enum flac_error flac_seek(uint64_t sample, flac_file *file);

  FLAC_EXPORT char *flac_strerror(enum flac_error error);

#ifdef __cplusplus
}
#endif
#endif
