#ifndef _DECODE_VIDEO
#define _DECODE_VIDEO

extern "C"{

#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>

}

class VideoDecoder{

public:

    VideoDecoder(const char *videoFileName);
    ~VideoDecoder();

    int getWidth() const {return width;}
    int getHeight() const {return height;}

    bool getNextFrame(uint8_t *buffer, uint32_t buffLen, uint32_t *outLen);

    bool init();

private:

    VideoDecoder(const VideoDecoder &);
    VideoDecoder& operator=(const VideoDecoder &);

    AVFormatContext *fmt_ctx;
    AVCodecContext *video_dec_ctx;
    AVCodecContext *audio_dec_ctx;
    int width, height;
    enum AVPixelFormat pix_fmt;
    AVStream *video_stream;
    AVStream *audio_stream;
    const char *src_filename;
    uint8_t *video_dst_data[4];
    int video_dst_linesize[4];
    int video_dst_bufsize;
    int video_stream_idx;
    int audio_stream_idx;
    AVFrame *frame;
    AVPacket pkt;
    int video_frame_count;
    int audio_frame_count;
    int got_frame;

    bool beganFlushCache;
    bool foundVideoFrame;


    int decode_packet(int *got_frame, int cached);
    int open_codec_context(
        int *stream_idx,
        AVCodecContext **dec_ctx, 
        AVFormatContext *fmt_ctx, 
        enum AVMediaType type);


    int get_format_from_sample_fmt(
        const char **fmt,
        enum AVSampleFormat sample_fmt);



    bool step();

};

#endif