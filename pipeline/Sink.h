/*
 * Sink.h
 *
 *  Created on: 09-oct-2008
 *      Author: arturo castro
 */

#ifndef SINK_H_
#define SINK_H_

#include "frames/Frame.h"
#include "events/NewFrameListener.h"

class Sink: public NewFrameListener {
public:
	Sink();
	virtual ~Sink();

	void newFrame(plFrame * frame){};
};

#endif /* SINK_H_ */
