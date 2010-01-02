/*
 * AudioFrame.h
 *
 *  Created on: 09-oct-2008
 *      Author: arturo castro
 */

#include "AudioGrabber.h"

AudioGrabber::AudioGrabber() {
	//ofEvents::addAudioReceivedListener(this);

}
AudioGrabber::~AudioGrabber(){
}
void AudioGrabber::audioReceived(float * input, int bufferSize, int nChannels){
    AudioFrame * frame = new AudioFrame(input,bufferSize,nChannels);
    newFrameEvent.notify(this,*frame);
    frame->release();

    //cout << "audio: " << frame.getTimestamp().epochTime() << "\n";
}

float AudioGrabber::getFps(){
    return 44100.0/1024.0;
}
