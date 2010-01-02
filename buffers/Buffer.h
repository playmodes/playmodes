/*
 * Buffer.h
 *
 *  Created on: 09-oct-2008
 *      Author: arturo castro
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "Poco/Timestamp.h"
#include "frames/Frame.h"
#include "pipeline/Source.h"

class Buffer {
public:
	Buffer();
	virtual ~Buffer();

	unsigned int size();

    void lock();
    void unlock();

    virtual void stop()=0;
    virtual void resume()=0;
protected:
   ofMutex timeMutex;
};

#endif /* BUFFER_H_ */
