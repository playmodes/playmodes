/*
 * AudioSink.h
 *
 *  Created on: 09-oct-2008
 *      Author: arturo castro
 */

#ifndef AUDIOSINK_H_
#define AUDIOSINK_H_

#include "frames/AudioFrame.h"
#include "../Sink.h"
#include "pipeline/events/AudioEvents.h"

class AudioSink: public AudioFrameListener {
public:
	AudioSink();
	virtual ~AudioSink();

    virtual void newAudioFrame(AudioFrame *frame){};

};

#endif /* AUDIOSINK_H_ */
