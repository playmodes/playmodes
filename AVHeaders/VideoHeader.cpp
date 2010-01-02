/*
 * AudioFrame.h
 *
 *  Created on: 09-oct-2008
 *      Author: arturo castro
 */

#include "VideoHeader.h"

VideoHeader::VideoHeader(VideoBuffer *buffer){
    //newFrameEvent.init("Playmodes.VideoHeader.newFrame");
    this->buffer=buffer;
    fps         =buffer->getFps();
    position    =buffer->size();
    oneFrame    =(pmTimeDiff)round(1000000.0/(float)fps);
    speed       =1;
    prevBufferPos=0;
    pct         =1;
    pctHasChanged=true;
    in          =0;
    out         =1;
    loopMode    =0;
    delay       =0;

}

VideoHeader::~VideoHeader(){
}

void VideoHeader::draw(){

    ofSetColor(250,250,250);
    float currentLength=(float)currentPos/(float)VIDEO_BUFFER_NUM_FRAMES*(float)ofGetWidth();
    sprintf(msgPos,"%i",currentPos);
    ofLine(currentLength,680,currentLength,720);

    float inPos  = in*(float)buffer->size()/(float)VIDEO_BUFFER_NUM_FRAMES*(float)ofGetWidth();
    float outPos = out*(float)buffer->size()/(float)VIDEO_BUFFER_NUM_FRAMES*(float)ofGetWidth();

    ofLine(inPos,680,inPos,730);
    ofLine(outPos,680,outPos,730);
    ofLine(inPos,730,outPos,730);
    //delay=0;
}

int VideoHeader::getFps(){
    return fps;
}

void VideoHeader::setFps(int fps){
    this->fps=fps;
}

VideoFrame * VideoHeader::getNextVideoFrame(){

        buffer->lock();
        if(pctHasChanged && buffer->size()){
            pct=CLAMP(pct,0,1);
            //cout << "vheader pct: "<< pct<< "\n";
            currentPos=pct*(buffer->size()-1);
            positionTS.update();
            position=buffer->getTotalFrames()-(buffer->size()-currentPos);
            pctHasChanged=false;
        }else {
            currentPos=getNextPosition();
            pct=(float)currentPos/(float)buffer->size();
        }
        VideoFrame * frame = buffer->getVideoFrame(currentPos);
        buffer->unlock();
        return frame;

}


//------------------------------------------
// returns the real position in the buffer
int VideoHeader::getNextPosition(){
    // calculate the next position in frames
    // from the beginning of the recording
    // based on speed
    oneFrame=(pmTimeDiff)(1000000.0/fps/speed);
    if((float)positionTS.elapsed()+(position-floor(position))*(float)abs(oneFrame)>=abs(oneFrame)){
        if(oneFrame!=0){
            position+=(float)positionTS.elapsed()/(float)oneFrame;

        }
        positionTS.update();

    }

    unsigned int buffer_size=buffer->size();

    // calculates the absolute position in frames
    // for all the duration
    if(loopMode && position>buffer->getTotalFrames()-(buffer_size-buffer_size*out))
        position=buffer->getTotalFrames()-(buffer_size-buffer_size*in);
    else if(loopMode && position<buffer->getTotalFrames()-(buffer_size-buffer_size*in))
        position=buffer->getTotalFrames()-(buffer_size-buffer_size*out);

    position=CLAMP(position,
                    buffer->getTotalFrames()-(buffer_size-buffer_size*in),
                    buffer->getTotalFrames()-(buffer_size-buffer_size*out));
    int backpos=buffer->getTotalFrames()-position;

    backpos=CLAMP(backpos,1,buffer_size);


    int nextPos=buffer_size-backpos-delay/oneFrame;

    return nextPos;
}

