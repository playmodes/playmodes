/*
 * BaseFilter.h
 *
 *  Created on: 09-oct-2008
 *      Author: arturo castro
 */

#ifndef BASEFILTER_H_
#define BASEFILTER_H_

#include "pipeline/Source.h"
#include "pipeline/Sink.h"

class BaseFilter: public Source, public Sink {
public:
	BaseFilter();
	virtual ~BaseFilter();


};

#endif /* BASEFILTER_H_ */
