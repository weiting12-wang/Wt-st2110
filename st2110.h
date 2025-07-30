
#ifndef WT_SMPTE2110_H
#define WT_SMPTE2110_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  WT_OK = 0,
  WT_ERR_INIT = -1,
  WT_ERR_PARAM = -2,
  WT_ERR_NOMEM = -3,
  WT_ERR_INTERNAL = -4,
  WT_ERR_TIMEOUT = -5
} wt_status_t;

typedef enum {
  WT_PROTOCOL_ST20,
  WT_PROTOCOL_ST22,
  WT_PROTOCOL_ST30,
  WT_PROTOCOL_ST31
} wt_protocol_t;

typedef enum {
  WT_CODEC_RAW,
  WT_CODEC_H264,
  WT_CODEC_H265,
  WT_CODEC_PCM,
  WT_CODEC_LPCM
} wt_codec_t;

typedef void* wt_handle_t;

typedef struct {
  void* data;
  size_t size;
  uint64_t timestamp_ns;
  int width;   // only for video
  int height;  // only for video
  int channels; // only for audio
  int sample_rate; // only for audio
} wt_frame_t;

// Rx callback type
typedef void (*wt_rx_callback_t)(wt_handle_t handle, const wt_frame_t* frame, void* user_data);

//
// TX
//
wt_status_t wt_tx_create(wt_protocol_t proto, wt_codec_t codec,
                         const char* local_ip, const char* dest_ip, int port,
                         int width, int height, int fps,
                         wt_handle_t* handle);

wt_status_t wt_tx_start(wt_handle_t handle);
wt_status_t wt_tx_push_frame(wt_handle_t handle, const uint8_t* data, size_t size, uint64_t timestamp_ns);
wt_status_t wt_tx_push_packet(wt_handle_t handle, const uint8_t* data, size_t size, uint64_t timestamp_ns);
wt_status_t wt_tx_stop(wt_handle_t handle);
wt_status_t wt_tx_destroy(wt_handle_t handle);

//
// RX
//
wt_status_t wt_rx_create(wt_protocol_t proto, wt_codec_t codec,
                         const char* local_ip, const char* source_ip, int port,
                         int width, int height, int fps,
                         wt_handle_t* handle);

wt_status_t wt_register_rx_buffers(wt_handle_t handle, void** buffers, int buffer_count, size_t buffer_size);
wt_status_t wt_register_rx_callback(wt_handle_t handle, wt_rx_callback_t cb, void* user_data);

wt_status_t wt_rx_start(wt_handle_t handle);
wt_status_t wt_rx_stop(wt_handle_t handle);
wt_status_t wt_rx_destroy(wt_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif // WT_SMPTE2110_H
